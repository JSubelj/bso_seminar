PROGRAM=main

EXTRA_CFLAGS=-DLWIP_HTTPD_CGI=1 -DLWIP_HTTPD_SSI=1 -I./fsdata

#Enable debugging
#EXTRA_CFLAGS+=-DLWIP_DEBUG=1 -DHTTPD_DEBUG=LWIP_DBG_ON

EXTRA_COMPONENTS=extras/mbedtls extras/httpd extras/i2c extras/dhcpserver

include ../../common.mk

html:
	@echo "Generating fsdata.."
	cd fsdata && ./makefsdata
