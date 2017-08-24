/* by Robert Kortowski 221450@student.pwr.edu.pl */
#include <iostream>
#include "Variable.h"

using namespace std;

Variable::Variable(cln::cl_I m){
	mem = m;
	size = 0;
	initiated = false;
	local = false;
	visible = true;
}

cln::cl_I Variable::getMem(){
	return mem;
}

void Variable::setSize(cln::cl_I a){
	size = a;
}

bool Variable::isArray(){
	return !(size == 0);
}
