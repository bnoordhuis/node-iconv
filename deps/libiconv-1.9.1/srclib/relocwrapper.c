/* Relocating wrapper program.
   Copyright (C) 2003 Free Software Foundation, Inc.
   Written by Bruno Haible <bruno@clisp.org>, 2003.

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

/* Dependencies:
   relocwrapper
    -> progname
    -> progreloc
        -> xreadlink
        -> canonicalize
    -> relocatable
    -> setenv
    -> strerror

   Macros that need to be set while compiling this file:
     - ENABLE_RELOCATABLE 1
     - INSTALLPREFIX the base installation directory
     - INSTALLDIR the directory into which this program is installed
     - LIBPATHVAR the platform dependent runtime library path variable
     - LIBDIRS a comma-terminated list of strings representing the list of
       directories that contain the libraries at installation time

   We don't want to internationalize this wrapper because then it would
   depend on libintl and therefore need relocation itself.  So use only
   libc functions, no gettext(), no error(), no xmalloc(), no xsetenv().
 */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if HAVE_UNISTD_H
# include <unistd.h>
#endif
#include <errno.h>

#include "progname.h"
#include "relocatable.h"
#include "setenv.h"

/* Return a copy of the filename, with an extra ".bin" at the end.  */
static char *
add_dotbin (const char *filename)
{
  size_t filename_len = strlen (filename);
  char *result = (char *) malloc (filename_len + 4 + 1);

  if (result != NULL)
    {
      memcpy (result, filename, filename_len);
      memcpy (result + filename_len, ".bin", 4 + 1);
      return result;
    }
  else
    {
      fprintf (stderr, "%s: %s\n", program_name, "memory exhausted");
      exit (1);
    }
}

/* List of directories that contain the libraries.  */
static const char *libdirs[] = { LIBDIRS NULL };
/* Verify that at least one directory is given.  */
typedef int verify1[2 * (sizeof (libdirs) / sizeof (libdirs[0]) > 1) - 1];

/* Relocate the list of directories that contain the libraries.  */
static void
relocate_libdirs ()
{
  size_t i;

  for (i = 0; i < sizeof (libdirs) / sizeof (libdirs[0]) - 1; i++)
    libdirs[i] = relocate (libdirs[i]);
}

/* Activate the list of directories in the LIBPATHVAR.  */
static void
activate_libdirs ()
{
  const char *old_value;
  size_t total;
  size_t i;
  char *value;
  char *p;

  old_value = getenv (LIBPATHVAR);
  if (old_value == NULL)
    old_value = "";

  total = 0;
  for (i = 0; i < sizeof (libdirs) / sizeof (libdirs[0]) - 1; i++)
    total += strlen (libdirs[i]) + 1;
  total += strlen (old_value) + 1;

  value = (char *) malloc (total);
  if (value == NULL)
    {
      fprintf (stderr, "%s: %s\n", program_name, "memory exhausted");
      exit (1);
    }
  p = value;
  for (i = 0; i < sizeof (libdirs) / sizeof (libdirs[0]) - 1; i++)
    {
      size_t len = strlen (libdirs[i]);
      memcpy (p, libdirs[i], len);
      p += len;
      *p++ = ':';
    }
  if (old_value[0] != '\0')
    strcpy (p, old_value);
  else
    p[-1] = '\0';

  if (setenv (LIBPATHVAR, value, 1) < 0)
    {
      fprintf (stderr, "%s: %s\n", program_name, "memory exhausted");
      exit (1);
    }
}

int
main (int argc, char *argv[])
{
  char *full_program_name;

  /* Set the program name and perform preparations for
     get_full_program_name() and relocate().  */
  set_program_name_and_installdir (argv[0], INSTALLPREFIX, INSTALLDIR);

  /* Get the full program path.  (Important if accessed through a symlink.)  */
  full_program_name = get_full_program_name ();
  if (full_program_name == NULL)
    full_program_name = argv[0];

  /* Invoke the real program, with suffix ".bin".  */
  argv[0] = add_dotbin (full_program_name);
  relocate_libdirs ();
  activate_libdirs ();
  execv (argv[0], argv);
  fprintf (stderr, "%s: could not execute %s: %s\n",
	   program_name, argv[0], strerror (errno));
  exit (127);
}
