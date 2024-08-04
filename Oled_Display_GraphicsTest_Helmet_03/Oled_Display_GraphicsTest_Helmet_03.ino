/*

  GraphicsTest.ino
  Arduino _ Peter Holweg 2022
    

*/

#include <U8g2lib.h>
#include <Wire.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE); // constructor for OLED 128x64 _Full page mode

  /*
  Fontname: Fixedsys
  Copyright: Copyright 1987, Microsoft Corporation
  Glyphs: 10/224
  BBX Build Mode: 0
*/
const uint8_t Fixedsys[182] U8G2_FONT_SECTION("Fixedsys") = 
  "\12\0\3\3\4\4\3\1\5\10\14\1\0\14\374\15\375\0\0\0\0\0\231\60\22\310\255E\263\214\212,"
  "\22\212\204H,Ml$\0\61\10\304\256u\30\351\37\62\16\310\255E\263\214\306\322\341^\17\7\1\63"
  "\21\310\255E\263\214\306R\341\224<.Ml$\0\64\17\310\255#\26\351\27\231\344p\220\212\265\0\65"
  "\17\310\255\361@\26\233\316cqib#\1\66\21\310\255E\263\214\312*\243\313\250X\232\330H\0\67"
  "\12\307\256\361*\324\252o\0\70\23\310\255E\263\214\212\22\221\214f\31\25K\23\33\11\0\71\22\310\255"
  "E\263\214\212\245\311i\42\26\227&\66\22\0\0\0\0\4\377\377\0";

  // https://stncrn.github.io/u8g2-unifont-helper/

  int hMeter = 64;                      // horizontal center for needle animation = 128/2
  int vMeter = 64;                      // vertical center for needle animation.
  int Radius = 64;                      // length of needle,radius.
  

////////////////////////////////////////////////////////////////////////

