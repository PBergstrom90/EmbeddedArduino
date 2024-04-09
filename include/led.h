#ifndef LED_H_
#define LED_H_

#define MIN_POWER_VALUE 0
#define MAX_POWER_VALUE 255 

void ledToggle();
void ledPowerValue(uint8_t value);

#endif // _LED_H_