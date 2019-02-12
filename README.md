![geekyjacket logo](https://github.com/oesterle/geekyjacket/raw/master/docs/logo.png "geekyjacket logo")

# geekyjacket
### Animate LEDs on your jacket with a Flutter app

Made at [DevCamp](https://devca.mp), February 1-3, 2019, by Eric Oesterle & Neil Heather. Winner for [“Coolest Hack.”](https://devca.mp/unleashing-the-heroes-f48a241f72a6)

![demo](https://github.com/oesterle/geekyjacket/raw/master/docs/gj_demo_vid.gif "demo")  
[Watch a longer clip of the demo](https://twitter.com/erico/status/1092261259544674304)

A project connecting a mobile [Flutter](https://flutter.io) app to wearables via Bluetooth LE.

Uses the [flutter_blue](https://pub.dartlang.org/packages/flutter_blue) plugin to connect with an [Adafruit Feather M0 Bluefruit](https://www.adafruit.com/product/2995) microcontroller.

### Project structure
**[mobile_app](https://github.com/oesterle/geekyjacket/tree/master/mobile_app)** contains the Flutter project. We used VS Code to build. We've only tested the project on iOS so far. See **[docs](https://github.com/oesterle/geekyjacket/tree/master/docs)** for how to connect to and control geekyjacket from your phone.

**[firmware](https://github.com/oesterle/geekyjacket/tree/master/firmware)** contains Arduino code. Be sure to install the board support package for your microcontroller. See the product guide for your MCU. For the [Adafruit Feather M0 Bluefruit](https://www.adafruit.com/product/2995), its this [product guide](https://learn.adafruit.com/adafruit-feather-m0-bluefruit-le/overview).

**[materials_and_construction](https://github.com/oesterle/geekyjacket/tree/master/materials_and_construction)** includes the list of materials, and will guide you through assembling the project and integrating it into the jacket sleeve.

### Running the app
See the annotated screenshots in the **[docs](https://github.com/oesterle/geekyjacket/tree/master/docs)** folder for
steps to get connected to **geekyjacket**. It's important to follow the steps to get the app to talk to the MCU. This process will be simplified in the future.
