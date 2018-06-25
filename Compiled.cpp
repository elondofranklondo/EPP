/*
 * Compiled.cpp
 *
 *  Created on: May 23, 2018
 *      Author: franklondo
 */
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <typeinfo>
#include <string>
#include <vector>
#include <sstream>
#include <dirent.h>
#include "Compiled.h"
#include "Reader.h"

typedef std::string String;
int Compiled::baseInd = 0;
int Compiled::basePos = 0;
int Compiled::templInd = 0;
int Compiled::templPos = 0;
int Compiled::posInd = 0;
int Compiled::posPos = 0;

void printDirectory(String cdir) {
	DIR* dirp;
	struct dirent* dp;
	dirp = opendir(cdir.c_str());
	while ((dp = readdir(dirp)) != NULL) {
			std::cout << "found file: " << dp->d_name << std::endl;
	}
}

//void Positional::add(String& sin) {
//
//}

Compiled::Compiled() {
}

Compiled::~Compiled() {
	// TODO Auto-generated destructor stub
}
////////////////////////////////////////////
void Compiled::Print() {

	int b,t,p;

	std::cout << "Bases" << std::endl << "-----" << std::endl;
	for (b = 0 ; b < baseInd; b++){
		std::cout << Bases[b].name << std::endl;
	}
	std::cout << std::endl;
	std::cout << "Templates" << std::endl << "--------" << std::endl;
	for (t = 0 ; t < templInd; t++){
		std::cout << Templates[t].name << std::endl;

	}
	std::cout << std::endl;
	std::cout << "Positionals" << std::endl << "--------" << std::endl;
	for (p = 0 ; p < posInd; p++){
		std::cout << Postions[p].location << std::endl;
		Postions[p].Print();
	}
}
bool Compiled::isValid(String& str) {
	int b,t;

	for (b = 0 ; b < baseInd; b++){
		if (str.compare(Bases[b].name) == 0) return false;
	}
//	for (t = 0 ; t < templInd; t++){
//		if (str.compare(Templates[t].name) == 0) return false;
//
//	}

	return true;
}
bool Compiled::isValid(int numin) {
	int t;
	posPos = 0;

	for (t = 0 ; t < posInd; t++){
		if (Postions[t].location == numin) {
			posPos = t;
			return false;
		}

	}

	return true;
}
void Compiled::addBase(String& s1, String& s2, String& s3, bool isfi) {
	std::cout << "adding Base: " << s1 << std::endl << "-----" << std::endl
			<< "1st arg: " << s2 << "\t2nd arg: " << s3 << std::endl;

	if (this->isValid(s1)) {
		Bases[baseInd].name = s1;
		Bases[baseInd].value = s2;
		Bases[baseInd].modifier = s3;
		if (isfi) {
			Bases[baseInd].read.setfilePath(s2);
			Bases[baseInd].read.PrintContents();
		} else {
//			Bases[baseInd].read();
		}
		baseInd++;
	} else {std::cout << "Cant Add Base: " << s1 << std::endl;}
}

void Compiled::addPosition(int i1, String& s2) {
	std::cout << "adding Position: " << i1 << std::endl << "-----" << std::endl
			<< "1st arg: " << s2 << std::endl;

	if (this->isValid(i1)) {
		Postions[posInd].location = i1;
		posPos = posInd;
		posInd++;
	}
	Postions[posPos].add(s2);
}

void Compiled::addTemplate(bool, std::vector<String>* svecp) {
	size_t ts = svecp->size();

	std::cout << "adding Template: ";
	for (size_t ti = 0; ti < ts; ti++) {
		std::cout << svecp->operator [](ti) << " ";
	}
	std::cout << std::endl;
}
