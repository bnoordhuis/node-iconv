/*
 * Copyright (C) 1999-2003 Free Software Foundation, Inc.
 * This file is part of the GNU LIBICONV Library.
 *
 * The GNU LIBICONV Library is free software; you can redistribute it
 * and/or modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * The GNU LIBICONV Library is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with the GNU LIBICONV Library; see the file COPYING.LIB.
 * If not, write to the Free Software Foundation, Inc., 59 Temple Place -
 * Suite 330, Boston, MA 02111-1307, USA.
 */

/*
 * eucJP-ms extensions
 */

static const unsigned short eucjp_msext_2uni_pagef3[188] = {
  /* 0xf3 */
  0xfffd, 0xfffd, 0xfffd, 0xfffd, 0xfffd, 0xfffd, 0xfffd, 0xfffd,
  0xfffd, 0xfffd, 0xfffd, 0xfffd, 0xfffd, 0xfffd, 0xfffd, 0xfffd,
  0xfffd, 0xfffd, 0xfffd, 0xfffd, 0xfffd, 0xfffd, 0xfffd, 0xfffd,
  0xfffd, 0xfffd, 0xfffd, 0xfffd, 0xfffd, 0xfffd, 0xfffd, 0xfffd,
  0xfffd, 0xfffd, 0xfffd, 0xfffd, 0xfffd, 0xfffd, 0xfffd, 0xfffd,
  0xfffd, 0xfffd, 0xfffd, 0xfffd, 0xfffd, 0xfffd, 0xfffd, 0xfffd,
  0xfffd, 0xfffd, 0xfffd, 0xfffd, 0xfffd, 0xfffd, 0xfffd, 0xfffd,
  0xfffd, 0xfffd, 0xfffd, 0xfffd, 0xfffd, 0xfffd, 0xfffd, 0xfffd,
  0xfffd, 0xfffd, 0xfffd, 0xfffd, 0xfffd, 0xfffd, 0xfffd, 0xfffd,
  0xfffd, 0xfffd, 0xfffd, 0xfffd, 0xfffd, 0xfffd, 0xfffd, 0xfffd,
  0xfffd, 0xfffd, 0x2170, 0x2171, 0x2172, 0x2173, 0x2174, 0x2175,
  0x2176, 0x2177, 0x2178, 0x2179, 0x2160, 0x2161,
  /* 0xf4 */
  0x2162, 0x2163, 0x2164, 0x2165, 0x2166, 0x2167, 0x2168, 0x2169,
  0xff07, 0xff02, 0x3231, 0x2116, 0x2121, 0x70bb, 0x4efc, 0x50f4,
  0x51ec, 0x5307, 0x5324, 0xfa0e, 0x548a, 0x5759, 0xfa0f, 0xfa10,
  0x589e, 0x5bec, 0x5cf5, 0x5d53, 0xfa11, 0x5fb7, 0x6085, 0x6120,
  0x654e, 0x663b, 0x6665, 0xfa12, 0xf929, 0x6801, 0xfa13, 0xfa14,
  0x6a6b, 0x6ae2, 0x6df8, 0x6df2, 0x7028, 0xfa15, 0xfa16, 0x7501,
  0x7682, 0x769e, 0xfa17, 0x7930, 0xfa18, 0xfa19, 0xfa1a, 0xfa1b,
  0x7ae7, 0xfa1c, 0xfa1d, 0x7da0, 0x7dd6, 0xfa1e, 0x8362, 0xfa1f,
  0x85b0, 0xfa20, 0xfa21, 0x8807, 0xfa22, 0x8b7f, 0x8cf4, 0x8d76,
  0xfa23, 0xfa24, 0xfa25, 0x90de, 0xfa26, 0x9115, 0xfa27, 0xfa28,
  0x9592, 0xf9dc, 0xfa29, 0x973b, 0x974d, 0x9751, 0xfa2a, 0xfa2b,
  0xfa2c, 0x999e, 0x9ad9, 0x9b72, 0xfa2d, 0x9ed1,
};

