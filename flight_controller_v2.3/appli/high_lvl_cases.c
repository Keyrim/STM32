/*
 * high_lvl_cases.c
 *
 *  Created on: 29 juin 2020
 *      Author: Th�o
 */

#include "high_lvl_cases.h"
#include "../btm/telemetrie.h"
#include "../../ressources/sequences_led.h"
#include "../btm/test_transition.h"

//Private functions used to transit from one state to an other
void transition_high_lvl(State_drone_t * drone);

//Fonctions o� on test des �tats
//Ces fonctions ne font pas de changement d'�tat
int16_t test_ppm(State_drone_t * drone, bool_e working);
int16_t test_arm_switch(State_drone_t * drone, bool_e armed);
int16_t test_throttle_really_low(State_drone_t * drone, bool_e superior);
int16_t test_throttle_low(State_drone_t * drone, bool_e superior);

//Fonctions o� on regarde si il ya une demande pour une action
//Ces fonction effectues elles m�mes les changements d'�tat
bool_e check_calibrate_mpu_request(State_drone_t * drone);
bool_e check_manual_pc_request(State_drone_t * drone);
bool_e check_stop_motor_request(State_drone_t * drone);
bool_e check_parachute_request(State_drone_t * drone);
bool_e check_manual_request(State_drone_t * drone);
bool_e check_manual_style_request(State_drone_t * drone);




int16_t test_ppm(State_drone_t * drone, bool_e working){
	//exemple :
	//ppm.is_ok = true
	//test = ok = 1 ;
	//1^1 = 0
	//On renvoit true

	if(drone->communication.ppm.is_ok ^ working)
		return 	0 ;
	else
		return 1 ;



}
int16_t test_arm_switch(State_drone_t * drone, bool_e armed){
	static uint32_t last_update = 0 ;
	int16_t to_return = 0;


	if((drone->communication.ppm.channels[SWITCH_1] < 1200) ^ armed)
		to_return = 1 ;
	else
		to_return = 0 ;


	if(drone->communication.ppm.last_update != last_update){
		last_update = drone->communication.ppm.last_update;
	}
	else
		to_return += 2 ;

	return to_return ;
}
int16_t test_throttle_low(State_drone_t * drone, bool_e superior){
	if((drone->communication.ppm.channels[THROTTLE] < 1100) ^ superior)
		return TRUE;
	else
		return FALSE ;
}
int16_t test_throttle_really_low(State_drone_t * drone, bool_e superior){
	if((drone->communication.ppm.channels[THROTTLE] < 1070) ^ superior)
		return TRUE;
	else
		return FALSE ;
}


bool_e check_parachute_request(State_drone_t * drone){
	if(drone->communication.ppm.channels[SWITCH_2] > 1650){
		drone->soft.state_flight_mode = PARACHUTE ;
		TELEMETRIE_send_high_lvl_transi(SUB_ID_PC_HIGH_LVL_TRANSITION_SWITCH, &drone->communication.uart_telem);
		return TRUE;
	}
	else
		return FALSE;
}
bool_e check_manual_style_request(State_drone_t * drone){
	if(drone->communication.ppm.channels[SWITCH_2] > 1350 && drone->communication.ppm.channels[SWITCH_2] < 1650){
		drone->soft.state_flight_mode = MANUAL_STYLEE ;
		TELEMETRIE_send_high_lvl_transi(SUB_ID_PC_HIGH_LVL_TRANSITION_SWITCH, &drone->communication.uart_telem);
		return TRUE ;
	}
	else
		return FALSE ;
}
bool_e check_manual_request(State_drone_t * drone){
	if(drone->communication.ppm.channels[SWITCH_2] < 1350){
		drone->soft.state_flight_mode = MANUAL ;
		TELEMETRIE_send_high_lvl_transi(SUB_ID_PC_HIGH_LVL_TRANSITION_SWITCH, &drone->communication.uart_telem);
		return TRUE ;
	}
	else
		return FALSE ;
}
bool_e check_calibrate_mpu_request(State_drone_t * drone){
	if(drone->soft.flag_request_calib_mpu){
		drone->soft.flag_request_calib_mpu = 0 ;
		drone->soft.state_flight_mode = CALIBRATE_MPU6050 ;
		TELEMETRIE_send_high_lvl_transi(SUB_ID_PC_HIGH_LVL_TRANSITION_PC_REQUEST, &drone->communication.uart_telem);
		return TRUE ;
	}
	else
		return FALSE ;
}
bool_e check_manual_pc_request(State_drone_t * drone){
	if(drone->soft.flag_request_manual_pc){
		drone->soft.flag_request_manual_pc = FALSE ;
		drone->soft.state_flight_mode = MANUAL_PC ;
		TELEMETRIE_send_high_lvl_transi(SUB_ID_PC_HIGH_LVL_TRANSITION_PC_REQUEST, &drone->communication.uart_telem);
		return TRUE;
	}
	else
		return FALSE;
}
bool_e check_stop_motor_request(State_drone_t * drone){
	if(drone->soft.flag_request_stop_motor){
		drone->soft.flag_request_stop_motor = 0 ;
		drone->soft.state_flight_mode = ON_THE_GROUND ;
		TELEMETRIE_send_high_lvl_transi(SUB_ID_PC_HIGH_LVL_TRANSITION_PC_REQUEST, &drone->communication.uart_telem);
		return TRUE ;
	}
	else
		return FALSE ;
}



