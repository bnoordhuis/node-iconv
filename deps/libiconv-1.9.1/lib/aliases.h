/* ANSI-C code produced by gperf version 3.0.1 */
/* Command-line: gperf -m 10 lib/aliases.gperf  */
/* Computed positions: -k'1,3-11,$' */

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
#error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gnu-gperf@gnu.org>."
#endif

#line 1 "lib/aliases.gperf"
struct alias { int name; unsigned int encoding_index; };

#define TOTAL_KEYWORDS 332
#define MIN_WORD_LENGTH 2
#define MAX_WORD_LENGTH 45
#define MIN_HASH_VALUE 15
#define MAX_HASH_VALUE 935
/* maximum key range = 921, duplicates = 0 */

#ifdef __GNUC__
__inline
#else
#ifdef __cplusplus
inline
#endif
#endif
static unsigned int
aliases_hash (register const char *str, register unsigned int len)
{
  static const unsigned short asso_values[] =
    {
      936, 936, 936, 936, 936, 936, 936, 936, 936, 936,
      936, 936, 936, 936, 936, 936, 936, 936, 936, 936,
      936, 936, 936, 936, 936, 936, 936, 936, 936, 936,
      936, 936, 936, 936, 936, 936, 936, 936, 936, 936,
      936, 936, 936, 936, 936,   6,  35, 936,  44,   5,
        6,  18,  60,   9,   8,  50,  14,  13, 280, 936,
      936, 936, 936, 936, 936, 107, 231,   5,  16,   7,
      169,  93,  11,   5,  65, 172,  10, 158,   8,   5,
       92, 936,  61,  38,  98, 152, 309,  89, 220,   6,
        6, 936, 936, 936, 936,  60, 936, 936, 936, 936,
      936, 936, 936, 936, 936, 936, 936, 936, 936, 936,
      936, 936, 936, 936, 936, 936, 936, 936, 936, 936,
      936, 936, 936, 936, 936, 936, 936, 936
    };
  register int hval = len;

  switch (hval)
    {
      default:
        hval += asso_values[(unsigned char)str[10]];
      /*FALLTHROUGH*/
      case 10:
        hval += asso_values[(unsigned char)str[9]];
      /*FALLTHROUGH*/
      case 9:
        hval += asso_values[(unsigned char)str[8]];
      /*FALLTHROUGH*/
      case 8:
        hval += asso_values[(unsigned char)str[7]];
      /*FALLTHROUGH*/
      case 7:
        hval += asso_values[(unsigned char)str[6]];
      /*FALLTHROUGH*/
      case 6:
        hval += asso_values[(unsigned char)str[5]];
      /*FALLTHROUGH*/
      case 5:
        hval += asso_values[(unsigned char)str[4]];
      /*FALLTHROUGH*/
      case 4:
        hval += asso_values[(unsigned char)str[3]];
      /*FALLTHROUGH*/
      case 3:
        hval += asso_values[(unsigned char)str[2]];
      /*FALLTHROUGH*/
      case 2:
      case 1:
        hval += asso_values[(unsigned char)str[0]];
        break;
    }
  return hval + asso_values[(unsigned char)str[len - 1]];
}

