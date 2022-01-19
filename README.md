# Lung_Impeadance_Device

This GitHub repository contains all the codes that were used in the creation of a lung impedance measurement device. The final codes used are the 'Sweeping_Sine_Wave', which produces a sine wave output that increases at 5 Hz frequency intervals from 5 to 25 Hz at the DAC pin output. The mentioned code is run on the Teensy-LC note different to Arduino library. The 'Complete_Code' is the final code used with the Teensy 4.0 which reads pressure data from two bidirectional pressure sensors and converts their value to pressure in kPa and flow L/s. The fast Fourier transofrm is computed of both of these parameters obtaining the real and imaginary values of both. The following part computes the complex ratio between these two values to obtain a final real and imaginary value which corresponds to resistance and reactance of the lungs. 

For more information of the circuits, literature or methodology behind this code, you can contact me at the following e-mail:
s1709505@ed.ac.uk 
