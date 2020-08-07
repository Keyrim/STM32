/*
 * MAE.h
 *
 *  Created on: 13 juin 2020
 *      Author: Th�o
 */

#ifndef MAE_H_
#define MAE_H_

//�tat pour la high lvl
typedef enum{
	WAIT_LOOP,
	PWM_HIGH,
	UPDATE_ANGLES,
	VERIF_SYSTEM,
	PWM_LOW,
	HIGH_LVL,
	STABILISATION,
	SEND_DATA,
	ERROR_HIGH_LEVEL
}Low_Level_SM;

//�tat pour la low lvl
typedef enum{
	ON_THE_GROUND,
	MANUAL,
	PARACHUTE,
	MANUAL_HAND_CONTROL,
	POSITION_HOLD,
	ALTITUDE_HOLD,
	CALIBRATE_MPU6050,
	MANUAL_PC,
	MANUAL_ACCRO,
	IMU_FAILED_INIT
}Flight_Mode_SM;

//�tat pour la stabilisation
typedef enum{
	STAB_OFF,
	LEVELLED,
	ACCRO
}Stabilisation_SM;



#endif /* MAE_H_ */
