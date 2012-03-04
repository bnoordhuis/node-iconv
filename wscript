import os
import sys

def make(ctx, rule):
	node_path = ctx.env and ctx.env['CPPPATH_NODE'] or []
	if isinstance(node_path, basestring): node_path = [node_path]
	extra_cxxflags = ' '.join('-I%s' % path for path in node_path)
	bin = 'bsd' in sys.platform and 'gmake' or 'make'
	cmd = '%s %s EXTRA_CXXFLAGS="%s"' % (bin, rule, extra_cxxflags)
	if os.system(cmd): raise RuntimeError('`make %s` failed' % rule)

def set_options(ctx):
	pass

def configure(ctx):
	ctx.check_tool('node_addon')

def build(ctx):
	make(ctx, 'all')

def clean(ctx):
	make(ctx, 'distclean')
