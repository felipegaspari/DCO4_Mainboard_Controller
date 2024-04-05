#ifndef __AUX_H__
#define __AUX_H__

float counter;
float counter2;

float mapFloat(float x, float in_min, float in_max, float out_min,
               float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
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
