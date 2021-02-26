/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Left                 motor         1               
// Right                motor         2               
// rightarm             motor         3               
// leftarm              motor         4               
// claw                 motor         5               
// ArmPento             pot           A               
// rLed                 led           B               
// gLed                 led           C               
// yLed                 led           D               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
bool gUp = true;
float speedAdj = 1;
void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Brain.Screen.print("Bryson is far superior to Ben in every way.");
  rLed.off();
  gLed.off();
  yLed.off();
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}
void liftArm(){
  int startVal = ArmPento.angle();
  Brain.Screen.newLine();
  Controller1.Screen.print(startVal);
  while(ArmPento.angle() - startVal < 20){
    leftarm.spin(directionType::fwd, 40, velocityUnits::pct);
    rightarm.spin(directionType::fwd, 40, velocityUnits::pct);
    Brain.Screen.newLine();
    Brain.Screen.print(ArmPento.angle()- startVal);
  }
  leftarm.stop(brakeType::brake);
  rightarm.stop(brakeType::brake);
}

void adjSpeed(){
  if(gUp){
    speedAdj = 1.5;
    gUp = false;
  } else {
    speedAdj = 1;
    gUp = true;
  }
  return;
}
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*---------------------------------------------------------------------------*/


void autonomous(void) {
  
  
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*---------------------------------------------------------------------------*/


void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    //left and right wheel drive
    yLed.off();
    Left.spin(directionType::fwd, (Controller1.Axis2.value() / 1.27)*speedAdj, velocityUnits::pct );
    Right.spin(directionType::fwd, (Controller1.Axis3.value() / 1.27)*speedAdj, velocityUnits::pct);
    //arm
    if(Controller1.ButtonR1.pressing()){
      rightarm.spin(directionType::fwd, 40, velocityUnits::pct);
      leftarm.spin(directionType::fwd, 40, velocityUnits::pct);
    } else if(Controller1.ButtonR2.pressing()){
      rightarm.spin(directionType::rev, 40, velocityUnits::pct);
      leftarm.spin(directionType::rev, 40, velocityUnits::pct);
    } else {
      rightarm.stop(brakeType::hold);
      leftarm.stop(brakeType::hold);
      yLed.on();
    }
    //Claw 
    if(Controller1.ButtonL1.pressing()){
      claw.spin(directionType::rev, 50, velocityUnits::pct);
    } else
    if(Controller1.ButtonL2.pressing()){
      claw.spin(directionType::fwd, 50, velocityUnits::pct);
    } else {
      claw.stop(brakeType::brake);
    }
   
  Controller1.ButtonA.released(adjSpeed);
  Controller1.ButtonUp.released(liftArm);
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}


//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
