        BinkD FAQ

        �⢥�� �� ��� ��������� ������ �� FTN-������� binkd
        $Date: 2004/03/11 14:39:47 $

    ��� FAQ ��⠢��� �� �᭮�� ����ᮢ, ��� ����������
� �宪���७樨 RU.BINKD. ����� �⢥⮢ �᭮���� �� ४���������
ࠧࠡ��稪��.
�� �ᥬ� �।������ﬨ � ����砭�ﬨ ����: Stas Degteff 2:5080/102

    01. ��� ����� ᢥ��� ����� BinkD.
    02. �� ⠪�� binkd
    03. ��⮪�� binkp
    04. �� ⠪�� � ��祬 �㦥� ����� fidonet.net
    05. binkd �� ᮥ�������. �� ������?
    06. ��� ����㦨�� binkd � HTTP-�ப�.
    07. ��� ����㦨�� binkd � SOCKS-�ப�.
    08. IP-�����: ��� ���⠢��� binkd ������ ����� � ���� (�������).
    09. �訡�� "start_file_transfer: .: Permission denied"
    10. binkd � ������: ��⮬���᪨� ������ � ��ᮥ�������.
    11. ������� ���䨣 �� ࠡ���饬 binkd. ����� ���������� ���������?
    12. ��� ����㦨�� binkd c T-mail/IP?
    13. ������� �� � ��த� ��� ���� ��� �������� ��� unix?
    14. Binkd ����� ����������, ��� �⪠ ᪮��⭠�.
    15. ��祬� BinkD �� �������� ��।������ ��ࠬ���� �� ����᪥ �� inetd
    16. ����� �� ᤥ���� FREQ � binkd.
    17. ��� �������� binkd � 䨤�-�⠭��, ࠡ������ �� ������.
    18. ����� �� �ਥ�� 䠩�� �� ᮧ������, �ணࠬ�� �� ����᪠����.
    19. �� ࠡ�⠥� skipmask.
    20. Binkd ��� DOS.
    21. Binkd ��� Windows 3.x.
    22. ����� FTN-������ � binkd.
    23. ��� ࠡ�⠥� "domain ... alias-for ..." � ���䨣�
    24. �� ����砥� �������⨪� "send: TCP/IP error (-10000)", ��� �� �����?
    25. Argus (Radius) � binkd: �訡�� Argus "Aborting due to carrier loss"
    26. � �������� ��⡠㭤� - ᨬ��� ��������� � binkd �� ����� ��⠫��.
    27. ���� �� ����������� ����᪠ �ਫ������ � binkd �� ᮡ���?
    28. � 祬 ࠧ��稥 ����� binkd/w32 � binkd/w9x?
    29. ���쭮 �� 墠⠥� �� � binkd! � �६� ᨭ�஭���஢��� �����.
    A1. �����㦨� ��� � binkd!
    A2. ��� �易���� � ࠧࠡ��稪���.
    A3. ���� �ࠧ� 㧭����� �� ���������� � binkd!
    A4. � ����� binkd �㤥� ������ ... ?

----------------------------------------------------------------------------

    01. ��� ����� ᢥ��� ����� BinkD, ���㬥����, FAQ � ��.

    ����-�� AFTNBINKD.

    �஬� ⮣�, � Internet'�:

    ������, ���������� ����� � ��. (Pavel Gulchouck 2:463/68):
    ftp://cvs.happy.kiev.ua/pub/fidosoft/mailer/binkd/
    ��ઠ�� (Matt Bedynek 1:106/1):
    ftp://fido.thunderdome.ws/pub/mirror/binkd/

    ����:
    �㡫��� CVS
       :pserver:binkd@cvs.happy.kiev.ua:/cvs , ����� binkd, ��஫� ���⮩
       �ਬ��� ������.
       ������������ �� �ࢥ� cvs:
       cvs -d :pserver:binkd@cvs.happy.kiev.ua:/cvs login
       ������� ��᫥���� ��室���� ��⪨ current:
       cvs -d :pserver:binkd@cvs.happy.kiev.ua:/cvs co binkd
       ������� ��᫥���� ��室���� ��⪨ binkd 0.9.5-stable:
       cvs -d :pserver:binkd@cvs.happy.kiev.ua:/cvs co -r binkd-0_9_5-stable binkd
       ������� ��室���� binkd 0.9.6-release:
       cvs -d :pserver:binkd@cvs.happy.kiev.ua:/cvs co -r binkd-0_9_6 binkd
    ftp://cvs.happy.kiev.ua/pub/fidosoft/mailer/binkd/snapshot (�᭮����)
    ftp://ftp.grumbler.org/pub/binkd/current (��ઠ��, ���������� 23:50 UTC+5)

    ���㬥���� (����.), ���������� ����� � ��.:
    http://www.doe.carleton.ca/~nsoveiko/fido/binkd/

    ��������� ����� �� val khokhlov (perl):
    http://www.vk.kiev.ua/create/soft.html#bnkds

    Man page, ���ᠭ�� binkp, ����୨�� � ��. (Stas Degteff 2:5080/102):
    http://binkd.grumbler.org/

    ��� FAQ:
    http://binkd.grumbler.org/binkdfaq.shtml (��� .txt)

    � ��樠���� ���筨��� ����୨�� binkd ��������� ⠪, �⮡� ��������
OS, ��������� � ᯮᮡ ᡮન.

    ���ᨨ ��� Windows (32bit):
    binkd.exe, binkdw32.exe - binkd/w32, ���᮫��, ᪮�����஢�� MS Visual C
    binkd-dll.exe   - binkd/w32, ���᮫��, MS Visual C, �ॡ�� msvcrt.dll
    binkd-mingw.exe - binkd/w32, ���᮫��, MinGW32, �ॡ�� msvcrt.dll
    binkd9x.exe     - binkd/w9x, ���������, ᪮�����஢�� MS Visual C
    binkd9x-dll.exe - binkd/w9x, ���������, MS Visual C, �ॡ�� msvcrt.dll
    binkd9x-mingw.exe - binkd/w9x, ���������, MinGW32, �ॡ�� msvcrt.dll

    ���ᨨ ��� OS/2:
    binkd2.exe   - ��������� Watcom C, ��ૠ ���
    binkd2e.exe  - emx, 㬥�� �����㦠�� ��૮��� dll � ࠡ���� ��� ���
    binkd2pl.exe - emx, perl ᫨������ ����᪨ (�.�. ��૮��� dll �� �㦭�)
    binkd2eo.exe - emx/omf (multithread), ��ૠ ���.


----------------------------------------------------------------------------


    02. �� ⠪�� binkd

    ����� - 䨤��� ������, ࠡ���騩 �१ ���୥� �� ��⮪��� binkp
