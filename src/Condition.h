/* by Robert Kortowski 221450@student.pwr.edu.pl */
#ifndef CONDITION_H
#define CONDITION_H

#include <vector>
#include <string>

class Condition{

public:
Condition(int);
void setFirstValueId(int);
void setSecondValueId(int);
void appendCode(int);
private:
int type;
int firstValueId;
int secondValueId;
};

#endif
