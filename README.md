# Kalman Filter for Localization

## Description
This is a small robot project to demonstrate the Kalman filter for the localization of vehicles.
Here, the localization is limited to one dimension: A robot drives towards a wall and tries to measure the distance to it.
The noisy signal of the ultrasonic sensor is filtered with the Kalman filter to obtain the distance estimation. It can be mathematically proven that this estimation minimizes the expected squared error (and other interesting properties).

![Robot](/pictures/robot.jpg)
The robot used for the distance measurements.

![Robot](/pictures/measurements.jpg)
The distance measurements and the smoothed signal obtained by the Kalman filter.

## Contents
* `KalmanFilter.ino` : Arduino code for the robot. Controls the motors and sends the distance measurements.
* `KalmanFilter.m` : Matlab code to trigger the start of the robot program, obtain the sensor measurements and calculate the Kalman filter outcome. 

