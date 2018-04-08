# Challenge
## Background
Consider an IOT device attached to machinery used to estimate its degree of usability.

The device measures its vibrations and stores the readings in a text file, one line for each reading. However, the device is flawed and reverses all the digits of the reading! The aim is to figure out the percentage time the machine is used, assuming the readings are taken at a fixed interval, and write it back to a text file.

## Required
1. Design a system using C/C++ that would read from a text file the readings and store them in the appropriate data structure.
2. Design a way to reverse back the reading’s digits with minimal complexity and without using the strrev() function.
3. Define an adequate way to estimate if the machine is in use or not, based on the series of readings.
4. Compute the percentage time the machine is in use and write it back to a text file.

## Stretch
1. Consider how large amounts of data would be handled if a connection between the device and where the data was consumed was a) intermittent, and b) remote.
2. What strategies might be put in place in the design of the device hardware and software to assist with manufacturing at large scale in production.

## Questions
1. What approach did you take to decide if the machine was in use based on the readings.
2. What is the time and space complexity of the written program?
3. What would you have done if you had more time?
4. What testing did you do, and why?

# Submission
## Assumptions
- The text file can be accessed on a local file system by the system
- In an embedded device it is likely that the vibration would be sensed with an accelerometer and the reading will represent the unit of acceleration rather the magnitude and frequency of vibration but here I have assumed that readings are a float representing the intensity of vibrations across a set frequency range.
- The device vibrates when in use and does not vibrate when not in use
- The magnitude of vibration is not constant when on and depends on use.
- The magnitude of vibration can be non-zero when not in use due to background vibration from surrounding devices.

## Running the Solution
- Uses gcc for building.
- Uses make to configure build options
- The follow options can be uses:
    - ```make``` builds a standard prod binary to ./bin/out
    - ```make run``` will run the above binary with the generated test data file
    - ```make test``` builds a binary with the tests, if successful then runs the tests.
    - ```make valgrind``` runs the production binary using valgrind to check for memory leak issues
    - ```make cppcheck``` runs static analysis on the src code
- Needs valgrind (memory profiler), [check](https://libcheck.github.io/check/doc/check_html/index.html) (unit test framework) and [cppcheck](http://cppcheck.sourceforge.net/) (static analysis) to be installed to run all tests above

## Answers
1. What approach did you take to decide if the machine was in use based on the readings.
    - Two approaches were written, the first a very simple classifier for two categories and a second based on k-means which can cluster on any number of clusters.
    - The simple approach I took was to find the min and max points, bisect these to get a threshold and then calculate the ratio above and below this. The assumption is that there is a large gap between the on and off state and that the noise is smaller than the gap.
    - The second, k-means based approach allows you to pass in the number of categories. It then will choose k random values as the starting means and cluster the points based on which mean has the lowest distance to each point. It then calculates the new mean for each cluster and iterates until those means converge. The difference here from a full k-means implementation is it only works in 1d and the distance calculation is just a subtraction rather than the euclidean distance. The second modification for k-means is to sort the list of means so that the cluster numbers return are also lower for the smallest mean cluster.

2. What is the time and space complexity of the written program?
    - Taking n as the number of readings in the text file:
        - Simple midpoint clustering
            - The clustering calculating code makes two n-length loops through the data so simplifies to O(n)
            - The dominant use of memory if holding all the data values and cluster numbers in an array so this is also O(n)
        - k-means clustering
            - The maximum number of iterations is set by MAX_ITERATIONS. In each iteration we make 1 n-length loop through the data. Within each loop we calculate k distances. So the worst case would be O(MAX_ITERATIONS\*n\*k) but as k should be much less that n this simplifies to O(n)
            - The dominant use of memory if holding all the data values and cluster numbers in an array so this is also O(n)


3. What would you have done if you had more time?
    - I would have taken this a step further and assumed that the input data is raw accelerometer values and adding another processing step to extract the vibration level from this to then pass into the clustering algorithm. One simple method for extracting the level would be a calculating the RMS across a set time interval. 
    - A more sophisticated approach may be to perform a Fourier Transform and analyse the data in the frequency domain, given that we are looking at motors, we should be able to see different frequency components in the data for different motor speeds. You would then be able to group/cluster the time-domain data intervals by the type of frequency response to identify off/idle/on times.
    - Built out a higher level test suite which links up the script to generate test data to the application to run through various test cases

4. What testing did you do, and why?
    - Simple unit test suite for some of the functions, these could benefit from more edge case testing.
    - Python script to generate input data and calculate the on time for comparison

5. Consider how large amounts of data would be handled if a connection between the device and where the data was consumed was a) intermittent, and b) remote.
    - If intermittence was an issue then the data would require a timestamp on each datapoint so that data gaps could be identified and handled apporpriately.
    - If the device was remote from where the data was processed then you would need to look at more robust methods for passing data between the device and the processing logic. The backend should have an api or messaging queue to which the data is uploaded. If the data cannot be uploaded due to connectivity issues it should be stored locally until upload is successful. On upload of new data the backend would store the data in an appropriate database and then a asynchronous job would be scheduled to process the data and store the result back into the db.

6. What strategies might be put in place in the design of the device hardware and software to assist with manufacturing at large scale in production.
    - Firmware OTA Updates - The firmware should be updatable over-the-air to ensure any firmware issues and possibly hardware issues can be fixes without requiring customer action or recall of products.
    - Global Connectivity - High-volume manufacturing becomes complex of different variants of the products are needed for different markets. In the design of the product you could consider multi-band GSM modules or combined NB-IoT/Cat-M0 modules to ensure the same product can be used globally. You should also consider using either a global roaming SIM or an E-SIM so that no local provisioning of SIM cards is required. 
    - Automated Testing - The hardware and software should make it simple to perform automated testing. On the hardware there should be sufficient testpoints to test the functionality with a test-jig. There should either be a seperate firmware for manufacturing test or there should be self-test functioanlity built into the firmware.