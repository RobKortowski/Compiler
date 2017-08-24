/* by Robert Kortowski 221450@student.pwr.edu.pl */
#ifndef LINE_H
#define LINE_H

#include <vector>
#include <string>

class Line{

public:
Line(int,std::string,int);
bool repair(int);
std::string getS();
void setEtq(int);
private:
int type;
std::string command;
int etq;
};

#endif
