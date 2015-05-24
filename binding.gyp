{
  'targets': [
    {
      'target_name': 'iconv',
      'dependencies': ['libiconv'],
      'include_dirs': ['<!(node -e "require(\'nan\')")'],
      'sources': ['src/binding.cc'],
      'cflags': [
        '-Wall',
        '-Wextra',
        '-Wno-unused-parameter',  # Squelches warnings coming from v8.h.
        '-fno-exceptions',
        '-fno-rtti',
      ],
      # Have to repeat flags on mac because of gyp's xcode emulation "feature".
      'xcode_settings': {
        'GCC_ENABLE_CPP_EXCEPTIONS': 'NO',
        'GCC_ENABLE_CPP_RTTI': 'NO',
        'WARNING_CFLAGS': ['-Wall', '-Wextra', '-Wno-unused-parameter'],
      },
    },

    {
      'target_name': 'libiconv',
      'type': 'static_library',
      'direct_dependent_settings': {
        'include_dirs':  ['support'],
      },
      'defines': ['ICONV_CONST=const', 'ENABLE_EXTRA=1'],
      'include_dirs': [
        'deps/libiconv/srclib',
        'support',
      ],
      'sources': ['deps/libiconv/lib/iconv.c'],
      'conditions': [
        ['OS == "win"', {
          'defines': ['WIN32_NATIVE=1'],
        }, {
          'defines': ['HAVE_WORKING_O_NOFOLLOW=1'],
          'cflags!': ['-W', '-Wall', '-Wextra'],
        }],
      ],
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
    }
  ]
}
