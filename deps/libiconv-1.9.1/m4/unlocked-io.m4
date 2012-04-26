#serial 7 -*- autoconf -*-

dnl From Jim Meyering.
dnl
dnl See if the glibc *_unlocked I/O macros or functions are available.
dnl Use only those *_unlocked macros or functions that are declared
dnl (because some of them were declared in Solaris 2.5.1 but were removed
dnl in Solaris 2.6, whereas we want binaries built on Solaris 2.5.1 to run
dnl on Solaris 2.6).

AC_DEFUN([jm_FUNC_GLIBC_UNLOCKED_IO],
[
  dnl Persuade glibc <stdio.h> to declare fgets_unlocked(), fputs_unlocked()
  dnl etc.
  AC_REQUIRE([AC_GNU_SOURCE])

  AC_CHECK_DECLS_ONCE(
     [clearerr_unlocked feof_unlocked ferror_unlocked
      fflush_unlocked fgets_unlocked fputc_unlocked fputs_unlocked
      fread_unlocked fwrite_unlocked getc_unlocked
      getchar_unlocked putc_unlocked putchar_unlocked])
])
