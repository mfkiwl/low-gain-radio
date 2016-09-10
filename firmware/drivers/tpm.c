#include <stdbool.h>

#include "v1_1.h"
#include "lgr_vector.h"
#include "core_cm0plus.h"
#include "cmsis_gcc.h"

#include "led.h"
#include "clocks.h"
#include "ringbuffer.h"

#include "tpm.h"
#define TPM0_MOD_1uS_at_24Mhz    	23
#define TPM0_MOD_1mS_at_24Mhz    	23999

static bool tpm0_count_flag = false;

void isr_tpm0(void)
{
	//read TOF register, if bit in tfo is set, then proceed.
	if ((TPM0.SC & TPM_SC_TOF) != 0)
	{
		led_action(TOGGLE, blue);
		reset_tof();
		tpm0_count_flag  = true;
	}
	else return;
}

void tpm0_mod_1us(void)
{
	TPM0.MOD = TPM0_MOD_1uS_at_24Mhz ;
}

void tpm0_mod_1ms(void)
{
	TPM0.MOD = TPM0_MOD_1mS_at_24Mhz ;
}

void reset_tof()
{
	TPM0.C0SC |= TPM_C0SC_CHF;
	TPM0.STATUS |= TPM_STATUS_TOF;
	TPM0.SC |= TPM_SC_TOF;
}

void disable_tpm()
{
	TPM0.SC &= TPM_SC_DISABLE;
}

void tpm0_enable_int() {
	TPM0.SC |= TPM0_TOIE;
}

void tpm0_disable_int(void) {
	TPM0.SC &= TPM0_TOIE_MASK;
}

void tpm0_sc_init()
{
	TPM0.SC   = TPM0_SC;
}
void tpm0_conf_init()
{
	TPM0.CONF = TPM0_CONF_LGR;
	TPM0.C0SC = (0b01 << 4); // software compare
}

void tpm0_init()
{
	//led_action(TOGGLE, green);
	NVIC_EnableIRQ(TPM0_IRQn);
	__enable_irq();
	enable_tpm_mcg_clock();
	tpm0_conf_init();
	tpm0_mod_1ms();
	tpm0_sc_init();
	tpm0_enable_int();
	tpm0_count_flag  = false;
}

void    tpm0_test_loop()
{
	uint32_t tpm0_count = 0;
	while(1)
	{
		if(tpm0_count_flag)
		{
			tpm0_count++;
		}
		if ((tpm0_count_flag % 1000) == 0)
		{
			printf("tic\t%d\r\n", tpm0_count);
		}
	}
}
