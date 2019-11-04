# Guitar Effect Box
The purpose of this project was to make a user-friendly audio system that can apply effects to a electric guitar signal.
The user interfaces with the system through a 5" touch screen and a rotary encoder.

Since I have no interest in making my own graphics I decided to use 5" touchscreen from 4D-systems since it comes with a user-friendly IDE with a lot of premade grapics and functionalities. I might switch to the LittlevGL open-source GUI library in the future (https://littlevgl.com/)

The project started out on a TI TMS320C5535, but I thoroughly disliked the TI CodeComposer environment, so I decided to change to a STM32H743 since it is reasonably fast (480 MHz), has a floating-point unit, higher quality IDE, but most importantly it's cheap! (20 USD for a devo-board).

A WM8731 audio codec is used as ADC/DAC and runs @ 48kHz.

So far 4 effects are implemented:
  - Wah Wah
  - Flanger
  - Overdrive
  - 3 band equalizer (bas, mid, treble)
  
Next effect to be implemented is reverb.
I'm not completely satisfied with the sound of the'standard' Schroeder reverberator (http://www.aes.org/e-lib/browse.cfm?elib=849) so I'm experimenting with alternative solutions.

The repository is divided into 3 parts:
  - stm (source code for STM32H7)
  - dsp_modules (a small framework that can build the binaries for algorithms used in the project, and compare the output with a reference MATLAB implementation to maintain a decent bit-accuracy)
  - display (project files for the 4D-systems display)
  
  ![alt text](https://drive.google.com/open?id=0B0oJ6huzHqSfMkNFR0N1M1hERGJnaHkzVUEzeUNSTWotQkdr)
  
TO DO:
- Implement reverb.
- Utilize TCM (tighly coupled memory) for both data and instruction.
- Implement USB recording/playback support.
- Add pictures of the box and screendump of the display
- Add block-diagram of hardware configuration
