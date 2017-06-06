#pragma once
#include "stdafx.h"



#define mpn short
#define MP magicParticle

//using namespace std;



class MagicSource;
class Lam;
class AstralArea;
class Essence;

//using hegaon positions in this version
struct AstralPoint
{
	enum AstralPointType { Astral, World, Reflexion, Shadow, ACell, WCell, RCell, SCell };

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

2d array can be AstralPoints' container, where n = 2k, k := 0..N, each [n] row has Oy offset +1 line down
*/

protected:
	AstralPointType owner;
	AstralArea* owner_ptr;
	mpn col;
	mpn row;

private:
	AstralPoint();
	
public:

	AstralPoint(mpn col, mpn row);

protected:
	AstralArea* getPointer();
	void setPointer(AstralArea* p);
	
};

typedef  mpn(*energonRule_func)(const mpn&, const mpn&);

/*functions for renaturization of bases of energons*/
mpn reNat_linear(const mpn&, const mpn&);
mpn reNat_quadro(const mpn&, const mpn&);
mpn reNat_straight(const mpn&, const mpn&);

struct magicParticle {

public:

	enum MPClass { QNT, TLE, TFU, ANT, ANM, INV, EXO };

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
			imaginaries[i] >= 0 ? std::cout << '+' << imaginaries[i] : std::cout << imaginaries[i];
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

		std::vector<mpn> mImaginaries;

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

		std::vector<mpn> mImaginaries;

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

//for MagicSources, MagicStreams, Essences
struct Connector {

	bool owner_1_state; //?
	bool owner_2_state;
	void* owner_1; //owner -
	void* owner_2; //owner +
private:
	Connector();
public:
	Connector(void* owner1, void* owner2);

	//false for owner_1, true for owner_2
	void setNewOwner(bool flag, void* newOwner);
	void setNewOwner(void* owner, void* newOwner);
	//false for owner_1, true for owner_2
	void* getOwner(bool flag);


};

struct NativeEnergons {
	char* feels; // filters - unknown Energon can't come in => radiation or something
	char* interacts; // definitions - known Energon is used inside the Essence or MagicSource
	char* ignores; // permission for SubStructures or Improvements use known or even unknown Energon;

	NativeEnergons();
	~NativeEnergons();

	char* getFeels();
	char* getInteracts(); 
	char* getIgnores();

	void setFeels(char* f);
	void setInteracts(char* i);
	void setIgnores(char* i);
};

//weather phenomenons exists in AstralAreas: one phenomenon for one AstralArea
struct AstralWeather {
	//TODO: this
	enum Phenomenon { Flow, Wind, Fog, Storm, Tornado, Uragan, Calm, Swell, Island };

	Phenomenon phenomenon;
	AstralPoint* p;

	AstralWeather();

	Phenomenon getPhenomenon();
	void setPhenomenon(Phenomenon p);
	AstralPoint* getAstralPoint();
	void setAstralPoint(AstralPoint* a);

	void levelUp();
	void levelDown();
};

//one controller for one LAM
struct AstralWeatherController {
	Lam* owner;

public:
	AstralWeatherController();
	~AstralWeatherController();

	void setLam(Lam* lam);
	Lam* getLam();

	void setWeather(AstralPoint p);
	void setWeather(mpn col, mpn row);
	void setWeather(AstralArea aa);
	void setRandomWeather(); //in this Lam
	void complementWeather(); //in this Lam
	void complementWeather(AstralPoint p);
	void complementWeather(mpn col, mpn row);
	void complementWeather(AstralArea aa);

	//levelup or leveldown
	void levelWeather(AstralPoint p, bool up = true);
	void levelWeather(mpn col, mpn row, bool up = true);
	void levelWeather(AstralArea aa, bool up = true);

	//* Astral Weather interactions */



};

class Connectable // TODO: make abstract
{
protected:
public: // delete
	Connector* inputConnectors; //TODO: array or container
	Connector* outputConnectors;
	
	// TODO: contructors
	Connectable();
	~Connectable();

	void setConnectorOutput(Connector outputCon);
	void setConnectorInput(Connector inputCon);
	void setConnectorsInput(Connector* inputConnectors, mpn n);
	void setConnectorsOutput(Connector* outputConnectors, mpn n);
	void addConnectorInput(Connector inputConnector);
	void addConnectorOutput(Connector outputConnector);
	//virtual void release() = 0; //
};

class Placeable {
protected:
public: // delete
	AstralPoint* outerAstralSpace_ptr; 


	Placeable();
	~Placeable();

	//TODO: getNeighbours



};

class Containable {
protected:
public: // delete

	AstralPoint* AstralSpace; // TODO: array or any container
	mpn AstralSpace_width;
	mpn AstralSpace_length;

	Containable(); //create a random AstralSpace 2x2 up to 5x5
	~Containable(); 

	Containable(mpn ASpace_width, mpn ASpace_length);
	Containable(mpn ASpace_width_or_length);