struct stringpool_t
  {
    char stringpool_str15[sizeof("CN")];
    char stringpool_str17[sizeof("L1")];
    char stringpool_str18[sizeof("L2")];
    char stringpool_str19[sizeof("HZ")];
    char stringpool_str20[sizeof("L6")];
    char stringpool_str21[sizeof("L5")];
    char stringpool_str26[sizeof("L8")];
    char stringpool_str29[sizeof("862")];
    char stringpool_str30[sizeof("L3")];
    char stringpool_str33[sizeof("866")];
    char stringpool_str34[sizeof("C99")];
    char stringpool_str38[sizeof("EUCCN")];
    char stringpool_str41[sizeof("CP1251")];
    char stringpool_str43[sizeof("CP1252")];
    char stringpool_str44[sizeof("CP862")];
    char stringpool_str45[sizeof("EUC-CN")];
    char stringpool_str47[sizeof("CP1256")];
    char stringpool_str48[sizeof("CP866")];
    char stringpool_str49[sizeof("CP1255")];
    char stringpool_str52[sizeof("CP1361")];
    char stringpool_str53[sizeof("CP932")];
    char stringpool_str55[sizeof("CP819")];
    char stringpool_str57[sizeof("CP936")];
    char stringpool_str59[sizeof("CP1258")];
    char stringpool_str62[sizeof("L7")];
    char stringpool_str67[sizeof("CP1253")];
    char stringpool_str72[sizeof("L4")];
    char stringpool_str75[sizeof("CP1133")];
    char stringpool_str77[sizeof("R8")];
    char stringpool_str84[sizeof("CHINESE")];
    char stringpool_str85[sizeof("ISO8859-1")];
    char stringpool_str87[sizeof("ISO8859-2")];
    char stringpool_str91[sizeof("ISO8859-6")];
    char stringpool_str92[sizeof("ISO-8859-1")];
    char stringpool_str93[sizeof("ISO8859-5")];
    char stringpool_str94[sizeof("ISO-8859-2")];
    char stringpool_str97[sizeof("ISO8859-16")];
    char stringpool_str98[sizeof("ISO-8859-6")];
    char stringpool_str99[sizeof("ISO8859-15")];
    char stringpool_str100[sizeof("ISO-8859-5")];
    char stringpool_str101[sizeof("ISO8859-9")];
    char stringpool_str103[sizeof("ISO8859-8")];
    char stringpool_str104[sizeof("ISO-8859-16")];
    char stringpool_str105[sizeof("850")];
    char stringpool_str106[sizeof("ISO-8859-15")];
    char stringpool_str108[sizeof("ISO-8859-9")];
    char stringpool_str109[sizeof("CP949")];
    char stringpool_str110[sizeof("ISO-8859-8")];
    char stringpool_str111[sizeof("ISO8859-3")];
    char stringpool_str112[sizeof("ISO-IR-6")];
    char stringpool_str114[sizeof("CYRILLIC")];
    char stringpool_str116[sizeof("ISO-2022-CN")];
    char stringpool_str117[sizeof("ISO8859-13")];
    char stringpool_str118[sizeof("ISO-8859-3")];
    char stringpool_str119[sizeof("CP1250")];
    char stringpool_str120[sizeof("CP950")];
    char stringpool_str121[sizeof("CP850")];
    char stringpool_str122[sizeof("ISO646-CN")];
    char stringpool_str123[sizeof("SJIS")];
    char stringpool_str124[sizeof("ISO-8859-13")];
    char stringpool_str125[sizeof("ISO-IR-126")];
    char stringpool_str126[sizeof("ISO-IR-226")];
    char stringpool_str127[sizeof("ISO-IR-166")];
    char stringpool_str129[sizeof("ISO-IR-165")];
    char stringpool_str131[sizeof("CP1257")];
    char stringpool_str132[sizeof("ASCII")];
    char stringpool_str134[sizeof("ISO-IR-58")];
    char stringpool_str136[sizeof("CP367")];
    char stringpool_str137[sizeof("LATIN1")];
    char stringpool_str138[sizeof("ISO-IR-159")];
    char stringpool_str139[sizeof("LATIN2")];
    char stringpool_str140[sizeof("GB2312")];
    char stringpool_str142[sizeof("ISO-IR-199")];
    char stringpool_str143[sizeof("LATIN6")];
    char stringpool_str145[sizeof("LATIN5")];
    char stringpool_str146[sizeof("ISO_8859-1")];
    char stringpool_str147[sizeof("CSISO2022CN")];
    char stringpool_str148[sizeof("ISO_8859-2")];
    char stringpool_str149[sizeof("ISO-IR-138")];
    char stringpool_str151[sizeof("CP1254")];
    char stringpool_str152[sizeof("ISO_8859-6")];
    char stringpool_str154[sizeof("ISO_8859-5")];
    char stringpool_str155[sizeof("LATIN8")];
    char stringpool_str157[sizeof("ISO-IR-101")];
    char stringpool_str158[sizeof("ISO_8859-16")];
    char stringpool_str159[sizeof("JP")];
    char stringpool_str160[sizeof("ISO_8859-15")];
    char stringpool_str161[sizeof("ISO-CELTIC")];
    char stringpool_str162[sizeof("ISO_8859-9")];
    char stringpool_str163[sizeof("LATIN3")];
    char stringpool_str164[sizeof("ISO_8859-8")];
    char stringpool_str165[sizeof("UHC")];
    char stringpool_str169[sizeof("ISO8859-10")];
    char stringpool_str170[sizeof("ISO_8859-15:1998")];
    char stringpool_str171[sizeof("MAC")];
    char stringpool_str172[sizeof("ISO_8859-3")];
    char stringpool_str173[sizeof("ISO-IR-109")];
    char stringpool_str175[sizeof("ISO8859-7")];
    char stringpool_str176[sizeof("ISO-8859-10")];
    char stringpool_str177[sizeof("CSASCII")];
    char stringpool_str178[sizeof("ISO_8859-13")];
    char stringpool_str179[sizeof("ISO-IR-179")];
    char stringpool_str182[sizeof("ISO-8859-7")];
    char stringpool_str184[sizeof("ISO-IR-203")];
    char stringpool_str189[sizeof("ISO-IR-149")];
    char stringpool_str190[sizeof("MS-EE")];
    char stringpool_str191[sizeof("ISO-IR-148")];
    char stringpool_str192[sizeof("US")];
    char stringpool_str194[sizeof("CP874")];
    char stringpool_str195[sizeof("ISO8859-4")];
    char stringpool_str196[sizeof("ISO-IR-110")];
    char stringpool_str197[sizeof("ISO_8859-10:1992")];
    char stringpool_str199[sizeof("ISO_8859-16:2000")];
    char stringpool_str201[sizeof("ISO8859-14")];
    char stringpool_str202[sizeof("ISO-8859-4")];
    char stringpool_str203[sizeof("IBM862")];
    char stringpool_str205[sizeof("SJIS-WIN")];
    char stringpool_str206[sizeof("ISO-IR-57")];
    char stringpool_str207[sizeof("IBM866")];
    char stringpool_str208[sizeof("ISO-8859-14")];
    char stringpool_str209[sizeof("ISO-IR-127")];
    char stringpool_str210[sizeof("ISO-2022-CN-EXT")];
    char stringpool_str211[sizeof("ISO-IR-87")];
    char stringpool_str212[sizeof("ISO-IR-157")];
    char stringpool_str213[sizeof("UCS-2")];
    char stringpool_str214[sizeof("IBM819")];
    char stringpool_str216[sizeof("SJIS-OPEN")];
    char stringpool_str219[sizeof("CSUNICODE")];
    char stringpool_str221[sizeof("ISO_8859-14:1998")];
    char stringpool_str222[sizeof("ISO-IR-14")];
    char stringpool_str225[sizeof("ELOT_928")];
    char stringpool_str227[sizeof("LATIN7")];
    char stringpool_str228[sizeof("UNICODE-1-1")];
    char stringpool_str229[sizeof("CSUNICODE11")];
    char stringpool_str230[sizeof("ISO_8859-10")];
    char stringpool_str232[sizeof("JIS0208")];
    char stringpool_str233[sizeof("UCS-2LE")];
    char stringpool_str235[sizeof("ISO-IR-100")];
    char stringpool_str236[sizeof("ISO_8859-7")];
    char stringpool_str238[sizeof("CHAR")];
    char stringpool_str239[sizeof("JIS_C6226-1983")];
    char stringpool_str244[sizeof("TIS620")];
    char stringpool_str247[sizeof("LATIN4")];
    char stringpool_str248[sizeof("X0212")];
    char stringpool_str251[sizeof("TIS-620")];
    char stringpool_str252[sizeof("CSISO159JISX02121990")];
    char stringpool_str253[sizeof("CSISO14JISC6220RO")];
    char stringpool_str256[sizeof("ISO_8859-4")];
    char stringpool_str259[sizeof("ISO-2022-JP-1")];
    char stringpool_str260[sizeof("ISO-2022-JP-2")];
    char stringpool_str262[sizeof("ISO_8859-14")];
    char stringpool_str263[sizeof("MS-CYRL")];
    char stringpool_str265[sizeof("JIS_C6220-1969-RO")];
    char stringpool_str266[sizeof("EUCJP")];
    char stringpool_str269[sizeof("GB18030")];
    char stringpool_str273[sizeof("EUC-JP")];
    char stringpool_str278[sizeof("CSUNICODE11UTF7")];
    char stringpool_str279[sizeof("UNICODE-1-1-UTF-7")];
    char stringpool_str280[sizeof("IBM850")];
    char stringpool_str281[sizeof("TIS620.2529-1")];
    char stringpool_str283[sizeof("ISO-IR-144")];
    char stringpool_str285[sizeof("X0201")];
    char stringpool_str286[sizeof("MACCYRILLIC")];
    char stringpool_str287[sizeof("UCS-4LE")];
    char stringpool_str288[sizeof("WINDOWS-1251")];
    char stringpool_str289[sizeof("WINDOWS-1252")];
    char stringpool_str290[sizeof("CSISO2022JP2")];
    char stringpool_str291[sizeof("WINDOWS-1256")];
    char stringpool_str292[sizeof("WINDOWS-1255")];
    char stringpool_str293[sizeof("EUCTW")];
    char stringpool_str294[sizeof("EUCJP-WIN")];
    char stringpool_str295[sizeof("IBM367")];
    char stringpool_str296[sizeof("TIS620-0")];
    char stringpool_str297[sizeof("WINDOWS-1258")];
    char stringpool_str298[sizeof("TIS620.2533-1")];
    char stringpool_str300[sizeof("EUC-TW")];
    char stringpool_str301[sizeof("WINDOWS-1253")];
    char stringpool_str302[sizeof("CSISOLATIN1")];
    char stringpool_str303[sizeof("X0208")];
    char stringpool_str304[sizeof("CSISOLATIN2")];
    char stringpool_str305[sizeof("EUCJP-OPEN")];
    char stringpool_str306[sizeof("GB_2312-80")];
    char stringpool_str308[sizeof("CSISOLATIN6")];
    char stringpool_str309[sizeof("CSISOLATINCYRILLIC")];
    char stringpool_str310[sizeof("CSISOLATIN5")];
    char stringpool_str311[sizeof("EUCKR")];
    char stringpool_str313[sizeof("GREEK8")];
    char stringpool_str316[sizeof("KSC_5601")];
    char stringpool_str317[sizeof("GB_1988-80")];
    char stringpool_str318[sizeof("EUC-KR")];
    char stringpool_str320[sizeof("ISO-10646-UCS-2")];
    char stringpool_str321[sizeof("UCS-4")];
    char stringpool_str322[sizeof("MULELAO-1")];
    char stringpool_str324[sizeof("ECMA-118")];
    char stringpool_str325[sizeof("KOI8-R")];
    char stringpool_str326[sizeof("CSUCS4")];
    char stringpool_str327[sizeof("WINDOWS-1250")];
    char stringpool_str328[sizeof("CSISOLATIN3")];
    char stringpool_str329[sizeof("ISO646-US")];
    char stringpool_str330[sizeof("CSKOI8R")];
    char stringpool_str331[sizeof("US-ASCII")];
    char stringpool_str333[sizeof("WINDOWS-1257")];
    char stringpool_str334[sizeof("MS-ANSI")];
    char stringpool_str337[sizeof("TIS620.2533-0")];
    char stringpool_str340[sizeof("IBM-CP1133")];
    char stringpool_str343[sizeof("WINDOWS-1254")];
    char stringpool_str344[sizeof("ISO-2022-JP")];
    char stringpool_str346[sizeof("BIG5")];
    char stringpool_str347[sizeof("MACICELAND")];
    char stringpool_str348[sizeof("MACINTOSH")];
    char stringpool_str350[sizeof("ISO646-JP")];
    char stringpool_str353[sizeof("BIG-5")];
    char stringpool_str354[sizeof("UTF-16")];
    char stringpool_str355[sizeof("CSWINDOWS31J")];
    char stringpool_str358[sizeof("CSBIG5")];
    char stringpool_str360[sizeof("UTF-8")];
    char stringpool_str361[sizeof("ARMSCII-8")];
    char stringpool_str363[sizeof("UTF-32")];
    char stringpool_str365[sizeof("CN-BIG5")];
    char stringpool_str367[sizeof("CSKSC56011987")];
    char stringpool_str368[sizeof("ROMAN8")];
    char stringpool_str369[sizeof("KOREAN")];
    char stringpool_str372[sizeof("UTF-16LE")];
    char stringpool_str373[sizeof("VISCII")];
    char stringpool_str374[sizeof("ISO-10646-UCS-4")];
    char stringpool_str375[sizeof("CSISO2022JP")];
    char stringpool_str378[sizeof("CSGB2312")];
    char stringpool_str383[sizeof("UTF-32LE")];
    char stringpool_str385[sizeof("CSVISCII")];
    char stringpool_str389[sizeof("ISO-2022-KR")];
    char stringpool_str393[sizeof("HP-ROMAN8")];
    char stringpool_str396[sizeof("MACTHAI")];
    char stringpool_str397[sizeof("CSISOLATINHEBREW")];
    char stringpool_str398[sizeof("HZ-GB-2312")];
    char stringpool_str399[sizeof("KOI8-T")];
    char stringpool_str401[sizeof("KS_C_5601-1989")];
    char stringpool_str406[sizeof("ASMO-708")];
    char stringpool_str409[sizeof("CSISOLATINARABIC")];
    char stringpool_str411[sizeof("UCS-2-INTERNAL")];
    char stringpool_str412[sizeof("CSISOLATIN4")];
    char stringpool_str415[sizeof("WINDOWS-31J")];
    char stringpool_str416[sizeof("ECMA-114")];
    char stringpool_str417[sizeof("EUCJP-MS")];
    char stringpool_str420[sizeof("CSISO2022KR")];
    char stringpool_str421[sizeof("UNICODELITTLE")];
    char stringpool_str424[sizeof("EUC-JP-MS")];
    char stringpool_str427[sizeof("TCVN")];
    char stringpool_str431[sizeof("EXTENDED_UNIX_CODE_PACKED_FORMAT_FOR_JAPANESE")];
    char stringpool_str432[sizeof("UTF-7")];
    char stringpool_str434[sizeof("VISCII1.1-1")];
    char stringpool_str438[sizeof("KS_C_5601-1987")];
    char stringpool_str440[sizeof("GBK")];
    char stringpool_str444[sizeof("ISO_8859-5:1988")];
    char stringpool_str445[sizeof("CSIBM866")];
    char stringpool_str446[sizeof("WINDOWS-874")];
    char stringpool_str447[sizeof("ISO_8859-9:1989")];
    char stringpool_str449[sizeof("ISO_8859-8:1988")];
    char stringpool_str452[sizeof("CSEUCTW")];
    char stringpool_str453[sizeof("ISO_8859-3:1988")];
    char stringpool_str454[sizeof("UCS-2BE")];
    char stringpool_str456[sizeof("GREEK")];
    char stringpool_str457[sizeof("CSPC862LATINHEBREW")];
    char stringpool_str459[sizeof("JIS_X0212")];
    char stringpool_str462[sizeof("CSMACINTOSH")];
    char stringpool_str465[sizeof("UCS-4-INTERNAL")];
    char stringpool_str466[sizeof("ARABIC")];
    char stringpool_str467[sizeof("JISX0201-1976")];
    char stringpool_str470[sizeof("CSEUCKR")];
    char stringpool_str471[sizeof("SHIFT-JIS")];
    char stringpool_str474[sizeof("CSISO87JISX0208")];
    char stringpool_str476[sizeof("ISO_8859-1:1987")];
    char stringpool_str477[sizeof("ISO_8859-2:1987")];
    char stringpool_str478[sizeof("CN-GB-ISOIR165")];
    char stringpool_str479[sizeof("ISO_8859-6:1987")];
    char stringpool_str481[sizeof("CSISO57GB1988")];
    char stringpool_str482[sizeof("CSSHIFTJIS")];
    char stringpool_str483[sizeof("CSISO58GB231280")];
    char stringpool_str485[sizeof("CSHPROMAN8")];
    char stringpool_str489[sizeof("MACCENTRALEUROPE")];
    char stringpool_str494[sizeof("HEBREW")];
    char stringpool_str495[sizeof("ISO_8859-4:1988")];
    char stringpool_str496[sizeof("JIS_X0201")];
    char stringpool_str506[sizeof("TCVN-5712")];
    char stringpool_str507[sizeof("KOI8-U")];
    char stringpool_str508[sizeof("UCS-4BE")];
    char stringpool_str511[sizeof("TCVN5712-1")];
    char stringpool_str512[sizeof("GEORGIAN-ACADEMY")];
    char stringpool_str513[sizeof("JIS_X0212-1990")];
    char stringpool_str514[sizeof("JIS_X0208")];
    char stringpool_str518[sizeof("MACROMAN")];
    char stringpool_str521[sizeof("ISO_8859-7:1987")];
    char stringpool_str525[sizeof("SHIFT_JIS")];
    char stringpool_str531[sizeof("WCHAR_T")];
    char stringpool_str534[sizeof("JIS_X0208-1983")];
    char stringpool_str542[sizeof("MS-HEBR")];
    char stringpool_str544[sizeof("JIS_X0212.1990-0")];
    char stringpool_str557[sizeof("GEORGIAN-PS")];
    char stringpool_str560[sizeof("JIS_X0208-1990")];
    char stringpool_str561[sizeof("CSISOLATINGREEK")];
    char stringpool_str569[sizeof("KOI8-RU")];
    char stringpool_str571[sizeof("CN-GB")];
    char stringpool_str576[sizeof("ANSI_X3.4-1986")];
    char stringpool_str577[sizeof("ISO_646.IRV:1991")];
    char stringpool_str578[sizeof("MACCROATIAN")];
    char stringpool_str582[sizeof("ANSI_X3.4-1968")];
    char stringpool_str588[sizeof("MS_KANJI")];
    char stringpool_str592[sizeof("JAVA")];
    char stringpool_str593[sizeof("UTF-16BE")];
    char stringpool_str604[sizeof("UTF-32BE")];
    char stringpool_str616[sizeof("CSPC850MULTILINGUAL")];
    char stringpool_str622[sizeof("UNICODEBIG")];
    char stringpool_str644[sizeof("BIG5HKSCS")];
    char stringpool_str647[sizeof("CSHALFWIDTHKATAKANA")];
    char stringpool_str650[sizeof("JOHAB")];
    char stringpool_str651[sizeof("BIG5-HKSCS")];
    char stringpool_str655[sizeof("UCS-2-SWAPPED")];
    char stringpool_str661[sizeof("NEXTSTEP")];
    char stringpool_str667[sizeof("MACHEBREW")];
    char stringpool_str683[sizeof("MACGREEK")];
    char stringpool_str684[sizeof("MS-GREEK")];
    char stringpool_str692[sizeof("MACUKRAINE")];
    char stringpool_str693[sizeof("MACARABIC")];
    char stringpool_str709[sizeof("UCS-4-SWAPPED")];
    char stringpool_str721[sizeof("MACTURKISH")];
    char stringpool_str731[sizeof("MACROMANIA")];
    char stringpool_str809[sizeof("TCVN5712-1:1993")];
    char stringpool_str826[sizeof("MS-TURK")];
    char stringpool_str828[sizeof("BIGFIVE")];
    char stringpool_str835[sizeof("BIG-FIVE")];
    char stringpool_str900[sizeof("CSEUCPKDFMTJAPANESE")];
    char stringpool_str908[sizeof("MS-ARAB")];
    char stringpool_str935[sizeof("WINBALTRIM")];
  };
