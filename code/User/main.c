#include "debug.h"

#define LED_Pin GPIO_Pin_7
#define LED_GPIO_Port GPIOC
//**************
#define OUT_A GPIO_Pin_0
#define OUT_A_Port GPIOD
//***************
#define OUT_B GPIO_Pin_2
#define OUT_B_Port GPIOD
//***************
#define OUT_C GPIO_Pin_3
#define OUT_C_Port GPIOD
//***************
#define OUT_D GPIO_Pin_4
#define OUT_D_Port GPIOD
//**************
#define IN_A GPIO_Pin_0
#define IN_A_Port GPIOC
//***************
#define IN_B GPIO_Pin_1
#define IN_B_Port GPIOC
//***************
#define IN_C GPIO_Pin_2
#define IN_C_Port GPIOC
//***************
#define IN_D GPIO_Pin_3
#define IN_D_Port GPIOC
//***************

int band = 0;


vu8 delay_ms = 0;

void USARTx_CFG(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure = {0};
    USART_InitTypeDef USART_InitStructure = {0};
    NVIC_InitTypeDef  NVIC_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_USART1, ENABLE);

    /* USART1 TX-->D.5   RX-->D.6 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

    USART_Init(USART1, &USART_InitStructure);
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);;

    USART_Cmd(USART1, ENABLE);
}

void Timer2_INIT(u16 arr, u16 psc)
{
    TIM_TimeBaseInitTypeDef TIMBase_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    TIMBase_InitStruct.TIM_Period = arr;
    TIMBase_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIMBase_InitStruct.TIM_Prescaler = psc;
    TIMBase_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM2, &TIMBase_InitStruct);

    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

    NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 5;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 5;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);
    TIM_Cmd(TIM2, ENABLE);
}

void GPIO_INIT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

    GPIO_InitStructure.GPIO_Pin = LED_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED_GPIO_Port, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = OUT_A;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(OUT_A_Port, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = OUT_B;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(OUT_B_Port, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = OUT_C;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(OUT_C_Port, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = OUT_D;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(OUT_D_Port, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = IN_A;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(IN_A_Port, &GPIO_InitStructure);
    GPIO_WriteBit(IN_A_Port, IN_A, Bit_SET);

    GPIO_InitStructure.GPIO_Pin = IN_B;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(IN_B_Port, &GPIO_InitStructure);
    GPIO_WriteBit(IN_B_Port, IN_B, Bit_SET);

    GPIO_InitStructure.GPIO_Pin = IN_C;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(IN_C_Port, &GPIO_InitStructure);
    GPIO_WriteBit(IN_C_Port, IN_C, Bit_SET);

    GPIO_InitStructure.GPIO_Pin = IN_D;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(IN_D_Port, &GPIO_InitStructure);
    GPIO_WriteBit(IN_D_Port, IN_D, Bit_SET);

    Delay_Ms(200);

    GPIO_WriteBit(OUT_A_Port, OUT_A, Bit_SET);
    GPIO_WriteBit(OUT_B_Port, OUT_B, Bit_SET);
    GPIO_WriteBit(OUT_C_Port, OUT_C, Bit_SET);
    GPIO_WriteBit(OUT_D_Port, OUT_D, Bit_SET);

}

void SendMode(){
	Delay_Ms(1);
	USART_SendData(USART1, 0xFE);
	Delay_Ms(1);
	USART_SendData(USART1, 0xFE);
	Delay_Ms(1);
	USART_SendData(USART1, 0x00);
	Delay_Ms(1);
	USART_SendData(USART1, 0x94);
	Delay_Ms(1);
	USART_SendData(USART1, 0x04);
	Delay_Ms(1);
	USART_SendData(USART1, 0x01);
	Delay_Ms(1);
	USART_SendData(USART1, 0x01);
	Delay_Ms(1);
	USART_SendData(USART1, 0xFD);
	Delay_Ms(1);
}

void SendBandData (int band){
	switch (band){
	case 160: {
		USART_SendData(USART1, 0xFE);
		Delay_Ms(1);
		USART_SendData(USART1, 0xFE);
		Delay_Ms(1);
		USART_SendData(USART1, 0x00);
		Delay_Ms(1);
		USART_SendData(USART1, 0x94);
		Delay_Ms(1);
		USART_SendData(USART1, 0x00);
		Delay_Ms(1);
		USART_SendData(USART1, 0x00);
		Delay_Ms(1);
		USART_SendData(USART1, 0x00);
		Delay_Ms(1);
		USART_SendData(USART1, 0x84);
		Delay_Ms(1);
		USART_SendData(USART1, 0x01);
		Delay_Ms(1);
		USART_SendData(USART1, 0x00);
		Delay_Ms(1);
		USART_SendData(USART1, 0xFD);
		SendMode();
		break;
	}
	case 80: {
		USART_SendData(USART1, 0xFE);
		Delay_Ms(1);
		USART_SendData(USART1, 0xFE);
		Delay_Ms(1);
		USART_SendData(USART1, 0x00);
		Delay_Ms(1);
		USART_SendData(USART1, 0x94);
		Delay_Ms(1);
		USART_SendData(USART1, 0x00);
		Delay_Ms(1);
		USART_SendData(USART1, 0x00);
		Delay_Ms(1);
		USART_SendData(USART1, 0x30);
		Delay_Ms(1);
		USART_SendData(USART1, 0x57);
		Delay_Ms(1);
		USART_SendData(USART1, 0x03);
		Delay_Ms(1);
		USART_SendData(USART1, 0x00);
		Delay_Ms(1);
		USART_SendData(USART1, 0xFD);
		SendMode();
		break;
	}
	case 60: {
		USART_SendData(USART1, 0xFE);
		Delay_Ms(1);
		USART_SendData(USART1, 0xFE);
		Delay_Ms(1);
		USART_SendData(USART1, 0x00);
		Delay_Ms(1);
		USART_SendData(USART1, 0x94);
		Delay_Ms(1);
		USART_SendData(USART1, 0x00);
		Delay_Ms(1);
		USART_SendData(USART1, 0x00);
		Delay_Ms(1);
		USART_SendData(USART1, 0x00);
		Delay_Ms(1);
		USART_SendData(USART1, 0x36);
		Delay_Ms(1);
		USART_SendData(USART1, 0x05);
		Delay_Ms(1);
		USART_SendData(USART1, 0x00);
		Delay_Ms(1);
		USART_SendData(USART1, 0xFD);
		SendMode();
		break;
	}
	case 40: {
		USART_SendData(USART1, 0xFE);
		Delay_Ms(1);
		USART_SendData(USART1, 0xFE);
		Delay_Ms(1);
		USART_SendData(USART1, 0x00);
		Delay_Ms(1);
		USART_SendData(USART1, 0x94);
		Delay_Ms(1);
		USART_SendData(USART1, 0x00);
		Delay_Ms(1);
		USART_SendData(USART1, 0x00);
		Delay_Ms(1);
		USART_SendData(USART1, 0x40);
		Delay_Ms(1);
		USART_SendData(USART1, 0x07);
		Delay_Ms(1);
		USART_SendData(USART1, 0x07);
		Delay_Ms(1);
		USART_SendData(USART1, 0x00);
		Delay_Ms(1);
		USART_SendData(USART1, 0xFD);
		SendMode();
		break;
	}
	case 30: {
		USART_SendData(USART1, 0xFE);
		Delay_Ms(1);
		USART_SendData(USART1, 0xFE);
		Delay_Ms(1);
		USART_SendData(USART1, 0x00);
		Delay_Ms(1);
		USART_SendData(USART1, 0x94);
		Delay_Ms(1);
		USART_SendData(USART1, 0x00);
		Delay_Ms(1);
		USART_SendData(USART1, 0x00);
		Delay_Ms(1);
		USART_SendData(USART1, 0x60);
		Delay_Ms(1);
		USART_SendData(USART1, 0x13);
		Delay_Ms(1);
		USART_SendData(USART1, 0x10);
		Delay_Ms(1);
		USART_SendData(USART1, 0x00);
		Delay_Ms(1);
		USART_SendData(USART1, 0xFD);
		SendMode();
		break;
	}
	case 20: {
		USART_SendData(USART1, 0xFE);
		Delay_Ms(1);
		USART_SendData(USART1, 0xFE);
		Delay_Ms(1);
		USART_SendData(USART1, 0x00);
		Delay_Ms(1);
		USART_SendData(USART1, 0x94);
		Delay_Ms(1);
		USART_SendData(USART1, 0x00);
		Delay_Ms(1);
		USART_SendData(USART1, 0x00);
		Delay_Ms(1);
		USART_SendData(USART1, 0x40);
		Delay_Ms(1);
		USART_SendData(USART1, 0x07);
		Delay_Ms(1);
		USART_SendData(USART1, 0x14);
		Delay_Ms(1);
		USART_SendData(USART1, 0x00);
		Delay_Ms(1);
		USART_SendData(USART1, 0xFD);
		SendMode();
		break;
	}
	case 17: {
		USART_SendData(USART1, 0xFE);
		Delay_Ms(1);
		USART_SendData(USART1, 0xFE);
		Delay_Ms(1);
		USART_SendData(USART1, 0x00);
		Delay_Ms(1);
		USART_SendData(USART1, 0x94);
		Delay_Ms(1);
		USART_SendData(USART1, 0x00);
		Delay_Ms(1);
		USART_SendData(USART1, 0x00);
		Delay_Ms(1);
		USART_SendData(USART1, 0x00);
		Delay_Ms(1);
		USART_SendData(USART1, 0x10);
		Delay_Ms(1);
		USART_SendData(USART1, 0x18);
		Delay_Ms(1);
		USART_SendData(USART1, 0x00);
		Delay_Ms(1);
		USART_SendData(USART1, 0xFD);
		SendMode();
		break;
	}
	case 15: {
		USART_SendData(USART1, 0xFE);
		Delay_Ms(1);
		USART_SendData(USART1, 0xFE);
		Delay_Ms(1);
		USART_SendData(USART1, 0x00);
		Delay_Ms(1);
		USART_SendData(USART1, 0x94);
		Delay_Ms(1);
		USART_SendData(USART1, 0x00);
		Delay_Ms(1);
		USART_SendData(USART1, 0x00);
		Delay_Ms(1);
		USART_SendData(USART1, 0x40);
		Delay_Ms(1);
		USART_SendData(USART1, 0x07);
		Delay_Ms(1);
		USART_SendData(USART1, 0x21);
		Delay_Ms(1);
		USART_SendData(USART1, 0x00);
		Delay_Ms(1);
		USART_SendData(USART1, 0xFD);
		SendMode();
		break;
	}
	case 12: {
		USART_SendData(USART1, 0xFE);
		Delay_Ms(1);
		USART_SendData(USART1, 0xFE);
		Delay_Ms(1);
		USART_SendData(USART1, 0x00);
		Delay_Ms(1);
		USART_SendData(USART1, 0x94);
		Delay_Ms(1);
		USART_SendData(USART1, 0x00);
		Delay_Ms(1);
		USART_SendData(USART1, 0x00);
		Delay_Ms(1);
		USART_SendData(USART1, 0x50);
		Delay_Ms(1);
		USART_SendData(USART1, 0x91);
		Delay_Ms(1);
		USART_SendData(USART1, 0x24);
		Delay_Ms(1);
		USART_SendData(USART1, 0x00);
		Delay_Ms(1);
		USART_SendData(USART1, 0xFD);
		SendMode();
		break;
	}
	case 10: {
		USART_SendData(USART1, 0xFE);
		Delay_Ms(1);
		USART_SendData(USART1, 0xFE);
		Delay_Ms(1);
		USART_SendData(USART1, 0x00);
		Delay_Ms(1);
		USART_SendData(USART1, 0x94);
		Delay_Ms(1);
		USART_SendData(USART1, 0x00);
		Delay_Ms(1);
		USART_SendData(USART1, 0x00);
		Delay_Ms(1);
		USART_SendData(USART1, 0x40);
		Delay_Ms(1);
		USART_SendData(USART1, 0x07);
		Delay_Ms(1);
		USART_SendData(USART1, 0x28);
		Delay_Ms(1);
		USART_SendData(USART1, 0x00);
		Delay_Ms(1);
		USART_SendData(USART1, 0xFD);
		SendMode();
		break;
	}
	case 6: {
		USART_SendData(USART1, 0xFE);
		Delay_Ms(1);
		USART_SendData(USART1, 0xFE);
		Delay_Ms(1);
		USART_SendData(USART1, 0x00);
		Delay_Ms(1);
		USART_SendData(USART1, 0x94);
		Delay_Ms(1);
		USART_SendData(USART1, 0x00);
		Delay_Ms(1);
		USART_SendData(USART1, 0x00);
		Delay_Ms(1);
		USART_SendData(USART1, 0x80);
		Delay_Ms(1);
		USART_SendData(USART1, 0x31);
		Delay_Ms(1);
		USART_SendData(USART1, 0x50);
		Delay_Ms(1);
		USART_SendData(USART1, 0x00);
		Delay_Ms(1);
		USART_SendData(USART1, 0xFD);
		SendMode();
		break;
	}
	case 0: printf ("No data\n"); break;
	}
}


int ReadBand (){
	int a = 0;
	int b = 0;
	int c = 0;
	int d = 0;
	a = GPIO_ReadInputDataBit(IN_A_Port, IN_A);
	b = GPIO_ReadInputDataBit(IN_B_Port, IN_B);
	c = GPIO_ReadInputDataBit(IN_C_Port, IN_C);
	d = GPIO_ReadInputDataBit(IN_D_Port, IN_D);
	if (a && !b && !c && !d) return 160;
	if (!a && b && !c && !d) return 80;
	if (!a && !b && !c && !d) return 60;
	if (a &&  b && !c && !d) return 40;
	if (!a && !b && c && !d) return 30;
	if (a && !b && c && !d) return 20;
	if (!a && b && c && !d) return 17;
	if (a && b && c && !d) return 15;
	if (!a && !b && !c && d) return 12;
	if (a && !b && !c && d) return 10;
	if (!a && b && !c && d) return 6;
	if (a && b && c && d) return 0;

}

void SetOuts (int band){
	if (band == 160){
		GPIO_WriteBit(OUT_A_Port, OUT_A, Bit_SET);
	    GPIO_WriteBit(OUT_B_Port, OUT_B, Bit_RESET);
		GPIO_WriteBit(OUT_C_Port, OUT_C, Bit_RESET);
		GPIO_WriteBit(OUT_D_Port, OUT_D, Bit_RESET);
	}
	if (band == 80){
		GPIO_WriteBit(OUT_A_Port, OUT_A, Bit_RESET);
	    GPIO_WriteBit(OUT_B_Port, OUT_B, Bit_SET);
		GPIO_WriteBit(OUT_C_Port, OUT_C, Bit_RESET);
		GPIO_WriteBit(OUT_D_Port, OUT_D, Bit_RESET);
	}
	if (band == 60){
		GPIO_WriteBit(OUT_A_Port, OUT_A, Bit_RESET);
	    GPIO_WriteBit(OUT_B_Port, OUT_B, Bit_RESET);
		GPIO_WriteBit(OUT_C_Port, OUT_C, Bit_RESET);
		GPIO_WriteBit(OUT_D_Port, OUT_D, Bit_RESET);
	}
	if (band == 40){
		GPIO_WriteBit(OUT_A_Port, OUT_A, Bit_SET);
	    GPIO_WriteBit(OUT_B_Port, OUT_B, Bit_SET);
		GPIO_WriteBit(OUT_C_Port, OUT_C, Bit_RESET);
		GPIO_WriteBit(OUT_D_Port, OUT_D, Bit_RESET);
	}
	if (band == 30){
		GPIO_WriteBit(OUT_A_Port, OUT_A, Bit_RESET);
	    GPIO_WriteBit(OUT_B_Port, OUT_B, Bit_RESET);
		GPIO_WriteBit(OUT_C_Port, OUT_C, Bit_SET);
		GPIO_WriteBit(OUT_D_Port, OUT_D, Bit_RESET);
	}
	if (band == 20){
		GPIO_WriteBit(OUT_A_Port, OUT_A, Bit_SET);
	    GPIO_WriteBit(OUT_B_Port, OUT_B, Bit_RESET);
		GPIO_WriteBit(OUT_C_Port, OUT_C, Bit_SET);
		GPIO_WriteBit(OUT_D_Port, OUT_D, Bit_RESET);
	}
	if (band == 17){
		GPIO_WriteBit(OUT_A_Port, OUT_A, Bit_RESET);
	    GPIO_WriteBit(OUT_B_Port, OUT_B, Bit_SET);
		GPIO_WriteBit(OUT_C_Port, OUT_C, Bit_SET);
		GPIO_WriteBit(OUT_D_Port, OUT_D, Bit_RESET);
	}
	if (band == 15){
		GPIO_WriteBit(OUT_A_Port, OUT_A, Bit_SET);
	    GPIO_WriteBit(OUT_B_Port, OUT_B, Bit_SET);
		GPIO_WriteBit(OUT_C_Port, OUT_C, Bit_SET);
		GPIO_WriteBit(OUT_D_Port, OUT_D, Bit_RESET);
	}
	if (band == 12){
		GPIO_WriteBit(OUT_A_Port, OUT_A, Bit_RESET);
	    GPIO_WriteBit(OUT_B_Port, OUT_B, Bit_RESET);
		GPIO_WriteBit(OUT_C_Port, OUT_C, Bit_RESET);
		GPIO_WriteBit(OUT_D_Port, OUT_D, Bit_SET);
	}
	if (band == 10){
		GPIO_WriteBit(OUT_A_Port, OUT_A, Bit_SET);
	    GPIO_WriteBit(OUT_B_Port, OUT_B, Bit_RESET);
		GPIO_WriteBit(OUT_C_Port, OUT_C, Bit_RESET);
		GPIO_WriteBit(OUT_D_Port, OUT_D, Bit_SET);
	}
	if (band == 6){
		GPIO_WriteBit(OUT_A_Port, OUT_A, Bit_RESET);
	    GPIO_WriteBit(OUT_B_Port, OUT_B, Bit_SET);
		GPIO_WriteBit(OUT_C_Port, OUT_C, Bit_RESET);
		GPIO_WriteBit(OUT_D_Port, OUT_D, Bit_SET);
	}

	if (band == 0){
		GPIO_WriteBit(OUT_A_Port, OUT_A, Bit_SET);
	    GPIO_WriteBit(OUT_B_Port, OUT_B, Bit_SET);
		GPIO_WriteBit(OUT_C_Port, OUT_C, Bit_SET);
		GPIO_WriteBit(OUT_D_Port, OUT_D, Bit_SET);
	}
}

int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    SystemCoreClockUpdate();
    Delay_Init();
    GPIO_INIT();
    USARTx_CFG();
    Timer2_INIT(999, 23999);
    while(1)
    {
    	band = ReadBand();
    	SendBandData(band);
    	SetOuts(band);
    	Delay_Ms(1000);
    }
}
