# What's here

A bit of history here. I fell in love with Anduril with my first D4v2 (a brass D4v2 with E21A 2000/2700K) since Apr, 2021. I started [modding the Anduril firmware](https://github.com/starryalley/anduril2) right away and added features that I personally need. Gradually I've added many new things. See my [good old Anduril repo](https://github.com/starryalley/anduril2) for more information. 

Anduril has since changed a lot in year 2023. I then started from scratch in the end of 2023, based on the [latest Anduril codebase](https://github.com/ToyKeeper/anduril), and slowly moved some of my (personally) most used features here. 

Please note that I usually do not care or consider other Anduril2 lights that I don't own, since I won't be able to test them, and I don't plan to make this Anduril fork a general codebase for all Anduril2 lights. Please just kindly file a bug report whenever you like.


# Features

## Strobe modes

I've added 3 more strobe modes. The order is:
- lightning mode
- candle mode
- fireworks mode with configurable amplitude (new)
    - default wobble
    - fireplace slow wobble
    - fireplace fast wobble
- lighthouse beacon mode (new)
- broken fluorescent mode (new)
- bike flasher
- party strobe
- tatical strobe
- police color strobe


### More configurable candle mode

In candle mode, add the following options which are saved:
- `6C`: making candle amplitude smaller (candle in sort of a more stillness, calmer)
- `7C`: making candle amplitude bigger (candle in the wind)
- `8C`: reset to default (which is a bit calmer then the stock one)


### Fireplace mode (in Candle mode)

Two additional wobble styles: fireplace_slow and fireplace_fast. Use `4H` to cycle through all 3 wobble styles. This is a saved configuration.

- style 1: Anduril2 stock candle mode (default)
- style 2: fireplace slow wobble
- style 3: fireplace fast wobble


### More configurable lightning mode 

In lightning mode, add the following options which are saved:
- `6C`: turn down busy factor so the lightning is less busy (less frequent)
- `7C`: turn up busy factor so the lightning is busier (more frequent)
- `8C`: reset to default (which is max 16sec until the next lightning strike, originally it's about 8sec)


### Fireworks mode

An additional strobe mode called Fireworks. The main emitters will light up like fireworks. 

Adjust firework brightness (explosion brightness):
- `6C`: decrease brightness by 12
- `7C`: increase brightness by 12
- `8C`: reset brightness to default (max regulated level, which is `RAMP_SMOOTH_CEIL`)

For multi channel lights, the firmware will not make use of different channels now. However I plan to implement randomly choosing channels (main emitters only) so the firework strobe mode will alternate between channels and mix channels too.


### Lighthouse Beacon mode

An additional strobe mode called Lighthouse Beacon. The main emitters will light up periodically like a lighthouse where the intensity rapidly accelerates to turbo (level 150) and then ramps back down to 0 (when it rotates away from the viewer). It will wait for a few seconds (configurable) before doing it again.

Adjust the delay by:
- `6C`: decrease delay by 1 second (Min: 0 second)
- `7C`: increase delay by 1 second (Max: 30 seconds)
- `8C`: reset delay to default (5 seconds)


### Broken Fluorescent mode

An additional strobe mode called broken fluorescent. The main emitters will flicker continously that simulate a broken fluorescent light. Brightness of the flicker can be adjusted by the usual `1H` and `2H` and is remembered.


## In STANDBY/LOCKOUT modes or POWERED OFF

### AUX LED can show different colours based on ambient temperature in standby/lockout mode

Add an additional mode "temperature" in AUX LED mode (for standby/lockout) after "voltage". The AUX LED will change colour based on the on-chip temperature reading. 
  - `<=12C`: pink/purple (red+blue)
  - `12~16C`: blue
  - `16-20C`: cyan (green+blue)
  - `20-25C`: green
  - `25-30C`: yellow (red+green)
  - `>30C`: red

This setting is after "voltage" mode. Use `7H` from off or lockout to loop each mode.


### When it's time to change battery, blink AUX red in standby/lockout mode

When voltage is < 3.3V(`VOLTAGE_RED`) when light is off, the off/lockout AUX mode will not activate. Instead, the AUX red LED will blink. Original idea from reddit user [connorkmiec93](https://www.reddit.com/user/connorkmiec93/) at this [post](https://www.reddit.com/r/flashlight/comments/mpj36p/im_doing_a_d4v2_with_anduril_2_giveaway/).

The blinking is in a pattern called breathing (although it's only low/high mode in AUX LED) so it's less distracting to the original blinking and one can tell the difference to the normal blinking in RED mode.

For lights with the indicator LED, the indicator LED will be used. ([default behaviour](https://github.com/ToyKeeper/anduril/commit/b2f95757bde9f3e23105d7b433fc59ace0f2ae87))

## Child UI (a Simple UI with limitations)

Child UI (in addition to Simple and Advanced) is basically the same as Simple UI but with the following differences (limitations):
- ramping style is fixed to 2-step discrete ramping (only low and high)
- only ramp floor and ceil (low and high level) can be configured (by `12H` from off in advanced UI)
- default floor and ceiling level: `SIMPLE_UI_FLOOR` and 50

Enter by `12C` from off, exit by `12H` from off.

Switch to this mode before handling the light to the kids.
