#ifndef BLINKER_H
#define BLINKER_H

#include <Arduino.h>

/// @brief Initializes the built-in led
void initBlinker();

/// @brief Turns on the built-in led for `duration` milliseconds, then turns it
/// off and waits `delay` milliseconds
/// @param duration
/// @param delay
void blink(unsigned long duration, unsigned long delay);


/// @brief Turns on the built-in led for 1 second, then turns it off and waits another second
void blinkIdle();

#endif