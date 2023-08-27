#ifndef BITWISE_H_
#define BITWISE_H_

#define SET_BIT(REG,BIT)        (REG |= (1<<BIT))
#define CLR_BIT(REG,BIT)        (REG &= (~(1<<BIT)))
#define GET_BIT(REG,BIT)        ((REG >> BIT) & 0X01)
#define TGL_BIT(REG,BIT)        (REG ^= (1<<BIT))
#define BIT_IS_SET(REG,BIT)     (REG & (1<<BIT))
#define BIT_IS_CLEAR(REG,BIT)   (!(REG & (1<<BIT)))




#endif /* BITWISE_H_ */
