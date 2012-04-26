# Sed script for tests/translit-check editing.
/set -e/ a\
# For systems that distinguish between text and binary I/O\
# the binary mode of iconv must be selected.\
UNAME=${UNAME-`uname 2>/dev/null`}\
case X$UNAME in\
  *-DOS) MODE='--binary' ;;\
  *)     MODE='' ;;\
esac
/iconv/ s/iconv/& $MODE/
