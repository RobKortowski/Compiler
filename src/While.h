/* by Robert Kortowski 221450@student.pwr.edu.pl */
#ifndef WHILE_H
#define WHILE_H

#include <map>
#include <vector>
#include <string>
#include "Member.h"

class While : public Member{

public:
While();
void setInsiderId(int);
void setConditionId(int);
void appendCode();
int getInsiderId(){return insiderId;};
private:
int insiderId;
int conditionId;
};

#endif
