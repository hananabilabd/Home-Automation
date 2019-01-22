
#ifndef MACROS_H_
#define MACROS_H_

#define set_bit(reg,bit) (reg=reg |(1<<bit))
#define clr_bit(reg,bit) (reg=reg &(~(1<<bit)))
#define get_bit(reg,bit) ((reg >> bit) & 1)
#define toggle_bit(reg,bit) (reg=(reg ^ (1<<bit)))
// #define toggle_bit(reg,bit) reg ^= (1<<bit)

#define sethigh_bit(reg) (reg=reg | 0xF0)
#define setlow_bit(reg) (reg=reg | 0x0F)
#define clrhigh_bit(reg) (reg=reg & 0x0F)
#define clrlow_bit(reg) (reg=reg & 0xF0)

#endif /* MACROS_H_ */
