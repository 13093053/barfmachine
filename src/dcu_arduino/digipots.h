/* TO-DO: fill in all correct values for everything. Also consider whether PORTs are active high/low. */
#ifndef DIGIPOTS_H
	#define DDRDIGIPOTS         DDRC    /* Data Direction Register for DigiPots */
	#define PORTDIGIPOTS        PORTC   /* Port for DigiPots */

	#define DDRLEDS             DDRC    /* Data Direction Register for LED(s) */
	#define PORTLEDS            PORTC   /* Port for LED(s) */
	#define ERRORLEDPIN			3		/* Pin for error LED */

	#define VOLUME_CS_PIN       2    /* Pin for volume control CS */
	#define BALANCE_CS_PIN      2    /* Pin for balance control CS */
	#define BASS_CUT_CS_PIN     1    /* Pin for bass cut control CS */
	#define TREBLE_CUT_CS_PIN   1    /* Pin for treble cut control CS */
	#define BASS_BOOST_CS_PIN   0    /* Pin for bass boost control CS */
	#define TREBLE_BOOST_CS_PIN 0    /* Pin for treble boost control CS */

        #define VOLUME_REG          0x00
        #define BALANCE_REG         0x01
        #define BASS_CUT_REG        0x00
        #define TREBLE_CUT_REG      0x01
        #define BASS_BOOST_REG      0x00
        #define TREBLE_BOOST_REG    0x01

	#define DIGIPOTVAL_PIN      0x00    /* Pin for the value to be loaded into the DigiPot */
#endif
