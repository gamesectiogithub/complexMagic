#pragma once
#include "stdafx.h"
#include "magictheory.h"



/** LAM 
*/




/** magicParticles
*/

magicParticle::MP(void) : type(QNT)
{

	base = 0;
	imaginaries.push_back(0);
	natures = new char;
	natures[0] = 'i';
	natures[1] = '\0';
	setAutoOrder();
	setAutoRule();
	reNaturize = reNat_straight;

};

magicParticle::MP(mpn mpBase, mpn mpIm) : base(mpBase), order(1), type(QNT)
{
	reNaturize = reNat_straight;
	imaginaries.push_back(mpIm);
	natures = new char;
	natures[0] = 'i';
	natures[1] = '\0';
	setAutoRule();
}

magicParticle::MP(mpn mpBase, mpn mpIm, char mpImType) : base(mpBase), order(1), type(QNT)
{
	reNaturize = reNat_straight;
	imaginaries.push_back(mpIm);
	natures = new char;
	natures[0] = mpImType;
	natures[1] = '\0';
	setAutoRule();
}

magicParticle::MP(mpn mpBase, std::vector<mpn> mpImaginaries, char* mpNatures) : base(mpBase), type(QNT)
{
	reNaturize = reNat_straight;
	imaginaries = mpImaginaries;
	natures = mpNatures;
	setAutoOrder();
	setAutoRule();
	stich();
}

magicParticle::~MP()
{
	delete[] n;
}


void magicParticle::delEnergon(mpn id) {

	imaginaries.erase(imaginaries.begin() + id);
	char* dub = natures;
	unsigned k = 0;

	for (unsigned i = 0; i < imaginaries.size() + 2; i++)
	{
		if (i != id) {
			dub[k] = natures[i];
		}
		else {
			k--;
		}
		++k;
	}

	natures = "";
	natures = dub;
}

void magicParticle::reNaturization(const char nature_from, const char nature_to, energonRule_func f)
{

	// TODO: delete goto's , method reNaturization

	for (unsigned i = 0; i < imaginaries.size(); i++)
	{
		if (natures[i] == nature_from) goto do_reNaturization;
	} goto doNot_reNaturization;

do_reNaturization:

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
	stich();
doNot_reNaturization:;
}

void magicParticle::setReNaturizationFunction(energonRule_func f) {
	reNaturize = f;
}

void magicParticle::setAutoOrder() {
	order = (char)imaginaries.size();
}

void magicParticle::setAutoRule()
{
	reNaturize = reNat_straight;
}

void magicParticle::setBase(mpn bs)
{
	base = bs;
}

void magicParticle::addComplexPart(mpn val, char imtype)
{
	imaginaries.push_back(val);
	natures[imaginaries.size() - 1] = imtype;
	natures[imaginaries.size()] = '\0';
}

void magicParticle::addEnergon(mpn base, char nature)
{
	addComplexPart(base, nature);
}

magicParticle::MPClass magicParticle::getClass()
{
	return type;
}

void magicParticle::stich()
{

	// TODO: delete goto's , method stich

	for (unsigned i = 0; i < imaginaries.size() - 1; i++)
	{
		for (unsigned j = i + 1; j < imaginaries.size(); j++)
		{
			if (natures[i] == natures[j]) {
				imaginaries[i] = imaginaries[i] + imaginaries[j];
				delEnergon(j);
			}

		}
	}

}

void magicParticle::setEnergon(mpn base, char nature)
{
	// if found then change
	// if not found then add
	for (unsigned i = 0; i < imaginaries.size(); i++)
	{
		if (natures[i] == nature) {
			imaginaries[i] = base;
		};
	}
	addEnergon(base, nature);
}

/*Operator '+' overriding for int*/
MP magicParticle::operator+(const int& second) {
	return MP(base + (mpn)second, imaginaries, natures);
}


/*Operator pre '++' overriding for MP
*/
MP& operator ++ (MP& f) {
	++f.base;
	return f;
}

/*Operator pre '--' overriding for MP
*/
MP& operator -- (MP& f) {
	--f.base;
	return f;
}

MP operator++(MP & f, int)
{
	MP g = MP(f.base, f.imaginaries, f.natures);
	f.base++;
	return g;
}

MP & operator--(MP & f, int)
{
	MP g = MP(f.base, f.imaginaries, f.natures);
	f.base--;
	return g;
}

std::ostream & operator<<(std::ostream & os, const MP & f)
{
	os << f.base;
	for (unsigned i = 0; i < f.imaginaries.size(); i++)
	{
		f.imaginaries[i] >= 0 ? os << '+' << f.imaginaries[i] : os << f.imaginaries[i];
		os << f.natures[i];
	}
	return os;
}

mpn reNat_straight(const mpn& a, const mpn& b)
{
	return a;
}

mpn reNat_linear(const mpn& a, const mpn& b)
{
	mpn A;
	return A = a * 10 + b + a / b + b / a;
}

mpn reNat_quadro(const mpn& a, const mpn& b)
{
	mpn A;
	return A = a*a - b;
}
