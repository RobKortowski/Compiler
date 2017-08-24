/* by Robert Kortowski 221450@student.pwr.edu.pl */
%{
#include <stdio.h>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Singleton.h"
#include "IfLoop.h"
#include "Skip.h"
#include "Expression.h"
#include "Gets.h"
#include "Value.h"
#include "Identifier.h"
#include "Line.h"
#include "Condition.h"
#include "Write.h"
#include "Read.h"
#include "While.h"
#include "ForLoop.h"
#include <sstream>


extern "C"
{
	int yylex();
	void yyerror(std::string);
	extern int yylineno;
  	extern char* yytext;
  	extern int yylval;
}
extern FILE *yyin;
extern FILE *yyout;
Singleton& singg = Singleton::getInstance();
bool firsti = true;
int firstId = 0;
//int first = 0;
//int id = 0;
/*char* fifo[SIZE];
int indexx = -1;
void pushs(const char* a){
	indexx++;
	fifo[indexx] = (char*)malloc(sizeof(char)*3);
	strncpy(fifo[indexx], a, 3);
}
void push(int a){
	indexx++;
	fifo[indexx] = (char*)malloc(sizeof(char)*15);
	sprintf(fifo[indexx], "%d ", a);
}
void reset(){
	for(int i = 0; i <= indexx; i++){
		free(fifo[i]);
	}
	indexx = -1;
}
void print(){
	for(int i = 0; i <= indexx; i++){
		fprintf(yyout,"%s", fifo[i]);
	}
	reset();
}*/
%}
%token VAR BEGINN END 
%token IF THEN ELSE ENDIF 
%token WHILE DO ENDWHILE 
%token FOR FROM TO DOWNTO ENDFOR
%token GETS 
%token READ
%token WRITE
%token SKIP
%token ADD SUB MUL DIV MOD
%token EQ NEQ LESS MORE LESSEQ MOREEQ
%token NUM PID LB RB EC
%token IDK
%%

program: VAR vdeclarations BEGINN commands END 
 ;

vdeclarations: vdeclarations PID
 | vdeclarations PID LB NUM RB
 | 	
 ;

commands: command commands 	{
								$$ = $1;
								singg.getMember($1)->setNextId($2);
							}
 | command 					{
								$$ = $1;
								singg.getMember($1)->setNextId(-1);
							}
 ;

command: identifier GETS expression EC 	{
	   										Gets* ge = new Gets();
											ge->setExpressionId($3);
											ge->setIdId($1);
											Identifier* i = singg.getIdentifier($1);
											i->setInitiated();
											i->checkLocal(yylineno);
											$$ = singg.addMember(ge);
	   									}
 | IF condition THEN commands ELSE commands ENDIF 	{
 														IfLoop* il = new IfLoop();
														il->setInsiderId($4);
														il->setSecInsiderId($6);
														il->setConditionId($2);
														$$ = singg.addMember(il);
 													}
 | WHILE condition DO commands ENDWHILE {
 											While* wh = new While();
											wh->setInsiderId($4);
											wh->setConditionId($2);
											$$ = singg.addMember(wh);	
 										} 
 | FOR PID FROM value TO value DO commands ENDFOR 	{
														ForLoop* a = new ForLoop(1);	
														a->setPidId($2);
														a->setFirstValueId($4);
														a->setSecondValueId($6);
														a->setInsiderId($8);
														singg.getVariable($2)->visible = false;
														
														Value* vi = singg.getValue($4);
														vi->checkPidDependant($2, yylineno);
														$$ = singg.addMember(a);	
													}
 | FOR PID FROM value DOWNTO value DO commands ENDFOR 	{
															ForLoop* a = new ForLoop(2);	
															a->setPidId($2);
															a->setFirstValueId($4);
															a->setSecondValueId($6);
															a->setInsiderId($8);
															singg.getVariable($2)->visible = false;
															
															Value* vi = singg.getValue($4);
															vi->checkPidDependant($2, yylineno);
															$$ = singg.addMember(a);	
														}
 | READ identifier EC 	{
							Read* r = new Read();
							r->setId($2);
							Identifier* i = singg.getIdentifier($2);
							i->setInitiated();
							i->checkLocal(yylineno);
							$$ = singg.addMember(r);
 						}
 | WRITE value EC 	{
 						Write* w = new Write();
						w->setValueId($2);
						$$ = singg.addMember(w);
 					}
 | SKIP EC 	{
 				Skip* s = new Skip();
				$$ = singg.addMember(s);
 			}
 ;

