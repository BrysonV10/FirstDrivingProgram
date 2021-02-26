#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor Left = motor(PORT1, ratio18_1, true);
motor Right = motor(PORT2, ratio18_1, false);
motor rightarm = motor(PORT3, ratio18_1, true);
motor leftarm = motor(PORT4, ratio18_1, false);
motor claw = motor(PORT5, ratio18_1, false);
pot ArmPento = pot(Brain.ThreeWirePort.A);
led rLed = led(Brain.ThreeWirePort.B);
led gLed = led(Brain.ThreeWirePort.C);
led yLed = led(Brain.ThreeWirePort.D);

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