/*
  Register definitions for the MKW01Z128 Freescale MCU

  Programmed by Theo Hill (mostly) & William Harrington
 */
#ifndef _KW0X_H_
#define _KW0X_H_
#include <stdint.h>

/* macros for padding */
#define  PASTE(a, b) _PASTE(a, b)
#define _PASTE(a, b) a ## b

#define PAD_BYTES(bytes)  const uint8_t PASTE(__PAD, __COUNTER__)[bytes] \
  __attribute__((deprecated("Padding must never be accessed")))

#define PACKED __attribute__((packed))

/* Port control and interrupts module registers */
struct PORT {
	uint32_t PCR[32];
	uint32_t GPCLR; // Write only
	uint32_t GPCHR; // Write only
	PAD_BYTES(24);
	uint32_t ISFR;  // W1C?
} PACKED;

/* define ports A-E */
#define PORTA (*((volatile struct PORT *) 0x40049000))
#define PORTB (*((volatile struct PORT *) 0x4004A000))
#define PORTC (*((volatile struct PORT *) 0x4004B000))
#define PORTD (*((volatile struct PORT *) 0x4004C000))
#define PORTE (*((volatile struct PORT *) 0x4004D000))

/* GPIO Module registers */
struct GPIO {
	uint32_t PDOR;
	uint32_t PSOR;
	uint32_t PCOR;
	uint32_t PTOR;
	uint32_t PDIR;
	uint32_t PDDR;
} PACKED;

/* define GPIO on ports A-E */
#define GPIOA (*((volatile struct GPIO *) 0x400FF000))
#define GPIOB (*((volatile struct GPIO *) 0x400FF040))
#define GPIOC (*((volatile struct GPIO *) 0x400FF080))
#define GPIOD (*((volatile struct GPIO *) 0x400FF0C0))
#define GPIOE (*((volatile struct GPIO *) 0x400FF100))

/* Oscillator Module registers */
struct OSC {
	uint8_t CR;
} PACKED;

/* define OSC0 */
#define OSC0 (*((volatile struct OSC *) 0x40065000))

/* System Integration Module registers */
struct SIM_t {
	uint32_t SOPT1;
	PAD_BYTES(4096);
	uint32_t SOPT2;
	PAD_BYTES(4);
	uint32_t SOPT4;
	uint32_t SOPT5;
	PAD_BYTES(4);
	uint32_t SOPT7;
	PAD_BYTES(8);
	uint32_t SDID;
	PAD_BYTES(12);
	uint32_t SCGC4;
	uint32_t SCGC5;
	uint32_t SCGC6;
	uint32_t SCGC7;
	uint32_t CLKDIV1;
	PAD_BYTES(4);
	uint32_t FCFG1;
	uint32_t FCFG2;
	PAD_BYTES(4);
	uint32_t UIDMH;
	uint32_t UIDML;
	uint32_t UIDL;
	PAD_BYTES(156);
	uint32_t COPC;
	uint32_t SRVCOP;
} PACKED;

/* define SIM */
#define SIM (*((volatile struct SIM_t *) 0x40047000))

/* Multi-purpose clock generator registers */
struct MCG_t {
	uint8_t C1;
	uint8_t C2;
	uint8_t C3;
	uint8_t C4;
	uint8_t C5;
	uint8_t C6;
	uint8_t S;
	PAD_BYTES(1);
	uint8_t SC;
	PAD_BYTES(1);
	uint8_t ATCVH;
	uint8_t ATCVL;
	uint8_t C7;
	uint8_t C8;
	PAD_BYTES(1);
	uint8_t C10;
} PACKED;

/* define MCG */
#define MCG (*((volatile struct MCG_t *) 0x40064000))

/* SPI Module registers */
struct SPI_t {
  	uint8_t S; /* status register */
  	uint8_t BR; /* baud rate register */
  	uint8_t C2; /* control register 2 */
  	uint8_t C1; /* control register 1 */
  	uint8_t ML; /* match low */
  	uint8_t MH; /* match high */
  	uint8_t DL; /* data low */
  	uint8_t DH; /* data high */
  	PAD_BYTES(2); /* padding for excess gap between DH & CI */
  	uint8_t CI; /* clear interrupt */
  	uint8_t C3; /* control register 3 */
} PACKED;

/* define SPI modules */
#define SPI0 (*((volatile struct SPI_t *) 0x40076000))
#define SPI1 (*((volatile struct SPI_t *) 0x40077000))

