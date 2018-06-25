//============================================================================
// Name        : EPP.cpp
// Author      : Elondo
// Version     :
// Copyright   : barkwoof
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <typeinfo>
#include <string>
#include <sstream>
#include "Reader.h"
#include "ArgHandle.h"
#include "Enterpret.h"
#include "Compiled.h"

using namespace std;

// FUNCTION DECLARATIONS
void setupArgs(ArgHandle&);

// END FUNCTION DECLARATIONS



int main(int argc, char *argv[]) {
	//printDirectory("../.");
	// Handle arguments
	ArgHandle arHand(argc, argv);
	setupArgs(arHand);

	//Reading in the rule files
	string ruleFile = arHand.retrieve<string>("rulefile");
	Reader rf(ruleFile);

	//Starting up Enterpreter
	Compiled pile;
	Compiled* pptr = &pile;
	Reader* rptr = &rf;
	Enterpret ep(rptr, pptr);
	ep.Process();
	pile.Print();

	return 0;
}

// FUNCTION IMPLEMENTATIONS
void setupArgs(ArgHandle& AH) {
//	AH.PrintArgs();

	AH.addArg("fname", 1);
	AH.addArg("lname", 2);
	AH.addArg("year", "-y");
	AH.addArg("mname", "-m");
	AH.addArg("rulefile", "-f");
	AH.addArg("race", "-r");
	AH.addArg("print", "-p", true);
	AH.finalize();
}

// END FUNCTION IMPLEMENTATIONS
