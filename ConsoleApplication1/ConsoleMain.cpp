// ConsoleMain.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

signed char sChar = 45; // 1 byte -128 +127
unsigned char version = '1'; // 1 byte 0+255
char* hi = "Comples Magic Application 2017 v";


int main(int argc, char* argv[])
{
	printHello(hi, version);




	/*
	runMagicParticlesTest();

	printChars();
	*/

	/* ending*/
	cout << "Press any key and Enter to exit";
	cin >> sChar;

	
    return 0;
}

void printHello(const char* string, int version) {
	char ver = version;
	cout << string << ver << endl;
}

void printChars()
{

	for (int i = 0; i <= 150; i++) {

		if (i == 13) i = 14;
		cout << i << ' ' << (char)i;
		cout << "  ";

		if (i % 10 == 0) cout << endl;
	}

	cout << endl;

}

void runMagicParticlesTest()
{

	MP cn;

	cn.toString();

	MP cn2(4, 2);

	cn2.toString();

	MP answer = cn + cn2;

	answer.toString();
	cout << "plus rr = 7: " << endl;
	mpn rr = 7;
	answer = answer + rr;
	answer.toString();
	cout << "plus 5: " << endl;
	answer = answer + 5;
	answer.toString();

	cout << "Another " << endl;

	MP cn6(4, 600, 'y');
	cn6.setBase(40);
	cn6.addComplexPart(3, 'p');
	cn6.addComplexPart(7, 'k');
	cn6.addComplexPart(9, 'n');
	cn6.toString();

	MP cn7(8, -350, 'y');
	cn7.addComplexPart(-2, 'p');
	cn7.addComplexPart(-2, 'k');
	cn7.addComplexPart(-3, 'm');
	cn7.addComplexPart(-3, 't');
	cn7.toString();


	answer = cn6 + cn7;
	cout << "their SUM:" << endl;
	answer.toString();

	answer = cn6 - cn7;
	cout << "their DIF:" << endl;
	answer.toString();

	cout << "And now we will renaturaize it: k ->> t " << endl;
	answer.reNaturization('k', 't');
	answer.toString();
	cout << "And now we will renaturaize it: p ->> t " << endl;
	answer.reNaturization('p', 't');
	answer.toString();
	cout << endl;
	cout << endl;
}