static int
eucjp_msext_mbtowc (conv_t conv, ucs4_t *pwc, const unsigned char *s, int n)
{
  unsigned char c1 = s[0];
  if ((c1 >= 0xf3 && c1 <= 0xf4)) {
    if (n >= 2) {
      unsigned char c2 = s[1];
      if (c2 >= 0xa1 && c2 < 0xff) {
        unsigned int i = 94 * (c1 - 0xa1) + (c2 - 0xa1);
        unsigned short wc = 0xfffd;
        {
          if (i < 7896)
            wc = eucjp_msext_2uni_pagef3[i-7708];
        }
        if (wc != 0xfffd) {
          *pwc = (ucs4_t) wc;
          return 2;
        }
      }
      return RET_ILSEQ;
    }
    return RET_TOOFEW(0);
  }
  return RET_ILSEQ;
}

static const unsigned short eucjp_msext_2charset[106] = {
  0xf4ac, 0xf4ad, 0xf3fd, 0xf3fe, 0xf4a1, 0xf4a2, 0xf4a3, 0xf4a4,
  0xf4a5, 0xf4a6, 0xf4a7, 0xf4a8, 0xf3f3, 0xf3f4, 0xf3f5, 0xf3f6,
  0xf3f7, 0xf3f8, 0xf3f9, 0xf3fa, 0xf3fb, 0xf3fc, 0xf4ab, 0xf4af,
  0xf4b0, 0xf4b1, 0xf4b2, 0xf4b3, 0xf4b5, 0xf4b6, 0xf4b9, 0xf4ba,
  0xf4bb, 0xf4bc, 0xf4be, 0xf4bf, 0xf4c0, 0xf4c1, 0xf4c2, 0xf4c3,
  0xf4c6, 0xf4c9, 0xf4ca, 0xf4cc, 0xf4cb, 0xf4cd, 0xf4ae, 0xf4d0,
  0xf4d1, 0xf4d2, 0xf4d4, 0xf4d9, 0xf4dc, 0xf4dd, 0xf4df, 0xf4e1,
  0xf4e4, 0xf4e6, 0xf4e7, 0xf4e8, 0xf4ec, 0xf4ee, 0xf4f1, 0xf4f4,
  0xf4f5, 0xf4f6, 0xf4fa, 0xf4fb, 0xf4fc, 0xf4fe, 0xf4c5, 0xf4f2,
  0xf4b4, 0xf4b7, 0xf4b8, 0xf4bd, 0xf4c4, 0xf4c7, 0xf4c8, 0xf4ce,
  0xf4cf, 0xf4d3, 0xf4d5, 0xf4d6, 0xf4d7, 0xf4d8, 0xf4da, 0xf4db,
  0xf4de, 0xf4e0, 0xf4e2, 0xf4e3, 0xf4e5, 0xf4e9, 0xf4ea, 0xf4eb,
  0xf4ed, 0xf4ef, 0xf4f0, 0xf4f3, 0xf4f7, 0xf4f8, 0xf4f9, 0xf4fd,
  0xf4aa, 0xf4a9,
};

