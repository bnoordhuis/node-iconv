all:
	node-waf configure build

install:	all
	node-waf install

clean:
	node-waf clean
