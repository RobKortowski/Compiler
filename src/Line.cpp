/* by Robert Kortowski 221450@student.pwr.edu.pl */
#include <iostream>
#include "Line.h"
#include "Singleton.h"
#include <sstream>

using namespace std;

Line::Line(int a, string s, int e){
	type = a;
	command = s;
	etq = e;
}

bool Line::repair(int a){
	if(type == 2){
		Singleton& s = Singleton::getInstance();
		vector<Line*>* vec =  s.getLines(etq);
		for(int i = 0; i < vec->size(); i++){
			vec->at(i)->setEtq(a);
		}
		return true;
	}else{
		return false;
	}
}

string Line::getS(){
	if(type == 2){
		return "";
	}else if(type == 1){	
		stringstream cmd;
		cmd << command << " " << etq << "\n";
		return cmd.str();
	}else if(type == 0){
		stringstream cmd;
		cmd << command << "\n";
		return cmd.str();
	}
}

void Line::setEtq(int a){
	etq = a;
}
