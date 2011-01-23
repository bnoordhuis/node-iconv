srcdir = '.'
blddir = 'build'
VERSION = '0.1.0'

def set_options(opt):
  opt.tool_options('compiler_cxx')

def configure(conf):
  conf.check_tool('compiler_cxx')
  conf.check_tool('node_addon')
  if conf.check(lib='iconv', libpath=['/usr/lib', '/usr/local/lib'], \
                uselib_store='ICONV'):
    conf.env.append_value('LINKFLAGS_DL', '-liconv')

def build(bld):
  iconv = bld.new_task_gen('cxx', 'shlib', 'node_addon')
  iconv.includes = '/usr/include /usr/local/include'
  iconv.target = 'iconv'
  iconv.source = 'iconv.cc'
  iconv.uselib = 'ICONV'
