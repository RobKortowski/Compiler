calc:  	calc.l calc.y Singleton.cpp Member.cpp Singleton.h Member.h IfLoop.h IfLoop.cpp Skip.h Skip.cpp Variable.h Variable.cpp Expression.cpp Expression.h Gets.h Gets.cpp Value.h Value.cpp Identifier.h Identifier.cpp Line.h Line.cpp Condition.h Condition.cpp Write.h Write.cpp While.cpp While.h Read.h Read.cpp ForLoop.h ForLoop.cpp
		bison -d calc.y
		flex calc.l
		g++ -o ../$@ calc.tab.c -lm lex.yy.c Singleton.cpp Member.cpp IfLoop.cpp Skip.cpp Variable.cpp Expression.cpp Gets.cpp Value.cpp Identifier.cpp Line.cpp Condition.cpp Write.cpp While.cpp Read.cpp ForLoop.cpp -l cln -lfl
