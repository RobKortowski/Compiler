/* by Robert Kortowski 221450@student.pwr.edu.pl */
#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include <vector>
#include <string>

class Identifier{

public:
Identifier(int);
void setFirstValueId(int);
void setSecondValueId(int);
void appendCode();
void checkInitiated(int);
void setInitiated();
bool isArray();
void checkLocal(int);
void checkPidDependant(int, int);
void checkVisible(int);
int firstValueId;

private:
void add(int);
int type;
//int firstValueId;
int secondValueId;
};

#endif