static const struct stringpool_t stringpool_contents =
  {
    "CN",
    "L1",
    "L2",
    "HZ",
    "L6",
    "L5",
    "L8",
    "862",
    "L3",
    "866",
    "C99",
    "EUCCN",
    "CP1251",
    "CP1252",
    "CP862",
    "EUC-CN",
    "CP1256",
    "CP866",
    "CP1255",
    "CP1361",
    "CP932",
    "CP819",
    "CP936",
    "CP1258",
    "L7",
    "CP1253",
    "L4",
    "CP1133",
    "R8",
    "CHINESE",
    "ISO8859-1",
    "ISO8859-2",
    "ISO8859-6",
    "ISO-8859-1",
    "ISO8859-5",
    "ISO-8859-2",
    "ISO8859-16",
    "ISO-8859-6",
    "ISO8859-15",
    "ISO-8859-5",
    "ISO8859-9",
    "ISO8859-8",
    "ISO-8859-16",
    "850",
    "ISO-8859-15",
    "ISO-8859-9",
    "CP949",
    "ISO-8859-8",
    "ISO8859-3",
    "ISO-IR-6",
    "CYRILLIC",
    "ISO-2022-CN",
    "ISO8859-13",
    "ISO-8859-3",
    "CP1250",
    "CP950",
    "CP850",
    "ISO646-CN",
    "SJIS",
    "ISO-8859-13",
    "ISO-IR-126",
    "ISO-IR-226",
    "ISO-IR-166",
    "ISO-IR-165",
    "CP1257",
    "ASCII",
    "ISO-IR-58",
    "CP367",
    "LATIN1",
    "ISO-IR-159",
    "LATIN2",
    "GB2312",
    "ISO-IR-199",
    "LATIN6",
    "LATIN5",
    "ISO_8859-1",
    "CSISO2022CN",
    "ISO_8859-2",
    "ISO-IR-138",
    "CP1254",
    "ISO_8859-6",
    "ISO_8859-5",
    "LATIN8",
    "ISO-IR-101",
    "ISO_8859-16",
    "JP",
    "ISO_8859-15",
    "ISO-CELTIC",
    "ISO_8859-9",
    "LATIN3",
    "ISO_8859-8",
    "UHC",
    "ISO8859-10",
    "ISO_8859-15:1998",
    "MAC",
    "ISO_8859-3",
    "ISO-IR-109",
    "ISO8859-7",
    "ISO-8859-10",
    "CSASCII",
    "ISO_8859-13",
    "ISO-IR-179",
    "ISO-8859-7",
    "ISO-IR-203",
    "ISO-IR-149",
    "MS-EE",
    "ISO-IR-148",
    "US",
    "CP874",
    "ISO8859-4",
    "ISO-IR-110",
    "ISO_8859-10:1992",
    "ISO_8859-16:2000",
    "ISO8859-14",
    "ISO-8859-4",
    "IBM862",
    "SJIS-WIN",
    "ISO-IR-57",
    "IBM866",
    "ISO-8859-14",
    "ISO-IR-127",
    "ISO-2022-CN-EXT",
    "ISO-IR-87",
    "ISO-IR-157",
    "UCS-2",
    "IBM819",
    "SJIS-OPEN",
    "CSUNICODE",
    "ISO_8859-14:1998",
    "ISO-IR-14",
    "ELOT_928",
    "LATIN7",
    "UNICODE-1-1",
    "CSUNICODE11",
    "ISO_8859-10",
    "JIS0208",
    "UCS-2LE",
    "ISO-IR-100",
    "ISO_8859-7",
    "CHAR",
    "JIS_C6226-1983",
    "TIS620",
    "LATIN4",
    "X0212",
    "TIS-620",
    "CSISO159JISX02121990",
    "CSISO14JISC6220RO",
    "ISO_8859-4",
    "ISO-2022-JP-1",
    "ISO-2022-JP-2",
    "ISO_8859-14",
    "MS-CYRL",
    "JIS_C6220-1969-RO",
    "EUCJP",
    "GB18030",
    "EUC-JP",
    "CSUNICODE11UTF7",
    "UNICODE-1-1-UTF-7",
    "IBM850",
    "TIS620.2529-1",
    "ISO-IR-144",
    "X0201",
    "MACCYRILLIC",
    "UCS-4LE",
    "WINDOWS-1251",
    "WINDOWS-1252",
    "CSISO2022JP2",
    "WINDOWS-1256",
    "WINDOWS-1255",
    "EUCTW",
    "EUCJP-WIN",
    "IBM367",
    "TIS620-0",
    "WINDOWS-1258",
    "TIS620.2533-1",
    "EUC-TW",
    "WINDOWS-1253",
    "CSISOLATIN1",
    "X0208",
    "CSISOLATIN2",
    "EUCJP-OPEN",
    "GB_2312-80",
    "CSISOLATIN6",
    "CSISOLATINCYRILLIC",
    "CSISOLATIN5",
    "EUCKR",
    "GREEK8",
    "KSC_5601",
    "GB_1988-80",
    "EUC-KR",
    "ISO-10646-UCS-2",
    "UCS-4",
    "MULELAO-1",
    "ECMA-118",
    "KOI8-R",
    "CSUCS4",
    "WINDOWS-1250",
    "CSISOLATIN3",
    "ISO646-US",
    "CSKOI8R",
    "US-ASCII",
    "WINDOWS-1257",
    "MS-ANSI",
    "TIS620.2533-0",
    "IBM-CP1133",
    "WINDOWS-1254",
    "ISO-2022-JP",
    "BIG5",
    "MACICELAND",
    "MACINTOSH",
    "ISO646-JP",
    "BIG-5",
    "UTF-16",
    "CSWINDOWS31J",
    "CSBIG5",
    "UTF-8",
    "ARMSCII-8",
    "UTF-32",
    "CN-BIG5",
    "CSKSC56011987",
    "ROMAN8",
    "KOREAN",
    "UTF-16LE",
    "VISCII",
    "ISO-10646-UCS-4",
    "CSISO2022JP",
    "CSGB2312",
    "UTF-32LE",
    "CSVISCII",
    "ISO-2022-KR",
    "HP-ROMAN8",
    "MACTHAI",
    "CSISOLATINHEBREW",
    "HZ-GB-2312",
    "KOI8-T",
    "KS_C_5601-1989",
    "ASMO-708",
    "CSISOLATINARABIC",
    "UCS-2-INTERNAL",
    "CSISOLATIN4",
    "WINDOWS-31J",
    "ECMA-114",
    "EUCJP-MS",
    "CSISO2022KR",
    "UNICODELITTLE",
    "EUC-JP-MS",
    "TCVN",
    "EXTENDED_UNIX_CODE_PACKED_FORMAT_FOR_JAPANESE",
    "UTF-7",
    "VISCII1.1-1",
    "KS_C_5601-1987",
    "GBK",
    "ISO_8859-5:1988",
    "CSIBM866",
    "WINDOWS-874",
    "ISO_8859-9:1989",
    "ISO_8859-8:1988",
    "CSEUCTW",
    "ISO_8859-3:1988",
    "UCS-2BE",
    "GREEK",
    "CSPC862LATINHEBREW",
    "JIS_X0212",
    "CSMACINTOSH",
    "UCS-4-INTERNAL",
    "ARABIC",
    "JISX0201-1976",
    "CSEUCKR",
    "SHIFT-JIS",
    "CSISO87JISX0208",
    "ISO_8859-1:1987",
    "ISO_8859-2:1987",
    "CN-GB-ISOIR165",
    "ISO_8859-6:1987",
    "CSISO57GB1988",
    "CSSHIFTJIS",
    "CSISO58GB231280",
    "CSHPROMAN8",
    "MACCENTRALEUROPE",
    "HEBREW",
    "ISO_8859-4:1988",
    "JIS_X0201",
    "TCVN-5712",
    "KOI8-U",
    "UCS-4BE",
    "TCVN5712-1",
    "GEORGIAN-ACADEMY",
    "JIS_X0212-1990",
    "JIS_X0208",
    "MACROMAN",
    "ISO_8859-7:1987",
    "SHIFT_JIS",
    "WCHAR_T",
    "JIS_X0208-1983",
    "MS-HEBR",
    "JIS_X0212.1990-0",
    "GEORGIAN-PS",
    "JIS_X0208-1990",
    "CSISOLATINGREEK",
    "KOI8-RU",
    "CN-GB",
    "ANSI_X3.4-1986",
    "ISO_646.IRV:1991",
    "MACCROATIAN",
    "ANSI_X3.4-1968",
    "MS_KANJI",
    "JAVA",
    "UTF-16BE",
    "UTF-32BE",
    "CSPC850MULTILINGUAL",
    "UNICODEBIG",
    "BIG5HKSCS",
    "CSHALFWIDTHKATAKANA",
    "JOHAB",
    "BIG5-HKSCS",
    "UCS-2-SWAPPED",
    "NEXTSTEP",
    "MACHEBREW",
    "MACGREEK",
    "MS-GREEK",
    "MACUKRAINE",
    "MACARABIC",
    "UCS-4-SWAPPED",
    "MACTURKISH",
    "MACROMANIA",
    "TCVN5712-1:1993",
    "MS-TURK",
    "BIGFIVE",
    "BIG-FIVE",
    "CSEUCPKDFMTJAPANESE",
    "MS-ARAB",
    "WINBALTRIM"
  };
