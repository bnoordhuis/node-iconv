/* Copyright (C) 1999-2003 Free Software Foundation, Inc.
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

/* Creates the aliases2.h table. */

#include <stdio.h>
#include <stdlib.h>

static void emit_encoding (const char* tag, const char* const* names, size_t n, const char* c_name)
{
  static unsigned int counter = 0;
  for (; n > 0; names++, n--, counter++) {
    printf("  S(%s_%u, \"",tag,counter);
    /* Output *names in upper case. */
    {
      const char* s = *names;
      for (; *s; s++) {
        unsigned char c = * (unsigned char *) s;
        if (c >= 0x80)
          exit(1);
        if (c >= 'a' && c <= 'z')
          c -= 'a'-'A';
        putc(c, stdout);
      }
    }
    printf("\", ei_%s )\n", c_name);
  }
}

int main (int argc, char* argv[])
{
  const char * tag = (argc > 1 ? argv[1] : "xxx");
#define DEFENCODING(xxx_names,xxx,xxx_ifuncs1,xxx_ifuncs2,xxx_ofuncs1,xxx_ofuncs2) \
  {                                                           \
    static const char* const names[] = BRACIFY xxx_names;     \
    emit_encoding(tag,names,sizeof(names)/sizeof(names[0]),#xxx); \
  }
#define BRACIFY(...) { __VA_ARGS__ }
#ifdef USE_AIX
#include "encodings_aix.def"
#endif
#ifdef USE_OSF1
#include "encodings_osf1.def"
#endif
#ifdef USE_DOS
#include "encodings_dos.def"
#endif
#ifdef USE_EXTRA
#include "encodings_extra.def"
#endif
#undef BRACIFY
#undef DEFENCODING
  fflush(stdout);
  if (ferror(stdout))
    exit(1);
  exit(0);
}
