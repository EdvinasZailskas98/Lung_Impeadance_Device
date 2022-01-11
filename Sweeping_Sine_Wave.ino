#include <Audio.h>

AudioSynthWaveformSine   sine1;          
AudioOutputAnalog        dac1;           
AudioConnection          patchCord1(sine1, dac1);

int startup_time      = 5000;
int time_5Hz          = 6000;
int time_10Hz         = 6000;
int time_15Hz         = 6000;
int time_20Hz         = 6000;
int time_25Hz         = 6000;
//int time_30Hz         = 3400;

void setup() {

  delay(startup_time);
  
  AudioMemory(2);
  sine1.frequency(5); 
  sine1.amplitude(0.115);
  delay(time_5Hz);

  sine1.frequency(10); 
  sine1.amplitude(0.072);
  delay(time_10Hz);

  sine1.frequency(15); 
  sine1.amplitude(0.065);
  delay(time_15Hz);

  sine1.frequency(20); 
  sine1.amplitude(0.062);
  delay(time_20Hz);

  sine1.frequency(25); 
  sine1.amplitude(0.061);
  delay(time_25Hz);
/*
  sine1.frequency(30); 
  sine1.amplitude(0.0605);
  delay(time_30Hz);
*/
}

void loop() {
  
 }