static const Summary16 eucjp_msext_uni2indx_page21[8] = {
  /* 0x2100 */
  {    0, 0x0000 }, {    0, 0x0040 }, {    1, 0x0002 }, {    2, 0x0000 },
  {    2, 0x0000 }, {    2, 0x0000 }, {    2, 0x03ff }, {   12, 0x03ff },
};
static const Summary16 eucjp_msext_uni2indx_page32[4] = {
  /* 0x3200 */
  {   22, 0x0000 }, {   22, 0x0000 }, {   22, 0x0000 }, {   22, 0x0002 },
};
static const Summary16 eucjp_msext_uni2indx_page4e[16] = {
  /* 0x4e00 */
  {   23, 0x0000 }, {   23, 0x0000 }, {   23, 0x0000 }, {   23, 0x0000 },
  {   23, 0x0000 }, {   23, 0x0000 }, {   23, 0x0000 }, {   23, 0x0000 },
  {   23, 0x0000 }, {   23, 0x0000 }, {   23, 0x0000 }, {   23, 0x0000 },
  {   23, 0x0000 }, {   23, 0x0000 }, {   23, 0x0000 }, {   23, 0x1000 },
};
static const Summary16 eucjp_msext_uni2indx_page50[31] = {
  /* 0x5000 */
  {   24, 0x0000 }, {   24, 0x0000 }, {   24, 0x0000 }, {   24, 0x0000 },
  {   24, 0x0000 }, {   24, 0x0000 }, {   24, 0x0000 }, {   24, 0x0000 },
  {   24, 0x0000 }, {   24, 0x0000 }, {   24, 0x0000 }, {   24, 0x0000 },
  {   24, 0x0000 }, {   24, 0x0000 }, {   24, 0x0000 }, {   24, 0x0010 },
  /* 0x5100 */
  {   25, 0x0000 }, {   25, 0x0000 }, {   25, 0x0000 }, {   25, 0x0000 },
  {   25, 0x0000 }, {   25, 0x0000 }, {   25, 0x0000 }, {   25, 0x0000 },
  {   25, 0x0000 }, {   25, 0x0000 }, {   25, 0x0000 }, {   25, 0x0000 },
  {   25, 0x0000 }, {   25, 0x0000 }, {   25, 0x1000 },
};
static const Summary16 eucjp_msext_uni2indx_page53[25] = {
  /* 0x5300 */
  {   26, 0x0080 }, {   27, 0x0000 }, {   27, 0x0010 }, {   28, 0x0000 },
  {   28, 0x0000 }, {   28, 0x0000 }, {   28, 0x0000 }, {   28, 0x0000 },
  {   28, 0x0000 }, {   28, 0x0000 }, {   28, 0x0000 }, {   28, 0x0000 },
  {   28, 0x0000 }, {   28, 0x0000 }, {   28, 0x0000 }, {   28, 0x0000 },
  /* 0x5400 */
  {   28, 0x0000 }, {   28, 0x0000 }, {   28, 0x0000 }, {   28, 0x0000 },
  {   28, 0x0000 }, {   28, 0x0000 }, {   28, 0x0000 }, {   28, 0x0000 },
  {   28, 0x0400 },
};
static const Summary16 eucjp_msext_uni2indx_page57[26] = {
  /* 0x5700 */
  {   29, 0x0000 }, {   29, 0x0000 }, {   29, 0x0000 }, {   29, 0x0000 },
  {   29, 0x0000 }, {   29, 0x0200 }, {   30, 0x0000 }, {   30, 0x0000 },
  {   30, 0x0000 }, {   30, 0x0000 }, {   30, 0x0000 }, {   30, 0x0000 },
  {   30, 0x0000 }, {   30, 0x0000 }, {   30, 0x0000 }, {   30, 0x0000 },
  /* 0x5800 */
  {   30, 0x0000 }, {   30, 0x0000 }, {   30, 0x0000 }, {   30, 0x0000 },
  {   30, 0x0000 }, {   30, 0x0000 }, {   30, 0x0000 }, {   30, 0x0000 },
  {   30, 0x0000 }, {   30, 0x4000 },
};
static const Summary16 eucjp_msext_uni2indx_page5b[38] = {
  /* 0x5b00 */
  {   31, 0x0000 }, {   31, 0x0000 }, {   31, 0x0000 }, {   31, 0x0000 },
  {   31, 0x0000 }, {   31, 0x0000 }, {   31, 0x0000 }, {   31, 0x0000 },
  {   31, 0x0000 }, {   31, 0x0000 }, {   31, 0x0000 }, {   31, 0x0000 },
  {   31, 0x0000 }, {   31, 0x0000 }, {   31, 0x1000 }, {   32, 0x0000 },
  /* 0x5c00 */
  {   32, 0x0000 }, {   32, 0x0000 }, {   32, 0x0000 }, {   32, 0x0000 },
  {   32, 0x0000 }, {   32, 0x0000 }, {   32, 0x0000 }, {   32, 0x0000 },
  {   32, 0x0000 }, {   32, 0x0000 }, {   32, 0x0000 }, {   32, 0x0000 },
  {   32, 0x0000 }, {   32, 0x0000 }, {   32, 0x0000 }, {   32, 0x0020 },
  /* 0x5d00 */
  {   33, 0x0000 }, {   33, 0x0000 }, {   33, 0x0000 }, {   33, 0x0000 },
  {   33, 0x0000 }, {   33, 0x0008 },
};
static const Summary16 eucjp_msext_uni2indx_page5f[35] = {
  /* 0x5f00 */
  {   34, 0x0000 }, {   34, 0x0000 }, {   34, 0x0000 }, {   34, 0x0000 },
  {   34, 0x0000 }, {   34, 0x0000 }, {   34, 0x0000 }, {   34, 0x0000 },
  {   34, 0x0000 }, {   34, 0x0000 }, {   34, 0x0000 }, {   34, 0x0080 },
  {   35, 0x0000 }, {   35, 0x0000 }, {   35, 0x0000 }, {   35, 0x0000 },
  /* 0x6000 */
  {   35, 0x0000 }, {   35, 0x0000 }, {   35, 0x0000 }, {   35, 0x0000 },
  {   35, 0x0000 }, {   35, 0x0000 }, {   35, 0x0000 }, {   35, 0x0000 },
  {   35, 0x0020 }, {   36, 0x0000 }, {   36, 0x0000 }, {   36, 0x0000 },
  {   36, 0x0000 }, {   36, 0x0000 }, {   36, 0x0000 }, {   36, 0x0000 },
  /* 0x6100 */
  {   36, 0x0000 }, {   36, 0x0000 }, {   36, 0x0001 },
};
static const Summary16 eucjp_msext_uni2indx_page65[23] = {
  /* 0x6500 */
  {   37, 0x0000 }, {   37, 0x0000 }, {   37, 0x0000 }, {   37, 0x0000 },
  {   37, 0x4000 }, {   38, 0x0000 }, {   38, 0x0000 }, {   38, 0x0000 },
  {   38, 0x0000 }, {   38, 0x0000 }, {   38, 0x0000 }, {   38, 0x0000 },
  {   38, 0x0000 }, {   38, 0x0000 }, {   38, 0x0000 }, {   38, 0x0000 },
  /* 0x6600 */
  {   38, 0x0000 }, {   38, 0x0000 }, {   38, 0x0000 }, {   38, 0x0800 },
  {   39, 0x0000 }, {   39, 0x0000 }, {   39, 0x0020 },
};
static const Summary16 eucjp_msext_uni2indx_page68[1] = {
  /* 0x6800 */
  {   40, 0x0002 },
};
static const Summary16 eucjp_msext_uni2indx_page6a[15] = {
  /* 0x6a00 */
  {   41, 0x0000 }, {   41, 0x0000 }, {   41, 0x0000 }, {   41, 0x0000 },
  {   41, 0x0000 }, {   41, 0x0000 }, {   41, 0x0800 }, {   42, 0x0000 },
  {   42, 0x0000 }, {   42, 0x0000 }, {   42, 0x0000 }, {   42, 0x0000 },
  {   42, 0x0000 }, {   42, 0x0000 }, {   42, 0x0004 },
};
static const Summary16 eucjp_msext_uni2indx_page6d[16] = {
  /* 0x6d00 */
  {   43, 0x0000 }, {   43, 0x0000 }, {   43, 0x0000 }, {   43, 0x0000 },
  {   43, 0x0000 }, {   43, 0x0000 }, {   43, 0x0000 }, {   43, 0x0000 },
  {   43, 0x0000 }, {   43, 0x0000 }, {   43, 0x0000 }, {   43, 0x0000 },
  {   43, 0x0000 }, {   43, 0x0000 }, {   43, 0x0000 }, {   43, 0x0104 },
};
static const Summary16 eucjp_msext_uni2indx_page70[12] = {
  /* 0x7000 */
  {   45, 0x0000 }, {   45, 0x0000 }, {   45, 0x0100 }, {   46, 0x0000 },
  {   46, 0x0000 }, {   46, 0x0000 }, {   46, 0x0000 }, {   46, 0x0000 },
  {   46, 0x0000 }, {   46, 0x0000 }, {   46, 0x0000 }, {   46, 0x0800 },
};
static const Summary16 eucjp_msext_uni2indx_page75[26] = {
  /* 0x7500 */
  {   47, 0x0002 }, {   48, 0x0000 }, {   48, 0x0000 }, {   48, 0x0000 },
  {   48, 0x0000 }, {   48, 0x0000 }, {   48, 0x0000 }, {   48, 0x0000 },
  {   48, 0x0000 }, {   48, 0x0000 }, {   48, 0x0000 }, {   48, 0x0000 },
  {   48, 0x0000 }, {   48, 0x0000 }, {   48, 0x0000 }, {   48, 0x0000 },
  /* 0x7600 */
  {   48, 0x0000 }, {   48, 0x0000 }, {   48, 0x0000 }, {   48, 0x0000 },
  {   48, 0x0000 }, {   48, 0x0000 }, {   48, 0x0000 }, {   48, 0x0000 },
  {   48, 0x0004 }, {   49, 0x4000 },
};
static const Summary16 eucjp_msext_uni2indx_page79[31] = {
  /* 0x7900 */
  {   50, 0x0000 }, {   50, 0x0000 }, {   50, 0x0000 }, {   50, 0x0001 },
  {   51, 0x0000 }, {   51, 0x0000 }, {   51, 0x0000 }, {   51, 0x0000 },
  {   51, 0x0000 }, {   51, 0x0000 }, {   51, 0x0000 }, {   51, 0x0000 },
  {   51, 0x0000 }, {   51, 0x0000 }, {   51, 0x0000 }, {   51, 0x0000 },
  /* 0x7a00 */
  {   51, 0x0000 }, {   51, 0x0000 }, {   51, 0x0000 }, {   51, 0x0000 },
  {   51, 0x0000 }, {   51, 0x0000 }, {   51, 0x0000 }, {   51, 0x0000 },
  {   51, 0x0000 }, {   51, 0x0000 }, {   51, 0x0000 }, {   51, 0x0000 },
  {   51, 0x0000 }, {   51, 0x0000 }, {   51, 0x0080 },
};
static const Summary16 eucjp_msext_uni2indx_page7d[14] = {
  /* 0x7d00 */
  {   52, 0x0000 }, {   52, 0x0000 }, {   52, 0x0000 }, {   52, 0x0000 },
  {   52, 0x0000 }, {   52, 0x0000 }, {   52, 0x0000 }, {   52, 0x0000 },
  {   52, 0x0000 }, {   52, 0x0000 }, {   52, 0x0001 }, {   53, 0x0000 },
  {   53, 0x0000 }, {   53, 0x0040 },
};
static const Summary16 eucjp_msext_uni2indx_page83[7] = {
  /* 0x8300 */
  {   54, 0x0000 }, {   54, 0x0000 }, {   54, 0x0000 }, {   54, 0x0000 },
  {   54, 0x0000 }, {   54, 0x0000 }, {   54, 0x0004 },
};
static const Summary16 eucjp_msext_uni2indx_page85[12] = {
  /* 0x8500 */
  {   55, 0x0000 }, {   55, 0x0000 }, {   55, 0x0000 }, {   55, 0x0000 },
  {   55, 0x0000 }, {   55, 0x0000 }, {   55, 0x0000 }, {   55, 0x0000 },
  {   55, 0x0000 }, {   55, 0x0000 }, {   55, 0x0000 }, {   55, 0x0001 },
};
static const Summary16 eucjp_msext_uni2indx_page88[1] = {
  /* 0x8800 */
  {   56, 0x0080 },
};
static const Summary16 eucjp_msext_uni2indx_page8b[40] = {
  /* 0x8b00 */
  {   57, 0x0000 }, {   57, 0x0000 }, {   57, 0x0000 }, {   57, 0x0000 },
  {   57, 0x0000 }, {   57, 0x0000 }, {   57, 0x0000 }, {   57, 0x8000 },
  {   58, 0x0000 }, {   58, 0x0000 }, {   58, 0x0000 }, {   58, 0x0000 },
  {   58, 0x0000 }, {   58, 0x0000 }, {   58, 0x0000 }, {   58, 0x0000 },
  /* 0x8c00 */
  {   58, 0x0000 }, {   58, 0x0000 }, {   58, 0x0000 }, {   58, 0x0000 },
  {   58, 0x0000 }, {   58, 0x0000 }, {   58, 0x0000 }, {   58, 0x0000 },
  {   58, 0x0000 }, {   58, 0x0000 }, {   58, 0x0000 }, {   58, 0x0000 },
  {   58, 0x0000 }, {   58, 0x0000 }, {   58, 0x0000 }, {   58, 0x0010 },
  /* 0x8d00 */
  {   59, 0x0000 }, {   59, 0x0000 }, {   59, 0x0000 }, {   59, 0x0000 },
  {   59, 0x0000 }, {   59, 0x0000 }, {   59, 0x0000 }, {   59, 0x0040 },
};
static const Summary16 eucjp_msext_uni2indx_page90[18] = {
  /* 0x9000 */
  {   60, 0x0000 }, {   60, 0x0000 }, {   60, 0x0000 }, {   60, 0x0000 },
  {   60, 0x0000 }, {   60, 0x0000 }, {   60, 0x0000 }, {   60, 0x0000 },
  {   60, 0x0000 }, {   60, 0x0000 }, {   60, 0x0000 }, {   60, 0x0000 },
  {   60, 0x0000 }, {   60, 0x4000 }, {   61, 0x0000 }, {   61, 0x0000 },
  /* 0x9100 */
  {   61, 0x0000 }, {   61, 0x0020 },
};
static const Summary16 eucjp_msext_uni2indx_page95[10] = {
  /* 0x9500 */
  {   62, 0x0000 }, {   62, 0x0000 }, {   62, 0x0000 }, {   62, 0x0000 },
  {   62, 0x0000 }, {   62, 0x0000 }, {   62, 0x0000 }, {   62, 0x0000 },
  {   62, 0x0000 }, {   62, 0x0004 },
};
static const Summary16 eucjp_msext_uni2indx_page97[6] = {
  /* 0x9700 */
  {   63, 0x0000 }, {   63, 0x0000 }, {   63, 0x0000 }, {   63, 0x0800 },
  {   64, 0x2000 }, {   65, 0x0002 },
};
static const Summary16 eucjp_msext_uni2indx_page99[40] = {
  /* 0x9900 */
  {   66, 0x0000 }, {   66, 0x0000 }, {   66, 0x0000 }, {   66, 0x0000 },
  {   66, 0x0000 }, {   66, 0x0000 }, {   66, 0x0000 }, {   66, 0x0000 },
  {   66, 0x0000 }, {   66, 0x4000 }, {   67, 0x0000 }, {   67, 0x0000 },
  {   67, 0x0000 }, {   67, 0x0000 }, {   67, 0x0000 }, {   67, 0x0000 },
  /* 0x9a00 */
  {   67, 0x0000 }, {   67, 0x0000 }, {   67, 0x0000 }, {   67, 0x0000 },
  {   67, 0x0000 }, {   67, 0x0000 }, {   67, 0x0000 }, {   67, 0x0000 },
  {   67, 0x0000 }, {   67, 0x0000 }, {   67, 0x0000 }, {   67, 0x0000 },
  {   67, 0x0000 }, {   67, 0x0200 }, {   68, 0x0000 }, {   68, 0x0000 },
  /* 0x9b00 */
  {   68, 0x0000 }, {   68, 0x0000 }, {   68, 0x0000 }, {   68, 0x0000 },
  {   68, 0x0000 }, {   68, 0x0000 }, {   68, 0x0000 }, {   68, 0x0004 },
};
static const Summary16 eucjp_msext_uni2indx_page9e[14] = {
  /* 0x9e00 */
  {   69, 0x0000 }, {   69, 0x0000 }, {   69, 0x0000 }, {   69, 0x0000 },
  {   69, 0x0000 }, {   69, 0x0000 }, {   69, 0x0000 }, {   69, 0x0000 },
  {   69, 0x0000 }, {   69, 0x0000 }, {   69, 0x0000 }, {   69, 0x0000 },
  {   69, 0x0000 }, {   69, 0x0002 },
};
static const Summary16 eucjp_msext_uni2indx_pagef9[19] = {
  /* 0xf900 */
  {   70, 0x0000 }, {   70, 0x0000 }, {   70, 0x0200 }, {   71, 0x0000 },
  {   71, 0x0000 }, {   71, 0x0000 }, {   71, 0x0000 }, {   71, 0x0000 },
  {   71, 0x0000 }, {   71, 0x0000 }, {   71, 0x0000 }, {   71, 0x0000 },
  {   71, 0x0000 }, {   71, 0x1000 }, {   72, 0x0000 }, {   72, 0x0000 },
  /* 0xfa00 */
  {   72, 0xc000 }, {   74, 0xffff }, {   90, 0x3fff },
};
static const Summary16 eucjp_msext_uni2indx_pageff[1] = {
  /* 0xff00 */
  {  104, 0x0084 },
};

