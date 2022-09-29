/************************************************************************************************
 * Ver:     1.2
 * MCU:     ATtiny1616-M
 * Clock:   1MHz Internal
 * Timer:   Enabled (default timer)
 * Startup: 8ms
 * BOD VL:  1.8V
 * EEPROM:  EEPROM Retained
 * 
 * Uses One Button Library from Matthias Hertel https://github.com/mathertel/OneButton
 * Compiled in Arduino IDE using Spence Konde's megaTinyCore (https://github.com/SpenceKonde/megaTinyCore)
 * 
 * Copyright 2022, Hojadurdy Durdygylyjov - Curious Design Labs
 ************************************************************************************************
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
 * and associated documentation files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, publish, distribute, 
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software 
 * is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all copies or 
 * substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING 
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 ************************************************************************************************/
 
#include <EEPROM.h>
#include <OneButton.h>
#include <avr/sleep.h>

//PIN DEFINITIONS

#define setButton     12
#define powerButton   2

OneButton button(setButton, true);

const int leds[9]={16, 11, 0, 1, 10, 9, 8, 7, 6};

//VARIABLES
unsigned long pressStartTime;
byte engageSequenceBegin = 0;


byte startupMode;             //   0,   1,   2,   3
byte settingsMode;            //   0,   1,   2

byte animationSequence;       //   1,   2,   3,   4,   5,   6,   7,   8
byte animationSpeed;          // 100,  90,  80,  70,  60,  50,  40,  30
byte ledBrightness;           //  31,  63,  95, 127, 159, 191, 223, 255 

//SETTINGS EEPROM ADDRESS
#define startupModeAddr         1
#define settingsModeAddr        2
#define animationSequenceAddr   11     
#define animationSpeedAddr      12   
#define ledBrightnessAddr       13    

//---------------------------------------------------------------------------------------------------------//

void startupSequence() {
    startupMode = EEPROM.read(startupModeAddr);
    settingsMode = EEPROM.read(settingsModeAddr);
    animationSequence = EEPROM.read(animationSequenceAddr);
    animationSpeed = EEPROM.read(animationSpeedAddr);
    ledBrightness = EEPROM.read(ledBrightnessAddr);
}

void devicePowerDown() {
    for(int b=0;b<=8;b++) {
        digitalWrite(leds[b], 0);
    }
    ADC0.CTRLA &= ~ADC_ENABLE_bm;
    sleep_cpu();
}

void devicePowerUp() {
    sleep_disable();
    EEPROM.write(startupModeAddr, 1);
}

void powerOnOff() {
    if(startupMode != 2) {
        EEPROM.write(startupModeAddr, 2);
    }
    else if(startupMode == 2) {
        EEPROM.write(startupModeAddr, 3);
    } 
} 

void checkTicks() {
    button.tick();
}

void flashLEDs(byte c) {
    for(int i=0;i<c;i++) {
        for(int b=0;b<=7;b++) {
            digitalWrite(leds[b], 0);
        }
        digitalWrite(leds[8], 0);
        delay(120);
        for(int b=0;b<=7;b++) {
            digitalWrite(leds[b], 1);
        }
        delay(60);
    }
    for(int b=0;b<=7;b++) {
        digitalWrite(leds[b], 0);
    }
}

// this function will be called when the button was held down for 1 second or more.
void pressStart() {
    pressStartTime = millis() - 1000; // as set in setPressTicks()
} 

// this function will be called when the button was released after a long hold.
void deviceSettingsSelect() {
    if(startupMode == 0 && settingsMode == 0) {
        EEPROM.write(settingsModeAddr, 1);
        flashLEDs(2);
    }
    else if(startupMode == 0 && settingsMode == 1) {
        EEPROM.write(settingsModeAddr, 2);
        flashLEDs(2);
    }
    else if(startupMode == 0 && settingsMode == 2) {
        EEPROM.write(startupModeAddr, 1);
        flashLEDs(2);
    }
    else if(startupMode == 1) {
        EEPROM.write(startupModeAddr, 0);
        EEPROM.write(settingsModeAddr, 0);
        flashLEDs(2);
    }
}

