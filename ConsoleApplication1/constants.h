#ifndef CONSTANTS_H_
#define CONSTANTS_H_



#define mpn short
#define DPI 6.283185 // 2*PI
#define PI 3.14159265358979323846
#define GOLDRATIO 1.6180339887498948 // (whole / big_part) = (big_part / small_part)
#define E 2,71828182845904523536

#define FLOW_STR "~"
#define WIND_STR "-"
#define FOG_STR "F"
#define STORM_STR "S"
#define TORNADO_STR "T"
#define URAGAN_STR "U"
#define CALM_STR "="
#define SWELL_STR "W"
#define ISLAND_STR "I"
#define DEFAULT_STR "X"


/*
bool bBool = true; // 1 byte

signed char sChar = 45; // 1 byte -128 +127
unsigned char version = '1'; // 1 byte 0+255

short int sInt = 32767; // 2 bytes -32768 +32767 
unsigned short uShort = 65535; // 2 bytes
long lInt = 4294967295L; // 4 bytes  -2^31 +2^31-1 
signed int iInt = 20; // depends on compile machine OS 16 bit or 32 bit
unsigned int uInt = 4294967295; // 4 bytes  -2^31 +2^31-1
unsigned long ulInt = 45UL;


float fFloat = -2e15F; // 4 bytes -3.4*10^38 +3.4*10^38
double dDouble = -2e15; // 8 bytes -3.4*10^308 +3.4*10^308
*/

char* DEFAULT_NATURES_7 = "abcdefg";
char* DEFAULT_NATURES_4 = "bcdg";
char* DEFAULT_NATURES_3 = "aef";

#endif // !CONSTANTS_H_