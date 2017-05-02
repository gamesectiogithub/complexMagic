#pragma once

#include "stdafx.h"
#include <cstring>
#include <vector>
#include "constants.h"
/*
#include <fstream>
#include <iomanip>
*/

/* mystic particles have types
*/
enum MPType { REAL, COMPLEX, MULTYR, MULTYC }; 

#define mpn short
#define MP magicParticle

using namespace std;


struct magicParticle {

	MPType type;
	char order; // use like a number
	mpn base;
	vector<mpn> imaginaries;
	char* natures;

	MP(void) {

		base = 0;
		imaginaries.push_back(0);
		natures = new char;
		natures[0] = 'i';
		natures[1] = '\0';
		setAutoOrder();
		setAutoType();
	};

	MP(mpn mpBase, mpn mpIm) : base(mpBase), order(1)
	{
		imaginaries.push_back(mpIm);
		natures = new char;
		natures[0] = 'i';
		natures[1] = '\0';
	}

	MP(mpn mpBase, mpn mpIm, char mpImType) : base(mpBase), order(1)
	{
		imaginaries.push_back(mpIm);
		natures = new char;
		natures[0] = mpImType;
		natures[1] = '\0';
	}

	MP(mpn mpBase, vector<mpn> mpImaginaries, char* mpNatures) : base(mpBase)
	{
		imaginaries = mpImaginaries;
		natures = mpNatures;
		setAutoOrder();
		setAutoType();
	}


	/*print Mystic Number in console
	*/
	void toString() {

		// base|imag[n]|nature[n]...
		cout << base;

		for (unsigned i = 0; i < imaginaries.size(); i++)
		{
			imaginaries[i] >= 0 ? cout << '+' << imaginaries[i] : cout << imaginaries[i];
			cout << natures[i];
		}

		cout << endl;
	};

	void setAutoType() {
		type = COMPLEX;
	}

	void setAutoOrder() {
		order = (char)imaginaries.size();
	}


	void setBase(mpn bs) {
		base = bs;
	}

	void addComplexPart(mpn val, char imtype) {
		imaginaries.push_back(val);
		natures[imaginaries.size() - 1] = imtype;
		natures[imaginaries.size()] = '\0';
	}


	/*Use right before setNatures. NOT SAFE METHOD

	void setImaginaries(unsigned total, mpn im, ...) {
	imaginaries.erase(imaginaries.begin(), imaginaries.end());
	mpn *p = &im;
	while (total--!=0)
	{
	imaginaries.push_back(*p);
	p++
	}
	}*/

	/*Use right after setImaginaries. NOT SAFE METHOD

	void setNatures(char* ch) {
	natures = "";
	natures = ch;
	}
	*/

	/*Operator '+' overriding for MP
	*/
	MP MP::operator+(MP& second) {

		mpn mBase;
		mBase = base + second.base;

		vector<mpn> mImaginaries;

		char* mNatures = natures;

		for (unsigned i = 0; i < imaginaries.size(); i++)
		{
			for (unsigned j = 0; j < second.imaginaries.size(); j++)
			{
				// sum for parts with the same nature
				if (natures[i] == second.natures[j]) {
					mImaginaries.push_back(imaginaries[i] + second.imaginaries[j]);
					break;
				}
				else if (j + 1 == second.imaginaries.size()) {
					// this [i] part of first has unique nature, must add it to answer
					mImaginaries.push_back(imaginaries[i]);
					mNatures[mImaginaries.size() - 1] = natures[i];
				}
			}
		}

		for (unsigned i = 0; i < second.imaginaries.size(); i++)
		{
			for (unsigned j = 0; j < imaginaries.size(); j++)
			{
				if (second.natures[i] == natures[j]) {
					break;
				}
				else if (j + 1 == imaginaries.size()) {
					// this [i] part of second has unique nature, must add it to answer
					mImaginaries.push_back(second.imaginaries[i]);
					mNatures[mImaginaries.size() - 1] = second.natures[i];
				}
			}
		}

		mNatures[mImaginaries.size()] = '\0'; // for correct char* array

		return MP(mBase, mImaginaries, mNatures);
	}

	/*Operator '+' overriding for #mpn
	*/
	MP MP::operator+(mpn& second) {
		return MP(base + second, imaginaries, natures);
	}

	/*Operator '-' overriding for #mpn
	*/
	MP MP::operator-(mpn& second) {
		return MP(base - second, imaginaries, natures);
	}

	/*Operator '-' overriding for MP
	*/
	MP MP::operator-(MP& second) {

		mpn mBase;
		mBase = base - second.base;

		vector<mpn> mImaginaries;

		char* mNatures = natures;

		for (unsigned i = 0; i < imaginaries.size(); i++)
		{
			for (unsigned j = 0; j < second.imaginaries.size(); j++)
			{
				// for parts with the same nature
				if (natures[i] == second.natures[j]) {
					mImaginaries.push_back(imaginaries[i] - second.imaginaries[j]);
					break;
				}
				else if (j + 1 == second.imaginaries.size()) {
					// this [i] part of first has unique nature, must add it to answer
					mImaginaries.push_back(imaginaries[i]);
					mNatures[mImaginaries.size() - 1] = natures[i];
				}
			}
		}

		for (unsigned i = 0; i < second.imaginaries.size(); i++)
		{
			for (unsigned j = 0; j < imaginaries.size(); j++)
			{
				if (second.natures[i] == natures[j]) {
					break;
				}
				else if (j + 1 == imaginaries.size()) {
					// this [i] part of second has unique nature, must add it to answer
					mImaginaries.push_back(second.imaginaries[i] * (-1));
					mNatures[mImaginaries.size() - 1] = second.natures[i];
				}
			}
		}

		mNatures[mImaginaries.size()] = '\0'; // for correct char* array

		return MP(mBase, mImaginaries, mNatures);
	}

};

/*Operator pre '++' overriding for #mpn*/
MP& operator ++ (MP& f);
/*Operator pre '--' overriding for #mpn*/
MP& operator -- (MP& f);
/*Operator post '++' overriding for #mpn*/
MP operator ++ (MP& f, int);
/*Operator post '--' overriding for #mpn*/
MP& operator -- (MP& f, int);
/*Operator << for std::cout*/
ostream& operator << (ostream& os, const MP& f);