void singleClick() {
    if(startupMode == 0 && settingsMode == 0) {
        if(animationSequence == 8) {
            EEPROM.write(animationSequenceAddr, 7);
        }
        else if(animationSequence == 7) {
            EEPROM.write(animationSequenceAddr, 6);
        }
        else if(animationSequence == 6) {
            EEPROM.write(animationSequenceAddr, 5);
        }
        else if(animationSequence == 5) {
            EEPROM.write(animationSequenceAddr, 4);
        }
        else if(animationSequence == 4) {
            EEPROM.write(animationSequenceAddr, 3);
        }
        else if(animationSequence == 3) {
            EEPROM.write(animationSequenceAddr, 2);
        }
        else if(animationSequence == 2) {
            EEPROM.write(animationSequenceAddr, 1);
        }
        else if(animationSequence == 1) {
            EEPROM.write(animationSequenceAddr, 8);
        }
    }
    else if(startupMode == 0 && settingsMode == 1) {
        if(animationSpeed == 100) {
            EEPROM.write(animationSpeedAddr, 90);
        }
        else if(animationSpeed == 90) {
            EEPROM.write(animationSpeedAddr, 80);
        }
        else if(animationSpeed == 80) {
            EEPROM.write(animationSpeedAddr, 70);
        }
        else if(animationSpeed == 70) {
            EEPROM.write(animationSpeedAddr, 60);
        }
        else if(animationSpeed == 60) {
            EEPROM.write(animationSpeedAddr, 50);
        }
        else if(animationSpeed == 50) {
            EEPROM.write(animationSpeedAddr, 40);
        }
        else if(animationSpeed == 40) {
            EEPROM.write(animationSpeedAddr, 30);
        }
        else if(animationSpeed == 30) {
            EEPROM.write(animationSpeedAddr, 100);
        }
    }
    else if(startupMode == 0 && settingsMode == 2) {
        if(ledBrightness == 31) {
            EEPROM.write(ledBrightnessAddr, 63);
        }
        else if(ledBrightness == 63) {
            EEPROM.write(ledBrightnessAddr, 95);
        }
        else if(ledBrightness == 95) {
            EEPROM.write(ledBrightnessAddr, 127);
        }
        else if(ledBrightness == 127) {
            EEPROM.write(ledBrightnessAddr, 159);
        }
        else if(ledBrightness == 159) {
            EEPROM.write(ledBrightnessAddr, 191);
        }
        else if(ledBrightness == 191) {
            EEPROM.write(ledBrightnessAddr, 223);
        }
        else if(ledBrightness == 223) {
            EEPROM.write(ledBrightnessAddr, 255);
        }
        else if(ledBrightness == 255) {
            EEPROM.write(ledBrightnessAddr, 31);
        }
    }
    else if (startupMode == 1) {
        engageSequenceBegin = 1;
    }
}

void showAnimationSequenceSetting() {
    if(animationSequence == 1) {
      digitalWrite(leds[0], 1);
      digitalWrite(leds[1], 0);
      digitalWrite(leds[2], 0);
      digitalWrite(leds[3], 0);
      digitalWrite(leds[4], 0);
      digitalWrite(leds[5], 0);
      digitalWrite(leds[6], 0);
      digitalWrite(leds[7], 0);
    }
    else if(animationSequence == 2) {
        digitalWrite(leds[0], 0);
        digitalWrite(leds[1], 1);
        digitalWrite(leds[2], 0);
        digitalWrite(leds[3], 0);
        digitalWrite(leds[4], 0);
        digitalWrite(leds[5], 0);
        digitalWrite(leds[6], 0);
        digitalWrite(leds[7], 0);
    }
    else if(animationSequence == 3) {
        digitalWrite(leds[0], 0);
        digitalWrite(leds[1], 0);
        digitalWrite(leds[2], 1);
        digitalWrite(leds[3], 0);
        digitalWrite(leds[4], 0);
        digitalWrite(leds[5], 0);
        digitalWrite(leds[6], 0);
        digitalWrite(leds[7], 0);
    }
    else if(animationSequence == 4) {
        digitalWrite(leds[0], 0);
        digitalWrite(leds[1], 0);
        digitalWrite(leds[2], 0);
        digitalWrite(leds[3], 1);
        digitalWrite(leds[4], 0);
        digitalWrite(leds[5], 0);
        digitalWrite(leds[6], 0);
        digitalWrite(leds[7], 0);
    }
    else if(animationSequence == 5) {
        digitalWrite(leds[0], 0);
        digitalWrite(leds[1], 0);
        digitalWrite(leds[2], 0);
        digitalWrite(leds[3], 0);
        digitalWrite(leds[4], 1);
        digitalWrite(leds[5], 0);
        digitalWrite(leds[6], 0);
        digitalWrite(leds[7], 0);
    }
    else if(animationSequence == 6) {
        digitalWrite(leds[0], 0);
        digitalWrite(leds[1], 0);
        digitalWrite(leds[2], 0);
        digitalWrite(leds[3], 0);
        digitalWrite(leds[4], 0);
        digitalWrite(leds[5], 1);
        digitalWrite(leds[6], 0);
        digitalWrite(leds[7], 0);
    }
    else if(animationSequence == 7) {
        digitalWrite(leds[0], 0);
        digitalWrite(leds[1], 0);
        digitalWrite(leds[2], 0);
        digitalWrite(leds[3], 0);
        digitalWrite(leds[4], 0);
        digitalWrite(leds[5], 0);
        digitalWrite(leds[6], 1);
        digitalWrite(leds[7], 0);
    }
    else if(animationSequence == 8) {
        digitalWrite(leds[0], 0);
        digitalWrite(leds[1], 0);
        digitalWrite(leds[2], 0);
        digitalWrite(leds[3], 0);
        digitalWrite(leds[4], 0);
        digitalWrite(leds[5], 0);
        digitalWrite(leds[6], 0);
        digitalWrite(leds[7], 1);
    }
}

