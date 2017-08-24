/* by Robert Kortowski 221450@student.pwr.edu.pl */
#ifndef SINGLETON_H
#define SINGLETON_H

#include <map>
#include <vector>
#include <string>
#include "Member.h"
#include "Variable.h" 
#include "Expression.h"
#include "Value.h"
#include "Identifier.h"
#include "Line.h"
#include "Condition.h"
#include <cln/cln.h>

class Singleton{

public:
int a;
static Singleton& getInstance();
int addMember(Member*);
Member* getMember(int);

void append(std::string);
void append(std::string, int);
void append(int);

std::vector<Line*> code;
std::map<int, std::vector<Line*>*> points;
std::vector<Line*>* getLines(int);

int addLiteral(cln::cl_I);
cln::cl_I getLiteral(int);
int addName(std::string);
std::string getStringName(int a);
bool nameExists(std::string);
int addVariable(Variable*);
int getNameId(std::string);
Variable* getVariable(int);

int addExpression(Expression*);
Expression* getExpression(int);

int addValue(Value*);
Value* getValue(int);

std::string cmd(std::string, int);

int addIdentifier(Identifier*);
Identifier* getIdentifier(int);

int getEtq();

int addCondition(Condition*);
Condition* getCondition(int);

cln::cl_I getMem();
cln::cl_I getVarsMem(int);
void incrementMem(cln::cl_I);

void loadNumber(cln::cl_I, int); 

int getStartingPoint();
private:
int etq;
std::vector<Condition*> conds;
std::vector<Identifier*> idens;
std::vector<Value*> vals;
std::vector<Expression*> exps;

std::vector<Variable*> vars;
std::map<std::string, int> names;
cln::cl_I memCount;

std::vector<cln::cl_I> literals;
std::vector<Member*> members;
Singleton();
Singleton(Singleton const&);
void operator=(Singleton const&);

};

#endif
