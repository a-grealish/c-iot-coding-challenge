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
* The text file can be accessed on a local file system by the system
* The readers are float values showing the intensity of vibrations
* The device vibrates when in use and does not vibrate when not in use
* The magnitude of vibration is not constant when on and depends on use.
* The magnitude of vibration can be non-zero when not in use

## Answers
