/*
 *  service.c -- Windows NT services support for binkd
 *
 *  service.c is a part of binkd project
 *
 *  Copyright (C) 2000 Dima Afanasiev, da@4u.net (Fido 2:5020/463)
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version. See COPYING.
 */
/*
 * $Id: service.c,v 2.8 2003/07/16 15:42:53 stas Exp $
 *
 * $Log: service.c,v $
 * Revision 2.8  2003/07/16 15:42:53  stas
 * Fix: restore -T option
 *
 * Revision 2.7  2003/07/16 15:08:49  stas
 * Fix NT services to use getopt(). Improve logging for service
 *
 * Revision 2.6  2003/06/11 09:00:44  stas
 * Don't try to install/uninstall/control service on incompatible OS. Thanks to Alexander Reznikov
 *
 * Revision 2.5  2003/06/09 18:00:19  stas
 * New command line parser (continue)
 *
 * Revision 2.4  2003/05/15 06:51:58  gul
 * Do not get 'i' and 'u' options from FTN-domain in -P option
 * (patch from Stanislav Degteff).
 *
 * Revision 2.3  2003/02/28 20:39:08  gul
 * Code cleanup:
 * change "()" to "(void)" in function declarations;
 * change C++-style comments to C-style
 *
 * Revision 2.2  2001/09/24 10:31:39  gul
 * Build under mingw32
 *
 * Revision 2.1  2001/08/24 13:23:28  da
 * binkd/binkd.c
 * binkd/readcfg.c
 * binkd/readcfg.h
 * binkd/server.c
 * binkd/nt/service.c
 *
 * Revision 2.0  2001/01/10 12:12:40  gul
 * Binkd is under CVS again
 *
 *
 */

#include <stdio.h>
#include <process.h>
#include <windows.h>
#include <io.h>
#include <direct.h>
#include <string.h>
#include <malloc.h>
#include "../Config.h"
#include "../tools.h"
#include "../common.h"
#include "../iphdr.h"
#include "service.h"

extern enum serviceflags service_flag;
extern char *service_name;
extern char *configpath;
extern int tray_flag;
#ifdef BINKD_DAEMONIZE
extern int daemon_flag;
#endif
extern int server_flag;
extern int client_flag;
extern int poll_flag;

extern int quiet_flag;
extern int verbose_flag;
extern int checkcfg_flag;
extern int no_MD5;
extern int no_crypt;

static char libname[]="ADVAPI32";
static char *srvname="binkd-service";
static char reg_path_prefix[]="SYSTEM\\CurrentControlSet\\Services\\";
static char reg_path_suffix[]="\\Parameters";
static SERVICE_STATUS_HANDLE sshan;
static SERVICE_STATUS sstat;
static int res_checkservice=0;
static DWORD dwErr=0;
static char **serv_argv=NULL;
static char **serv_envp=NULL;
static int service_main(int type);
extern int checkcfg_flag;
int isService=0;

static BOOL ReportStatusToSCMgr(DWORD dwCurrentState,
                         DWORD dwWin32ExitCode,
                         DWORD dwWaitHint)
{
  static DWORD dwCheckPoint = 1;
  BOOL fResult = TRUE;

  if (dwCurrentState == SERVICE_START_PENDING)
    sstat.dwControlsAccepted = 0;
  else
    sstat.dwControlsAccepted = SERVICE_ACCEPT_STOP;
  sstat.dwCurrentState = dwCurrentState;
  sstat.dwWin32ExitCode = dwWin32ExitCode;
  sstat.dwWaitHint = dwWaitHint;

  if ( ( dwCurrentState == SERVICE_RUNNING ) ||
       ( dwCurrentState == SERVICE_STOPPED ) )
    sstat.dwCheckPoint = 0;
  else
    sstat.dwCheckPoint = dwCheckPoint++;

  fResult = SetServiceStatus( sshan, &sstat);
  return fResult;
}

BOOL SigHandler(DWORD SigType);

static void WINAPI ServiceCtrl(DWORD dwCtrlCode)
{
  switch(dwCtrlCode)
  {
  case SERVICE_CONTROL_STOP:
    ReportStatusToSCMgr(SERVICE_STOP_PENDING, NO_ERROR, 0);
    SigHandler(CTRL_SERVICESTOP_EVENT);
    return;
  case SERVICE_CONTROL_INTERROGATE:
  default:
    break;
  }
  ReportStatusToSCMgr(sstat.dwCurrentState, NO_ERROR, 0);
}

