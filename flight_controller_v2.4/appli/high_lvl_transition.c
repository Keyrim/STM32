/*
 * high_lvl_transition.c
 *
 *  Created on: 6 ao�t 2020
 *      Author: Theo
 */


#include "high_lvl_transition.h"


//Nombre d'�tat high lvl max
#define NB_STATES 8
//Nb de fonctions de test max pour chaque �tat possible
#define NB_FUNCTION_TRANSITION 5

//Tableaux pour les transition : fonction de tests, param�tre pour les fonctions, state suivant si condition valid�
bool_e (* test_functions[NB_STATES][NB_FUNCTION_TRANSITION])(State_drone_t * drone, int32_t setting);
int32_t function_parameter [NB_STATES][NB_FUNCTION_TRANSITION] ;
Flight_Mode_SM next_states [NB_STATES][NB_FUNCTION_TRANSITION] ;

//Nombre de fonctions de test pour chaques �tat (quand on it�re � coup de for, on veut pas aller sur une case vide
int8_t nb_test_functions_per_state [NB_STATES] ;

void high_lvl_transi(State_drone_t * drone){
	for(int8_t f = 0; f < nb_test_functions_per_state[f]; f ++){
		//On it�re pour appeler chaques fonctions de test possible pour un �tat donn�
		if(test_functions[drone->soft.state_flight_mode][f](drone, function_parameter[drone->soft.state_flight_mode][f])){
			//On met � jour le nouvel �tat
			drone->soft.state_flight_mode = next_states[drone->soft.state_flight_mode][f] ;

			//Pas la peine de test les autres fonctions
			break;
		}
	}
}

