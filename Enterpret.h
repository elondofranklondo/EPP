/*
 * Enterpret.h
 *
 *  Created on: May 20, 2018
 *      Author: franklondo
 */

#ifndef ENTERPRET_H_
#define ENTERPRET_H_

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <typeinfo>
#include <string>
#include <sstream>
#include <vector>

#include "Reader.h"
#include "Commands.h"
#include "Compiled.h"
#include "ArgHandle.h"


typedef std::string String;

class Enterpret {
//	static int lineCnt;
	static bool onFlag;
	Reader* rp;
	Compiled* pp;
	static String onDeck, rawOnDeck, inProcess;
	std::vector<String> sepBySpace, sepByComma;
	std::vector<String>::size_type vsize,sbs,sbc;
	std::vector<String>* vptr;
	static Commands com;
	static Command* cptr;
	void ProcessLine(String&);
public:
	Enterpret(Reader*, Compiled*);
	virtual ~Enterpret();
	String replaceinString(String&, String, String);
	void Process();
	void split(const String& str, const String& delimiter, std::vector<String>* invec);

};

#endif /* ENTERPRET_H_ */
