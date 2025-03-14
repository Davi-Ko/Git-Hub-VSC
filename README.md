# {PROJETO SONOFF}

## First Version:

This is the first model of the ESP-01 project firmware build!<br>
<p align="center">
  <a href="V_0.0.1.ino">
    <img src="https://img.shields.io/badge/V_0.0.1-blue" alt="V_0.0.1">
  </a>
</p><br>
This is a way to make two relays work as twins using their own Wi-Fi, without the help of a router and external Wi-Fi.<br>
In ths project, we use relays with a module Wi-Fi called ESP-01 of the ESP8266 line. The idea is to make the relay be able to communicate with another, to do this the relay must be both an Access Point as well as a Client. Even though we are using only two in this starter, it is possible to use multiple relays that can ask the status of each relay and alter their state depending on your wishes, it can be a toggle function as well as a synchronized function.
