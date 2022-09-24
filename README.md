# Flux Capacitor Micro

### WHAT IS IT?

A tiny (36mm x 29mm) pin badge and keychain PCB version of Flux Capacitor featuring 25 animated LEDs that animate to create the “fluxxing” effect. It’s 100% decorative, it doesn’t actually let you travel through time when worn around the neck.

![FLUXXXXING](https://github.com/hojadurdy/Flux_Capacitor_Micro/blob/main/Video/FC_Micro_Flash.GIF?raw=true "FLUXXXXING")

This tiny Flux Capacitor is controlled by a Microchip ATtiny1616 microcontroller. Thankfully this board has a much lower power requirement than the silkscreen indicates on the back, and skips along, sipping power from the single CR2016/LIR2016 coin cell battery (instead of plutonium or a lightning strike), slipped into the rear mounted coin cell holder. By using PWM (Pulse Width Modulation) pins for 8 channels of 3 paralleled LEDs, different animation patterns are generated for the fluxxxing effect. In settings mode, users are able change between 8 different animation, speed and LED brightness.

### WHAT IS NEW WITH THIS DESIGN?

- Main difference is the new design significantly slimmer due to slim battery holder and changing PCB thickness from 1.6mm to 0.8mm. Older design (V3) had a thickness of 6.15mm, the new design is only 3.4mm thick. 
- Front design has been updated to look like similar to Flux Capacitor Mini design. 
- A much brighter center LED has been added to get a brighter center beam flash, similar to the original Flux Capacitor.
- Instead of just 2 animations, now there are 8 different animations that can be selected in settings.
- Power toggle switch has been replaced with a push button. When pressed device goes in do "Power Down" mode. during "Power Down" mode device only consumes 0.5 uA.

Below you can see the thickness comparison of V3 on the left and V4 on the right.

![ V3 vs V4](https://github.com/hojadurdy/Flux_Capacitor_Micro/blob/main/Photo/Transparent_Background/v3v4.png?raw=true " V3 vs V4")

### HOW LONG WILL THE BATTERY LAST?

CR2016 (Non-Rechargeable) with average of 90 mAh battery capacity.

- 100% LED Brightness :  80 Hours
- 25%  LED Brightness :  128 Hours

LIR2016 (Rechargeable) with average of 20 mAh battery capacity.

- 100% LED Brightness :  18 Hours
- 25%  LED Brightness :  28 Hours

### HOW TO SETUP AND OPERATE

To begin with, turn on the device by pressing power button. In order to enter settings mode just hold the set button for 1 second. If all of the LEDs flashes twice, you are successfully entered settings mode. 

![BUTTONS](https://github.com/hojadurdy/Flux_Capacitor_Micro/blob/main/Photo/Transparent_Background/back3.png?raw=true " BUTTONS")

After the LEDs flash you will see that only single LED remains on. That single LED shows which animation is selected. To change that, just short press the set button and the LED should start shifting from inner to outer LED with each press. After selecting the preferred animation, hold the set button for 1 second to save. LEDs should flash twice to confirm.

Next setting is animation speed. To change the animation speed, just short press the set button to increase the speed. LEDs will turn on from inner to outer to indicate animation speed. At maximum speed all LEDs should be on. Hold the set button for 1 second to save animation speed. LEDs should flash twice to confirm.

Last setting is LED brightness. Same as before to change the brightness just short press the set buttonto increase the brightness. LEDs will turn on from inner to outer to indicate brightness level. At maximum brightness all LEDs should be on. Hold the set button for 1 second to save brightness setting. LEDs should flash twice to confirm and device should exit the setting mode. LEDs should start animating.

**If you short press the button with gear icon during normal operation, device initiates engage mode.
LEDs start to animate faster with much brighter center beam as shown in the video below.**

### P.S.
**Only CR2016 or LIR2016 batteries are compatible. If you prefer to use larger CR2032 or LIR2032 batteries, message me from store page. I will change the battery holder to a larger one. Also batteries are not included due to shipping restrictions.**

<a href="https://www.tindie.com/stores/curiousdesignlabs/?ref=offsite_badges&utm_source=sellers_Hojadurdy&utm_medium=badges&utm_campaign=badge_large"><img src="https://d2ss6ovg47m0r5.cloudfront.net/badges/tindie-larges.png" alt="I sell on Tindie" width="200" height="104"></a>