//Transition
bool_e transition_init = 0 ;
test_t arm_switch_test ;



void transition_high_lvl(State_drone_t * drone){
	switch(drone->soft.state_flight_mode){
		case ON_THE_GROUND :
			//Conditions de transitions
//			if(drone->communication.ppm.channels[SWITCH_1] > 1500 && drone->communication.ppm.is_ok && (drone->capteurs.batterie.voltage > 10.8 || !USE_BATTERIE_CHECK)){	//Conditions g�n�rales
//				if(drone->communication.ppm.channels[THROTTLE] < 1100 && drone->communication.ppm.channels[THROTTLE] > 1070){								//Pour passer en manuel
//					drone->soft.state_flight_mode = MANUAL ;
//				}
//			}


			if(check_calibrate_mpu_request(drone))
				break;
			else if(check_manual_pc_request(drone))
				break;
			else if(test_ppm(drone, TRUE)){
				if(TRANSITION_test(&arm_switch_test, drone, TRUE, 1)){
					if(test_throttle_low(drone, FALSE)){
						if(test_throttle_really_low(drone, TRUE))
							drone->soft.state_flight_mode = MANUAL ;
					}
				}
			}

			break;

		case MANUAL :
			if(test_ppm(drone, FALSE)){
				drone->soft.state_flight_mode = ON_THE_GROUND ;
				TELEMETRIE_send_high_lvl_transi(SUB_ID_PC_HIGH_LVL_TRANSITION_PPM_ISNT_OK, &drone->communication.uart_telem);
			}

			else if(TRANSITION_test(&arm_switch_test, drone, FALSE, 5)){
				drone->soft.state_flight_mode = ON_THE_GROUND ;
				TELEMETRIE_send_high_lvl_transi(SUB_ID_PC_HIGH_LVL_TRANSITION_ARM_SWITCH, &drone->communication.uart_telem);
			}

			else if(test_throttle_really_low(drone, FALSE)){
				drone->soft.state_flight_mode = ON_THE_GROUND ;
				TELEMETRIE_send_high_lvl_transi(SUB_ID_PC_HIGH_LVL_TRANSITION_THROTTLE_LOW, &drone->communication.uart_telem);
			}

			break;

		case MANUAL_STYLEE:
			break;

		case PARACHUTE:
			break;

		case ALTITUDE_HOLD:
			break;

		case POSITION_HOLD:
			break;

		case CALIBRATE_MPU6050:
			//Le state calibrate_mpu n'appelle pas la fonction de transition
			break;

		case MANUAL_PC:
			if(check_stop_motor_request(drone))
				break;
			break;

		default:
			break;
	}
}






void HIGH_LVL_On_The_Ground(State_drone_t * drone){
	//On d�marre par ici et on va en profiter pour init les transition
	if(!transition_init){
		TRANSITION_init_test(&arm_switch_test, test_arm_switch);

		transition_init = 1;
	}

	if(drone->soft.entrance_flight_mode){
		drone->stabilisation.stabilize = FALSE ;
		LED_SEQUENCE_set_sequence(&drone->ihm.led_etat, SEQUENCE_LED_1);
	}
	//Si on est au sol on met la consigne des moteurs � z�ro
	drone->stabilisation.escs[0].pulsation = PULSATION_MIN ;
	drone->stabilisation.escs[1].pulsation = PULSATION_MIN ;
	drone->stabilisation.escs[2].pulsation = PULSATION_MIN ;
	drone->stabilisation.escs[3].pulsation = PULSATION_MIN ;

	transition_high_lvl(drone);

}

