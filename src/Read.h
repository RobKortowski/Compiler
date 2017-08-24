/* by Robert Kortowski 221450@student.pwr.edu.pl */
#ifndef READ_H
#define READ_H

#include <vector>
#include <string>
#include "Member.h"

class Read : public Member{

public:
Read();
void setId(int);
void appendCode();
int getInsiderId(){return -1;};
private:
int id;
};

#endif
