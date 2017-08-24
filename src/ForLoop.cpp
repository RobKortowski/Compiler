/* by Robert Kortowski 221450@student.pwr.edu.pl */
#include <iostream>
#include "ForLoop.h"
#include "Singleton.h"
#include "Identifier.h"
#include "Gets.h"
#include "Value.h"
#include "Condition.h"
#include "Expression.h"

using namespace std;

ForLoop::ForLoop(int a){
	type = a;
}
void ForLoop::setFirstValueId(int a){
	firstValueId = a;
}
void ForLoop::setSecondValueId(int a){
	secondValueId = a;
}

void ForLoop::setInsiderId(int a){
	insiderId = a;
}
void ForLoop::setPidId(int a){
	pidId = a;
}

void ForLoop::appendCode(){
	Singleton& s = Singleton::getInstance();

	Variable* vio = new Variable(s.getMem());
	int boundPID = s.addVariable(vio);

	Identifier* i2 = new Identifier(1);
	i2->setFirstValueId(boundPID);
	int idId2 = s.addIdentifier(i2); // temp local variable bound

	Value* v2 = new Value(2);
	v2->setChild(idId2);
	int valId2 = s.addValue(v2);

	Expression* e2 = new Expression(1);
	e2->setFirstValueId(secondValueId);
	int expId2 = s.addExpression(e2);

	Gets* ge2 = new Gets();	
	ge2->setExpressionId(expId2);
	ge2->setIdId(idId2);
	ge2->setNextId(-1);
//########################################33 end of bound value prep 


	Identifier* i = new Identifier(1);
	i->setFirstValueId(pidId);
	int idId = s.addIdentifier(i);
	//i->setInitiated();
	
	Value* v = new Value(2);
	v->setChild(idId);
	int valId = s.addValue(v);
	
	Expression* e = new Expression(1);
	e->setFirstValueId(firstValueId);
	int expId = s.addExpression(e);
	
	Gets* ge = new Gets();	
	ge->setExpressionId(expId);
	ge->setIdId(idId);
	ge->setNextId(-1);
	
	Condition* con;
	if(type == 1)
		con = new Condition(5);
	else 
		con = new Condition(6);


	//con = new Condition(2);

	con->setFirstValueId(valId);
	con->setSecondValueId(valId2);


// actual code 
	ge2->appendCode();
	ge->appendCode();
	
	int repEtq = s.getEtq();
	int finEtq = s.getEtq();
	int endEtq = s.getEtq();
	s.append(repEtq);
	con->appendCode(finEtq);
	s.append("JUMP", endEtq);
	s.append(finEtq);
	s.getMember(insiderId)->appendCode();

	i->appendCode();
	s.append(s.cmd("LOAD", 1));
	if(type == 1){
		s.append(s.cmd("INC", 1));
	
	//	cout << "dsdsdssd11111111111111111111111dssssssssssssssssssss"<< endl;	
	}
	else if(type == 2){
		s.append(s.cmd("JZERO", 1), endEtq);
		s.append(s.cmd("DEC", 1));
	//	cout << "dsdsdssddssssssssssssssssssss"<< endl;	
	}
	s.append(s.cmd("STORE", 1));

	s.append("JUMP", repEtq);
	s.append(endEtq);
	
	
	if(getNextId()>=0)
 		s.getMember(getNextId())->appendCode();
}
