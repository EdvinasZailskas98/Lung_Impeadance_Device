#include <SoftwareSerial.h>

SoftwareSerial BTHC08Serial(21, 20); // RX | TX      Declaring pins for receiving and transmitting serial data 
                                     //              to and from the bluetooth module
byte sine_data [91]=
 {
0,  
4,    9,    13,   18,   22,   27,   31,   35,   40,   44, 
49,   53,   57,   62,   66,   70,   75,   79,   83,   87, 
91,   96,   100,  104,  108,  112,  116,  120,  124,  127,  
131,  135,  139,  143,  146,  150,  153,  157,  160,  164,    //Sine Data used for Fast Fourier Transform
167,  171,  174,  177,  180,  183,  186,  189,  192,  195,       
198,  201,  204,  206,  209,  211,  214,  216,  219,  221,  
223,  225,  227,  229,  231,  233,  235,  236,  238,  240,  
241,  243,  244,  245,  246,  247,  248,  249,  250,  251,  
252,  253,  253,  254,  254,  254,  255,  255,  255,  255
  };

float Freq_Flow[32], Real_Flow[32], Imag_Flow[32];            //Storing Frequency, Imaginary and Real values of flow
float Freq_MP[32], Real_MP[32], Imag_MP[32];                  //Storing Frequency, Imaginary and Real values of mouth pressure
float F_Freq[4], F_Real[4], F_Imag[4];                        //5 values for frequencies of 5, 10, 15, 20 and 25Hz

float FlowSensor  = 19;   //Flow Differential Pressure Sensor at A1 input
float MouthSensor = 18;   //Mouth Differential Pressure Sensor at A2 input
int   RedLed      = 22 ;
int   GreenLed    = 23 ;

float FlowPressureReading  =0;   //Storing Variable ADC
float MouthPressureReading =0;  //Storing Variable ADC

float FlowPressureVoltage;       //Voltage Val
float MouthPressureVoltage;       //Voltage Val

float PreFlowPressure;       //pre unit conversion 
float PreMouthPressure;       //pre unit conversion

float Flow[4096];              //Final Flow Value L/s
float MouthPressure[4096];       //Final Pressure Value kPa





