/* by Robert Kortowski 221450@student.pwr.edu.pl */
#ifndef VALUE_H
#define VALUE_H

#include <vector>
#include <string>

class Value{

public:
Value(int);
void setChild(int);
void appendCode(int);
bool isTwo();
void checkPidDependant(int,int);

private:
bool two;
int type;
int child;
};

#endif
