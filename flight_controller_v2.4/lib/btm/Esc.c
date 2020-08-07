/*
 * esc.c
 *
 *  Created on: 23 mars 2020
 *      Author: Theo
 */


#include "Esc.h"

#include "stm32f1_gpio.h"
#include "systick.h"
#include "../../appli/settings.h"


//On met � jour la valeur pulsation en tenant compte des valeurs max et mini autoris�es
void ESC_Set_pulse(ESC_e * esc, uint16_t pulsation){
	pulsation = MIN(PULSATION_MAX, pulsation);
	pulsation = MAX(PULSATION_MIN, pulsation);
	esc->pulsation = pulsation ;
}

//Init des ports
void ESC_init(ESC_e * esc, GPIO_TypeDef* gpio, uint16_t gpio_pin){
		esc->gpio = gpio ;
		esc->gpio_pin = gpio_pin ;
		esc->pulsation = 1000 ;
		BSP_GPIO_PinCfg(esc->gpio, esc->gpio_pin, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH );
		esc->signal_state = FALSE ;

}

//On met le signal � l'�tat haut
void ESC_Start_pulse(ESC_e * esc){
	esc->pulse_start_time = SYSTICK_get_time_us();
	esc->gpio->BSRR = esc->gpio_pin ;
	esc->signal_state = TRUE ;

}

//Si le temps est �coul� on met le signal � l'�tat bas
//On renvoit toujours l'�tat du signal
bool_e ESC_End_pulse(ESC_e * esc){

	if(SYSTICK_get_time_us() >= esc->pulsation + esc->pulse_start_time && esc->signal_state){
		esc->gpio->BSRR = (uint32_t)(esc->gpio_pin) << 16U ;
		esc->signal_state = FALSE ;
	}

	return esc->signal_state ;
}


