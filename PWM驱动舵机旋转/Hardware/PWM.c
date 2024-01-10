#include "stm32f10x.h"                  // Device header

void PWM_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);    //重映射需开启AFIO时钟
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //Timer3部分重映射  
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;               //复用推挽输出 PA1
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	TIM_InternalClockConfig(TIM3);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;                     //不分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;        //向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 20000 - 1;		// 自动重装值ARR  这里一个周期为20000us即20ms       定时器周期T=ARR*t       即T=(PSC+1) X(ARR+1)/TIMx_CLK   
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;		// 时钟预分频数PSC 这里为1us记一次数     时钟源周期 t=1/(72M/PSC )   (72为默认时钟频率单位M)
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;              //定时器一次一中断
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;        //比较输出模式选择，总共有八种
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;       //比较输出极性
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;     //比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0;		//CCR 设置待装入捕获比较寄存器的脉冲值即PWN占比 Duty=CCR/(ARR+1)x100%
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);
	
	TIM_Cmd(TIM3, ENABLE);         
}

void PWM_SetCompare2(uint16_t Compare)
{
	TIM_SetCompare2(TIM3, Compare);
}
