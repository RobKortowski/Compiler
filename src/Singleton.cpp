/* by Robert Kortowski 221450@student.pwr.edu.pl */
#include <iostream>
#include "Singleton.h"
#include <sstream>

using namespace std;

Singleton& Singleton::getInstance(){
	static Singleton ins;
	return ins;
}

Singleton::Singleton(){
	a = 3;
	etq = 98;
	memCount = 0;
}

int Singleton::addMember(Member* a){
	int ret = members.size();
	members.push_back(a);
	return ret;
}

Member* Singleton::getMember(int a){
	return members.at(a);
}

void Singleton::append(string line){
	Line* l = new Line(0, line, 0);
	code.push_back(l);
}

void Singleton::append(string line, int ee){
	Line* l = new Line(1, line, ee);
	if (points.find(ee) == points.end()){
		vector<Line*>* vec = new vector<Line*>();
		vec->push_back(l);
		points[ee] = vec;
	}
	else{
		points.at(ee)->push_back(l);
	}
	code.push_back(l);
}

void Singleton::append(int e){
	Line* l = new Line(2, "", e);
	code.push_back(l);
}

int Singleton::addLiteral(cln::cl_I a){
	int ret = literals.size();
	literals.push_back(a);
	return ret;
}

cln::cl_I Singleton::getLiteral(int a){
	return literals.at(a);
}

cln::cl_I Singleton::getMem(){
	memCount = memCount + 1;
	return memCount;
}

void Singleton::incrementMem(cln::cl_I inc){
	memCount = memCount + inc;
}

cln::cl_I Singleton::getVarsMem(int a){
	return vars.at(a)->getMem();
}

int Singleton::addName(string a){		
	Variable* v = new Variable(getMem());
	int ret = addVariable(v);
	names[a] = ret;
	return ret;
}

int Singleton::addVariable(Variable* v){
	int ret = vars.size();
	vars.push_back(v);
	return ret;
}

bool Singleton::nameExists(string a){
	if (names.find(a) == names.end()){
		return false;
	}
	else{
		return true;
	}
}

int Singleton::getNameId(string a){
	return names.at(a);
}

string Singleton::getStringName(int a){
	map<string, int>::const_iterator it;
	for(it = names.begin(); it != names.end(); ++it){
		if(it->second == a){
			return it->first;
		}
	}
}

Variable* Singleton::getVariable(int a){
	return vars.at(a);
}

int Singleton::addExpression(Expression* v){
	int ret = exps.size();
	exps.push_back(v);
	return ret;
}

Expression* Singleton::getExpression(int a){
	return exps.at(a);
}

int Singleton::addValue(Value* v){
	int ret = vals.size();
	vals.push_back(v);
	return ret;
}

Value* Singleton::getValue(int a){
	return vals.at(a);
}

string Singleton::cmd(string s, int a){
	stringstream cmd;
	cmd << s << " " << a;
	return cmd.str();
}

int Singleton::addIdentifier(Identifier* v){
	int ret = idens.size();
	idens.push_back(v);
	return ret;
}

Identifier* Singleton::getIdentifier(int a){
	return idens.at(a);
}

int Singleton::getEtq(){
	etq++;
	return etq;
}

vector<Line*>* Singleton::getLines(int a){
	return points.at(a);
}

int Singleton::addCondition(Condition* v){
	int ret = conds.size();
	conds.push_back(v);
	return ret;
}

Condition* Singleton::getCondition(int a){
	return conds.at(a);
}

void Singleton::loadNumber(cln::cl_I number, int r){
	vector<bool> actions;
	cln::cl_I n = number;
	cln::cl_I two = 2;
	cln::cl_I one = 1;

	while(n != 0){
		if(cln::oddp(n)){
			n = n - one;
			actions.push_back(false);
		}else{
			n = exquo(n, two);
			actions.push_back(true);
		}
	}
	append(cmd("ZERO", r));
	while(!actions.empty()){
		bool a = actions.back();
		actions.pop_back();
		if(a){
			append(cmd("SHL", r));
		}else{
			append(cmd("INC", r));
		}
	}
}

int Singleton::getStartingPoint(){
	int seek = 0;
	int forst = 0;
	for(int i = 0; i < members.size(); i++){
		int x = members.at(i)->getInsiderId();
		if(x == seek){
			forst = i;
			seek = i;
			i = -1;
		}
	}
	return forst;
}
