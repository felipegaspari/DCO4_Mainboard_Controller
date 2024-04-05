#ifndef __TIMERS_H__
#define __TIMERS_H__

#define TIM1_CH1_PIN PE_9 //ADSR
#define TIM1_CH2_PIN PE_11 //ADSR
#define TIM1_CH3_PIN PE_13
#define TIM1_CH4_PIN PE_14

#define TIM2_CH1_PIN PA_15
#define TIM2_CH2_PIN PB_3
#define TIM2_CH3_PIN PB_10 
#define TIM2_CH4_PIN PB_11 

#define TIM3_CH1_PIN PB_4
#define TIM3_CH2_PIN PB_5
#define TIM3_CH3_PIN PB_0_ALT1
#define TIM3_CH4_PIN PB_1_ALT1

#define TIM4_CH1_PIN PD_12 
#define TIM4_CH2_PIN PD_13 
#define TIM4_CH3_PIN PD_14 
#define TIM4_CH4_PIN PD_15 

#define TIM5_CH1_PIN PA_0_ALT1
#define TIM5_CH2_PIN PA_1_ALT1
#define TIM5_CH3_PIN PA_2_ALT1
#define TIM5_CH4_PIN PA_3_ALT1

#define TIM8_CH1_PIN PC_6_ALT1
#define TIM8_CH2_PIN PC_7_ALT1
#define TIM8_CH3_PIN PC_8_ALT1
#define TIM8_CH4_PIN PC_9_ALT1

#define TIM12_CH1_PIN PB_14_ALT2
#define TIM12_CH2_PIN PB_15_ALT2

#define TIM13_CH1_PIN PA6_ALT1

#define TIM15_CH1_PIN PE_5
#define TIM15_CH2_PIN PE_6

HardwareTimer *htim1 = new HardwareTimer(TIM1);
HardwareTimer *htim2 = new HardwareTimer(TIM2);
HardwareTimer *htim3 = new HardwareTimer(TIM3);
HardwareTimer *htim4 = new HardwareTimer(TIM4);
HardwareTimer *htim5 = new HardwareTimer(TIM5);
HardwareTimer *htim8 = new HardwareTimer(TIM8);

HardwareTimer *htim12 = new HardwareTimer(TIM12);
HardwareTimer *htim13 = new HardwareTimer(TIM13);
HardwareTimer *htim15 = new HardwareTimer(TIM15);

#endif
/*
//PWM sin opamp
PB_4    TIM3_CH1
PE_6    TIM15_CH2
PA_0    TIM5_CH1
PA_2    TIM5_CH3

PA_6    TIM13_CH1
PB_0    TIM3_CH3
PE_14   TIM1_CH4
PB_10   TIM2_CH3

//PWM con opamp - 4
PC_6 	  TIM8_CH1
PD_14 	TIM4_CH3
PD_12 	TIM4_CH1
PB_14	  TIM12_CH1

//PWM con opamp - a mix_board
PE_5 	  TIM15_CH1
PA_1	  TIM5_CH2
PA_3	  TIM5_CH2
PB_1 	  TIM3_CH4

PE_9	  TIM1_CH1
PE_11	  TIM1_CH2
PE_13	  TIM1_CH3
PB_11	  TIM2_CH4

// PWM SUELTOS
PC_7 	  TIM8_CH2
PD_15 	TIM4_CH4
PD_13	  TIM4_CH2
PB_15	  TIM12_CH2
*/