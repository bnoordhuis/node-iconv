# Sed script for tests/stateful-check editing.

/set -e/ a\
# For systems that distinguish between text and binary I/O\
# the binary mode of iconv must be selected and for\
# systems with severe filename restrictions allow for\
# an alternate filename.\
UNAME=${UNAME-`uname 2>/dev/null`}\
case X$UNAME in\
  *-DOS) MODE='--binary'\
         filename=`echo "$charset" | sed "s|ISO-|ISO/|;s|2022-|2022|"` ;;\
  *)     MODE=''\
         filename="$charset" ;;\
esac
/iconv/ s/iconv/& $MODE/
s/\$charset"-snippet/$filename"-snippet/g
