/*
 * ArgHandle.h
 *
 *  Created on: May 17, 2018
 *      Author: franklondo
 */

#ifndef ARGHANDLE_H_
#define ARGHANDLE_H_

#include <string>
#include <sstream>
#include <iostream>
#include <map>
#include <cstdlib>

typedef std::string String;


struct Erg {
	String name;
	bool reqFlag;
};


class ArgHandle {
private:
	int ac;
	char** av;
	std::map<String, Erg> log;
	std::map<String, String> ret;

public:
	ArgHandle(int, char**);
	virtual ~ArgHandle();
	void PrintArgs();
	void addArg(String s, int i);
	void addArg(String s, String i, bool blfag = false);
	void finalize();
	template<typename T>
	T retrieve(String s) {
		String temp = ret.find(s)->second;
		T out;
		std::istringstream ss(temp);
		return ss >> out ? out : 0;
	}

};

#endif /* ARGHANDLE_H_ */
