#pragma once

class Lam;

//using square positions in this version
class AstralPoint
{
protected:
	Lam* n;
	Lam* s;
	Lam* w;
	Lam* e;

public:
	AstralPoint();
	AstralPoint(Lam*);
	AstralPoint(Lam*, char);
	AstralPoint(Lam*, Lam*, Lam*, Lam*);
	~AstralPoint();

protected:
	//return North, East, South, West
	Lam* getPos();
};

// functionality

typedef MP(*determination_f)(const int, MP[]);
typedef void(*determination_v)(const int, MP[]);

void determineMPlist(const int cnt, MP mpa[]);
MP determineMPfunc(const int cnt, MP mpa[]);

// LAM

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

// magicparticles

/* mystic particles have types
*/

#define mpn short
#define MP magicParticle

typedef  mpn(*energonRule_func)(const mpn&, const mpn&);


using namespace std;

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
	vector<mpn> imaginaries;
	char* natures;
	energonRule_func reNaturize;

	int* n = NULL;
	bool conserved = false; // if true -> methods must not work: stich,

public:

	MP(void) : type(QNT)
	{

		base = 0;
		imaginaries.push_back(0);
		natures = new char;
		natures[0] = 'i';
		natures[1] = '\0';
		setAutoOrder();
		setAutoRule();
		reNaturize = reNat_straight;

	};

	MP(mpn mpBase, mpn mpIm) : base(mpBase), order(1), type(QNT)
	{
		reNaturize = reNat_straight;
		imaginaries.push_back(mpIm);
		natures = new char;
		natures[0] = 'i';
		natures[1] = '\0';
		setAutoRule();
	}

	MP(mpn mpBase, mpn mpIm, char mpImType) : base(mpBase), order(1), type(QNT)
	{
		reNaturize = reNat_straight;
		imaginaries.push_back(mpIm);
		natures = new char;
		natures[0] = mpImType;
		natures[1] = '\0';
		setAutoRule();
	}

	MP(mpn mpBase, vector<mpn> mpImaginaries, char* mpNatures) : base(mpBase), type(QNT)
	{
		reNaturize = reNat_straight;
		imaginaries = mpImaginaries;
		natures = mpNatures;
		setAutoOrder();
		setAutoRule();
		stich();
	}


	~MP()
	{
		delete[] n;
	}

	/*deleting complex part with number {id}*/
	void delEnergon(mpn id) {

		imaginaries.erase(imaginaries.begin() + id);
		char* dub = natures;
		unsigned k = 0;

		for (unsigned i = 0; i < imaginaries.size() + 2; i++)
		{
			if (i != id) {
				dub[k] = natures[i];
			}
			else {
				k--;
			}
			++k;
		}

		natures = "";
		natures = dub;
	}

	/*function for converting energons to another nature*/
	void reNaturization(char nature_from, char nature_to, energonRule_func f = reNat_straight)
	{

		// TODO: delete goto's , method reNaturization

		for (unsigned i = 0; i < imaginaries.size(); i++)
		{
			if (natures[i] == nature_from) goto do_reNaturization;
		} goto doNot_reNaturization;

	do_reNaturization:

		mpn base_f = 0, base_t = 0;

		for (unsigned i = 0; i < imaginaries.size(); i++)
		{
			if (natures[i] == nature_from)
			{
				base_f = (mpn)i;
			}
			if (natures[i] == nature_to)
			{
				base_t = (mpn)i;
			}
		}

		imaginaries[base_f] = f(imaginaries[base_f], imaginaries[base_t]);
		natures[base_f] = nature_to;
		stich();
	doNot_reNaturization:;
	}

	/*determine function of renaturization*/
	void setReNaturizationFunction(energonRule_func f) {
		reNaturize = f;
	}

	/*print Mystic Number with cout & endl*/
	void toString() {

		// base|imag[n]|nature[n]...
		cout << base;

		for (unsigned i = 0; i < imaginaries.size(); i++)
		{
			imaginaries[i] >= 0 ? cout << '+' << imaginaries[i] : cout << imaginaries[i];
			cout << natures[i];
		}

		cout << endl;
	};

	void setAutoOrder() {
		order = (char)imaginaries.size();
	}

	void setAutoRule() {
		reNaturize = reNat_straight;
	}

	void setBase(mpn bs) {
		base = bs;
	}

	void addComplexPart(mpn val, char imtype) {
		imaginaries.push_back(val);
		natures[imaginaries.size() - 1] = imtype;
		natures[imaginaries.size()] = '\0';
	}

	void addEnergon(mpn base, char nature) {
		addComplexPart(base, nature);
	}

	MPClass getClass() {
		return type;
	}

	/*stich all energons with the same nature*/
	void stich() {

		// TODO: delete goto's , method stich

		for (unsigned i = 0; i < imaginaries.size() - 1; i++)
		{
			for (unsigned j = i + 1; j < imaginaries.size(); j++)
			{
				if (natures[i] == natures[j]) {
					imaginaries[i] = imaginaries[i] + imaginaries[j];
					delEnergon(j);
				}

			}
		}

	}

	/*sort energons by order in LAM*/
	// void sortOrder()

	/*setters for energons*/
	void setEnergon(mpn base, char nature) {
		// if found then change
		// if not found then add
		for (unsigned i = 0; i < imaginaries.size(); i++)
		{
			if (natures[i] == nature) {
				imaginaries[i] = base;
			};
		}
		addEnergon(base, nature);
	}

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
	friend ostream& operator << (ostream& os, const MP& f);

};

// magicSource

enum Chakra { Istok = 0, Zarod, Jivot, Persi, Lada, Lelya, Usta, Chelo, Rodnik };
enum Shapes { Circle, Oval, Triang, Rectang, Fugure };

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