/* real-time clock module registers */
struct RTC_t {
  	uint32_t TSR; /* time seconds register */
  	uint32_t TPR; /* time prescaler register */
  	uint32_t TAR; /* time alarm register */
  	uint32_t TCR; /* time compensation register */
  	uint32_t CR; /* control register */
  	uint32_t SR; /* status register */
  	uint32_t LR; /* lock register */
  	uint32_t IER; /* interrupt enable register */
} PACKED;

/* define RTC */
#define RTC (*((volatile struct RTC_t *) 0x4003D000))

/* Timer/PWM Module registers */
struct TPM_t {
  	uint32_t SC; /* status and control register */
  	uint32_t CNT; /* counter register */
  	uint32_t MOD; /* modulo register */
  	uint32_t C0SC; /* channel n status and control register 0 */
  	uint32_t C0V; /* channel n value register 0 */
  	uint32_t C1SC; /* channel n status and control register 1 */
  	uint32_t C1V; /* channel n value register 1 */
  	uint32_t C2SC; /* channel n status and control register 2 */
  	uint32_t C2V; /* channel n value register 2 */
  	uint32_t C3SC; /* channel n status and control register 3 */
  	uint32_t C3V; /* channel n value register 3 */
  	uint32_t C4SC; /* channel n status and control register 4 */
  	uint32_t C4V; /* channel n value register 4 */
  	uint32_t C5SC; /* channel n status and control register 5 */
  	uint32_t C5V; /* channel n value register 5 */
  	PAD_BYTES(20);
  	uint32_t STATUS; /* capture and compare status register */
  	PAD_BYTES(48);
  	uint32_t CONF; /* configuration register */
} PACKED;

/* define TPM modules */
#define TPM0 (*((volatile struct TPM_t *) 0x40038000))
#define TPM1 (*((volatile struct TPM_t *) 0x40039000))
#define TPM2 (*((volatile struct TPM_t *) 0x4003A000))

/* System Mode Controller registers */
struct SMC_t {
	uint8_t PMPROT; /* Power Mode Protection register */
	uint8_t PMCTRL; /* Power Mode Control register */
	uint8_t STOPCTRL; /* Stop Control Register */
	uint8_t PMSTAT; /* Power Mode Status register */
} PACKED;

/* define SMC */
#define SMC (*((volatile struct SMC_t *) 0x4007E000))

/* Power Management Controller registers */
struct PMC_t {
	uint8_t LVDSC1; /* Low Voltage Detect Status and Control 1 register */
	uint8_t LVDSC2; /* Low Voltage Detect Status and Control 2 register */
	uint8_t REGSC; /* Regulator Status and Control register */
} PACKED;

/* define PMC */
#define PMC (*((volatile struct PMC_t *) 0x4007D001))

/* Low-Leakage Wakeup Unit */
struct LLWU_t {
	uint8_t PE1; /* Pin Enable 1 register */
	uint8_t PE2; /* Pin Enable 2 register */
	uint8_t PE3; /* Pin Enable 3 register */
	uint8_t PE4; /* Pin Enable 4 register */
	uint8_t ME; /* Module Enable register */
	uint8_t F1; /* Flag 1 register */
	uint8_t F2; /* Flag 2 register */
	uint8_t F3; /* Flag 3 register */
	uint8_t FILT1; /* Pin Filter 1 register */
	uint8_t FILT2; /* Pin Filter 2 register */
} PACKED;

/* define LLWU */
#define LLWU (*((volatile struct LLWU_t *) 0x4007C000))

/* Reset Control Module registers */
struct RCM_t {
	uint8_t SRS0; /* System Reset Status Register 0 */
	uint8_t SRS1; /* System Reset Status Register 1 */
	uint8_t RPFC; /* Reset Pin Filter Control register */
	uint8_t RPFW; /* Reset Pin Filter Width register */
} PACKED;

/* define RCM */
#define RCM (*((volatile struct RCM_t *) 0x4007F000))

/* Miscellaneous Control Module */
struct MCM_t {
	uint16_t PLAMC; /* Crossbar switch (AXBS) master configuration */
	uint32_t PLACR; /* Platform Control register */
	PAD_BYTES(48);
	uint32_t CPO; /* Compute Operation control register */
} PACKED;

/* define MCM */
#define MCM (*((volatile struct MCM_t *) 0xF000300A))

