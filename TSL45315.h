#include "Wire.h"

enum PowerMode
{
    POWER_DOWN = 0x00,
    SINGLE_CYCLE = 0x02,
    NORMAL_OPERATION  = 0x03
};

enum IntMode
{
    INTEGRATION_400MS = 0x00,
    INTEGRATION_200MS = 0x01,
    INTEGRATION_100MS = 0x02
};

class TSL45315
{
public:
    /**
        Create a new TSL object.
        @param deviceAddr The address for your TSL device.
    */
    TSL45315(uint8_t deviceAddr = 0x29);

    /**
        Set the operating mode for the device. This can also be used to reset the deice during operation.
        @param mode The operating mode, see enum PowerMode for valid options.
        @param integration The integrating time, see enum IntMode for valid options.
    */
    void begin(PowerMode mode = NORMAL_OPERATION, IntMode integration = INTEGRATION_400MS);
    
    /**
        Reads the current ambient light value from the sensor. Readings are in Lux.
        @return The current ambient light value in Lux.
    */
    uint32_t readLux();
    
private:
    uint16_t read16();

    uint8_t m_i2cAddr = 0;
    IntMode m_intMode = INTEGRATION_400MS;

    static const uint8_t CMD = 0x80;
    static const uint8_t CONTROL_REGISTER = 0x00;
    static const uint8_t CONFIG_REGISTER = 0x01;
    static const uint8_t DATA_LSB_REGISTER = 0x04;
    static const uint8_t DATA_MSG_REGISTER = 0x05;
};