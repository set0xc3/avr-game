#include "core.h"
#include "platform.h"
#include "timer.h"

#include "avr/interrupt.h"
#include <avr/io.h>

#include <stdbool.h>
#include <stdint.h>

// Глобальный счётчик миллисекунд (обновляется Timer1)
volatile uint32_t g_counter_ms = 0;

// Настройка Timer1 в режиме CTC для генерации прерывания каждую 1 мс
void
Timer1_Init(void)
{
  // Режим CTC: WGM12 = 1
  TCCR1B |= (1 << WGM12);
  // При F_CPU = 16 МГц и делителе 64:
  // Частота таймера = 16e6 / 64 = 250 kHz, т.е. 250 тактов = 1 мс.
  OCR1A = 250 - 1;
  // Устанавливаем делитель 64 (CS11 и CS10)
  TCCR1B |= (1 << CS11) | (1 << CS10);
  // Обнуляем Timer1
  TCNT1 = 0;
  // Разрешаем прерывание по совпадению с OCR1A
  TIMSK1 |= (1 << OCIE1A);
}

void
hardware_init(void)
{
  enable_global_interrupts();
  Timer1_Init();
}

int
main(void)
{
  hardware_init();

  gpio_mode_output(&DDRB, DDB5);

  Timer timer_a = { 0 };
  timer_init(&timer_a, 0, 100, 100, true);
  timer_start(&timer_a);

  while (1) {
    // TimerBegin
    //
    timer_update(&timer_a, g_counter_ms);

    // TimerUpdate
    // ...

    // TimerEnd
    //
    switch (timer_a.state) {
    case TIMER_STATE_WAITING:
      gpio_set_low(&PORTB, PB5);
      break;
    case TIMER_STATE_RUNNING:
      gpio_set_high(&PORTB, PB5);
      break;
    case TIMER_STATE_SLEEPING:
      gpio_set_low(&PORTB, PB5);
      break;
    case TIMER_STATE_DONE:
      gpio_set_low(&PORTB, PB5);
      break;
    }
  }

  return 0;
}

// Вызывается каждую 1 мс. */
ISR(TIMER1_COMPA_vect) { g_counter_ms++; }
