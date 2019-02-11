
/*********************************************************************
 geekyjacket
 by Eric Oesterle & Neil Heather
 
 Built and presented at at DevCamp 2019 (Feb 1-3, 2019): 
 https://devca.mp/
 This version targets the Adafruit Feather M0 Bluefruit, but should
 be adaptable to other Bluefruit boards:
 https://www.adafruit.com/product/2995

 Designed to be controlled by a mobile app built on the Flutter
 framework, which is also part of this project and our demo:
 https://github.com/oesterle/geekyjacket

 This version is based on bleuart_datamode.ino from Adafruit Industries:
     This is an example for our nRF51822 based Bluefruit LE modules
    
     Pick one up today in the adafruit shop!
    
     Adafruit invests time and resources providing this open source code,
     please support Adafruit and open-source hardware by purchasing
     products from Adafruit!

 MIT license, check LICENSE for more information
 All text above, and the splash screen below must be included in
 any redistribution
*********************************************************************/


#include <Arduino.h>
#include <SPI.h>
#if not defined (_VARIANT_ARDUINO_DUE_X_) && not defined (_VARIANT_ARDUINO_ZERO_)
  #include <SoftwareSerial.h>
#endif

#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"

#include "BluefruitConfig.h"

#include <Adafruit_NeoPixel.h>

uint8_t curCol = 114;


// Set up NeoPixels. For the demo, we used about half of a 1m, 144-pixel
// Adafruit NeoPixel strip. Specifically we used a mini skinny one, with
// a white flexible PCB:
//
// "Adafruit Mini Skinny NeoPixel Digital RGB LED Strip - 144 LED/m - 1m WHITE"
// https://www.adafruit.com/product/2969
//
// There is also a variant that has a black background, which reflects less
// light, but would also be a bit less visible when off:
// 
// Adafruit Mini Skinny NeoPixel Digital RGB LED Strip - 144 LED/m - 1m BLACK
// https://www.adafruit.com/product/2970
//
// There are also less dense strips that are typically less expensive. This
// one has a black background, and is 60 LED/meter:
//
// "Adafruit Mini Skinny NeoPixel Digital RGB LED Strip - 60 LED/m - BLACK"
// https://www.adafruit.com/product/2964

#define PIN            6
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(72, PIN, NEO_GRB + NEO_KHZ800);

/*=========================================================================
    APPLICATION SETTINGS

    FACTORYRESET_ENABLE       Perform a factory reset when running this sketch
   
                              Enabling this will put your Bluefruit LE module
                              in a 'known good' state and clear any config
                              data set in previous sketches or projects, so
                              running this at least once is a good idea.
   
                              When deploying your project, however, you will
                              want to disable factory reset by setting this
                              value to 0.  If you are making changes to your
                              Bluefruit LE device via AT commands, and those
                              changes aren't persisting across resets, this
                              is the reason why.  Factory reset will erase
                              the non-volatile memory where config data is
                              stored, setting it back to factory default
                              values.
       
                              Some sketches that require you to bond to a
                              central device (HID mouse, keyboard, etc.)
                              won't work at all with this feature enabled
                              since the factory reset will clear all of the
                              bonding data stored on the chip, meaning the
                              central device won't be able to reconnect.
    MINIMUM_FIRMWARE_VERSION  Minimum firmware version to have some new features
    MODE_LED_BEHAVIOUR        LED activity, valid options are
                              "DISABLE" or "MODE" or "BLEUART" or
                              "HWUART"  or "SPI"  or "MANUAL"
    -----------------------------------------------------------------------*/
    #define FACTORYRESET_ENABLE         1
    #define MINIMUM_FIRMWARE_VERSION    "0.6.6"
    #define MODE_LED_BEHAVIOUR          "MODE"
/*=========================================================================*/


/* ...hardware SPI, using SCK/MOSI/MISO hardware SPI pins and then user selected CS/IRQ/RST */
Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);



// A small helper
void error(const __FlashStringHelper*err) {
  Serial.println(err);
  while (1);
}

