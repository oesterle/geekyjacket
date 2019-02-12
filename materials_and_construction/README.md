![geekyjacket logo](https://github.com/oesterle/geekyjacket/raw/master/docs/logo.png "geekyjacket logo")

# geekyjacket
## Materials and construction

### Materials
* A jacket
* Sheer matching fabric (1/2 yard)  
  * organza or chiffon
* Needle and thread  
  * We cheated and used [3/8" wide Dritz Res•Q Tape](https://www.joann.com/res-q-tape-3-8inx5yds/9448929.html) instead, for quick, temporary assembly.
* [Adafruit Feather M0 Bluefruit](https://www.adafruit.com/product/2995) microcontroller
  * programmable with the Arduino IDE
* 1/2 meter of [NeoPixel strip](https://www.adafruit.com/product/2959?length=1)  
  * We used the [Mini Skinny 144 LEDs/m](https://www.adafruit.com/product/2969) version.
* [Lithium Ion Cylindrical Battery - 3.7v 2200mAh](https://www.adafruit.com/product/1781)  

### Set up the Arduino IDE
Be sure to set up the Arduino IDE for use with the Feather. Follow the instructions in the [product guide](https://learn.adafruit.com/adafruit-feather-m0-bluefruit-le/overview) for installing the **board support package** and the **Bluefruit library**.

### Soldering the NeoPixel LED strip
Locate the input end of the NeoPixel LED strip – arrows on the strip point *away* from this end. Solder the connections:

NeoPixel strip | Feather
-------------- | -------------
Gnd            | Gnd
+5V            | Bat
Din            | Pin 6

For more durability, use flexible silicone wire to connect to the Feather. A good choice would be Adafruit's [Silicone Cover Stranded-Core Ribbon Cable - 4 Wires 1 Meter Long - 26AWG Black](https://www.adafruit.com/product/3892).  
![schematic](https://github.com/oesterle/geekyjacket/raw/master/materials_and_construction/gj_schematic_bb_1024px_b.jpg "schematic")

### Powering the MCU and LEDs
For the animations in our demo, which light a maximum of 10 LEDs at a time, we use Adafruit's [Lithium Ion Cylindrical Battery - 3.7v 2200mAh](https://www.adafruit.com/product/1781). NeoPixel LEDs can use 60mA each on full brightness. For 10 LEDs on at full brightness, this would require about 600mA current draw. See the (NeoPixel Überguide)[https://learn.adafruit.com/adafruit-neopixel-uberguide/the-magic-of-neopixels] for more info on powering LED strips.

Also, you'll note that we are power the strip from the ~3.7V battery, rather than its 5V rated power. This is fairly common in mobile projects, and exploits the WS2812B tolerance for somewhat lower voltage.

### Testing
Test the MCU and strip before sewing into the jacket sleeve.

### Sewing, or "sewing"
We used 0.5m of NeoPixel strip for one sleeve, cutting a 1m strip in half. (NeoPixel strips usually have cutlines between pixels.)

We found sheer black fabric at [JOANN Fabric and Craft Stores](https://www.joann.com) that just hides the LED strip, while being transparent enough for the LEDs to show through when on. Ask for organza or chiffon.  
![organza](https://github.com/oesterle/geekyjacket/raw/master/materials_and_construction/organza.jpg "organza")

Lay out the strip on the sleeve. Cut a small hole (4cm/1.5in) near the cuff to hide the Feather and battery inside the sleeve.  
![Neil prepares to cut the cuff hole](https://github.com/oesterle/geekyjacket/raw/master/materials_and_construction/assembly_cut_1024p.jpg "Neil prepares to cut the cuff hole")

For the quick build, we used 3/8" (9.5mm) wide Dritz Res•Q tape. Apply the tape to the sleeve parallel to the strip, on both sides of the strip. Cut a piece of the sheer fabric about 2" (5cm) wide, and a bit longer than the strip. Press the sheer fabric onto the tape.  
![Dritz Res•Q Tape](https://github.com/oesterle/geekyjacket/raw/master/materials_and_construction/dritz_res_q_tape.jpg "Dritz Res•Q Tape")

For a more permanant build, sew the sheer fabric, folding the edges under before sewing to avoid fraying. An iron set at the lowest setting may be helpful in preparing the edge for sewing. Use Velcro if you'd like to be able to launder the garment.

Push the Feather and battery through the hole to hide them inside the sleeve. You can sew a small pocket near the cuff to hold both, protecting both the electronics and your wrist from each other.  
![Hide the Feather inside sleeve](https://github.com/oesterle/geekyjacket/raw/master/materials_and_construction/assembly_cuff.jpg "Hide the Feather inside sleeve")
