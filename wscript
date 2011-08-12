import os

def make(ctx, rule):
	os.system('make %s NODE_INCLUDE_PATH="%s"' % (rule, ctx.env['CPPPATH_NODE']))
	os.system('cd deps/libiconv-1.13.1/ && gzip -dc ../libiconv-1.13-ja-1.patch.gz | patch -p1 && ./configure --disable-shared --enable-static --enable-relocatable --enable-extra-encodings && make && cd ../../ && make')

def set_options(ctx):
	pass

def configure(ctx):
	ctx.check_tool('node_addon')

def build(ctx):
	make(ctx, 'all')
