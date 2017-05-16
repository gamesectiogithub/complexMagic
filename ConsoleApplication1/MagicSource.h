#pragma once

#include "magicParticles.h"
#include <string>

enum Chakra { Istok = 0, Zarod, Jivot, Persi, Lada, Lelya, Usta, Chelo, Rodnik };

class Essence
{
protected:
	string essenceName = "Something";
	bool alive = false;
public:
	virtual string getName() {
		return essenceName;
	}

	virtual void setName(string s) {
		essenceName = s;
	}
};

class NonAstralObject : public Essence
{
public:
	NonAstralObject() {
		setName("Some_Object");
		alive = false;
	}
};

class MagicUser : public NonAstralObject
{
protected:
	Chakra affixChakra;
	int thisNumber;
public:

	static int mageNumber;

	static int getNumber() {
		return mageNumber;
	}

	static int setNumber(int i) {
		mageNumber = i;
	}

	MagicUser() {
		setName("Mage");
		alive = true;
		thisNumber = getNumber();
		setNumber(thisNumber + 1);
	}

	Chakra getChakra() {
		return affixChakra;
	}

	void setChakra(Chakra c) {
		affixChakra = c;
	}

	void setChakra(int i) {
		affixChakra = (Chakra)(i%9);
	}

	void setChakra() {
		affixChakra = (Chakra)(rand()%9);
	}

	string getName() {
		return essenceName + to_string( thisNumber);
	}

	virtual void setName(string s) {
		essenceName = s;
	}
};

class MagicSource
{
public:
	MagicSource();
	~MagicSource();
protected:
	Essence thisEssence;
	Essence affixEssence;
	AstralPoint placement;
	mpn power;
	char* energonNatures;
	bool limitedTime;
	bool limitedEnergy;
	Functionality functions;
	MagicStream stream;
};

