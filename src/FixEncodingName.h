
#line 1 "src/FixEncodingName.rl"
// workaround for shortcoming in libiconv: "UTF-8" is recognized but "UTF8" isn't
const char* Recoder::FixEncodingName(const char* name) {
	const char* p = name, *const pe = p + 64;
	int cs;

	
#line 10 "src/FixEncodingName.h"
static const int FixEncodingName_start = 1;
static const int FixEncodingName_first_final = 19;
static const int FixEncodingName_error = 0;

static const int FixEncodingName_en_main = 1;


#line 18 "src/FixEncodingName.h"
	{
	cs = FixEncodingName_start;
	}

#line 23 "src/FixEncodingName.h"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
case 1:
	switch( (*p) ) {
		case 85: goto st2;
		case 117: goto st2;
	}
	goto st0;
st0:
cs = 0;
	goto _out;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
	switch( (*p) ) {
		case 84: goto st3;
		case 116: goto st3;
	}
	goto st0;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
	switch( (*p) ) {
		case 70: goto st4;
		case 102: goto st4;
	}
	goto st0;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
	switch( (*p) ) {
		case 49: goto st5;
		case 51: goto st11;
		case 55: goto st17;
		case 56: goto st18;
	}
	goto st0;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
	if ( (*p) == 54 )
		goto st6;
	goto st0;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
	switch( (*p) ) {
		case 0: goto tr9;
		case 66: goto st7;
		case 76: goto st9;
		case 98: goto st7;
		case 108: goto st9;
	}
	goto st0;
tr9:
#line 16 "src/FixEncodingName.rl"
	{ return "UTF-16";   }
	goto st19;
tr13:
#line 19 "src/FixEncodingName.rl"
	{ return "UTF-16BE"; }
	goto st19;
tr15:
#line 18 "src/FixEncodingName.rl"
	{ return "UTF-16LE"; }
	goto st19;
tr17:
#line 17 "src/FixEncodingName.rl"
	{ return "UTF-32";   }
	goto st19;
tr21:
#line 21 "src/FixEncodingName.rl"
	{ return "UTF-32BE"; }
	goto st19;
tr23:
#line 20 "src/FixEncodingName.rl"
	{ return "UTF-32LE"; }
	goto st19;
tr24:
#line 14 "src/FixEncodingName.rl"
	{ return "UTF-7";    }
	goto st19;
tr25:
#line 15 "src/FixEncodingName.rl"
	{ return "UTF-8";    }
	goto st19;
st19:
	if ( ++p == pe )
		goto _test_eof19;
case 19:
#line 122 "src/FixEncodingName.h"
	goto st0;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
	switch( (*p) ) {
		case 69: goto st8;
		case 101: goto st8;
	}
	goto st0;
st8:
	if ( ++p == pe )
		goto _test_eof8;
case 8:
	if ( (*p) == 0 )
		goto tr13;
	goto st0;
st9:
	if ( ++p == pe )
		goto _test_eof9;
case 9:
	switch( (*p) ) {
		case 69: goto st10;
		case 101: goto st10;
	}
	goto st0;
st10:
	if ( ++p == pe )
		goto _test_eof10;
case 10:
	if ( (*p) == 0 )
		goto tr15;
	goto st0;
st11:
	if ( ++p == pe )
		goto _test_eof11;
case 11:
	if ( (*p) == 50 )
		goto st12;
	goto st0;
st12:
	if ( ++p == pe )
		goto _test_eof12;
case 12:
	switch( (*p) ) {
		case 0: goto tr17;
		case 66: goto st13;
		case 76: goto st15;
		case 98: goto st13;
		case 108: goto st15;
	}
	goto st0;
st13:
	if ( ++p == pe )
		goto _test_eof13;
case 13:
	switch( (*p) ) {
		case 69: goto st14;
		case 101: goto st14;
	}
	goto st0;
st14:
	if ( ++p == pe )
		goto _test_eof14;
case 14:
	if ( (*p) == 0 )
		goto tr21;
	goto st0;
st15:
	if ( ++p == pe )
		goto _test_eof15;
case 15:
	switch( (*p) ) {
		case 69: goto st16;
		case 101: goto st16;
	}
	goto st0;
st16:
	if ( ++p == pe )
		goto _test_eof16;
case 16:
	if ( (*p) == 0 )
		goto tr23;
	goto st0;
st17:
	if ( ++p == pe )
		goto _test_eof17;
case 17:
	if ( (*p) == 0 )
		goto tr24;
	goto st0;
st18:
	if ( ++p == pe )
		goto _test_eof18;
case 18:
	if ( (*p) == 0 )
		goto tr25;
	goto st0;
	}
	_test_eof2: cs = 2; goto _test_eof; 
	_test_eof3: cs = 3; goto _test_eof; 
	_test_eof4: cs = 4; goto _test_eof; 
	_test_eof5: cs = 5; goto _test_eof; 
	_test_eof6: cs = 6; goto _test_eof; 
	_test_eof19: cs = 19; goto _test_eof; 
	_test_eof7: cs = 7; goto _test_eof; 
	_test_eof8: cs = 8; goto _test_eof; 
	_test_eof9: cs = 9; goto _test_eof; 
	_test_eof10: cs = 10; goto _test_eof; 
	_test_eof11: cs = 11; goto _test_eof; 
	_test_eof12: cs = 12; goto _test_eof; 
	_test_eof13: cs = 13; goto _test_eof; 
	_test_eof14: cs = 14; goto _test_eof; 
	_test_eof15: cs = 15; goto _test_eof; 
	_test_eof16: cs = 16; goto _test_eof; 
	_test_eof17: cs = 17; goto _test_eof; 
	_test_eof18: cs = 18; goto _test_eof; 

	_test_eof: {}
	_out: {}
	}

#line 24 "src/FixEncodingName.rl"


	return name;
}
