/* by Robert Kortowski 221450@student.pwr.edu.pl */
#include <iostream>
#include "Gets.h"
#include "Singleton.h"
#include "Expression.h"
#include "Identifier.h"

using namespace std;

Gets::Gets(){

}
void Gets::setExpressionId(int a){
	expressionId = a;
}

void Gets::setIdId(int a){
	idId = a;
}

void Gets::appendCode(){
	Singleton& s = Singleton::getInstance();
	Expression* e = s.getExpression(expressionId);
	Identifier* i = s.getIdentifier(idId);
	e->appendCode();
	i->appendCode();
 	s.append(s.cmd("STORE", 4));
	
	if(getNextId()>=0)
 		s.getMember(getNextId())->appendCode();
}

void Gets::appendCode(bool a){
	Singleton& s = Singleton::getInstance();
	Expression* e = s.getExpression(expressionId);
	Identifier* i = s.getIdentifier(idId);
	e->appendCode();
	i->appendCode();
 	s.append(s.cmd("INC", 4));
 	s.append(s.cmd("STORE", 4));
	
	if(getNextId()>=0)
 		s.getMember(getNextId())->appendCode();
}
