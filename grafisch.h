#pragma once

/*
De biColor LED matrix is eigenlijk een scherm waar twee led matrixen samen zitten.
Elke matrix heeft een eigen MAX7221 chip die zijn kleur aanstuurt.
Het scherm kan je dus eigenlijk zien als twee afzonderlijk aan te sturen schermen, waarbij elk "scherm" een kleur is.

Het is niet mogelijk beide schermen tegelijk aan te zetten. Daarom wordt een ISR timer gebruikt die constant het ene scherm aanzet, dan weer uitziet, dan het andere aan zet, en weer uit zet, enz...
*/

#include <LedControl.h>

#define ISR_FREQ 190 //190=650Hz    // Snelheid van de timer: standaard laten
#define GREEN 1      // Nummer van het "groene scherm"
#define RED 0        // Nummer van het "rode scherm"

int maxInShutdown = GREEN; // Houdt bij welk "scherm" momenteel uit staat (nodig voor switchen tussen de schermen)

// DATA IN-pin, CLK-pin, LOAD(/CS)-pin, aantal schermen
LedControl lc = LedControl(2, 3, 4, 2); // Hier moet je je eigen poortnummers invullen. Enkel het getal dat zegt hoeveel scherm er aangesloten zijn moet je nu op 2 zetten

/////////   Aangepaste Methodes om met kleurenscherm te werken //////////
/////////   Enkel SetLed en ClearMatrix heb je nodig, de andere twee gebruiken we eigenlijk niet //////////

void startISR()
{                          // Starts the ISR
  TCNT2 = 0;               // clear counter (needed here also)
  TIMSK2 |= (1 << OCIE2A); // set interrupts=enabled (calls ISR(TIMER2_COMPA_vect)
}

void stopISR()
{                           // Stops the ISR
  TIMSK2 &= ~(1 << OCIE2A); // disable interrupts
}

void SetLed(byte Color, byte Row, byte Col, byte State)
{
  stopISR(); // disable interrupts - stop toggling shutdown when updating
  lc.setLed(Color, Row, Col, State);
  startISR(); // enable interrupts again
}

void SetRow(byte Color, byte Row, byte State)
{
  stopISR(); // disable interrupts - stop toggling shutdown when updating
  lc.setRow(Color, Row, State);
  startISR(); // enable interrupts again
}

void SetColumn(byte Color, byte Col, byte State)
{
  stopISR(); // disable interrupts - stop toggling shutdown when updating
  lc.setColumn(Color, Col, State);
  startISR(); // enable interrupts again
}

void ClearMatrix()
{
  stopISR(); // disable interrupts - stop toggling shutdown when updating
  lc.clearDisplay(GREEN);
  lc.clearDisplay(RED);
  startISR(); // enable interrupts again
}

/////////   Methodes die de timer besturen, gewoon overnemen - niet aanpassen //////////
void setISRtimer()
{                   // setup ISR timer controling toggleing
  TCCR2A = 0x02;    // WGM22=0 + WGM21=1 + WGM20=0 = Mode2 (CTC)
  TCCR2B = 0x05;    // CS22=1 + CS21=0 + CS20=1 = /128 prescaler (125kHz)
  TCNT2 = 0;        // clear counter
  OCR2A = ISR_FREQ; // set TOP (divisor) - see #define
}

ISR(TIMER2_COMPA_vect)
{ //This ISR toggles shutdown between the 2MAX7221's
  if (maxInShutdown == RED)
  {
    lc.shutdown(GREEN, true); // The order here is critical - Shutdown first!
    lc.shutdown(RED, false);  // . . . Then restart the other.
    maxInShutdown = GREEN;
  }
  else
  {
    lc.shutdown(RED, true);
    lc.shutdown(GREEN, false);
    maxInShutdown = RED;
  }
}

void teken_pixel(int x, int y, int color)
{
  if (x >= 0 && x < 8)
  {
    if (y >= 0 && y < 8)
    {
      SetLed(0, x, y, true);
    }
  }
}

void teken_leegte(int x, int y, int color)
{
  if (x >= 0 && x < 8)
  {
    if (y >= 0 && y < 8)
    {
      SetLed(0, x, y, false);
    }
  }
}

void teken_sterfte()
{
  // teken een X op het scherm
  if (huidigeFrame % 2 == 1)
  {
    for (int i = 0; i < 8; i++)
    {
      teken_pixel(i, i, GREEN);
      teken_pixel(7 - i, i, RED);
    }
  }
}
void led_setup()
{
  lc.setIntensity(0, 15); // 0 = dim, 15 = full brightness
  //setISRtimer(); // setup the timer
  //startISR();    // start the timer to toggle shutdown
}
