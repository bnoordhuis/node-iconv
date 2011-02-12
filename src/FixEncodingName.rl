// workaround for shortcoming in libiconv: "UTF-8" is recognized but "UTF8" isn't
const char* Recoder::FixEncodingName(const char* name) {
	const char* p = name, *const pe = p + 64;
	int cs;

	%%{
		machine FixEncodingName;

		write data;
		write init;
		write exec;

		main := /UTF/i
			( ( /7/     0 ) @ { return "UTF-7";    }
			| ( /8/     0 ) @ { return "UTF-8";    }
			| ( /16/    0 ) @ { return "UTF-16";   }
			| ( /32/    0 ) @ { return "UTF-32";   }
			| ( /16LE/i 0 ) @ { return "UTF-16LE"; }
			| ( /16BE/i 0 ) @ { return "UTF-16BE"; }
			| ( /32LE/i 0 ) @ { return "UTF-32LE"; }
			| ( /32BE/i 0 ) @ { return "UTF-32BE"; }
			)
			;
	}%%

	return name;
}
