#pragma once

namespace interrupt
{
    void attachTimer3AInterrupt(unsigned int interruptFrequencyHz);
    void detachTimer3Interrupt();
}
