/*
 * Commands.cpp
 *
 *  Created on: May 21, 2018
 *      Author: franklondo
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <typeinfo>
#include <string>
#include <sstream>
#include <vector>
#include <stdexcept>
#include "Commands.h"
#include "Compiled.h"
#include "ArgHandle.h"

typedef std::string String;

int Commands::comnum = 0;
int Commands::compos = 0;
Compiled* Command::pp = NULL;
Command* Commands::cmds[MAX_RULES] = {NULL};


////////Parent Command////////////////////////////

Command::Command() {
	Commands::comnum++;
}

Command::~Command() {
	// TODO Auto-generated destructor stub
}

void Command::execute(String&, String&) {
	std::cout << "Error Command Not Created" << std::endl;
//	return true;
}

void Command::Print() {
	std::cout << "Name: " << name << std::endl;
}
void Command::split(const String& str, const String& delimiter, std::vector<String>* invec) {
	invec->clear();

	typename String::size_type start = 0;
	auto pos = str.find_first_of(delimiter, start);
	while(pos != String::npos) {
	        if(pos != start) // ignore empty tokens
	        	invec->emplace_back(str, start, pos - start);
	        start = pos + 1;
	        pos = str.find_first_of(delimiter, start);
	    }
	    if(start < str.length()) {// ignore trailing delimiter
	    	invec->emplace_back(str, start, str.length() - start);
	    }

}
////////Childen Commands////////////////////////////
Define::Define() {
	name = "Define";
}
Always::Always() {
	name = "Always";
}
Template::Template() {
	name = "Template";
}
void Define::execute(String& str1, String& str2) {
	// Boiler plate : this separates the parameters into strings
	std::cout << "Executing DEFINE with parameters of " << str1 << "\tArg: " << str2 << std::endl;
	this->split(str1 , ",", &paramVec);
	bool errParse = false;

	// Set up the defaults parameters
	String t1 = "arg"; //1
	String t2 = "";    //2
	String t3 = "";    //3
	bool f1 = false;



	switch (paramVec.size()) {
		case 0: {
			break;
		}
		case 1: {
			if (t1.compare(paramVec[0]) != 0) {
				f1 = true;
				t2 = paramVec[0];
			}
			break;
		}
		case 2: {
			if ((t1.compare(paramVec[0]) != 0) && (t3.compare(paramVec[1]) != 0)) {
				f1 = true;
				t2 = paramVec[0];
				t3 = paramVec[1];
			} else {
				errParse = true;
			}
			break;
		}
		default: {
			std::cout << "Error with Arguemnts for define" << std::endl;
			errParse = true;
			break;
		}
	}
	if (!errParse) {pp->addBase(str2,t2,t3,f1);}
	else {std::cout << "Skipping over this command" << std::endl;}
}

void Always::execute(String& str1, String& str2) {
	// Boiler plate : this separates the parameters into strings
	std::cout << "Executing ALWAYS with parameters of " << str1 << "\tArg: " << str2 << std::endl;
	this->split(str1 , ",", &paramVec);
	bool errParse = false;

	// Set up the defaults parameters
	int i_t1 = 0; //1

	switch (paramVec.size()) {
		case 0: {
			break;
		}
		case 1: {
			try {
				i_t1 = std::stoi(str1);
				std::cout << "Position: " << i_t1 << std::endl;
			}
			catch (const std::invalid_argument& ia) {
				std::cout << "Invalid argument: " << ia.what() << "(" << str1 << ")" << std::endl;
			}
			break;
		}
		default: {
			std::cout << "Error with Arguemnts for Always" << std::endl;
			errParse = true;
			break;
		}
	}
	if (!errParse) {pp->addPosition(i_t1,str2);}
	else {std::cout << "Skipping over this command" << std::endl;}
}
void Template::execute(String& str1, String& str2) {
	// Boiler plate : this separates the parameters into strings
	std::cout << "Executing TEMPLATE with parameters of " << str1 << "\tArg: " << str2 << std::endl;
	this->split(str1 , ",", &paramVec);
	this->split(str2 , "+", &sepByPlus);
	bool errParse = false;

	// Set up the defaults parameters
	String t1 = "all"; //1
	String t2 = "original"; //1

	bool f1 = false;



	switch (paramVec.size()) {
		case 0: {
			break;
		}
		case 1: {
			if (t1.compare(paramVec[0]) != 0) {
				if (t2.compare(paramVec[0]) == 0){
				f1 = true;
				} else {
				errParse = true;
				}
			}
			break;
		}
		default: {
			std::cout << "Error with Arguemnts for define" << std::endl;
			errParse = true;
			break;
		}
	}
	if (!errParse) {pp->addTemplate(f1, &sepByPlus);}
	else {std::cout << "Skipping over this command" << std::endl;}
}
////////Command Holder////////////////////////////

Commands::Commands() {
	this->setup();
}
Commands::~Commands() {
	compos = 0;
	for (compos; compos < comnum; compos++) {
		delete cmds[compos];
	}
}
////////////////////////////////

void Commands::setup() {
	int temp = 0;
	Commands::cmds[temp++] = new Define();
	Commands::cmds[temp++] = new Always();
	Commands::cmds[temp++] = new Template();
}
void Commands::setCompiler(Compiled* pin) {
	Command::pp = pin;
	this->Print();
}
bool Commands::findInd(String& fin, String& params, Command** cp) {
	String temp;
	compos = 0;
	for (compos; compos < comnum; compos++) {
		temp = cmds[compos]->getName();
		if (fin.compare(temp) == 0) {
			std::cout << "Found Command: " << temp << "\tParams: " << params << std::endl;
			*cp = cmds[compos];
			return true;
		}
	}
	return false;
}
void Commands::Print() {
	compos = 0;
	std::cout << "Commands" << std::endl << "-------" << std::endl;
	for (compos; compos < comnum; compos++) {
		cmds[compos]->Print();
	}
}
