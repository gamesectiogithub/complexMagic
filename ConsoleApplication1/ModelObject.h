#pragma once
#include "stdafx.h"



class ModelObject
{
protected:
	std::string name;
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

	virtual std::string getName() {
		return name;
	}

	// TODO: make it =0
	virtual void setName(std::string s) {
		name = s + "_" + std::to_string(thisnum);
	}
	

};

