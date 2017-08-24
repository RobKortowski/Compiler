/* by Robert Kortowski 221450@student.pwr.edu.pl */
#ifndef GETS_H
#define GETS_H

#include <map>
#include <vector>
#include <string>
#include "Member.h"

class Gets : public Member{

public:
Gets();
void setExpressionId(int);
void setIdId(int);
void appendCode();
void appendCode(bool);
int getInsiderId(){return -1;};
private:
int idId;
int expressionId;
};

#endif
