UNAME		:= $(shell uname)

NODE_PATH	= /usr/local

LIBICONV_DIR	= deps/libiconv-1.13.1
LIBICONV	= $(LIBICONV_DIR)/lib/.libs/libiconv.a

CXXFLAGS	= -I$(LIBICONV_DIR)/include -I$(NODE_PATH)/include/node -O2 -fPIC -Wall -ansi

OBJS		= src/iconv.o src/Recoder.o

all:	$(LIBICONV) $(OBJS)
ifeq ($(UNAME),Darwin)
	$(CXX) -flat_namespace -undefined suppress -shared -o iconv.o $(OBJS) $(LIBICONV)
else
	$(CXX) -shared -o iconv.node $(OBJS) $(LIBICONV)
endif

install:	all
	mkdir -p $(HOME)/.node_libraries && cp iconv.node $(HOME)/.node_libraries

clean:
	rm -f $(OBJS) iconv.node

distclean:	clean
	cd $(LIBICONV_DIR) && $(MAKE) distclean

iconv.o:	Recoder.h iconv.cc

Recoder.o:	Recoder.h Recoder.cc

$(LIBICONV_DIR)/Makefile:
	cd $(LIBICONV_DIR) && ./configure --disable-shared --enable-static --enable-relocatable --enable-extra-encodings

$(LIBICONV):	$(LIBICONV_DIR)/Makefile
	cd $(LIBICONV_DIR) && $(MAKE) CFLAGS+=-fPIC