void atServiceExit(void)
{
  char *sp;

  if(serv_argv)
  {
    sp=serv_argv[0];
    free(serv_argv);
    free(sp);
    serv_argv=NULL;
  }
  if(serv_envp)
  {
    sp=serv_envp[0];
    free(serv_envp);
    free(sp);
    serv_envp=NULL;
  }
  ReportStatusToSCMgr(SERVICE_STOPPED, dwErr, 3000);
  if((checkcfg_flag==2)&&(res_checkservice>0))
    service_main(4);
}

int binkd_main(int argc, char **argv, char **envp);
static void ServiceStart(LPTSTR args)
{
  HKEY hk;
  LONG rc;
  DWORD dw, sw=MAXPATHLEN+1;
  int i, argc;
  char *sp=(char*)malloc(sw);
  char *env=NULL;

  strcpy(sp, reg_path_prefix);
  strcat(sp, srvname);
  strcat(sp, reg_path_suffix);
  isService=1;

  atexit(atServiceExit);
  for(;;)
  {
    if(RegOpenKey(HKEY_LOCAL_MACHINE, sp, &hk)!=ERROR_SUCCESS)
    {
      dwErr=GetLastError();
      break;
    }
    if(RegQueryValueEx(hk, "path", NULL, &dw, sp, &sw)!=ERROR_SUCCESS)
    {
      dwErr=GetLastError();
      break;
    }
    SetCurrentDirectory(sp);
    sw=MAXPATHLEN+1;
    switch(RegQueryValueEx(hk, "args", NULL, &dw, sp, &sw))
    {
    case ERROR_SUCCESS: break;
    case ERROR_MORE_DATA:
      free(sp);
      sp=(char*)malloc(sw);
      if(RegQueryValueEx(hk, "args", NULL, &dw, sp, &sw)==ERROR_SUCCESS)
        break;
    default:
      dwErr=GetLastError();
    }
    if(dwErr!=NO_ERROR)
      break;
    sw=0;
    rc=RegQueryValueEx(hk, "env", NULL, &dw, env, &sw);
    if(((rc==ERROR_MORE_DATA)||(rc==ERROR_SUCCESS))&&(sw))
    {
      env=(char*)malloc(sw);
      if(RegQueryValueEx(hk, "env", NULL, &dw, env, &sw)!=ERROR_SUCCESS)
      {
        free(env);
        env=NULL;
      }
    }
    RegCloseKey(hk);
    hk=0;

    if (!ReportStatusToSCMgr(SERVICE_RUNNING, NO_ERROR, 0)) break;

    if(env)
    {
      for(i=argc=0;env[i];i+=strlen(env+i)+1) argc++;
      serv_envp=(char**)malloc(sizeof(char*)*(argc+1));
      for(i=argc=0;env[i];i+=strlen(env+i)+1) serv_envp[argc++]=env+i;
      serv_envp[argc++]=NULL;
    }
    for(i=argc=0;sp[i];i+=strlen(sp+i)+1) argc++;
    serv_argv=(char**)malloc(sizeof(char*)*(argc+1));
    for(i=argc=0;sp[i];i+=strlen(sp+i)+1) serv_argv[argc++]=sp+i;
    serv_argv[argc]=NULL;

    binkd_main(argc, serv_argv, serv_envp);
    break;
  }
  if(hk) RegCloseKey(hk);
  atServiceExit();
}

static void WINAPI ServiceMain(LPTSTR args)
{
  sshan=RegisterServiceCtrlHandler(srvname, ServiceCtrl);
  while(sshan)
  {
    sstat.dwServiceType = SERVICE_WIN32_OWN_PROCESS | (tray_flag? SERVICE_INTERACTIVE_PROCESS : 0);
    sstat.dwServiceSpecificExitCode = 0;
    if (!ReportStatusToSCMgr(SERVICE_START_PENDING, NO_ERROR, 3000)) break;
    ServiceStart(args);
    break;
  }
  if(sshan)
    atServiceExit();
  exit(0);
}

