{
  'variables': {
    'node_iconv_use_system_libiconv%': 0,
  },

  'targets': [
    {
      'target_name': 'iconv',
      'cflags!': [ '-fno-exceptions' ],
      'cflags_cc!': [ '-fno-exceptions' ],
      'xcode_settings': { 
        'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
        'CLANG_CXX_LIBRARY': 'libc++',
        'MACOSX_DEPLOYMENT_TARGET': '10.7',
        'GCC_ENABLE_CPP_RTTI': 'NO',
        'WARNING_CFLAGS': ['-Wall', '-Wextra', '-Wno-unused-parameter'],
      },
      'msvs_settings': {
        'VCCLCompilerTool': { 'ExceptionHandling': 1 },
      },
      'include_dirs': [
        '<!@(node -p "require(\'node-addon-api\').include")',
        'support'
      ],
      'dependencies': [
          "<!(node -p \"require('node-addon-api').gyp\")"],
      'sources': ['src/binding.cc'],
      'ccflags': [
        '-Wall',
        '-Wextra',
        '-Wno-unused-parameter',  # Squelches warnings coming from v8.h.
        '-fno-exceptions',
        '-fno-rtti',
      ],
      'conditions': [
        ['node_iconv_use_system_libiconv==0', {
          'defines': ['ICONV_CONST=const', 'ENABLE_EXTRA=1'],
          'include_dirs': ['support'],
          'sources': [
            'deps/libiconv/lib/iconv.c',
            'support/localcharset.c',
          ],
          'cflags!': ['-W', '-Wall', '-Wextra'],
          'msvs_settings': {
            'VCCLCompilerTool': {
              'DisableSpecificWarnings': [
                '4018',  # Signed/unsigned comparison.
                '4090',  # Const/non-const mismatch.
                '4244',  # Narrowing cast.
                '4267',  # Narrowing cast.
              ],
            },
          },
          'xcode_settings': {
            'WARNING_CFLAGS!': ['-W', '-Wall', '-Wextra'],
            'WARNING_CFLAGS': [
              '-Wno-parentheses-equality',
              '-Wno-static-in-inline',
              '-Wno-tautological-compare',
            ],
          },
        }],
      ],
    },
  ],
}
