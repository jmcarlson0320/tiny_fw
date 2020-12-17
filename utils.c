#include "app.h"

float lerp(float norm, float min, float max)
{
    return (max - min) * norm + min;
}

float norm(float value, float min, float max)
{
    return (value - min) / (max - min);
}

float map(float value, float srcMin, float srcMax, float destMin, float destMax)
{
    float n = norm(value, srcMin, srcMax);
    return lerp(n, destMin, destMax);
}

int point_in_rect(int x, int y, int x0, int y0, int w, int h)
{
    return x0 <= x && x <= x0 + w && y0 <= y && y <= y0 + h;
}
