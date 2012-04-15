# Additional editing of Makefiles
/extrasub/,/^CEOF/ {
  /^CEOF$/ i\
# DJGPP specific Makefile changes.\
  /^aliaspath *	*=/s,:,";",g\
  /^lispdir *	*=/ c\\\\\
lispdir = \\$(prefix)/gnu/emacs/site-lisp\
  /^docdir *	*=/s,/doc/,/gnudocs/,g\
  /TEXINPUTS=/s,:,";",g\
  /PATH=/s,:,";",g\
  /CFLAGS[ 	]*=/s,=,= -O2 -g,g\
  s,config\\.h\\.in,config.h-in,g\
  s,\\.tab\\.c,_tab.c,g\
  s,\\.tab\\.h,_tab.h,g\
  s,\\.old\\.,_old.,g\
  s,\\.\\([1-9]\\)\\.html,.\\1-html,g\
  s,\\.html,-html,g\
  s,/doc,/gnudocs,g\
  s,localcharset\\.h\\.in,localcharset.h-in,g\
  s,Makefile\\.in\\.in,Makefile.in-in,g\
  s,Makefile\\.am\\.in,Makefile.am-in,g\
  /^install-info-am:/,/^$/ s,file-\\[0-9\\]\\[0-9\\],& \\$\\$file[0-9] \\$\\$file[0-9][0-9],\
  /^\\.y\\.c:/,/^$/ {\
    /\\\$(YACC)/ {\
      s,[ 	]*&&.*$,,\
      a\\\\\
	-mv -f y_tab.c \\$*.c\\\\\
	-@test -f y.tab.c && mv -f y.tab.c \\$*.c\\\\\
	-@test -f y.tab.h && mv -f y.tab.h y_tab.h\
    }\
  }
}

# Rename config.h.in into config.h-in
/^ *CONFIG_HEADERS=/,/^EOF/ {
  s|"lib/config\.h|&:lib/config.h-in|
  s|"config\.h|&:config.h-in|
}

# Rename iconv.h.in into iconv.h-in
/^ *CONFIG_FILES=/,/^EOF/ {
  s|include/iconv\.h|&:include/iconv.h-in|
}

# Replace (command) > /dev/null with `command > /dev/null`, since
# parenthesized commands always return zero status in the ported Bash,
# even if the named command doesn't exist
# This does no longer work with autoconf 2.5, libtool 1.4 and automake 1.5.
# /if ([^|;]*null/{
#   s,(,`,
#   s,),,
#   s,;  *then,`; then,
# }

# Replace (command) > /dev/null with `command > /dev/null`, since
# parenthesized commands always return zero status in the ported Bash,
# even if the named command doesn't exist
/if [^{].*null/,/ then/ {
  /test .*null/ {
    s,(,,
    s,),,
  }
}

# DOS-style absolute file names should be supported as well
/\*) srcdir=/s,/\*,[\\\\/]* | [A-z]:[\\\\/]*,
/\$]\*) INSTALL=/s,\[/\$\]\*,[\\\\/$]* | [A-z]:[\\\\/]*,
/\$]\*) ac_rel_source=/s,\[/\$\]\*,[\\\\/$]* | [A-z]:[\\\\/]*,

# Switch the order of the two Sed commands, since DOS path names
# could include a colon
/ac_file_inputs=/s,\( -e "s%\^%\$ac_given_srcdir/%"\)\( -e "s%:% $ac_given_srcdir/%g"\),\2\1,

# Prevent the spliting of conftest.subs.
# The sed script: conftest.subs is split into 48 or 90 lines long files.
# This will produce sed scripts called conftest.s1, conftest.s2, etc.
# that will not work if conftest.subs contains a multi line sed command
# at line #90. In this case the first part of the sed command will be the
# last line of conftest.s1 and the rest of the command will be the first lines
# of conftest.s2. So both script will not work properly.
# This matches the configure script produced by Autoconf 2.12
/ac_max_sed_cmds=[0-9]/ s,=.*$,=`sed -n "$=" conftest.subs`,
# This matches the configure script produced by Autoconf 2.14a
/ac_max_sed_lines=[0-9]/ s,=.*$,=`sed -n "$=" $ac_cs_root.subs `,

# The following two items are changes needed for configuring
# and compiling across partitions.
# 1) The given srcdir value is always translated from the
#    "x:" syntax into "/dev/x" syntax while we run configure.
/^[ 	]*-srcdir=\*.*$/ a\
    ac_optarg=`echo "$ac_optarg" | sed "s,^\\([A-Za-z]\\):,/dev/\\1,"`
/set X `ls -Lt \$srcdir/ i\
   if `echo $srcdir | grep "^/dev/" - > /dev/null`; then\
     srcdir=`echo "$srcdir" | sed -e "s%^/dev/%%" -e "s%/%:/%"`\
   fi

#  2) We need links across partitions,
#     so we will use "cp -pf" instead of "ln".
/# Make a symlink if possible; otherwise try a hard link./,/EOF/ {
  s,;.*then, 2>/dev/null || cp -pf \$srcdir/\$ac_source \$ac_dest&,
}

# Let libtool use _libs all the time.
/objdir=/s,\.libs,_libs,
