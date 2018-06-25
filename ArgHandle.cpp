/*
 * ArgHandle.cpp
 *
 *  Created on: May 17, 2018
 *      Author: franklondo
 */
#include "ArgHandle.h"
#include <string>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <map>

typedef std::string String;

ArgHandle::ArgHandle(int act, char** vecarg) {
	ac = act;
	av = vecarg;

}

ArgHandle::~ArgHandle() {
	// TODO Auto-generated destructor stub
}

void ArgHandle::PrintArgs() {

	for(int i = 0; i < ac; ++i){
		std::cout << av[i] << std::endl;
	}
}

void ArgHandle::addArg(String s, int i) {
	String temp_s;
	Erg e;

	e.name = s;
	e.reqFlag = false;
	temp_s = std::to_string(i);

	log[temp_s] = e;
//	std::cout << "position:" << i << "\tstring:" << s << std::endl;
}

void ArgHandle::addArg(String s, String i, bool bflag) {
	Erg e;
	e.name = s;
	e.reqFlag = bflag;

	log[i] = e;
//	std::cout << "flag:" << i << "\tstring:" << s << std::endl;
	ret[s] = "false";
}

void ArgHandle::finalize() {
	String temp_arg, t2, ti, hold;
	int pos = 1;
	Erg tes;

	for(int i = 1; i < ac; ++i){
		if (av[i][0] == '-') {

			tes = log.find(av[i])->second;
			t2 = tes.name;

			if (tes.reqFlag) {
				ret[t2] = "true";
			} else {
				hold = std::string(av[i+1]);
				ret[t2] = hold;
				i++;
			}
		} else {
			ti = std::to_string(pos);
			tes = log.find(ti)->second;
			t2 = tes.name;
			hold = std::string(av[i]);
			ret[t2] = hold;
			pos++;
		}
	}
}

//template<typename T>
//T ArgHandle::retrieve(String s) {
//	T temp = ret.find(s)->second;
//	return "woof";
//}
