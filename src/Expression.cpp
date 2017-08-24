/* by Robert Kortowski 221450@student.pwr.edu.pl */
#include <iostream>
#include "Expression.h"
#include "Singleton.h"
#include "Value.h"

using namespace std;

Expression::Expression(int a){
	type = a;
}
void Expression::setFirstValueId(int a){
	firstValueId = a;
}
void Expression::setSecondValueId(int a){
	secondValueId = a;
}
void Expression::appendCode(){
	Singleton& s = Singleton::getInstance();
	if(type == 1){
		Value* v = s.getValue(firstValueId);
		v->appendCode(4);
	}else if(type >= 2){	
		Value* v1 = s.getValue(firstValueId);	
		Value* v2 = s.getValue(secondValueId);
		if(type == 2){
			v1->appendCode(4);
			v2->appendCode(3);
			s.append(s.cmd("ZERO", 0));	
			s.append(s.cmd("STORE", 3));
			s.append(s.cmd("ADD", 4));
		}else if(type == 3){		
			v1->appendCode(4);
			v2->appendCode(3);
			s.append(s.cmd("ZERO", 0));	
			s.append(s.cmd("STORE", 3));
			s.append(s.cmd("SUB", 4));
		}else if(type == 4){
			if(v1->isTwo()||v2->isTwo()){
				if(v1->isTwo()){
					v2->appendCode(4);
				}else if(v2->isTwo()){
					v1->appendCode(4);
				}
				s.append(s.cmd("SHL", 4));
			}else{
				v1->appendCode(4);
				v2->appendCode(3);
				int start = s.getEtq();	
				int odd = s.getEtq();	
				int end = s.getEtq();	
				int zero = s.getEtq();	
				int startmul = s.getEtq();	
				int e2 = s.getEtq();	

				s.append(s.cmd("ZERO", 0));	
				s.append(s.cmd("STORE", 3));
				s.append(s.cmd("SUB", 4));	
				s.append(s.cmd("JZERO", 4), e2);
				v1->appendCode(4);
				s.append("JUMP", startmul);
				s.append(e2);	
				v1->appendCode(3);
				v2->appendCode(4);

				s.append(startmul);	
				s.append(s.cmd("ZERO", 0));	
				s.append(s.cmd("ZERO", 2));	
				s.append(s.cmd("JZERO", 3), zero);	
				s.append(s.cmd("JZERO", 4), end);		
				s.append(start);	
				s.append(s.cmd("JODD", 3), odd);	
				
				s.append(s.cmd("SHL", 4));	
				s.append(s.cmd("SHR", 3));	
				s.append("JUMP", start);	

				s.append(odd);
				s.append(s.cmd("DEC", 3));	
				s.append(s.cmd("JZERO", 3), end);	
				s.append(s.cmd("STORE", 4));
				s.append(s.cmd("ADD", 2));
				s.append("JUMP", start);
				
				s.append(zero);
				s.append(s.cmd("ZERO", 4));	
				s.append(end);	
				
				s.append(s.cmd("STORE", 2));	
				s.append(s.cmd("ADD", 4));
			}
		}else if(type == 5){	
			v1->appendCode(4);
			v2->appendCode(3);
			if(v2->isTwo()){
				s.append(s.cmd("SHR", 4)); 	//zeroing to access help mem
			}else{
				int startOver = s.getEtq();	
				int checkLast = s.getEtq();	
				int checkEven = s.getEtq();	
				int zero = s.getEtq();	
				int finish = s.getEtq();	
				int finishDec = s.getEtq();	
				int veryEnd = s.getEtq();	
				int back2 = s.getEtq();	
				int two = s.getEtq();	
		
				
				
				
				s.append(s.cmd("JZERO", 3), zero); //if dividing by zero, go end and be happy :)
				s.append(s.cmd("DEC", 3)); 
				s.append(s.cmd("JZERO", 3), veryEnd); //if dividing by one be mega super happy	
				s.append(s.cmd("DEC", 3)); 
				s.append(s.cmd("JZERO", 3), two); //if dividing by two be superhappy
				s.append(s.cmd("INC", 3)); 
				s.append(s.cmd("INC", 3)); 


				s.append(s.cmd("ZERO", 0)); 	//zeroing to access help mem
				s.append(s.cmd("ZERO", 2));   	//for copy zero to help mem
				s.append(s.cmd("STORE", 3));	//save dividing element on help#1
				s.append(s.cmd("INC", 0)); 		//memory to help #2
				s.append(s.cmd("STORE", 2));     //zero to help#2
				s.append(s.cmd("INC", 0));      //memory to help#3
				s.append(s.cmd("STORE", 2));     //zero to help#3   
				s.append(s.cmd("INC", 0));      //memory to help#4
				s.append(s.cmd("STORE", 2));     //zero to help#4   
				s.append(s.cmd("ZERO", 0)); 	//zero to r0
				s.append(s.cmd("ZERO", 1)); 	//zero to r1 , end of prep.
				s.append(s.cmd("INC", 1));      //	

				s.append(startOver);	// not zeroed, try substractig more  
				s.append(s.cmd("ZERO", 0)); 	//zero to r0
				s.append(s.cmd("INC", 0));      //memory to help#2
				s.append(s.cmd("STORE", 3));    //save current divisor
				s.append(s.cmd("INC", 0));      //memory to help#3
				s.append(s.cmd("STORE", 4));    // svae current number
				s.append(s.cmd("DEC", 0));      //points to help#2 - divisor
				s.append(s.cmd("SUB", 4));      // x/y         x - y
				
				s.append(s.cmd("JZERO", 4), checkLast);  //go check if last division - if current c = 0	
								
				s.append(s.cmd("INC", 0));      //memory to help#3 - zeby przywrocic gore mmory	
				s.append(s.cmd("LOAD", 4));    // svae current number
				s.append(s.cmd("SHL", 3));      // double divisor
				s.append(s.cmd("SHL", 1));      // double temp out	
				s.append("JUMP", startOver);

				s.append(checkLast);
				//s.append(s.cmd("JZERO", 1), checkEven); //TODO go check if even if yes then increment #4 and re	
				s.append("JUMP", checkEven); //TODO go check if even if yes then increment #4 and re	
				s.append(back2);	
				s.append(s.cmd("DEC", 1)); // check if r1 == 1 if yes then finish 
				s.append(s.cmd("JZERO", 1), finish);
				s.append(s.cmd("INC", 1));

				s.append(s.cmd("ZERO", 0));
				s.append(s.cmd("INC", 0));
				s.append(s.cmd("LOAD", 3));    // load last div
				s.append(s.cmd("SHR", 3));    
				s.append(s.cmd("STORE", 3));
				s.append(s.cmd("INC", 0));     
				s.append(s.cmd("LOAD", 4));    // load base number
				s.append(s.cmd("DEC", 0));     
				s.append(s.cmd("SUB", 4));     

				s.append(s.cmd("ZERO", 0));
				s.append(s.cmd("LOAD", 3));    // load base div

				s.append(s.cmd("INC", 0));     
				s.append(s.cmd("INC", 0));     
				s.append(s.cmd("INC", 0));     
				s.append(s.cmd("SHR", 1));    // goot tmp out
				s.append(s.cmd("ADD", 1));     
				s.append(s.cmd("STORE", 1));     
				s.append(s.cmd("ZERO", 1));     
				s.append(s.cmd("INC", 1));     
				s.append("JUMP", startOver);

				s.append(checkEven);	
				s.append(s.cmd("ZERO", 0));
				s.append(s.cmd("INC", 0));     
				s.append(s.cmd("LOAD", 2)); 
				s.append(s.cmd("INC", 0));
				s.append(s.cmd("SUB", 2));
				s.append(s.cmd("JZERO", 2), finish);
				s.append("JUMP", back2);

				//s.append(finishDec);
				//s.append(s.cmd("DEC", 1));

				s.append(finish);	
				s.append(s.cmd("ZERO", 0));	
				s.append(s.cmd("ZERO", 4));	
				s.append(s.cmd("STORE", 1));
				s.append(s.cmd("ADD", 4));
				s.append(s.cmd("INC", 0));
				s.append(s.cmd("INC", 0));
				s.append(s.cmd("INC", 0));	
				s.append(s.cmd("ADD", 4));
				s.append("JUMP", veryEnd);

				s.append(zero);
				s.append(s.cmd("ZERO", 4));	
				s.append("JUMP", veryEnd);

				s.append(two);
				s.append(s.cmd("SHR", 4));	
				//s.append("JUMP", veryEnd);
				
				
				s.append(veryEnd);
			}
		}else if(type == 6){	

			v1->appendCode(4);
			v2->appendCode(3);
			int startOver = s.getEtq();	
			int checkLast = s.getEtq();	
			int checkEven = s.getEtq();	
			int zero = s.getEtq();	
			int finish = s.getEtq();	
			int finishDec = s.getEtq();	
			int veryEnd = s.getEtq();	
			int back2 = s.getEtq();	
	
			s.append(s.cmd("JZERO", 3), zero); //if dividing by zero, go end and be happy :)

			s.append(s.cmd("ZERO", 0)); 	//zeroing to access help mem
			s.append(s.cmd("ZERO", 2));   	//for copy zero to help mem
			s.append(s.cmd("STORE", 3));	//save dividing element on help#1
			s.append(s.cmd("INC", 0)); 		//memory to help #2
			s.append(s.cmd("STORE", 2));     //zero to help#2
			s.append(s.cmd("INC", 0));      //memory to help#3
			s.append(s.cmd("STORE", 2));     //zero to help#3   
			s.append(s.cmd("INC", 0));      //memory to help#4
			s.append(s.cmd("STORE", 2));     //zero to help#4   
			s.append(s.cmd("ZERO", 0)); 	//zero to r0
			s.append(s.cmd("ZERO", 1)); 	//zero to r1 , end of prep.
			s.append(s.cmd("INC", 1));      //	

			s.append(startOver);	// not zeroed, try substractig more  
			s.append(s.cmd("ZERO", 0)); 	//zero to r0
			s.append(s.cmd("INC", 0));      //memory to help#2
			s.append(s.cmd("STORE", 3));    //save current divisor
			s.append(s.cmd("INC", 0));      //memory to help#3
			s.append(s.cmd("STORE", 4));    // svae current number
			s.append(s.cmd("DEC", 0));      //points to help#2 - divisor
			s.append(s.cmd("SUB", 4));      // x/y         x - y
			
			s.append(s.cmd("JZERO", 4), checkLast);  //go check if last division - if current c = 0	
							
			s.append(s.cmd("INC", 0));      //memory to help#3 - zeby przywrocic gore mmory	
			s.append(s.cmd("LOAD", 4));    // svae current number
			s.append(s.cmd("SHL", 3));      // double divisor
			s.append(s.cmd("SHL", 1));      // double temp out	
			s.append("JUMP", startOver);

			s.append(checkLast);
			//s.append(s.cmd("JZERO", 1), checkEven); //TODO go check if even if yes then increment #4 and re	
			s.append("JUMP", checkEven); //TODO go check if even if yes then increment #4 and re	
			s.append(back2);	
			s.append(s.cmd("DEC", 1)); // check if r1 == 1 if yes then finish  +decreasing out so its ok
			s.append(s.cmd("JZERO", 1), finish);
			s.append(s.cmd("INC", 1));

			s.append(s.cmd("ZERO", 0));
			s.append(s.cmd("INC", 0));
			s.append(s.cmd("LOAD", 3));    // load last div
			s.append(s.cmd("SHR", 3));    
			s.append(s.cmd("STORE", 3));
			s.append(s.cmd("INC", 0));     
			s.append(s.cmd("LOAD", 4));    // load base number
			s.append(s.cmd("DEC", 0));     
			s.append(s.cmd("SUB", 4));     

			s.append(s.cmd("ZERO", 0));
			s.append(s.cmd("LOAD", 3));    // load base div

			s.append(s.cmd("INC", 0));     
			s.append(s.cmd("INC", 0));     
			s.append(s.cmd("INC", 0));     
			s.append(s.cmd("SHR", 1));    // goot tmp out
			s.append(s.cmd("ADD", 1));     
			s.append(s.cmd("STORE", 1));     
			s.append(s.cmd("ZERO", 1));     
			s.append(s.cmd("INC", 1));     
			s.append("JUMP", startOver);

			s.append(checkEven);	
			s.append(s.cmd("ZERO", 0));
			s.append(s.cmd("INC", 0));     
			s.append(s.cmd("LOAD", 2)); 
			s.append(s.cmd("INC", 0));
			s.append(s.cmd("SUB", 2));
			s.append(s.cmd("JZERO", 2), zero);
			s.append("JUMP", back2);

			//s.append(finishDec);
			//s.append(s.cmd("DEC", 1));

			s.append(finish);	
			s.append(s.cmd("ZERO", 0));	
			s.append(s.cmd("INC", 0));
			s.append(s.cmd("INC", 0));	
			s.append(s.cmd("LOAD", 4));
			s.append("JUMP", veryEnd);

			s.append(zero);
			s.append(s.cmd("ZERO", 4));	

			s.append(veryEnd);

		}

	}
}
