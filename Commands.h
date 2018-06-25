/*
 * Commands.h
 *
 *  Created on: May 21, 2018
 *      Author: franklondo
 */

#ifndef COMMANDS_H_
#define COMMANDS_H_

#define MAX_RULES 20

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <typeinfo>
#include <string>
#include <vector>
#include <stdexcept>
#include <sstream>
#include "Compiled.h"

typedef std::string String;

class Command {
protected:
	String name;
	std::vector<String> sepByPlus, paramVec;
public:
	String getName(){ return name;}
	static Compiled* pp;
	Command();
	virtual ~Command();
	void split(const String& str, const String& delimiter, std::vector<String>* invec);
	virtual void execute(String&, String&);
	void Print();
};

class Define : public Command {
public:
	Define();
	void execute(String&, String&);
};
class Always : public Command {
public:
	Always();
	void execute(String&, String&);
};
class Template : public Command {
public:
	Template();
	void execute(String&, String&);
};

class Commands {
public:
	static int comnum,compos;
	static Command* cmds[MAX_RULES];
	Commands();
	void setCompiler(Compiled*);
	bool findInd(String&, String&, Command**);
	void setup();
	void Print();
	virtual ~Commands();
};

#endif /* COMMANDS_H_ */
