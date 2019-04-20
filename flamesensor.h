
#ifndef FLAME_SENSOR_h
#define FLAME_SENSOR_h

class FlameSensor : public Thread {
public:
	int pin;
    int samples;
    int adc;
    int offset = -1;
    float voltage;
    float distance;

    FlameSensor (int pin, int samples) {
        this->pin = pin;
        this->samples = samples;
        pinMode(pin, INPUT);
    }

    void calibrate() {
        int reading = analogRead(pin);
        if (reading > offset)
            offset = reading;
    }

	void run() {
        adc = 0;
        for (int s = 0; s < samples; s++) {
            if (offset > 0)
                adc += analogRead(pin) - offset;
            else
                adc += analogRead(pin);
        }
        adc /= samples;
        voltage =  (float) adc / 1024.0 * 5.0;
        distance = voltage;
		runned();
	}
};

#endif