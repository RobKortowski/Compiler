/* by Robert Kortowski 221450@student.pwr.edu.pl */
#ifndef SKIP_H
#define SKIP_H

#include <map>
#include <vector>
#include <string>
#include "Member.h"

class Skip : public Member{

public:
Skip();
void appendCode();
int getInsiderId(){return -1;};
private:
};

#endif
