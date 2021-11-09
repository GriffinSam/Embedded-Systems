#include "uop_msb.h"
#include <chrono>
#include <cstdint>
using namespace uop_msb;
using namespace chrono;
//BusOut lights(PC_2, PC_3, PC_6);
DigitalOut greenLED(PC_6);
DigitalOut yellowLED(PC_3);
DigitalOut redLED(PC_2);

//Fun output stuff
LCD_16X2_DISPLAY disp;
Buzzer buzz;
LatchedLED ledDisp(LatchedLED::STRIP);

//Analogue Inputs
AnalogIn pot(AN_POT_PIN);
AnalogIn ldr(AN_LDR_PIN);
AnalogIn mic(MIC_AN_PIN);
void redbar (){
ledDisp.setGroup(LatchedLED::LEDGROUP::RED);
    for (unsigned int n=0; n<8; n++) {
        ledDisp = 1 << n;
        wait_us(250000);
    }
    ledDisp = 0;
}
void greenbar (){
ledDisp.setGroup(LatchedLED::LEDGROUP::GREEN);
    for (unsigned int n=0; n<8; n++) {
        ledDisp = 1 << n;
        wait_us(250000);
    }
    ledDisp = 0;
}
void bluebar(){
ledDisp.setGroup(LatchedLED::LEDGROUP::BLUE);
    for (unsigned int n=0; n<8; n++) {
        ledDisp = 1 << n;
        wait_us(250000);
    }     
    ledDisp = 0;
}



int main()
{

    //Test LED Bar Display
    ledDisp.enable(true);

    

    
    
    


    while (true) {
        //Read Analog to Digital Converter values (16 bit)
        redLED = 0;
        unsigned short potVal   = pot.read_u16();
        unsigned short lightVal = ldr.read_u16();
        unsigned short micVal   = mic.read_u16(); 

        //Write to terminal
        printf("--------------------------------\n");
        printf("Potentiometer: %x\n", potVal);
        printf("Light Dependant Resistor: %X\n", lightVal);
        printf("Microphone: %X\n", micVal);   
        if (lightVal < 0x2000) {
            greenbar();}

        if (potVal > 0x8000){
           redbar();
        }
        if (micVal > 0x9200){
            bluebar();

        }
        //Wait 0.25 seconds
        wait_us(500000);

    }
}

