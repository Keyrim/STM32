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

void sub_receive_data(uint8_t c, uint8_t * state_flying, double * consigne_roll_base, double * consigne_pitch_base){
	//Fonctionnement : on d�marre en attente de donn�e,
	//Quand on re�oit on r�cup�re l'id et on passe en lecture "receiving", on traite la donn�e en fonction de son id

	static sub_receive_e state = ATTENTE ;
	static uint8_t id = 0 ;
	static uint8_t compteur = 0 ;
	static uint8_t buffer[5] = {0};


	switch(state){
		case ATTENTE :
			compteur = 0 ;
			id = c ;
			state = RECEIVING ;
			break;
		case RECEIVING:
			switch(id){
				case ID_DRONE_CONSIGNE :
					//Si on a re�u une consigne, on a que un octect � g�rer donc pas besoin de compteur
					switch(c){
						case SUB_ID_DRONE_CONSIGNE_STOP_MOTEUR :
							*state_flying = 0 ; // correspond � on_the_ground
							break;
						default:
							break;
					}
					state = ATTENTE ;
					break;
				case ID_DRONE_PITCH_ROLL_BASE:
					//On save la valeur et incr�mente le compteur
					SAVE_AND_INCREASE ;
					//Si le compteur == 2, on a nos deux valeurs
					if(compteur == 2){
						*consigne_roll_base = (double)buffer[0] - 90 ;
						*consigne_pitch_base = (double)buffer[1] - 90 ;
						state = ATTENTE ;
					}

					break;
				default:
					//Si on comprend pas on passe en attente
					state = ATTENTE ;
					break;
			}
			break;
		default:
			//Ya aucun moyen on arrive l� mais au cas o�
			state = ATTENTE ;
			break;

	}
}
