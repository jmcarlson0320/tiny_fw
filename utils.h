#ifndef UTILS_H
#define UTILS_H

float lerp(float norm, float min, float max);
float norm(float value, float min, float max);
float map(float value, float srcMin, float srcMax, float destMin, float destMax);
int point_in_rect(int x, int y, int x0, int y0, int w, int h);

#endif
