/*
 *  Control Motor Speed Through Light Sensor (e.g. Photoresistor).
 *
 *  Copyright (C) 2010 Efstathios Chatzikyriakidis (stathis.chatzikyriakidis@gmail.com)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

const int motorPin = 9;  // the pin number (PWM) for the motor.
const int sensorPin = 0; // the pin number for the input sensor.

// new and old values (speed) for motor device.
int newValue = 0;
int oldValue = 0;

// the following values may change according to the light sensor.
// perform a calibration with pure dark, and pure light at first.

const int sensorMin = 0;   // set the appropriate value of the light sensor.
const int sensorMax = 900; // set the appropriate value of the light sensor.

const int LIGHT_SENSE = 5; // difference level sensitivity value.
const long delayTime = 30; // motor delay time in millis.

// startup point entry (runs once).
void setup () {
  // set sensor as input.
  pinMode(sensorPin, INPUT);

  // set motor as output.
  pinMode(motorPin, OUTPUT);
}

// loop the main sketch.
void loop () {
  // get the value from the light sensor.
  newValue = analogRead(sensorPin);

  // map the value to the min, max of the motor.
  newValue = map (newValue, sensorMin, sensorMax, 20, 255);

  // ensure that the value is between min, max of the motor.
  newValue = constrain(newValue, 20, 255);

  // assume the new value only if there was enough difference.
  if (abs(newValue - oldValue) > LIGHT_SENSE) {
    // get the new value.
    oldValue = newValue;
  }

  // set the signal to the motor.
  analogWrite(motorPin, oldValue);
  
  // wait some time the motor to move.
  delay(delayTime);
}
