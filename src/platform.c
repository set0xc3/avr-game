#include "platform.h"

#include "avr/interrupt.h"
#include "util/delay.h"

void
platform_init()
{
}

void
platform_deinit()
{
}

inline void
enable_external_interrupts()
{
  sei();
}

inline void
disable_external_interrupts()
{
  cli();
}

inline void
enable_external_interrupt(u8 interrupt_num)
{
  EIMSK |= (1 << interrupt_num);
}

inline void
disable_external_interrupt(u8 interrupt_num)
{
  EIMSK &= ~(1 << interrupt_num);
}

inline void
delay_us(f64 us)
{
  _delay_us(us);
}

inline void
delay_ms(f64 ms)
{
  _delay_ms(ms);
}
