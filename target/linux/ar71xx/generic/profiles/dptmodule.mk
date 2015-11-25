#
# Copyright (C) 2009 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

define Profile/DPT-Module
	NAME:=DPT-Module
	PACKAGES:=kmod-usb-core kmod-usb2  kmod-ledtrig-usbdev
endef


define Profile/DPT-Module/Description
	Package set optimized for the DPTechnics Module.
endef
$(eval $(call Profile,DPT-Module))
