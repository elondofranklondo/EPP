/*
 * Reader.h
 *
 *  Created on: May 9, 2018
 *      Author: franklondo
 */

#ifndef READER_H_
#define READER_H_
#define STRINGSIZES 100

#include <fstream>
#include <iostream>
#include <string>

typedef std::string String;

class Reader {
private:
	int lineCnt,linepos;
	String File[STRINGSIZES];
	String Fname;
public:
	bool active;
	Reader();
	Reader(String);
	virtual ~Reader();
	void ReadFile();
	void setfilePath (String);
	void PrintContents();
	String getnextline();
	int getlineCnt(){return lineCnt;};

};

#endif /* READER_H_ */
