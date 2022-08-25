#include <Arduino.h>
#include <unity.h>
#include <StreamAverage.hpp>

void setup()
{
    Serial.begin(115200);
    UNITY_BEGIN();
    RUN_TEST([]{
        StreamAverage<double> average;
        average.add(1.0);
        average.add(2.0);
        TEST_ASSERT(true);
    });
    UNITY_END();
}

void loop()
{

}