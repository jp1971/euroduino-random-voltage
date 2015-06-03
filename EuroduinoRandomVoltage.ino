 /*
    Telekinetic     
                   n
        |\   |  or
       _| \-/ic
      /    un
    //    ~ + \
   //         |
  //    \      \
 |||     | .  .|
///     / \___/

*/

/* Random Voltage Generator
 * ------------------------
 * This sketch reads the values of the two Euroduino potentiometers.
 * The values are next run through the map function to scale the range
 * and invert the rate.  The values are then passed to the random function
 * that generates values for the analogWrite and delay functions.
 */
 
/*  Copyright 2015 JP1971 (jameson@jp1971.com)

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/

// These constants won't change.  They're used to give names
// to the pins used:
const int analogIn1Pin = A0;  // Analog Input 1
const int analogIn2Pin = A1; // Analog Input 2
const int analogPot1Pin = A2;  // Pot 1
const int analogPot2Pin = A3; // Pot 2
const int analogOut1Pin = 5;  // Analog Output 1
const int analogOut2Pin = 6; // Analog Output 2
const int DigitalIn1Pin = 8;  // Digital Input 1
const int DigitalIn2Pin = 9;  // Digital Input 2
const int DigitalOut1Pin = 3;  // Digital Output 1
const int DigitalOut2Pin = 4;  // Digital Output 2
const int Switch1Up = A4;  // Switch 1 Up
const int Switch1Dwn = A5;  // Switch 1 Dwn
const int Switch2Up = 7;  // Switch 2 Up
const int Switch2Dwn = 2;  // Switch 2 Dwn

// Leave these values alone
int range1 = 0;
int rate1 = 0;
int range2 = 0;
int rate2 = 0;
char switch1;
char switch2;

void setup() {
  /* Set up I/O pins */
  pinMode( DigitalIn1Pin, INPUT );
  pinMode( DigitalIn2Pin, INPUT );
  pinMode( DigitalOut1Pin, OUTPUT ); 
  pinMode( DigitalOut2Pin, OUTPUT ); 
  pinMode( Switch1Up, INPUT_PULLUP );
  pinMode( Switch1Dwn, INPUT_PULLUP );
  pinMode( Switch2Up, INPUT_PULLUP );
  pinMode( Switch2Dwn, INPUT_PULLUP );
  Serial.begin(9600);
}

void loop() {
  
  // Potentiometer controlled random voltage
  
  // Read range potentiometer
  range1 = analogRead( analogPot1Pin );
  
  // Map value to scale appropriate for analogWrite
  range1 = map( range1, 0, 1023, 0, 255 );
  
  // Print value in serial monitor to debug
  // Serial.print( "range1: " );
  // Serial.println( range1 );
  
  // Read rate potentiometer
  rate1 = analogRead( analogPot2Pin );
  
  // If rate is less than 100, set it to 100.
  if( rate1 < 100 ) {
    rate1 = 100;
  }
  
  // Use map to invert value
  rate1 = map( rate1, 100, 1023, 1023, 100 );
  
  // Print value in serial monitor to debug
//  Serial.print( "rate1: " );
//  Serial.println( rate1 );
  
  // Process switches
  if ( digitalRead( Switch1Up ) == LOW) {
    switch1 = 'u';
  } else if ( digitalRead( Switch1Dwn ) == LOW ) {
    switch1 = 'm';
  } else {
    switch1 = 'd';
  }
  
  // Write CV
  analogWrite( analogOut1Pin, random( 0, range1 ) );
  
  // Write Digital Out
  if ( range1 > 511 ) {
    digitalWrite( DigitalOut1Pin, HIGH );
  } else {
    digitalWrite( DigitalOut1Pin, LOW );
  }
  // Wait
  if ( switch1 = 'u' ) {
    delay( rate1 / 2 );
  } else {
    delay( random( 0, ( rate1 ) ) );
  }
  
  // Control voltage controlled random voltage
  // Read range potentiometer
  range2 = analogRead( analogIn1Pin );
  // Map value to scale appropriate for analogWrite
  range2 = map( range2, 0, 1023, 0, 255 );
//  Serial.print( "range2: " );
//  Serial.println( range2 );
  // Read range potentiometer
  rate2 = analogRead( analogIn2Pin );
  // If rate is less than 100, set it to 100.
  if( rate2 < 100 ) {
    rate2 = 100;
  }
  // Use map to invert value
  rate2 = map( rate2, 100, 1023, 1023, 100 );
//  Serial.print( "rate2: " );
//  Serial.println( rate2 );
  // Write CV
  analogWrite( analogOut2Pin, random( 0, range2 ) );
  // Write Digital Out
  if ( range2 > 511 ) {
    digitalWrite( DigitalOut2Pin, HIGH );
  } else {
    digitalWrite( DigitalOut2Pin, LOW );
  }
  // Wait
  delay( rate2 );
}