#define stringpool ((const char *) &stringpool_contents)

static const struct alias aliases[] =
  {
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 271 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str15, ei_iso646_cn},
    {-1},
#line 60 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str17, ei_iso8859_1},
#line 68 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str18, ei_iso8859_2},
#line 319 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str19, ei_hz},
#line 133 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str20, ei_iso8859_10},
#line 125 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str21, ei_iso8859_9},
    {-1}, {-1}, {-1}, {-1},
#line 147 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str26, ei_iso8859_14},
    {-1}, {-1},
#line 196 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str29, ei_cp862},
#line 76 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str30, ei_iso8859_3},
    {-1}, {-1},
#line 200 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str33, ei_cp866},
#line 51 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str34, ei_c99},
    {-1}, {-1}, {-1},
#line 309 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str38, ei_euc_cn},
    {-1}, {-1},
#line 167 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str41, ei_cp1251},
    {-1},
#line 170 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str43, ei_cp1252},
#line 194 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str44, ei_cp862},
#line 308 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str45, ei_euc_cn},
    {-1},
#line 182 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str47, ei_cp1256},
#line 198 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str48, ei_cp866},
#line 179 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str49, ei_cp1255},
    {-1}, {-1},
#line 339 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str52, ei_johab},
#line 298 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str53, ei_cp932},
    {-1},
