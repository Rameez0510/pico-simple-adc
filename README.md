 # Pico Simple ADC and PWM
- This repository contains a simple example of using the ADC and PWM on the Raspberry Pi Pico.  
- It also shows the ADC read value on a MAX7219 LED dot matrix display.

## Commit 1: ADC demonstration
- In this, an LDR and a 10k ohm resistor are connected in series to the ADC pin of the Pico.
- The ADC value is read using a repeating timer callback.
- The value of ADC is displayed on the MAX7219 LED dot matrix display.