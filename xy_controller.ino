
const int midi_chan = 1;

// set xyz controller numbers - need to change to something that doesn't conflict with keyboard
int x_controller = 20;
int y_controller = 21;
int depth_controller = 22;

// initialize xyz values
int x_val = 0;
int y_val = 0;
int depth_val = 0; 

void setup() {
}

elapsedMillis msec = 0;
int change_probability = 20;  // dummy code: 20% chance of changing values.

void loop() {
  if (msec >= 1000) {  // dummy code - only simulate every 1 second
    msec = 0;
    // these next few lines simulate my finger "touching" the pad,
    // b/c don't have an input device yet
    int change_flip = random(1, 100);  // random number from 1-100 
    bool change = change_flip <= change_probability;  // if number is <= change probability, change values
    if (change == true) {
      int x_val = random(1, 127);
      int y_val = random(1, 127);
      int depth_val = random(1, 127); 

      usbMIDI.sendControlChange(x_controller, x_val, 1);
      usbMIDI.sendControlChange(y_controller, y_val, 1);
      usbMIDI.sendControlChange(depth_controller, depth_val, 1);
      
    }
  }

  while (usbMIDI.read()) {
      // ignore incoming messages
  }

}
