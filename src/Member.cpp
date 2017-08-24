/* by Robert Kortowski 221450@student.pwr.edu.pl */
#include <iostream>
#include "Member.h"


using namespace std;

Member::Member(){}

void Member::setId(int a){
	id = a;
	return;
}

int Member::getId(){
	return id;
}

void Member::setNextId(int a){
	nextId = a;
	return;
}

int Member::getNextId(){
	return nextId;
}

/*void Member::setInsiderId(int a){
	insiderId = a;
	return;
}*/
