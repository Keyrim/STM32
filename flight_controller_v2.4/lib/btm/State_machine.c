/*
 * state_machine.c
 *
 *  Created on: 30 avr. 2020
 *      Author: Theo
 */

#include "State_machine.h"


//Appelle une fonction et renvoit des �tats de succ�s ou �chec par rapport aux param�tres
uint8_t try_action(running_e result, uint8_t in_progress, uint8_t sucess, uint8_t fail){
	uint8_t to_return ;
	switch(result){
		case END_OK :
			to_return =  sucess ;
			break ;
		case END_ERROR :
			to_return = fail ;
			break;
		case END_TIMEOUT:
			to_return = fail ;
			break;
		case IN_PROGRESS :
			to_return = in_progress;
			break;
		default :
			to_return = fail ;
			break;

	}

	return to_return ;


}

