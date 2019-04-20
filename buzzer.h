
#ifndef Buzzer_h
#define Buzzer_h

#include "Thread.h"

class Buzzer: public Thread {
public:
    boolean state;
	int pin;

    Buzzer (int pin, bool state) {
        this->pin = pin;
        this->state = state;
        
        pinMode(pin, OUTPUT);
        digitalWrite(pin, state);
    }

    void off() {
        state = false;
        digitalWrite(pin, state);
    }

    void on(){
        state = true;
        digitalWrite(pin, state);
    }

	void run(){
        state = !state;
        digitalWrite(pin, state);
		runned();
	}
};

#endif