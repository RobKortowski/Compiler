/* by Robert Kortowski 221450@student.pwr.edu.pl */
#include <iostream>
#include "While.h"
#include "Singleton.h"
#include "Condition.h"

using namespace std;

While::While(){
	setInsiderId(-1);
}

void While::setInsiderId(int a){
	insiderId = a;
}

void While::setConditionId(int a){
	conditionId = a;
}

void While::appendCode(){
	Singleton& s = Singleton::getInstance();
	int repEtq = s.getEtq();
	int finEtq = s.getEtq();
	int endEtq = s.getEtq();

	s.append(repEtq);
	s.getCondition(conditionId)->appendCode(finEtq);
	s.append("JUMP", endEtq);
	s.append(finEtq);
	s.getMember(insiderId)->appendCode();
	s.append("JUMP", repEtq);
	s.append(endEtq);
	if(getNextId()>=0)
 		s.getMember(getNextId())->appendCode();
}
