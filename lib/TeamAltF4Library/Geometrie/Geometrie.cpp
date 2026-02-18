#include "Geometrie.h"

Geometrie::Geometrie(Application *a) : app(a) {}

float Geometrie::normalizeAngle(float angle) {
	while (angle < 0) angle += 360;
	while (angle >= 360) angle -= 360;


	if (angle > 180)
		angle -= 360;

	return angle;
}
