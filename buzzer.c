#include"buzzer.h"

void buzzer_on(void)
{
		BuzzerPort=0;
}

void buzzer_off(void)
{
		BuzzerPort=1;
}

void buzzer_delay(void)
{
		BuzzerPort=0;
		delay_ms(400);
		BuzzerPort=1;
		delay_ms(400);
}
