#pragma once

#include "stdafx.h"


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

