# Wheater Station with Digistump Oak
This projects allows to fetch weather data (temperature, humidity, pressure and ambient light) with the Digistump [Oak](http://digistump.com/oak/) and it's Wheather [Shield](http://digistump.com/products/163). The data is send to the [Particle](https://www.particle.io/prototype) cloud and collected with a python script to store the data in a MySQL database.

The wheater data is visualised with [Highcharts](http://www.highcharts.com/) on an Apache webserver.

# Oak configuration
To guarantee a long runtime when battery powered, following strategies are used:
* use deep sleed mode of Oak
* send data only each 150s
* disable onboard LED

Therefore following hardware modifications have been made:
* connect WAKE-RST solder pad
* cut LED-EN solder pad of main onboard LED

To program the Oak with the Arduino IDE you have to connect PIN1 to GND at power cyle to put the Oak in safe mode.

General information and how to build up the Wheater Shield you'll find in the corresponding [wiki](http://digistump.com/wiki/oak)

Sourcecode modifications:
* change ALTITUDE define to you altitude (in meters)
* adjust the sleep time (150s is default)

# Webserver configuration
In this project I am using a MySQL database and an Apache Webserver running on a [Onion Omega](https://onion.io/omega) platform. For security reasons, make sure that "config.ini" is not accessible with the webbrowser.

A sample database (weather.sql) is given.

Modifications:
* change database login details in "config.ini"
* change database login details in "get_data.py"

# Images
![screenshot](/doc/screenshot.png)