void showAnimationSpeedSetting() {
    if(animationSpeed == 30) {
        digitalWrite(leds[0], 1);
        digitalWrite(leds[1], 1);
        digitalWrite(leds[2], 1);
        digitalWrite(leds[3], 1);
        digitalWrite(leds[4], 1);
        digitalWrite(leds[5], 1);
        digitalWrite(leds[6], 1);
        digitalWrite(leds[7], 1);
    }
    else if(animationSpeed == 40) {
        digitalWrite(leds[0], 0);
        digitalWrite(leds[1], 1);
        digitalWrite(leds[2], 1);
        digitalWrite(leds[3], 1);
        digitalWrite(leds[4], 1);
        digitalWrite(leds[5], 1);
        digitalWrite(leds[6], 1);
        digitalWrite(leds[7], 1);
    }
    else if(animationSpeed == 50) {
        digitalWrite(leds[0], 0);
        digitalWrite(leds[1], 0);
        digitalWrite(leds[2], 1);
        digitalWrite(leds[3], 1);
        digitalWrite(leds[4], 1);
        digitalWrite(leds[5], 1);
        digitalWrite(leds[6], 1);
        digitalWrite(leds[7], 1);
    }
    else if(animationSpeed == 60) {
        digitalWrite(leds[0], 0);
        digitalWrite(leds[1], 0);
        digitalWrite(leds[2], 0);
        digitalWrite(leds[3], 1);
        digitalWrite(leds[4], 1);
        digitalWrite(leds[5], 1);
        digitalWrite(leds[6], 1);
        digitalWrite(leds[7], 1);
    }
    else if(animationSpeed == 70) {
        digitalWrite(leds[0], 0);
        digitalWrite(leds[1], 0);
        digitalWrite(leds[2], 0);
        digitalWrite(leds[3], 0);
        digitalWrite(leds[4], 1);
        digitalWrite(leds[5], 1);
        digitalWrite(leds[6], 1);
        digitalWrite(leds[7], 1);
    }
    else if(animationSpeed == 80) {
        digitalWrite(leds[0], 0);
        digitalWrite(leds[1], 0);
        digitalWrite(leds[2], 0);
        digitalWrite(leds[3], 0);
        digitalWrite(leds[4], 0);
        digitalWrite(leds[5], 1);
        digitalWrite(leds[6], 1);
        digitalWrite(leds[7], 1);
    }
    else if(animationSpeed == 90) {
        digitalWrite(leds[0], 0);
        digitalWrite(leds[1], 0);
        digitalWrite(leds[2], 0);
        digitalWrite(leds[3], 0);
        digitalWrite(leds[4], 0);
        digitalWrite(leds[5], 0);
        digitalWrite(leds[6], 1);
        digitalWrite(leds[7], 1);
    }
    else if(animationSpeed == 100) {
        digitalWrite(leds[0], 0);
        digitalWrite(leds[1], 0);
        digitalWrite(leds[2], 0);
        digitalWrite(leds[3], 0);
        digitalWrite(leds[4], 0);
        digitalWrite(leds[5], 0);
        digitalWrite(leds[6], 0);
        digitalWrite(leds[7], 1);
    }
}

