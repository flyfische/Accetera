# Accetera
IoT Thermostat

I wanted to create a network-connected thermostat that could be monitored and controlled remotely.

A potentiometer is used on the base thermostat to control temperature. When the temperature is updated via web interface, the potentiometer input is ignored until it is changed again. In simpler terms, the thermostat listens to whichever input was most recently updated.

I used the arduino C library to program the base thermostat station. The web interface is running Python Flask on the Intel Edison. This page can be accessed via web browser on both PC and phone.

In this example, an LED is lit when the unit is calling for heat. In a real-life application, a relay would be used to control the HVAC unit.

Unit will call for heat when the set temperature (set by user) is greater than the current room temperature.
