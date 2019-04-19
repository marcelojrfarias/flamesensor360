
#ifndef CONFIG_h
#define CONFIG_h

// Project info
#define PROJECT_NAME "Flame Sensor 360"
#define PROJECT_VERSION "v1.0"

// Logging settings
#define LOG_ENABLED true
#define LOG if(LOG_ENABLED) Serial
#define LOG_SPEED 115200

// Sensors Pinout
#define FS_COUNT 8
#define FS0_PIN A0
#define FS1_PIN A1
#define FS2_PIN A2
#define FS3_PIN A3
#define FS4_PIN A4
#define FS5_PIN A5
#define FS6_PIN A6
#define FS7_PIN A7

// LEDs Pinout
#define LED0_PIN 3
#define LED1_PIN 4
#define LED2_PIN 5
#define LED3_PIN 6
#define LED4_PIN 7
#define LED5_PIN 8
#define LED6_PIN 9
#define LED7_PIN 10

// LEDs Pinout
#define BZZ_PIN 3

#endif