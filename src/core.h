#ifndef CORE_H
#define CORE_H

#include <avr/interrupt.h>
#include <stdbool.h>
#include <util/delay.h>

#define Seconds(value) ((uint32_t)value * 1000UL)
#define Minutes(value) ((uint32_t)value * 60UL * 1000UL)

#define ArrayCount(a) (sizeof((a)) / sizeof(*(a)))

#define Clamp(value, min, max)                                                \
  ((value <= min) ? min : (value >= max) ? max : value)
#define ClampTop(value, max) ((value >= max) ? max : value)

// GPIO

// Установка пина как входа (DDRx)
static inline void
gpio_mode_input(volatile uint8_t *ddr, uint8_t pin)
{
  *ddr &= ~(1 << pin); // DDRx бит = 0
}

// Установка пина как выхода (DDRx)
static inline void
gpio_mode_output(volatile uint8_t *ddr, uint8_t pin)
{
  *ddr |= (1 << pin); // DDRx бит = 1
}

// Установка низкого уровня (PORTx)
static inline void
gpio_set_low(volatile uint8_t *port, uint8_t pin)
{
  *port &= ~(1 << pin); // PORTx бит = 0
}

// Установка высокого уровня (PORTx)
static inline void
gpio_set_high(volatile uint8_t *port, uint8_t pin)
{
  *port |= (1 << pin); // PORTx бит = 1
}

// Переключение уровня (PORTx)
static inline void
gpio_set_toggle(volatile uint8_t *port, uint8_t pin)
{
  *port ^= (1 << pin);
}

// Включение подтягивающего резистора (для входа)
static inline void
gpio_enable_pullup(volatile uint8_t *port, uint8_t pin)
{
  *port |= (1 << pin); // PORTx бит = 1 при DDRx = 0
}

// Чтение состояния пина (PINx)
static inline bool
gpio_get_level(volatile uint8_t *pin_reg, uint8_t pin)
{
  return (*pin_reg & (1 << pin)) != false;
}

#endif