static DWORD srvtype = SERVICE_WIN32_OWN_PROCESS;
static int service_main(int type)
{
  SC_HANDLE sman=NULL, shan=NULL;
  HINSTANCE hl;
  int i, rc=0;

  if((!type)||(type==6))
  {
    hl=LoadLibrary(libname);
    if(!hl) return 1;
    if(!GetProcAddress(hl, "OpenSCManagerA"))
    {
      FreeLibrary(hl);
      return 2;
    }
    FreeLibrary(hl);
  }

  sman=OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
  if(!sman)
  { int err = GetLastError();
    if(res_checkservice)
      Log(1, "OpenSCManager failed: %s",tcperr(err));
    else if(err==ERROR_ACCESS_DENIED)
    {
      Log(isService?1:-1, "Access to NT service controls is denied.");
    }
    return 3;
  }
  if(!type)  /* return 0 if we can install service */
  {
    CloseServiceHandle(sman);
    return 0;
  }
  shan=OpenService(sman, srvname, SERVICE_ALL_ACCESS);

  switch(type)
  {
  case 6:
    if(!shan) rc=1; else
    if(!QueryServiceStatus(shan,&sstat)) rc=2; else
    if(sstat.dwCurrentState != SERVICE_START_PENDING) rc=3;
    break;
  case 1: /* return 0 if service installed, or 1 if not */
    if(!shan) rc=1;
    break;
  case 5:
  case 2: /* install, if we don have one */
    if(!shan)
    {
      char path[MAXPATHLEN+1];
      if(GetModuleFileName(NULL, path, MAXPATHLEN)<1)
      {
        Log(1, "Error in GetModuleFileName()=%s", tcperr(GetLastError()) );
        CloseServiceHandle(sman);
        return 1;
      }
      shan=CreateService(sman, srvname, srvname, SERVICE_ALL_ACCESS,
        srvtype, SERVICE_AUTO_START,
        SERVICE_ERROR_NORMAL, path, NULL, NULL, NULL, NULL, NULL);
      if(!shan)
        Log(1, "Error in CreateService()=%s", tcperr(GetLastError()) );
    }
    if(!shan) rc=1;
    if((rc)||(type==2)) break;
  case 4: /* start service */
    if(!shan)
    {
      Log(-1, "Service \"%s\" not installed...", srvname);
      rc=1;
      break;
    }
    if(StartService(shan, 0, NULL))
    {
      int j;
      for(i=j=0;(i<30)&&(QueryServiceStatus(shan,&sstat));i++)
      {
        if((sstat.dwCurrentState == SERVICE_START_PENDING)||
          ((i<3)&&(sstat.dwCurrentState != SERVICE_RUNNING))||((j++)<9))
        {
          printf(".");
          Sleep(300);
        }
        else break;
      }
      putchar('\n');
      if(sstat.dwCurrentState != SERVICE_RUNNING)
      {
        Log(-1, "Service not started...");
        rc=1;
      }
    }
    else
    {
      Log(1, "Error in StartService()=%s", tcperr(GetLastError()) );
      rc=1;
    }
    break;
  case 3: /* stop & uninstall. */
    if(!shan) break;
    /* try to stop the service  */
    if(ControlService(shan, SERVICE_CONTROL_STOP, &sstat))
    {
      for(i=0;(i<30)&&(QueryServiceStatus(shan,&sstat));i++)
      {
        if((sstat.dwCurrentState==SERVICE_STOP_PENDING) ||
          ((i<3)&&(sstat.dwCurrentState!=SERVICE_STOPPED)))
        {
          printf(".");
          Sleep(300);
        }
        else break;
      }
      putchar('\n');
      if(sstat.dwCurrentState!=SERVICE_STOPPED)
        Log(1, "Unable to stop service!");
    }
    if(!DeleteService(shan))
    {
      Log(1, "Error in DeleteService()=%s", tcperr(GetLastError()) );
      rc=1;
    }
    break;
  }

  if(shan) CloseServiceHandle(shan);
  CloseServiceHandle(sman);
  return rc;
}

static HWND mainWindow;
static NOTIFYICONDATA nd;
static int wstate = 0;

static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam,  LPARAM lParam)
{
    if ((lParam == WM_LBUTTONDBLCLK) || (lParam == WM_RBUTTONUP))
    {
    	ShowWindow(mainWindow, SW_RESTORE);
        SetForegroundWindow(mainWindow);
        Shell_NotifyIcon(NIM_DELETE, &nd);
        wstate = 2;
    }
    return 1;
}

