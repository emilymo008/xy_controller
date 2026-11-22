#include <Trill.h>

Trill trillSensor;
boolean touchActive = false;

bool threeFingerRelease;  

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

void loop() {
/// DEFINE EVERYTHING YOU NEED HERE!

  const int midi_chan = 1;  // midi channel

  // set xyz controller numbers - need to change to something that doesn't conflict with keyboard
  int x_controller = 21;
  int y_controller = 22;
  int depth_controller = 23;

  // initialize xyz values
  int x_val = 0;
  int y_val = 0;
  int depth_val = 0; 
  // TODO: IMPLEMENT DEPTH!!!
  
  // initialize data we grab from trill
  int xPos, yPos, vTouches, hTouches, maxTouches;

  // if (threeFingerRelease){
  //   Serial.print("THREE FINGER RELEASE!");
  // }

  delay(50); // Read 20 times per second
  // Serial.print("running \n");
  trillSensor.read();

  vTouches = trillSensor.getNumTouches();  // vertical axis
  hTouches = trillSensor.getNumHorizontalTouches();  // horizontal axis
  maxTouches = max(hTouches, vTouches);

  // basically when you rotate your fingers 90 degrees the axis flips
  xPos = trillSensor.touchHorizontalLocation(0);
  yPos = trillSensor.touchLocation(0);

  // if threeFingerRelease is true and num touches = 0 , turn off threeFingerRelease
  // threeFingerRelease indicates that the 3-finger touch to reset to 0,0 is still being released
  if(threeFingerRelease & maxTouches == 0) {
    threeFingerRelease = 0;
  }

  // if threeFingerRelease is true...
  if(!threeFingerRelease & maxTouches > 0) {  // if any touches sensed
    Serial.print(hTouches);
    Serial.print(" h touches");
    Serial.print(" ");
    Serial.print(vTouches);
    Serial.print(" v touches");

    Serial.print(" //// ");
    
    bool threeOrMore = maxTouches >= 3;
 
      if(threeOrMore) {  // 3 finger tap
      // this is where I'll put the slow descend to 0,0
      // for now just violently snap to 0
      x_val = 0;
      y_val = 0;
      
      // As the 3 finger touch is released, need to avoid all new touch senses until maxtouches returns to 0
      threeFingerRelease = true;

    } else {
      // get just the coordinates of the first touch
      // each vertical / horiz has a location and size 
      // (location goes from 0 to 1792, size depends on how big my finger is)

      x_val = (127 * xPos) / 1792;
      y_val = (127 * yPos) / 1792;

    }

    usbMIDI.sendControlChange(x_controller, x_val, 1);
    usbMIDI.sendControlChange(y_controller, y_val, 1);

    Serial.print("midi coords: (");
    Serial.print(x_val);
    Serial.print(",");
    Serial.print(y_val);
    Serial.print(") \n");
    touchActive = true;
  }
 
}

 