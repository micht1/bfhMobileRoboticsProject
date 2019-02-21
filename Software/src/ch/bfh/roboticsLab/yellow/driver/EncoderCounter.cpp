#line 2 "ch/bfh/roboticsLab/yellow/driver/EncoderCounter.cpp"
/* EncoderCounter.cpp
 * Copyright (c) ZHAW
 * All rights reserved.
 */

#include <ch/bfh/roboticsLab/yellow/driver/EncoderCounter.h>

namespace ch {
namespace bfh {
namespace roboticsLab {
namespace yellow {
namespace driver {

EncoderCounter::EncoderCounter(const PinName a, const PinName b) {

  /* Implementaiton note:
   * Only certain pin combinations are supported:
   * (a == PA_0) && (b == PA_1) -- Uses TIM2 CH1 & CH2
   * (a == PA_6) && (b == PC_7) -- Uses TIM3 CH1 & CH2
   * (a == PB_6) && (b == PB_7) -- Uses TIM4 CH1 & CH2
   */

  /* Configure timer for the given pin pair */
  if ((a == PA_0) && (b == PA_1)) {

    // pinmap OK, use TIM2 CH1 and CH2
    TIM = TIM2;

    // Note: Port A is enabled by default by mbed

    // configure general purpose I/O registers
    GPIOA->MODER &= ~GPIO_MODER_MODER0;     // reset port A0
    GPIOA->MODER |= GPIO_MODER_MODER0_1;    // set alternate mode of port A0
    GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR0;     // reset pull-up/pull-down on port A0
    GPIOA->PUPDR |= GPIO_PUPDR_PUPDR0_1;    // set input as pull-down
    GPIOA->AFR[0] &= ~(0xF << 4 * 0);       // reset alternate function of port A0
    GPIOA->AFR[0] |= 1 << 4 * 0;            // set alternate funtion 1 of port A0

    GPIOA->MODER &= ~GPIO_MODER_MODER1;     // reset port A1
    GPIOA->MODER |= GPIO_MODER_MODER1_1;    // set alternate mode of port A1
    GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR1;     // reset pull-up/pull-down on port A1
    GPIOA->PUPDR |= GPIO_PUPDR_PUPDR1_1;    // set input as pull-down
    GPIOA->AFR[0] &= ~(0xF << 4 * 1);       // reset alternate function of port A1
    GPIOA->AFR[0] |= 1 << 4 * 1;            // set alternate funtion 1 of port A1

    // configure reset and clock control registers
    RCC->APB1RSTR |= RCC_APB1RSTR_TIM2RST;  //reset TIM2 controller
    RCC->APB1RSTR &= ~RCC_APB1RSTR_TIM2RST;

    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;     // TIM2 clock enable

  } else if ((a == PA_6) && (b == PC_7)) {

    // pinmap OK, use TIM3 CH1 and CH2
    TIM = TIM3;

    // Note: Port A is enabled by default by mbed, Port C must be enabled manually
    // configure reset and clock control registers
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

    // configure general purpose I/O registers
    GPIOA->MODER &= ~GPIO_MODER_MODER6;     // reset port A6
    GPIOA->MODER |= GPIO_MODER_MODER6_1;    // set alternate mode of port A6
    GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR6;     // reset pull-up/pull-down on port A6
    GPIOA->PUPDR |= GPIO_PUPDR_PUPDR6_1;    // set input as pull-down
    GPIOA->AFR[0] &= ~(0xF << 4 * 6);       // reset alternate function of port A6
    GPIOA->AFR[0] |= 2 << 4 * 6;            // set alternate funtion 2 of port A6

    GPIOC->MODER &= ~GPIO_MODER_MODER7;     // reset port C7
    GPIOC->MODER |= GPIO_MODER_MODER7_1;    // set alternate mode of port C7
    GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR7;     // reset pull-up/pull-down on port C7
    GPIOC->PUPDR |= GPIO_PUPDR_PUPDR7_1;    // set input as pull-down
    GPIOC->AFR[0] &= ~0xF0000000;           // reset alternate function of port C7
    GPIOC->AFR[0] |= 2 << 4 * 7;            // set alternate funtion 2 of port C7

    // configure reset and clock control registers
    RCC->APB1RSTR |= RCC_APB1RSTR_TIM3RST;  //reset TIM3 controller
    RCC->APB1RSTR &= ~RCC_APB1RSTR_TIM3RST;

    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;     // TIM3 clock enable

  } else if ((a == PB_6) && (b == PB_7)) {

    // pinmap OK, use TIM4 CH1 and CH2
    TIM = TIM4;

    // configure reset and clock control registers
    // Note: Port B must be enabled manually
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

    // configure general purpose I/O registers
    GPIOB->MODER &= ~GPIO_MODER_MODER6;     // reset port B6
    GPIOB->MODER |= GPIO_MODER_MODER6_1;    // set alternate mode of port B6
    GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR6;     // reset pull-up/pull-down on port B6
    GPIOB->PUPDR |= GPIO_PUPDR_PUPDR6_1;    // set input as pull-down
    GPIOB->AFR[0] &= ~(0xF << 4 * 6);       // reset alternate function of port B6
    GPIOB->AFR[0] |= 2 << 4 * 6;            // set alternate funtion 2 of port B6

    GPIOB->MODER &= ~GPIO_MODER_MODER7;     // reset port B7
    GPIOB->MODER |= GPIO_MODER_MODER7_1;    // set alternate mode of port B7
    GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR7;     // reset pull-up/pull-down on port B7
    GPIOB->PUPDR |= GPIO_PUPDR_PUPDR7_1;    // set input as pull-down
    GPIOB->AFR[0] &= ~0xF0000000;           // reset alternate function of port B7
    GPIOB->AFR[0] |= 2 << 4 * 7;            // set alternate funtion 2 of port B7

    // configure reset and clock control registers
    RCC->APB1RSTR |= RCC_APB1RSTR_TIM4RST;  //reset TIM4 controller
    RCC->APB1RSTR &= ~RCC_APB1RSTR_TIM4RST;

    RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;     // TIM4 clock enable

  } else {

    // Notify user of wrong paramerers.
    // This is a compile-time error but an assertion here doesn't seem to work properly (see mbed_assert.h)
    // Exceptions are not enabled for runtime errors.
//    printf("EncoderCounter: pin combination not supported");
    return;
  }

  // configure general purpose timer
  TIM->CR1 = 0x0000;          // counter disable
  TIM->CR2 = 0x0000;          // reset master mode selection
  TIM->SMCR = TIM_SMCR_SMS_1 | TIM_SMCR_SMS_0; // counting on both TI1 & TI2 edges
  TIM->CCMR1 = TIM_CCMR1_CC2S_0 | TIM_CCMR1_CC1S_0;
  TIM->CCMR2 = 0x0000;        // reset capture mode register 2
  TIM->CCER = TIM_CCER_CC2E | TIM_CCER_CC1E;
  TIM->CNT = 0x0000;          // reset counter value
  TIM->ARR = 0xFFFF;          // auto reload register
  TIM->CR1 = TIM_CR1_CEN;     // counter enable
}

EncoderCounter::~EncoderCounter() {
}

void EncoderCounter::reset() {

  TIM->CNT = 0x0000;
}

void EncoderCounter::reset(const int16_t offset) {

  TIM->CNT = -offset;
}

int16_t EncoderCounter::read() {

  return static_cast<int16_t>(-TIM->CNT);
}

/**
 * The empty operator is a shorthand notation of the <code>read()</code> method.
 */
EncoderCounter::operator int16_t() {

  return read();
}

}
}
}
}
}
