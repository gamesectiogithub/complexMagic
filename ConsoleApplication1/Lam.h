#pragma once

#include "AstralPoint.h"
#include <string>

enum AstralAreaType { Astral, World, Reflexion, Shadow };

class Lam
{
protected:
	AstralPoint* position = new AstralPoint();
	string natures;

public:
	virtual ~Lam();
	Lam(AstralPoint* p, string s);

	AstralPoint* getPos();
	string getNatures();
	void setNatures(string s);
};

class AstralArea : public Lam 
{
protected:
	AstralAreaType AAType = Astral;
	bool hasTime = false;

public:
	AstralArea();
	virtual ~AstralArea();
	AstralArea(AstralAreaType AAType_, AstralPoint* position_);
	AstralArea(AstralAreaType AAType_, AstralPoint* position_, string natures);
	AstralArea(AstralAreaType AAType_, bool hasTime_, AstralPoint* position_, string natures_);
};