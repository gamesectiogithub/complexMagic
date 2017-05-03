
#include "stdafx.h"

/*Operator pre '++' overriding for #mpn
*/
MP& operator ++ (MP& f) {
	++f.base;
	return f;
}

/*Operator pre '--' overriding for #mpn
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
	mpn A;
	return A = a + b;
}

mpn reNat_linear(const mpn& a, const mpn& b)
{
	mpn A;
	return A = a + b;
}

mpn reNat_quadro(const mpn& a, const mpn& b)
{
	mpn A;
	return A = a + b;
}