	//TODO: need template
	void* getAstralSpaceContent(AstralPoint* p_center, mpn area_radius);
	void* getAstralSpaceContent(AstralPoint p);// returns AstralSpace content at the AstralPoint
	void* getAstralSpaceContent(mpn col, mpn row);// returns AstralSpace content at the special coordinats
	void* getAstralSpaceContent(); // returns array of pointers to all AstralSpace elements
								   //need template
	void setAstralSpaceContent(AstralPoint p, void* aa);

	//TODO: template
	AstralPoint* getNeighbours(mpn centerCell_col, mpn centerCell_row); // returns array AstralPoint [0]-[5] clockwise
	AstralPoint* getFarFacetNeighbours(mpn centerCell_col, mpn centerCell_row); // reaturns array AstralPoint [0]-[5] clockwise; distance 1 cell
	AstralPoint* getFarVertexNeighbours(mpn centerCell_col, mpn centerCell_row); // reaturns array AstralPoint [0]-[5] clockwise; distance 1 cell
	AstralPoint* getFarNeighbours(mpn centerCell_col, mpn centerCell_row);// reaturns array AstralPoint [0]-[11] clockwise; distance 1 cell

};

// base class for objects
class Essence : virtual public ModelObject, virtual public Connectable
{
protected:

	MagicSource* magicSrcPtr;
	Lam* currentLAM;
	
	mpn inputConNumber;
	
	NativeEnergons nativeEnergons;
public:

	Essence();
	~Essence();

	void setLam(Lam* lam);
	Lam* getLam();

	void setMagicSource(MagicSource* msptr);
	bool isMagicSourcePresentation();
	MagicSource* getMagicSource();

	

};

//Local area of multiuniverse
class Lam : virtual public Containable, virtual public ModelObject
{
private:
	AstralWeatherController AWC;

protected:
	
	NativeEnergons nenergons;
	


public:
	
	Lam();
	virtual ~Lam();
	Lam(AstralPoint* space, char* f, char* in, char ig);
	Lam(mpn space_w, mpn space_l, char* f, char* in, char ig);
	Lam(AstralPoint* space, NativeEnergons ne);
	Lam(mpn space_w, mpn space_l, NativeEnergons ne);

	const NativeEnergons getNativeEnergons();
	void setNativeEnergons(NativeEnergons ne_);

	

};

class MagicStream : virtual public Connectable, virtual public ModelObject
{
public:
	enum Shapes { Circle, Oval, Triang, Rectang, Figure };

protected:
	std::vector<MP> magicParticles;
	std::vector<Shapes> shapesConfig;
	Lam* traceLAMs;
	bool isSrcLAM;


public: //methods
	Essence* getAffixPoint();
	void setAffixPoint(Essence* e);



};

//MPs are borning due to AstralWeather interaction with Multiuniverse elements
class MagicParticlesGenerator
{};

//Astral Area of LAM with the same weather behaviour
class AstralArea : public Lam, public Placeable, virtual public Containable
{
protected:
	
	bool hasTime = false;
	std::string natures;
	AstralWeather astralWeather;
	MagicStream* superPositonalBackgroundStream;
	char* nativeEnergons;
public:

	AstralArea();
	virtual ~AstralArea();
	

	AstralPoint* getPos();
	std::string getNatures();
	void setNatures(std::string s);

	MP* createMagicParticle();
};

//Astral Area of LAM which can be included into one AstralArea
class World : public AstralArea
{

};

//Special types of World
class SubWorld : public World
{

};

// functionality

typedef MP(*determination_f)(const int, MP[]);
typedef void(*determination_v)(const int, MP[]);

void determineMPlist(const int cnt, MP mpa[]);
MP determineMPfunc(const int cnt, MP mpa[]);

//default non-alive Essence
class NonAstralObject : public Essence
{
protected:
	bool is_alive;

public:
	NonAstralObject() {
		setName("Some_Object");
		is_alive = false;
	}
};

//default alive Essence
class AliveEssence : public Essence
{
public:
	enum Chakra { Istok = 0, Zarod, Jivot, Persi, Lada, Lelya, Usta, Chelo, Rodnik };


};

//default alive affix point of the magical architecture
class MagicUser : public AliveEssence
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

//container for functions of MagicSources
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

//deafult class for elemenets of magical architecture
class MagicSource : virtual public Connectable, virtual public ModelObject, public Placeable
{
public:
	MagicSource();
	~MagicSource();
protected:
	Essence* thisEssence;
	mpn magicPower;
	char* energonNatures;
	bool limitedTime;
	bool limitedEnergy;
	Functionality functions;
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

class Fantom : public MagicSource 
{};

class Unevennes : public MagicSource
{};

class Anomaly : public MagicSource
{
	/*
	BlackHole
	Voka
	Vavylon
	Waterfall
	Timeloop
	Sarcophagus

	-Ring
	Arch
	Mirror
	Portal
	Gates
	-Barrier

	Worldbasis
	Forcepl
	Tumulus
	Fountain
	Tower
	Pharos

	*/
};


/* complex Anomalies*/

class Link : public MagicSource, public MagicStream
{};

class Channel : public Link 
{};

class Bridge : public Channel
{};

class Field : public Link 
{};

class Ring : public Field
{};

class Barrier : public Bridge
{};

