/* by Robert Kortowski 221450@student.pwr.edu.pl */
%{
	extern "C"
    {
        int yylex(void);
		void yyerror(char*);
    }
	int state = 0;
#include "calc.tab.h"
#include <iostream>
#include "Singleton.h"
#include "Variable.h"
#include <string>
#include <cln/cln.h>
#include <cln/io.h>
#include <cln/input.h>
#include <sstream>

using namespace cln;
using namespace std;

std::string lastPid = "";
bool first = false;
Singleton& s = Singleton::getInstance();
cl_read_flags* flags = new cl_read_flags();

bool inBrace = false;

int afterFor = 0;
int afterForFrom = 0;

bool inExpression = false;

%}
%s VARA
%s CODE
%s COMMENT
%%

<VARA,CODE,INITIAL>{
"{" 	{
			BEGIN(COMMENT);
		}
"}"     {
			stringstream err;
			err << "[Line "<<yylineno<<"] ERROR: " << "Closing unopened comment.";
			throw  err.str();
		}
}

<INITIAL>{
[\n] 	{yylineno++;}
[ \t]	{}
VAR 	{   

			flags->rational_base = 10;
			flags->syntax = syntax_integer;

			s.getMem();//addVariable(helpvar);
			s.getMem();//addVariable(helpvar);
			s.getMem();//addVariable(helpvar);
			s.getMem();//addVariable(helpvar);
			BEGIN(VARA);
			state = 1;
			return VAR;
		}
. 		{
			stringstream err;
			err << "[Line "<<yylineno<<"] ERROR: " << "Unknown symbol: " << yytext;
			throw  err.str();
			return IDK;
		}
}

<VARA>{
[\n] 	{yylineno++;}
[ \t]	{}
[_a-z]+ {
			if(inBrace){
				stringstream err;
				err << "[Line "<<yylineno<<"] ERROR: " << "Unclosed brace.";
				throw  err.str();
			}

			first = true;
			lastPid = yytext;
			if(s.nameExists(lastPid)){
				stringstream err;
				err << "[Line "<<yylineno<<"] ERROR: " << "Second declaration of pidentifier: " << yytext;
				throw  err.str();
			}else{
				yylval = s.addName(lastPid);
			}
			return PID;
		}
"[" 	{
			if(inBrace){
				stringstream err;
				err << "[Line "<<yylineno<<"] ERROR: " << "Braces next to each other.";
				throw  err.str();
			}
			inBrace = true;
			return LB;
		}
"]" 	{
			if(!inBrace){
				stringstream err;
				err << "[Line "<<yylineno<<"] ERROR: " << "Closing brace without opening one.";
				throw  err.str();
			}
			inBrace = false;
			return RB;
		}
[0-9]+ 	{
			if(!inBrace){
				stringstream err;
				err << "[Line "<<yylineno<<"] ERROR: " << "Number "<< yytext << " used not as array size.";
				throw  err.str();
			}
			if(!first){
				stringstream err;
				err << "[Line "<<yylineno<<"] ERROR: " << "Number "<< yytext << " used with no pidentifier.";
				throw  err.str();
			}
			int idid = s.getNameId(lastPid);
			Variable* var = s.getVariable(idid);	
			cln::cl_I c = read_integer(*flags ,yytext, NULL, NULL);	
			if(c <= 0){
				stringstream err;
				err << "[Line "<<yylineno<<"] ERROR: " << "Wrong array size: " << yytext;
				throw  err.str();
			}
			var->setSize(c);
			s.incrementMem(c-1);	
			
			return NUM; 
		}
BEGIN   {
			BEGIN(CODE);
			state = 2;
			return BEGINN;
		}
[^\n\t \]\[]+ {
			stringstream err;
			err << "[Line "<<yylineno<<"] ERROR: " << "Unrecognizable sequence of characters: " << yytext;
			throw  err.str();
			return IDK;
		}

}

<CODE>{
[\n] 	{yylineno++;}
[ \t]	{}

IF 		{
			return IF;
		}

THEN	{
			return THEN;
		}

ELSE	{
			return ELSE;
		}

ENDIF	{
			return ENDIF;
		}

WHILE	{
			return WHILE;
		}

DO		{
			return DO;
		}

ENDWHILE {
			return ENDWHILE;
		}

FOR		{
			afterFor++;
			return FOR;
		}

FROM	{
			afterForFrom++;
			return FROM;
		}

DOWNTO	{
			return DOWNTO;
		}

TO		{
			return TO;
		}

ENDFOR	{
			afterForFrom--;
			afterFor--;
			return ENDFOR;
		}

:=		{
			inExpression = true;
			return GETS;
		}

READ	{
			inExpression = true;
			return READ;
		}

WRITE	{
			inExpression = true;
			return WRITE;
		}

SKIP	{
			return SKIP;
		}

END 	{
			return END;
		}

"+"		{
			return ADD;
		}

"-"		{
			return SUB;
		}

"*"		{
			return MUL;
		}

"/"		{
			return DIV;
		}

"%"		{
			return MOD;
		}

"<="	{
			return LESSEQ;
		}

">="	{
			return MOREEQ;
		}

"<>"	{
			return NEQ;
		}

"=" 	{
			return EQ;
		}

"<"		{
			return LESS;
		}

">" 	{
			return MORE;
		}

[_a-z]+ { //accessed with brace if array go to null :
			
			first = true;
			lastPid = yytext;
			if(s.nameExists(lastPid)){
				if(afterFor == (afterForFrom+1)){	
					int id = s.getNameId(lastPid);
					if(s.getVariable(id)->local){
						if(s.getVariable(id)->visible == true){
							stringstream err;
							err << "[Line "<<yylineno<<"] ERROR: " << "Variable >>" << yytext << "<< already used as iterator in a forefather loop.";
							throw  err.str();
						}
						s.getVariable(id)->visible = true;;
						yylval = id;
					}else{
						stringstream err;
						err << "[Line "<<yylineno<<"] ERROR: " << "Variable conflict- >>" << yytext << "<< used as local and global variable.";
						throw  err.str();
					}
				}else{
					yylval = s.getNameId(lastPid);
				}
			}else{
				if(afterFor == (afterForFrom+1)){	
					int id = s.addName(lastPid);
					yylval = id;
					s.getVariable(id)->local = true;;
					s.getVariable(id)->initiated = true;;
					s.getVariable(id)->visible = true;;
				}else{
					stringstream err;
					err << "[Line "<<yylineno<<"] ERROR: " << "Undeclared variable: " << yytext;
					throw  err.str();
				}
			}
			return PID;
		}

"[" 	{
			inBrace = true; //check if last pid is array
			return LB;
		}

"]" 	{
			inBrace = false;
			return RB;
		}

[0-9]+ 	{ 	
			cln::cl_I c = read_integer(*flags ,yytext, NULL, NULL);
			yylval = s.addLiteral(c); 
			return NUM; 
		}

";"   	{
			inExpression = false;
			return EC;
		}

. 		{
			stringstream err;
			err << "[Line "<<yylineno<<"] ERROR: " << "Unknown symbol: " << yytext;
			throw  err.str();
			return IDK;
		}
}

<COMMENT>{
[\n] 	{yylineno++;}
[^}{\n]*
"{" 	{
			stringstream err;
			err << "[Line "<<yylineno<<"] ERROR: " << "Impossible comment error";
			throw  err.str();
		}
"}" 	{
			if(state == 0){
				BEGIN(INITIAL);
			}else if(state == 1){
				BEGIN(VARA);
			}else if(state == 2){
				BEGIN(CODE);
			}
		}
}

