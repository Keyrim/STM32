/*
 * sub_channels_analysis.c
 *
 *  Created on: 5 ao�t 2020
 *      Author: Theo
 */

#include "sub_action.h"

//Analyse des s�quences des cannaux radio
void sub_channels_analysis(State_drone_t * drone){
	static uint32_t last_time = 0 ;
	//On regarde si l'ibus ou le ppm � fait un update de ses valeurs, si il y a eu un update on refais une analyse
	if(last_time < drone->communication.ibus.last_update){
		last_time = SYSTICK_get_time_us() ;
		channel_analysis_process(&drone->communication.ch_analysis);
	}
}

