#pragma once

#include "stdafx.h"

/** Astralpoint
*/


AstralPoint::AstralPoint()
{
	n = NULL;
	e = NULL;
	s = NULL;
	w = NULL;
}

AstralPoint::AstralPoint(Lam * L)
{
	n = L;	e = NULL;	s = NULL;	w = NULL;
}

AstralPoint::AstralPoint(Lam * L, char T)
{
	switch (T)
	{
	case 'n':
	case 'N':
		n = L;
		break;
	case 'W':
	case 'w':
		w = L;
		break;
	case 'E':
	case 'e':
		e = L;
		break;
	case 's':
	case 'S':
		s = L;
		break;
	default:
		AstralPoint(L);
		break;
	}
}

AstralPoint::AstralPoint(Lam * A, Lam * B, Lam * C, Lam *D)
{
	n = A;	e = B;	s = C;	w = D;
}

AstralPoint::~AstralPoint()
{
	delete n, e, s, w;
}

Lam* AstralPoint::getPos()
{
	Lam* l = 0;
	l[0] = *n;
	l[1] = *e;
	l[2] = *s;
	l[3] = *w;

	return l;
}

/** LAM 
*/


Lam::~Lam()
{
	delete position;
}

Lam::Lam(AstralPoint* p, string s)
{
	position = p;
	natures = s;
}

AstralPoint* Lam::getPos()
{
	return position;
}

string Lam::getNatures()
{
	return natures;
}

void Lam::setNatures(string s)
{
	natures = s;
}

/** magicParticles
*/


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

ostream & operator<<(ostream & os, const MP & f)
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


