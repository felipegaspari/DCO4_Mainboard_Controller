void init_timers() {
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  htim1->setMode(1, TIMER_OUTPUT_COMPARE_PWM1, TIM1_CH1_PIN);
  htim1->setMode(2, TIMER_OUTPUT_COMPARE_PWM1, TIM1_CH2_PIN);
  htim1->setMode(3, TIMER_OUTPUT_COMPARE_PWM1, TIM1_CH3_PIN);
  htim1->setMode(4, TIMER_OUTPUT_COMPARE_PWM1, TIM1_CH4_PIN);

  htim1->pause();
  htim1->setPreloadEnable(true);
  htim1->setPrescaleFactor(1);                      // Due to setOverflow with MICROSEC_FORMAT, prescaler will be computed automatically based on timer input clock
  htim1->setOverflow(ADSR_1_DACSIZE, TICK_FORMAT);  // 100000 microseconds = 100 milliseconds
  htim1->setCaptureCompare(1, 1, TICK_COMPARE_FORMAT);
  htim1->setCaptureCompare(2, 1, TICK_COMPARE_FORMAT);
  htim1->setCaptureCompare(3, 1, TICK_COMPARE_FORMAT);
  htim1->setCaptureCompare(4, 1, TICK_COMPARE_FORMAT);
  htim1->resume();

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ENABLE_SPI
  htim2->setMode(1, TIMER_OUTPUT_COMPARE_PWM1, TIM2_CH1_PIN);
  htim2->setMode(2, TIMER_OUTPUT_COMPARE_PWM1, TIM2_CH2_PIN);
#endif
  htim2->setMode(3, TIMER_OUTPUT_COMPARE_PWM1, TIM2_CH3_PIN);
  htim2->setMode(4, TIMER_OUTPUT_COMPARE_PWM1, TIM2_CH4_PIN);

  htim2->pause();
  htim2->setPreloadEnable(true);
  htim2->setPrescaleFactor(1);                      // Due to setOverflow with MICROSEC_FORMAT, prescaler will be computed automatically based on timer input clock
  htim2->setOverflow(ADSR_1_DACSIZE, TICK_FORMAT);  // 100000 microseconds = 100 milliseconds
#ifndef ENABLE_SPI
  htim2->setCaptureCompare(1, 1, TICK_COMPARE_FORMAT);
  htim2->setCaptureCompare(2, 1, TICK_COMPARE_FORMAT);
#endif
  htim2->setCaptureCompare(3, 1, TICK_COMPARE_FORMAT);
  htim2->setCaptureCompare(4, 1, TICK_COMPARE_FORMAT);
  htim2->resume();

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  htim3->setMode(1, TIMER_OUTPUT_COMPARE_PWM1, TIM3_CH1_PIN);
#ifndef ENABLE_SPI
  htim3->setMode(2, TIMER_OUTPUT_COMPARE_PWM1, TIM3_CH2_PIN);
#endif
  htim3->setMode(3, TIMER_OUTPUT_COMPARE_PWM1, TIM3_CH3_PIN);
  htim3->setMode(4, TIMER_OUTPUT_COMPARE_PWM1, TIM3_CH4_PIN);

  htim3->pause();
  htim3->setPreloadEnable(true);
  htim3->setPrescaleFactor(1);                      // Due to setOverflow with MICROSEC_FORMAT, prescaler will be computed automatically based on timer input clock
  htim3->setOverflow(ADSR_1_DACSIZE, TICK_FORMAT);  // 100000 microseconds = 100 milliseconds
  htim3->setCaptureCompare(1, 1, TICK_COMPARE_FORMAT);
#ifndef ENABLE_SPI
  htim3->setCaptureCompare(2, 1, TICK_COMPARE_FORMAT);
#endif
  htim3->setCaptureCompare(3, 1, TICK_COMPARE_FORMAT);
  htim3->setCaptureCompare(4, 1, TICK_COMPARE_FORMAT);
  htim3->resume();

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  htim4->setMode(1, TIMER_OUTPUT_COMPARE_PWM1, TIM4_CH1_PIN);
  htim4->setMode(2, TIMER_OUTPUT_COMPARE_PWM1, TIM4_CH2_PIN);
  htim4->setMode(3, TIMER_OUTPUT_COMPARE_PWM1, TIM4_CH3_PIN);
  htim4->setMode(4, TIMER_OUTPUT_COMPARE_PWM1, TIM4_CH4_PIN);

  htim4->pause();
  htim4->setPreloadEnable(true);
  htim4->setPrescaleFactor(1);                      // Due to setOverflow with MICROSEC_FORMAT, prescaler will be computed automatically based on timer input clock
  htim4->setOverflow(ADSR_1_DACSIZE, TICK_FORMAT);  // 100000 microseconds = 100 milliseconds
  htim4->setCaptureCompare(1, 1, TICK_COMPARE_FORMAT);
  htim4->setCaptureCompare(2, 1, TICK_COMPARE_FORMAT);
  htim4->setCaptureCompare(3, 1, TICK_COMPARE_FORMAT);
  htim4->setCaptureCompare(4, 1, TICK_COMPARE_FORMAT);
  htim4->resume();

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  htim5->setMode(1, TIMER_OUTPUT_COMPARE_PWM1, TIM5_CH1_PIN);
  htim5->setMode(2, TIMER_OUTPUT_COMPARE_PWM1, TIM5_CH2_PIN);
  htim5->setMode(3, TIMER_OUTPUT_COMPARE_PWM1, TIM5_CH3_PIN);
  htim5->setMode(4, TIMER_OUTPUT_COMPARE_PWM1, TIM5_CH4_PIN);

  htim5->pause();
  htim5->setPreloadEnable(true);
  htim5->setPrescaleFactor(1);                      // Due to setOverflow with MICROSEC_FORMAT, prescaler will be computed automatically based on timer input clock
  htim5->setOverflow(ADSR_1_DACSIZE, TICK_FORMAT);  // 100000 microseconds = 100 milliseconds
  htim5->setCaptureCompare(1, 1, TICK_COMPARE_FORMAT);
  htim5->setCaptureCompare(2, 1, TICK_COMPARE_FORMAT);
  htim5->setCaptureCompare(3, 1, TICK_COMPARE_FORMAT);
  htim5->setCaptureCompare(4, 1, TICK_COMPARE_FORMAT);
  htim5->resume();

  // //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  htim8->setMode(1, TIMER_OUTPUT_COMPARE_PWM1, TIM8_CH1_PIN);
  htim8->setMode(2, TIMER_OUTPUT_COMPARE_PWM1, TIM8_CH2_PIN);
  //htim8->setMode(3, TIMER_OUTPUT_COMPARE_PWM1, TIM8_CH3_PIN);
#ifndef ENABLE_SPI
  htim8->setMode(4, TIMER_OUTPUT_COMPARE_PWM1, TIM8_CH4_PIN);
#endif

  htim8->pause();
  htim8->setPreloadEnable(true);
  htim8->setPrescaleFactor(1);                      // Due to setOverflow with MICROSEC_FORMAT, prescaler will be computed automatically based on timer input clock
  htim8->setOverflow(ADSR_1_DACSIZE, TICK_FORMAT);  // 100000 microseconds = 100 milliseconds
  htim8->setCaptureCompare(1, 1, TICK_COMPARE_FORMAT);
  htim8->setCaptureCompare(2, 1, TICK_COMPARE_FORMAT);
  //htim8->setCaptureCompare(3, 1, TICK_COMPARE_FORMAT);
#ifndef ENABLE_SPI
  htim8->setCaptureCompare(4, 1, TICK_COMPARE_FORMAT);
#endif
  htim8->resume();

  // //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  htim12->setMode(1, TIMER_OUTPUT_COMPARE_PWM1, TIM12_CH1_PIN);
 #ifndef ENABLE_SPI
  htim12->setMode(2, TIMER_OUTPUT_COMPARE_PWM1, TIM12_CH2_PIN);
#endif
  htim12->pause();
  htim12->setPreloadEnable(true);
  htim12->setPrescaleFactor(1);                      // Due to setOverflow with MICROSEC_FORMAT, prescaler will be computed automatically based on timer input clock
  htim12->setOverflow(ADSR_1_DACSIZE, TICK_FORMAT);  // 100000 microseconds = 100 milliseconds
  htim12->setCaptureCompare(1, 1, TICK_COMPARE_FORMAT);
  #ifndef ENABLE_SPI
  htim12->setCaptureCompare(2, 1, TICK_COMPARE_FORMAT);  // TEMPORARY CONFLICT WITH SPI PIN !!
#endif
  htim12->resume();

  // //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  htim13->setMode(1, TIMER_OUTPUT_COMPARE_PWM1, TIM13_CH1_PIN);


  htim13->pause();
  htim13->setPreloadEnable(true);
  htim13->setPrescaleFactor(1);                      // Due to setOverflow with MICROSEC_FORMAT, prescaler will be computed automatically based on timer input clock
  htim13->setOverflow(ADSR_1_DACSIZE, TICK_FORMAT);  // 100000 microseconds = 100 milliseconds
  htim13->setCaptureCompare(1, 1, TICK_COMPARE_FORMAT);

  htim13->resume();

  // //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  htim15->setMode(1, TIMER_OUTPUT_COMPARE_PWM1, TIM15_CH1_PIN);
  htim15->setMode(2, TIMER_OUTPUT_COMPARE_PWM1, TIM15_CH2_PIN);

  htim15->pause();
  htim15->setPreloadEnable(true);
  htim15->setPrescaleFactor(1);                      // Due to setOverflow with MICROSEC_FORMAT, prescaler will be computed automatically based on timer input clock
  htim15->setOverflow(ADSR_1_DACSIZE, TICK_FORMAT);  // 100000 microseconds = 100 milliseconds
  htim15->setCaptureCompare(1, 1, TICK_COMPARE_FORMAT);
  htim15->setCaptureCompare(2, 1, TICK_COMPARE_FORMAT);

  htim15->resume();

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
