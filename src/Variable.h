/* by Robert Kortowski 221450@student.pwr.edu.pl */
#ifndef VARIABLE_H
#define VARIABLE_H

#include <vector>
#include <string>
#include <cln/cln.h>

class Variable{

public:
bool initiated;
bool local;
bool visible;

Variable(cln::cl_I);
void setSize(cln::cl_I);
cln::cl_I getMem();
bool isArray();
private:
cln::cl_I size;
cln::cl_I mem;
};

#endif
