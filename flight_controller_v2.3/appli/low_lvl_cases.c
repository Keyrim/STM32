/*
 * low_lvl_cases.c
 *
 *  Created on: 29 juin 2020
 *      Author: Th�o
 */


#include "low_lvl_cases.h"

void LOW_LVL_Wait_Loop(State_drone_t * drone){

	uint32_t time = SYSTICK_get_time_us();
	if(time >= drone->soft.previous_time_loop + LOOP_PERIODE){
		drone->soft.previous_time_loop += LOOP_PERIODE ;
		drone->soft.state_low_level = PWM_HIGH ;
		drone->soft.free_time = 0 ;	//Si c'est l'heure on passe direct au state suivant
	}
	else
		drone->soft.free_time = drone->soft.previous_time_loop + LOOP_PERIODE - time ;	//si on a du temps dispo, on le dit
}
void LOW_LVL_Pwm_High(State_drone_t * drone){
	//Starting pwm signals for the escs
	sub_esc_start_pulse(drone->stabilisation.escs);
	drone->soft.state_low_level = UPDATE_ANGLES ;
}

void LOW_LVL_Update_Angles(State_drone_t * drone){
	//read mpu data and appli the filter
	MPU6050_ReadAll(&drone->capteurs.mpu.raw_data_mpu);
	DRONE_mpu6050_update_angles(&drone->capteurs.mpu);
	drone->soft.state_low_level = VERIF_SYSTEM ;
}

void LOW_LVL_Verif_System(State_drone_t * drone){
	uint32_t time = SYSTICK_get_time_us();
	//Verif si le ppm est toujours bien re�u
	if(time > drone->communication.ppm.previous_time_rising + TIME_OUT_PPM)
		drone->communication.ppm.is_ok = FALSE ;
	else
		drone->communication.ppm.is_ok = TRUE ;

	//Verif si le gps est ok
	if(time > drone->capteurs.gps.last_time_read_gps + TIME_OUT_GPS)
		drone->capteurs.gps.is_ok = FALSE ;
	else
		drone->capteurs.gps.is_ok = TRUE ;

	//Mesure batterie
	DRONE_batterie_update(&drone->capteurs.batterie);

	drone->soft.state_low_level = PWM_LOW ;
}

void LOW_LVL_Pwm_Low(State_drone_t * drone){
	drone->soft.state_low_level = try_action(sub_esc_end_pulse(drone->stabilisation.escs), drone->soft.state_low_level, ESCS_SETPOINTS, ERROR_HIGH_LEVEL);
}


void LOW_LVL_Escs_Setpoints(State_drone_t * drone, State_base_t * base){
	//D�termine un changement de mode de vol
	static Flight_Mode_SM previous_state_flight_mode = PARACHUTE ;
	drone->soft.entrance_flight_mode = drone->soft.state_flight_mode != previous_state_flight_mode ;
	previous_state_flight_mode = drone->soft.state_flight_mode ;
	switch(drone->soft.state_flight_mode){

		case ON_THE_GROUND :
			if(drone->soft.entrance_flight_mode)
				LED_SEQUENCE_set_sequence(&drone->ihm.led_etat, SEQUENCE_LED_1);
			HIGH_LVL_On_The_Ground(drone);

			break;

		case MANUAL :
			if(drone->soft.entrance_flight_mode)
					LED_SEQUENCE_set_sequence(&drone->ihm.led_etat, SEQUENCE_LED_2);
			HIGH_LVL_Manual(drone);

			break;
		case MANUAL_STYLEE:
			if(drone->soft.entrance_flight_mode){
				TELEMETRIE_send_consigne_base(SUB_ID_BASE_CONSIGNE_START_SENDING_ANGLES, &drone->communication.uart_telem);
				LED_SEQUENCE_set_sequence(&drone->ihm.led_etat, SEQUENCE_LED_4);
			}
			HIGH_LVL_Manual_Stylee(drone, base);
			break;
		case PARACHUTE :
			if(drone->soft.entrance_flight_mode)
				LED_SEQUENCE_set_sequence(&drone->ihm.led_etat, SEQUENCE_LED_3);
			HIGH_LVL_Parachute(drone);

			break;
		case POSITION_HOLD:
			//TODO Position hold function
			break;
		case ALTITUDE_HOLD:
			//TODO Altitude hold function
			break;
	}


	//If we fly, we compute our outputs, according to our targets, to keep the drone leveled
	if(drone->soft.state_flight_mode){
		double roll_output 	= PID_compute(&drone->stabilisation.pid_roll, drone->consigne.roll, drone->capteurs.mpu.y);
		double pitch_output = PID_compute(&drone->stabilisation.pid_pitch, drone->consigne.pitch, drone->capteurs.mpu.x);
		double yaw_output	= PID_compute(&drone->stabilisation.pid_yaw, drone->consigne.yaw, drone->capteurs.mpu.z);

		ESC_Set_pulse(&drone->stabilisation.escs[0], (uint16_t)(1000 + drone->consigne.throttle + (int16_t)(- roll_output - pitch_output - yaw_output)));
		ESC_Set_pulse(&drone->stabilisation.escs[1], (uint16_t)(1000 + drone->consigne.throttle + (int16_t)(+ roll_output - pitch_output + yaw_output)));
		ESC_Set_pulse(&drone->stabilisation.escs[2], (uint16_t)(1000 + drone->consigne.throttle + (int16_t)(- roll_output + pitch_output + yaw_output)));
		ESC_Set_pulse(&drone->stabilisation.escs[3], (uint16_t)(1000 + drone->consigne.throttle + (int16_t)(+ roll_output + pitch_output - yaw_output)));
	}

	drone->soft.state_low_level = SEND_DATA ;
}

void LOW_LVL_Send_Data(State_drone_t * drone){
	//if(drone->communication.ppm.channels[SWITCH_4] > 1500)
		sub_send_data(drone);
	drone->soft.state_low_level = WAIT_LOOP ;
}