void showLEDBrightnessSetting() {
    if(ledBrightness == 255) {
        digitalWrite(leds[0], 1);
        digitalWrite(leds[1], 1);
        digitalWrite(leds[2], 1);
        digitalWrite(leds[3], 1);
        digitalWrite(leds[4], 1);
        digitalWrite(leds[5], 1);
        digitalWrite(leds[6], 1);
        digitalWrite(leds[7], 1);
    }
    else if(ledBrightness == 223) {
        digitalWrite(leds[0], 0);
        digitalWrite(leds[1], 1);
        digitalWrite(leds[2], 1);
        digitalWrite(leds[3], 1);
        digitalWrite(leds[4], 1);
        digitalWrite(leds[5], 1);
        digitalWrite(leds[6], 1);
        digitalWrite(leds[7], 1);
    }
    else if(ledBrightness == 191) {
        digitalWrite(leds[0], 0);
        digitalWrite(leds[1], 0);
        digitalWrite(leds[2], 1);
        digitalWrite(leds[3], 1);
        digitalWrite(leds[4], 1);
        digitalWrite(leds[5], 1);
        digitalWrite(leds[6], 1);
        digitalWrite(leds[7], 1);
    }
    else if(ledBrightness == 159) {
        digitalWrite(leds[0], 0);
        digitalWrite(leds[1], 0);
        digitalWrite(leds[2], 0);
        digitalWrite(leds[3], 1);
        digitalWrite(leds[4], 1);
        digitalWrite(leds[5], 1);
        digitalWrite(leds[6], 1);
        digitalWrite(leds[7], 1);
    }
    else if(ledBrightness == 127) {
        digitalWrite(leds[0], 0);
        digitalWrite(leds[1], 0);
        digitalWrite(leds[2], 0);
        digitalWrite(leds[3], 0);
        digitalWrite(leds[4], 1);
        digitalWrite(leds[5], 1);
        digitalWrite(leds[6], 1);
        digitalWrite(leds[7], 1);
    }
    else if(ledBrightness == 95) {
        digitalWrite(leds[0], 0);
        digitalWrite(leds[1], 0);
        digitalWrite(leds[2], 0);
        digitalWrite(leds[3], 0);
        digitalWrite(leds[4], 0);
        digitalWrite(leds[5], 1);
        digitalWrite(leds[6], 1);
        digitalWrite(leds[7], 1);
    }
    else if(ledBrightness == 63) {
        digitalWrite(leds[0], 0);
        digitalWrite(leds[1], 0);
        digitalWrite(leds[2], 0);
        digitalWrite(leds[3], 0);
        digitalWrite(leds[4], 0);
        digitalWrite(leds[5], 0);
        digitalWrite(leds[6], 1);
        digitalWrite(leds[7], 1);
    }
    else if(ledBrightness == 31) {
        digitalWrite(leds[0], 0);
        digitalWrite(leds[1], 0);
        digitalWrite(leds[2], 0);
        digitalWrite(leds[3], 0);
        digitalWrite(leds[4], 0);
        digitalWrite(leds[5], 0);
        digitalWrite(leds[6], 0);
        digitalWrite(leds[7], 1);
    }
}

void deviceSettings() {
    switch(settingsMode) {
        case 0:
            showAnimationSequenceSetting();
        break;

        case 1:
            showAnimationSpeedSetting();
        break;

        case 2:
            showLEDBrightnessSetting();
        break;
    }
}

void deviceRun() {
    if(engageSequenceBegin == 1) {
        engageSequence();
        engageSequenceBegin = 0;
    }
    else if(engageSequenceBegin == 0) {
        if(animationSequence == 1) {
            animationSequence1();
        }
        else if(animationSequence == 2) {
            animationSequence2();
        }
        else if(animationSequence == 3) {
            animationSequence3();
        } 
        else if(animationSequence == 4) {
            animationSequence4();
        } 
        else if(animationSequence == 5) {
            animationSequence5();
        } 
        else if(animationSequence == 6) {
            animationSequence6();
        } 
        else if(animationSequence == 7) {
            animationSequence7();
        } 
        else if(animationSequence == 8) {
            animationSequence8();
        }
    }
}

