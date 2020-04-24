{
  'variables': {
    'node_iconv_use_system_libiconv%': 0,
  },

  'targets': [
    {
      'target_name': 'iconv',
      'sources': ['binding.c'],
      'ccflags': ['-Wall', '-Wextra'],
      # Have to repeat flags on mac because of gyp's xcode emulation "feature".
      'xcode_settings': {
        'WARNING_CFLAGS': ['-Wall', '-Wextra'],
      },
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
