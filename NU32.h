#ifndef NU32__H__
#define NU32__H__

#include <xc.h>                     // processor SFR definitions
#include <sys/attribs.h>            // __ISR macro

/*
 * Initialize User Interface, LEDs and buttons
 */
#define YELLOW_LED LATEbits.LATE0    // LED1 on the UBW32 board
#define RED_LED    LATEbits.LATE1    // LED2 on the UBW32 board
#define WHITE_LED  LATEbits.LATE2    // LED3 on the UBW32 board
#define GREEN_LED  LATEbits.LATE3    // LED4 on the UBW32 board
#define USER_SW    PORTEbits.RE6     // USER button on the UBW32 board

#define LED_OFF (1)
#define LED_ON  (0)
#define SW_PRESSED  (0)
#define SW_RELEASED (1)

#define NU32_SYS_FREQ 80000000ul    // 80 million Hz

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Configure oscillator setup
 */
#if defined(USE_XTAL)

#define PRIMARY_OSC_TYPE XT
#define OSC_FREQUENCY       (8000000ul) /* External crystal frequency */
#define PLL_INPUT_DIVIDER   (2ul)
#define PLL_MULTIPLIER      (20ul)

#if defined(USE_PLL)
#define OSC_SELECTOR        (0b011)     /* Use Primary Oscillator + PLL*/
#else
#define OSC_SELECTOR        (0b010)     /* Use Primary Oscillator */
#endif

#else

#define PRIMARY_OSC_TYPE OFF
#define OSC_FREQUENCY       (8000000ul) /* Internal Fast RC oscillator frequency */
#define PLL_INPUT_DIVIDER   (2ul)
#define PLL_MULTIPLIER      (20ul)

#if defined(USE_PLL)
#define OSC_SELECTOR        (0b001)     /* Use FRC + PLL */
#else
#define OSC_SELECTOR        (0b000)     /* Use FRC */
#endif

#endif

#if defined(USE_PLL)
#define GetSystemClock()        ((OSC_FREQUENCY/PLL_INPUT_DIVIDER)*PLL_MULTIPLIER)
#define PB_CLOCK_DIVIDER        (1ul)
#else
#define GetSystemClock()        (OSC_FREQUENCY)
#define PB_CLOCK_DIVIDER        (1ul)
#endif
#define GetPeripheralClock()    (GetSystemClock()/PB_CLOCK_DIVIDER)
#define GetInstructionClock()   (GetSystemClock())

    void PIC_Init(void);
    void NU32_Startup(void);
	void NU32_ReadUART3(char * string, int maxLength);
	void NU32_WriteUART3(const char * string);


/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif
#endif // NU32__H__
