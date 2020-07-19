/*
 * test_transition.h
 *
 *  Created on: 19 juil. 2020
 *      Author: Th�o
 */

#ifndef BTM_TEST_TRANSITION_H_
#define BTM_TEST_TRANSITION_H_

#include "../../appli/system_d.h"

typedef struct{
	int16_t (*test_function)(State_drone_t * drone, bool_e test);
	int16_t nb_test_succesfull;

}test_t;

typedef struct{
	bool_e (*check_function)(State_drone_t * drone);
	int16_t nb_check_recquiered;
	int16_t nb_check_succesfull;
}check_request_t;

void TRANSITION_init_test(test_t * test, int16_t (*test_function)(State_drone_t * drone, bool_e test));
void TRANSITION_init_check(check_request_t * check, bool_e (*check_function)(State_drone_t * drone), int16_t nb_check_recquiered);

bool_e TRANSITION_test(test_t * test_struct, State_drone_t * drone, bool_e test, int16_t nb_recquiered);

#endif /* BTM_TEST_TRANSITION_H_ */
