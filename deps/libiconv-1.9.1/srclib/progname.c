/* Program name management.
   Copyright (C) 2001-2003 Free Software Foundation, Inc.
   Written by Bruno Haible <haible@clisp.cons.org>, 2001.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */


#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/* Specification.  */
#include "progname.h"

#include <stdio.h>
#include <string.h>

#undef set_program_name


/* String containing name the program is called with.
   To be initialized by main().  */
const char *program_name;

/* Set program_name, based on argv[0].  */
void
set_program_name (const char *argv0)
{
  /* libtool creates a temporary executable whose name is prefixed with
     "lt-".  Remove this prefix here.  */
#ifdef __BEOS__
  /* BeOS also makes argv[0] absolute.  Remove a leading "<dirname>/lt-".  */
  const char *slash;
  const char *base;

  slash = strrchr (argv0, '/');
  base = (slash != NULL ? slash + 1 : argv0);
  if (strncmp (base, "lt-", 3) == 0)
    argv0 = base + 3;
#else
  if (strncmp (argv0, "lt-", 3) == 0)
    argv0 += 3;
#endif
  program_name = argv0;
}


/* Indicates whether errors and warnings get prefixed with program_name.
   Default is true.  */
bool error_with_progname = true;

/* Print program_name prefix on stderr if and only if error_with_progname
   is true.  */
void
maybe_print_progname ()
{
  if (error_with_progname)
    fprintf (stderr, "%s: ", program_name);
}
