/* by Robert Kortowski 221450@student.pwr.edu.pl */
#ifndef FORLOOP_H
#define FORLOOP_H

#include <map>
#include <vector>
#include <string>
#include "Member.h"

class ForLoop : public Member{

public:
ForLoop(int);
void setFirstValueId(int);
void setSecondValueId(int);
void setInsiderId(int);
void setPidId(int);
void appendCode();
int getInsiderId(){return insiderId;};
private:
int type;
int firstValueId;
int secondValueId;
int pidId;
int insiderId;
};

#endif
