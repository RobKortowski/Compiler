/* by Robert Kortowski 221450@student.pwr.edu.pl */
#include <iostream>
#include "Condition.h"
#include "Singleton.h"
#include "Value.h"

using namespace std;

Condition::Condition(int a){
	type = a;
}
void Condition::setFirstValueId(int a){
	firstValueId = a;
}
void Condition::setSecondValueId(int a){
	secondValueId = a;
}
void Condition::appendCode(int etq){
	Singleton& s = Singleton::getInstance();
	Value* v1 = s.getValue(firstValueId);	
	Value* v2 = s.getValue(secondValueId);
	v1->appendCode(3);
	v2->appendCode(4);
	if(type == 1){
		int e1 = s.getEtq();
		int e2 = s.getEtq();
		s.append(s.cmd("ZERO", 0));	
		s.append(s.cmd("STORE", 4));
		s.append(s.cmd("LOAD", 2));
		s.append(s.cmd("STORE", 3));
		s.append(s.cmd("SUB", 2));
		s.append(s.cmd("JZERO", 2), e1);
		s.append("JUMP", e2);
		s.append(e1);
		s.append(s.cmd("LOAD", 2));
		s.append(s.cmd("STORE", 4));
		s.append(s.cmd("SUB", 2));
		s.append(s.cmd("JZERO", 2), etq);
		s.append(e2);
	}else if(type == 2){	
		int e1 = s.getEtq();
		int e2 = s.getEtq();
		s.append(s.cmd("ZERO", 0));	
		s.append(s.cmd("STORE", 4));
		s.append(s.cmd("LOAD", 2));
		s.append(s.cmd("STORE", 3));
		s.append(s.cmd("SUB", 2));
		s.append(s.cmd("JZERO", 2), e1);
		s.append("JUMP", etq);
		s.append(e1);
		s.append(s.cmd("LOAD", 2));
		s.append(s.cmd("STORE", 4));
		s.append(s.cmd("SUB", 2));
		s.append(s.cmd("JZERO", 2), e2);
		s.append("JUMP", etq);
		s.append(e2);
	
	}else if(type == 3){
		int e2 = s.getEtq();
		s.append(s.cmd("ZERO", 0));	
		s.append(s.cmd("STORE", 3));
		s.append(s.cmd("SUB", 4));	
		s.append(s.cmd("JZERO", 4), e2);
		s.append("JUMP", etq);
		s.append(e2);

	}else if(type == 4){
		int e2 = s.getEtq();
		s.append(s.cmd("ZERO", 0));	
		s.append(s.cmd("STORE", 4));
		s.append(s.cmd("SUB", 3));	
		s.append(s.cmd("JZERO", 3), e2);
		s.append("JUMP", etq);
		s.append(e2);
	}else if(type == 5){	
		int checkEven = s.getEtq();
		s.append(s.cmd("ZERO", 0));
		s.append(s.cmd("STORE", 4));
		s.append(s.cmd("INC", 0));
		s.append(s.cmd("STORE", 3));
		s.append(s.cmd("SUB", 4));	
		s.append(s.cmd("JZERO", 4), checkEven);
		s.append("JUMP", etq);
		s.append(checkEven);	
		s.append(s.cmd("DEC", 0));
		s.append(s.cmd("SUB", 3));	
		s.append(s.cmd("JZERO", 3), etq);
	
	}else if(type == 6){
		int checkEven = s.getEtq();
		s.append(s.cmd("ZERO", 0));
		s.append(s.cmd("STORE", 3));
		s.append(s.cmd("INC", 0));
		s.append(s.cmd("STORE", 4));
		s.append(s.cmd("SUB", 3));	
		s.append(s.cmd("JZERO", 3), checkEven);
		s.append("JUMP", etq);
		s.append(checkEven);	
		s.append(s.cmd("DEC", 0));
		s.append(s.cmd("SUB", 4));	
		s.append(s.cmd("JZERO", 4), etq);
	}
}
