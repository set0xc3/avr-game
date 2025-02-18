#ifndef PLATFORM_H
#define PLATFORM_H

#include "builtin.h"

void platform_init();
void platform_deinit();

inline void enable_external_interrupts(void);
inline void disable_external_interrupts(void);

// Прерывание
// Пины: INT0, INT1
inline void enable_external_interrupt(u8 interrupt_num);
inline void disable_external_interrupt(u8 interrupt_num);

inline void delay_us(f64 us);
inline void delay_ms(f64 ms);

#endif