(FSP-1011). ��� ��⮪�� �����ন������ ⠪�� �����ࠬ� ���� (win32; RitLabs;
http://www.ritlabs.com), BForce (unix), �ணࠬ��� Internet Rex (DOS/W32/OS2) �
BeeMail (win32; Stephen Proffitt, 1:105/10; http://beemail.gexonline.net/)

    ��ࠪ���⨪�:
    - freeware, ������ ��室����
    - ���ᨨ ��� Unix (linux, freebsd, SCO, ...), OS/2 (native & EMX),
      Windows NT & Windows 95
    - ����������� ࠡ��� ������� ��� Unix � �ࢨᮬ Windows NT/2000
    - ���⮥ TCP-ᮥ������� (楫��⭮��� ������ ��᫥�������� �� �஢�� TCP)
    - BSO (bink-style outbound)
    - LBSO (Long BSO)
    - ������� ��ਠ�� � �����প�� ASO (Amiga-style outbound),
      �����࠭���� � ���� ���祩 (�. �� �ࢥ�� �����প�)
    - �࠭���� ��⥩ � ?LO 䠩��� (�ᯮ������ �� ࠧ��饭�� ��⡠㭤�
      �� �⥢�� ��᪠�)
    - ���ᮭ���� 䠩������ ��� ��ࠢ�塞�� � �ਭ������� 䠩��� ��� �������
      㧫�
    - �����প� 䠩����ᮢ T-mail � The Brake!
    - �����প� �࠭��樨 FTN-���ᮢ � �������� ��� (*.fidonet.net)
    - �����প� 䠩�� ��஫�� �⨫� T-mail - ��稭�� � 0.9.4 � ifcico - c 1.0
    - �����প� FREQ � �ᯮ�짮������ SRIF
    - ᮧ����� 䫠��� �� �ਥ�� 䠩�� (�� ��᪥)
    - ����� �ணࠬ� �� �ਥ�� 䠩�� (�� ��᪥)
    - �⪠� �� �ਥ�� 䠩�� (�� ��᪥) - ��稭�� � 0.9.4
    - ࠡ�� �१ HTTP ��� SOCKS �ப�-�ࢥ� (��稭�� � ���ᨨ 0.9.3.https)
    - ��஢���� ��஫�� (MD5) - ��稭�� � ५��� 0.9.4
    - ��஢���� ��䨪� - ��稭�� � 0.9.5
    - �஢�ઠ IP-���� 㤠������� 㧫� �� �室��� ᮥ�������� -
      ��稭�� � 0.9.5


----------------------------------------------------------------------------


    03. ��⮪�� binkp

    �����஢�� ��������: binkd protocol. ���ᠭ � FSP-1011 (FIDOnet standard
proposal - �।������� ��� ���㦤����/��ᬮ�७�� FTSC �⠭����) �
���� 24554 �뤥��� ��� binkp � RFC-1700 (request for comments,
���᪠��� IANA).
    �ᯮ����騩 �����஭��� TCP-ᮥ������� ��⮪�� ������ 䠩����,
ࠧࠡ�⠭�� ��� FTN-������ binkd. �� 㬮�砭�� �ᯮ���� ���� 24554.
    �������� ��� ���ᨨ ��⮪���: 1.0 � 1.1, ���⭮ ᮢ���⨬�.
�᭮���� �⫨稥 ���ᨨ 1.1 � ���������� ������ FREQ �� �६� ��ᨨ. �஬�
⮣�, binkp 1.1 � �����饥 �६� ����� ��樨 NR (non-reliable mode,
०�� ࠡ��� � ���������� ������� �裡) � ND (no dupes mode, ०�� �����
�� ����୮� ��।�� 䠩���), MD5 (��஢���� ��஫��), CRYPT (��஢����
��䨪�).
    ����� ��⮪��� 1.1 �����ন������ �����஬ binkd, ����� 1.0 ॠ��������
� ������ Argus � ��� ������ (� ��� binkp ॠ������� � ����������� ᮡ�⢥�����
��堭���� ��ࠡ�⪨ FREQ � ��㣨�� ��������ﬨ), � MBSE, Internet Rex, BForce
� ��㣨�. � ����� Internet Rex (2.24 � ����� �������) ॠ������� ⠪�� ᢮�
(��ᮢ���⨬�) ��ਠ�� binkp/1.1.
    ���ᠭ�� ��⮪��� �� ���᪮� �몥 ����� ���:
http://binkd.grumbler.org/binkp/


----------------------------------------------------------------------------


    04. �� ⠪�� � ��祬 �㦥� ����� fidonet.net

    fidonet.net - �����, ��ॣ����஢���� ��� ��⥬� �࠭��樨 FTN-���ᮢ
� ������� ����� internet. �ᯮ������ �२����⢥��� �� binkp-ᮥ��������.
���� 1:2/3 �८�ࠧ���� � ����� f3.n2.z1.fidonet.net (��� �����: 1:2/3.4
�८�ࠧ���� � p4.f3.n2.z1.fidonet.net), ��⥬ binkd (��� ��㣮� binkp-������)
����砥� �।�⢠�� ����樮���� ��⥬� IP-���� 㧫�. �᫨ ����� �������
- ����� ������� ��⠭����� ᮥ�������.
    ��室� �� �⮣� �뫠 ��⠢���� "����� ������ fidonet.net": �������� ���
� ���� fidonet.net �뤠���� 㧫��, ���������騬 � �������, ����騬
����ﭭ� IP-���� ��� �������� ��� � ��㣫����筮 �⢥��騬 �� ����� 24554
�� ��⮪��� binkp.


----------------------------------------------------------------------------


    05. binkd �� ᮥ�������, ᮮ�頥� �� ⠩���� (timeout). �� ������?

    1. �஢����, �⢥砥� �� 㤠����� 㧥� �� ����� 24554 (������� telnet).
�᫨ ᮥ������� �� ��⠭����������, �஢����, ������祭 �� ��� ��������
� ����� ������ � �� (������� ping). �᫨ �஢�ન �ᯥ�� - �஢����
����ன�� (�� �⮬ �������� 㢥��祭�� �஢�� ��⮪���஢����: loglevel 6
��� �����).


    ��� �ਬ��� ��� 㧫� 2:5080/68:

    1.1.
    (� �⢥� �� ⥫��� �ࠢ���騥 ᨬ���� �࠭�, ࠧ������ �� ��ப�
    �믮����� ��� 㤮��⢠)

    m:\>telnet f68.n5080.z2.fidonet.net 24554

    -.OPT CRAM-MD5-593e3e5411515fc1cf75816bb74e41d0-SYS Academ
    -ZYZ Alexei Kuklin-LOC Ekaterinburg, Russia-NDL 115200,TCP,BINKP,HUB
    -%TIME Tue, 20 Feb 2001 15:25:20 +0500- VER binkd/0.9.4/Win32 binkp/1.1
    - 2:5080/68@fidonet-OPT ND

    M:\>ping f68.n5080.z2.fidonet.net

    Pinging fido68.imp.uran.ru [195.19.130.68] with 32 bytes of data:

    Reply from 195.19.130.68: bytes=32 time=505ms TTL=122
    Reply from 195.19.130.68: bytes=32 time=555ms TTL=122
    Reply from 195.19.130.68: bytes=32 time=406ms TTL=122
    Reply from 195.19.130.68: bytes=32 time=372ms TTL=122

    ���� ࠡ�⠥�. �஢���� ����ன�� ᢮��� Binkd. ��������, ����� ᫨誮�
�����쪨� ⠩���� (�६�, ����室���� ��� ��⠭���� ᮥ�������, ����� �業���
�� ����প� ��। �⢥⮬ � telnet).

    ��㣮� ��ਠ��: ⥫��� ᮥ�������, � ���� - ��� (ᮮ�頥� "Request timed
out" ��� "�ॢ�襭 ���ࢠ� ��������"):

    M:\>ping f68.n5080.z2.fidonet.net

    Pinging fido68.imp.uran.ru [195.19.130.68] with 32 bytes of data:

    Request timed out.
    Request timed out.
    Request timed out.
    Request timed out.

    �� ����砥�, �� ICMP-������ ����饭� �� ��� ����� ����. �� ࠡ���
binkd ��� �� ������.



    1.2.

    M:\>ping f68.n5080.z2.fidonet.net

    Unknown host f68.n5080.z2.fidonet.net

    ����� �⢥� ����砥�, �� ��� �������� �� ᬮ� �����㦨�� ������ � DNS
��� �⮣� 㧫�. �஢���� ����ன�� DNS � ��⥬�. �᫨ ��� ���� -  㡥�����,
�� DNS-�ࢥ� ࠡ�⠥� � ���� 㤠������� 㧫� 㪠��� �ࠢ��쭮.



    1.3.

    �᫨ ���� ��室��, � telnet-ᮥ������� �� ��⠭���������� - ��������,
�� binkd �� �⮬ 㧫� � ����� ������ �� �⢥砥�. ���஡��
���᭨�� � �ᮯ�� 㧫�, ����饭 �� � ���� binkd. �᫨ ����饭 � ᮥ�������
� ��㣨�� 㧫��� - �� ����砥�, �� ����� � ����� 24554 ������ �� 䠩ࢮ���
��襩 ��. ���஡�� �������� binkd �१ �ப�-�ࢥ� - �. "���
����㦨�� binkd � HTTP-�ப�", "��� ����㦨�� binkd � SOCKS-�ப�"


    1.4.

    M:\>ping -w 5000 f68.n5080.z2.fidonet.net

    Pinging fido68.imp.uran.ru [195.19.130.68] with 32 bytes of data:

    Reply from 195.19.130.68: bytes=32 time=3674ms TTL=122
    Request timed out.
    Reply from 195.19.130.68: bytes=32 time=4232ms TTL=122
    Request timed out.

    ������ �� ���� 24554 ������ ᮥ�������, � �� - ���.

    ���� ࠡ�⠥�, �� ����� �裡 ����� ���� ᨫ쭮 ����㦥� ��� ᫨誮�
��������. �� �⮬ binkd ᮥ������� �� �� ������ ����⪥ (�������
IP-������) ��� �� ᮥ������� ���� (᫨誮� ���� �६� �������� �⢥�
㤠������� 㧫�). ���� ��砩 "������稬", ��᪮��� ������ �������
� ��� � �������� �� �� �� �� � ���ﭨ�. �� ��஬ ��砥 �㦭� 㢥�����
���祭�� �६��� �������� � 䠩�� ���䨣��樨 binkd (���祭�� ��������
� ᥪ㭤��):

    timeout 60
    connect-timeout 300
    call-delay 60

    �᫨ 㢥��祭�� ��� ���祭�� �� �������� - ᬥ��� �������.


    1.5.
    ������ �� ���� 24554 �� ᮥ�������, ��� �� ���� �� �⢥砥�.

    ���� �� �⢥砥�. ������ ��ਠ��� :
    1 - � ����� ������ ��� �������� ���� 㤠����� 㧥� �� ������祭
� ���୥� ��� ����襭� ������⨧��� (���� �� ����� �裡, �⪫�祭��
�����ய�⠭��, �஢������ ࠡ��� � ������ �� �஢����஢ � ��.) -
�।�ਬ�� ��᪮�쪮 ����⮪ �����;
    2 - ��� �������� ��室���� � Intranet � ��室 � Internet �������� ⮫쪮
�१ �ப�-�ࢥ� - �. "��� ����㦨�� binkd � HTTP-�ப�", "��� ����㦨��
binkd � SOCKS-�ப�"


----------------------------------------------------------------------------


    06. ��� ����㦨�� binkd � HTTP-�ப�.

    ��।�� � ��� �࣠����樨 ���짮��⥫� ��室�� � Internet �᪫��⠫쭮
�१ �ப�-�ࢥ�, ��⠭������� �� �����⢥���� ��������, ����饬 ��室
� ����.
�� �⮬ binkd �� ����� ��⠭����� ��אַ� ᮥ������� � 㤠����� 㧫�� � �㦭�
�ᯮ�짮���� ��� �ப�-�ࢥ�.
    �����প� �ப�-�ࢥ஢ �뫠 ����祭� � ���ᨨ 0.9.3.https, 0.9.4 �
����� �������.
    ����� �१ HTTP �ப� �������� ⮫쪮 � ⮬ ��砥, �᫨
� �ப�-�ࢥ� ࠧ�襭� ������� CONNECT host 24554 (ᮥ������� � ���⮬
24554) ���� ������� CONNECT ࠧ�襭� ��� ��� ���� �����祭��. ���筮 ��
������� �ᯮ������ � ��⮪��� "���饭�� HTTP" (��뫪� ���� HTTPS://...),
���� ���뢠����� S-HTTP. ��-�� �⮣� ⠪�� �ப� ��।�� ���뢠��
"HTTPS-�ப�".
    �᫨ binkd ᮮ���, �� �ந��諠 �訡�� ���ਧ�樨, ����� � ����ன��
�ப�-�ࢥ� �㦭�� ������� ����饭� (��� ࠧ�襭� ⮫쪮 ��� ���� 443,
�� ��� ��� ������⢥���).

    �।�������, �� ��������, ������祭�� � Internet, ����� �� ����७���
�� IP-���� 192.168.0.1 � �ப�-�ࢥ� �� ��� "�⢥砥�" �� ����� 3128.
��� ��ப� � 䠩�� ���䨣��樨 binkd, ���室���� ��� ࠡ��� �१ ���
HTTP-�ப�:

    1. �ப�-�ࢥ� ��� ���ਧ�樨 ���짮��⥫� (�� �ॡ���� ������� ���
� ��஫�):

    proxy 192.168.0.1:3128

    2. �ப�-�ࢥ� � ���ਧ�樥� ���짮��⥫� (�ॡ���� ������� ��� �
��஫�, � �ਬ���, ��� user � ��஫� password):

    proxy 192.168.0.1:3128/user/password

    3. �ப�-�ࢥ� ��� Microsoft � ���ਧ�樥� ���짮��⥫� �� ��⮪���
NTLM. (�ॡ���� �室��� � �����.)
� �ਬ���, ��� user � ��஫� password, �������� ���짮��⥫� host � �����
ntdomain:

    proxy 192.168.0.1:3128/user/password/host/ntdomain

    �᫨ ����������� �ப�-�ࢥ� ࠧ�訫 ᮥ������� ⮫쪮 � ���࠭�묨
���⠬� (���筮 �� ���� 443) - ⮣�� binkd �뤠�� �������⨪� "Connection
rejected by proxy". ��� �ਬ��:
      31 Mar 16:48:43 [59987] BEGIN, binkd/0.9.3/SOCKS/HTTPS -p BINKD.CFG
      31 Mar 16:48:43 [59987] clientmgr started
    + 31 Mar 16:48:43 [40423] call to 2:5000/44@fidonet
      31 Mar 16:48:43 [40423] trying 195.209.235.3, port 24554...
      31 Mar 16:48:43 [40423] connected to proxy.osu.ru:24554
      31 Mar 16:48:44 [40423] Connection rejected by proxy (HTTP/1.0 403 Forbidden)
    ? 31 Mar 16:48:44 [40423] unable to connect: {13} Permission denied

    � �⮬ ��砥 ����� ���஡����� �ᯮ�짮���� http-�㭭�����, ���ਬ��
� ������� httport (����� ����� �� http://www.htthost.com/)


----------------------------------------------------------------------------


    07. ��� ����㦨�� binkd � SOCKS-�ப�.

    ��।�� � ��� �࣠����樨 ���짮��⥫� �室�� � Internet �᪫��⠫쭮
�१ �ப�-�ࢥ�, ��⠭������� �� �����⢥���� ��������, ����饬 ��室
� ����. �� �⮬ binkd �� ����� ��⠭����� ��אַ� ᮥ������� � 㤠����� 㧫��
� �㦭� �ᯮ�짮���� ��� �ப�-�ࢥ�.
    �����প� �ப�-�ࢥ஢ �뫠 ����祭� � ����� 0.9.4 � ����� �������.
    Binkd ࠡ�⠥� � SOCKS-�ப� ���ᨩ 4 � 5. ���� �� �ॡ��� ���ਧ�樨
(����� ����� � ��஫�), ���� ��� �ࠢ��� �� �ॡ���.

    �।�������, �� ��������, ������祭�� � Internet, ����� �� ����७���
�� IP-���� 192.168.0.1 � SOCKS-�ࢥ� �� ��� "�⢥砥�" �� ����� 1080.
��� ��ப� � 䠩�� ���䨣��樨 binkd, ���室���� ��� ࠡ��� �१ ���
SOCKS-�ப�:

    1. SOCKS-�ࢥ� ��� ���ਧ�樨 ���짮��⥫� (�� �ॡ���� ������� ���
� ��஫�):

    socks 192.168.0.1:1080

    2. SOCKS-�ࢥ� � ���ਧ�樥� ���짮��⥫� (�ॡ���� ������� ��� �
��஫�, � �ਬ���, ��� user � ��஫� password):

    socks 192.168.0.1:1080/user/password


----------------------------------------------------------------------------


    08. ��� ���⠢��� binkd ������ ����� � ���� (�������)

    �㦭� ᮧ���� ����. binkd �� 㬥�� ���।�⢮� ��樨 -P:

    binkd -P1:2/3 binkd.cfg

���筮 �� �⮬ �㦭�, �⮡� binkd �����訫 ࠡ��� �� ����砭�� ��ᨨ,
��� 祣� �ᯮ������ ���� -p:

    binkd -p -P1:2/3 binkd.cfg

    �᫨ binkd ��᫥ ����砭�� ��ᨨ ����� �� �����蠥���, 㬥����
���祭�� ��ࠬ��� rescan-delay (������ � timeout).

    �᫨ binkd ࠡ�⠥� ����ﭭ� (���ਬ�� ��⠭����� ��� �ࢨ� � Windows)
� �ॡ���� ॣ��୮ ������� �����, �㦭� �ᯮ�짮���� ���譨� �� �⭮襭��
� binkd �ணࠬ�� ��� �ਯ��. ���ਬ��, � DOS, Windows ��� OS/2 �����筮
�믮����� �������:

    cd . >> %outbound%\NNNNMMMM.ilo
    ��� NNNN - ��⭠������ ����� ��,
        MMMM - ��⭠������ ����� 㧫�,
        %outbound% - ���� � ��⡠㭤� �㦭�� ����.

----------------------------------------------------------------------------


    09. �訡�� "start_file_transfer: .: Permission denied"

    �� ᮮ�饭�� ������ ����� binkd �� ����� ������ 䠩� �� ��ࠢ��,
㪠����� � ��誥 (*.?lo). ���॥ �ᥣ� � �⮬ 䠩�� ���� ��ப�, ������
�� ����� ".", �.�. poll ᮧ������ ��������

    echo . >> xxxxyyyy.flo

�� �㦭� �������� �� "cd . >> xxxxyyyy.flo"


----------------------------------------------------------------------------


    10. Binkd/win � ������: ��⮬���᪨� ������ � ��ᮥ�������

    �����: ����ந�� ��⥬� ⠪, �⮡� binkd ���樨஢�� ⥫�䮭�� ������
� �஢������, ����ࠫ �����, ��᫥ 祣� ᮥ������� �㦭� ࠧ�ࢠ��.
    ��襭��:

1 ��ਠ��
    ��⠭����� ��⮬���᪮� ��⠭������� �裡 � ⠩���� � ᢮��⢠�
ᮥ������� (�������� ᮥ������� �� ������⢨� ������ �१ 㪠������
�६�). �� �⮬ 㤮��� �ᯮ�짮���� ���⠭������ �ணࠬ�� �������
(Advanced Dialer � �.�.). binkd �㦭� �㤥� ��ਮ���᪨ ����᪠��
� ���箬 -p (�, ��������, -P���� - �⮡� binkd ᮧ��� ���� �� ����)%

binkd -p -P1:2/3.4  binkd.cfg


2 ��ਠ��
    �ᯮ������ ���� ��������� ��ப� -p � �������� 䠩�, �
���஬ ����᪠���� �ࢨ� 㤠������� ����㯠 (RAS), ��⥬ ����᪠���� binkd,
��᫥ �����襭�� binkd RAS ��⠭����������.

��� Windows NT � Windows 2000 ��� ��ਠ��:
    === binkdpoll1.cmd
    rasdial ����������
    binkd -p binkd.cfg
    rasdial ���������� /disconnect
    ===

    === binkdpoll2.cmd
    net start "remote access service"
    net start "remote access auto service"
    binkd -p binkd.cfg
    net stop "remote access auto service"
    net stop "remote access service"
    ===

3 ��ਠ�� (������訩 ��� win9x)
    �ᯮ������� ��樨 ��������� ��ப� -p � -P����, �ࠢ����� ᮥ��������
�����⢫���� ���⠭���⭮� �ணࠬ��� ������� (� �ਬ���, dialerp).
��� ��ਠ�� �������� ������� (�ᮡ���� � ��砥 ���宩 �裡 � �������
�஢�����) ��������� ⮬�, �� dialerp �� ��⠭������� ᮥ������� �����
����᪠�� 㪠����� �ணࠬ��. ��� �������� 䠩�, ����� �㦭� ��뢠��
�� ��ࠬ��� Execute 䠩�� ���䨣��樨 dialerp:

    ====
    binkd -p -P1:2/3.4  binkd.cfg
    dialerp BREAK *
    ====

    ��⠥��� �����: ��� ����� dialerp. �⢥�: ��� � ����
(Alexander Vedjakin, 2:5020/540) ��� ���� � ��娢�� 䠩�-�� � �� ftp/http.


    �� �� ��ਠ�� � 䠩�� ���䨣��樨 binkd �㦭� ���⠢��� �����
���祭�� � ��ࠬ��� rescan-delay - ⮣�� binkd �㤥�
���������� ����॥:

    === binkd.cfg
    # Outbound rescans period (sec)
    rescan-delay 2
    ===

----------------------------------------------------------------------------


    11. ������� ���䨣 �� ࠡ���饬 binkd. ����� ���������� ���������?

    ��稭�� � ���ᨨ 0.9.1 binkd ���稫�� ��।����� ���������� 䠩��
���䨣��樨. ����饭�� � 䫠��� -C �� �� �⮬ �����蠫�� � ����� 3.
(��᫥ ������ �室�饩 ��ᨨ �ந��������� �஢�ઠ �६��� ����䨪�樨).
��� 䠩� ��� ����᪠ binkd ���ᨩ 0.9.1-0.9.3 � 0.9.4-0.9.6/w32:
    ====
    :aaa
    binkd -C binkd.cfg
    if errorlevel 4 goto end
    if errorlevel 3 goto aaa
    :end
    ====
    � ������ 0.9.4/unix � /os2-emx (⮫쪮 � ���) ᤥ��� ��⮬���᪨�
��१���� binkd, �᫨ �� ����饭 � ���箬 -C. �஬� ⮣�, ��稭�� � ���ᨨ
0.9.4 �஢������� 䠩��, ����祭�� � ���䨣 �� include, � �஢�ઠ
�ந�室�� �� ⮫쪮 �� �室��� ᮥ��������, �� � �१ �����
rescan-delay ᥪ㭤.
    � ���ᨨ 0.9.4/w32 �� ��⠭���� binkd � ����⢥ �ࢨ� Windows NT, �㦭�
��⠭����� ��� � ��ࠬ��஬ -C: ⮣�� binkd �㤥� �����뢠�� ���䨣.
    �� ���ᨨ 0.9.4 ��������� ���䨣� �� �஢��﫨��, �᫨ binkd �� ����饭
� ०��� client-only (���� -c).
    � ������ ��� unix ���䨣 �����뢠���� �� ᨣ���� SIGHUP, ��������
kill -HUP `cat /var/run/binkd.pid`
    � ���ᨨ 1.0 ᤥ���� ��⮬���᪮� �����뢠��� ���䨣� �� ���
���������. �஢�ઠ �஢������ �१ ����� rescan-delay ᥪ㭤.


----------------------------------------------------------------------------


    12. ��� ����㦨�� binkd c T-mail/IP?

    H���� �� ����㦨��. ��⮪��� �ਭ樯���쭮 ࠧ��: binkd ࠡ�⠥�
�� ��⮪��� binkp, t-mail/IP - EMSI & etc.


----------------------------------------------------------------------------


    13. ������� �� � ��த� ��� ���� ��� �������� ��� unix?

    ������� ������⢮ Perl'���� �ਯ⮢, � �ਬ��� ���:

    binkdstat ����� 0.1 beta4 �� 6.01.2002
    ������� ����⨪� ��� binkd
    (c) Dmitry Sergienko, 2:464/910@fidonet, trooper@unity.net 14.08.2000
    http://www.unity.net/~trooper/fido/binkdstat

    ��᪮�쪮 ࠧ��� ������஢ ����� � Nick Soveiko:
    http://www.doe.carleton.ca/~nsoveiko/fido/binkd/statistics_generators/

    ����� ������� �ணࠬ�� BndStat:
    BNDST101.ZIP   34812 14-Aug-01 (AREA:AFTNMISC)
    BndStat 1.01. With sources. BinkD statistics generator. Compiled for all
    platforms. Included win32 binaries. (C) Dmitry Rusov, 2:5090/94

----------------------------------------------------------------------------


    14. Binkd ����� ���������� (~20 ᥪ㭤), ��� �⪠ ᪮��⭠� (���).

    ����୮� "����祭" ��ࠬ��� backresolv (����� � ��� �������� ���
㤠������� ���) � �� ����஥� DNS.
    ����� ���⮥ - �㦭� ���������஢��� backresolv � 䠩�� ���䨣��樨.
    ��᫮����: ����室��� ����ந�� DNS.


----------------------------------------------------------------------------


    15. ��祬� BinkD �� ��� �������� ��।������ ��ࠬ���� �� ����᪥ �� inetd

    � inetd.conf �㦭� ���� ��ࠬ��஬ 㪠�뢠�� ��� �ணࠬ�� (� ��砥
� binkd - �� ��ப�), ���� � ����� ��ࠬ��ࠬ� - ���� ����᪠ (-iqs �
��祥 �� �����), ��᫥���� ��ࠬ��஬ - �������⥢�� ��� ���䨣�:

binkp stream tcp nowait root /usr/fido/binkd binkd -isq /usr/fido/binkd.cfg

�᫨ �� �ᯮ������ ���� -q, � ���䨣� �㦭� ���� �뢮� �� ���᮫�
(���������஢��� printq, percents, conlog).


----------------------------------------------------------------------------


    16. ����� �� ᤥ���� FREQ � binkd.

    ������! Binkd �����ন���� WAZOO FREQ.

    �⮡� ������� 䠩�� � 㤠������ ��⥬� �㦭� ᮧ���� 䠩� ����
nnnnmmmm.REQ � �������� ��� � outbound �冷� � 䠩���� *.?ut � *.?lo,
�⭮��騬�� � �㦭��� �����. �� 䠩�� *.REQ �� ���樨���� �஧����� � binkd,
��� ᮢ��襭�� FREQ �㦭� ᮧ���� ����.
    ��� �ਥ�� � ��ࠡ�⪨ FREQ � Binkd ����ࠨ������ �맮� ���譥��
�४-������, �����ন���饣� SRIF (� �ਬ���, Allfix). ��⠩ 䠩�
"!SRIF.TXT" � �������਩ � "exec" � ���䨣-䠩��.
    ��� �ਬ��� ��ப� � ���䨣� ��� DOS-based OS � ��� *nix (⠬ ��室����
㪠�뢠�� ���� � ॣ���묨 ��ࠦ���ﬨ, �⮡� binkd �ᯮ���� 䠩��
������ᨬ� �� ॣ���� �㪢: � *.REQ, � *.req):

    exec "\\ftn\\allfix\\allfix.exe RP -SRIF *S" *.req

    exec "/ftn/bin/tmafreq *S" *.[rR][eE][qQ]


----------------------------------------------------------------------------


    17. ��� �������� binkd � 䨤�-�⠭��, ࠡ������ �� ������.

    �㦭� ����ந�� ������� ������ � ���� �� ०�� BSO (binkley-style
outbound), ⠪ �⮡� � ��� (� � binkd ⮦�) ᮢ������ inbound- �
outbound-��⠫���. �᫨ �� ������ "㬥��" ⮫쪮 AMA (arcmail-attach)
- �ਤ���� ᬥ���� ������.


----------------------------------------------------------------------------


    18. ����� �� �ਥ�� 䠩�� �� ᮧ������, �ணࠬ�� �� ����᪠����

    �����猪 ���ࠢ��쭮 㪠���� ��᪠ � ���䨣�. �㦭� ⠪ (���ᨨ ���
windows � os/2 - ���� ��� ��ப�, � ��-������ ��⠫��):

    flag m:\\ftn\\flg\\pntseg.flg m:\\\\ftn\\\\inbound\\\\sec\\\\pntstr*.*
    flag m:\\ftn\\flg\\toss.flg *.su? *.mo? *.tu? *.we? *.th? *.fr? *.sa? *.pkt

    exec "/usr/local/bin/ftrack -c /fido/conf/ftrack" *.[Pp][Kk][Tt]
    flag "/ftn/flg/echo-in" /ftn/inboundsec/*.[Ss][Uu][0-9A-Za-z]
    flag "/ftn/flg/echo-in" /ftn/inboundsec/*.[Mm][Oo][0-9A-Za-z]
    flag "/ftn/flg/echo-in" /ftn/inboundsec/*.[Tt][Uu][0-9A-Za-z]
    flag "/ftn/flg/echo-in" /ftn/inboundsec/*.[Ww][Ee][0-9A-Za-z]
    flag "/ftn/flg/echo-in" /ftn/inboundsec/*.[Tt][Hh][0-9A-Za-z]
    flag "/ftn/flg/echo-in" /ftn/inboundsec/*.[Ff][Rr][0-9A-Za-z]
    flag "/ftn/flg/echo-in" /ftn/inboundsec/*.[Ss][Aa][0-9A-Za-z]
    flag "/ftn/flg/fech-in" /ftn/inboundsec/*.[Tt][Ii][Cc]

    ���� 㪠�뢠�� ������ ��� 䠩��, ����� ������ �ਭ�����, � ������
᫥蠬� ��� ��᪠ ������ ��稭����� � ᨬ���� "������窠". ��� 䫠�� �㦭�
�ᯮ�짮���� ������ ���.
    ������ ��� - ��⮬� �� ��� 䠩�� ��� ��� ����砥� ᮡ�⨥ �ਥ�� 䠩��
�� � ����㭤, � � ⥪�騩 ��⠫��. �᫨ ��᪠ ��稭����� � "*", � � ��
(� ��᪮��� 䠩�� �ਭ������� � ���� �� ����㭤��, ࠡ�⠥� ��� ��� ��ᨩ
- � ��஫���, � ����஫���).
    � ��� �㦭� ���뢠��, �� ����訥-�����쪨� �㪢� � ������ 䠩���
ࠧ������� (�ᯮ���� ॣ���� ��ࠦ���� � ��᪠�).


----------------------------------------------------------------------------


    19. �� ࠡ�⠥� skipmask.

    ��� skipmask ��� 䠩�� �ࠢ�������� ��� ��� � ॣ���஧���ᨬ�.


----------------------------------------------------------------------------


    20. Binkd ��� DOS.

    Victor Pashkevich (2:451/30) ����஢�� binkd 0.9.2 ��� ����樮����
��⥬� MS DOS. C ���� 2003 ���� ���� ��ਠ�� �⮣� ���� �����ন������
��樠�쭮 (� ����祭 � ��ॢ� ��室����� �� CVS).
    ��室���� binkd 0.9.2/dos:
    http://www.doe.carleton.ca/~nsoveiko/fido/binkd/0.9.2/
    ��室���� � ����୨�� binkd 0.9.2/dos � binkd 0.9.5a/dos (�� ᠬ� ᢥ���):
    http://www.n451.z2.fidonet.net/binkd/
    ������ ��室���� - �� CVS.

�ᮡ������� ���ᨨ ��� DOS � ⮬, �� � ��⥬� ��� �����প� �� � ������
��������� ॠ������ �ᯮ���� ���� �� �⥪�� IP, ࠧࠡ�⠭��� ������ᨬ묨
�ந�����⥫ﬨ. ��������� �� Victor Pashkevich ࠡ�⠥� ⮫쪮 � �ࠩ��ࠬ�
IBM TCP/IP ���ᨨ 2.1. ���� �� ����� � Internet:
    http://www.ibm.com
    http://binkd.grumbler.org/tcpdos21.rar
    ftp://ftp.grumbler.org/pub/tcpdos/tcpdos21.rar

    �஬� ����饣���, ����� �����騩 ����� ����஢��� binkd ��� ���������
� ���� ����� �ࠩ��஢ IP ��� DOS :-). ��室���� - � Internet'� � 䠩�-��
(�. "��� ����� ᢥ��� ����� BinkD.")


----------------------------------------------------------------------------


    21. Binkd ��� Windows 3.x.

    Sergey Zharsky (zharik@usa.net) ����஢�� binkd 0.9.2 � binkd 0.9.5 ���
Windows 3.x. ����⠥� c IP �⥪��� Trumpet Winsock ver. 3.0 revision D �
Novell TCP/IP Client for Win 3.11 (�. �⢥� �� ����� "Binkd ��� DOS."
��ࠣ�� "�ᮡ�������...").

    ��室���� � ����୨��:
    http://zharik.host.sk/index.php?pages=d&page=d

    ���쪮 0.9.2:
    http://www.doe.carleton.ca/~nsoveiko/fido/binkd/0.9.2/


----------------------------------------------------------------------------


    22. ����� FTN-������ � binkd � ����, �� ������ਢ��騩 5D outbound.

    ������: ��� ������ (� ࠧ�묨 ����ࠬ� ���, ��� �� ���ਭ樯���쭮),
���� �� ���� ����� ��ࠢ�����, �� ��ன - ���. ����� ����� �����
����������, �᫨ ��������� �����প� 5D outbound � ����, �४�� � ��㣨�
䨤���� �ணࠬ�, �ᯮ��㥬�� �� FTN-��⥬�.

    ����筠� ���䨣���� binkd ��� ���� ������� � 5D outbound:

    domain fidonet c:\\ftn\\outbound\\fido 2
    domain omeganet c:\\ftn\\outbound\\omega 11
    address 2:5070/222@fidonet 11:58/6@omeganet

    � domain �ய��뢠���� �� default ���� ��, � ����, ������ �� ����
��������� � ����� outbound'� (�.�. ��� ����, 㪠������ � ��ப�
domain, ���७�� ��⡠㭤� �� ��ࠡ��뢠����).

    �᫨ �� ⢮� ���� ᮧ����� ��� omeganet ������ � ��⠫��� omega, � ����
�뫮 �� ����� 11; � ࠧ �� ᮧ���� � omega.00b (��� ��� ⠬?), � ����� ����
2, ��� ⠪:

    domain fidonet c:\\ftn\\outbound\\fido 2
    domain omeganet c:\\ftn\\outbound\\omega 2
    address 2:5070/222@fidonet 11:58/6@omeganet


----------------------------------------------------------------------------


    23. ��� ࠡ�⠥� "domain ... alias-for ..." � ���䨣�

    ������ ���뢠���� �� ������� ���� 㤠������ ��஭�.
    �ਬ��:

domain fidonet.net alias-for fidonet

�� �஢�થ ������: fidonet.net � ���� 㤠������ ��஭� ���������
�� fidonet � ���� 1:2/3.4@fidonet.net �㤥� ���ਭ������� ��� 1:2/3.4@fidonet


----------------------------------------------------------------------------


    24. �� ����砥� �������⨪� "send: TCP/IP error (-10000)" � ��� �� �����?

    ��� ��� �訡��, �᭮���� ��ࠢ���� ��। �⢥⢫����� binkd 0.9.5-stable:

    1. ���� � ⮬, �� � ��� ���� � ���� binkd �� �뫮 ᤥ���� ��࠭����
���祭�� ���� �訡��, �� �� �� ��﫮�� ����� �஬� ��� � win-���ᨨ.
�訡�� ��﫠�� ��⮬�, �� � run-time ������⥪� MS Visual C (� �⫨稥 ��
����設�⢠) ����蠥��� �⠭����. �訡�� � ⮬, �� errno � h_errno � MSVC RTL
����� ����ᠬ�, ���뢠�騬�� � ��⥬�� �맮��, � �� ��� �室���� �
�맮� GetLastError(). � ���祭��, �����頥��� �⮩ ��⥬��� �㭪樥�,
���뢠���� � ��� �� �� �ᯥ譮� ��⥬��� �맮��. ����� ��ࠧ��, errno
���⠢����� � ���� ���ਬ�� �� �ᯥ譮� ����⨨ 䠩��. (�� �⠭����� errno
�� ������ �������� �᫨ �� �뫮 �訡��.) � binkd ���ﭨ� �⮣� ���� ���࠭���:
    2003/04/28 07:30:16  gul
    * Bugfix: Log() changes TCPERRNO

    2.
    �訡�� � Winsock - select() �ᥣ�� �����頥� �ᯥ�� ��� ��� non-blocked
socket. ���ﭨ� �� (� ��㣨� �����㦥���� � winsock �訡��) ���筮 ���࠭���:
    2003/06/06 16:27:44  gul
    * Workaround winsock bug - giveup CPU when sending file
    2003/08/11 08:41:55  gul
    * workaround winsock bug (patch by Alexander Reznikov)
    2003/08/24 00:29:31  hbrew
    * win9x-select-workaround fix, thanks to Pavel Gulchouck)

    E��� ��� ��䥪� �� ��᮪�� �஢��� ��⮪���஢���� (� ��� ������ ���
ᮮ�饭�� 'data transfer would block', �⫠��筠� ���ଠ�� �� १���⠬
ࠡ��� select()). H� �� ࠡ��� � ���筮� ०��� �� �� �����. ���࠭��� ��
�����, �� ����� �� �⠫ �᫮����� ���.


----------------------------------------------------------------------------


    25. Argus (Radius) � binkd: �訡�� Argus "Aborting due to carrier loss"

    ����� ����� binkd � Radius (��� Argus - �� ������⢥���) ���뢠����
� ������⭮� �������⨪�� "Aborting due to carrier loss" �� ����祭���
� Radius ��஢���� ��䨪�. �� �⮬ �� ��஭� binkd ᮥ������� ���뢠����
�� ���樠⨢� 㤠������ ��஭� ("Connection reset by peer").

    ��� � ��஭� Radius:
    30-Aug-2003 22:24:31 Encrypted (2:463/375) session
    30-Aug-2003 22:24:32 Aborting due to carrier loss
    30-Aug-2003 22:24:32 Session aborted
    30-Aug-2003 22:24:32 End

    ��稭� � ⮬, �� ����� Argus �ਤ㬠�� ᢮� ᯮᮡ ��஢���� ��䨪�,
� � binkd �� ���७�� �� ॠ��������. �� �� ��祣�, �� ⮭����� � ⮬, ��
Argus (� �᫥� �� ��� Radius) �� ᮡ��� ᮢ���⨬���� � ��⮪���� binkp:
��஢���� ����砥��� ����᫮���, ��� �஢�ப ��� �����প� 㤠������
��஭��. ����� �����饥 ����襭�� ᯥ�䨪�樨 �������⨬� - �� ��. ��室:
�⪫���� ��஢���� � Argus ��� ������� �����, � ���ண� �ᯮ������ binkd.

    �ࠢ��쭮� ��������� ������ ������ �뫮 ���� ᫥���騬:
    - �᫨ ��஢���� ����易⥫쭮 - �த������ ���ਯ⮢����� ����;
    - �᫨ � ����ன�� ������ ��⠭������ ��易⥫쭮� ��஢���� - ᮮ����
㤠������ ��஭� �� ���਩��� �����襭��, ���ਬ�� ⠪:
    M_ERR "DES encription required"


----------------------------------------------------------------------------


    26. � �������� ��⠫��� - ᨬ��� ��������� � binkd �� ����� ��⠫��.

    �� ����ன�� binkd � ࠡ���饩 �⠭樨 � bink/+: � ����� ����砥���
ᨬ��� "#", �� ���� �������ਥ� ��� ���䨣� binkd �, �⮡� binkd ���ਭ�
�ࠢ���� ����, ��� ᨬ��� ���� �������� � ���䨣� ����� ��襬:

    domain fidonet c:\\fido\\\#out
    inbound-nonsecure c:\\fido\\unsec\#in
    inbound c:\\fido\\\#in

    � ���ᨨ 1.0 ��稭�� � ᭠��� 1.0a-317 ��� �᪥����� ����� ��
�ᯮ�짮����, ��᪮��� ��砫�� ��������� � �।��� ��ப� �⠫� �������
��᫥����⥫쭮��� �஡��� � ��⪨ (" #") ��� ⠡��樨 � ��⪨. �ਬ���
����.

    ��� ���������:
    temp-inbound c:\\fido\\temp#this_is_not_a_comment_but_a_directory_name

    �������ਨ:
    inbound c:\\fido\\in # �� �������਩, ��⮬� �� ���� �஡�� ��। "#"
    # ��� �� ��ப� - �������਩


----------------------------------------------------------------------------


    27. ���� �� ����������� ����᪠ �ਫ������ � binkd �� ᮡ���?

    �᫨ ��� � �६����� ᮡ���� - ���, � �� �㤥�. ��� �ࠢ����� ᮡ��ﬨ
�������� ࠧ����ࠧ�� �����஢騪�, � ᮢ६����� ����樮���� ��⥬�� ���
����祭� � ���⠢��.

    �᫨ �� ��� � ᮡ�⨨ �ਥ�� �����ண� 䠩�� - ����� ॠ�������� (��稭��
� ���ᨨ 0.9), �. � ���䨣� ⮪��� exec � flag.


----------------------------------------------------------------------------


    28. � 祬 ࠧ��稥 ����� binkd/w32 � binkd/w9x?

    Binkd/w32 - �ࠤ�樮��� ��ਠ�� binkd, ���᮫쭮� win32 �ਫ������.
Binkd/w9x - GUI-�ਫ������ win32, ᮧ���饥 �६���� ���᮫�� ���� �� ���
����室�����. �᫨ �������� binkd/w32 � �������饬 ���᮫쭮� ����
(���ਬ��, � ���� command.com ��� cmd.exe), �� �㤥� ࠡ���� � ⮬ �� ����.
� �⫨稥 �� ���� binkd/w9x �� ����᪥ �ࠧ� �� �⤠�� �ࠢ����� �맢��襩
��� �����.
    ����室������ ࠧࠡ�⪨ binkd/w9x �뫠 �맢��� ⥬, �� � Windows 95/98/Me
� � Windows NT/2000/XP/2003 ���� ��᪮�쪮 ��쥧��� ࠧ��稩.
    ��-�����, ���᮫� ॠ�������� ��-ࠧ����. �᭮���� �⫨稥 - ���᮫�
� Windows 9x �� ���ਭ����� ᨣ���� shutdown � window close, ���⮬�
ࠡ���騩 binkd/w32 �� ����� ���४⭮ ���������� �� �����⨨ ���� �
�����襭�� (��१���㧪�) ��⥬�.
    ��-�����, � ������ Windows ࠧ��� ��⮪ ᨫ쭮 ࠧ������� �ਭ樯�
ࠡ��� �ࢨᮢ.
    � �⮣�, binkd 1.0a/w32 ����� ࠡ���� ⮫쪮 �ࢨᮬ Windows NT �
��᫥�����, � binkd 1.0a/w9x - ⮫쪮 �ࢨᮬ Windows 95/98/Me. � ���饬
���������� ᤥ���� �����প� �ࢨᮢ NT � binkd/w9x. ���४⭠� �����প�
ࠡ��� binkd/w32 �ࢨᮬ ��� Windows 9x ���������� ��-�� ���ᠭ���
�ᮡ�����⥩ ॠ����樨 ���᮫� � ��� ��⥬��.


----------------------------------------------------------------------------


    29. ���쭮 �� 墠⠥� �� � binkd! � �६� ᨭ�஭���஢��� �����.

    �⮡� �������� - �ᯮ��� talk, icq ��� irc (�� ��� Gadu-Gadu).
�᫨ ����, ��� �������� binkd, � �� ⮬� �� ������ ����� p������ � ��
����᫥����, � ������ ��㣮�. ������ �� 㬮���p�祭��, �᫨ ᨫ쭮 ����.
    � ��� ᨭ�஭���樨 �६��� �� IP ���� ᯥ樠��� �⨫���, ���ਬ��,
ntpdate. ��祬 ntp* ����� �६� � �ࢥ஢ �筮�� �६���, � �⫨稥 ��
�����஢.


----------------------------------------------------------------------------


    A1. �����㦨� ��� � binkd!

    ���p���� �ᢥ���� ��p�� (��������, �訡�� 㦥 ��ࠢ����). �᫨
�� ������� - ���� "������" p��p����稪��:
    binkd-bugs@happy.kiev.ua
    Pavel Gulchouck 2:463/68
    p���뫪� binkd-dev@happy.kiev.ua
    � ��ᬥ �㦭� ���஡�� ������ ����� ������������� �訡��, ��
�⮬ ��易⥫쭮 㪠���� ����p ��pᨨ � �ਫ����� ��१�� �� ���p������
���� (loglevel ����� 5).


----------------------------------------------------------------------------


    A2. ��� �易���� � ࠧࠡ��稪���.

    ���� ����� ���ᨩ binkd - ����਩ ����� - �뭥 ��襫 �� �஥��.
� 2000-2003 ����� �஥�� ���न����� ����� ����� 2:463/68 (Pavel Gulchouck
<gul@gul.kiev.ua>), �� �� � ���� ������� ���� ����.
    ��� ��饭�� ࠧࠡ��稪�� � ���஢ ᮧ���� ���뫪�:
binkd-dev@happy.kiev.ua. �⮡� �� ��� ����������, ������ ���쬮:

	To: majordomo@happy.kiev.ua
	Subject:

	subscribe binkd-dev


----------------------------------------------------------------------------


    A3. ���� �ࠧ� 㧭����� �� ���������� � binkd!

    �������� �� ᯨ᮪ ���뫪� binkd-diffs@happy.kiev.ua: �� ����
��ࠢ������ ��������� � ��室����� (������ ����� � �஢���� ���� �� �訡��).
�������� � �।��饬 �⢥�.

    ��� ���㦤���� binkd, ��饭�� ���짮��⥫�� � ࠧࠡ��稪�� ��������
��� �宪���७樨 FIDOnet: ���᪮��筠� RU.BINKD � �������筠�
(����㭠த���) BINKD. ��� �� ��堡�� :).


----------------------------------------------------------------------------


    A4. � ����� binkd �㤥� ������ ... ?

    ��������, �㤥� �����-�����. � ����� � �� �㤥�. ����� ���������, ����
�������� ����������� �㤥� ॠ�������� ��� ���࠭��� "������⮪"
ᠬ����⥫쭮 - ���� ��室���� ������. �� �⮬ ����� ��� ��᫠��
ࠧࠡ��稪�� ����: ��������, �� �㤥� ����祭 � �᭮���� ���� � �����猪
�㤥� ࠧ��饭 �� ���ᠩ� ��� FTP.


    === �����.
