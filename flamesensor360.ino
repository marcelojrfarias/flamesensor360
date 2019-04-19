// Config file
#include "config.h"
#include "Thread.h"
#include "ThreadController.h"

// Thread Controllers 
ThreadController System; // to manage all system Threads

// System Functions
void initSensors();
void readSensors();
void printSensors();
void searchForFlames();

// System Threads
Thread ThreadSerachForFlames(searchForFlames, 250);

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

    // Add System Threads to the System Trhead Controller
    System.add(&ThreadSerachForFlames);

    // Setup sensors
    initSensors();
}

void loop() {
    System.run();
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

void printSensors() {
    for (int fs = 0; fs < FS_COUNT; fs++) {
        LOG.print(fsValues[fs]);
        LOG.print("V\t");
    }
    LOG.print("\n");
}


void searchForFlames() {
    readSensors();
    printSensors();
}