#line 57 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str55, ei_iso8859_1},
    {-1},
#line 314 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str57, ei_ces_gbk},
    {-1},
#line 188 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str59, ei_cp1258},
    {-1}, {-1},
#line 140 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str62, ei_iso8859_13},
    {-1}, {-1}, {-1}, {-1},
#line 173 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str67, ei_cp1253},
    {-1}, {-1}, {-1}, {-1},
#line 84 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str72, ei_iso8859_4},
    {-1}, {-1},
#line 227 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str75, ei_cp1133},
    {-1},
#line 219 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str77, ei_hp_roman8},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 276 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str84, ei_gb2312},
#line 62 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str85, ei_iso8859_1},
    {-1},
#line 70 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str87, ei_iso8859_2},
    {-1}, {-1}, {-1},
#line 102 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str91, ei_iso8859_6},
#line 53 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str92, ei_iso8859_1},
#line 93 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str93, ei_iso8859_5},
#line 63 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str94, ei_iso8859_2},
    {-1}, {-1},
#line 159 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str97, ei_iso8859_16},
#line 94 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str98, ei_iso8859_6},
#line 154 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str99, ei_iso8859_15},
#line 87 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str100, ei_iso8859_5},
#line 127 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str101, ei_iso8859_9},
    {-1},
#line 119 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str103, ei_iso8859_8},
#line 155 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str104, ei_iso8859_16},
#line 192 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str105, ei_cp850},
#line 150 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str106, ei_iso8859_15},
    {-1},