expression: value 	{ /*laduje na r4 wynik*/
						Expression* a = new Expression(1);
						a->setFirstValueId($1);
						$$ = singg.addExpression(a);
		  			}
 | value ADD value 	{	
						Expression* a = new Expression(2);
						a->setFirstValueId($1);
						a->setSecondValueId($3);
						$$ = singg.addExpression(a);
 					}
 | value SUB value 	{	
						Expression* a = new Expression(3);
						a->setFirstValueId($1);
						a->setSecondValueId($3);
						$$ = singg.addExpression(a);
 					}
 | value MUL value 	{	
						Expression* a = new Expression(4);
						a->setFirstValueId($1);
						a->setSecondValueId($3);
						$$ = singg.addExpression(a);
 					}
 | value DIV value 	{	
						Expression* a = new Expression(5);
						a->setFirstValueId($1);
						a->setSecondValueId($3);
						$$ = singg.addExpression(a);
 					}
 | value MOD value 	{	
						Expression* a = new Expression(6);
						a->setFirstValueId($1);
						a->setSecondValueId($3);
						$$ = singg.addExpression(a);
 					}
 ;

condition: value EQ value 	{
								Condition* a = new Condition(1);
								a->setFirstValueId($1);
								a->setSecondValueId($3);
								$$ = singg.addCondition(a);
							}
 | value NEQ value 			{
								Condition* a = new Condition(2);
								a->setFirstValueId($1);
								a->setSecondValueId($3);
								$$ = singg.addCondition(a);
							}
 | value LESS value 		{
								Condition* a = new Condition(3);
								a->setFirstValueId($1);
								a->setSecondValueId($3);
								$$ = singg.addCondition(a);
							}

 | value MORE value 		{
								Condition* a = new Condition(4);
								a->setFirstValueId($1);
								a->setSecondValueId($3);
								$$ = singg.addCondition(a);
							}

 | value LESSEQ value 		{
								Condition* a = new Condition(5);
								a->setFirstValueId($1);
								a->setSecondValueId($3);
								$$ = singg.addCondition(a);
							}

 | value MOREEQ value 		{
								Condition* a = new Condition(6);
								a->setFirstValueId($1);
								a->setSecondValueId($3);
								$$ = singg.addCondition(a);
							}

 ;

value: NUM 	{ /* laduje na podany rejestr wartosc */
				Value* v = new Value(1);
				v->setChild($1);
				$$ = singg.addValue(v);
	 		}
 | identifier 	{
					Value* v = new Value(2);
					v->setChild($1);
					Identifier* i = singg.getIdentifier($1);
					i->checkInitiated(yylineno);
					$$ = singg.addValue(v);
 				}
 ;

identifier: PID {/*laduje adres na r0*/
		  			Identifier* i = new Identifier(1);
					i->setFirstValueId($1);
					i->checkVisible(yylineno);
					if(i->isArray()){
						std::stringstream err;
						err << "[Line "<<yylineno<<"] ERROR: " << "Wrong usage of array pidentifier: " << singg.getStringName($1);
						throw  err.str();
					}
					$$ = singg.addIdentifier(i);
				}
 | PID LB PID RB{
		  			Identifier* i = new Identifier(2);
					i->setFirstValueId($1);
					i->setSecondValueId($3);
					i->checkVisible(yylineno);
					if(!(i->isArray())){
						std::stringstream err;
						err << "[Line "<<yylineno<<"] ERROR: " << "Refering to normal variable as to array: " << singg.getStringName($1);
						throw  err.str();
					}
					$$ = singg.addIdentifier(i);
 				}
 | PID LB NUM RB{
		  			Identifier* i = new Identifier(3);
					i->setFirstValueId($1);
					i->setSecondValueId($3);	
					i->checkVisible(yylineno);
					if(!(i->isArray())){
						std::stringstream err;
						err << "[Line "<<yylineno<<"] ERROR: " << "Refering to normal variable as to array: " << singg.getStringName($1);
						throw  err.str();
					}
					$$ = singg.addIdentifier(i);
 				}
 ;
%%
using namespace std;
int main(int argc, char **argv)
{
	if(argc!=3){
		cout << "Żeby uruchomić: calc inputFileName outputFileName" << endl;
		return -1;
	}
	try{
		yyin = fopen(argv[1], "r");
		yyparse();

	
		int startingPoint = singg.getStartingPoint();

		singg.getMember(startingPoint)->appendCode();
		singg.append("HALT");

		int num = singg.code.size();
		int lnum = 0;
		for (int i = 0; i<num; i++){
			if(!singg.code.at(i)->repair(lnum)){
				lnum++;	
			}
		}

		yyout = fopen(argv[2], "w");
		
		for (int i = 0; i<num; i++){
			const char * c = singg.code.at(i)->getS().c_str();
			fprintf(yyout, "%s", c);
		}
	}catch(char const* err){
		cout << err << endl;
	}catch(string err){
		cout << err << endl;
	}

}
void yyerror(string message)
{
  //fprintf(stderr, "%d: error: '%s' at '%s', yylval=%u\n", yylineno, message, yytext, yylval);
	stringstream err;
	err << "[Line "<<yylineno<<"] ERROR: " << "couldn't match syntax" /*message*/ << " near '" << *yytext <<"'";
	throw  err.str();
}
/*void yyerror(char *s)
{
  //reset();
  fprintf(stderr, "Błąd.\n %s \n", s);
  std::vector<int> a;
}*/



