Basic usage
-----------

Default device address for this library is ```0x39``` but can be changed in the ctor.

### Continuous operation
This mode can be used if you want to read the ambient light value in a loop and don't have any power consumption limits. This is the default mode.
```
#include <TSL45315.h>
TSL45315 tsl;

void setup()
{
    tsl.begin();
}

void loop()
{
    uint32_t lux = tsl.readLux();
}
```

### Discrete operation
Use this mode if you need to save power.
```
#include <TSL45315.h>
TSL45315 tsl;

void setup()
{
}

void loop()
{
    tsl.begin(PowerMode::SINGLE_CYCLE);
    delay($AT_LEAST_YOUR_INTEGRATION_TIME$);
    uint32_t lux = tsl.readLux();
}
```