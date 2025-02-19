#include "platform.h"

#include "avr/interrupt.h"
#include "util/delay.h"

void
platform_init(void)
{
}

void
platform_deinit(void)
{
}

void
enable_global_interrupts(void)
{
  sei();
}

void
disable_global_interrupts(void)
{
  cli();
}

void
enable_external_interrupt(uint8_t interrupt_num)
{
  EIMSK |= (1 << interrupt_num); // Enable INTn
}

void
disable_external_interrupt(uint8_t interrupt_num)
{
  EIMSK &= ~(1 << interrupt_num); // Disable INTn
}

void
configure_external_interrupt(uint8_t interrupt_num, uint8_t trigger_mode)
{
  if (interrupt_num > 1) {
    // Handle invalid interrupt number (ATmega328P supports INT0 and INT1)
    return;
  }

  // Configure trigger mode (e.g., LOW, CHANGE, FALLING, RISING)
  if (interrupt_num == 0) {
    EICRA = (EICRA & ~((1 << ISC01) | (1 << ISC00))) | (trigger_mode << ISC00);
  } else if (interrupt_num == 1) {
    EICRA = (EICRA & ~((1 << ISC11) | (1 << ISC10))) | (trigger_mode << ISC10);
  }
}

static inline void
delay_us(double us)
{
  _delay_us(us);
}

static inline void
delay_ms(double ms)
{
  _delay_ms(ms);
}
