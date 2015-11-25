Source-Makefile: feeds/telephony/net/asterisk-13.x/Makefile
Package: asterisk13
Menu: 1
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread +jansson +libncurses +libopenssl +libpopt +libsqlite3 +libstdcpp +libuuid +libxml2 +libxslt +zlib
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Complete open source PBX, v13.6.0
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description:  Asterisk is a complete PBX in software. It provides all of the features
 you would expect from a PBX and more. Asterisk does voice over IP in three
 protocols, and can interoperate with almost all standards-based telephony
 equipment using relatively inexpensive hardware.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-sounds
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Sounds support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides the sound-files for Asterisk-13.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-app-alarmreceiver
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Alarm receiver support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'Central Station Alarm receiver for Ademco Contact ID' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-app-authenticate
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Authenticate commands support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'Execute arbitrary authenticate commands' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-app-chanisavail
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Channel availability check support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'support for checking if a channel is available' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-app-chanspy
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Channel listen in support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'support for listening in on any channel' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-app-confbridge
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13 +PACKAGE_asterisk13-app-confbridge:asterisk13-bridge-builtin-features +PACKAGE_asterisk13-app-confbridge:asterisk13-bridge-simple +PACKAGE_asterisk13-app-confbridge:asterisk13-bridge-softmix
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: ConfBridge support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'Software bridge for multi-party audio conferencing' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-app-dahdiras
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13 +PACKAGE_asterisk13-app-dahdiras:asterisk13-chan-dahdi
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Execute an ISDN RAS support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'support for executing an ISDN RAS using DAHDI' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-app-directed_pickup
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Directed call pickup support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'support for directed call pickup' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-app-disa
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Direct Inward System Access support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'Direct Inward System Access' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-app-exec
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Exec application support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'support for application execution' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-app-minivm
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Minimal voicemail system support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'a voicemail system in small building blocks working together based on the Comedian Mail voicemail' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-app-mixmonitor
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Record a call and mix the audio support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'record a call and mix the audio during the recording' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-app-originate
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Originate a call support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'originating an outbound call and connecting it to a specified extension or application' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-app-playtones
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Playtones application support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'play a tone list' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-app-read
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Variable read support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'a trivial application to read a variable' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-app-readexten
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Extension to variable support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'a trivial application to read an extension into a variable' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-app-record
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Record sound file support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'to record a sound file' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-app-sayunixtime
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Say Unix time support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'an application to say Unix time' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-app-senddtmf
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Send DTMF digits support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'Sends arbitrary DTMF digits' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-app-sms
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13 +PACKAGE_asterisk13-app-sms:libpopt +PACKAGE_asterisk13-app-sms:libstdcpp
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: SMS support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'SMS support (ETSI ES 201 912 protocol 1)' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-app-stack
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13 +PACKAGE_asterisk13-app-stack:asterisk13-res-agi
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Stack applications support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'Stack applications Gosub Return etc.' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-app-system
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: System exec support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'support for executing system commands' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-app-talkdetect
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: File playback with audio detect support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'for file playback with audio detect' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-app-verbose
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Verbose logging support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'Verbose logging application' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-app-waituntil
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Sleep support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'support sleeping until the given epoch' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-app-while
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: While loop support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'a while loop implementation' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-bridge-builtin-features
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Bridging features support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'built in bridging features' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-bridge-builtin-interval-features
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Built in bridging interval features support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'built in bridging interval features' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-bridge-holding
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Bridging for storing channels in a bridge support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'bridging technology for storing channels in a bridge' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-bridge-native-rtp
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Native RTP bridging technology module support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'native RTP bridging technology module' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-bridge-simple
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Simple two channel bridging module support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'simple two channel bridging module' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-bridge-softmix
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Multi-party software based channel mixing support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'multi-party software based channel mixing' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-cdr
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Provides CDR support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'Call Detail Record' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-cdr-csv
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Provides CDR CSV support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'Call Detail Record with CSV support' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-cdr-sqlite3
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13 libsqlite3
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Provides CDR SQLITE3 support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'Call Detail Record with SQLITE3 support' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-chan-dahdi
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13 +PACKAGE_asterisk13-chan-dahdi:dahdi-tools-libtonezone +PACKAGE_asterisk13-chan-dahdi:kmod-dahdi +PACKAGE_asterisk13-chan-dahdi:libpri
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: DAHDI channel support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'DAHDI channel support' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-chan-iax2
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13 +PACKAGE_asterisk13-chan-iax2:asterisk13-res-timing-timerfd
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: IAX2 channel support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'IAX support' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-chan-sip
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13 +PACKAGE_asterisk13-chan-sip:asterisk13-app-confbridge
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: SIP channel support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'the channel chan_sip' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-chan-skinny
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Skinny channel support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'the channel chan_skinny' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-chan-unistim
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Unistim channel support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'channel driver for the UNISTIM (Unified Networks IP Stimulus) protocol' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-codec-a-mu
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Alaw to ulaw translation support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'translation between alaw and ulaw codecs' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-codec-adpcm
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: ADPCM text support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'ADPCM text ' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-codec-alaw
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Signed linear to alaw translation support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'translation between signed linear and alaw codecs' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-codec-dahdi
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13 +PACKAGE_asterisk13-codec-dahdi:asterisk13-chan-dahdi
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: DAHDI codec support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'DAHDI native transcoding support' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-codec-g722
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: G.722 support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'a high bit rate 48/56/64Kbps ITU standard codec' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-codec-g726
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Signed linear to G.726 translation support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'translation between signed linear and ITU G.726-32kbps codecs' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-codec-gsm
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: linear to GSM translation support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'translate between signed linear and GSM' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-codec-ilbc
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: linear to ILBC translation support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'translate between signed linear and ILBC' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-codec-lpc10
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Linear to LPC10 translation support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'translate between signed linear and LPC10' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-codec-resample
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: resample sLinear audio support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'resample sLinear audio' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-codec-ulaw
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Signed linear to ulaw translation support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'translation between signed linear and ulaw codecs' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-curl
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13 +PACKAGE_asterisk13-curl:libcurl
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: CURL support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'CURL support' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-format-g726
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: G.726 support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'support for headerless G.726 16/24/32/40kbps data format' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-format-g729
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: G.729 support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'support for raw headerless G729 data' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-format-gsm
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: GSM format support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'support for GSM format' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-format-h263
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: H263 format support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'support for H264 format' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-format-h264
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: H264 format support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'support for H264 format' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-format-ilbc
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: ILBC format support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'support for ILBC format' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-format-pcm
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: PCM format support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'support for PCM format' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-format-sln
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Raw slinear format support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'support for raw slinear format' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-format-vox
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: VOX format support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'support for ADPCM vox format' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-format-wav
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: WAV format (8000hz Signed Linear) support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'support for proprietary Microsoft WAV format (8000hz Signed Linear)' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-format-wav-gsm
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: WAV format (Proprietary GSM) support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'support for proprietary Microsoft WAV format (Proprietary GSM)' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-func-base64
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: base64 support support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'support of base64 function' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-func-blacklist
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Blacklist on callerid support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'looking up the callerid number and see if it is blacklisted' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-func-channel
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Channel info support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'Channel info dialplan function' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-func-cut
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: CUT function support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'CUT function' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-func-db
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Database interaction support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'functions for interaction with the database' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-func-devstate
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Blinky lights control support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'functions for manually controlled blinky lights' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-func-enum
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: ENUM support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'ENUM' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-func-env
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Environment functions support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'Environment dialplan functions' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-func-extstate
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Hinted extension state support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'retrieving the state of a hinted extension for dialplan control' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-func-global
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Global variable support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'global variable dialplan functions' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-func-groupcount
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Group count support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'for counting number of channels in the specified group' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-func-math
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Math functions support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'Math functions' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-func-module
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Simple module check function support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'Simple module check function' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-func-realtime
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: realtime support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'the realtime dialplan function' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-func-shell
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Shell support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'support for shell execution' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-func-uri
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: URI encoding and decoding support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'Encodes and decodes URI-safe strings' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-func-vmcount
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: vmcount dialplan support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'a vmcount dialplan function' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-odbc
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13 +PACKAGE_asterisk13-odbc:libpthread +PACKAGE_asterisk13-odbc:libc +PACKAGE_asterisk13-odbc:unixodbc
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: ODBC support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'ODBC support' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-pbx-ael
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Asterisk Extension Logic support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'support for symbolic Asterisk Extension Logic' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-pbx-dundi
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Dundi support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'provides Dundi Lookup service for Asterisk' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-pbx-realtime
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Realtime Switch support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'realtime switch support' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-pbx-spool
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Call Spool support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'outgoing call spool support' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-pgsql
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13 +PACKAGE_asterisk13-pgsql:libpq
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: PostgreSQL support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'PostgreSQL support' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-pjsip
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13 +PACKAGE_asterisk13-pjsip:asterisk13-res-sorcery +PACKAGE_asterisk13-pjsip:libpjsip +PACKAGE_asterisk13-pjsip:libpjmedia +PACKAGE_asterisk13-pjsip:libpjnath +PACKAGE_asterisk13-pjsip:libpjsip-simple +PACKAGE_asterisk13-pjsip:libpjsip-ua +PACKAGE_asterisk13-pjsip:libpjsua +PACKAGE_asterisk13-pjsip:libpjsua2
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: pjsip channel support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'the channel pjsip' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-res-adsi
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Provide ADSI support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'Analog Display Services Interface capability' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-res-ael-share
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Shareable AEL code support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'support for shareable AEL code mainly between internal and external modules' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-res-agi
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Asterisk Gateway Interface support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'Support for the Asterisk Gateway Interface extension' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-res-calendar
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Calendaring API support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'Calendaring support (ICal and Google Calendar)' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-res-clioriginate
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Calls via CLI support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'Originate calls via the CLI' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-res-fax
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13 +PACKAGE_asterisk13-res-fax:asterisk13-res-timing-pthread
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: FAX modules support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'Generic FAX resource for FAX technology resource modules' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-res-http-websocket
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: HTTP websocket support support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for '' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-res-monitor
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Provide Monitor support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'Cryptographic Signature capability' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-res-musiconhold
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: MOH support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'Music On Hold support' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-res-parking
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Phone Parking support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'Phone Parking application' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-res-phoneprov
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Phone Provisioning support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'Phone provisioning application for the asterisk internal http server' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-res-realtime
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Realtime support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'Realtime Interface' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-res-rtp-asterisk
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13 +PACKAGE_asterisk13-res-rtp-asterisk:libpjsip +PACKAGE_asterisk13-res-rtp-asterisk:libpjmedia +PACKAGE_asterisk13-res-rtp-asterisk:libpjnath +PACKAGE_asterisk13-res-rtp-asterisk:libpjsip-simple +PACKAGE_asterisk13-res-rtp-asterisk:libpjsip-ua +PACKAGE_asterisk13-res-rtp-asterisk:libpjsua +PACKAGE_asterisk13-res-rtp-asterisk:libpjsua2
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: RTP stack support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for '' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-res-rtp-multicast
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: RTP multicast engine support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for '' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-res-smdi
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Provide SMDI support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'Simple Message Desk Interface capability' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-res-sorcery
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Sorcery data layer support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for '' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-res-srtp
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13 +PACKAGE_asterisk13-res-srtp:libsrtp
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: SRTP Support support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'Secure RTP connection' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-res-timing-dahdi
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13 +PACKAGE_asterisk13-res-timing-dahdi:asterisk13-chan-dahdi
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: DAHDI Timing Interface support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for '' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-res-timing-pthread
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: pthread Timing Interface support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for '' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-res-timing-timerfd
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Timerfd Timing Interface support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for '' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@

Package: asterisk13-voicemail
Submenu: Telephony
Version: 13.6.0-1
Depends: +libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread asterisk13 +PACKAGE_asterisk13-voicemail:asterisk13-res-adsi +PACKAGE_asterisk13-voicemail:asterisk13-res-smdi
Conflicts: 
Menu-Depends: 
Provides: 
Build-Depends: libxml2/host
Section: net
Category: Network
Title: Voicemail support
Maintainer: Jiri Slachta <slachta@cesnet.cz>
Source: asterisk-13.6.0.tar.gz
License: GPL-2.0
LicenseFiles: COPYING LICENSE
Type: ipkg
Description: This package provides support for 'voicemail related modules' in Asterisk.
http://www.asterisk.org/
Jiri Slachta <slachta@cesnet.cz>
@@


