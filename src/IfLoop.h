/* by Robert Kortowski 221450@student.pwr.edu.pl */
#ifndef IFLOOP_H
#define IFLOOP_H

#include <map>
#include <vector>
#include <string>
#include "Member.h"

class IfLoop : public Member{

public:
IfLoop();
void setInsiderId(int);
void setSecInsiderId(int);
void setConditionId(int);
void appendCode();
int getInsiderId(){return insiderId;};
private:
int insiderId;
int secInsiderId;
int conditionId;
};

#endif
