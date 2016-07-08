#include <avr/interrupt.h>
//#include <LiquidCrystal.h>

#ifndef phys253_h
#define phys253_h
#include <phys253.h>
#endif

#include "EDetect.h"
#include "LLRobot.h"

#define ledPin 13
 
void setup()
{
    pinMode(13, OUTPUT);
}
 
/* This gets called when the Timer3 comparison interrupt is triggered */
ISR(TIMER3_COMPA_vect)
{
    /* Toggle LED pin */
    digitalWrite(ledPin, !digitalRead(ledPin));
}
 

void attachTimer3AInterrupt(unsigned int interruptFrequencyHz)
{
    const uint32_t timerOverflowHz[] = {F_CPU / 1, F_CPU / 8, F_CPU / 64, F_CPU / 256, F_CPU / 1024};
    for (uint8_t i = 4; i < 5; i++)
    {
        /* The number of 16-bit timer overflows needed to obtain the desired frequency */
        const uint32_t overflowsNeeded = timerOverflowHz[i] / interruptFrequencyHz;
        /* Check if the number of overflows can be stored in a 16-bit register */
        if (overflowsNeeded <= 0xFFFFU)
        {
            noInterrupts();
            TCCR3A = 0;                         /* Clear current comparison value */
            TCNT3  = 0;                         /* Clear current timer value      */
            OCR3A  = (uint16_t)overflowsNeeded; /* Set timer comparison value     */
            TCCR3A = (1 << WGM32);              /* Set timer comparison mode      */
            TCCR3A |= i + 1;                    /* Set timer prescaler value      */
            TIMSK |= (1 << OCIE3A);            /* Set timer interrupt enable     */
            interrupts();
            return;
        }
    }
}
 
/* Disables the Timer3A comparison interrupt */
void detachTimer3Interrupt()
{
    TIMSK &= ~(1 << OCIE3A);
}
 
void loop()
{
}

