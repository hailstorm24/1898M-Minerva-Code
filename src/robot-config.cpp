#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor Oink = motor(PORT1, ratio18_1, false);
motor Twim = motor(PORT2, ratio18_1, false);
motor Theresa = motor(PORT3, ratio18_1, false);
motor Fatima = motor(PORT4, ratio18_1, false);
digital_out Adonnari = digital_out(Brain.ThreeWirePort.A);
digital_out Bedonnolo = digital_out(Brain.ThreeWirePort.B);
motor Fidello = motor(PORT5, ratio36_1, false);
motor Seda = motor(PORT6, ratio36_1, false);
motor Sieves = motor(PORT7, ratio36_1, false);
motor Oeci = motor(PORT8, ratio36_1, false);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}