/*
 * sub_free_time.c
 *
 *  Created on: 29 juil. 2020
 *      Author: Th�o
 */
#include "sub_action.h"
#include "branchement.h"
#include "systick.h"


//On rajoute des case comme on veut, on rajoute une ligne state = 0 pour le case de fin
void sub_free_time(State_drone_t * drone, State_base_t * base){
	if(drone->soft.dead_line){

		uint32_t free_time = drone->soft.dead_line - SYSTICK_get_time_us() ;
		static int32_t state = 0 ;

		static uint32_t ms5611_time_needed = 60 ;
		switch(state){
			case 0 :
				IBUS_check_data(&drone->communication.ibus);
				break;

			case 1 :
				if(free_time >= ms5611_time_needed){
					ms5611_time_needed = sub_ms5611(drone);
				}
				break;

			case 2 :
				//Si on a re�u des donn�es de la base
				if(UART_data_ready(UART_TELEMETRIE)){
					sub_receive_data(UART_get_next_byte(UART_TELEMETRIE), drone, base);
				}
				break;

			case 3 :
				uart_send(&drone->communication.uart_telem);
				break;

			case 4 :
				//led d'etat
				LED_SEQUENCE_play(&drone->ihm.led_etat);
				break ;

			case 5:
				sub_channels_analysis(drone);
				state = 0 ; //On boycot le gps
				break;

			case 10 :
				//Si on re�u des donn�es du gps
				if(UART_data_ready(UART_GPS)){
					uint8_t c = UART_get_next_byte(UART_GPS) ;
					if(DRONE_GPS_process_rx(c, &drone->capteurs.gps) >= 3){
						drone->capteurs.gps.last_time_read_gps = SYSTICK_get_time_us() ;
					}
					if(GPS_RELAY)
						uart_add_one(&drone->communication.uart_telem, c);
				}
				state = 0 ;
				break ;



		}
		if(state)
			state ++;



	}
}

