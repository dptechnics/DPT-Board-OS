#
# libwebsockets makefile for openwrt
#

include $(TOPDIR)/rules.mk

PKG_NAME:=libwebsockets
PKG_VERSION:=2015-04-29
PKG_RELEASE=$(PKG_SOURCE_VERSION)

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/warmcat/libwebsockets.git
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION)-$(PKG_SOURCE_VERSION).tar.gz
PKG_SOURCE_VERSION:=3ae1badae7a05e0982e0dfbcb078da3d4b92a81d
CMAKE_INSTALL:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

CMAKE_OPTIONS += -DLWS_OPENSSL_CLIENT_CERTS=/etc/ssl/certs
CMAKE_OPTIONS += -DLWS_OPENSSL_SUPPORT=ON
CMAKE_OPTIONS += -DLWS_WITH_SSL=ON
CMAKE_OPTIONS += -DLWS_WITHOUT_TESTAPPS=OFF

define Package/libwebsockets/Default
	SECTION:=libs
	CATEGORY:=Libraries
	TITLE:=libwebsockets
	DEPENDS:=+zlib +libopenssl
endef

define Package/libwebsockets
	$(call Package/libwebsockets/Default)
	TITLE+= (libraries)
endef

define Package/libwebsockets/description
	libwebsockets
	This package contains libwebsocket libraries
endef

define Package/libwebsockets-examples
	$(call Package/libwebsockets/Default)
	DEPENDS:=libwebsockets
	TITLE+= (examples)
endef

define Package/libwebsockets-examples/description
	libwebsockets examples
	This package contains libwebsockets examples
endef

define Package/libwebsockets/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libwebsockets.so* $(1)/usr/lib/
endef

define Package/libwebsockets-examples/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/libwebsockets-test-client $(1)/usr/bin/
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/libwebsockets-test-echo $(1)/usr/bin/
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/libwebsockets-test-fraggle $(1)/usr/bin/
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/libwebsockets-test-ping $(1)/usr/bin/
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/libwebsockets-test-server $(1)/usr/bin/
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/libwebsockets-test-server-extpoll $(1)/usr/bin/

	$(INSTALL_DIR) $(1)/usr/share/libwebsockets-test-server
	$(INSTALL_DATA) $(PKG_INSTALL_DIR)/usr/share/libwebsockets-test-server/favicon.ico $(1)/usr/share/libwebsockets-test-server/
	$(INSTALL_DATA) $(PKG_INSTALL_DIR)/usr/share/libwebsockets-test-server/leaf.jpg $(1)/usr/share/libwebsockets-test-server/
	$(INSTALL_DATA) $(PKG_INSTALL_DIR)/usr/share/libwebsockets-test-server/libwebsockets.org-logo.png $(1)/usr/share/libwebsockets-test-server/
	$(INSTALL_DATA) $(PKG_INSTALL_DIR)/usr/share/libwebsockets-test-server/libwebsockets-test-server.key.pem $(1)/usr/share/libwebsockets-test-server/
	$(INSTALL_DATA) $(PKG_INSTALL_DIR)/usr/share/libwebsockets-test-server/libwebsockets-test-server.pem $(1)/usr/share/libwebsockets-test-server/
	$(INSTALL_DATA) $(PKG_INSTALL_DIR)/usr/share/libwebsockets-test-server/test.html $(1)/usr/share/libwebsockets-test-server/
endef

$(eval $(call BuildPackage,libwebsockets))
$(eval $(call BuildPackage,libwebsockets-examples))
