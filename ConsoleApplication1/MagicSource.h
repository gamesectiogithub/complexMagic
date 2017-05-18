#pragma once

#include <string>
#include "Lam.h"
#include "functionality.h"

enum Chakra { Istok = 0, Zarod, Jivot, Persi, Lada, Lelya, Usta, Chelo, Rodnik };
enum Shapes { Circle, Oval, Triang, Rectang, Fugure  };

class Essence
{
protected:
	string essenceName = "Something";
	bool is_alive = false;
	MagicSource* magicSrcPtr = 0;
	Lam* currentWorld = 0;
public:
	virtual string getName() {
		return essenceName;
	}

	virtual void setName(string s) {
		essenceName = s;
	}
	// connect MagicSrc to some presentation essence in some world
	virtual void makeThisMagicSource(MagicSource* msrc, Lam* world) {
		magicSrcPtr = msrc;
		currentWorld = world;
	}
};

class NonAstralObject : public Essence
{
public:
	NonAstralObject() {
		setName("Some_Object");
		is_alive = false;
	}
};

class MagicUser : public NonAstralObject
{
protected:
	Chakra affixChakra;
	int thisnum;

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
		is_alive = true;
		setNumber(getNumber() + 1);
		thisnum = getNumber();
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
		return essenceName;
	}

	virtual void setName(string s) {
		essenceName = s + to_string(thisnum);
	}
};

struct Functionality {

	/* MP dissapear*/
	determination_v fAbsorb;
	/* MP are allowed to come in */
	determination_v fTake;
	/* MP are enprisoned*/
	determination_v fAccumulate;
	/* MP are producing*/
	determination_f fGenerate;
	/* MP are remaking*/
	determination_f fTransform;
	/* MP are allowed to come out*/
	determination_v fGive;
	/* MP are allowed*/
	determination_v fIgnore;

};

struct MagicStream {

	vector<MP> magicParticles;
	vector<Shapes> stream;

	Essence* affixEssence;

	
public: //methods
	Essence* getAffixPoint();
	void setAffixPoint(Essence* e);

};

class MagicSource
{
public:
	MagicSource();
	~MagicSource();
protected:
	Essence* thisEssence;
	
	AstralPoint placement;
	mpn power;
	char* energonNatures;
	bool limitedTime;
	bool limitedEnergy;
	Functionality functions;
	MagicStream stream;


public:

	Essence* getSourcePoint();
	
	AstralPoint getPlacement();
	mpn getPower();
	char* getEnergonNatures();
	bool isLimitedTime();
	bool isLimitedEnergy();
	const Functionality getFunctions();
	const MagicStream getStream();

	
	void setEnergonNatures();
	void setLimitedTime();
	void setLimitedEnergy();

	void setFunction(determination_v func);
	void setFunction(determination_f func);

};

