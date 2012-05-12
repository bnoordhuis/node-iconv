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
      ],
      'include_dirs': [
        'deps/libiconv/srclib',
        'support',
      ],
      'sources': [
        'deps/libiconv/lib/iconv.c',
        'iconv.cc'
      ],
      'conditions': [
        ['OS == "win"', {
          'sources': ['deps/libiconv/libcharset/lib/localcharset.c'],
          'defines': [
            'WIN32_NATIVE=1',
            'LIBDIR="."', # not actually used
          ],
        }],
      ],
    }
  ]
}
