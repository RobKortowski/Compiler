/* by Robert Kortowski 221450@student.pwr.edu.pl */
#include <iostream>
#include "Read.h"
#include "Singleton.h"
#include "Value.h"

using namespace std;

Read::Read(){}

void Read::setId(int a){
	id = a;
}

void Read::appendCode(){
	Singleton& s = Singleton::getInstance();
	Identifier* i = s.getIdentifier(id);	
	s.append(s.cmd("GET", 4));
	i->appendCode();
	s.append(s.cmd("STORE", 4));
	if(getNextId()>=0)
 		s.getMember(getNextId())->appendCode();
}
