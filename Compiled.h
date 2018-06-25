/*
 * Compiled.h
 *
 *  Created on: May 23, 2018
 *      Author: franklondo
 */

#ifndef COMPILED_H_
#define COMPILED_H_

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <typeinfo>
#include <string>
#include <sstream>
#include <vector>
#include <dirent.h>
#include "Reader.h"


#define MAX_COMP 10

typedef std::string String;

void printDirectory(String);

struct Base {
	Reader read;
	String name, value, modifier;
	Base() : read() {}
	virtual ~Base() {}
};

struct TemplateStruct {
	String name[MAX_COMP];
};

struct Positional {
	int location, curInd;
	String value[MAX_COMP];
	Positional() : location(0), curInd(0) {}
	void add(String& sin) {value[curInd++] = sin;}
	void Print() {for(int ui = 0; ui < curInd; ui++) {std::cout << value[ui] << "\t";}std::cout << std::endl;}
	virtual ~Positional() {}
};

class Compiled {
	bool valid;
public:
	static int baseInd, basePos, templInd, templPos, posPos, posInd;
	Positional Postions[MAX_COMP];
	Base Bases[MAX_COMP];
	TemplateStruct Templates[MAX_COMP*10];
	Compiled();
	virtual ~Compiled();
	void Print();
	bool isValid(String&);
	bool isValid(int);
	void addBase(String&, String&, String&, bool);
	void addPosition(int, String&);
	void addTemplate(bool, std::vector<String>*);
};

#endif /* COMPILED_H_ */