#line 120 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str108, ei_iso8859_9},
#line 336 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str109, ei_cp949},
#line 113 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str110, ei_iso8859_8},
#line 78 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str111, ei_iso8859_3},
#line 16 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str112, ei_ascii},
    {-1},
#line 91 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str114, ei_iso8859_5},
    {-1},
#line 316 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str116, ei_iso2022_cn},
#line 141 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str117, ei_iso8859_13},
#line 71 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str118, ei_iso8859_3},
#line 164 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str119, ei_cp1250},
#line 330 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str120, ei_cp950},
#line 190 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str121, ei_cp850},
#line 269 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str122, ei_iso646_cn},
#line 295 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str123, ei_sjis},
#line 136 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str124, ei_iso8859_13},
#line 106 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str125, ei_iso8859_7},
#line 158 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str126, ei_iso8859_16},
#line 235 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str127, ei_tis620},
    {-1},
#line 277 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str129, ei_isoir165},
    {-1},
#line 185 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str131, ei_cp1257},
#line 13 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str132, ei_ascii},
    {-1},
#line 274 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str134, ei_gb2312},
    {-1},
#line 19 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str136, ei_ascii},
#line 59 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str137, ei_iso8859_1},
#line 266 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str138, ei_jisx0212},
#line 67 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str139, ei_iso8859_2},
#line 310 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str140, ei_euc_cn},
    {-1},
#line 145 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str142, ei_iso8859_14},
#line 132 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str143, ei_iso8859_10},
    {-1},
#line 124 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str145, ei_iso8859_9},
#line 54 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str146, ei_iso8859_1},
#line 317 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str147, ei_iso2022_cn},
#line 64 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str148, ei_iso8859_2},
#line 116 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str149, ei_iso8859_8},
    {-1},
#line 176 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str151, ei_cp1254},
#line 95 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str152, ei_iso8859_6},
    {-1},
#line 88 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str154, ei_iso8859_5},
#line 146 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str155, ei_iso8859_14},
    {-1},
#line 66 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str157, ei_iso8859_2},
#line 156 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str158, ei_iso8859_16},
#line 248 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str159, ei_iso646_jp},
#line 151 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str160, ei_iso8859_15},
#line 148 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str161, ei_iso8859_14},
#line 121 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str162, ei_iso8859_9},
#line 75 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str163, ei_iso8859_3},
#line 114 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str164, ei_iso8859_8},
#line 337 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str165, ei_cp949},
    {-1}, {-1}, {-1},
#line 135 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str169, ei_iso8859_10},
#line 152 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str170, ei_iso8859_15},
#line 204 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str171, ei_mac_roman},
#line 72 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str172, ei_iso8859_3},
#line 74 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str173, ei_iso8859_3},
    {-1},
#line 112 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str175, ei_iso8859_7},
#line 128 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str176, ei_iso8859_10},
#line 22 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str177, ei_ascii},
#line 137 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str178, ei_iso8859_13},
#line 138 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str179, ei_iso8859_13},
    {-1}, {-1},
#line 103 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str182, ei_iso8859_7},
    {-1},
#line 153 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str184, ei_iso8859_15},
    {-1}, {-1}, {-1}, {-1},
#line 282 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str189, ei_ksc5601},
#line 166 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str190, ei_cp1250},
#line 123 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str191, ei_iso8859_9},
#line 21 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str192, ei_ascii},
    {-1},
#line 236 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str194, ei_cp874},
#line 86 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str195, ei_iso8859_4},
#line 82 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str196, ei_iso8859_4},
#line 130 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str197, ei_iso8859_10},
    {-1},
#line 157 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str199, ei_iso8859_16},
    {-1},
