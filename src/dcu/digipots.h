/* TO-DO: fill in all correct values for everything. Also consider whether PORTs are active high/low. */
#ifndef DIGIPOTS_H
	#define DDRDIGIPOTS         DDRx    /* Data Direction Register for DigiPots */
	#define PORTDIGIPOTS        PORTx   /* Port for DigiPots */

	#define DDRLEDS             DDRx    /* Data Direction Register for LED(s) */
	#define PORTLEDS            PORTx   /* Port for LED(s) */

	#define VOLUME_CS_PIN       0x00    /* Pin for volume control CS */
	#define BALANCE_CS_PIN      0x00    /* Pin for balance control CS */
	#define BASS_CUT_CS_PIN     0x00    /* Pin for bass cut control CS */
	#define TREBLE_CUT_CS_PIN   0x00    /* Pin for treble cut control CS */
	#define BASS_BOOST_CS_PIN   0x00    /* Pin for bass boost control CS */
	#define TREBLE_BOOST_CS_PIN 0x00    /* Pin for treble boost control CS */

	#define DIGIPOTVAL_PIN      0x00    /* Pin for the value to be loaded into the DigiPot */
#endif
