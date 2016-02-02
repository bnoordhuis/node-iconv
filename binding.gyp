{
  'targets': [
    {
      'target_name': 'iconv',
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
  ]
}
