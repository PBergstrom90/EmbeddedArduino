# AVR - Programming hardwareregisters for an Arduinoboard

This repository contains five different branches, each focusing on specific tasks related to programming AVR hardware registers for Arduinoboards.

## Branches and Tasks

### 1. Deluppgift01-Timer1 (Timer)

#### Instructions:

- Configure TIMER1 to blink an LED with 200 ms on/off cycles.
- Use GPIO code to control an LED connected to Arduino/Freenove pin 3.
- Utilize timer compare A interrupt to toggle the LED.
  
### 2. Deluppgift02-ADCread (ADC from Potentiometer)

#### Instructions:

- Connect a potentiometer as a voltage divider to pin A0.
- Set up ADC and read the value via hardware registers.
- Print the read value and calculated voltage on pin A0 every second via the serial port.

### 3. Deluppgift03-LEDcmd

#### Instructions:

- Connect an LED to pin 3 (PWM capable).
- Implement a configurable timer with Timer1.
- Create a command interpreter that handles the command `ledpowerfreq <power> <time>`.

### 4. Deluppgift04-ButtonCounter

#### Instructions:

- Write a counter for the number of button presses.
- Use Timer1 to measure the input from pin 5.
- Print the number of button presses every second.

### 5. Deluppgift05-RampLED

#### Instructions:

- Ramp an LED's power linearly from 0-255 and then down periodically.
- Control the ramp time via a command sent through the serial port, e.g., `ledramptime 500 ms`.

### Main 

- Mainbranch is currently synced with "Deluppgift03-LEDcmd" and does not represent the full scale of the project.
- Please select different branches for different parts of the project.

---

## How to Use Each Branch

1. **Clone the Repository**
    ```bash
    git clone <repository_url>
    ```
  
2. **Switch to Desired Branch**
    ```bash
    git checkout <branch_name>
    ```
  
3. **Upload Code to Arduino/Freenove Board**
    - Open the `.ino` file in the Arduino IDE.
    - Select the correct board and port.
    - Click "Upload" to upload the code to the board.

4. **View Serial Monitor Output**
    - Open the Serial Monitor in the Arduino IDE to view the program output.

---

