#pragma once
#include <Arduino.h>

class PDController {
public:
    float Kp;
    float Kd;

    float lastMeasurement = 0.0f;
    float output = 0.0f;

    PDController(float p, float d) : Kp(p), Kd(d) {}

    float update(float error, float measurement) {
        float derivative = -(measurement - lastMeasurement);
        lastMeasurement = measurement;


        output = Kp * error + Kd * derivative;
        return output;
    }
};