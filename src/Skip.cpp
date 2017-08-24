/* by Robert Kortowski 221450@student.pwr.edu.pl */
#include <iostream>
#include "Skip.h"
#include "Singleton.h"

using namespace std;

Skip::Skip(){}

void Skip::appendCode(){
	Singleton& s = Singleton::getInstance();
	//s.append("skip");

	if(getNextId()>=0)
 		s.getMember(getNextId())->appendCode();
}
