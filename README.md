# ⚡ Enhanced Anduril Firmware Fork: Expanding Flashlight Capabilities ⚡

Welcome to my customized fork of the Anduril firmware, originally created by ToyKeeper. This version includes several enhancements designed to push the limits of your flashlight—whether it's communicating in Morse code or refining special effects.

This project builds upon the features from [starryalley’s Anduril2 repo](https://github.com/starryalley/Anduril2). Be sure to explore the original project for more detailed insights into its wide array of capabilities.

**Disclaimer:** I’m an enthusiastic hobbyist exploring C programming through this project. While I aim to maintain high functionality, some features may still be in development or experimental. Thanks for your understanding!

## 🌟 New Features & Enhancements

### 🔠 Morse Code Mode

  * **Morse Code Messaging:** You can now use your flashlight to communicate in Morse code. To access Morse code mode, cycle through the blinkie modes until you reach the mode. It will be in rotation before cycling back to battery check. Here, you can enter custom messages via the 4H menu:
    - 1-Letter Entry
    - 2-Backspace
    - 3-Message Clear
    - 4-Speed Control
    - Letters are entered using the number of clicks for each letter (e.g., 1 click for A, 2 clicks for B, 10 clicks or 1H for J, etc.). 30 clicks (3x1H) adds a space.
    - The flashlight will play back your message, using flashes for dots and dashes.
    
  * **Core Logic Files:**
    - `morse_code.c` and `morse-code.h`: Handle mapping button presses to Morse code, storing the message, and managing playback.
    - `morse_mode.c` and `morse-mode.h`: Oversee state transitions and ensure smooth user interaction.

  * **Morse Code Speed Configuration:** Adjust the speed of Morse code playback via the 4H menu for precise control.
    - Can be adjusted during message playback using 1H and 2H like smooth ramping.

  * **Message Entry:** Easily add characters or clear the message entirely through intuitive options within the menu.

  * **Miscellaneous Config Menu:** Added an option to toggle between Morse code number output and standard readouts for battery voltage and temperature.

### 🎨 Special Effects & RGB Modes

  * **Spin RGB Animation:** Adds a dynamic RGB effect on Hank lights (e.g., D4K), cycling through colors to simulate spinning—perfect for a visual touch of flair.

  * **RGB Cycle Adjustments:** Expanded the RGB cycle to include white, offering more variety in color patterns like disco and rainbow.

### 🌡️ Temperature Output Toggle

  * **Celsius/Fahrenheit Toggle:** Added a configuration option to toggle between Celsius and Fahrenheit for temperature readouts. The option is placed after the thermal calibration setting (note: calibration is still in Celsius).

### 🔄 State Management

  * **Morse Code Mode Integration:** Fully incorporated into Anduril’s state machine, ensuring a seamless user experience.
    
  * **Error Handling:** Only valid characters (A-Z) are processed, and invalid inputs are gracefully handled.

### 🔧 Additional Modifications

  * **Blink Pattern Enhancements:**
      - **'Splat' Pattern:** A mix of disco and rainbow effects, offering vibrant color transitions.
      - **'Pulse' Pattern:** Alternates between off, high, and low brightness to create a rhythmic light pattern.

  * **Moonlight Mode Adjustment:** The floor has been lowered to achieve a dimmer moonlight mode, offering a softer, more subtle light.

  * **Dual Channel Swap:** For dual-channel Hank lights, CH1 and CH2 have been swapped to align with user preferences from the website configuration.

  * **Lockout Mode Enhancements:**
      - In lockout mode, 5H activates momentary mid-level brightness, and 6H activates momentary turbo for quick access without unlocking the flashlight.

  * **Mid-ramp Blink:** Enabled mid-ramp blinking functionality for a more interactive ramping experience.

  * **Tempcheck for Non-Regulated Devices:** Added experimental support for temperature checks on devices without thermal regulation (e.g., BLF LT1 with attiny1616). This feature is a work in progress.

## 🛠️ What Is Anduril? And What's FSM?

Anduril is a comprehensive user interface for flashlights, powered by FSM (Finite State Machine), which provides a structured, intuitive control system for complex flashlight behavior.

## 🔧 Firmware Flashing: Stay Updated

To update your flashlight with the latest firmware, download the latest `.hex` file from this repository and follow these steps:

**Required Tools:**
  - Adapter: You may need a UPDI 3-pin adapter or AVR ISP 6-pin adapter depending on your flashlight’s MCU.
  - Software: `avrdude`, `pymcuprog`, or `ZFlasher` will work for flashing the firmware.
  - Device: Use a modern computer or phone to run the flashing program.

For detailed instructions, visit [anduril.click](https://anduril.click).

## 🛠️ Compiling: DIY Firmware

If you prefer to build your firmware from source, here’s what you’ll need:

**Build Requirements:**
  - AVR Toolchain: Install via `sudo apt install gcc-avr avr-libc binutils-avr`
  - Miscellaneous Tools: `sudo apt install git wget unzip bash`
  - Atmel DFPs: Download and install with `./make dfp`.

**Building:**
Run the provided `make` script:
```bash
./make
````
The compiled firmware will be available in the `hex/` directory.

## 🎨 Customization

To personalize your firmware, place custom overrides in the `users/myname/` directory. The build script will automatically apply your changes.

## 💻 Flashing Programs

### AVRdude

```bash
sudo apt install avrdude
````
### PyMCUprog

\`\`\`bash
sudo apt install python3 python3-pip python3-venv
python3 -m venv .venv
source .venv/bin/activate
pip install pymcuprog
\`\`\`

Activate the virtual environment with `source .venv/bin/activate` when using pymcuprog, and deactivate with `deactivate` when done.

## 🤝 Contributing

Want to contribute to the project? Here’s how you can help:

  - Support ToyKeeper on Patreon.
  - Submit pull requests or patches to improve code, documentation, or tools.
  - Report bugs or suggest new features.
  - Share your experiences on forums and contribute to the community.
  - Encourage flashlight manufacturers to adopt and support this firmware.



