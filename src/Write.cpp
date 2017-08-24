/* by Robert Kortowski 221450@student.pwr.edu.pl */
#include <iostream>
#include "Write.h"
#include "Singleton.h"
#include "Value.h"

using namespace std;

Write::Write(){}

void Write::setValueId(int a){
	valueId = a;
}

void Write::appendCode(){
	Singleton& s = Singleton::getInstance();
	Value* v = s.getValue(valueId);
	v->appendCode(4);
	s.append(s.cmd("PUT", 4));
	if(getNextId()>=0)
 		s.getMember(getNextId())->appendCode();
}
