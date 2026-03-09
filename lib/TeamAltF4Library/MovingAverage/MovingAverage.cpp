#include "MovingAverage.h"

MovingAverage::MovingAverage(int averageValueCount, bool useAngleMode) : angleMode(useAngleMode) {
	values.resize(averageValueCount);
	values.reserve(averageValueCount);
	for (size_t i = 0; i < values.size(); i++) {
		values[i] = -1;
	}
	
}

void MovingAverage::newValue(float v) {
	if (values[0] == -1) {
		for (size_t i = 0; i < values.size(); i++) {
			values[i] = v;
		}
	} else {
		for (size_t i = values.size() - 1; i > 0; i--) {
			values[i] = values[i-1];
		}	
		values[0] = v;
	}
}

float MovingAverage::getAverage() {
	if (angleMode) {
		for (size_t i = 1; i < values.size(); i++) {
			if (values[0] - values[i] < -190.0f ) {
				values[i] -= 360.0f;
			} else if (values[0] - values[i] > 190.0f) {
				values[i] += 360.0f;
			}
		}
		float average = 0;
		for (size_t i = 0; i < values.size(); i++) {
			average += values[i];
		}
		average = average / values.size();
		if (average < 0.0f) {
			average += 360.0f;
		} else if (average > 360.0f) {
			average -=  360.0f;
		}
		return average;
	} else {
		float average = 0;
		for (size_t i = 0; i < values.size(); i++) {
			average += values[i];
		}
		average = average / values.size();
		return average;
	}
	
}
