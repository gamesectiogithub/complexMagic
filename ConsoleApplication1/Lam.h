#pragma once

#include "stdafx.h"

enum AstralAreaType { Astral, World, Reflexion, Shadow };

struct AstralWeather {
	//TODO: this
	enum AstralPenomenon { Rain, Wind };

	bool dummy = false;
};


class Lam
{
protected:
	AstralPoint* position = new AstralPoint();
	string natures;
	AstralWeather astralWeather;
private:
	const bool isTimeless = true;
protected:
	MagicStream* superPositonalBackgroundStream;
	char* nativeEnergons;

public:;
	virtual ~Lam();
	Lam(AstralPoint* p, string s);

	AstralPoint* getPos();
	string getNatures();
	void setNatures(string s);

	MP createMagicParticle();
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

