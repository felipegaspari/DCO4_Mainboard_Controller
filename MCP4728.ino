//#include <Adafruit_MCP4728.h>
#include "MCP4728.h"
#include <Wire.h>

// Adafruit_MCP4728 mcp;
// Adafruit_MCP4728 mcp2;
// Adafruit_MCP4728 mcp3;

MCP4728 mcp;
MCP4728 mcp2;
MCP4728 mcp3;

void init_MCP4728() {

  Wire.setSDA(PB_9);
  Wire.setSCL(PB_8);
  Wire.setClock(1000000);
  Wire.begin();

  // mcp.begin(0x63);
  // mcp2.begin(0x64);
  // mcp3.begin(0x65);

  mcp.attach(Wire, 255, 0x63);
  mcp2.attach(Wire, 255, 0x64);
  mcp3.attach(Wire, 255, 0x65);

  Wire.setClock(1000000);


  // mcp.selectVref(MCP4728::VREF::VDD, MCP4728::VREF::VDD, MCP4728::VREF::VDD, MCP4728::VREF::VDD);
  // mcp.selectPowerDown(MCP4728::PWR_DOWN::GND_100KOHM, MCP4728::PWR_DOWN::GND_100KOHM, MCP4728::PWR_DOWN::GND_100KOHM, MCP4728::PWR_DOWN::GND_100KOHM);
  // mcp.selectGain(MCP4728::GAIN::X2, MCP4728::GAIN::X2, MCP4728::GAIN::X2, MCP4728::GAIN::X2);

  // mcp2.selectVref(MCP4728::VREF::VDD, MCP4728::VREF::VDD, MCP4728::VREF::VDD, MCP4728::VREF::VDD);
  // mcp2.selectPowerDown(MCP4728::PWR_DOWN::GND_100KOHM, MCP4728::PWR_DOWN::GND_100KOHM, MCP4728::PWR_DOWN::GND_100KOHM, MCP4728::PWR_DOWN::GND_100KOHM);
  // mcp2.selectGain(MCP4728::GAIN::X2, MCP4728::GAIN::X2, MCP4728::GAIN::X2, MCP4728::GAIN::X2);

  // mcp3.selectVref(MCP4728::VREF::VDD, MCP4728::VREF::VDD, MCP4728::VREF::VDD, MCP4728::VREF::VDD);
  // mcp3.selectPowerDown(MCP4728::PWR_DOWN::GND_100KOHM, MCP4728::PWR_DOWN::GND_100KOHM, MCP4728::PWR_DOWN::GND_100KOHM, MCP4728::PWR_DOWN::GND_100KOHM);
  // mcp3.selectGain(MCP4728::GAIN::X2, MCP4728::GAIN::X2, MCP4728::GAIN::X2, MCP4728::GAIN::X2);

  mcp.analogWrite(MCP4728::DAC_CH::A, 4095);
  mcp.analogWrite(MCP4728::DAC_CH::B, 4095);
  mcp.analogWrite(MCP4728::DAC_CH::C, 4095);
  mcp.analogWrite(MCP4728::DAC_CH::D, 4095);

  mcp2.analogWrite(MCP4728::DAC_CH::A, 4095);
  mcp2.analogWrite(MCP4728::DAC_CH::B, 4095);
  mcp2.analogWrite(MCP4728::DAC_CH::C, 4095);
  mcp2.analogWrite(MCP4728::DAC_CH::D, 4095);

  mcp3.analogWrite(MCP4728::DAC_CH::A, 4095);
  mcp3.analogWrite(MCP4728::DAC_CH::B, 4095);
  mcp3.analogWrite(MCP4728::DAC_CH::C, 4095);
  mcp3.analogWrite(MCP4728::DAC_CH::D, 4095);
}