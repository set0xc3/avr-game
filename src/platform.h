#ifndef PLATFORM_H
#define PLATFORM_H

#include <stdbool.h>
#include <stdint.h>

void platform_init(void);
void platform_deinit(void);

void enable_global_interrupts(void);
void disable_global_interrupts(void);

// Enable specific external interrupt (INT0 or INT1)
void enable_external_interrupt(uint8_t interrupt_num);
// Disable specific external interrupt (INT0 or INT1)
void disable_external_interrupt(uint8_t interrupt_num);
// Validate and configure interrupts
void configure_external_interrupt(uint8_t interrupt_num, uint8_t trigger_mode);

static inline void delay_us(double us);
static inline void delay_ms(double ms);

#endif
