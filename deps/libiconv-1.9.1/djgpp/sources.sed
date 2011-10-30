# Fixes for lib/iconv.c.
# All encodings files recide in encdings dir now.
/^#[ 	]*include/ s|"encodings\.def|"encodings/encodings.def|
/^#[ 	]*include/ s|"encodings_aix\.def|"encodings/aix.def|
/^#[ 	]*include/ s|"encodings_dos\.def|"encodings/dos.def|
/^#[ 	]*include/ s|"encodings_osf1\.def|"encodings/osf1.def|
/^#[ 	]*include/ s|"encodings_local\.def|"encodings/local.def|
/^#[ 	]*include/ s|"aliases\.h|"aliases/aliases.h|
/^#[ 	]*include/ s|"aliases_aix\.h|"aliases/aix.h|
/^#[ 	]*include/ s|"aliases_dos\.h|"aliases/dos.h|
/^#[ 	]*include/ s|"aliases_osf1\.h|"aliases/osf1.h|
/^#[ 	]*include/ s|"aliases_local\.h|"aliases/local.h|

# Fixes for lib/converters.h, cns11643??.h and iso?????.h files.
# All cns, iso, georgian and mac files recide in their respective dirs now.
/^#[ 	]*include/ s|"cns|&/|
/^#[ 	]*include/ s|"iso|&/|
/^#[ 	]*include/ s|"georgian_|"georgian/|
/^#[ 	]*include/ s|"mac_|"mac/|
