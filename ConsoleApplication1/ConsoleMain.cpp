// ConsoleMain.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "constants.h"
#include "ConsoleMain.h"

using namespace std;


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

char* hi = "Comples Magic Application 2017 v";

int main()
{
	printHello(hi, version);
	
	MP cn;
	
	cn.toString();

	MP cn2(4,2);

	cn2.toString();

	MP answer = cn + cn2;

	answer.toString();

	cout << "Press any key and Enter to exit";
	cin >> sChar;

    return 0;
}

void printHello(const char* string, int version) {
	char ver = version;
	cout << string << ver << endl;
}