void animationSequence1() {
    float brightnessScaleVal = ledBrightness/255.00;
    analogWrite(leds[0], 31*brightnessScaleVal);
    analogWrite(leds[5], 191*brightnessScaleVal);
    analogWrite(leds[6], 223*brightnessScaleVal);
    delay(animationSpeed); 
    analogWrite(leds[0], 31*brightnessScaleVal);
    analogWrite(leds[1], 63*brightnessScaleVal);
    analogWrite(leds[6], 223*brightnessScaleVal);
    analogWrite(leds[7], 255*brightnessScaleVal);
    analogWrite(leds[5], 0);
    delay(animationSpeed);
    analogWrite(leds[1], 63*brightnessScaleVal);
    analogWrite(leds[2], 95*brightnessScaleVal);
    analogWrite(leds[7], 255*brightnessScaleVal);
    analogWrite(leds[0], 0);
    analogWrite(leds[6], 0);
    delay(animationSpeed);
    analogWrite(leds[2], 95*brightnessScaleVal);
    analogWrite(leds[3], 127*brightnessScaleVal);
    analogWrite(leds[1], 0);
    analogWrite(leds[7], 0);
    delay(animationSpeed);
    analogWrite(leds[3], 127*brightnessScaleVal);
    analogWrite(leds[4], 159*brightnessScaleVal);
    analogWrite(leds[2], 0);
    delay(animationSpeed);
    analogWrite(leds[4], 159*brightnessScaleVal);
    analogWrite(leds[5], 191*brightnessScaleVal);
    analogWrite(leds[3], 0);
    delay(animationSpeed);
    analogWrite(leds[4], 0);
}

void animationSequence2() {
    float brightnessScaleVal = ledBrightness/255.00;
    analogWrite(leds[0], 10*brightnessScaleVal);
    delay(animationSpeed); 
    analogWrite(leds[1], 30*brightnessScaleVal);
    delay(animationSpeed); 
    analogWrite(leds[2], 60*brightnessScaleVal);
    delay(animationSpeed);
    analogWrite(leds[3], 100*brightnessScaleVal);
    delay(animationSpeed);
    analogWrite(leds[4], 150*brightnessScaleVal);
    delay(animationSpeed);
    analogWrite(leds[0], 0);
    analogWrite(leds[1], 10*brightnessScaleVal);
    analogWrite(leds[2], 30*brightnessScaleVal);
    analogWrite(leds[3], 60*brightnessScaleVal);
    analogWrite(leds[4], 100*brightnessScaleVal);
    analogWrite(leds[5], 180*brightnessScaleVal);
    delay(animationSpeed);
    analogWrite(leds[1], 0);
    analogWrite(leds[2], 10*brightnessScaleVal);
    analogWrite(leds[3], 30*brightnessScaleVal);
    analogWrite(leds[4], 70*brightnessScaleVal);
    analogWrite(leds[5], 130*brightnessScaleVal);
    analogWrite(leds[6], 200*brightnessScaleVal);
    delay(animationSpeed);
    analogWrite(leds[2], 0);
    analogWrite(leds[3], 20*brightnessScaleVal);
    analogWrite(leds[4], 80*brightnessScaleVal);
    analogWrite(leds[5], 150*brightnessScaleVal);
    analogWrite(leds[6], 180*brightnessScaleVal);
    analogWrite(leds[7], 255*brightnessScaleVal);
    delay(animationSpeed);
    analogWrite(leds[3], 0);
    delay(animationSpeed);
    analogWrite(leds[4], 0);
    delay(animationSpeed);
    analogWrite(leds[5], 0);
    delay(animationSpeed);
    analogWrite(leds[6], 0);
    delay(animationSpeed);
    analogWrite(leds[7], 0);
}

void animationSequence3() {
    for(int i=0;i<=7;i++) {
        analogWrite(leds[i-1], 0);
        analogWrite(leds[i], ledBrightness);
        delay(animationSpeed);
    }
    for(int i=7;i>=0;i--) {
        analogWrite(leds[i+1], 0);
        analogWrite(leds[i], ledBrightness);
        delay(animationSpeed);
    }
}

