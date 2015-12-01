# 
# Copyright (C) Daan Pape, DPTechnics
#
# This work is licensed under the Creative Commons
# Attribution-NonCommercial 4.0 International 
# License. To view a copy of this license, 
# visit http://creativecommons.org/licenses/by-nc/4.0/.

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=dpt-watchdog
PKG_RELEASE:=1

PKG_BUILD_DIR := $(KERNEL_BUILD_DIR)/$(PKG_NAME)
PKG_MAINTAINER := Daan Pape <daan@dptechnics.com>

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/dpt-watchdog
  SECTION:=utils
  CATEGORY:=Utilities
  SUBMENU:=DPTechnics
  TITLE:=DPTechnics system watchdog
endef

define Package/dpt-watchdog/description
The DPT-Watchdog checks if critical DPTechnics programs are running. This means the 
state of the breakout-server and dpt-connector are checked. If one of these services
is not running the DPT-Board will reset in an attempt to recover. 
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

define Package/dpt-watchdog/install
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/dpt-watchdog.init $(1)/etc/init.d/dpt-watchdog
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/dpt-watchdog $(1)/usr/sbin/dpt-watchdog
endef

$(eval $(call BuildPackage,dpt-watchdog))
