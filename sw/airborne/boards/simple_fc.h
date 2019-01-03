#ifndef CONFIG_SIMPLE_FC_H
#define CONFIG_SIMPLE_FC_H

#define BOARD_SIMPLE_FC

/* Lisa/M has a 25MHz external clock and 168MHz internal. */
#define EXT_CLK 25000000
#define AHB_CLK 168000000

/*
 * Onboard LEDs
 */

/* PB3 */
#ifndef USE_LED_1
#define USE_LED_1 1
#endif
#define LED_1_GPIO GPIOB
#define LED_1_GPIO_PIN GPIO3
#define LED_1_GPIO_ON gpio_clear
#define LED_1_GPIO_OFF gpio_set
#define LED_1_AFIO_REMAP ((void)0)

/* PB4 */
#ifndef USE_LED_2
#define USE_LED_2 1
#endif
#define LED_2_GPIO GPIOB
#define LED_2_GPIO_PIN GPIO4
#define LED_2_GPIO_ON gpio_clear
#define LED_2_GPIO_OFF gpio_set
#define LED_2_AFIO_REMAP ((void)0)

/* PB5 */
#ifndef USE_LED_3
#define USE_LED_3 1
#endif
#define LED_3_GPIO GPIOB
#define LED_3_GPIO_PIN GPIO5
#define LED_3_GPIO_ON gpio_clear
#define LED_3_GPIO_OFF gpio_set
#define LED_3_AFIO_REMAP ((void)0)

#ifdef USE_LED_4
#undef USE_LED_4
#warning "LED_4 not available on SimpleFC"
#endif

#ifdef USE_LED_5
#undef USE_LED_5
#warning "LED_5 not available on SimpleFC"
#endif

/* Default actuators driver */
#define DEFAULT_ACTUATORS "subsystems/actuators/actuators_pwm.h"
#define ActuatorDefaultSet(_x,_y) ActuatorPwmSet(_x,_y)
#define ActuatorsDefaultInit() ActuatorsPwmInit()
#define ActuatorsDefaultCommit() ActuatorsPwmCommit()


/* UART */
#define UART1_GPIO_AF GPIO_AF7
#define UART1_GPIO_PORT_RX GPIOA
#define UART1_GPIO_RX GPIO10
#define UART1_GPIO_PORT_TX GPIOA
#define UART1_GPIO_TX GPIO9

#define UART2_GPIO_AF GPIO_AF7
#define UART2_GPIO_PORT_RX GPIOA
#define UART2_GPIO_RX GPIO3
// TODO USART2 is rx only
#define UART2_GPIO_PORT_TX GPIOA
#define UART2_GPIO_TX GPIO2

#define UART3_GPIO_AF GPIO_AF7
#define UART3_GPIO_PORT_RX GPIOB
#define UART3_GPIO_RX GPIO11
#define UART3_GPIO_PORT_TX GPIOB
#define UART3_GPIO_TX GPIO10

#define UART4_GPIO_AF GPIO_AF8
#define UART4_GPIO_PORT_RX GPIOA
#define UART4_GPIO_RX GPIO1
// TODO USART2 is rx only
#define UART4_GPIO_PORT_TX GPIOA
#define UART4_GPIO_TX GPIO0

/*
 * Spektrum
 */
/* The line that is pulled low at power up to initiate the bind process */
/* These are not common between versions of lisa/mx and thus defined in the
 * version specific header files. */

#define SPEKTRUM_BIND_PIN GPIO3
#define SPEKTRUM_BIND_PIN_PORT GPIOC

#define SPEKTRUM_UART2_RCC RCC_USART2
#define SPEKTRUM_UART2_BANK GPIOA
#define SPEKTRUM_UART2_PIN GPIO3
#define SPEKTRUM_UART2_AF GPIO_AF7
#define SPEKTRUM_UART2_IRQ NVIC_USART2_IRQ
#define SPEKTRUM_UART2_ISR usart2_isr
#define SPEKTRUM_UART2_DEV USART2

#define SPEKTRUM_UART4_RCC RCC_UART4
#define SPEKTRUM_UART4_BANK GPIOA
#define SPEKTRUM_UART4_PIN GPIO1
#define SPEKTRUM_UART4_AF GPIO_AF8
#define SPEKTRUM_UART4_IRQ NVIC_UART4_IRQ
#define SPEKTRUM_UART4_ISR uart4_isr
#define SPEKTRUM_UART4_DEV UART4

/*
 * PPM config
 * 1 - PA1, Timer 2 input 2 (default)
 * 2 - PA3, Timer 2 input 4
 */