//--------------------------------------------------------------------------------------------------------------
void loop() {
  int i;
  float Vdd = 5;
  for (i = 0; i < 4096; i++)
    {
      FlowPressureReading  = analogRead(FlowSensor);
      MouthPressureReading = analogRead(MouthSensor);                   //Read ADC value of both sensors
      
      FlowPressureVoltage  = FlowPressureReading  * (5.0 / 1023.0);     //Voltage of pressure at pneumotach
      MouthPressureVoltage = MouthPressureReading * (5.0 / 1023.0);     //Voltage of pressure at pneumotach

      PreFlowPressure  = (((FlowPressureVoltage/Vdd)-0.5)  * pow(((FlowPressureVoltage/(Vdd * 0.4))-1.25),2)  * 525.0);     // flow value but prior to conversion from Pa to L/s
      PreMouthPressure = (((MouthPressureVoltage/Vdd)-0.5) * pow(((MouthPressureVoltage/(Vdd * 0.4))-1.25),2) * 525.0);     // pressure value prior to converting from Pa to kPa

      Flow[i]          = ((PreFlowPressure * 21.24) /1000.0);    // flow value in L/s
      MouthPressure[i] = (PreMouthPressure / 1000.0);              // pressure value in kPa
      
    }

FFT(Flow, 4096, 60, Freq_Flow, Real_Flow, Imag_Flow);                  //Performing FFT of Flow
FFT(MouthPressure, 4096, 60, Freq_MP, Real_MP, Imag_MP);               //Performing FFT of mouth pressure


 for(int i = 0; i < 4096; i++)
{
  Serial.println(Freq_Flow[i]);
  delay(50);
  //Serial.println(Real_Flow[i]);
 // delay(50);
// Serial.println(Imag_Flow[i]);                                          //Printing values of FFT transformation
 // delay(50);
  
}

/*
for (int i = 0; i < 4096; i++){
  if ( Freq_MP[i] < 5.05 && Freq_MP[i] > 4.95 ){
  F_Real[0] = complex_division_Real(Real_MP[i], Real_Flow[i], Imag_MP[i], Imag_Flow[i]);   //Perform complex ratio using real and imaginary values
  F_Imag[0] = complex_division_Imag(Real_MP[i], Real_Flow[i], Imag_MP[i], Imag_Flow[i]);   //at 5Hz
  F_Freq [0] = 5;
  }
  else if (Freq_MP[i] < 10.05 && Freq_MP[i] > 9.95 ){
  F_Real[1] = complex_division_Real(Real_MP[i], Real_Flow[i], Imag_MP[i], Imag_Flow[i]);   //Perform complex ratio using real and imaginary values
  F_Imag[1] = complex_division_Imag(Real_MP[i], Real_Flow[i], Imag_MP[i], Imag_Flow[i]);   //at 10 Hz
  F_Freq [1] = 10; 
}
  else if (Freq_MP[i] < 15.05 && Freq_MP[i] > 14.95){
  F_Real[2] = complex_division_Real(Real_MP[i], Real_Flow[i], Imag_MP[i], Imag_Flow[i]);   //Perform complex ratio using real and imaginary values
  F_Imag[2] = complex_division_Imag(Real_MP[i], Real_Flow[i], Imag_MP[i], Imag_Flow[i]);   //at 15Hz
  F_Freq [2] = 15;
}
  else if (Freq_MP[i] < 20.05 && Freq_MP[i] > 19.95 ){
  F_Real[3] = complex_division_Real(Real_MP[i], Real_Flow[i], Imag_MP[i], Imag_Flow[i]);   //Perform complex ratio using real and imaginary values
  F_Imag[3] = complex_division_Imag(Real_MP[i], Real_Flow[i], Imag_MP[i], Imag_Flow[i]);   //at 20Hz
  F_Freq [3] =20;
}
  else if (Freq_MP[i] < 25.05 && Freq_MP[i] > 24.95 ){
  F_Real[4] = complex_division_Real(Real_MP[i], Real_Flow[i], Imag_MP[i], Imag_Flow[i]);   //Perform complex ratio using real and imaginary values
  F_Imag[4] = complex_division_Imag(Real_MP[i], Real_Flow[i], Imag_MP[i], Imag_Flow[i]);   //at 25Hz
  F_Freq [4] = 25;
}}



for (int i = 0; i <= 5; i++) {
    BTHC08Serial.write(F_Real[i]);                //Send 5 calculated real values to HC08
    delay(1500);
  }
  
for (int i = 0; i <= 5; i++) {
    BTHC08Serial.write(F_Imag[i]);                //Send 5 calculated imaginary values to HC08
    delay(1500);
  }

for (int i = 0; i <= 5; i++) {
    BTHC08Serial.write(F_Freq[i]);                //Send corresponding frequency of above calculations
    delay(1500);                                  //delay set to 1500 because rate of LightBlue app on phone 
  }                                               //for receiving data is too slow
digitalWrite(GreenLed, LOW);
*/
}

//-------------------------------------------------------------------------------------------------------------
void setup() {

Serial.begin(9600);
BTHC08Serial.begin(9600);
  
  pinMode(16, OUTPUT);// VDD for the HC-08 Bluetooth Module
  digitalWrite(16, HIGH);
  
  pinMode(17, OUTPUT); // GND for the HC-08 Bluetooth Module
  digitalWrite(17, LOW);

  pinMode(RedLed, OUTPUT);
  pinMode(GreenLed, OUTPUT);
  digitalWrite(RedLed, HIGH); //RED light on when not recording measurement
  
  delay(5000);
  digitalWrite(RedLed, LOW);    //Once measurement begins RED LED off
  digitalWrite(GreenLed, HIGH); //and Green LED comes on


}


//--------------------------------------------------------------------------------------------------------------


