/*
 / _____)             _              | |
( (____  _____ ____ _| |_ _____  ____| |__
 \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 _____) ) ____| | | || |_| ____( (___| | | |
(______/|_____)_|_|_| \__)_____)\____)_| |_|
    (C)2013 Semtech

Description: Target board general functions implementation

License: Revised BSD License, see LICENSE.TXT file include in the project

Maintainer: Andreas Pella (IMST GmbH), Miguel Luis and Gregory Cristian

Modified for Unwired Range rev. 2 by oleg@unwds.com
*/
#ifndef __BOARD_H__
#define __BOARD_H__

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "stm32l1xx.h"
#include "stm32l1xx_hal.h"
#include "utilities.h"
#include "timer.h"
#include "delay.h"
#include "gpio.h"
#include "adc.h"
#include "spi.h"
#include "i2c.h"
#include "uart.h"
#include "radio.h"
#include "sx1276/sx1276.h"
#include "adc-board.h"
#include "rtc-board.h"
#include "sx1276-board.h"

/*!
 * Generic definition
 */
#ifndef SUCCESS
#define SUCCESS                                     1
#endif

#ifndef FAIL
#define FAIL                                        0
#endif

/*!
 * Enables the choice between Led1 and Potentiometer.
 * LED1 and Potentiometer are exclusive.
 * \remark When using Potentimeter don't forget  that the connection between
 *         ADC input pin of iM880A and the Demoboard Poti requires a connection
 *         between X5:11 - X5:18.
 *         Remove the original jumpers for that.
 *         On SK-iM880A X5 is the 20 pin header close to the DIP SW and Buttons
 */
#define USE_POTENTIOMETER                           0


/*!
 * Board MCU pins definitions
 */

#define RADIO_RESET                                 PA_0

#define RADIO_MOSI                                  PB_15
#define RADIO_MISO                                  PB_14
#define RADIO_SCLK                                  PB_13
#define RADIO_NSS                                   PB_12

#define RADIO_DIO_0                                 PB_11
#define RADIO_DIO_1                                 PB_10
#define RADIO_DIO_2                                 PB_9
#define RADIO_DIO_3                                 PB_8
// #define RADIO_DIO_4                                 PB_4 // to be removed
// #define RADIO_DIO_5                                 PB_5 // to be removed

// #define RADIO_ANT_SWITCH_HF                         PA_12 // to be removed
// #define RADIO_ANT_SWITCH_LF                         PB_2 // to be removed

#define OSC_LSE_IN                                  PC_14
#define OSC_LSE_OUT                                 PC_15

// #define OSC_HSE_IN                                  PH_0 // to be removed
// #define OSC_HSE_OUT                                 PH_1 // to be removed

// #define USB_DM                                      PA_12 // to be removed
// #define USB_DP                                      PA_12 // to be removed

#define JTAG_TMS                                    PA_13
#define JTAG_TCK                                    PA_14
#define JTAG_TDI                                    PA_15
#define JTAG_TDO                                    PB_3
// #define JTAG_NRST                                   PB_4 // to be removed

#define I2C_SCL                                     PB_10
#define I2C_SDA                                     PB_11

#define UART_TX                                     PB_7
#define UART_RX                                     PB_6

#if ( USE_POTENTIOMETER == 1 )
#define POTI                                        PA_3
#else
#define LED_1                                       PA_1
#endif
#define LED_2                                       PA_2
#define LED_3                                       PA_3
#define LED_4                                       PA_6

/*!
 * LED GPIO pins objects
 */
#if ( USE_POTENTIOMETER == 0 )
extern Gpio_t Led1;
#endif
extern Gpio_t Led2;
extern Gpio_t Led3;
extern Gpio_t Led4;

/*!
 * MCU objects
 */
extern Adc_t Adc;
extern I2c_t I2c;
extern Uart_t Uart1;

enum BoardPowerSource
{
    USB_POWER = 0,
    BATTERY_POWER
};


/*!
 * \brief Initializes the target board peripherals.
 */
void BoardInitMcu( void );

/*!
 * \brief Initializes the boards peripherals.
 */
void BoardInitPeriph( void );

/*!
 * \brief De-initializes the target board peripherals to decrease power
 *        consumption.
 */
void BoardDeInitMcu( void );

/*!
 * \brief Measure the Potentiometer level
 *
 * \retval value  Potentiometer level ( value in percent )
 */
uint8_t BoardMeasurePotiLevel( void );

/*!
 * \brief Measure the VDD voltage
 *
 * \retval value  VDD voltage in milivolts
 */
uint16_t BoardMeasureVdd( void );

/*!
 * \brief Get the current battery level
 *
 * \retval value  battery level ( 0: very low, 254: fully charged )
 */
uint8_t BoardGetBatteryLevel( void );

/*!
 * Returns a pseudo random seed generated using the MCU Unique ID
 *
 * \retval seed Generated pseudo random seed
 */
uint32_t BoardGetRandomSeed( void );

/*!
 * \brief Gets the board 64 bits unique ID
 *
 * \param [IN] id Pointer to an array that will contain the Unique ID
 */
void BoardGetUniqueId( uint8_t *id );

/*!
 * \brief Get the board power source
 *
 * \retval value  power source ( 0: USB_POWER,  1: BATTERY_POWER )
 */
uint8_t GetBoardPowerSource( void );

#endif // __BOARD_H__
