
#ifndef BIT_MATH_H_
#define BIT_MATH_H_


#define SET_BIT(var, bitNum)       (var |=  (1<<bitNum))
#define CLR_BIT(var, bitNum)       (var &= ~(1<<bitNum))
#define GET_BIT(var, bitNum)       ((var >> (bitNum)) & (0x01))


#endif 

