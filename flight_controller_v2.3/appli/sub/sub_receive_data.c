/*
 * sub_receive_data.c
 *
 *  Created on: 13 juin 2020
 *      Author: Th�o
 */


#include "sub_action.h"
#include "../IDs.h"

//Macro pratique
#define SAVE_AND_INCREASE buffer[compteur] = c ;compteur++ ;

typedef enum {
	ATTENTE,
	RECEIVING
}sub_receive_e;


void sub_receive_data(uint8_t c, State_drone_t * drone, State_base_t * base){

	static uint8_t id = 0 ;
	static uint8_t compteur = 0 ;
	static uint8_t buffer[5] = {0};
	static uint8_t new_data = 1 ;

	if(new_data){
		compteur = 0 ;
		id = c ;
		new_data = 0 ;
	}
	else
	{
		switch(id){
			case ID_DRONE_CONSIGNE :
				//Si on a re�u une consigne, on a que un octect � g�rer donc pas besoin de compteur
				switch(c){
					case SUB_ID_DRONE_CONSIGNE_STOP_MOTEUR :
						drone->state_flight_mode = 0 ; // correspond � on_the_ground
						break;
					default:
						break;
				}
				new_data = 1 ;
				break;
			case ID_DRONE_PITCH_ROLL_BASE:
				//On save la valeur et incr�mente le compteur
				SAVE_AND_INCREASE ;
				//Si le compteur == 2, on a nos deux valeurs
				if(compteur == 2){
					base->angle_x = (double)(buffer[0] - 90)  ;
					base->angle_y = (double)(buffer[1] - 90)  ;
					new_data = 1 ;
				}

				break;
			default:
				//Si on comprend pas on reset les choses
				compteur = 0 ;
				id = c ;
				new_data = 0 ;
				break;
		}
	}
}
