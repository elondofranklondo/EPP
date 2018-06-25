/*
 * Enterpret.cpp
 *
 *  Created on: May 20, 2018
 *      Author: franklondo
 */
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <typeinfo>
#include <string>
#include <sstream>
#include "Enterpret.h"
#include "Commands.h"
#include "ArgHandle.h"

typedef std::string String;

//int Enterpret::lineCnt = 0;
bool Enterpret::onFlag = false;
String Enterpret::onDeck = "";
String Enterpret::rawOnDeck = "";
String Enterpret::inProcess = "";
Commands Enterpret::com;
Command* Enterpret::cptr;

Enterpret::Enterpret(Reader* inn, Compiled* inp) {
	try {
		if (onFlag) {throw false;}
		else {
			onFlag = true;
			rp = inn;
			pp = inp;
			vsize = 0;
			sbs = 0;
			sbc = 0;
			vptr = &sepBySpace;
			com.setCompiler(inp);
			cptr = NULL;
//			std::cout << "Ready to Enterp" << std::endl;
			}
	} catch (bool ofl) {
		std::cout << "ERROR: Enterpreter already running" << std::endl;
	}
}

Enterpret::~Enterpret() {
	onFlag = false;
}

///////////////////////////////////////////////////
void Enterpret::ProcessLine(String& in) {

	std::cout << "Processing Line:" << in << std::endl;


	String comPar,comArg,comComma, activeCom, inn;
	size_t begp,endp,difp,begs;

	begp = in.find_first_of("(");
	endp = in.find_first_of(")");


	if ((begp == String::npos) && (endp == String::npos)) {
		inn = in;
		comPar = "";
	} else {
		difp = endp - begp;
		inn = in.substr(0,begp) + in.substr(endp+1);
		comPar = in.substr(begp+1,difp-1);
		comPar = this->replaceinString(comPar, " ", "");
	}

	begs = inn.find_first_of(" ");
	activeCom = inn.substr(0,begs);
	comArg = inn.substr(begs+1);
	comArg = this->replaceinString(comArg, " ", "");

	if (this->com.findInd(activeCom, comPar, &cptr)) {
			vptr = &sepByComma;
			this->split(comArg, ",", vptr);
			sbc = vsize;
//			std::cout << "Process:" << comArg << std::endl;
			for (unsigned i=0; i < sbc; i++) {
//				std::cout << "Comma Arg: " << sepByComma[i] << std::endl;
				cptr->execute(comPar,sepByComma[i]);
			}
	} else {
		std::cout << "Command Not Found: " << activeCom << std::endl;
	}
}
void Enterpret::Process() {
	String sig = "##RULEFILE##";
	rawOnDeck = rp->getnextline();
	size_t ind;
	if (sig.compare(rawOnDeck) == 0) {
		for(int i = 1; i < rp->getlineCnt(); i++) {
			rawOnDeck = rp->getnextline();
			ind = rawOnDeck.find_first_of(";");
			if (ind != String::npos) {
				onDeck = rawOnDeck.substr(0,ind);
				this->ProcessLine(onDeck);
			} else {
				std::cout << "ERROR: No terminator for line:" << rawOnDeck << std::endl;
			}
		}
	} else{
		std::cout << "ERROR: Rule File Missing Signature" << std::endl;
	}
}
void Enterpret::split(const String& str, const String& delimiter, std::vector<String>* invec) {
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

	vsize = invec->size();
}

String Enterpret::replaceinString(String& str, String tofind, String toreplace) {
        size_t position = 0;
        for ( position = str.find(tofind); position != std::string::npos; position = str.find(tofind,position) )
        {
                str.replace(position ,1, toreplace);
        }
        return(str);
}


