#pragma once
#include "stdafx.h"
#include "magictheory.h"
#include <ctime>


magicParticle::MP(void) : type(QNT)
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

magicParticle::MP(mpn mpBase, mpn mpIm) : base(mpBase), order(1), type(QNT)
{
	reNaturize = reNat_straight;
	imaginaries.push_back(mpIm);
	natures = new char;
	natures[0] = 'i';
	natures[1] = '\0';
	setAutoRule();
}

magicParticle::MP(mpn mpBase, mpn mpIm, char mpImType) : base(mpBase), order(1), type(QNT)
{
	reNaturize = reNat_straight;
	imaginaries.push_back(mpIm);
	natures = new char;
	natures[0] = mpImType;
	natures[1] = '\0';
	setAutoRule();
}

magicParticle::MP(mpn mpBase, std::vector<mpn> mpImaginaries, char* mpNatures) : base(mpBase), type(QNT)
{
	reNaturize = reNat_straight;
	imaginaries = mpImaginaries;
	natures = mpNatures;
	setAutoOrder();
	setAutoRule();
	stich();
}

magicParticle::~MP()
{
	delete[] n;
}


void magicParticle::delEnergon(mpn id) {

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

void magicParticle::reNaturization(const char nature_from, const char nature_to, energonRule_func f)
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

void magicParticle::setReNaturizationFunction(energonRule_func f) {
	reNaturize = f;
}

void magicParticle::setAutoOrder() {
	order = (char)imaginaries.size();
}

void magicParticle::setAutoRule()
{
	reNaturize = reNat_straight;
}

void magicParticle::setBase(mpn bs)
{
	base = bs;
}

void magicParticle::addComplexPart(mpn val, char imtype)
{
	imaginaries.push_back(val);
	natures[imaginaries.size() - 1] = imtype;
	natures[imaginaries.size()] = '\0';
}

void magicParticle::addEnergon(mpn base, char nature)
{
	addComplexPart(base, nature);
}

magicParticle::MPClass magicParticle::getClass()
{
	return type;
}

void magicParticle::stich()
{

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

void magicParticle::setEnergon(mpn base, char nature)
{
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

/*Operator '+' overriding for int*/
MP magicParticle::operator+(const int& second) {
	return MP(base + (mpn)second, imaginaries, natures);
}


/*Operator pre '++' overriding for MP
*/
MP& operator ++ (MP& f) {
	++f.base;
	return f;
}

/*Operator pre '--' overriding for MP
*/
MP& operator -- (MP& f) {
	--f.base;
	return f;
}

MP operator++(MP & f, int)
{
	MP g = MP(f.base, f.imaginaries, f.natures);
	f.base++;
	return g;
}

MP & operator--(MP & f, int)
{
	MP g = MP(f.base, f.imaginaries, f.natures);
	f.base--;
	return g;
}

std::ostream & operator<<(std::ostream & os, const MP & f)
{
	os << f.base;
	for (unsigned i = 0; i < f.imaginaries.size(); i++)
	{
		f.imaginaries[i] >= 0 ? os << '+' << f.imaginaries[i] : os << f.imaginaries[i];
		os << f.natures[i];
	}
	return os;
}

mpn reNat_straight(const mpn& a, const mpn& b)
{
	return a;
}

std::string hexy_string2(std::string s_)
{
	std::string ss = "";
	ss += " +-+";
	ss += "+<"; ss += s_; ss += ">+";
	ss += " +-+";
	return ss;
}

std::string hexy_string(std::string s_)
{
	std::string ss = "";
	ss += " +-+";
	ss += "+<"; ss += s_; ss += ">+";
	ss += " +-+";
	
	ss.insert(4, "\n", 1);
	ss.insert(10, "\n", 1);
	ss.insert(15, "\n", 1);
	return ss;
}

mpn reNat_linear(const mpn& a, const mpn& b)
{
	mpn A;
	return A = a * 10 + b + a / b + b / a;
}

mpn reNat_quadro(const mpn& a, const mpn& b)
{
	mpn A;
	return A = a*a - b;
}

AstralPoint::AstralPoint(): owner_type(LamCell), col(0), row(0)
{
	content_ptr = NULL;
};

AstralPoint::~AstralPoint()
{
	/*delete owner_ptr;
	delete content_ptr;
	/*/
	setContentPointer(NULL);
	
}

AstralPoint::AstralPoint(mpn col_, mpn row_): owner_type(LamCell)
{
	
	setCol(col_);
	setRow(row_);
	content_ptr = NULL;
}



const AstralPoint::AstralPointType AstralPoint::getAstralpointType()
{
	return owner_type;
}

void AstralPoint::setAstralPointType(AstralPointType apt)
{
	owner_type = apt;
}

void AstralPoint::setCol(mpn col_)
{
	col = col_;
}

void AstralPoint::setRow(mpn row_)
{
	row = row_;
}

mpn AstralPoint::getCol() const
{
	return col;
}

 mpn AstralPoint::getRow() const
{
	return row;
}

Placeable * AstralPoint::getContentPointer() const
{
	return content_ptr;
}

void AstralPoint::setContentPointer(Placeable * p)
{
	//delete content_ptr;
	content_ptr = p;
}

std::string AstralPoint::toString(bool with_new_lines)
{
	std::string I__ = "";
	if (with_new_lines) {
		return hexy_string(getContentPointer() != NULL ? I__ = getContentPointer()->toString() : I__ = DEFAULT_STR);
	}
	else {
		return hexy_string2(getContentPointer() != NULL ? I__ = getContentPointer()->toString() : I__ = DEFAULT_STR);
	}
	
}

 bool operator<(const AstralPoint &  ap, const AstralPoint &  pa)
{

	return ((pa.getCol()< ap.getCol()) && (pa.getRow() < ap.getRow()));
}

bool operator>(const AstralPoint &  ap, const AstralPoint &  pa)
{
	return (pa.getCol() > ap.getCol() && pa.getRow() > ap.getRow());
}

const Lam::AstralAreaType Lam::getType()
{
	return type;
}

Connector::Connector(void * owner1, void * owner2)
{
	owner_1 = owner1;
	owner_2 = owner2;
}

void Connector::setNewOwner(bool flag, void * newOwner)
{
	flag ? owner_2 = newOwner : owner_1 = newOwner;
}

void Connector::setNewOwner(void * owner, void * newOwner)
{
	owner_2 == owner ? setNewOwner(true, newOwner) : setNewOwner(false, newOwner);
}

void * Connector::getOwner(bool flag)
{
	return flag ? owner_2 : owner_1;
}

NativeEnergons::NativeEnergons()
{
	setFeels("abcdefg");
	setInteracts("bcdg");
	setIgnores("aef");
}

char * NativeEnergons::getFeels()
{
	return feels;
}

char * NativeEnergons::getInteracts()
{
	return interacts;
}

char * NativeEnergons::getIgnores()
{
	return ignores;
}

void NativeEnergons::setFeels(char * f)
{
	feels = f;
}

void NativeEnergons::setInteracts(char * i)
{
	interacts = i;
}

void NativeEnergons::setIgnores(char * i)
{
	ignores = i;
}

AstralWeather::AstralWeather(AstralPoint * p_, Phenomenon ph_)
{
	//p = new AstralPoint();
	setAstralPoint(p_);
	setPhenomenon(ph_);
}

AstralWeather::AstralWeather(AstralPoint * p_)
{
	setAstralPoint(p_);
	setPhenomenon(Phenomenon::Calm);
}

AstralWeather::AstralWeather()
{
	setAstralPoint(NULL);
}

AstralWeather::~AstralWeather()
{
	//delete p;
	setAstralPoint(NULL);
}

AstralWeather::Phenomenon AstralWeather::getPhenomenon()
{
	return phenomenon;
}

void AstralWeather::setPhenomenon(Phenomenon p)
{
	phenomenon = p;
}

AstralPoint * AstralWeather::getAstralPoint()
{
	return p;
}

void AstralWeather::setAstralPoint(AstralPoint * a)
{
	//delete p;
	p = a;
}

void AstralWeather::levelUp()
{
	setPhenomenon(static_cast<AstralWeather::Phenomenon>((static_cast<int>(getPhenomenon()) + 1) % 9));
}

void AstralWeather::levelDown()
{
	setPhenomenon(static_cast<AstralWeather::Phenomenon>((static_cast<int>(getPhenomenon()) - 1) % 9));
}

std::string AstralWeather::toString(bool shortView)
{
	std::string I__ = "";
	switch (getPhenomenon())
	{
	case (static_cast<Phenomenon>(0)): I__ = FLOW_STR;  break;
	case (static_cast<Phenomenon>(1)): I__ = WIND_STR;  break;
	case (static_cast<Phenomenon>(2)): I__ = FOG_STR;  break;
	case (static_cast<Phenomenon>(3)): I__ = STORM_STR;  break;
	case (static_cast<Phenomenon>(4)): I__ = TORNADO_STR;  break;
	case (static_cast<Phenomenon>(5)): I__ = URAGAN_STR;  break;
	case (static_cast<Phenomenon>(6)): I__ = CALM_STR;  break;
	case (static_cast<Phenomenon>(7)): I__ = SWELL_STR;  break;
	case (static_cast<Phenomenon>(8)): I__ = ISLAND_STR;  break;

	default: I__ = DEFAULT_STR; 
	}

	if (shortView) {
		return I__;
	}
	else {
		return hexy_string(I__);
	}
	
}

Lam * AstralWeatherController::getLam()
{
	return owner;
}

Placeable::Placeable(AstralPoint* ap_ptr)
{
	outerAstralSpace_ptr = ap_ptr;
}

Placeable::~Placeable()
{
	outerAstralSpace_ptr = NULL;
}

std::string Placeable::toString()
{
	return DEFAULT_STR;
}


Containable::Containable(mpn ASpace_width, mpn ASpace_length)
{
	init( abs(ASpace_width), abs(ASpace_length) );
}

Containable::Containable(mpn ASpace_width_or_length)
{
	init(abs(ASpace_width_or_length), abs(ASpace_width_or_length));
}


void Containable::init(mpn a, mpn b)
{
	AstralSpace_length = a;
	AstralSpace_width = b;

	AstralCellVector* rowY = new AstralCellVector();
	for (mpn i = 0; i < a; i++) {
		for (mpn j = 0; j < b; j++) {
			rowY->push_back(AstralCell(AstralPoint(i, j), AstralWeather(&AstralPoint(i, j))));
		}
		AstralSpace.push_back(*rowY);
		rowY->resize(0);
	}
	delete rowY;

	
}

	Containable::Containable()
{
	srand(time(0));
	AstralSpace_length = rand()%4 + 1;
	srand(time(0));
	AstralSpace_width = rand()%4 + 1;
	init(AstralSpace_length, AstralSpace_width);
}

	std::string Containable::toString()
	{
		std::string ss = "";
		
		mpn xx = AstralSpace_width * 3 + 2;
		mpn yy = AstralSpace_length * 2 + 2;

		for (unsigned i = 0; i < xx; i++) {
			for (unsigned j = 0; j < yy; j++) {
				ss += " ";
			}
			ss += "\n";
		}
		mpn pos = 0;
		mpn it = 1;

		//fisrt pattern
		while (pos != yy)
		{
			ss.insert(it, "   +-+");
			it = it + 6;
			pos++;
		}

		//second pattern
		for (mpn line = 1; line < xx-1; line=line+2) {
			for (mpn pos = 1; pos < yy; pos= pos + 4) {
				ss.insert(pos, "+-+");
			}
		}

		//third pattern
		for (mpn line = 2; line < xx - 2; line = line + 2) {
			for (mpn pos = 0; pos < yy; pos = pos + 4) {
				pos==0 ? ss.insert(pos, "+") : ss.insert(pos, "+-+");
			}
		}

		//ss[xx + 5 + (it + 1)*xx] = AstralSpace[i][j].astralPoint.toString()[7];

		return ss;
	}
