/*
 * Reader.cpp
 *
 *  Created on: May 9, 2018
 *      Author: franklondo
 */
#include <fstream>
#include <iostream>
#include <string>

#include "Reader.h"

typedef std::string String;

Reader::Reader() {
	active = false;
	Fname = "";
	lineCnt = 0;
	linepos = 0;
}

Reader::Reader(String innStr) {
	active = false;
	Fname = "";
	lineCnt = 0;
	linepos = 0;
	this->setfilePath(innStr);
}

Reader::~Reader() {
	// TODO Auto-generated destructor stub
}

// METHODS

void Reader::setfilePath(String inStr) {
	Fname = inStr;
	lineCnt = 0;
	linepos = 0;
	this->ReadFile();
	active = true;
}
void Reader::ReadFile() {
	String line;
	String* ptr = &Fname;
	std::ifstream myfile;
	myfile.open((*ptr).c_str());

	if (myfile.is_open())
	  {
	    while ( std::getline (myfile,line) )
	    {
	      File[lineCnt] = line;
	      lineCnt++;
	    }
	    myfile.close();
	  }

	  else std::cout << "Unable to open file";
}

void Reader::PrintContents() {
	for(int i = 0; i < lineCnt; ++i) {
		std::cout << File[i] << std::endl;
	}

}
String Reader::getnextline() {
	String getter;
	if (linepos == lineCnt) {
		linepos = 0;
		return "done";
	} else {
		getter = File[linepos];
		linepos++;
		return getter;
	}
}
