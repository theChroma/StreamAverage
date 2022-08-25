#include <unity.h>
#include <StreamAverage.hpp>

void setUp(void) {}
void tearDown(void) {}

int main(int argc, char** argv)
{
    UNITY_BEGIN();
    RUN_TEST([]{
        StreamAverage<double> average;
        average.add(1.0);
        average.add(2.0);
        TEST_ASSERT(1.5 == average);
    });
    UNITY_END();

    return 0;
}