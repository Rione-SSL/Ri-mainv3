
#ifndef _SETUP_COM_H_
#define _SETUP_COM_H_

#define INLINE inline __attribute__((always_inline))

#define BALL_DETECT_VALUE 700
#define MODE_UNMATCH -1

#ifndef PI
#define PI 3.141592653589
#endif

#define STRAIGHT_KICKER 0
#define CHIP_KICKER 1

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue)                                         \
    (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

#endif