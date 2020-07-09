/*
 * settings.h
 *
 *  Created on: 28 mars 2020
 *      Author: Theo
 */

#ifndef SETTINGS_H_
#define SETTINGS_H_

//Low lvl frequency
#define LOW_LVL_FREQUENCY 	250
#define LOW_LVL_PERIODE		4


//PPM settings
#define TIME_OUT_PPM 20000 	//(en micros seconde)
#define NB_CHANNEL 8
#define PITCH 1
#define ROLL 0
#define THROTTLE 2
#define YAW 3
#define SWITCH_1 4
#define SWITCH_2 5
#define SWITCH_3 6
#define SWITCH_4 7

//telemetrie
#define UART_TELEMETRIE UART3_ID

//Gps settings
#define TIME_OUT_GPS 2000000 //(en microsecondes)
#define UART_GPS UART2_ID
#define GPS_RELAY	FALSE

//Main loop settings
#define LOOP_PERIODE 4000

//PWM Settings
#define PULSATION_MIN 1000
#define PULSATION_MAX 2000

//pid max setpoint order (in degrees or degrees per second for the yaw)
#define roll_and_pitch_max_setpoint 70
#define yaw_max_setpoint 400

//PID settings
#define kp_roll 2.94 //2.94
#define ki_roll 0
#define kd_roll 0.4 //0.27

#define kp_pitch 2.94 //2.94
#define ki_pitch 0
#define kd_pitch 0.4 //0.27

#define kp_yaw 4
#define ki_yaw 0
#define kd_yaw 0

#define PID_MAX_OUTPUT 200

//Batterie
#define USE_BATTERIE_CHECK FALSE
#define BATTERIE_RESISTANCES_COEF ((double)0.00550)

#endif /* SETTINGS_H_ */
