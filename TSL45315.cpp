#include "TSL45315.h"

TSL45315::TSL45315(uint8_t deviceAddr)
{
    m_i2cAddr = deviceAddr;
}

void TSL45315::begin(PowerMode mode, IntMode integration)
{
    //Put integration mode in member var as we need it for data readout
    m_intMode = integration;

    //Set Power mode ----------------------------------
    Wire.begin();
    // Start I2C Transmission
    Wire.beginTransmission(m_i2cAddr);

    // Select control register
    Wire.write(CMD | CONTROL_REGISTER);

    // Set operating mode
    Wire.write(static_cast<uint8_t>(mode));

    // Stop I2C transmission
    Wire.endTransmission();

    //Configure multiplyer -----------------------------
    // Start I2C Transmission
    Wire.beginTransmission(m_i2cAddr);

    // Select configuration register
    Wire.write(CMD | CONFIG_REGISTER);

    // Set integration time and multiplyer
    Wire.write(static_cast<uint8_t>(m_intMode));

    // Stop I2C transmission
    Wire.endTransmission();
}

uint32_t TSL45315::readLux()
{
    // Start I2C Transmission
    Wire.beginTransmission(m_i2cAddr);
    
    // Select data register
    Wire.write(CMD | DATA_LSB_REGISTER);

    // Stop I2C transmission
    Wire.endTransmission();

    uint32_t lux = read16();

    switch(m_intMode)
    {
        case INTEGRATION_400MS:
        return lux;

        case INTEGRATION_200MS:
        return lux * 2; // This is done in accordance with the datasheet

        case INTEGRATION_100MS:
        return lux * 4; // This is done in accordance with the datasheet
    }
}

uint16_t TSL45315::read16()
{
    unsigned int lsb = 0, msb = 0;
  
    // Request 2 bytes of data
    Wire.requestFrom(m_i2cAddr, static_cast<uint8_t>(2));

    // Read 2 bytes of data
    if (Wire.available() == 2)
    {
      lsb = Wire.read();
      msb = Wire.read();
    }

    return ((static_cast<uint16_t>(msb) << 8) | static_cast<uint16_t>(lsb));
}