static const unsigned char Acontrol[] U8X8_PROGMEM = {
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf,
   0xff, 0x7f, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0x03, 0xff, 0x3f, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 0xff, 0x1f, 0xf0, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03,
   0xfe, 0x3f, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xfc, 0xf3, 0x03, 0x3f, 0x1f, 0xf0, 0xf9, 0xe7, 0x4f, 0x92, 0x24,
   0x49, 0x92, 0x24, 0xff, 0x7f, 0xf0, 0xc1, 0x03, 0x0f, 0x1c, 0xf0, 0xe0,
   0x81, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x3f, 0xe0, 0x80, 0x03,
   0x0e, 0x3c, 0x70, 0xc0, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc,
   0x3f, 0xe0, 0x80, 0x03, 0x0f, 0x1c, 0x70, 0xc0, 0x01, 0x07, 0x00, 0x00,
   0x00, 0x00, 0x00, 0xfc, 0x7f, 0xe0, 0xc0, 0x03, 0x06, 0x3c, 0x70, 0xe0,
   0x81, 0x5f, 0xdb, 0xb6, 0x6d, 0xdb, 0xd6, 0xff, 0x3f, 0xe0, 0x80, 0x03,
   0x0f, 0x1c, 0x70, 0xc0, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0x3f, 0xe0, 0x80, 0x03, 0x07, 0x3c, 0x70, 0xc0, 0x81, 0xbf, 0xdb, 0xb6,
   0x6d, 0xdb, 0xae, 0xff, 0x3f, 0xe0, 0x80, 0x03, 0x0e, 0x1c, 0x70, 0xc0,
   0x01, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x7f, 0xe0, 0xc0, 0x03,
   0x0f, 0x3c, 0x70, 0xe0, 0x81, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc,
   0x3f, 0xe0, 0x80, 0x03, 0x0f, 0x1c, 0x70, 0xc0, 0x01, 0x03, 0x00, 0x00,
   0x00, 0x00, 0x00, 0xfc, 0x3f, 0xe0, 0x80, 0x03, 0x06, 0x3c, 0x70, 0xe0,
   0x81, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x80, 0xfe, 0x3f, 0xe0, 0x80, 0x03,
   0x0f, 0x1c, 0x70, 0xc0, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0x7f, 0xe0, 0xc0, 0x03, 0x07, 0x3c, 0x70, 0xc0, 0x81, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0x3f, 0xe0, 0x80, 0x03, 0x0e, 0x1c, 0x70, 0xc0,
   0x01, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x3f, 0xe0, 0x80, 0x03,
   0x0f, 0x3c, 0x70, 0xe0, 0x81, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc,
   0x3f, 0xe0, 0x80, 0x03, 0x0f, 0x1c, 0x70, 0xc0, 0x01, 0x03, 0x00, 0x00,
   0x00, 0x00, 0x00, 0xfc, 0x7f, 0xe0, 0xc0, 0x03, 0x06, 0x3c, 0x70, 0xc0,
   0x81, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x3f, 0xe0, 0x80, 0x03,
   0x0f, 0x1c, 0x70, 0xc0, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0x3f, 0xe0, 0x80, 0x03, 0x07, 0x3c, 0x70, 0xe0, 0x81, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0x3f, 0xe0, 0x80, 0x03, 0x0e, 0x1c, 0x70, 0xc0,
   0x01, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x7f, 0xe0, 0xc0, 0x03,
   0x07, 0x3c, 0x78, 0xc0, 0x81, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc,
   0x3f, 0xe0, 0x80, 0xcf, 0x0f, 0xfc, 0x78, 0xc0, 0x01, 0x03, 0x00, 0x00,
   0x00, 0x00, 0x00, 0xfc, 0x3f, 0xe0, 0x80, 0xff, 0x07, 0xfc, 0x7f, 0xe0,
   0x81, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x3f, 0xe0, 0x80, 0xff,
   0x0f, 0xf8, 0x7f, 0xc0, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0x7f, 0xf0, 0xc1, 0x87, 0x0f, 0x7c, 0xfc, 0xe0, 0x83, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xe3, 0x07, 0x3f, 0x3f, 0xf0, 0xf3,
   0xc7, 0x1f, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03,
   0xff, 0x1f, 0xf0, 0xff, 0xff, 0x0f, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0x03, 0xff, 0x1f, 0xf0, 0xff, 0xff, 0x0f, 0xf8, 0xff,
   0xfe, 0xff, 0xff, 0xff, 0xff, 0x03, 0x83, 0x03, 0x00, 0x3f, 0xf0, 0x0f,
   0xf0, 0x03, 0xe0, 0x03, 0xf0, 0x83, 0x01, 0xff, 0xff, 0x00, 0x80, 0x03,
   0x00, 0x1c, 0xf0, 0x03, 0x80, 0x01, 0xc0, 0x00, 0xc0, 0x03, 0x00, 0xfe,
   0x7f, 0x00, 0x00, 0x03, 0x00, 0x3c, 0xf0, 0x01, 0x00, 0x03, 0xe0, 0x00,
   0x80, 0x03, 0x00, 0xfc, 0x3f, 0xe0, 0x81, 0x03, 0x0e, 0x38, 0xf0, 0xc0,
   0x03, 0x0f, 0x7c, 0xe0, 0x01, 0x03, 0x06, 0xfc, 0x3f, 0xe0, 0x01, 0x03,
   0x1f, 0x10, 0x70, 0x00, 0x00, 0x0e, 0x3c, 0xe0, 0x03, 0x03, 0x0f, 0xfc,
   0x3f, 0xf0, 0x81, 0x03, 0x1f, 0x38, 0xf0, 0x00, 0x00, 0x0e, 0x7c, 0xe0,
   0x03, 0x03, 0x0f, 0xfc, 0x3f, 0xe0, 0x81, 0x03, 0x1f, 0x18, 0xf0, 0x80,
   0xc5, 0x0f, 0x3c, 0xe0, 0x01, 0x03, 0x0f, 0xfc, 0x3f, 0xe0, 0x01, 0x03,
   0x0e, 0x38, 0xe0, 0x80, 0x87, 0x0f, 0x78, 0xc0, 0x81, 0x03, 0x0e, 0xfc,
   0x7f, 0x00, 0x80, 0x03, 0x00, 0x18, 0x80, 0x01, 0x00, 0x0f, 0xe0, 0x00,
   0x80, 0x03, 0x0f, 0xfc, 0xff, 0x00, 0x80, 0x03, 0x00, 0x3e, 0x80, 0x03,
   0x80, 0x0f, 0xc0, 0x01, 0xc0, 0x03, 0x0f, 0xfc, 0xff, 0x03, 0xc3, 0x87,
   0x81, 0xff, 0xc0, 0x0f, 0xf0, 0x3f, 0xf0, 0x07, 0xf8, 0x87, 0x1f, 0xfe,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xff, 0xff, 0x7f, 0xf8,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0xff, 0xff, 0xf8,
   0xff, 0xff, 0x7f, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0x1f, 0xff, 0xff, 0xf9, 0xff, 0xff, 0x3f, 0xfe, 0xff, 0xff, 0xff, 0xff,
   0xff, 0x1f, 0x18, 0x0c, 0x08, 0x02, 0xc1, 0xf8, 0x81, 0x88, 0x00, 0x00,
   0x0e, 0x06, 0xff, 0xff, 0xff, 0x1f, 0x8b, 0x88, 0x18, 0x03, 0x88, 0xf8,
   0x78, 0x8c, 0x00, 0x7e, 0xc4, 0x20, 0xfe, 0xff, 0xff, 0x8f, 0xc7, 0x88,
   0x10, 0xe3, 0x98, 0xf8, 0xe0, 0x88, 0x38, 0x0e, 0xc4, 0x63, 0xfc, 0xff,
   0xff, 0x9f, 0xcf, 0x88, 0x99, 0xe3, 0x18, 0xf9, 0x81, 0x88, 0x38, 0x06,
   0xc4, 0x03, 0xfc, 0xff, 0xff, 0x8f, 0xc7, 0x88, 0x11, 0xe3, 0x98, 0xf8,
   0x03, 0x88, 0x38, 0x46, 0xc4, 0xe3, 0xff, 0xff, 0xff, 0x1f, 0x8b, 0x88,
   0x18, 0xe3, 0x88, 0xf8, 0x8f, 0x88, 0x38, 0x46, 0xc4, 0xe4, 0xfe, 0xff,
   0xff, 0x1f, 0x18, 0x8c, 0x19, 0xe2, 0xc1, 0xf8, 0xc0, 0x80, 0x38, 0x0e,
   0x0c, 0x04, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff };

