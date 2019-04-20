// Libraries included
#include "config.h"
#include "led.h"
#include "FlameSensor.h"
#include "Buzzer.h"
#include "Thread.h"
#include "ThreadController.h"

// Thread Controllers 
ThreadController System; // to manage all system Threads
ThreadController Leds;
ThreadController Sensors;

// System Functions
void initSensors();
void calibrateSensors(int samples);
void printSensors();
void searchForFlames();

// System Threads
Thread ThreadSearchForFlames(searchForFlames, 200);

FlameSensor flameSensors[FS_COUNT] = {
    FlameSensor (FS0_PIN, 2),
    FlameSensor (FS1_PIN, 2),
    FlameSensor (FS2_PIN, 2),
    FlameSensor (FS3_PIN, 2),
    FlameSensor (FS4_PIN, 2),
    FlameSensor (FS5_PIN, 2),
    FlameSensor (FS6_PIN, 2),
    FlameSensor (FS7_PIN, 2)
};

LED leds[LED_COUNT] = {
    LED(LED0_PIN, LOW),
    LED(LED1_PIN, LOW),
    LED(LED2_PIN, LOW),
    LED(LED3_PIN, LOW),
    LED(LED4_PIN, LOW),
    LED(LED5_PIN, LOW),
    LED(LED6_PIN, LOW),
    LED(LED7_PIN, LOW)
};

Buzzer buzzer(BZZ_PIN, LOW);

void setup() {
    // Start the logging serial port
    LOG.begin(LOG_SPEED);

    // Print the project name and version  
    LOG.print(PROJECT_NAME); LOG.print(" "); LOG.println(PROJECT_VERSION);

    // Add System Threads to the System Trhead Controller
    System.add(&ThreadSearchForFlames);
    System.add(&Sensors);
    System.add(&Leds);
    System.add(&buzzer);
    
    // Setup the interface
    initLeds();

    // Setup the sensors
    initSensors();

    // Setup the buzzer
    initBuzzer();

    // Calibrate the sensors
    LOG.println("Calibrating the sensors...");
    calibrateSensors(20);
    LOG.println("Sensors calibrated!");
}

// The main function
void loop() {
    System.run();
    Sensors.run();
    Leds.run();
}

// Init LEDs
void initLeds() {
    for (int led = 0; led < LED_COUNT; led++) {
        leds[led].setInterval(1000);
        Leds.add(&leds[led]);
    }
}

// Init sensors
void initSensors() {
    for (int fs = 0; fs < FS_COUNT; fs++) {
        flameSensors[fs].setInterval(100);
        Sensors.add(&flameSensors[fs]);
    }
}

// Init buzzer
void initBuzzer() {
    buzzer.setInterval(BZZ_MAX_INTERVAL);
}

// Print sensors voltage reading
void printSensors() {
    for (int fs = 0; fs < FS_COUNT; fs++) {
        LOG.print(flameSensors[fs].voltage);
        LOG.print("V\t");
    }
    LOG.print("\n");
}

// Calibrate the sensors and print offsets calibrated
void calibrateSensors(int samples) {
    for (int fs = 0; fs < FS_COUNT; fs++) {
        flameSensors[fs].calibrate();
    }
    for (int fs = 0; fs < FS_COUNT; fs++) {
        LOG.print(flameSensors[fs].offset);
        LOG.print("\t");
    }
    LOG.print("\n");
}

// Search for flames and blink the respective leds
void searchForFlames() {
    bool flameFound = false;
    for (int fs = 0; fs < FS_COUNT; fs++) {
        if (flameSensors[fs].voltage < FS_MIN_VOLTAGE) {
            leds[fs].enabled = false;
            leds[fs].off();
        } else {
            unsigned int interval = voltageToInterval(flameSensors[fs].voltage);
            leds[fs].enabled = true;
            leds[fs].setInterval(interval);

            flameFound = true;
        }

        if (flameFound) {
            buzzer.enabled = true;
        } else {
            buzzer.enabled = false;
            buzzer.off();
        }
    }
}

// Convert voltage to time interval 
float voltageToInterval (float voltage) {
    return (LED_MIN_INTERVAL + (1.0 - voltage / FS_MAX_VOLTAGE)  * (LED_MAX_INTERVAL - LED_MIN_INTERVAL));
}
