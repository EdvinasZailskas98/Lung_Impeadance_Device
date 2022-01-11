void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  int aReal = 5;
  int aImag = 7;

  int bReal = 6;
  float bImag = 5.5;

  float ResR, ResI;
  
 ResI = complex_division_Imag(aReal, bReal, aImag, bImag);
 ResR = complex_division_Real(aReal, bReal, aImag, bImag);
 
 Serial.println(ResR);
 delay (1000);
 Serial.println(ResI);


  
}

float complex_division_Imag(float realA, float realB, float imagA, float imagB) {
  float divide     = (pow(realB, 2)) + (pow(imagB, 2));
  float Real       = (realA * realB);
  float imaginary  = (imagA *  imagB);
  float num2       = (imagA * realB) - (realA * imagB);
  float out_imag   = num2 / divide;
  return (out_imag);
}


float complex_division_Real(float realA, float realB, float imagA, float imagB) {
  float divide     = (pow(realB, 2)) + (pow(imagB, 2));
  float Real       = (realA * realB);
  float imaginary  = (imagA *  imagB);
  float num1       = Real + imaginary;
  float out_real   = num1 / divide;
  return (out_real);
}


















void loop() {
  // put your main code here, to run repeatedly:

}