void animationSequence4() {
    analogWrite(leds[3], ledBrightness);
    analogWrite(leds[4], ledBrightness);
    delay(animationSpeed*2.5);
    analogWrite(leds[3], 0);
    analogWrite(leds[4], 0);
    analogWrite(leds[2], ledBrightness*0.6);
    analogWrite(leds[5], ledBrightness*0.6);
    delay(animationSpeed*1.6);
    analogWrite(leds[2], 0);
    analogWrite(leds[5], 0);
    analogWrite(leds[1], ledBrightness*0.3);
    analogWrite(leds[6], ledBrightness*0.3);
    delay(animationSpeed*1.9);
    analogWrite(leds[1], 0);
    analogWrite(leds[6], 0);
    analogWrite(leds[0], ledBrightness*0.1);
    analogWrite(leds[7], ledBrightness*0.1);
    delay(animationSpeed*2.2);
    analogWrite(leds[0], 0);
    analogWrite(leds[7], 0);
    delay(animationSpeed*2.5);
}

void animationSequence5() {
    analogWrite(leds[2], 0);
    analogWrite(leds[5], 0);
    analogWrite(leds[3], ledBrightness);
    analogWrite(leds[4], ledBrightness);
    delay(animationSpeed*2.5);
    analogWrite(leds[3], 0);
    analogWrite(leds[4], 0);
    analogWrite(leds[2], ledBrightness*0.6);
    analogWrite(leds[5], ledBrightness*0.6);
    delay(animationSpeed*1.6);
    analogWrite(leds[2], 0);
    analogWrite(leds[5], 0);
    analogWrite(leds[1], ledBrightness*0.3);
    analogWrite(leds[6], ledBrightness*0.3);
    delay(animationSpeed*1.9);
    analogWrite(leds[1], 0);
    analogWrite(leds[6], 0);
    analogWrite(leds[0], ledBrightness*0.1);
    analogWrite(leds[7], ledBrightness*0.1);
    delay(animationSpeed*2.2);
    analogWrite(leds[0], 0);
    analogWrite(leds[7], 0);
    analogWrite(leds[1], ledBrightness*0.3);
    analogWrite(leds[6], ledBrightness*0.3);
    delay(animationSpeed*1.9);
    analogWrite(leds[1], 0);
    analogWrite(leds[6], 0);
    analogWrite(leds[2], ledBrightness*0.6);
    analogWrite(leds[5], ledBrightness*0.6);
    delay(animationSpeed*1.6);
}

void animationSequence6() {
    morseCode_S();  
    morseCode_O();
    morseCode_S();
    delay(600);
}

void animationSequence7() {
    for(int i=0;i<8;i++) {
        analogWrite(leds[i-1], 0);
        analogWrite(leds[i], ledBrightness);
        delay(animationSpeed/4);
    }
    digitalWrite(leds[7], 0);
    delay(60);
    for(int i=0;i<8;i++) {
        analogWrite(leds[i-1], 0);
        analogWrite(leds[i], ledBrightness);
        delay(animationSpeed/4);
    }
    digitalWrite(leds[7], 0);
    delay(500);
}

void animationSequence8() {
    for(int i=0;i<8;i++) {
        analogWrite(leds[i-1], 0);
        analogWrite(leds[i], ledBrightness);
        delay(animationSpeed);
    }
    digitalWrite(leds[7], 0);
}

void morseCode_S() {
    for(int i=0;i<8;i++) {
        analogWrite(leds[i], ledBrightness);
        digitalWrite(leds[8], 1);
    }
    delay(2*animationSpeed);
    for(int i=0;i<8;i++) {
        analogWrite(leds[i], 0);
        digitalWrite(leds[8], 0);
    }
    delay(2*animationSpeed);
    for(int i=0;i<8;i++) {
        analogWrite(leds[i], ledBrightness);
        digitalWrite(leds[8], 1);
    }
    delay(2*animationSpeed);
    for(int i=0;i<8;i++) {
        analogWrite(leds[i], 0);
        digitalWrite(leds[8], 0);
    }
    delay(2*animationSpeed);
    for(int i=0;i<8;i++) {
        analogWrite(leds[i], ledBrightness);
        digitalWrite(leds[8], 1);
    }
    delay(2*animationSpeed);
    for(int i=0;i<8;i++) {
        analogWrite(leds[i], 0);
        digitalWrite(leds[8], 0);
    }
    delay(6*animationSpeed);
}