static void closeProcess(void)
{
    Shell_NotifyIcon(NIM_DELETE, &nd);
    ShowWindow(mainWindow, SW_RESTORE);
}

static void processKeyCode(WORD kc, DWORD cs, HANDLE out)
{
    if ((cs & SHIFT_PRESSED) &&
        ((kc == VK_UP) || (kc == VK_DOWN) || (kc == VK_LEFT) || (kc == VK_RIGHT)))
    {
        CONSOLE_SCREEN_BUFFER_INFO cb;
        if(!GetConsoleScreenBufferInfo(out, &cb)) return;
        switch(kc)
        {
            case VK_UP: cb.dwSize.Y-=10; break;
            case VK_DOWN: cb.dwSize.Y+=10; break;
            case VK_LEFT: cb.dwSize.X-=10; break;
            case VK_RIGHT: cb.dwSize.X+=10; break;
        }
        SetConsoleScreenBufferSize(out, cb.dwSize);
    }
}

extern int percents;
extern int conlog;
extern int printq;
extern int quiet_flag;
static void wndthread(void *par)
{
    WINDOWPLACEMENT wp;
    WNDCLASS rc;
    char *cn = "testclass";
    char buf[256];
    char bn[20];
    ATOM wa;
    HWND wnd;
    HICON hi;
    HANDLE in, out;
    int i;

    i = GetConsoleTitle(buf, sizeof(buf));
    if (i < 0) i = 0;
    buf[i] = 0;
    sprintf(bn, "%x", (unsigned int)GetCurrentThreadId());
    for (i = 0; i < 40; i++)
    {
        SetConsoleTitle(bn);
        if (((mainWindow = FindWindow(NULL, bn)) != NULL) || (isService)) break;
        Sleep(100);
    }
    SetConsoleTitle(buf);
    if ((!IsWindow(mainWindow)) || (!mainWindow))
    {
        if (!AllocConsole())
        {
            Log(-1, "unable to find main window... (%s)", bn);
            return;
        }
        else
        {
            HANDLE ha = GetStdHandle(STD_OUTPUT_HANDLE);
            int hCrt = _open_osfhandle((long) ha, 0x4000);
            FILE *hf = _fdopen( hCrt, "w" );
            *stdout = *hf;

            ha = GetStdHandle(STD_ERROR_HANDLE);
            hCrt = _open_osfhandle((long) ha, 0x4000);
            hf = _fdopen( hCrt, "w" );
            *stderr = *hf;
            setvbuf( stdout, NULL, _IONBF, 0 );
            setvbuf( stderr, NULL, _IONBF, 0 );

            strcpy(buf, srvname);
            SetConsoleTitle(srvname);
            for (i = 0; i < 40; i++)
            {
                if ((mainWindow = FindWindow(NULL, srvname)) != NULL) break;
                Sleep(100);
            }
            if (!mainWindow) return;
            isService = 0;
        }
    }

    hi = (HICON)SendMessage(mainWindow, WM_GETICON, ICON_SMALL, 0);
    if (!hi)
    {
        hi = (HICON)SendMessage(mainWindow, WM_GETICON, ICON_BIG, 0);
    }
    if (!hi)
    {
        hi = LoadIcon(NULL, IDI_INFORMATION);
    }

    memset(&rc, 0, sizeof(rc));
    rc.lpszClassName = cn;
    rc.lpfnWndProc = WindowProc;
    wa = RegisterClass(&rc);
    if (!wa)
    {
        Log(-1, "unable to register class...");
        return;
    }
    wnd = CreateWindow(cn, "", 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL);
    if (!wnd)
    {
        Log(-1, "Unable to create message window...");
        return;
    }
    memset(&nd, 0, sizeof(nd));
    nd.cbSize = sizeof(nd);
    nd.hWnd = wnd;
    nd.uID = 1111;
    nd.uFlags = NIF_TIP|NIF_MESSAGE|NIF_ICON;
    nd.uCallbackMessage = 1111;
    nd.hIcon = hi;
    atexit(closeProcess);
    strncpy(nd.szTip, buf, 63);
    i = 1000;
    in = GetStdHandle(STD_INPUT_HANDLE);
    out = GetStdHandle(STD_OUTPUT_HANDLE);
    for (;;)
    {
        MSG msg;
        INPUT_RECORD cb;
        DWORD dw;
        if (in)
        {
            while(PeekConsoleInput(in, &cb, 1, &dw))
            {
                if (!dw)
                {
                    break;
                }
                ReadConsoleInput(in, &cb, 1, &dw);
                if ((cb.EventType == KEY_EVENT) && (cb.Event.KeyEvent.bKeyDown))
                {
                    processKeyCode(cb.Event.KeyEvent.wVirtualKeyCode,
                        cb.Event.KeyEvent.dwControlKeyState, out);
                }
            }
	    }

        while(PeekMessage( &msg, wnd, 0, 0, PM_REMOVE))
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        if ((i++) < 10)
        {
            Sleep(50);
            continue;
        }
        i = 0;
        if (wstate != 1)
        {
            memset(&wp, 0, sizeof(wp));
            wp.length = sizeof(wp);
            if ((GetWindowPlacement(mainWindow, &wp)) &&
                (wp.showCmd == SW_SHOWMINIMIZED))
            {
    	        wstate = 1;
                Shell_NotifyIcon(NIM_ADD, &nd);
                ShowWindow(mainWindow, SW_HIDE);
            }
    	}
    }
}