#line 149 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str201, ei_iso8859_14},
#line 79 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str202, ei_iso8859_4},
#line 195 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str203, ei_cp862},
    {-1},
#line 302 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str205, ei_cp932},
#line 270 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str206, ei_iso646_cn},
#line 199 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str207, ei_cp866},
#line 142 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str208, ei_iso8859_14},
#line 97 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str209, ei_iso8859_6},
#line 318 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str210, ei_iso2022_cn_ext},
#line 259 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str211, ei_jisx0208},
#line 131 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str212, ei_iso8859_10},
#line 24 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str213, ei_ucs2},
#line 58 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str214, ei_iso8859_1},
    {-1},
#line 301 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str216, ei_cp932},
    {-1}, {-1},
#line 26 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str219, ei_ucs2},
    {-1},
#line 144 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str221, ei_iso8859_14},
#line 247 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str222, ei_iso646_jp},
    {-1}, {-1},
#line 108 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str225, ei_iso8859_7},
    {-1},
#line 139 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str227, ei_iso8859_13},
#line 29 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str228, ei_ucs2be},
#line 30 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str229, ei_ucs2be},
#line 129 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str230, ei_iso8859_10},
    {-1},
#line 257 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str232, ei_jisx0208},
#line 31 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str233, ei_ucs2le},
    {-1},
#line 56 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str235, ei_iso8859_1},
#line 104 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str236, ei_iso8859_7},
    {-1},
#line 342 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str238, ei_local_char},
#line 260 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str239, ei_jisx0208},
    {-1}, {-1}, {-1}, {-1},
#line 230 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str244, ei_tis620},
    {-1}, {-1},
#line 83 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str247, ei_iso8859_4},
#line 265 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str248, ei_jisx0212},
    {-1}, {-1},
#line 229 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str251, ei_tis620},
#line 267 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str252, ei_jisx0212},
#line 249 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str253, ei_iso646_jp},
    {-1}, {-1},
#line 80 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str256, ei_iso8859_4},
    {-1}, {-1},
#line 305 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str259, ei_iso2022_jp1},
#line 306 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str260, ei_iso2022_jp2},
    {-1},
#line 143 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str262, ei_iso8859_14},
#line 169 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str263, ei_cp1251},
    {-1},
#line 245 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str265, ei_iso646_jp},
#line 286 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str266, ei_euc_jp},
    {-1}, {-1},
#line 315 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str269, ei_gb18030},
    {-1}, {-1}, {-1},
#line 285 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str273, ei_euc_jp},
    {-1}, {-1}, {-1}, {-1},
#line 46 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str278, ei_utf7},
#line 45 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str279, ei_utf7},
#line 191 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str280, ei_cp850},
#line 232 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str281, ei_tis620},
    {-1},
#line 90 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str283, ei_iso8859_5},
    {-1},
#line 252 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str285, ei_jisx0201},
#line 210 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str286, ei_mac_cyrillic},
#line 37 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str287, ei_ucs4le},
#line 168 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str288, ei_cp1251},
#line 171 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str289, ei_cp1252},
#line 307 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str290, ei_iso2022_jp2},
#line 183 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str291, ei_cp1256},
#line 180 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str292, ei_cp1255},
#line 322 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str293, ei_euc_tw},
#line 292 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str294, ei_eucjp_ms},
#line 20 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str295, ei_ascii},
#line 231 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str296, ei_tis620},
#line 189 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str297, ei_cp1258},
#line 234 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str298, ei_tis620},
    {-1},
#line 321 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str300, ei_euc_tw},
#line 174 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str301, ei_cp1253},
#line 61 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str302, ei_iso8859_1},
#line 258 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str303, ei_jisx0208},
#line 69 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str304, ei_iso8859_2},
#line 290 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str305, ei_eucjp_ms},
#line 273 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str306, ei_gb2312},
    {-1},
#line 134 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str308, ei_iso8859_10},
#line 92 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str309, ei_iso8859_5},
#line 126 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str310, ei_iso8859_9},
#line 334 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str311, ei_euc_kr},
    {-1},
#line 109 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str313, ei_iso8859_7},
    {-1}, {-1},
#line 279 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str316, ei_ksc5601},
#line 268 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str317, ei_iso646_cn},
#line 333 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str318, ei_euc_kr},
    {-1},
#line 25 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str320, ei_ucs2},
#line 33 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str321, ei_ucs4},
#line 226 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str322, ei_mulelao},
    {-1},
#line 107 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str324, ei_iso8859_7},
#line 160 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str325, ei_koi8_r},
#line 35 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str326, ei_ucs4},
#line 165 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str327, ei_cp1250},
#line 77 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str328, ei_iso8859_3},
#line 14 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str329, ei_ascii},
#line 161 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str330, ei_koi8_r},
#line 12 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str331, ei_ascii},
    {-1},
#line 186 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str333, ei_cp1257},
#line 172 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str334, ei_cp1252},
    {-1}, {-1},
#line 233 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str337, ei_tis620},
    {-1}, {-1},
#line 228 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str340, ei_cp1133},
    {-1}, {-1},
#line 177 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str343, ei_cp1254},
#line 303 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str344, ei_iso2022_jp},
    {-1},
#line 324 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str346, ei_ces_big5},
#line 207 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str347, ei_mac_iceland},
#line 203 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str348, ei_mac_roman},
    {-1},
#line 246 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str350, ei_iso646_jp},
    {-1}, {-1},
#line 325 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str353, ei_ces_big5},
#line 38 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str354, ei_utf16},
#line 300 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str355, ei_cp932},
    {-1}, {-1},
#line 329 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str358, ei_ces_big5},
    {-1},
#line 23 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str360, ei_utf8},
#line 222 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str361, ei_armscii_8},
    {-1},
#line 41 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str363, ei_utf32},
    {-1},
#line 328 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str365, ei_ces_big5},
    {-1},
#line 283 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str367, ei_ksc5601},
#line 218 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str368, ei_hp_roman8},
#line 284 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str369, ei_ksc5601},
    {-1}, {-1},
#line 40 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str372, ei_utf16le},
#line 238 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str373, ei_viscii},
#line 34 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str374, ei_ucs4},
#line 304 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str375, ei_iso2022_jp},
    {-1}, {-1},
#line 312 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str378, ei_euc_cn},
    {-1}, {-1}, {-1}, {-1},
#line 43 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str383, ei_utf32le},
    {-1},
#line 240 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str385, ei_viscii},
    {-1}, {-1}, {-1},
#line 340 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str389, ei_iso2022_kr},
    {-1}, {-1}, {-1},
#line 217 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str393, ei_hp_roman8},
    {-1}, {-1},
