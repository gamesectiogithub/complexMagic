
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

