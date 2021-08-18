
#include "UART0.h"



void  UART0_Init(void)
{	
	SET_BIT(RCGCUART, 0);     // provide clock to UART0
	SET_BIT(RCGCGPIO, 0);     // provide clock to GPIOA As UART0 Tx & Rx pins are PA0 & PA1
	
	
	CLR_BIT(UART0_CTL, 0);    // disable UART0 to write to control register
	
	
	/* configuring baud rate through clock division factor */
	#if UART0_CLK_DIVSOR == 16
		CLR_BIT(UART0_CTL, 5);     // set UART0 clock divisor to be 16
	#elif UART0_CLK_DIVSOR == 8
		SET_BIT(UART0_CTL, 5);     // set UART0 clock divisor to be 8
	#endif
	double clkDivisionFactor = UART0_SYSTEM_CLK / ((double)UART0_CLK_DIVSOR * UART0_BAUD_RATE);  //refer to Eqn in paga 896 in datasheet
	UART0_IBRD = (int)clkDivisionFactor;  //refer to Eqn in paga 896 in datasheet
	UART0_FBRD = (int)(((clkDivisionFactor - (int)clkDivisionFactor)*64.0 + 0.5));  //refer to Eqn in paga 896 in datasheet



	/* configuring number of data bits in UART0 frame */
	#if UART0_DATA_BITS == 8
		SET_BIT(UART0_LCRH, 6);
		SET_BIT(UART0_LCRH, 5);
	#elif UART0_DATA_BITS == 7
		SET_BIT(UART0_LCRH, 6);
		CLR_BIT(UART0_LCRH, 5);
	#elif UART0_DATA_BITS == 6
		CLR_BIT(UART0_LCRH, 6);
		SET_BIT(UART0_LCRH, 5);
	#elif UART0_DATA_BITS == 5
		CLR_BIT(UART0_LCRH, 6);
		CLR_BIT(UART0_LCRH, 5);
	#endif
	
	
	/* configuring number of stop bits in UART0 frame */
	#if UART0_STOP_BITS == 1
		CLR_BIT(UART0_LCRH, 3);   // tramsmit 1 stop bit
	#elif UART0_STOP_BITS == 2
		SET_BIT(UART0_LCRH, 3);   // tramsmit 2 stop bits
	#endif
	
	
	/* configuring parity bit in UART0 frame */
	#if UART0_PARITY_BIT == 1
		SET_BIT(UART0_LCRH, 1);   // tramsmit parity bit
	#elif UART0_PARITY_BIT == 0
		CLR_BIT(UART0_LCRH, 1);   // no parity bit
	#endif
	
	
	/* configuring UART0 FIFOs */
	#if UART0_RX_FIFO == 1 || UART0_TX_FIFO == 1
		SET_BIT(UART0_LCRH, 4);   // Enable  FIFOs
	#elif UART0_RX_FIFO == 0 && UART0_TX_FIFO == 0
		CLR_BIT(UART0_LCRH, 4);   // Disable FIFOs
	#endif
	
	
	
	/* enable/disable UART0 Rx according to config */
	#if UART0_RX_STATE == 1
		SET_BIT(UART0_CTL, 9);     // enable UART0 RX
		SET_BIT(GPIOAAFSEL, 0);    // confg PA0 for alternate function
		SET_BIT(GPIOAPCTL, 0);     // confg PA0 alternate function to be UART0 Rx 
	#elif UART0_RX_STATE == 0
		CLR_BIT(UART0_CTL, 9);     // disable UART0 RX
	#endif
	
	
	/* enable/disable UART0 Tx according to config */
	#if UART0_TX_STATE == 1
		SET_BIT(UART0_CTL, 8);     // enable UART0 TX
		SET_BIT(GPIOAAFSEL, 1);    // confg PA1 for alternate function
		SET_BIT(GPIOAPCTL, 4);     // confg PA0 for UART0 Tx function
	#elif UART0_TX_STATE == 0
		CLR_BIT(UART0_CTL, 8);     // disable UART0 TX
	#endif
	
	
	
	
	/* enable/disable UART0 Rx interrupt according to config */
	#if UART0_RX_INTR == 1
		SET_BIT(UART0_IM, 4);     // enable  UART0 RX Interrupt
	#elif UART0_RX_INTR == 0
		CLR_BIT(UART0_IM, 4);     // disable UART0 RX Interrupt
	#endif
	
	
	/* enable/disable UART0 Tx interrupt according to config */
	#if UART0_TX_INTR == 1
		SET_BIT(UART0_IM, 5);     // enable  UART0 TX Interrupt
	#elif UART0_TX_INTR == 0
		CLR_BIT(UART0_IM, 5);     // disable UART0 RX Interrupt
	#endif
	
	
	#if UART0_RX_INTR == 1 || UART0_TX_INTR == 1 
		SET_BIT(INTR_EN0, 5);   //if any UART0 interrupt is enabled, enable UART0 global Interrupt (IRQ5) for NVIC
	#endif
	
	SET_BIT(UART0_CTL, 0);    // enable UART0
}





void UART0_TxOneByte(unsigned char data)
{
	while( GET_BIT(UART0_FR, 5) == 1 );  // do nothing while UART0 Tx FIFO is full 
	UART0_DR = data;     // send the data
}






void UART0_Handler(void)
{
	if( GET_BIT(UART0_RIS, 4) == 1 )  //if UART0 Rx interrupt is the active interrupt
	{
		SET_BIT(UART0_ICR, 4);    //clear UART0 Rx interrupt
		unsigned char recievedData = ((unsigned char)(UART0_DR & (0xFF)));  //read recieved byte
		
		if( recievedData >= 'a' && recievedData <= 'z' )   //if the recieved byte is a small character
		{
			UART0_TxOneByte(recievedData - 'a' + 'A');    //send its cabital letter
		}
		else
		{
			UART0_TxOneByte(recievedData + 1);    //send its successive character
		}
	}
}