void HIGH_LVL_Manual(State_drone_t * drone){
	//			---------------------------- 		MAIN PART 			----------------------------------------
	if(drone->soft.entrance_flight_mode){
		drone->capteurs.mpu.z = 0 ;
		drone->stabilisation.stabilize = TRUE ;
		LED_SEQUENCE_set_sequence(&drone->ihm.led_etat, SEQUENCE_LED_2);
	}

	drone->consigne.roll = ((double)(drone->communication.ppm.channels[ROLL]- 1500) / (double)500) * (double)roll_and_pitch_max_setpoint ;
	drone->consigne.pitch = ((double)(drone->communication.ppm.channels[PITCH]- 1500) / (double)500) * (double)roll_and_pitch_max_setpoint ;
	double yaw_consigne_degre_sec = ((double)(drone->communication.ppm.channels[YAW] - 1500) / (double)500) * (double)yaw_max_setpoint ;//Consigne en degr� par seconde attention ^^
	drone->consigne.yaw += yaw_consigne_degre_sec / (double)250 ;
	drone->consigne.throttle = (double)(drone->communication.ppm.channels[THROTTLE] - 1050)  ;

	//			---------------------------- Condition de transition 	----------------------------------------
	transition_high_lvl(drone);
}

void HIGH_LVL_Manual_Stylee(State_drone_t * drone, State_base_t * base){
	if(drone->soft.entrance_flight_mode){
		drone->stabilisation.stabilize = TRUE ;
		TELEMETRIE_send_consigne_base(SUB_ID_BASE_CONSIGNE_START_SENDING_ANGLES, &drone->communication.uart_telem);
		LED_SEQUENCE_set_sequence(&drone->ihm.led_etat, SEQUENCE_LED_4);
	}
	//			---------------------------- 		MAIN PART 			----------------------------------------
	drone->consigne.yaw = ((double)(drone->communication.ppm.channels[YAW] - 1500) / (double)500) * (double)yaw_max_setpoint ;	//Consigne en degr� par seconde attention ^^
	drone->consigne.throttle = (double)(drone->communication.ppm.channels[THROTTLE] - 1050)  ;
	drone->consigne.roll = base->angle_x ;
	drone->consigne.pitch = base->angle_y ;

	//			---------------------------- Condition de transition 	----------------------------------------
	transition_high_lvl(drone);

}

void HIGH_LVL_Parachute(State_drone_t * drone){
	if(drone->soft.entrance_flight_mode){
		drone->stabilisation.stabilize = TRUE ;
		LED_SEQUENCE_set_sequence(&drone->ihm.led_etat, SEQUENCE_LED_3);
	}

	//			---------------------------- 		MAIN PART 			----------------------------------------
	drone->consigne.throttle = (double)(drone->communication.ppm.channels[THROTTLE] - 1050)  ;
	if(sub_parachute(drone) != IN_PROGRESS){
		drone->soft.state_flight_mode = ON_THE_GROUND ;
	}
	else
		transition_high_lvl(drone);
}

void HIGH_LVL_Calibrate_MPU(State_drone_t * drone){
	if(drone->soft.entrance_flight_mode){
		drone->stabilisation.stabilize = FALSE ;
		LED_SEQUENCE_set_sequence(&drone->ihm.led_etat, SEQUENCE_LED_6);
	}

	//			---------------------------- 		MAIN PART 			----------------------------------------
	if(mpu6050_calibrate(&drone->capteurs.mpu, 1000)){
		drone->soft.state_flight_mode = ON_THE_GROUND ;
	}
}

void HIGH_LVL_Manual_Pc(State_drone_t * drone){
	if(drone->soft.entrance_flight_mode){
		drone->stabilisation.stabilize = TRUE ;
		LED_SEQUENCE_set_sequence(&drone->ihm.led_etat, SEQUENCE_LED_5);
	}

	//Controle des consigne moteurs pas evenement dans la sub "receive_data" donc rien � faire � part check si on reste l� ou pas
	transition_high_lvl(drone);
}















