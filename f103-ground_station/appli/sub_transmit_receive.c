/*
 * sub_receive_pc.c
 *
 *  Created on: 15 juin 2020
 *      Author: Th�o
 */

#include "sub.h"
#include "IDs.h"



void sub_transmit(uint8_t c, uart_struct_e * uart, transmit_t * transmit, receive_struct_t * receive){

	switch(transmit->state){
		case WAIT_TRANSMIT:
			transmit->id = c ;
			//On d�termince la longeur de nos donn�es (1 � 5 octects)
			transmit->data_size = ((transmit->id % 100) / 20) + 1 ;	//Ex : 124 => (%100) => 24 => (/20) => 1 => (+1) => 2 octects (voir r�partitions adresses)
			transmit->data_size ++ ; //On augmente de 1 car on save l'id
			transmit->buffer[0] = transmit->id ;	//On save l'id
			transmit->compteur = 1 ;	//On met le compteur � 1 car c est l� qu on va commencer � �crire
			transmit->state = BUFFERING ;
			break;
		case BUFFERING :
			transmit->buffer[transmit->compteur] = c;
			transmit->compteur ++ ;

			if(transmit->compteur == transmit->data_size){
				//Une fois qu'on � tout re�u on envoi au buffer d'envoit ^^
				if(transmit->id < 200)
					uart_add_few(uart, transmit->buffer, (uint16_t)transmit->data_size);
				else{
					switch(transmit->buffer[0]){
						case ID_BASE_CONSIGNE_BASE:
							switch(transmit->buffer[1]){
								case SUB_ID_BASE_CONSIGNE_START_SENDING_ANGLES:
									receive->send_angles = 1 ;
									break;
								default:
									break;
							}
							break;
						default:
							break;
					}
			}
				transmit->state = WAIT_TRANSMIT ;
			}
			break;
		default :
			transmit->state = WAIT_TRANSMIT ;
			break;

	}

}





































