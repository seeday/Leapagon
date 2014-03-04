Leapagon
========

A hacky Windows leap motion controller for Super Hexagon.

##Compiling
Leapagon depends on the Leap Motion SDK from https://developer.leapmotion.com

Leapagon includes ```Leap.h``` which depends on ```LeapMath.h```. Both must be in the same directory as ```leapagon.cpp```.

Visual Studio: Add ```Leap.lib``` and ```Leapd.lib``` as dependencies to the linker and place ```Leap.dll``` in the build location.

##Running
Make sure ```Leap.dll``` is in the same directory as the executable, start Super Hexagon, then start Leapagon. It should start tracking hands.

##Controls
Tilt your hand to the left to go left, tilt your hand to the right to go right. Space is still restart/select.
