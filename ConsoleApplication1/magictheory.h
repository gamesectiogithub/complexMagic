#pragma once

#include "stdafx.h"

#define mpn short
#define MP magicParticle

using namespace std;

enum AstralAreaType { Astral, World, Reflexion, Shadow };

//using hegaon positions in this version
class AstralPoint
{

/**lets print to console or txt file like 

 +-+
+<I>+
 +-+

symbol I is any informational symbol
space usage: 1 informational symbol in total 15 symbols, 12 symbols can be shared
hex and neighbors:

       +-+
    +-+<I>+-+
   +<I>+-+<I>+
    +-+<I>+-+
   +<I>+-+<I>+
    +-+<I>+-+ 
       +-+

*/

protected:
	AstralAreaType owner;
	mpn col;
	mpn row;

public:

	AstralPoint();
	~AstralPoint();

	AstralPoint(mpn col, mpn row);

protected:
	/*methods*/
	
};


// magicparticles


typedef  mpn(*energonRule_func)(const mpn&, const mpn&);

/*functions for renaturization of bases of energons*/
mpn reNat_linear(const mpn&, const mpn&);
mpn reNat_quadro(const mpn&, const mpn&);
mpn reNat_straight(const mpn&, const mpn&);


struct magicParticle {

public:

	enum MPClass { QNT, TLE, TFU, ATM, AMS, INV, EXO };

private:
	const MPClass type;
	char order; // use like a number
	mpn base;
	std::vector<mpn> imaginaries;
	char* natures;
	energonRule_func reNaturize;
	int* n = NULL;
	bool conserved = false; // if true -> methods must not work: stich,

public:

	MP();
	MP(mpn mpBase, mpn mpIm);
	MP(mpn mpBase, mpn mpIm, char mpImType);
	MP(mpn mpBase, std::vector<mpn> mpImaginaries, char* mpNatures);

	~MP();

	/*deleting complex part with number {id}*/
	void delEnergon(mpn id);

	/*function for converting energons to another nature*/
	//TODO: change default parameter
	void reNaturization(const char nature_from, const char nature_to, energonRule_func f = reNat_straight);

	/*determine function of renaturization*/
	void setReNaturizationFunction(energonRule_func f);

	/*print Mystic Number with cout & endl*/
	void toString() {

		// base|imag[n]|nature[n]...
		std::cout << base;

		for (unsigned i = 0; i < imaginaries.size(); i++)
		{
			imaginaries[i] >= 0 ? std::cout << '+' << imaginaries[i] : cout << imaginaries[i];
			std::cout << natures[i];
		}

		std::cout << std::endl;
	};

	void setAutoOrder();

	void setAutoRule();

	void setBase(mpn bs);

	void addComplexPart(mpn val, char imtype);

	void addEnergon(mpn base, char nature);

	MPClass getClass();

	/*stich all energons with the same nature*/
	void stich();

	/*sort energons by order in LAM*/
	// void sortOrder()

	/*setters for energons*/
	void setEnergon(mpn base, char nature);

	/*getters for energons*/


	/*Operator '=' overriding for MP*/
	void operator=(const MP& second) {
		this->base = second.base;
		this->imaginaries = second.imaginaries;
		this->natures = second.natures;
		this->order = second.order;
	}

	/*Operator '+' overriding for MP*/
	MP MP::operator+(const MP& second) {

		mpn mBase;
		mBase = base + second.base;

		vector<mpn> mImaginaries;

		char* mNatures = natures;

		for (unsigned i = 0; i < imaginaries.size(); i++)
		{
			for (unsigned j = 0; j < second.imaginaries.size(); j++)
			{
				// sum for parts with the same nature
				if (natures[i] == second.natures[j]) {
					mImaginaries.push_back(imaginaries[i] + second.imaginaries[j]);
					break;
				}
				else if (j + 1 == second.imaginaries.size()) {
					// this [i] part of first has unique nature, must add it to answer
					mImaginaries.push_back(imaginaries[i]);
					mNatures[mImaginaries.size() - 1] = natures[i];
				}
			}
		}

		for (unsigned i = 0; i < second.imaginaries.size(); i++)
		{
			for (unsigned j = 0; j < imaginaries.size(); j++)
			{
				if (second.natures[i] == natures[j]) {
					break;
				}
				else if (j + 1 == imaginaries.size()) {
					// this [i] part of second has unique nature, must add it to answer
					mImaginaries.push_back(second.imaginaries[i]);
					mNatures[mImaginaries.size() - 1] = second.natures[i];
				}
			}
		}

		mNatures[mImaginaries.size()] = '\0'; // for correct char* array

		return MP(mBase, mImaginaries, mNatures);
	}

	/*Operator '+' overriding for #mpn*/
	MP MP::operator+(const mpn& second) {
		return MP(base + second, imaginaries, natures);
	}

	/*Operator '+' overriding for int*/
	MP operator+(const int&);

