import Options

def set_options(ctx):
	ctx.tool_options('compiler_cxx')
	ctx.add_option('--libiconv', action='store', default=None, help='libiconv prefix')

def configure(ctx):
	ctx.check_tool('compiler_cxx')
	ctx.check_tool('node_addon')

	prefix = Options.options.libiconv
	if prefix:
		ctx.env.append_value('LIB_ICONV', 'iconv')
		ctx.env.append_value('LIBPATH_ICONV', prefix + '/lib')
		ctx.env.append_value('CPPATH_ICONV', prefix + '/include')
	
def build(ctx):
	t = ctx.new_task_gen('cxx', 'shlib', 'node_addon', source='iconv.cc', target='iconv')
	if Options.options.libiconv:
		t.uselib = 'ICONV'
