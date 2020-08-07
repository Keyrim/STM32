/*
 * sub_esc.c
 *
 *  Created on: 1 juil. 2020
 *      Author: Th�o
 */

#include "sub_action.h"

//On passe � low l'�tat des signaux pour cr�er notre pwm
running_e sub_esc_end_pulse(ESC_e* escs){
	running_e to_return = IN_PROGRESS ;
	//Par d�fault on dit que les signaux on finit
	bool_e escs_high = FALSE ;
	for(uint8_t e = 0; e < 4 ; e ++)
		//On appelle la fonction de fin pour chaque esc et on test si le signal est finis
		escs_high |= ESC_End_pulse(&escs[e]);
	//Si tous les signaux sont fait on dit qu on a fini
	if(!escs_high)
		to_return = END_OK ;
	return to_return ;
}

//On d�marre le signal pour chacuns des escs
void sub_esc_start_pulse(ESC_e * escs){
	for(uint8_t e = 0; e < 4 ; e ++)
		ESC_Start_pulse(&escs[e]);
}
