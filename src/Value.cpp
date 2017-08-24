/* by Robert Kortowski 221450@student.pwr.edu.pl */
#include <iostream>
#include "Value.h"
#include "Singleton.h"
#include "Identifier.h"
#include <sstream>

using namespace std;

Value::Value(int a){
	type = a;
}
void Value::setChild(int a){
	child = a;
}
bool Value::isTwo(){
	if(type == 2){
		return false;
	}else if(type == 1){
		Singleton& s = Singleton::getInstance();
		cln::cl_I lit = s.getLiteral(child);			
		return lit == 2;
	}
}


void Value::checkPidDependant(int p, int yylineno){
	if(type == 2){
		Singleton& s = Singleton::getInstance();
		Identifier* i = s.getIdentifier(child);
		i->checkPidDependant(p, yylineno);
	}
}


void Value::appendCode(int r){
	Singleton& s = Singleton::getInstance();
	if(type == 1){
		cln::cl_I lit = s.getLiteral(child);			
		s.loadNumber(lit,r);
	}else if(type == 2){
		Identifier* i = s.getIdentifier(child);

//					i->checkinitiated();

		i->appendCode();
		s.append(s.cmd("LOAD", r));
	/*	if (s.getVariable(i->firstValueId)->local){
			s.append(s.cmd("DEC", r));
		}*/
	}
}
