# Onstep-calibration-stepper
OnStep is a computer controlled stepper motor goto system for Equatorial and Alt/Az mounts. The easy to work with Arduino based code runs on several popular microcontrollers enabling telescope control from a wide range of popular astronomy software. More information on Onstep is available on https://onstep.groups.io/g/main/wiki.

This is a simple Arduino sketch that can be used to perform exact number of microsteps on an Onstep hardware. This tool is completely independent from Onstep code.
It is intended to be programmed on your Arduino-based telescope control hardware to measure key parameters on the mechanics of your telescope.

Instructions:
  1. Create a folder named Stepper and put the source file stepper.ino inside
  2. Modify the pin assignments in the #define statements according to your hardware. 
  3. Prior to compiling in Arduino, select your associated board. This sketch was written for our BluePill-based hardware, but should work for other flavors as well
  4. Compile in Arduino and program into your Onstep board. Note that this sketch will overwrite the existing Onstep code on your board, and you will need to re-program Onstep.
  5. Once the board is in run mode, start a serial terminal connection to your board (115200 baud 8N1)
  6. Use the following commands in the serial interface to take any specified number of microsteps to your motors
      * ">> A+nnnn" (followed by ENTER): advance ALTITUDE motor by nnnn microsteps in the positive direction
      * ">> A-nnnn" (followed by ENTER): advance ALTITUDE motor by nnnn microsteps in the negative direction
      * ">> Z+nnnn" (followed by ENTER): advance AZIMUTH motor by nnnn microsteps in the positive direction
      * ">> Z-nnnn" (followed by ENTER): advance AZIMUTH motor by nnnn microsteps in the negative direction
        maximum value of nnnn is currently limited to 9999 microsteps, you can enter consecutive commands to achieve larger number of microsteps
      
The method to measure backlash in any axis is as follows:
  1. Precisely mark the starting position (we used an attached laser pointer in a closed room)
  2. Take a relatively large number of steps in one direction:
        ">> Z+9999"
  3. Return to the exact inital position (marked by laser pointer) by issuing microsteps in the opposite direction.
     If there is any backlash in your system you will notice that taking the same number of microsteps, you will be short of your target point.
     So issue additional commands in small increments (always in the negative direction)
        * ">> Z-9999"
        * ">> Z-50"
        * ">> Z-50"       
        * ">> Z-30"
     In the example above, if the pointer ends up in alignment to the starting point, this means your Azimuth backlash is 50+50+30 = 130 microsteps

By the same token, this tool can also be used to calculate your telescope's precise reduction ratio in both axes.
Count the number of microsteps that it takes for the axis to make a 360-degree turn (or 90-degree turn if more convenient) and figure out how many
microsteps you need per 1-degree move.

Please share your feedback.

Murat Isik
murat . isik . istanbul @ gmail . com        