#ifndef PPM_CONFIG
#define PPM_CONFIG 1
#endif

#if PPM_CONFIG == 1

#define USE_PPM_TIM2 1
#define PPM_CHANNEL         TIM_IC2
#define PPM_TIMER_INPUT     TIM_IC_IN_TI2
#define PPM_IRQ             NVIC_TIM2_IRQ
#define PPM_CC_IE           TIM_DIER_CC2IE
#define PPM_CC_IF           TIM_SR_CC2IF
#define PPM_GPIO_PORT       GPIOA
#define PPM_GPIO_PIN        GPIO1
#define PPM_GPIO_AF         GPIO_AF1

#elif PPM_CONFIG == 2
#define USE_PPM_TIM1 1
#define PPM_CHANNEL         TIM_IC4
#define PPM_TIMER_INPUT     TIM_IC_IN_TI4
#define PPM_IRQ             NVIC_TIM2_IRQ
#define PPM_CC_IE           TIM_DIER_CC4IE
#define PPM_CC_IF           TIM_SR_CC4IF
#define PPM_GPIO_PORT       GPIOA
#define PPM_GPIO_PIN        GPIO3
#define PPM_GPIO_AF         GPIO_AF1

#else
#error "Unknown PPM config"

#endif // PPM_CONFIG

/* SPI */
#define SPI1_GPIO_AF GPIO_AF5
#define SPI1_GPIO_PORT_MISO GPIOA
#define SPI1_GPIO_MISO GPIO6
#define SPI1_GPIO_PORT_MOSI GPIOA
#define SPI1_GPIO_MOSI GPIO7
#define SPI1_GPIO_PORT_SCK GPIOA
#define SPI1_GPIO_SCK GPIO5

// PC4 -> MPU
#define SPI_SELECT_SLAVE0_PORT GPIOC
#define SPI_SELECT_SLAVE0_PIN GPIO4

// PC5 -> Baro
#define SPI_SELECT_SLAVE1_PORT GPIOC
#define SPI_SELECT_SLAVE1_PIN GPIO5


/* I2C mapping */
#define I2C1_GPIO_PORT GPIOB
#define I2C1_GPIO_SCL GPIO6
#define I2C1_GPIO_SDA GPIO7


/*
 * ADC
 */

/* Onboard ADCs */
/*
   BATT PC0/ADC10
   CURR PC1/ADC11
   ADC2 PC2/ADC12
   ADC3 PC3/ADC13
*/

/* provide defines that can be used to access the ADC_x in the code or airframe file
 * these directly map to the index number of the 4 adc channels defined above
 * 4th (index 3) is used for bat monitoring by default
 */
#ifndef USE_ADC_1
#define USE_ADC_1
#endif

#if USE_ADC_1
#define AD1_1_CHANNEL 10
#define ADC_1 AD1_1
#define ADC_1_GPIO_PORT GPIOC
#define ADC_1_GPIO_PIN GPIO3
#endif

#if USE_ADC_2
#define AD1_2_CHANNEL 11
#define ADC_2 AD1_2
#define ADC_2_GPIO_PORT GPIOC
#define ADC_2_GPIO_PIN GPIO0
#endif

#if USE_ADC_3
#define AD1_3_CHANNEL 12
#define ADC_3 AD1_3
#define ADC_3_GPIO_PORT GPIOC
#define ADC_3_GPIO_PIN GPIO1
#endif

#if USE_ADC_4
#define AD2_1_CHANNEL 13
#define ADC_4 AD1_4
#define ADC_4_GPIO_PORT GPIOC
#define ADC_4_GPIO_PIN GPIO5
#endif

/* allow to define ADC_CHANNEL_VSUPPLY in the airframe file*/
#ifndef ADC_CHANNEL_VSUPPLY
#define ADC_CHANNEL_VSUPPLY ADC_1
#endif

#define DefaultVoltageOfAdc(adc) (0.0045*adc)

/*
 * PWM
 *
 */
#define PWM_USE_TIM3 1
#define PWM_USE_TIM4 1
#define PWM_USE_TIM12 1

#define USE_PWM1 1
#define USE_PWM2 1
#define USE_PWM3 1
#define USE_PWM4 1
#define USE_PWM5 1
#define USE_PWM6 1
#define USE_PWM7 1
#define USE_PWM8 1

#define ACTUATORS_PWM_NB 8

