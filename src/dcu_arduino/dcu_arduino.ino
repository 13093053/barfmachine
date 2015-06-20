/* Filename: dcu.c 
 * Authors: Kevin Oei, Koen van Vliet
 * For Pro-Q2
 * Description: Digital control unit firmware for speaker system
 * Status: - 
 * Notes:   - Check for MSB in parameters. If high: error condition
 *       - Implement status LEDs
 */

 /* TO-DO: Set the DDRs correctly (optional), put the right memory address values in setPot(), use the right value in toggleErrorLED() */

#include "midi.h"
#include "digipots.h"
#include <SPI.h>


void spiSend(uint8_t memcom, uint8_t data);
void setPot(int potno, uint8_t val);
void toggleErrorLED(int onoff);

void setup(){
  /* Setup I/O */
  PORTDIGIPOTS = 0xFF;
  DDRDIGIPOTS  = 0xFF;
  DDRLEDS     = 0xFF;
  PORTLEDS = 0xFF;
  /* Setup serial comms (31250-8-n-1) NOTE: THIS IS FOR PC ONLY, HAVE TO FIX FOR ATmega */
  Serial.begin(115200);
  
  /* Setup SPI bus (mode0.0) */
  SPI.begin();

  Serial.println("PRO-Q2:\"barkmachine\" test 1 - (c)2015 Kevin Oei, Koen van Vliet ");  
}

void loop() {
  int i;
  /* Reset digital potentiometers (255 is the max position) */
  static uint8_t potpos[6] = {255};
  /* Connect terminals */
  for (i = 0; i < 6; i++) {
    setPot(i,potpos[i]);
  }
  
  /* Main program loop */
    while (1) {
    uint8_t cmd, cc, vv;
    char s[50]; /* Is still being used anywhere? */
    while (Serial.available()==0); /* Wait for buffer to be empty */
    Serial.print("Got byte");
    cmd = (uint8_t)Serial.read();
    if (cmd & 0x80) { /* Check if 0b1xxxxxxx (valid MIDI command) */
      toggleErrorLED(0); /* Turn off error LED */
      while (Serial.available() == 0);
      cc = Serial.read(); /* Acquire controller number */
      if (~cc & 0x80) { /* Check if 0b0xxxxxxx (valid controller number value) */
        while (Serial.available() == 0);
        vv = Serial.read(); /* Acquire controller value */
        if (~vv & 0x80) { /* Check if 0b0xxxxxxx (valid controller value) */
          /* Check command type */
          switch (cmd) {
            case CTRL_CH:  snprintf(s, sizeof(s), "Controller %d = %d", cc, vv);
                    Serial.println(s);
                    potpos[cc] = vv;
                    setPot(cc,potpos[cc]);
                    break;
            /*case 'r':    for (i = 0; i < sizeof(potpos); i++) {
                      potpos[i] = 127;
                      setPot(i,potpos[i]);
                    }
                    break; */
            default:    Serial.println("What?");
          }
        }
        else {
          toggleErrorLED(1); /* Turn on error LED */ 
        }      }
      else {
        toggleErrorLED(1); /* Turn on error LED */ 
      }
    }
  }
}

/* The messages that are sent out are 16-bit long. SPI can only send 8-bit at one time */
/* Thus, two SPI transmissions are required for a full message to be sent */
/* The message is as follows: AAAA.CCDD.DDDD.DDDD where A is memory address, C is command and D is data. */
/* See pg.47 of DigiPot datasheet */
void spiSend(uint8_t memcom, uint8_t data) {
  SPI.transfer(memcom);                  /* Transmit memory address and command */
  SPI.transfer(data);                    /* Transmit data (the value to be written to the DigiPot) */
}

void setPot(int potno, uint8_t val) {
  /* Select the CS of the correct IC. Note that a low signal will 'activate' the IC. */
  /* ADDRESS MEMORY STILL NEEDS TO BE FILLED IN */
  Serial.print("Changing potentiometer #");
    Serial.print(potno);
    Serial.println("!");
  switch (potno) {
    case 0: PORTDIGIPOTS &= ~(1 << VOLUME_CS_PIN);
        spiSend(VOLUME_REG, val);
                                break;
    case 1: PORTDIGIPOTS &= ~(1 << BALANCE_CS_PIN);
        spiSend(BALANCE_REG, val);
                                break;
    case 2: PORTDIGIPOTS &= ~(1 << BASS_CUT_CS_PIN);
      spiSend(BASS_CUT_REG, val);
                        break;
    case 3: PORTDIGIPOTS &= ~(1 << TREBLE_CUT_CS_PIN);
            spiSend(TREBLE_CUT_REG, val);
                        break;
    case 4: PORTDIGIPOTS &= ~(1 << BASS_BOOST_CS_PIN);
        spiSend(BASS_BOOST_REG, val);
                                break;
    case 5: PORTDIGIPOTS &= ~(1 << TREBLE_BOOST_CS_PIN);
        spiSend(TREBLE_BOOST_REG, val);
                                break;
    default: Serial.println("Invalid potmeter ID selected.");
                                break;
  }
  PORTDIGIPOTS |= (1 << VOLUME_CS_PIN) | (1 << BALANCE_CS_PIN) | (1 << BASS_CUT_CS_PIN) | (1 << TREBLE_CUT_CS_PIN) | (1 << BASS_BOOST_CS_PIN) | (1 << TREBLE_BOOST_CS_PIN) ;
}

void toggleErrorLED(int onoff) {
  if (onoff == 0) {
    PORTLEDS &= ~(1<<ERRORLEDPIN);
  }
  else {
    PORTLEDS |= (1<<ERRORLEDPIN);
  }
  
}


