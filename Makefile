UNAME := $(shell uname)

ifeq ($(NODE_PATH),)
	NODE_PATH = /usr/local
endif

ifeq ($(NODE_INCLUDE_PATH),)
	NODE_INCLUDE_PATH = $(NODE_PATH)/include/node
endif

LIBICONV_DIR	=deps/libiconv-1.13.1
LIBICONV	=$(LIBICONV_DIR)/lib/.libs/libiconv.a

CXXFLAGS	=-I$(LIBICONV_DIR)/include -I$(LIBICONV_DIR)/lib -I$(NODE_INCLUDE_PATH) -D_FORTIFY_SOURCE=2 -DEV_MULTIPLICITY=0 -fPIC -Wall -Wextra -ansi
CXXFLAGS_DEBUG	=-O0 -g
CXXFLAGS_RELEASE=-O2

all:	release

debug:	CXXFLAGS += $(CXXFLAGS_DEBUG)
debug:	build

release:	CXXFLAGS += $(CXXFLAGS_RELEASE)
release:	build

build:	$(LIBICONV) iconv.o
ifeq ($(UNAME),Darwin)
	$(CXX) -flat_namespace -undefined suppress -shared -o iconv.node iconv.o $(LIBICONV)
else
	$(CXX) -shared -o iconv.node iconv.o $(LIBICONV)
endif

install:	all
	mkdir -p $(HOME)/.node_libraries && cp iconv.node $(HOME)/.node_libraries

clean:
	rm -f iconv.o iconv.node

distclean:	clean
	$(MAKE) -C $(LIBICONV_DIR) distclean

iconv.o:	iconv.cc

$(LIBICONV_DIR)/Makefile:
	cd $(LIBICONV_DIR) && ./configure --disable-shared --enable-static --enable-relocatable --enable-extra-encodings

$(LIBICONV):	$(LIBICONV_DIR)/Makefile
	$(MAKE) -C $(LIBICONV_DIR) CFLAGS+=-fPIC
