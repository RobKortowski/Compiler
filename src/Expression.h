/* by Robert Kortowski 221450@student.pwr.edu.pl */
#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <vector>
#include <string>

class Expression{

public:
Expression(int);
void setFirstValueId(int);
void setSecondValueId(int);
void appendCode();
private:
int type;
int firstValueId;
int secondValueId;
};

#endif
