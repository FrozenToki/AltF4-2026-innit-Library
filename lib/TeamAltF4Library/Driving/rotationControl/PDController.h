#pragma once

class PDController {
public:
    float Kp;
    float Kd;

    float lastMeasurement = 0;
    float output = 0;

    PDController(float p, float d) : Kp(p), Kd(d) {}

    float update(float error, float measurement) {
        float derivative = -(measurement - lastMeasurement);
        lastMeasurement = measurement;

        output = Kp * error + Kd * derivative;
        return output;
    }
};