	/*Operator '-' overriding for int*/
	MP MP::operator-(const int& second) {
		return MP(base - (mpn)second, imaginaries, natures);
	}

	/*Operator '-' overriding for #mpn*/
	MP MP::operator-(const mpn& second) {
		return MP(base - second, imaginaries, natures);
	}

	/*Operator '-' overriding for MP*/
	MP MP::operator-(const MP& second) {

		mpn mBase;
		mBase = base - second.base;

		vector<mpn> mImaginaries;

		char* mNatures = natures;

		for (unsigned i = 0; i < imaginaries.size(); i++)
		{
			for (unsigned j = 0; j < second.imaginaries.size(); j++)
			{
				// for parts with the same nature
				if (natures[i] == second.natures[j]) {
					mImaginaries.push_back(imaginaries[i] - second.imaginaries[j]);
					break;
				}
				else if (j + 1 == second.imaginaries.size()) {
					// this [i] part of first has unique nature, must add it to answer
					mImaginaries.push_back(imaginaries[i]);
					mNatures[mImaginaries.size() - 1] = natures[i];
				}
			}
		}

		for (unsigned i = 0; i < second.imaginaries.size(); i++)
		{
			for (unsigned j = 0; j < imaginaries.size(); j++)
			{
				if (second.natures[i] == natures[j]) {
					break;
				}
				else if (j + 1 == imaginaries.size()) {
					// this [i] part of second has unique nature, must add it to answer
					mImaginaries.push_back(second.imaginaries[i] * (-1));
					mNatures[mImaginaries.size() - 1] = second.natures[i];
				}
			}
		}

		mNatures[mImaginaries.size()] = '\0'; // for correct char* array

		return MP(mBase, mImaginaries, mNatures);
	}

	//prototypes
	/*Operator pre '++' overriding for MP*/
	friend MP& operator ++ (MP& f);
	/*Operator pre '--' overriding for MP*/
	friend MP& operator -- (MP& f);
	/*Operator post '++' overriding for MP*/
	friend MP operator ++ (MP& f, int);
	/*Operator post '--' overriding for MP*/
	friend MP& operator -- (MP& f, int);
	/*Operator << for std::cout with MP*/
	friend std::ostream& operator << (std::ostream& os, const MP& f);

};


struct Connector {
	bool owner_1_state;
	bool owner_2_state;
	void* owner_1;
	void* owner_2;
};

struct NativeEnergons {
	char* feels;
	char* interacts;
	char* ignores;
};

class MagicSource;
class Lam;

class Essence : public ModelObject
{
public:
	enum Chakra { Istok = 0, Zarod, Jivot, Persi, Lada, Lelya, Usta, Chelo, Rodnik };

protected:

	bool is_alive = true;
	MagicSource* magicSrcPtr;
	Lam* currentLAM;
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


//one controller for one LAM
class AstralWeatherController {

public:
	AstralWeatherController();
	~AstralWeatherController();
};

//weather phenomenons
struct AstralWeather {
	//TODO: this
	enum AstralPenomenon { Flow, Wind, Fog, Storm, Tornado, Uragan, Calm, Swell, Island };

	bool dummy = false;
};

//Local area of multiuniverse
class Lam
{
private:
	char* index; // for global map with many different LAMs

protected:
	AstralPoint* AstralSpace = new AstralPoint(); // TODO array or any container

public:
	

	   virtual ~Lam();
	   Lam(AstralPoint* p, std::string s);
};

class MagicStream {
public:
	enum Shapes { Circle, Oval, Triang, Rectang, Fugure };

protected:
	std::vector<MP> magicParticles;
	std::vector<Shapes> shapesConfig;
	Lam* msLAMs;
	Connector* connectors;
	Essence* affixEssence;

public: //methods
	Essence* getAffixPoint();
	void setAffixPoint(Essence* e);

};

class AstralArea : public Lam
{
protected:
	AstralAreaType AAType;
	bool hasTime = false;
	std::string natures;
	AstralWeather astralWeather;
	MagicStream* superPositonalBackgroundStream;
	char* nativeEnergons;
public:

	AstralArea();
	virtual ~AstralArea();
	AstralArea(AstralAreaType AAType_, AstralPoint* position_);
	AstralArea(AstralAreaType AAType_, AstralPoint* position_, std::string natures);
	AstralArea(AstralAreaType AAType_, bool hasTime_, AstralPoint* position_, std::string natures_);

	AstralPoint* getPos();
	std::string getNatures();
	void setNatures(std::string s);

	MP* createMagicParticle();
};



// functionality

typedef MP(*determination_f)(const int, MP[]);
typedef void(*determination_v)(const int, MP[]);

void determineMPlist(const int cnt, MP mpa[]);
MP determineMPfunc(const int cnt, MP mpa[]);

// magicSource



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
		affixChakra = (Chakra)(i % 9);
	}

	void setChakra() {
		affixChakra = (Chakra)(rand() % 9);
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
	Connector* inputConnectors;
	Connector* outputConnectors;
	//Functionality functions;
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