#line 216 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str396, ei_mac_thai},
#line 118 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str397, ei_iso8859_8},
#line 320 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str398, ei_hz},
#line 225 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str399, ei_koi8_t},
    {-1},
#line 281 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str401, ei_ksc5601},
    {-1}, {-1}, {-1}, {-1},
#line 99 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str406, ei_iso8859_6},
    {-1}, {-1},
#line 101 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str409, ei_iso8859_6},
    {-1},
#line 47 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str411, ei_ucs2internal},
#line 85 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str412, ei_iso8859_4},
    {-1}, {-1},
#line 299 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str415, ei_cp932},
#line 98 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str416, ei_iso8859_6},
#line 289 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str417, ei_eucjp_ms},
    {-1}, {-1},
#line 341 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str420, ei_iso2022_kr},
#line 32 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str421, ei_ucs2le},
    {-1}, {-1},
#line 291 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str424, ei_eucjp_ms},
    {-1}, {-1},
#line 241 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str427, ei_tcvn},
    {-1}, {-1}, {-1},
#line 287 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str431, ei_euc_jp},
#line 44 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str432, ei_utf7},
    {-1},
#line 239 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str434, ei_viscii},
    {-1}, {-1}, {-1},
#line 280 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str438, ei_ksc5601},
    {-1},
#line 313 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str440, ei_ces_gbk},
    {-1}, {-1}, {-1},
#line 89 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str444, ei_iso8859_5},
#line 201 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str445, ei_cp866},
#line 237 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str446, ei_cp874},
#line 122 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str447, ei_iso8859_9},
    {-1},
#line 115 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str449, ei_iso8859_8},
    {-1}, {-1},
#line 323 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str452, ei_euc_tw},
#line 73 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str453, ei_iso8859_3},
#line 27 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str454, ei_ucs2be},
    {-1},
#line 110 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str456, ei_iso8859_7},
#line 197 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str457, ei_cp862},
    {-1},
#line 262 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str459, ei_jisx0212},
    {-1}, {-1},
#line 205 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str462, ei_mac_roman},
    {-1}, {-1},
#line 49 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str465, ei_ucs4internal},
#line 100 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str466, ei_iso8859_6},
#line 251 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str467, ei_jisx0201},
    {-1}, {-1},
#line 335 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str470, ei_euc_kr},
#line 294 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str471, ei_sjis},
    {-1}, {-1},
#line 261 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str474, ei_jisx0208},
    {-1},
#line 55 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str476, ei_iso8859_1},
#line 65 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str477, ei_iso8859_2},
#line 278 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str478, ei_isoir165},
#line 96 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str479, ei_iso8859_6},
    {-1},
#line 272 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str481, ei_iso646_cn},
#line 297 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str482, ei_sjis},
#line 275 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str483, ei_gb2312},
    {-1},
#line 220 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str485, ei_hp_roman8},
    {-1}, {-1}, {-1},
#line 206 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str489, ei_mac_centraleurope},
    {-1}, {-1}, {-1}, {-1},
#line 117 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str494, ei_iso8859_8},
#line 81 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str495, ei_iso8859_4},
#line 250 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str496, ei_jisx0201},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 242 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str506, ei_tcvn},
#line 162 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str507, ei_koi8_u},
#line 36 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str508, ei_ucs4be},
    {-1}, {-1},
#line 243 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str511, ei_tcvn},
#line 223 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str512, ei_georgian_academy},
#line 264 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str513, ei_jisx0212},
#line 254 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str514, ei_jisx0208},
    {-1}, {-1}, {-1},
#line 202 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str518, ei_mac_roman},
    {-1}, {-1},
#line 105 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str521, ei_iso8859_7},
    {-1}, {-1}, {-1},
#line 293 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str525, ei_sjis},
    {-1}, {-1}, {-1}, {-1}, {-1},
#line 343 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str531, ei_local_wchar_t},
    {-1}, {-1},
#line 255 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str534, ei_jisx0208},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 181 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str542, ei_cp1255},
    {-1},
#line 263 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str544, ei_jisx0212},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1},
#line 224 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str557, ei_georgian_ps},
    {-1}, {-1},
#line 256 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str560, ei_jisx0208},
#line 111 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str561, ei_iso8859_7},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 163 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str569, ei_koi8_ru},
    {-1},
#line 311 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str571, ei_euc_cn},
    {-1}, {-1}, {-1}, {-1},
#line 18 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str576, ei_ascii},
#line 15 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str577, ei_ascii},
#line 208 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str578, ei_mac_croatian},
    {-1}, {-1}, {-1},
#line 17 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str582, ei_ascii},
    {-1}, {-1}, {-1}, {-1}, {-1},
#line 296 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str588, ei_sjis},
    {-1}, {-1}, {-1},
#line 52 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str592, ei_java},
#line 39 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str593, ei_utf16be},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1},
#line 42 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str604, ei_utf32be},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1},
#line 193 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str616, ei_cp850},
    {-1}, {-1}, {-1}, {-1}, {-1},
#line 28 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str622, ei_ucs2be},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1},
#line 332 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str644, ei_big5hkscs},
    {-1}, {-1},
#line 253 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str647, ei_jisx0201},
    {-1}, {-1},
#line 338 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str650, ei_johab},
#line 331 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str651, ei_big5hkscs},
    {-1}, {-1}, {-1},
#line 48 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str655, ei_ucs2swapped},
    {-1}, {-1}, {-1}, {-1}, {-1},
#line 221 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str661, ei_nextstep},
    {-1}, {-1}, {-1}, {-1}, {-1},
#line 214 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str667, ei_mac_hebrew},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 212 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str683, ei_mac_greek},
#line 175 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str684, ei_cp1253},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 211 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str692, ei_mac_ukraine},
#line 215 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str693, ei_mac_arabic},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 50 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str709, ei_ucs4swapped},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1},
#line 213 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str721, ei_mac_turkish},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 209 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str731, ei_mac_romania},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1}, {-1}, {-1},
#line 244 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str809, ei_tcvn},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 178 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str826, ei_cp1254},
    {-1},
#line 327 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str828, ei_ces_big5},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 326 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str835, ei_ces_big5},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1},
#line 288 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str900, ei_euc_jp},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 184 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str908, ei_cp1256},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 187 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str935, ei_cp1257}
  };

#ifdef __GNUC__
__inline
#endif
const struct alias *
aliases_lookup (register const char *str, register unsigned int len)
{
  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register int key = aliases_hash (str, len);

      if (key <= MAX_HASH_VALUE && key >= 0)
        {
          register int o = aliases[key].name;
          if (o >= 0)
            {
              register const char *s = o + stringpool;

              if (*str == *s && !strcmp (str + 1, s + 1))
                return &aliases[key];
            }
        }
    }
  return 0;
}
