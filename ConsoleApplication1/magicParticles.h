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

#define mpn short
#define MP magicParticle

typedef  mpn (*energonRule_func)(const mpn&,const mpn&);


using namespace std;

/*functions for renaturization of bases of energons*/
mpn reNat_linear(const mpn&, const mpn&);
mpn reNat_quadro(const mpn&, const mpn&);
mpn reNat_straight(const mpn&, const mpn&);


struct magicParticle {

public:
	enum MPType { REAL, COMPLEX, MULTYR, MULTYC };
	enum MPClass { QNT, TLE, TFU, ATM, AMS, INV, EXO };

private:
	const MPType type;
	char order; // use like a number
	mpn base;
	vector<mpn> imaginaries;
	char* natures;
	energonRule_func reNaturize;

	int* n = NULL;
	bool conserved = false; // if true -> methods must not work: stich,

public:

	MP(void) : type(COMPLEX)
	{

		base = 0;
		imaginaries.push_back(0);
		natures = new char;
		natures[0] = 'i';
		natures[1] = '\0';
		setAutoOrder();
		setAutoRule();

	};

	MP(mpn mpBase, mpn mpIm) : base(mpBase), order(1), type(COMPLEX)
	{
		imaginaries.push_back(mpIm);
		natures = new char;
		natures[0] = 'i';
		natures[1] = '\0';
		setAutoRule();
	}

	MP(mpn mpBase, mpn mpIm, char mpImType) : base(mpBase), order(1), type(COMPLEX)
	{
		imaginaries.push_back(mpIm);
		natures = new char;
		natures[0] = mpImType;
		natures[1] = '\0';
		setAutoRule();
	}

	MP(mpn mpBase, vector<mpn> mpImaginaries, char* mpNatures) : base(mpBase), type(COMPLEX)
	{
		imaginaries = mpImaginaries;
		natures = mpNatures;
		setAutoOrder();
		setAutoRule();
	}

	
	~MP ()
	{
		delete[] n;
	}
	
	
	/*function for converting energons to another nature*/
	void reNaturization(char nature_from, char nature_to, energonRule_func f = reNat_straight)
	{
		mpn base_f = 0, base_t = 0;
		
		for (unsigned i = 0; i < imaginaries.size(); i++)
		{
			if (natures[i] == nature_from)
			{
				base_f = (mpn)i;
			}
			if (natures[i] == nature_to)
			{
				base_t = (mpn)i;
			}
		}

		imaginaries[base_f] = f(imaginaries[base_f], imaginaries[base_t]);
		natures[base_f] = nature_to;
		
	}

	/*print Mystic Number with cout & endl*/
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

	void setAutoOrder() {
		order = (char)imaginaries.size();
	}

	void setAutoRule() {
		reNaturize = reNat_straight;
	}
	
	void setBase(mpn bs) {
		base = bs;
	}

	void addComplexPart(mpn val, char imtype) {
		imaginaries.push_back(val);
		natures[imaginaries.size() - 1] = imtype;
		natures[imaginaries.size()] = '\0';
	}

	const MPType getType() {
		return type;
	}

	/*stich all energons with the same nature*/
	// void stich()

	/*sort energons by order in LAM*/
	// void sortOrder()

	/*setters for energons*/

	/*getters for energons*/


	/*Operator '+' overriding for MP*/
	MP MP::operator+(const MP& second) {

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

	/*Operator '+' overriding for #mpn*/
	MP MP::operator+(const mpn& second) {
		return MP(base + second, imaginaries, natures);
	}

	/*Operator '+' overriding for int*/
	MP operator+(const int& second);

	/*Operator '-' overriding for int*/
	MP MP::operator-(const int& second) {
		return MP(base - (mpn)second, imaginaries, natures);
	}

	/*Operator '-' overriding for #mpn*/
	MP MP::operator-(const mpn& second) {
		return MP(base - second, imaginaries, natures);
	}

	/*Operator '-' overriding for MP*/
	MP MP::operator-(const MP& second) {

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

	//prototypes
	/*Operator pre '++' overriding for MP*/
	friend MP& operator ++ (MP& f);
	/*Operator pre '--' overriding for MP*/
	friend MP& operator -- (MP& f);
	/*Operator post '++' overriding for MP*/
	friend MP operator ++ (MP& f, int);
	/*Operator post '--' overriding for MP*/
	friend MP& operator -- (MP& f, int);
	/*Operator << for std::cout with MP*/
	friend ostream& operator << (ostream& os, const MP& f);

};