///////////////////////////////////////////////////////////////////////////////////
///// de BMP in GIMP geladen, en geexporteerd naar xbm, dan openen met notepad++///
///////////////////////////////////////////////////////////////////////////////////

static const unsigned char back[] U8X8_PROGMEM = {
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xfe, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f,
   0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0x7f, 0xbe, 0x00, 0x00, 0x7d, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x02, 0x00, 0x00, 0x40, 0xfe, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x00, 0x00,
   0x00, 0x00, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0x07, 0xc0, 0x7f, 0xfe, 0x03, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0xfc, 0x7f, 0xff, 0x3f, 0x00, 0xfe,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0xe0, 0xfc, 0xff,
   0xff, 0x3f, 0x07, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f,
   0x0e, 0xf8, 0xfe, 0xff, 0xff, 0xff, 0x3f, 0x40, 0xfe, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xe0, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0x07, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f,
   0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0xf8, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0x0f, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f,
   0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0xfb, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xcf, 0xc1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc1,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x83, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0x0f, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xf8, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0x1f, 0xfc, 0xff, 0xff, 0xff, 0xff, 0x1b, 0xfc,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xc8, 0xff, 0xff,
   0xff, 0xff, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0x87, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xe1, 0xff, 0xff, 0xff, 0xff, 0xc3, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x83, 0xff, 0xff,
   0xff, 0xff, 0x81, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0x89, 0xff, 0xff, 0xff, 0xff, 0xb0, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0x1b, 0xfe, 0xff, 0xff, 0x7f, 0xf8, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0xfe, 0xff,
   0xff, 0x3f, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0x7f, 0xfc, 0xff, 0xff, 0x1f, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xf8, 0xff, 0xff, 0x1f, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff,
   0xff, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xe1, 0xff, 0xff, 0xc7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc3, 0xff, 0xff, 0xc3, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x47, 0xfe,
   0x7f, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0x0f, 0xfe, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0xff, 0xff, 0xf1, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc7, 0xff,
   0xff, 0xe7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0xe0, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00,
   0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0x3f, 0x00, 0x00, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x00, 0x00, 0xf0, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00,
   0x00, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0x03, 0x00, 0x00, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00,
   0x00, 0x00, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0x7f, 0x00, 0x00, 0x00, 0x00, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x00, 0x00,
   0x00, 0x00, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0x1f, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xff,
   0xff, 0xff, 0xff, 0xff };
/////////////////


void setup(void) {
  
  u8g2.begin();
  u8g2.setBusClock(200000);// Speed up i2C bus.
  
  u8g2.clearBuffer();
  u8g2.setDrawColor(0); // Black
  u8g2.drawXBMP(0, 0, 128, 64, Acontrol);            // display " Ableton Control Surface" LOGO.
  u8g2.sendBuffer();                                 // Transfer internal OLED memory to the OLED display
  delay(3000);                                       // show the LOGO for 3 seconds.
}


void loop(void) {
  // programm loop
    
  int sensorValue = analogRead(A0);                  // read the input on analog pin 0:
  int SensorH = map(sensorValue, 0, 1023, 150, 30);  // horizontal needle deflection in degrees.
  int SensorM = map(sensorValue, 0, 1023, 0, 127);   // CC numbers MIDI 0-127
  int Xv = cos(SensorH*PI/180)*Radius;               // Calculate X Value for needle.
  int Yv = sin(SensorH*PI/180)*Radius;               // Calculate Y Value for needle.
  int X1 = Xv + hMeter;                              // add half of OLED width to value.
  int Y1 = vMeter - Yv;                              // subtract value from height OLED.
  
  u8g2.clearBuffer();                     // clear the internal memory
  //u8g2.setFont(u8g2_font_osb29_tr);     // 59% 
  //u8g2.setFont(u8g2_font_profont29_mn); // 45%
  //u8g2.setFont(u8g2_font_inb38_mn);     // 46%
  u8g2.setFont(Fixedsys);                 // 44% home made font containing only 0-9

  u8g2.setDrawColor(0); // Black
  u8g2.drawXBMP(0, 0, 128, 64, back);     // display "Backdrop" in memory.
  u8g2.setDrawColor(1);
  u8g2.setCursor(4,62);                   // Position the cursor.
  u8g2.print(SensorM);                    // print the CC- MIDI value in the OLED memory.
  u8g2.drawLine(64, 64, X1, Y1);          // Draw the needle in the OLED memory.
  u8g2.sendBuffer();                      // Transfer internal OLED memory to the OLED display

}