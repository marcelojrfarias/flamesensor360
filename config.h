
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
#define FS0_PIN A6
#define FS1_PIN A5
#define FS2_PIN A4
#define FS3_PIN A3
#define FS4_PIN A2
#define FS5_PIN A1
#define FS6_PIN A0
#define FS7_PIN A7
#define FS_MIN_VOLTAGE 0.20
#define FS_MAX_VOLTAGE 5.0

// LEDs Pinout
#define LED_COUNT 8
#define LED0_PIN 3
#define LED1_PIN 4
#define LED2_PIN 5
#define LED3_PIN 6
#define LED4_PIN 7
#define LED5_PIN 8
#define LED6_PIN 9
#define LED7_PIN 2
#define LED_MIN_INTERVAL 50
#define LED_MAX_INTERVAL 500

// LEDs Pinout
#define BZZ_PIN 10
#define BZZ_MIN_INTERVAL 50
#define BZZ_MAX_INTERVAL 500

#endif