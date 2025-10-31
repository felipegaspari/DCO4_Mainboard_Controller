#ifndef __AUX_H__
#define __AUX_H__

float counter;
float counter2;

//#define RUNNING_AVERAGE

#ifdef RUNNING_AVERAGE
#include "RunningAverage.h"

RunningAverage myRA(2000);
/* USAGE:
unsigned long a;
unsigned long b;
a = micros();
b = micros();
myRA.addValue(b - a);
Serial.println(myRA.getAverage());
*/
#endif


float mapFloat(float x, float in_min, float in_max, float out_min,
               float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

struct Point {
  float x, y;
};

// Función que calcula un punto en la curva de Bézier cúbica para un valor dado de t
Point bezierCubic(const Point& A, const Point& P1, const Point& P2, const Point& B, float t) {
  float one_minus_t = 1.0f - t;
  float one_minus_t_squared = one_minus_t * one_minus_t;
  float t_squared = t * t;
  float x = one_minus_t_squared * one_minus_t * A.x + 3 * one_minus_t_squared * t * P1.x + 3 * one_minus_t * t_squared * P2.x + t_squared * t * B.x;
  float y = one_minus_t_squared * one_minus_t * A.y + 3 * one_minus_t_squared * t * P1.y + 3 * one_minus_t * t_squared * P2.y + t_squared * t * B.y;
  return { x, y };
}

// Función para encontrar el valor de y dado un valor de x en la curva de Bézier
float findYForX(const Point& A, const Point& P1, const Point& P2, const Point& B, float xTarget, float tol = 1e-5) {
  float tLow = 0.0f;
  float tHigh = 1.0f;
  float tMid;

  while ((tHigh - tLow) > tol) {
    tMid = (tLow + tHigh) / 2.0f;
    Point midPoint = bezierCubic(A, P1, P2, B, tMid);
    if (midPoint.x < xTarget) {
      tLow = tMid;
    } else {
      tHigh = tMid;
    }
  }

  Point resultPoint = bezierCubic(A, P1, P2, B, tMid);
  return resultPoint.y;
}

void generateBezierArray(Point A, Point B, Point P1, Point P2, uint16_t arraySize, uint16_t (&array)[4096]) {

  for (int x = 0; x < arraySize; ++x) {
    float yResult = findYForX(A, P1, P2, B, static_cast<float>(x));

    array[x] = yResult;
  }
}

uint16_t linearToExponential(uint16_t linearValue, float base, uint16_t maxValue) {

  if (linearValue < 0) linearValue = 0;
  if (linearValue > 4095) linearValue = 4095;

  float normalizedValue = (float)linearValue / 4095.0;
  float expValue = pow(base, normalizedValue) - 1;
  float maxExpValue = pow(base, 1.0) - 1;
  uint16_t scaledExpValue = (uint16_t)(expValue * (maxValue / maxExpValue));

  return scaledExpValue;
}

// unsigned int isintable16[] = {
//   0, 1144, 2287, 3430, 4571, 5712, 6850, 7987, 9121, 10252, 11380,
//   12505, 13625, 14742, 15854, 16962, 18064, 19161, 20251, 21336, 22414,
//   23486, 24550, 25607, 26655, 27696, 28729, 29752, 30767, 31772, 32768,

//   33753, 34728, 35693, 36647, 37589, 38521, 39440, 40347, 41243, 42125,
//   42995, 43851, 44695, 45524, 46340, 47142, 47929, 48702, 49460, 50203,
//   50930, 51642, 52339, 53019, 53683, 54331, 54962, 55577, 56174, 56755,

//   57318, 57864, 58392, 58902, 59395, 59869, 60325, 60763, 61182, 61583,
//   61965, 62327, 62671, 62996, 63302, 63588, 63855, 64103, 64331, 64539,
//   64728, 64897, 65047, 65176, 65286, 65375, 65445, 65495, 65525, 65535,
// };

// float isin(float f)
// {
//   boolean pos = true;  // positive
//   if (f < 0)
//   {
//     f = -f;
//     pos = !pos;
//   }

//   long x = f;
//   unsigned int r = (f - x) * 256;

//   if (x >= 360) x %= 360;
//   if (x >= 180)
//   {
//     x -= 180;
//     pos = !pos;
//   }
//   if (x >= 90)
//   {
//     x = 180 - x;
//     if (r != 0)
//     {
//       r = 256 - r;
//       x--;
//     }
//   }


//   unsigned int v = isintable16[x];
//   // uint16_terpolate if needed
//   if (r > 0) v = v + ((isintable16[x + 1] - v) / 8 * r) / 32;

//   if (pos) return v * 0.0000152590219; // = /65535.0
//   return v * -0.0000152590219 ;
// }

//void delayCycles(uint16_t cycles) {
//for (uint16_t i = 0; i < cycles;i++)
//__asm( "nop" );
//}

#endif