/*
M1 T4C4
M2 T4C3
*/
#if USE_PWM1
#define PWM_SERVO_1 0
#define PWM_SERVO_1_TIMER TIM4
#define PWM_SERVO_1_GPIO GPIOB
#define PWM_SERVO_1_PIN GPIO9
#define PWM_SERVO_1_AF GPIO_AF2
#define PWM_SERVO_1_OC TIM_OC4
#define PWM_SERVO_1_OC_BIT (1<<3)
#else
#define PWM_SERVO_1_OC_BIT 0
#endif

#if USE_PWM2
#define PWM_SERVO_2 1
#define PWM_SERVO_2_TIMER TIM4
#define PWM_SERVO_2_GPIO GPIOB
#define PWM_SERVO_2_PIN GPIO8
#define PWM_SERVO_2_AF GPIO_AF2
#define PWM_SERVO_2_OC TIM_OC3
#define PWM_SERVO_2_OC_BIT (1<<2)
#else
#define PWM_SERVO_2_OC_BIT 0
#endif

/*
M3 T3C2
M4 T3C1
*/
#if USE_PWM3
#define PWM_SERVO_3 2
#define PWM_SERVO_3_TIMER TIM3
#define PWM_SERVO_3_GPIO GPIOC
#define PWM_SERVO_3_PIN GPIO7
#define PWM_SERVO_3_AF GPIO_AF2
#define PWM_SERVO_3_OC TIM_OC2
#define PWM_SERVO_3_OC_BIT (1<<1)
#else
#define PWM_SERVO_3_OC_BIT 0
#endif

#if USE_PWM4
#define PWM_SERVO_4 3
#define PWM_SERVO_4_TIMER TIM3
#define PWM_SERVO_4_GPIO GPIOC
#define PWM_SERVO_4_PIN GPIO6
#define PWM_SERVO_4_AF GPIO_AF2
#define PWM_SERVO_4_OC TIM_OC1
#define PWM_SERVO_4_OC_BIT (1<<0)
#else
#define PWM_SERVO_4_OC_BIT 0
#endif

/*
M5 T12C2
M6 T12C1
*/
#if USE_PWM5
#define PWM_SERVO_5 4
#define PWM_SERVO_5_TIMER TIM12
#define PWM_SERVO_5_GPIO GPIOB
#define PWM_SERVO_5_PIN GPIO15
#define PWM_SERVO_5_AF GPIO_AF9
#define PWM_SERVO_5_OC TIM_OC2
#define PWM_SERVO_5_OC_BIT (1<<1)
#else
#define PWM_SERVO_5_OC_BIT 0
#endif

#if USE_PWM6
#define PWM_SERVO_6 5
#define PWM_SERVO_6_TIMER TIM12
#define PWM_SERVO_6_GPIO GPIOB
#define PWM_SERVO_6_PIN GPIO14
#define PWM_SERVO_6_AF GPIO_AF9
#define PWM_SERVO_6_OC TIM_OC1
#define PWM_SERVO_6_OC_BIT (1<<0)
#else
#define PWM_SERVO_6_OC_BIT 0
#endif

/*
M7 T3C3
M8 T3C4
*/
#if USE_PWM7
#define PWM_SERVO_7 6
#define PWM_SERVO_7_TIMER TIM3
#define PWM_SERVO_7_GPIO GPIOB
#define PWM_SERVO_7_PIN GPIO0
#define PWM_SERVO_7_AF GPIO_AF2
#define PWM_SERVO_7_OC TIM_OC3
#define PWM_SERVO_7_OC_BIT (1<<2)
#else
#define PWM_SERVO_7_OC_BIT 0
#endif

#if USE_PWM8
#define PWM_SERVO_8 7
#define PWM_SERVO_8_TIMER TIM3
#define PWM_SERVO_8_GPIO GPIOB
#define PWM_SERVO_8_PIN GPIO1
#define PWM_SERVO_8_AF GPIO_AF2
#define PWM_SERVO_8_OC TIM_OC4
#define PWM_SERVO_8_OC_BIT (1<<3)
#else
#define PWM_SERVO_8_OC_BIT 0
#endif

#define PWM_TIM3_CHAN_MASK (PWM_SERVO_3_OC_BIT|PWM_SERVO_4_OC_BIT|PWM_SERVO_7_OC_BIT|PWM_SERVO_8_OC_BIT)
#define PWM_TIM4_CHAN_MASK (PWM_SERVO_1_OC_BIT|PWM_SERVO_2_OC_BIT)
#define PWM_TIM12_CHAN_MASK (PWM_SERVO_5_OC_BIT|PWM_SERVO_6_OC_BIT)

/* by default activate onboard baro */
//#ifndef USE_BARO_BOARD
//#define USE_BARO_BOARD 1
//#endif

#endif /* CONFIG_SIMPLE_FC_H */
