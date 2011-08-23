import os

def make(ctx, rule):
	os.system('gzip -dc deps/libiconv-1.13-ja-1.patch.gz | patch -p1 -f -d deps/libiconv-1.13.1/')
	os.system('make %s NODE_INCLUDE_PATH="%s"' % (rule, ctx.env['CPPPATH_NODE']))

def set_options(ctx):
	pass

def configure(ctx):
	ctx.check_tool('node_addon')

def build(ctx):
	make(ctx, 'all')
