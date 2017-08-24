/* by Robert Kortowski 221450@student.pwr.edu.pl */
#include <iostream>
#include "IfLoop.h"
#include "Singleton.h"
#include "Condition.h"

using namespace std;

IfLoop::IfLoop(){
	setInsiderId(-1);
	setSecInsiderId(-1);
}

void IfLoop::setInsiderId(int a){
	insiderId = a;
}

void IfLoop::setSecInsiderId(int a){
	secInsiderId = a;
}

void IfLoop::setConditionId(int a){
	conditionId = a;
}

void IfLoop::appendCode(){
	Singleton& s = Singleton::getInstance();
	int finEtq = s.getEtq();
	int endEtq = s.getEtq();
	s.getCondition(conditionId)->appendCode(finEtq);
 	s.getMember(secInsiderId)->appendCode();
	s.append("JUMP", endEtq);
	s.append(finEtq);
	s.getMember(insiderId)->appendCode();
	s.append(endEtq);
	if(getNextId()>=0)
 		s.getMember(getNextId())->appendCode();
}
