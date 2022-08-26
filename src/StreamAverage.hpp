#ifndef AccumulationAverage_h
#define AccumulationAverage_h

/**
 * @brief Class for averaging without having huge 
 *        data Buffers consuming all your memory.
 * 
 * @tparam Type of the data to average
 */
template<typename T>
class StreamAverage
{
    private:
    size_t numData = 0;
    T average = 0;

    public:
    /**
     * @brief Add new value to the average
     * 
     * @param value The value to add
     * @return The new Average
     */
    T add(T value)
    {
        if(numData == 0)
            average = value;
        else
            average = (value + average * numData) / (1 + numData);
        
        numData++;
        return average;
    }


    /**
     * @brief Add new value to the average
     * 
     * @param value The value to add
     * @return The new Average
     */
    T operator<<(T value)
    {
        if(numData == 0)
            average = value;
        else
            average = (value + average * numData) / (1 + numData);
        
        numData++;
        return average;
    }


    /**
     * @brief Add new value to the average
     * 
     * @param value The value to add
     * @return The new Average
     */
    T operator+=(T value)
    {
        if(numData == 0)
            average = value;
        else
            average = (value + average * numData) / (1 + numData);
        
        numData++;
        return average;
    }


    /**
     * @brief Get the current average
     * 
     * @return The Momentary average
     */
    T get() const
    {
        return average;
    }


    /**
     * @brief Resets the average
     * 
     */
    void reset()
    {
        numData = 0;
        average = 0;
    }
    
    /**
     * @brief Implicitly get the current average
     */
    operator T() const
    {
        return average;
    }
};

#endif