#include "stdafx.h"
#include "AstralPoint.h"
#include "Lam.h"

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

AstralPoint::AstralPoint(Lam * A, Lam * B , Lam * C, Lam *D)
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
