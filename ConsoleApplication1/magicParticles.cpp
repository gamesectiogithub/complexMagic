
#include "stdafx.h"



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
	return A = a*10 + b + a/b + b/a;
}

mpn reNat_quadro(const mpn& a, const mpn& b)
{
	mpn A;
	return A = a*a - b;
}
