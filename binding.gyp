{
  'targets': [
    {
      'target_name': 'iconv',
      'defines': [
        'ICONV_CONST=const',
        'USE_AIX=1',
        'USE_DOS=1',
        'USE_EXTRA=1',
        'USE_OSF1=1',
        'LIBDIR="."', # not actually used
      ],
      'include_dirs': [
        'deps/libiconv/srclib',
        'support',
      ],
      'sources': [
        'deps/libiconv/libcharset/lib/localcharset.c',
        'deps/libiconv/lib/iconv.c',
        'src/iconv.cc'
      ],
      'conditions': [
        ['OS == "win"', {
          'defines': ['WIN32_NATIVE=1'],
        }, {
          'defines': ['HAVE_WORKING_O_NOFOLLOW=1'],
          'cflags': [
            # silence warnings from iconv.c
            '-Wno-unused-function',
            '-Wno-unused-parameter',
            '-Wno-unused-variable',
          ],
        }],
      ],
    }
  ]
}
