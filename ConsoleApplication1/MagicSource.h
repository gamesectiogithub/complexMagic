#pragma once

#include "stdafx.h"	

enum Chakra { Istok = 0, Zarod, Jivot, Persi, Lada, Lelya, Usta, Chelo, Rodnik };
enum Shapes { Circle, Oval, Triang, Rectang, Fugure  };

struct NativeEnergons {
	char* feels;
	char* interacts;
	char* ignores;
};

class Essence : public ModelObject
{
protected:

	bool is_alive = true;
	MagicSource* magicSrcPtr;
	Lam* currentLAM = 0;
	Connector* inputConnectors;
	Connector outputConnector;
	NativeEnergons nativeEnergons;
public:
	
	// connect MagicSrc to some presentation essence in some world
	virtual void makeThisMagicSource(MagicSource* msrc, Lam* world) {
		magicSrcPtr = msrc;
		currentLAM = world;
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
	

public:

	MagicUser() {
		
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
};

struct Functionality {

	/* MP dissapear*/
	determination_v fAbsorb;
	/* MP are enprisoned*/
	determination_v fAccumulate;
	/* MP are producing*/
	determination_f fGenerate;
	/* MP are remaking*/
	determination_f fTransform;
	/* MP are allowed to come in */
	determination_v fFeel;
	/* MP are allowed to come out*/
	determination_v fInteract;
	/* MP are allowed*/
	determination_v fIgnore;

};

struct Connector {
	bool owner_1_state;
	bool owner_2_state;
	void* owner_1;
	void* owner_2;
};

class MagicStream {
protected:
	vector<MP> magicParticles;
	vector<Shapes> shapesConfig;
	Lam* msLAMs[];
	Connector* connectors[];
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
	AstralPoint astralPosition;
	mpn magicPower;
	char* energonNatures;
	bool limitedTime;
	bool limitedEnergy;
	Functionality functions;
	MagicStream stream;
	NativeEnergons nativeEnergons;
	Connector* inputConnectors[];
	Connector* outputConnectors[];
	Functionality functions;
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