/* Micro Trace Buffer registers */
struct MTB_t {
	uint32_t POSITION; /* Position register */
	uint32_t MASTER; /* Master register */
	uint32_t FLOW; /* Flow register */
	uint32_t BASE; /* Base register */
	PAD_BYTES(3824);
	uint32_t MODECTRL; /* Integration Mode Control Register */
	PAD_BYTES(156);
	uint32_t TAGSET; /* Claim TAG Set Register */
	uint32_t TAGCLEAR; /* Claim TAG Clear Register */
	PAD_BYTES(8);
	uint32_t LOCKACCESS; /* Lock Access Register */
	uint32_t LOCKSTAT; /* Lock Status Register */
	uint32_t AUTHSTAT; /* Authentication Status Register */
	uint32_t DEVICEARCH; /* Device Architecture Register */
	PAD_BYTES(8);
	uint32_t DEVICECFG; /* Device Configuration Register */
	uint32_t DEVICETYPID; /* Device Type Identifier Register */
	uint32_t PERIPHID4; /* Peripheral ID register */
	uint32_t PERIPHID5; /* Peripheral ID register */
	uint32_t PERIPHID6; /* Peripheral ID register */
	uint32_t PERIPHID7; /* Peripheral ID register */
	uint32_t PERIPHID0; /* Peripheral ID register */
	uint32_t PERIPHID1; /* Peripheral ID register */
	uint32_t PERIPHID2; /* Peripheral ID register */
	uint32_t PERIPHID3; /* Peripheral ID register */
	uint32_t COMPID0; /* Component ID register */
	uint32_t COMPID1; /* Component ID register */
	uint32_t COMPID2; /* Component ID register */
	uint32_t COMPID3; /* Component ID register */
} PACKED;

/* Direct Memory Access Multiplexer */
struct DMAMUX_t {
	uint8_t CHCFG0; /* Channel Configuration register */
	uint8_t CHCFG1; /* Channel Configuration register */
	uint8_t CHCFG2; /* Channel Configuration register */
	uint8_t CHCFG3; /* Channel Configuration register */
} PACKED;

/* define DMAMUX0 */
#define DMAMUX0 (*((volatile struct DMAMUX_t *) 0x40021000))

/* Direct Memory Access Controller Module */
struct DMA_t {
  uint32_t SAR0; /* Source Address register */
  uint32_t DAR0; /* Destination Address register */
  uint32_t DSR_BCR0; /* DMA Status register / Byte count register */
  uint32_t DCR0; /* DMA control register */
} PACKED;

/* define DMA0 - DMA3 */
#define DMA0 (*((volatile struct DMA_t *) 0x40008100))
#define DMA1 (*((volatile struct DMA_t *) 0x40008110))
#define DMA2 (*((volatile struct DMA_t *) 0x40008120))
#define DMA3 (*((volatile struct DMA_t *) 0x40008130))

/* Analog to Digital Converters module */
struct ADC_t {
	uint32_t SC1A; /* ADC status and control registers 1 */
	uint32_t SC1B; /* ADC status and control registers 1 */
	uint32_t CFG1; /* ADC configuration register 1 */
	uint32_t CFG2; /* ADC configuration register 2 */
	uint32_t RA; /* ADC Data result register */
	uint32_t RB; /* ADC data result register */
	uint32_t CV1; /* Compare Value registers */
	uint32_t CV2; /* Compare Value registers */
	uint32_t SC2; /* Status and Control register 2 */
	uint32_t SC3; /* Status and Control register 3 */
	uint32_t OFS; /* ADC Offset Correction register */
	uint32_t PG; /* ADC Plus-Side Gain register */
	uint32_t MG; /* ADC Minus-Side Gain register */
	uint32_t CLPD; /* ADC Plus-Side General Calibration Value register */
	uint32_t CLPS; /* ADC Plus-Side General Calibration Value register */
	uint32_t CLP4; /* ADC Plus-Side General Calibration Value register */
	uint32_t CLP3; /* ADC Plus-Side General Calibration Value register */
	uint32_t CLP2; /* ADC Plus-Side General Calibration Value register */
	uint32_t CLP1; /* ADC Plus-Side General Calibration Value register */
	uint32_t CLP0; /* ADC Plus-Side General Calibration Value register */
	PAD_BYTES(4);
	uint32_t CLMD; /* ADC Minus-Side General Calibration Value register */
	uint32_t CLMS; /* ADC Minus-Side General Calibration Value register */
	uint32_t CLM4; /* ADC Minus-Side General Calibration Value register */
	uint32_t CLM3; /* ADC Minus-Side General Calibration Value register */
	uint32_t CLM2; /* ADC Minus-Side General Calibration Value register */
	uint32_t CLM1; /* ADC Minus-Side General Calibration Value register */
	uint32_t CLM0; /* ADC Minus-Side General Calibration Value register */
} PACKED;

/* define ADC */
#define ADC (*((volatile struct ADC_t *) 0x4003B000))

#undef PASTE
#undef _PASTE
#undef PAD_BYTES
#undef PACKED
#endif
