#ifdef ENABLE_SPI
// void init_BU2505FV() {


//   SPI.setMOSI(PB15);  // using pin name PY_n
//   SPI.setSCLK(PB13);  // using pin number PYn
//   SPI.begin();
//   SPI.beginTransaction(spisettings);

//   pinMode(LD_PIN, OUTPUT);
//   digitalWrite(LD_PIN, LOW);
// }

// static void BU2505FV_set_channel(uint16_t channel_n, uint16_t val_n) {

//   uint16_t val_10bit = (val_n & 0x3FF) << 6;
//   uint16_t channel = channel_n << 2;

//   uint16_t message = (val_10bit | channel);

//   SPI.transfer16(message,1);

//   digitalWrite(LD_PIN, HIGH);
//   for (volatile int i = 0; i < 2; i++)
//     ;
//   digitalWrite(LD_PIN, LOW);

// }

#endif