static int
eucjp_msext_wctomb (conv_t conv, unsigned char *r, ucs4_t wc, int n)
{
  if (n >= 2) {
    const Summary16 *summary = NULL;
    if (wc >= 0x2100 && wc < 0x2180)
      summary = &eucjp_msext_uni2indx_page21[(wc>>4)-0x210];
    else if (wc >= 0x3200 && wc < 0x3240)
      summary = &eucjp_msext_uni2indx_page32[(wc>>4)-0x320];
    else if (wc >= 0x4e00 && wc < 0x4f00)
      summary = &eucjp_msext_uni2indx_page4e[(wc>>4)-0x4e0];
    else if (wc >= 0x5000 && wc < 0x51f0)
      summary = &eucjp_msext_uni2indx_page50[(wc>>4)-0x500];
    else if (wc >= 0x5300 && wc < 0x5490)
      summary = &eucjp_msext_uni2indx_page53[(wc>>4)-0x530];
    else if (wc >= 0x5700 && wc < 0x58a0)
      summary = &eucjp_msext_uni2indx_page57[(wc>>4)-0x570];
    else if (wc >= 0x5b00 && wc < 0x5d60)
      summary = &eucjp_msext_uni2indx_page5b[(wc>>4)-0x5b0];
    else if (wc >= 0x5f00 && wc < 0x6130)
      summary = &eucjp_msext_uni2indx_page5f[(wc>>4)-0x5f0];
    else if (wc >= 0x6500 && wc < 0x6670)
      summary = &eucjp_msext_uni2indx_page65[(wc>>4)-0x650];
    else if (wc >= 0x6800 && wc < 0x6810)
      summary = &eucjp_msext_uni2indx_page68[(wc>>4)-0x680];
    else if (wc >= 0x6a00 && wc < 0x6af0)
      summary = &eucjp_msext_uni2indx_page6a[(wc>>4)-0x6a0];
    else if (wc >= 0x6d00 && wc < 0x6e00)
      summary = &eucjp_msext_uni2indx_page6d[(wc>>4)-0x6d0];
    else if (wc >= 0x7000 && wc < 0x70c0)
      summary = &eucjp_msext_uni2indx_page70[(wc>>4)-0x700];
    else if (wc >= 0x7500 && wc < 0x76a0)
      summary = &eucjp_msext_uni2indx_page75[(wc>>4)-0x750];
    else if (wc >= 0x7900 && wc < 0x7af0)
      summary = &eucjp_msext_uni2indx_page79[(wc>>4)-0x790];
    else if (wc >= 0x7d00 && wc < 0x7de0)
      summary = &eucjp_msext_uni2indx_page7d[(wc>>4)-0x7d0];
    else if (wc >= 0x8300 && wc < 0x8370)
      summary = &eucjp_msext_uni2indx_page83[(wc>>4)-0x830];
    else if (wc >= 0x8500 && wc < 0x85c0)
      summary = &eucjp_msext_uni2indx_page85[(wc>>4)-0x850];
    else if (wc >= 0x8800 && wc < 0x8810)
      summary = &eucjp_msext_uni2indx_page88[(wc>>4)-0x880];
    else if (wc >= 0x8b00 && wc < 0x8d80)
      summary = &eucjp_msext_uni2indx_page8b[(wc>>4)-0x8b0];
    else if (wc >= 0x9000 && wc < 0x9120)
      summary = &eucjp_msext_uni2indx_page90[(wc>>4)-0x900];
    else if (wc >= 0x9500 && wc < 0x95a0)
      summary = &eucjp_msext_uni2indx_page95[(wc>>4)-0x950];
    else if (wc >= 0x9700 && wc < 0x9760)
      summary = &eucjp_msext_uni2indx_page97[(wc>>4)-0x970];
    else if (wc >= 0x9900 && wc < 0x9b80)
      summary = &eucjp_msext_uni2indx_page99[(wc>>4)-0x990];
    else if (wc >= 0x9e00 && wc < 0x9ee0)
      summary = &eucjp_msext_uni2indx_page9e[(wc>>4)-0x9e0];
    else if (wc >= 0xf900 && wc < 0xfa30)
      summary = &eucjp_msext_uni2indx_pagef9[(wc>>4)-0xf90];
    else if (wc >= 0xff00 && wc < 0xff10)
      summary = &eucjp_msext_uni2indx_pageff[(wc>>4)-0xff0];
    if (summary) {
      unsigned short used = summary->used;
      unsigned int i = wc & 0x0f;
      if (used & ((unsigned short) 1 << i)) {
        unsigned short c;
        /* Keep in `used' only the bits 0..i-1. */
        used &= ((unsigned short) 1 << i) - 1;
        /* Add `summary->indx' and the number of bits set in `used'. */
        used = (used & 0x5555) + ((used & 0xaaaa) >> 1);
        used = (used & 0x3333) + ((used & 0xcccc) >> 2);
        used = (used & 0x0f0f) + ((used & 0xf0f0) >> 4);
        used = (used & 0x00ff) + (used >> 8);
        c = eucjp_msext_2charset[summary->indx + used];
        r[0] = (c >> 8); r[1] = (c & 0xff);
        return 2;
      }
    }
    return RET_ILUNI;
  }
  return RET_TOOSMALL;
}
