#include <TSL45315.h>
TSL45315 tsl;

void setup()
{
    Serial.begin(115200);
}

void loop()
{
    Serial.print("Lux: ");
    tsl.begin(PowerMode::SINGLE_CYCLE,IntMode::INTEGRATION_100MS);
    delay(500);
    Serial.println(tsl.readLux());
}
