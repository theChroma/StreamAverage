// To run test:
// pio test -vv -e pc

#include <gtest/gtest.h>
#include <StreamAverage.h>

#include <vector>
#include <numeric>
#include <utility>

template<typename T> 
struct StreamAverageTest : public testing::Test
{
	StreamAverage<typename T::first_type> unitUnderTest;
	std::vector<typename T::first_type> values;
};

using testTypes = testing::Types
<
	std::pair<int, float>,
	std::pair<double, double>,
	std::pair<float, float>,
	std::pair<int, int>,
	std::pair<uint16_t, uint16_t>
>;

TYPED_TEST_SUITE(StreamAverageTest, testTypes);


TYPED_TEST(StreamAverageTest, resetsAverageAndChecksZero)
{
	this->unitUnderTest << 12;
	this->unitUnderTest << 2;
	this->unitUnderTest.reset();
	EXPECT_EQ(0, this->unitUnderTest.get());
	EXPECT_EQ(0, this->unitUnderTest.getNumValues());
	EXPECT_EQ(0, this->unitUnderTest.getMax());
	EXPECT_EQ(0, this->unitUnderTest.getMin());
}

TYPED_TEST(StreamAverageTest, checksMaxMinNumValues)
{
	this->unitUnderTest.reset();
	this->unitUnderTest << 12;
	this->unitUnderTest << 2;
	this->unitUnderTest << 5;
	this->unitUnderTest << 58;
	EXPECT_EQ(58, this->unitUnderTest.getMax());
	EXPECT_EQ(2, this->unitUnderTest.getMin());
	EXPECT_EQ(4, this->unitUnderTest.getNumValues());
}

TYPED_TEST(StreamAverageTest, checksOperatorsAndImplicitCast)
{
	using T = typename TypeParam::first_type;
	this->unitUnderTest.reset();
	this->unitUnderTest << 29;
	T average = this->unitUnderTest;
	EXPECT_EQ(29, average);
}

TYPED_TEST(StreamAverageTest, addsValuesAndChecksPrecision)
{
	this->unitUnderTest.reset();
	for(size_t i = 0; i < 1000; i++)
	{
		typename TypeParam::first_type newValue = static_cast<typename TypeParam::first_type>(std::rand() / 1.37);

		this->values.push_back(newValue);
		typename TypeParam::first_type expectedAvg = 
		std::reduce(this->values.begin(), this->values.end()) / static_cast<typename TypeParam::second_type>(this->values.size());

		typename TypeParam::first_type actualAvg = this->unitUnderTest << newValue;

		EXPECT_NEAR(expectedAvg, actualAvg, 0.1);
	}
}

int main()
{
	testing::InitGoogleTest();
	return RUN_ALL_TESTS();
}