int build_service_parameter(char**argv,char**asp)
{ int len;

  *asp=(char*)calloc(1,strlen(argv[0]) + strlen(srvname) +3 + strlen(configpath) +11 +3*11); /* max: 11 options */
  len = sprintf(*asp, "%s", argv[0]) + 1;
  if(srvname){
    strcpy(*asp+len,"-S");
    len+=3;
    strcpy(*asp+len,srvname);
    len+=strlen(srvname)+1;
  }
#if defined(WIN32) && !defined(BINKDW9X)
  if(tray_flag){
    strcpy(*asp+len,"-T");
    len+=3;
  }
#endif
  if(server_flag){
    strcpy(*asp+len,"-s");
    len+=3;
  }
  if(client_flag){
    strcpy(*asp+len,"-c");
    len+=3;
  }
  if(poll_flag){
    strcpy(*asp+len,"-p");
    len+=3;
  }
  if(quiet_flag){
    strcpy(*asp+len,"-q");
    len+=3;
  }
  if(verbose_flag){
    strcpy(*asp+len,"-v");
    len+=3;
  }
  if(checkcfg_flag){
    strcpy(*asp+len,"-C");
    len+=3;
  }
  if(no_MD5){
    strcpy(*asp+len,"-m");
    len+=3;
  }
  if(no_crypt){
    strcpy(*asp+len,"-r");
    len+=3;
  }
  if(configpath){
    strcpy(*asp+len,configpath);
    len+=strlen(configpath)+1;
  }
  len++;

  return len;
}

