/* TO-DO: fill in all correct values for everything. Also consider whether PORTs are active high/low. */
#ifndef DIGIPOTS_H
	#define DDRDIGIPOTS         DDRC    /* Data Direction Register for DigiPots */
	#define PORTDIGIPOTS        PORTC   /* Port for DigiPots */

	#define DDRLEDS             DDRD    /* Data Direction Register for LED(s) */
	#define PORTLEDS            PORTD   /* Port for LED(s) */
	#define ERRORLEDPIN			2		/* Pin for error LED */

	#define VOLUME_CS_PIN       0x00    /* Pin for volume control CS */
	#define BALANCE_CS_PIN      0x00    /* Pin for balance control CS */
	#define BASS_CUT_CS_PIN     0x00    /* Pin for bass cut control CS */
	#define TREBLE_CUT_CS_PIN   0x00    /* Pin for treble cut control CS */
	#define BASS_BOOST_CS_PIN   0x00    /* Pin for bass boost control CS */
	#define TREBLE_BOOST_CS_PIN 0x00    /* Pin for treble boost control CS */

	#define DIGIPOTVAL_PIN      0x00    /* Pin for the value to be loaded into the DigiPot */
#endif
