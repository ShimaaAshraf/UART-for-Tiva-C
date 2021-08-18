
#ifndef  _UART_H_
#define  _UART_H_


#include "Bit_Math.h"

// UART0 Rx pin      -->  PA0 
// UART0 Tx pin      -->  PA1
// UART0 Interrput   -->  Interrput 5 




/* UART0 configrations */
#define  UART0_BAUD_RATE     9600     //use UART0 with baud rate = 9600 
#define  UART0_DATA_BITS     8        //use 8 data bits
#define  UART0_PARITY_BIT    0        //don't use parity bit
#define  UART0_STOP_BITS     1        //use 1 stop bit
#define  UART0_RX_STATE      1        //Enable  UART0 reciever
#define  UART0_TX_STATE      1        //Enable  UART0 transmitter
#define  UART0_RX_INTR       1        //Enable  UART0 reciever    interrupt
#define  UART0_TX_INTR       0        //Disable UART0 transmitter interrupt
#define  UART0_RX_FIFO       0        //Disable UART0 reciever    FIFO
#define  UART0_TX_FIFO       0        //Disable UART0 transmitter FIFO
#define  UART0_CLK_DIVSOR    16 
#define  UART0_SYSTEM_CLK    16000000UL   // Assume system clock is 16 MHz 



/* UART0 necessary register defintoins */
#define  UART0_DR      (*(volatile int *)(0x4000C000))    // UART0 data register
#define  UART0_FR      (*(volatile int *)(0x4000C018))    // UART0 flags
#define  UART0_IBRD    (*(volatile int *)(0x4000C024))    // UART0 buad rate divisor integer  part
#define  UART0_FBRD    (*(volatile int *)(0x4000C028))    // UART0 buad rate divisor fraction part
#define  UART0_LCRH    (*(volatile int *)(0x4000C02C))    // UART0 Line Control
#define  UART0_CTL     (*(volatile int *)(0x4000C030))    // UART0 control register
#define  UART0_IM      (*(volatile int *)(0x4000C038))    // UART0 Interrupts Mak register
#define  UART0_RIS     (*(volatile int *)(0x4000C03C))    // UART0 Interrupts Status register
#define  UART0_ICR     (*(volatile int *)(0x4000C044))    // UART0 Interrupts Clear register


/* other register defintoins related to UART0 */
#define  INTR_EN0      (*(volatile int *)(0xE000E100))    // Interrupts 0:32 enable register
#define  RCGCUART      (*(volatile int *)(0x400FE618))    // UART clock control register
#define  RCGCGPIO      (*(volatile int *)(0x400FE608))    // GPIO clock control register
#define  GPIOAAFSEL    (*(volatile int *)(0x40004420))    // GPIOA Alternate Function Select register
#define  GPIOAPCTL     (*(volatile int *)(0x4000452C))    // GPIOA Port Control register

#define  NULL  (void *)0 


/* UART0 necessary functions ptototypes */
void  UART0_Init(void);
void  UART0_TxOneByte(unsigned char data);



#endif
