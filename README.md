# StreamAverage

C++ / Arduino Stream-Average-Library
**Disclaimer:** This is not a moving average, instead it accumulates the average of the
values you add

## Installating
### PlatformIO
### Arduino Library Manager
### From Github

## Documentation

First create a `StreamAverage` object. You can pass it two types as template argument.
`ExternalType` The first type is used to get and set values in the Average.
`InternalType` The second type is used for the internal calculations of the average.

By default internal and external types are the same.

```cpp
StreamAverage<float> average; // uses float both externally and internally
StreamAverage<int, float> average; // uses int externally and float internally
```


You cann get values into the average by using the `add()` method
```cpp
average.add(newValue);
```
or the shift operator
```cpp
average << newValue;
```

Both methods return the new value of the average, including the `newValue`
```cpp
float newAverage;
newAverage = average.add(2);
newAverage = average << 4;
// new Average now contains 3
```


You can get the current average using `get()`
```cpp
float currentAverage = average.get();
```
or get it implicitly
```cpp
float currentAverage = average;
```


You can get the maximum and minimum value the average holds, by calling `getMax()` and `getMin()`
```cpp
average << 5.5;
average << 43.27;
average << -19.3;
average << 0.02;
float maximum = average.getMax(); // 43.27
float minimum = average.getMin(); // -19.3 
```


To find out how many values have been added to the average, use `getNumValues()`
```cpp
size_t num = average.getNumValues();
```


After calling the `reset()` method, `get()`, `getMax()`, `getMin()`, `getNumValues()` will evalueate to 0
```cpp
average.reset();
```