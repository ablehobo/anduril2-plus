# ⚡ Enhanced Anduril Firmware Fork: Lighting Up New Possibilities! ⚡

Welcome to my customized fork of the Anduril firmware by ToyKeeper. I’ve added some brilliant new features to make your flashlight even more capable—because who doesn’t want a flashlight that can send secret messages in Morse code? 🌟

The journey began with this [starry repo](https://github.com/starryalley/Anduril2) that adds many enhancemnts like an improved candle mode, so be sure to check out the project's page for a full list of features that are included in this fork.

**Disclaimer:** I’m not a professional programmer—just a flashlight enthusiast using Anduril as an excuse to learn C. This project is a hands-on way for me to explore coding, so while I’m having fun, some features might be a bit experimental. Thanks for understanding!
## 🌟 New Features & Enhancements
### 🔠 Morse Code Mode

  * Morse Code Messaging: Flashlight communication just got old-school cool! Enter Morse code mode via cycling through the blinkie modes. You can input custom messages by entering the 7H menu and pressing the button a specific number of times for each letter (e.g., 1 press for A, 2 presses for B, etc.). The flashlight will then playback your message, using light to represent dots and dashes.
    
  * Custom Files:
      * morse_code.c and morse-code.h: These files handle the core logic for mapping button presses to Morse code, storing the messages, and playing them back at user-defined speeds.
      * morse_mode.c and morse-mode.h: These manage the state transitions and configurations within the Morse code mode, ensuring smooth user interaction.

### 🎛️ Menu Enhancements
    
  * Morse Code Speed Configuration: Adjust the playback speed of your Morse code messages to match your preferred signaling tempo. (3rd option in 7H menu)
    
  * Message Entry: Easily add characters to your message or start fresh with the "create new message" option in the menu. (1st and 2nd option in 7H menu respectively.

  * Misc. Config Menu: New entry to toggle between Morse Code number output or normal

  * Thermal Config Menu: New option to choose Celsius or Fahrenheight readouts

### 🔄 State Management

  * Seamless Integration: The new Morse code mode is fully integrated into the Anduril state machine, with transitions modeled after the thermal configuration to maintain a consistent user experience.
    
  * Error Handling: Proper handling of invalid Morse code inputs ensures that only valid characters (A-Z) are processed, with graceful recovery from out-of-range inputs.

### 🎨 Special Effects for Hank Lights

  * Spin RGB Animation: Hank lights like the D4K now have a unique spin RGB animation. This effect cycles through red, green, and blue, creating the illusion that the button is spinning—a visual treat that adds flair to your flashlight!

### 🔧 Other Modifications

  * Blink Pattern Enhancements:
      * 'Splat' Pattern: A cross between disco and rainbow, this pattern brings a lively burst of color to your flashlight’s repertoire.
      * 'Pulse' Blink Pattern: A new blink pattern that alternates between off, high, and low brightness—perfect for those who want to create a rhythm with their light.

  * Moonlight Mode Adjustment:
      *Lowered Moonlight Floor: Achieved a dimmer moonlight mode, giving you a subtle and softer light in low-light situations.

  * Dual Channel Hank Lights Channel Swap:
      * Swapped CH1 and CH2 on dual channel Hank lights because atleast the two I have are opposite from how I configured them on the website

  * Lockout Mode Enhancements:
      * Mid and Turbo Activation: In lockout mode, a 5H activates momentary mid-level, and a 6H activates momentary turbo, providing quick access to higher brightness without unlocking.

  * RGB Cycle Adjustment:
      * White Color Addition: Expanded the RGB cycle to include white, giving you more color options in disco, rainbow, and other color patterns.

  * Temperature Output Modification:
        * Fahrenheit Option: Toggle between Celsius and Fahrenheit in temperature readouts with a simple configuration option placed after thermal calibration.
        
  * Tempcheck Mode for Non-Regulated Devices: Enabled tempcheck mode on devices without thermal regulation, such as the BLF LT1 with an attiny1616. This feature is still a work in progress as I continue experimenting.

### 🛠️ What Is Anduril? And What's FSM?

Anduril is the ultimate flashlight UI, powered by FSM (Flashlight Spaghetti Monster), which makes controlling your flashlight as easy as untangling a well-organized flowchart.
🔧 Firmware Flashing: Stay Up to Date

Flashing your firmware has never been easier. Grab the latest .hex file here and follow the steps to update your light.
Required Tools:

  * Adapter: Depending on your light’s MCU, you might need a UPDI 3-pin adapter or an AVR ISP 6-pin adapter.
  * Software: avrdude, pymcuprog, or ZFlasher will get the job done.
  * Device: A modern computer or phone to run the flashing program.

For a detailed flashing guide, check out anduril.click.
### 🛠️ Compiling: DIY Firmware

For those who like to tinker, compiling your firmware is encouraged! Linux is the preferred environment, but virtual machines and Docker work just fine.
Build Requirements:

  * AVR Toolchain: sudo apt install gcc-avr avr-libc binutils-avr
  * Miscellaneous Tools: sudo apt install git wget unzip bash
  * Atmel DFPs: Use ./make dfp to download and install these.

Building:

Run the make script included in this repo. For a full build, simply run ./make. Your compiled firmware will be ready in the hex/ directory.
### 🎨 Customization

Place user-specific overrides in the users/myname/ directory, and the build script will handle the rest. Your personal settings will be applied automatically.
### 💻 Flashing Programs
#### AVRdude

   ##### bash

    sudo apt install avrdude

#### PyMCUprog

   ##### bash

    sudo apt install python3 python3-pip python3-venv
    python3 -m venv .venv
    source .venv/bin/activate
    pip install pymcuprog

Activate the virtual environment with source .venv/bin/activate when using pymcuprog, and deactivate with deactivate when done.
### 🤝 Contributing

Want to help this project shine even brighter? Here’s how you can contribute:

  * Support ToyKeeper on Patreon.
  * Submit pull requests or patches to improve the code, docs, or tools.
  * Report bugs or suggest new features.
  * Share your knowledge on forums and contribute to the documentation.
  * Encourage manufacturers to adopt and support this firmware.
