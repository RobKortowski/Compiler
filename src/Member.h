/* by Robert Kortowski 221450@student.pwr.edu.pl */
#ifndef MEMBER_H
#define MEMBER_H

#include <vector>
#include <string>

class Member{

public:
Member();
void setId(int);
int getId();
void setNextId(int);
int getNextId();
//void setInsiderId(int);
virtual void appendCode()=0;
virtual int getInsiderId()=0;
private:
//int insiderId;
int id;
int nextId;
};

#endif
