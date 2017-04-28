#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <cstring>
#include "stdafx.h"
#include <vector>

#define mpn short
#define MP magicParticle
#define PI 3.14159265358979323846

using namespace std;

enum MPType { REAL, COMPLEX, MULTYR, MULTYC }; // mystic particles have types

struct magicParticle {


	MPType type;
	char order; // use like a number
	mpn base;
	vector<mpn> imaginaries;
	char* natures;

	MP(void) {

		type = COMPLEX;
		order = 2;
		base = -1;
		imaginaries.push_back(1);
		imaginaries.push_back(-2);
		natures = new char;
		natures[0] = 'i';
		natures[1] = 'j';
	};

	MP( mpn mpBase, mpn mpIm) : base(mpBase), order(1)
	{
		imaginaries.push_back(mpIm);
		natures = new char;
		natures[0] = 'i';
	}

	MP(mpn mpBase, vector<mpn> mpImaginaries, char* mpNatures) : base(mpBase)
	{
		imaginaries = mpImaginaries;
		natures = mpNatures;
	}


	/*print Mystic Number in console
	*/
	void toString() {
		
		// base|imag[n]|nature[n]|imag[n]|nature[n]...
		cout << base;

		for (int i = 0; i < imaginaries.size(); i++)
		{
			imaginaries[i] > 0 ? cout << '+' << imaginaries[i] : cout << imaginaries[i];
			cout << natures[i];
		}

		cout << endl;
	};

	/*Operator '+' overriding for MP
	*/
	MP MP::operator+(MP& second) {

		// sorting 


		mpn mBase;
		mBase = base + second.base;

		vector<mpn> mImaginaries;
		vector<int> additionalImags;
		
		for (int i = 0; i < imaginaries.size(); i++)
		{
			for (int j = 0; j < second.imaginaries.size(); j++)
			{
				// sum for parts with the same nature
				if (natures[i] == second.natures[j]) {
					mImaginaries.push_back(imaginaries[i] + second.imaginaries[j]);
				}
			}
		}

		// remeber unique natures 

			


		char* mNatures = natures;

		int ii = imaginaries.size(); //count members of answer MP

		for (int addPart : additionalImags)
		{
			// add them to answer
			mImaginaries.push_back(second.imaginaries[additionalImags[addPart]]);
			mNatures[ii++] = second.natures[additionalImags[addPart]];
		}

		mNatures[ii] = '\0';

		return MP(mBase, mImaginaries, mNatures);
	}
};


#endif // !CONSTANTS_H_