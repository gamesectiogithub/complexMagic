#pragma once
#include "stdafx.h"

class ModelObject
{
protected:
	string name = "Something";
	int thisnum;

public:
	static int classNumber;

public:
	ModelObject() {
		setName("ModelObject");
		setNumber(getNumber() + 1);
		thisnum = getNumber();
	}
	~ModelObject();

	static int getNumber() {
		return classNumber;
	}

	static int setNumber(int i) {
		classNumber = i;
	}

	virtual string getName() {
		return name;
	}

	// TODO: make it =0
	virtual void setName(string s) {
		name = s + "_" + to_string(thisnum);
	}
	

};

