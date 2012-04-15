/* Copyright (C) 2000-2003 Free Software Foundation, Inc.
   This file is part of the GNU LIBICONV Library.

   The GNU LIBICONV Library is free software; you can redistribute it
   and/or modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either version 2
   of the License, or (at your option) any later version.

   The GNU LIBICONV Library is distributed in the hope that it will be
   useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with the GNU LIBICONV Library; see the file COPYING.LIB.
   If not, write to the Free Software Foundation, Inc., 59 Temple Place -
   Suite 330, Boston, MA 02111-1307, USA.  */

#include "config.h"
#ifndef ICONV_CONST
# define ICONV_CONST const
#endif

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iconv.h>
#include <errno.h>
#if HAVE_LOCALE_H
#include <locale.h>
#endif
#include <fcntl.h>

/* Ensure that iconv_no_i18n does not depend on libintl.  */
#ifdef NO_I18N
# undef ENABLE_NLS
# undef ENABLE_RELOCATABLE
#endif

#include "binary-io.h"
#include "progname.h"
#include "relocatable.h"
#include "gettext.h"

#define _(str) gettext(str)

#if O_BINARY
  static int force_binary = 0;
#endif

static int discard_unconvertible = 0;
static int silent = 0;

static void usage (int exitcode)
{
  const char* helpstring1 =
#if O_BINARY
    _("Usage: iconv [--binary] [-c] [-s] [-f fromcode] [-t tocode] [file ...]");
#else
    _("Usage: iconv [-c] [-s] [-f fromcode] [-t tocode] [file ...]");
#endif
  const char* helpstring2 =
    _("or:    iconv -l");
  fprintf(exitcode ? stderr : stdout, "%s\n%s\n", helpstring1, helpstring2);
  exit(exitcode);
}

static void print_version (void)
{
  printf("iconv (GNU libiconv %d.%d)\n",
         _libiconv_version >> 8, _libiconv_version & 0xff);
  printf("Copyright (C) %s Free Software Foundation, Inc.\n", "2000-2002");
  printf(_("\
This is free software; see the source for copying conditions.  There is NO\n\
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n"));
  printf(_("Written by %s.\n"),"Bruno Haible");
  exit(0);
}

static int print_one (unsigned int namescount, const char * const * names,
                      void* data)
{
  unsigned int i;
  (void)data;
  for (i = 0; i < namescount; i++) {
    if (i > 0)
      putc(' ',stdout);
    fputs(names[i],stdout);
  }
  putc('\n',stdout);
  return 0;
}

static int convert (iconv_t cd, FILE* infile, const char* infilename)
{
  char inbuf[4096+4096];
  size_t inbufrest = 0;
  char outbuf[4096];
  int status = 0;

#if O_BINARY
  if (force_binary)
    SET_BINARY(fileno(infile));
#endif
  iconv(cd,NULL,NULL,NULL,NULL);
  for (;;) {
    size_t inbufsize = fread(inbuf+4096,1,4096,infile);
    if (inbufsize == 0) {
      if (inbufrest == 0)
        break;
      else {
        if (!silent)
          fprintf(stderr,_("iconv: %s: incomplete character or shift sequence\n"),infilename);
        return 1;
      }
    } else {
      const char* inptr = inbuf+4096-inbufrest;
      size_t insize = inbufrest+inbufsize;
      inbufrest = 0;
      while (insize > 0) {
        char* outptr = outbuf;
        size_t outsize = sizeof(outbuf);
        size_t res = iconv(cd,(ICONV_CONST char**)&inptr,&insize,&outptr,&outsize);
        if (outptr != outbuf) {
          int saved_errno = errno;
          if (fwrite(outbuf,1,outptr-outbuf,stdout) < outptr-outbuf)
            return 1;
          errno = saved_errno;
        }
        if (res == (size_t)(-1)) {
          if (errno == EILSEQ) {
            if (discard_unconvertible == 1) {
              int one = 1;
              iconvctl(cd,ICONV_SET_DISCARD_ILSEQ,&one);
              discard_unconvertible = 2;
              status = 1;
            } else {
              if (!silent)
                fprintf(stderr,_("iconv: %s: cannot convert\n"),infilename);
              return 1;
            }
          } else if (errno == EINVAL) {
            if (inbufsize == 0 || insize > 4096) {
              if (!silent)
                fprintf(stderr,_("iconv: %s: incomplete character or shift sequence\n"),infilename);
              return 1;
            } else {
              inbufrest = insize;
              if (insize > 0) {
                /* Like memcpy(inbuf+4096-insize,inptr,insize), except that
                   we cannot use memcpy here, because source and destination
                   regions may overlap. */
                char* restptr = inbuf+4096-insize;
                do { *restptr++ = *inptr++; } while (--insize > 0);
              }
              break;
            }
          } else if (errno != E2BIG) {
            if (!silent) {
              int saved_errno = errno;
              fprintf(stderr,_("iconv: %s: "),infilename);
              errno = saved_errno;
              perror("");
            }
            return 1;
          }
        }
      }
    }
  }
  {
    char* outptr = outbuf;
    size_t outsize = sizeof(outbuf);
    size_t res = iconv(cd,NULL,NULL,&outptr,&outsize);
    if (outptr != outbuf) {
      int saved_errno = errno;
      if (fwrite(outbuf,1,outptr-outbuf,stdout) < outptr-outbuf)
        return 1;
      errno = saved_errno;
    }
    if (res == (size_t)(-1)) {
      if (errno == EILSEQ) {
        if (discard_unconvertible == 1) {
          int one = 1;
          iconvctl(cd,ICONV_SET_DISCARD_ILSEQ,&one);
          discard_unconvertible = 2;
          status = 1;
        } else {
          if (!silent)
            fprintf(stderr,_("iconv: %s: cannot convert\n"),infilename);
          return 1;
        }
      } else if (errno == EINVAL) {
        if (!silent)
          fprintf(stderr,_("iconv: %s: incomplete character or shift sequence\n"),infilename);
        return 1;
      } else {
        if (!silent) {
          int saved_errno = errno;
          fprintf(stderr,_("iconv: %s: "),infilename);
          errno = saved_errno;
          perror("");
        }
        return 1;
      }
    }
  }
  if (ferror(infile)) {
    fprintf(stderr,_("iconv: %s: I/O error\n"),infilename);
    return 1;
  }
  return status;
}

