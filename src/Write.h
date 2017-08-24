/* by Robert Kortowski 221450@student.pwr.edu.pl */
#ifndef WRITE_H
#define WRITE_H

#include <vector>
#include <string>
#include "Member.h"

class Write : public Member{

public:
Write();
void setValueId(int);
void appendCode();
int getInsiderId(){return -1;};
private:
int valueId;
};

#endif
