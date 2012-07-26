UNAME := $(shell uname)

ifeq ($(NODE_PATH),)
	NODE_PATH = /usr/local
endif

ifeq ($(EXTRA_CXXFLAGS),)
	EXTRA_CXXFLAGS = -I$(NODE_PATH)/include/node
endif

LIBICONV_DIR	=deps/libiconv
LIBICONV	=$(LIBICONV_DIR)/lib/.libs/libiconv.a

CXXFLAGS	=-I$(LIBICONV_DIR)/include -I$(LIBICONV_DIR)/lib $(EXTRA_CXXFLAGS) -D_FORTIFY_SOURCE=2 -DEV_MULTIPLICITY=0 -fPIC -Wall -Wextra -ansi
CXXFLAGS_DEBUG	=-O0 -g
CXXFLAGS_RELEASE=-O2

all:	release

debug:	CXXFLAGS += $(CXXFLAGS_DEBUG)
debug:	build

release:	CXXFLAGS += $(CXXFLAGS_RELEASE)
release:	build

build:	$(LIBICONV) binding.o
ifeq ($(UNAME),Darwin)
	$(CXX) -flat_namespace -undefined suppress -shared -o iconv.node binding.o $(LIBICONV)
else
	$(CXX) -shared -o iconv.node binding.o $(LIBICONV)
endif

install:	all
	mkdir -p $(HOME)/.node_libraries && cp iconv.node $(HOME)/.node_libraries

clean:
	rm -f binding.o iconv.node

distclean:	clean
	[ ! -f $(LIBICONV_DIR)/Makefile ] || $(MAKE) -C $(LIBICONV_DIR) distclean

binding.o:	binding.cc

$(LIBICONV_DIR)/Makefile:
	cd $(LIBICONV_DIR) && ./configure --disable-shared --enable-static --enable-relocatable --enable-extra-encodings

$(LIBICONV):	$(LIBICONV_DIR)/Makefile
ifeq ($(UNAME),Darwin)
	# see https://github.com/bnoordhuis/node-iconv/issues/19
	$(MAKE) -C $(LIBICONV_DIR)
else
	$(MAKE) -C $(LIBICONV_DIR) CFLAGS+=-fPIC
endif
