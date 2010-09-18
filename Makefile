NODE_PATH	=/usr/local

LIBICONV_DIR	=deps/libiconv-1.13.1
LIBICONV	=$(LIBICONV_DIR)/lib/.libs/libiconv.a

CXXFLAGS	=-I$(LIBICONV_DIR)/include -I$(NODE_PATH)/include/node -O2 -fPIC -Wall -ansi

all:	$(LIBICONV) iconv.o
	$(CXX) -shared -o iconv.node iconv.o $(LIBICONV)

install:	all
	cp iconv.node $(HOME)/.node_libraries

clean:
	rm -f iconv.o iconv.node

distclean:	clean
	cd $(LIBICONV_DIR) && $(MAKE) distclean

iconv.o:	iconv.cc

$(LIBICONV_DIR)/Makefile:
	cd $(LIBICONV_DIR) && ./configure --disable-shared --enable-static --enable-relocatable --enable-extra-encodings

$(LIBICONV):	$(LIBICONV_DIR)/Makefile
	cd $(LIBICONV_DIR) && $(MAKE) CFLAGS+=-fPIC
