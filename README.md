# Car-Link

Car Link is software to visualize the 1D camera output in real time for the NXPCup contest.

The camera pixels are sent on the serie port of the car, and recived on the computer.
It require a specific sequence for synchronizing with the flow of data. This sequence is formated in the client software compiled on the robot.

The whole software is build in C++ with the QT library.

The UI is composed as follow :
![UI](/github/carLinkScreenshot.png)


1. Tool box : Here you can connect to serie port or change the parameters
2. State information : values of some state variable of the robot
3. Main plot :  Real Time plot of the 1D camera signal
5. Time plot :  Evolution of the signal over time
5. Console : Raw numerical signal