/**************************************************************************/
/*!
    @brief  Sets up the HW an the BLE module (this function is called
            automatically on startup)
*/
/**************************************************************************/
void setup(void)
{
  //while (!Serial);  // required for Flora & Micro
  delay(500);

  pixels.begin();
  
  updatePixels();

  
  Serial.begin(115200);
  Serial.println(F("Adafruit Bluefruit Command <-> Data Mode Example"));
  Serial.println(F("------------------------------------------------"));

  /* Initialise the module */
  Serial.print(F("Initialising the Bluefruit LE module: "));

  if ( !ble.begin(VERBOSE_MODE) )
  {
    error(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
  }
  Serial.println( F("OK!") );

  if ( FACTORYRESET_ENABLE )
  {
    /* Perform a factory reset to make sure everything is in a known state */
    Serial.println(F("Performing a factory reset: "));
    if ( ! ble.factoryReset() ){
      error(F("Couldn't factory reset"));
    }
  }

  /* Disable command echo from Bluefruit */
  ble.echo(false);

  Serial.println("Requesting Bluefruit info:");
  /* Print Bluefruit information */
  ble.info();

  Serial.println(F("Please use Adafruit Bluefruit LE app to connect in UART mode"));
  Serial.println(F("Then Enter characters to send to Bluefruit"));
  Serial.println();

  ble.verbose(false);  // debug info is a little annoying after this point!

  /* Wait for connection */
  while (! ble.isConnected()) {
      delay(500);
  }

  Serial.println(F("******************************"));

  // LED Activity command is only supported from 0.6.6
  if ( ble.isVersionAtLeast(MINIMUM_FIRMWARE_VERSION) )
  {
    // Change Mode LED Activity
    Serial.println(F("Change LED activity to " MODE_LED_BEHAVIOUR));
    ble.sendCommandCheckOK("AT+HWModeLED=" MODE_LED_BEHAVIOUR);
  }

  // Set module to DATA mode
  Serial.println( F("Switching to DATA mode!") );
  ble.setMode(BLUEFRUIT_MODE_DATA);

  Serial.println(F("******************************"));
  
}

/**************************************************************************/
/*!
    @brief  Constantly poll for new command or response data
*/
/**************************************************************************/

uint16_t offset = 0;

void updatePixels() {
  // Show the current color tag in the Serial Monitor.
  Serial.println("");
  Serial.print("color tag: ");
  Serial.println(curCol);

  uint32_t aCol = pixels.Color(0,0,0);

  // When change colors/animations based on a single character 
  // coming over Bluetooth LE UART from the mobile device.
  // In our first demo, since we are building the mobile app
  // in Google's Flutter, we used the Google brand colors,
  // red: 'r', yellow: 'y', green: 'g', and blue: 'b'
  // 
  // We also have a special sparkly white pattern: 'a'.
  //
  // Any other character sets all pixels to off, and
  // our jacket looks like any normal jacket, since
  // we've hidden the NeoPixel strip behind a layer
  // of black chiffon.
  //
  switch(curCol){
    case 'r':
      Serial.println("red");
      aCol = pixels.Color(128,0,0);
      break;
    case 'y':
      aCol = pixels.Color(128,80,0);
      break;
    case 'g':
      aCol = pixels.Color(0,128,0);
      break;
    case 'b':
      aCol = pixels.Color(0,32,128);
      break;
    default:
      Serial.println("default");
      aCol = pixels.Color(0,0,0);
      break;
  }

  // first, turn off all the pixels
  for (uint16_t j = 0; j < 80; j++){
    pixels.setPixelColor(j, pixels.Color(0,0,0));
  }
  
  if (curCol == 'a'){
    // show our special sparkly white pattern
    pixels.setPixelColor(random(72),pixels.Color(255,255,255));
    pixels.setPixelColor(random(72),pixels.Color(255,255,255));
    pixels.setPixelColor(random(72),pixels.Color(255,255,255));
    delay(50);
  } else {
    // Show a chosen color on 10 pixels. This 10-pixel segment
    // moves across the strip, using an offset.
    // The Adafruit_NeoPixel library is forgiving: when this
    // offset causes some of the pixels to move off the end of the
    // strip, we don't get a range error. Yay.
    for (uint16_t i = 0; i < 10; i++){
      pixels.setPixelColor(i + offset, aCol);
    }
  }
  
  // Add one to the offset, and set it back to 0 when 
  // we reach the end.
  offset = (offset + 1) % 72;

  // For performance reasons, the strip doesn't update until
  // we do pixels.show():
  pixels.show();
}

void loop(void)
{
  // Check for user input
  char n, inputs[BUFSIZE+1];

  if (Serial.available())
  {
    n = Serial.readBytes(inputs, BUFSIZE);
    inputs[n] = 0;
    // Send characters to Bluefruit
    Serial.print("Sending: ");
    Serial.println(inputs);

    // Send input data to host via Bluefruit
    ble.print(inputs);
  }

  // Echo received data
  while ( ble.available() )
  {
    int c = ble.read();

    Serial.print((char)c);

    curCol = c;

    // Hex output too, helps w/debugging!
    Serial.print(" [0x");
    if (c <= 0xF) Serial.print(F("0"));
    Serial.print(c, HEX);
    Serial.print("] ");
  }

  updatePixels();
}


