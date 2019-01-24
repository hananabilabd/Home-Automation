#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "delay1.h"

void USART2_Init(void);
void USART2_PutChar(char c);
void USART2_PutString(char *s);
uint16_t USART2_GetChar(void);
// Buffer for store received chars
#define BUF_SIZE	16
char buf[BUF_SIZE];
int i = 0;

void delay(unsigned int nCount);
GPIO_InitTypeDef GPIO_InitStruct;
// Tx = A2   , Rx A3  //UART
int main(void)
{
	// Enable clock for GPIOA
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	// Configure PA0 as push-pull output
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	DelayInit();
	// Initialize USART
	USART2_Init();
	
	while (1)
	{
		// Read received char
		char c = USART2_GetChar();
		
		if (c == 0){
			GPIO_ResetBits(GPIOA, GPIO_Pin_0);
		delay(1000);
		
		}
		else if (c==1){
			// Set bit will turn off LED (because the logic is interved)
		GPIO_SetBits(GPIOA, GPIO_Pin_0);
		delay(1000);
		}
			
	
	}
}

void USART2_Init()
{
	// Initialization struct
	USART_InitTypeDef USART_InitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
	
	// Step 1: USART2 initialization
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	USART_InitStruct.USART_BaudRate = 9600;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART2, &USART_InitStruct);
	USART_Cmd(USART2, ENABLE);
	
	// Step 2: GPIO initialization for Tx and Rx pin
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	// Tx pin initialization as push-pull alternate function
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	// Rx pin initialization as input floating
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void USART2_PutChar(char c)
{
	// Wait until transmit data register is empty
	while (!USART_GetFlagStatus(USART2, USART_FLAG_TXE));
	// Send a char using USART2
	USART_SendData(USART2, c);
}

void USART2_PutString(char *s)
{
	// Send a string
	while (*s)
	{
		USART2_PutChar(*s++);
	}
}

uint16_t USART2_GetChar()
{
	// Wait until data is received
	while (!USART_GetFlagStatus(USART2, USART_FLAG_RXNE));
	// Read received char
	return USART_ReceiveData(USART2);
}
void delay(unsigned int nCount)
{
	unsigned int i, j;
	
	for (i = 0; i < nCount; i++)
		for (j = 0; j < 0x2AFF; j++);
}
