# 
# Copyright (C) Daan Pape, DPTechnics
#
# This work is licensed under the Creative Commons
# Attribution-NonCommercial 4.0 International 
# License. To view a copy of this license, 
# visit http://creativecommons.org/licenses/by-nc/4.0/.

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=dpt-web-ide-server
PKG_RELEASE:=1
PKG_BUILD_DIR := $(KERNEL_BUILD_DIR)/$(PKG_NAME)
PKG_MAINTAINER := Daan Pape <daan@dptechnics.com>
PKG_BUILD_DEPENDS = libwebsockets

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/dpt-web-ide-server
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=Web Servers/Proxies
  TITLE:=DPT-Web IDE Server
  DEPENDS:=+libwebsockets
endef

define Package/dpt-web-ide-server/description
  The DPT-Websocket server is based on libwebsockets and provides functions such as chat and interactive usage of the DPT-WebIDE
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

define Package/dpt-web-ide-server/conffiles
	/etc/config/dpt-web-ide-server
endef

TARGET_LDFLAGS += -lcrypt
CMAKE_OPTIONS = -DTLS_SUPPORT=on

define Package/dpt-web-ide-server/install
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/dpt-web-ide-server.init $(1)/etc/init.d/dpt-web-ide-server
	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_CONF) ./files/dpt-web-ide-server.config $(1)/etc/config/dpt-web-ide-server
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/dpt-web-ide-server $(1)/usr/sbin/dpt-web-ide-server
endef

$(eval $(call BuildPackage,dpt-web-ide-server))
