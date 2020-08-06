/*
 * channel_analysis.c
 *
 *  Created on: 5 ao�t 2020
 *      Author: Theo
 */

#include "channel_annalysis.h"


bool_e channel_analysis_init(channel_analysis_t * channels, int32_t nb_channel, int32_t * channels_array){

	if(nb_channel > NB_CHANNEL_MAX)
		//Si on la struct � des tableaux trop petit on laisse tomber
		return 1 ;
	channels->nb_channels = nb_channel ;
	channels->channels = channels_array ;

	//Configuration des channels par d�fault, � savoir les 4 premi�re en "joystick"
	for(uint8_t ch = 0 ; ch < 4; ch ++){
		channels->channel_type[ch] = JOYSTICK ;
		channels->analysis_mode[ch] = NO_ANALYSIS ;
	}
	//Les autres ont dit c'est des switch
	for(uint8_t ch = 4 ; ch < 10; ch ++){
		channels->channel_type[ch] = SWITCH_3_POS ;
		channels->analysis_mode[ch] = NO_ANALYSIS ;
	}

	channels->is_init = TRUE ;
	return 0 ;
}

void channel_analysis_process(channel_analysis_t * channels){
	for(int8_t ch = 0; ch < channels->nb_channels; ch++ ){
		switch (channels->analysis_mode[ch]) {
			case NO_ANALYSIS:
				//On fait R
				break;
			case SEQUENCE_ANALYSIS:
				//..
				break;
			case INSTANT_ANALYSIS:
				if(channels->channels[ch] < 1300)
					channels->pos[ch] = 0 ;
				else if(channels->channels[ch] > 1300 && channels->channels[ch] < 1600)
					channels->pos[ch] = 1 ;
				else if(channels->channels[ch] > 1600)
					channels->pos[ch] = 2 ;
				else
					channels->pos[ch] = -1 ;
				break;
			default:
				break;
		}
	}
}
