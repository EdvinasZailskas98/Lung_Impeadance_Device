#include <SoftwareSerial.h>

SoftwareSerial BTHC08Serial(21, 20); // RX | TX
// Connect the HC-08 TX to Arduino pin 10 RX.
// Connect the HC-08 RX to Arduino pin 11 TX through a voltage divider.

void setup()
{
   pinMode(16, OUTPUT);// this pin will pull the HC-05 
  digitalWrite(16, HIGH);
    pinMode(17, OUTPUT);
  digitalWrite(17, LOW);
  
  Serial.begin(9600);
  BTHC08Serial.begin(9600);
    delay (3000);
/*
  BTHC08Serial.println(-0.58);
  delay (2500);
  BTHC08Serial.println(-1.56);
  delay (2500);
  BTHC08Serial.println(-2.46);
*/

for (int i = 0; i <= 5; i++) {
    BTHC08Serial.write(i);
    delay(3000);
  }
for (int i = 0; i <= 5; i++) {
    BTHC08Serial.write(i);
    delay(3000);
  }
  }


void loop()

{
//    Serial.write(10,DEC);
  
}
