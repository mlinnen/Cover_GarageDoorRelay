# Overview
This arduino library is designed to control a relay that will open or close a cover (blind or rolling door). The library will track the last state the cover was in and if a command comes in to place the cover in the same state it is already in then the command will be ignored.

## Dependencies
This library depends on the following libraries:
* RBD_Timer https://github.com/alextaujenis/RBD_Timer

The example Arduino Sketch also depends on the following libraries:
* PubSubClient http://pubsubclient.knolleary.net

You must install the dependent libraries before you compile the examples.

## Examples
### MQTT Garage Door Relay
This example uses the library to control a relay that triggers a garage door to open or close based on subscribing to commnad changes from an MQTT broker.  This example also subscribes to door state changes from an MQTT broker which allows for the library to know what state the door is currently in or transitioning to.

#### Configuration
The example requires you to fill out the Wifi and MQTT details before it will compile.

1. In the example folder copy mywifi.sample.h to mywifi.h
2. Edit the mywifi.h file to set the Wifi connection details.
3. In the example folder copy mymqttbroker.sample.h to mymqttbroker.h
4. Edit the mymqttbroker.h file to set the MQTT broker details.

After you make the changes to the mywifi.h and mymqttbroker.h you should be able to compile the example. 

#### Wiring
TODO

#### Running the example
The mosquitto MQTT broker and client tools are included in this repository in the test/MQTT/mosquitto folder.  You can use the test/MQTT/brokerlocal.bat to start up a local MQTT broker or just use one that is on on your network. 

You can use the test/MQTT/auditlocal.bat to launch the mosquitto_sub.exe to monitor all messages published to the local broker.  Use this if you are running the local broker without any username or password.

If you have a broker on your network that is password protected then use the test/MQTT/audit.bat to launch the mosquitto_sub.exe to monitor all messages published to the broker.  Before you run the audit.bat you should set the following environment variables:
* MQTT_IP - set to the IP of the MQTT Broker
* MQTT_USR - set to the user used to connect to the broker
* MQTT_PWD - set to the password of the user that will connect to the broker.

Once the broker and the audit are running you can go ahead and download the code to the arduino and let it run.

Executing the state batch files in the test/MQTT/ folder will publish a message on the MQTT broker and change the state of the Door Relay.  Executing the Command batch files will publish a command on the MQTT broker and the relay will react to it.  If you are using a local broker without a user name and password then use the batch files that start with local. 


### More Complete Examples
This repository contains more examples on how to use the cover libraries in a more complete way.  [Cover Full Examples](https://github.com/mlinnen/Cover_FullExamples)


