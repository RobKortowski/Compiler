/* by Robert Kortowski 221450@student.pwr.edu.pl */
#include <iostream>
#include "Singleton.h"
#include "Identifier.h"
#include <cln/cln.h>
#include <sstream>
using namespace std;

Identifier::Identifier(int a){
	type = a;
}
void Identifier::setFirstValueId(int a){
	firstValueId = a;
}
void Identifier::setSecondValueId(int a){
	secondValueId = a;
}

void Identifier::setInitiated(){	
	Singleton& s = Singleton::getInstance();
	if(type == 1){
		s.getVariable(firstValueId)->initiated = true;
	}
}

void Identifier::checkVisible(int yylineno){
	Singleton& s = Singleton::getInstance();
	if(type == 1 || type == 3 || type == 2){
		if(s.getVariable(firstValueId)->local && !(s.getVariable(firstValueId)->visible)){	
			stringstream err;
			err << "[Line "<<yylineno<<"] ERROR: " << "Undeclareded variable: " << s.getStringName(firstValueId);
			throw  err.str();
		}
	}
	if(type == 2){	
		if(s.getVariable(secondValueId)->local && !(s.getVariable(secondValueId)->visible)){	
			stringstream err;
			err << "[Line "<<yylineno<<"] ERROR: " << "Undeclaredeed variable: " << s.getStringName(secondValueId);
			throw  err.str();
		}
	}
}

void Identifier::checkPidDependant(int p, int yylineno){
	Singleton& s = Singleton::getInstance();
	if(type == 1){
		if(firstValueId == p){
			stringstream err;
			err << "[Loop ending with line "<<yylineno<<"] ERROR: " << "Using local iterator "<< s.getStringName(p) <<" to self-initiate." ;
			throw  err.str();
		}
	}else if(type == 2){
		if(secondValueId == p){
			stringstream err;
			err << "[Loop ending with line "<<yylineno<<"] ERROR: " << "Using local iterator "<< s.getStringName(p) <<" to self-initiate." ;
			throw  err.str();
		}
	}
}

bool Identifier::isArray(){	
	Singleton& s = Singleton::getInstance();
	return s.getVariable(firstValueId)->isArray();	
}

void Identifier::checkInitiated(int yylineno){	
	Singleton& s = Singleton::getInstance();
	if(type == 1){
		if(!(s.getVariable(firstValueId)->initiated)){	
			stringstream err;
			err << "[Line "<<yylineno<<"] ERROR: " << "Usage of uninitiated variable: " << s.getStringName(firstValueId);
			throw  err.str();
		}
	}else if(type == 2){	
		if(!(s.getVariable(secondValueId)->initiated)){	
			stringstream err;
			err << "[Line "<<yylineno<<"] ERROR: " << "Usage of uninitiated variable: " << s.getStringName(secondValueId);
			throw  err.str();
		}
	}
}

void Identifier::checkLocal(int yylineno){	
	Singleton& s = Singleton::getInstance();
	if(type == 1){
		if(s.getVariable(firstValueId)->local){	
			stringstream err;
			err << "[Line "<<yylineno<<"] ERROR: " << "Changing local iterator: " << s.getStringName(firstValueId);
			throw  err.str();
		}
	}
}

void Identifier::add(int a){
	Singleton& s = Singleton::getInstance();
	string com = s.cmd("INC",0);
	for(int i = 0; i < a ; i++){
		s.append(com);
	}
}
void Identifier::appendCode(){
	Singleton& s = Singleton::getInstance();
	if(type == 1){
		//s.append(s.cmd("ZERO", 0));
		cln::cl_I mem = s.getVarsMem(firstValueId);
		s.loadNumber(mem, 0);
	}else if(type == 2){
		cln::cl_I mem = s.getVarsMem(firstValueId);		
		s.loadNumber(mem, 1);
		mem = s.getVarsMem(secondValueId);
		s.loadNumber(mem, 0);
		/*if (s.getVariable(secondValueId)->local){
			s.append(s.cmd("DEC", 1));
		}*/
		s.append(s.cmd("ADD", 1));
		s.append(s.cmd("COPY", 1));
	}else if(type == 3){
		cln::cl_I mem = s.getVarsMem(firstValueId);			
		s.loadNumber(mem, 1);
		s.append(s.cmd("ZERO", 0));
		s.append(s.cmd("STORE", 1));
		cln::cl_I lit = s.getLiteral(secondValueId);			
		s.loadNumber(lit, 1);
		s.append(s.cmd("ADD", 1));
		s.append(s.cmd("COPY", 1));
	}
}
