#include <Arduino.h>
#include <unity.h>
#include <StreamAverage.hpp>

template <typename T>
T generateRandom()
{
    return random(-500, 100) / 1.39;
}

template <typename T, size_t arraySize>
void testAdd()
{
    T testValues[arraySize];

    Serial.println("Test Values:");
    for(T value : testValues)
    {
        value = random(-1000, 1000);
        Serial.println(value);
    }
    Serial.println();

    StreamAverage<T> average;
    TEST_ASSERT(0 == average);
        
    for(size_t i = 0; i < arraySize; i++)
    {
        T sum = 0.0f;
        T expectedAverage = 0.0f;
        for(size_t j = 0; j <= i; j++)
        {
            sum += testValues[j];
            expectedAverage = sum / (j + 1);
        }
        average.add(testValues[i]);
        T actualAverage = average.get();

        Serial.printf("Expecting %f == %f\n", expectedAverage, average);
        TEST_ASSERT_EQUAL_FLOAT(expectedAverage, actualAverage);
    }
}

void testRunner()
{
    testAdd<float, 100>();
}

void add()
{
    StreamAverage<float> average;
    TEST_ASSERT_EQUAL_FLOAT(-1.2f, average.add(-1.2f));    
    TEST_ASSERT_EQUAL_FLOAT(0.0f, average.add(1.2f));    
    TEST_ASSERT_EQUAL_FLOAT(1.1f, average.add(3.3f));  
}

void setup()
{
    Serial.begin(115200);
    UNITY_BEGIN();
    RUN_TEST(testRunner);
    UNITY_END();
}

void loop()
{}