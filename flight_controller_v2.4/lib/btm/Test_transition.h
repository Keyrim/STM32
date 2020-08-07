/*
 * test_transition.h
 *
 *  Created on: 19 juil. 2020
 *      Author: Th�o
 */

#ifndef BTM_TEST_TRANSITION_H_
#define BTM_TEST_TRANSITION_H_

#include "../../appli/system_d.h"


//Structure de test avec le nombre de test r�ussis et la fonction de test � appeler
typedef struct{
	int32_t (*test_function)(State_drone_t * drone, bool_e test);
	int32_t nb_test_succesfull;
}test_t;


void TRANSITION_init_test(test_t * test, int32_t (*test_function)(State_drone_t * drone, bool_e test));
bool_e TRANSITION_test(test_t * test_struct, State_drone_t * drone, bool_e test, int32_t nb_recquiered);

#endif /* BTM_TEST_TRANSITION_H_ */