int service(int argc, char **argv, char **envp)
{
  int i, j, k, len;
  char *sp=NULL;
  char *esp=NULL, *asp=NULL;
  HKEY hk=0;

  if(service_flag==w32_noservice) return 0;
  else{
    if( W32_CheckOS(VER_PLATFORM_WIN32_NT) )
    {
      Log(0,"Can't operate witn Windows NT services: incompatible OS type");
      return 1;
    }
  }


  if(service_name) srvname = service_name;  /* Use service name from command line if specified */

  if (tray_flag)
  {
     srvtype |= SERVICE_INTERACTIVE_PROCESS;
#ifdef HAVE_THREADS
#ifdef __MINGW32__
     _beginthread(wndthread, 0, NULL);
#else
     _beginthread(wndthread, 0, 0, NULL);
#endif
#endif

  }

  j=checkservice();

  if(service_flag && j==CHKSRV_CANT_INSTALL){
      Log(0, "Can't operate witn Windows NT services...");
  }

  switch(service_flag){

  case w32_installservice:
    if (j==CHKSRV_INSTALLED){
      Log(-1, "Service %s already installed...", srvname);
      exit(0);
    }else{

      sp=(char*)malloc(MAXPATHLEN+1);
      strcpy(sp, reg_path_prefix);
      strcat(sp, srvname);
      if(!service_main(2))
      {
        Log(-1, "Service '%s' installed...", srvname);
      }
      else
      {
        Log(1, "Unable to install service %s!",srvname);
        free(sp);
        return -1;
      }
      if( RegOpenKey(HKEY_LOCAL_MACHINE, sp, &hk)==ERROR_SUCCESS )
      {
        RegCloseKey(hk);
        hk = NULL;
      }
      else
      {
        Log(1, "Unable to open registry key %s!", sp);
        free(sp);
        return -1;
      }

      /* build arguments list for service */
      len = build_service_parameter(argv,&asp);

      /* build enviroment */
      if(envp)
      {
        for(i=j=0; envp[i];i++) j+=strlen(envp[i])+1;
        j += strlen("BINKD_RERUN=NTSERVICE");
        esp=(char*)malloc(++j);
        for(i=j=0; envp[i];i++)
        {
          strcpy(esp+j, envp[i]);
          j+=strlen(envp[i])+1;
        }
          strcpy(esp+j, "BINKD_RERUN=NTSERVICE");
        esp[j++]=0;
      }

      strcat(sp, reg_path_suffix);
      k=1;
      if((RegOpenKey(HKEY_LOCAL_MACHINE, sp, &hk)==ERROR_SUCCESS) ||
         (RegCreateKey(HKEY_LOCAL_MACHINE, sp, &hk)==ERROR_SUCCESS))
      for(;;)
      {
        if(RegSetValueEx(hk, "args", 0, REG_BINARY, asp, len)!=ERROR_SUCCESS) break;
        if((esp)&&
           (RegSetValueEx(hk, "env", 0, REG_BINARY, esp, j)!=ERROR_SUCCESS)) break;
        if(GetCurrentDirectory(MAXPATHLEN, sp)<1) break;
        if(RegSetValueEx(hk, "path", 0, REG_SZ, sp, strlen(sp))!=ERROR_SUCCESS) break;
        k=0;
        break;
      }
      RegCloseKey(hk);
      if(k)
      {
        Log(1, "Unable to store data in registry...");
        res_checkservice=(-1);
      }
      free(sp);
      free(asp);
      if(esp) free(esp);
      if(!service_main(4))
      {
        Log(-1, "Service '%s' started.", srvname);
        exit(0);
      }
      Log(1, "Unable to start service!");
      return -1;
    }
    break;

  case w32_uninstallservice:
    if (j==CHKSRV_NOT_INSTALLED){
      Log(-1, "Service '%s' already uninstalled...", srvname);
      exit(0);
    }else{
      if(service_main(3))  return argc;
      Log(-1, "Service '%s' uninstalled.", srvname);
      exit(0);
    }
    break;

  default:
    break;
  }
  return 0;
}

/* Return:
 * -1 : can't install service
 *  1 : Service not installed
 *  2 : Service installed
 */
int checkservice(void)
{
  if(res_checkservice) return res_checkservice;
  if(service_main(0)) return res_checkservice=(CHKSRV_CANT_INSTALL);
  if(service_main(1)) return res_checkservice=CHKSRV_NOT_INSTALLED;
  return res_checkservice=CHKSRV_INSTALLED;
}

/* Try connect to NT service controller
 * Return 1 if program running standalone or system error
 */
int tell_start_ntservice(void)
{
  SERVICE_TABLE_ENTRY dt[]= { {"", (LPSERVICE_MAIN_FUNCTION)ServiceMain}, {NULL, NULL}};
  int res=0;

  if(!StartServiceCtrlDispatcher(dt)){  /* Can't start service */
    switch( GetLastError() ){
    case ERROR_FAILED_SERVICE_CONTROLLER_CONNECT:  /*1063*/
       res=1;   /* Program running not an as service */
       if (tray_flag)
         _beginthread(wndthread, 0, NULL);
       break;
    case ERROR_SERVICE_ALREADY_RUNNING:
       Log(-1,"Error %u: Double call of StartServiceCtrlDispatcher()",ERROR_SERVICE_ALREADY_RUNNING);
       break;
    case ERROR_INVALID_DATA:
       Log(-1,"Error %u: The specified dispatch table contains entries that are not in the proper format.", ERROR_INVALID_DATA);
       break;
    default:
       Log(-1, "tell_start_ntservice(): %s",TCPERR() );
    }
  }
  return res;
}