int main (int argc, char* argv[])
{
  const char* fromcode = NULL;
  const char* tocode = NULL;
  int do_list = 0;
  iconv_t cd;
  int i;
  int status;

  set_program_name (argv[0]);
#if HAVE_SETLOCALE
  /* Needed for the locale dependent encodings, "char" and "wchar_t",
     and for gettext. */
  setlocale(LC_CTYPE,"");
#if ENABLE_NLS
  /* Needed for gettext. */
  setlocale(LC_MESSAGES,"");
#endif
#endif
#if ENABLE_NLS
  bindtextdomain("libiconv",relocate(LOCALEDIR));
#endif
  textdomain("libiconv");
  for (i = 1; i < argc;) {
    if (!strcmp(argv[i],"-f")) {
      if (i == argc-1) usage(1);
      if (fromcode != NULL) usage(1);
      fromcode = argv[i+1];
      i += 2;
      continue;
    }
    if (!strcmp(argv[i],"-t")) {
      if (i == argc-1) usage(1);
      if (tocode != NULL) usage(1);
      tocode = argv[i+1];
      i += 2;
      continue;
    }
    if (!strcmp(argv[i],"-l")) {
      do_list = 1;
      i++;
      continue;
    }
    if (!strcmp(argv[i],"--help")) {
      usage(0);
    }
    if (!strcmp(argv[i],"--version")) {
      print_version();
    }
#if O_BINARY
    if (!strcmp(argv[i],"--binary")) {
      force_binary = 1;
      i++;
      continue;
    }
#endif
    if (argv[i][0] == '-') {
      const char *option = argv[i] + 1;
      if (*option == '\0')
        usage(1);
      for (; *option; option++)
        switch (*option) {
          case 'c': discard_unconvertible = 1; break;
          case 's': silent = 1; break;
          default: usage(1);
        }
      i++;
      continue;
    }
    break;
  }
  if (do_list) {
    if (i != 2 || i != argc)
      usage(1);
    iconvlist(print_one,NULL);
    status = 0;
  } else {
#if O_BINARY
    if (force_binary)
      SET_BINARY(fileno(stdout));
#endif
    if (fromcode == NULL)
      fromcode = "char";
    if (tocode == NULL)
      tocode = "char";
    cd = iconv_open(tocode,fromcode);
    if (cd == (iconv_t)(-1)) {
      if (iconv_open("UCS-4",fromcode) == (iconv_t)(-1))
        fprintf(stderr,_("iconv: conversion from %s unsupported\n"),fromcode);
      else if (iconv_open(tocode,"UCS-4") == (iconv_t)(-1))
        fprintf(stderr,_("iconv: conversion to %s unsupported\n"),tocode);
      else
        fprintf(stderr,_("iconv: conversion from %s to %s unsupported\n"),fromcode,tocode);
      exit(1);
    }
    if (i == argc)
      status = convert(cd,stdin,_("(stdin)"));
    else {
      status = 0;
      for (; i < argc; i++) {
        const char* infilename = argv[i];
        FILE* infile = fopen(infilename,"r");
        if (infile == NULL) {
          int saved_errno = errno;
          fprintf(stderr,_("iconv: %s: "),infilename);
          errno = saved_errno;
          perror("");
          status = 1;
        } else {
          status |= convert(cd,infile,infilename);
          fclose(infile);
        }
      }
    }
    iconv_close(cd);
  }
  if (fflush(stdout) || ferror(stdout)) {
    fprintf(stderr,_("iconv: I/O error\n"));
    status = 1;
  }
  exit(status);
}