void morseCode_O() {
    for(int i=0;i<8;i++) {
        analogWrite(leds[i], ledBrightness);
        digitalWrite(leds[8], 1);
    }
    delay(6*animationSpeed);
    for(int i=0;i<8;i++) {
        analogWrite(leds[i], 0);
        digitalWrite(leds[8], 0);
    }
    delay(2*animationSpeed);
    for(int i=0;i<8;i++) {
        analogWrite(leds[i], ledBrightness);
        digitalWrite(leds[8], 1);
    }
    delay(6*animationSpeed);
    for(int i=0;i<8;i++) {
        analogWrite(leds[i], 0);
        digitalWrite(leds[8], 0);
    }
    delay(2*animationSpeed);
    for(int i=0;i<8;i++) {
        analogWrite(leds[i], ledBrightness);
        digitalWrite(leds[8], 1);
    }
    delay(6*animationSpeed);
    for(int i=0;i<8;i++) {
        analogWrite(leds[i], 0);
        digitalWrite(leds[8], 0);
    }
    delay(6*animationSpeed);
}

void engageSequence() {
    for(int del=50;del>0;del--) {
        float brightnessScaleVal = ledBrightness/255.00;
        analogWrite(leds[0], 31*brightnessScaleVal);
        analogWrite(leds[5], 191*brightnessScaleVal);
        analogWrite(leds[6], 223*brightnessScaleVal);
        delay(30); 
        analogWrite(leds[0], 31*brightnessScaleVal);
        analogWrite(leds[1], 63*brightnessScaleVal);
        analogWrite(leds[6], 223*brightnessScaleVal);
        analogWrite(leds[7], 255*brightnessScaleVal);
        analogWrite(leds[5], 0);
        delay(30);
        analogWrite(leds[1], 63*brightnessScaleVal);
        analogWrite(leds[2], 95*brightnessScaleVal);
        analogWrite(leds[7], 255*brightnessScaleVal);
        digitalWrite(leds[8], 1);
        analogWrite(leds[0], 0);
        analogWrite(leds[6], 0);
        delay(30);
        analogWrite(leds[2], 95*brightnessScaleVal);
        analogWrite(leds[3], 127*brightnessScaleVal);
        analogWrite(leds[1], 0);
        analogWrite(leds[7], 0);
        delay(30);
        analogWrite(leds[3], 127*brightnessScaleVal);
        analogWrite(leds[4], 159*brightnessScaleVal);
        digitalWrite(leds[8], 0);
        analogWrite(leds[2], 0);
        delay(30);
        analogWrite(leds[4], 159*brightnessScaleVal);
        analogWrite(leds[5], 191*brightnessScaleVal);
        analogWrite(leds[3], 0);
        delay(30);
        analogWrite(leds[4], 0); 
    }
    flashLEDs(1);
    delay(100);
    flashLEDs(2);
}

void setup() {
    for(int i=0;i<=8;i++) {
        pinMode(leds[i], OUTPUT); 
    }
    pinMode(setButton, INPUT); 
    pinMode(powerButton, INPUT); 

    attachInterrupt(digitalPinToInterrupt(setButton), checkTicks, FALLING);
    attachInterrupt(digitalPinToInterrupt(powerButton), powerOnOff, FALLING);
    
    button.attachClick(singleClick);
    button.setPressTicks(1000); // that is the time when LongPressStart is called
    button.attachLongPressStart(pressStart);
    button.attachLongPressStop(deviceSettingsSelect);
/*
    EEPROM.write(startupModeAddr, 1);
    EEPROM.write(settingsModeAddr, 0);
    EEPROM.write(animationSequenceAddr, 1);
    EEPROM.write(animationSpeedAddr, 50);
    EEPROM.write(ledBrightnessAddr, 159);
*/
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
}

void loop() {
    button.tick();
    startupSequence();          
    switch(startupMode) {
        case 0:
            deviceSettings();
        break;

        case 1:
            deviceRun();
        break;

        case 2:
            devicePowerDown();
        break;

        case 3:
            devicePowerUp();
        break;
    }
}
