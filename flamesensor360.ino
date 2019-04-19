// Config file
#include "config.h"

int fsPins[FS_COUNT] = {
    FS0_PIN,
    FS1_PIN,
    FS2_PIN,
    FS3_PIN,
    FS4_PIN,
    FS5_PIN,
    FS6_PIN,
    FS7_PIN,
};

float fsValues[FS_COUNT];

void setup() {
    // Start the logging serial port
    LOG.begin(LOG_SPEED);

    // Print the project name and version  
    LOG.print(PROJECT_NAME); LOG.print(" "); LOG.println(PROJECT_VERSION);

    // Setup sensors
    initSensors();
}

void loop() {
    readSensors();

    printSensorsValues();

    delay(250);
}

// Init sensors
void initSensors() {
    for (int fs = 0; fs < FS_COUNT; fs++) {
        pinMode(fsPins[fs], INPUT);
    }
}

void readSensors() {
    for (int fs = 0; fs < FS_COUNT; fs++) {
        fsValues[fs] = analogRead(fsPins[fs]);
        fsValues[fs] = (fsValues[fs] / 1024.0) * 5.0;
    }
}

void printSensorsValues() {
    for (int fs = 0; fs < FS_COUNT; fs++) {
        LOG.print(fsValues[fs]);
        LOG.print("V\t");
    }
    LOG.print("\n");
}