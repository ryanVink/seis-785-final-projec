# Dinner For Two


### Technologies Used

* Particle.io cloud
* AWS Lambda

### Languages Used

* C/C++
* nodejs

### Hardware Used

* Particle Photon
* LEDs
* Pigtail Connectors
* TLCTLC59711 from Adafruit

### What it Does

It scrapes an opentable URL for the specific restaraunt. After scraping the webpage
it figures out how many open seats for two people it has.  After it does that it sends the
a color and a position to the photon via the Particle.publish API.  

The Photon sets the color for the given position on the board.

The colors are as follows.
* Green = five open positions
* Yellow = less than 5 open tables but more than 0
* Red = 0 open tables