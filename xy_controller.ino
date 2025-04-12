#include <Trill.h>

const int midi_chan = 1;  // midi channel

// set xyz controller numbers - need to change to something that doesn't conflict with keyboard
int x_controller = 21;
int y_controller = 22;
int depth_controller = 23;

// initialize xyz values
int x_val = 0;
int y_val = 0;
int depth_val = 0; 

Trill trillSensor;
boolean touchActive = false;

void setup() {
  // Initialise serial and touch sensor
  Serial.begin(115200);
  int ret = trillSensor.setup(Trill::TRILL_SQUARE);
  if(ret != 0) {
    Serial.println("failed to initialise trillSensor");
    Serial.print("Error code: ");
    Serial.println(ret);
  } 
  else {
    Serial.println("Success initialising trillSensor");
  }
}

elapsedMillis msec = 0;
int change_probability = 20;  // dummy code: 20% chance of changing values.

void loop() {

  delay(50); // Read 20 times per second
  Serial.print("running \n");
  trillSensor.read();

  if(trillSensor.getNumTouches() > 0 || trillSensor.getNumHorizontalTouches() > 0) {  // if any touches sensed
    Serial.print(trillSensor.getNumHorizontalTouches());
    Serial.print(" h touches");
    Serial.print(" ");
    Serial.print(trillSensor.getNumTouches());
    Serial.print(" v touches");

    Serial.print(" //// ");

    // get just the coordinates of the first touch
    // each vertical / horiz has a location and size 
    // (location goes from 0 to 1792, size depends on how big my finger is)

    int x_val = 127 * trillSensor.touchHorizontalLocation(0) / 1792;
    int y_val = 127 * trillSensor.touchLocation(0) / 1792;

    usbMIDI.sendControlChange(x_controller, x_val, 1);
    usbMIDI.sendControlChange(y_controller, y_val, 1);
    // TODO: touch

    Serial.print("midi coords: (");
    Serial.print(x_val);
    Serial.print(",");
    Serial.print(y_val);
    Serial.print(") \n");

    // Serial.print(trillSensor.touchHorizontalLocation(0));
    // Serial.print(" = x value, ");
    // Serial.print(trillSensor.touchLocation(0));
    // Serial.print(" = y value, ");
    
    // Serial.print(" //// ");

    // Serial.print(trillSensor.touchHorizontalSize(0));
    // Serial.print(" = horizontal touch size, ");
    // Serial.print(trillSensor.touchSize(0));
    // Serial.print(" = vertical touch size, ");
    
    touchActive = true;
  }
 
}

  // if (msec >= 1000) {  // dummy code - only simulate every 1 second
  //   msec = 0;


    
  //   these next few lines simulate my finger "touching" the pad,
  //   b/c don't have an input device yet
  //   int change_flip = random(1, 100);  // random number from 1-100 
  //   bool change = change_flip <= change_probability;  // if number is <= change probability, change values
  //   if (change == true) {
  //     int x_val = random(1, 127);
  //     int y_val = random(1, 127);
  //     int depth_val = random(1, 127); 

  //     usbMIDI.sendControlChange(x_controller, x_val, 1);
  //     usbMIDI.sendControlChange(y_controller, y_val, 1);
  //     usbMIDI.sendControlChange(depth_controller, depth_val, 1);
      
  //   }

  // }

  // while (usbMIDI.read()) {
  //     // ignore incoming messages
  // }


