void init_timers() {
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
  htim2->setMode(2, TIMER_OUTPUT_COMPARE_PWM1, PB_3);
  htim2->setMode(3, TIMER_OUTPUT_COMPARE_PWM1, PB_10);

  htim2->pause();
  htim2->setPreloadEnable(true);
  htim2->setPrescaleFactor(1);                      // Due to setOverflow with MICROSEC_FORMAT, prescaler will be computed automatically based on timer input clock
  htim2->setOverflow(ADSR_1_DACSIZE, TICK_FORMAT);  // 100000 microseconds = 100 milliseconds

  htim2->setCaptureCompare(2, 1, TICK_COMPARE_FORMAT);
  htim2->setCaptureCompare(3, 1, TICK_COMPARE_FORMAT);


  htim2->resume();

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  htim3->setMode(1, TIMER_OUTPUT_COMPARE_PWM1, PB_4);
  htim3->setMode(2, TIMER_OUTPUT_COMPARE_PWM1, PB_5);

  htim3->pause();
  htim3->setPreloadEnable(true);
  htim3->setPrescaleFactor(1);                      // Due to setOverflow with MICROSEC_FORMAT, prescaler will be computed automatically based on timer input clock
  htim3->setOverflow(ADSR_1_DACSIZE, TICK_FORMAT);  // 100000 microseconds = 100 milliseconds
  htim3->setCaptureCompare(1, 1, TICK_COMPARE_FORMAT);
  htim3->setCaptureCompare(2, 1, TICK_COMPARE_FORMAT);

  htim3->resume();

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  htim4->setMode(1, TIMER_OUTPUT_COMPARE_PWM1, PB_6);
  htim4->setMode(2, TIMER_OUTPUT_COMPARE_PWM1, PB_7);
  htim4->setMode(3, TIMER_OUTPUT_COMPARE_PWM1, PB_8);
  htim4->setMode(4, TIMER_OUTPUT_COMPARE_PWM1, PB_9);

  htim4->pause();
  htim4->setPreloadEnable(true);
  htim4->setPrescaleFactor(1);                      // Due to setOverflow with MICROSEC_FORMAT, prescaler will be computed automatically based on timer input clock
  htim4->setOverflow(ADSR_1_DACSIZE, TICK_FORMAT);  // 100000 microseconds = 100 milliseconds

  htim4->setCaptureCompare(1, 1, TICK_COMPARE_FORMAT);
  htim4->setCaptureCompare(2, 1, TICK_COMPARE_FORMAT);
  htim4->setCaptureCompare(3, 1, TICK_COMPARE_FORMAT);
  htim4->setCaptureCompare(4, 1, TICK_COMPARE_FORMAT);

  htim4->resume();

  Serial.begin(2000000);

  LFO1_class.setWaveForm(2);    // initialize waveform
  LFO1_class.setAmpl(4096);     // set amplitude to maximum
  LFO1_class.setAmplOffset(0);  // no offset to the amplitude
  LFO1_class.setMode(0);        // set sync mode to mode0 -> no sync to BPM
  LFO1_class.setMode0Freq(0.3);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
