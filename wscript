def set_options(ctx):
	ctx.tool_options('compiler_cxx')

def configure(ctx):
	ctx.check_tool('compiler_cxx')
	ctx.check_tool('node_addon')

	ctx.env.STATICLIB_ICONV = ['iconv']
	ctx.env.CPPPATH_ICONV   = ['deps/libiconv-1.13.1/include']
	ctx.env.LIBPATH_ICONV   = ['deps/libiconv-1.13.1/lib/.libs']

def build(ctx):
	t = ctx.new_task_gen('cxx', 'shlib', 'node_addon', source='iconv.cc', target='iconv')
