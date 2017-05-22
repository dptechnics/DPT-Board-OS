#
# Copyright (C) 2014-2015, Daan Pape <daan@dptechnics.com>
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without 
# modification, are permitted provided that the following conditions are met:
# 
#     1. Redistributions of source code must retain the above copyright 
#        notice, this list of conditions and the following disclaimer.
#
#     2. Redistributions in binary form must reproduce the above copyright 
#        notice, this list of conditions and the following disclaimer in the 
#        documentation and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
# POSSIBILITY OF SUCH DAMAGE.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=dpt-breakout-server
PKG_RELEASE=1

PKG_BUILD_DIR := $(KERNEL_BUILD_DIR)/$(PKG_NAME)
PKG_MAINTAINER:=Daan Pape <daan@dptechnics.com>

PKG_BUILD_DEPENDS = ustream-ssl libiwinfo libuci libubus libubox libblobmsg-json libcurl libpthread

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/dpt-breakout-server/default
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=Web Servers/Proxies
  TITLE:=DPTechnics dpt-breakout-server for the DPT-Module
endef

define Package/dpt-breakout-server
  $(Package/dpt-breakout-server/default)
  DEPENDS:=+libubox +libjson-c +libiwinfo +libsqlite3 +libuci +libubus +libblobmsg-json +libcurl +libpthread
endef

define Package/dpt-breakout-server/description
  The dpt-breakout-server is the C web framework developed by DPTechnics which enables
  the easy development of high performance embedded IoT applications on the DPTechnics
  DPT-Module platform. More information on www.dptechnics.com
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

define Package/dpt-breakout-server/conffiles
	/etc/config/dpt-breakout-server
endef

define Package/dpt-breakout-server/install
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/dpt-breakout-server.init $(1)/etc/init.d/dpt-breakout-server
	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_CONF) ./files/dpt-breakout-server.config $(1)/etc/config/dpt-breakout-server
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/dpt-breakout-server $(1)/usr/sbin/dpt-breakout-server
endef

$(eval $(call BuildPackage,dpt-breakout-server))
