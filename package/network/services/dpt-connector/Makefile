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

PKG_NAME:=dpt-connector
PKG_RELEASE:=1
PKG_BUILD_DIR := $(KERNEL_BUILD_DIR)/$(PKG_NAME)
PKG_MAINTAINER := Daan Pape <daan@dptechnics.com>
PKG_BUILD_DEPENDS = libcurl libjson-c

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/dpt-connector
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=BlueCherry
  TITLE:=BlueCherry IoT platform connector
  DEPENDS:=+libcurl +libjson-c
endef

define Package/dpt-connector/description
  The DPT-Connector manages the IoT-connection to the BlueCherry
  platform on platform.bluecherry.io
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

define Package/dpt-connector/conffiles
	/etc/config/dpt-connector
endef

define Package/dpt-connector/install
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/dpt-connector.init $(1)/etc/init.d/dpt-connector

	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_CONF) ./files/dpt-connector.config $(1)/etc/config/dpt-connector

	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/dpt-connector $(1)/usr/sbin/dpt-connector
endef

$(eval $(call BuildPackage,dpt-connector))