float FFT(float in[],int N,float Frequency, float freq[], float reali[], float imagi[])
{
/*
Term:
1. in[]     : Data array, 
2. N        : Number of sample (recommended sample size 2,4,8,16,32,64,128...)
3. Frequency: sampling frequency required as input (Hz)
*/

unsigned int data[13]={1,2,4,8,16,32,64,128,256,512,1024,2048};
int a,c1,f,o,x;
a=N;  
                                 
      for(int i=0;i<12;i++)                 //calculating the levels
         { if(data[i]<=a){o=i;} }
      
int in_ps[data[o]]={};     //input for sequencing
float out_r[data[o]]={};   //real part of transform
float out_im[data[o]]={};  //imaginory part of transform
float out_f[data[o]]={};  //frequency of transform


           
x=0;  
      for(int b=0;b<o;b++)                     // bit reversal
         {
          c1=data[b];
          f=data[o]/(c1+c1);
                for(int j=0;j<c1;j++)
                    { 
                     x=x+1;
                     in_ps[x]=in_ps[j]+f;
                    }
         }

 
      for(int i=0;i<data[o];i++)            // update input array as per bit reverse order
         {
          if(in_ps[i]<a)
          {out_r[i]=in[in_ps[i]];}
          if(in_ps[i]>a)
          {out_r[i]=in[in_ps[i]-a];}      
         }


int i10,i11,n1;
float e,c,s,tr,ti;

    for(int i=0;i<o;i++)                                    //fft
    {
     i10=data[i];              // overall values of sine/cosine  :
     i11=data[o]/data[i+1];    // loop with similar sine cosine:
     e=360/data[i+1];
     e=0-e;
     n1=0;

          for(int j=0;j<i10;j++)
          {
          c=cosine(e*j);
          s=sine(e*j);    
          n1=j;
          
                for(int k=0;k<i11;k++)
                 {
                 tr=c*out_r[i10+n1]-s*out_im[i10+n1];
                 ti=s*out_r[i10+n1]+c*out_im[i10+n1];
          
                 out_r[n1+i10]=out_r[n1]-tr;
                 out_r[n1]=out_r[n1]+tr;
          
                 out_im[n1+i10]=out_im[n1]-ti;
                 out_im[n1]=out_im[n1]+ti;          
          
                 n1=n1+i10+i10;              
                  }       
             }
     }


for(int i=0;i<data[o];i++)
{

out_f[i]=i*Frequency/N;                                    // Frequency
if (out_f[i] > 4.95 && out_f[i] < 25.05 ){
freq [i] = out_f[i]; 
reali[i] = out_r[i];                                            //Array of Real values and their corresponding
imagi[i] = out_im[i];                                           //imaginary values from the FFT
}
else {
freq [i] = 0; 
reali[i] = 0;                                            //Array of Real values and their corresponding
imagi[i] = 0; 
}
}}
//-----------------------------------------------------------------------------------------------------------------

float complex_division_Imag(float realA, float realB, float imagA, float imagB) {
  float divide     = (pow(realB, 2)) + (pow(imagB, 2));
  float Real       = (realA * realB);
  float imaginary  = (imagA *  imagB);
  float num2       = (imagA * realB) - (realA * imagB);                                 //Imaginary Value of Complex Ratio Function
  float out_imag   = num2 / divide;
  return (out_imag);
}

//--------------------------------------------------------------------------------------------------

float complex_division_Real(float realA, float realB, float imagA, float imagB) {
  float divide     = (pow(realB, 2)) + (pow(imagB, 2));
  float Real       = (realA * realB);
  float imaginary  = (imagA *  imagB); 
  float num1       = Real + imaginary;                                                 //Real Value of Complex Ratio Function
  float out_real   = num1 / divide;
  return (out_real);
}

//--------------------------------------------------------------------------------------------- 

float sine(int i)
{
  int j=i;
  float out;
  while(j<0){j=j+360;}
  while(j>360){j=j-360;}
  if(j>-1   && j<91){out= sine_data[j];}
  else if(j>90  && j<181){out= sine_data[180-j];}
  else if(j>180 && j<271){out= -sine_data[j-180];}
  else if(j>270 && j<361){out= -sine_data[360-j];}
  return (out/255);
}

float cosine(int i)
{
  int j=i;
  float out;
  while(j<0){j=j+360;}
  while(j>360){j=j-360;}
  if(j>-1   && j<91){out= sine_data[90-j];}
  else if(j>90  && j<181){out= -sine_data[j-90];}
  else if(j>180 && j<271){out= -sine_data[270-j];}
  else if(j>270 && j<361){out= sine_data[j-270];}
  return (out/255);

//-----------------------------------------------------------------------------------------------
}
