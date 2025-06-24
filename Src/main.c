/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Benoit Christian Mbole Zogo
 * @brief          : LED Blinky Project – STM32F407 (Bare-metal, no HAL)
 ******************************************************************************
 * @attention
 *
 * This project demonstrates how to toggle an LED connected to PD15
 * using direct register access (bare-metal approach).
 *
 ******************************************************************************
 */

#include <stdint.h>
#include <stdio.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

/* -------------------- Peripheral Base Addresses -------------------- */
#define PERIPH_BASE     (0x40000000UL)        // Base address for peripherals
#define AHB1_OFFSET     (0x00020000UL)        // Offset for AHB1 peripherals
#define AHB1_BASE       (PERIPH_BASE + AHB1_OFFSET)

#define GPIOD_OFFSET    (0x00000C00UL)        // Offset for GPIOD
#define GPIOD_BASE      (AHB1_BASE + GPIOD_OFFSET)
#define RCC_BASE        (AHB1_BASE + 0x3800UL) // RCC base address

/* -------------------- Register Definitions -------------------- */
#define RCC_AHB1ENR     (*(volatile uint32_t *)(RCC_BASE + 0x30))   // RCC AHB1 peripheral clock enable register
#define GPIOD_MODER     (*(volatile uint32_t *)(GPIOD_BASE + 0x00)) // GPIOD mode register
#define GPIOD_ODR       (*(volatile uint32_t *)(GPIOD_BASE + 0x14)) // GPIOD output data register

/* -------------------- Bit Definitions -------------------- */
#define RCC_AHB1ENR_GPIOD_EN   (1 << 3)      // Enable clock for GPIOD
#define GPIOD_PIN15            (1 << 15)     // Pin 15 on GPIOD

/* -------------------- Delay Constant -------------------- */
#define DELAY_COUNT    (1000000UL)           // Rough delay count

/* -------------------- Function Prototypes -------------------- */
void delay(volatile uint32_t count);

/* -------------------- Main Function -------------------- */
int main(void)
{
    // 1. Enable clock access to GPIOD
    RCC_AHB1ENR |= RCC_AHB1ENR_GPIOD_EN;

    // 2. Configure PD15 as general-purpose output
    GPIOD_MODER &= ~(3 << (15 * 2));  // Clear mode bits for pin 15
    GPIOD_MODER |=  (1 << (15 * 2));  // Set pin 15 to output mode (01)

    // 3. Blink the LED
    while (1)
    {
        GPIOD_ODR ^= GPIOD_PIN15;     // Toggle PD15
        delay(DELAY_COUNT);           // Delay
    }
}

/* -------------------- Delay Function -------------------- */
/**
 * @brief  Simple blocking delay using a loop
 * @param  count: number of iterations to delay
 */
void delay(volatile uint32_t count)
{
    while (count--)
    {
        __asm__("nop");  // No Operation – waste one CPU cycle
    }
}
