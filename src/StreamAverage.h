#ifndef StreamAverage_h
#define StreamAverage_h

/**
 * @brief Class for averaging without having huge 
 *        data Buffers consuming all your memory.
 * 
 * @tparam ExternalType Type used to get and set values in the class
 * @tparam InternalType Type used for internal calculations of the average
 *         By default internal and external types are the same
 */
template<typename ExternalType, typename InternalType = ExternalType>
class StreamAverage
{
private:
    ExternalType max = 0;
    ExternalType min = 0;
    size_t numValues = 0;
    InternalType sum = 0;

public:
    /**
     * @brief Add new value to the average
     * 
     * @param value The value to add
     * @return The new Average
     */
    inline ExternalType add(ExternalType value)
    {
        if(numValues == 0)
        {
            max = value;
            min = value;
        }
        
        if(value > max) max = value;
        if(value < min) min = value;

        sum += value;
        return (InternalType)sum / ++numValues;
    }


    /**
     * @brief Add new value to the average
     * 
     * @param value The value to add
     * @return The new Average
     */
    inline ExternalType operator<<(ExternalType value)
    {
        return add(value);
    }


    /**
     * @brief Get the current average
     */
    inline ExternalType get() const
    {
        if(numValues == 0) return (InternalType)0;
        return (InternalType)sum / numValues;
    }


    /**
     * @brief Get the maximum value added to the average
     *        since the last reset 
     */
    inline ExternalType getMax() const
    {
        return max;
    }


    /**
     * @brief Get the minimum value added to the average
     *        since the last reset
     */
    inline ExternalType getMin() const
    {
        return min;
    }

    /**
     * @brief Get the number of values the average holds
     * 
     * @return size_t 
     */
    inline size_t getNumValues() const
    {
        return numValues;
    }


    /**
     * @brief Resets the average, maximum and minimum
     * 
     */
    inline void reset()
    {
        max = 0;
        min = 0;
        numValues = 0;
        sum = 0;
    }
    
    /**
     * @brief Get the current average implicitly
     */
    inline operator ExternalType() const
    {
        return get();
    }
};

#endif