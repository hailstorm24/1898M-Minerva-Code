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
// Oink                 motor         1               
// Twim                 motor         2               
// Theresa              motor         3               
// Fatima               motor         4               
// Adonnari             digital_out   A               
// Bedonnolo            digital_out   B               
// Fidello              motor         5               
// Seda                 motor         6               
// ---- END VEXCODE CONFIGURED DEVICES ----


#include "vex.h"



using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here 

motor_group Libby = motor_group(Oink, Theresa);
motor_group Robert = motor_group(Twim, Fatima);


//Credit to https://www.vexforum.com/t/vexcode-v5-text-example/68242/8 Doctortictac starts here
// vex::brain    Brain;
vex::motor    back_right_motor(vex::PORT4,vex::gearSetting::ratio18_1, true);  
vex::motor    back_left_motor(vex::PORT3,vex::gearSetting::ratio18_1,false);
vex::motor    front_right_motor(vex::PORT2, vex::gearSetting::ratio18_1,true);
vex::motor    front_left_motor(vex::PORT1, vex::gearSetting::ratio18_1, false);

  

//Doctortictac credit ends here
/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
//aut
void drive_forward(double direction){

    Libby.spinFor(reverse,1100*direction,degrees,false);
    Robert.spinFor(forward,1100*direction,degrees,false);
} 
//end part 1
//radius of wheel = 2.125

//circumference = pi*2r = 4.25pi    35 inches    4.25pi inches - length traveled in 1 rotation


/*
set position of each side to zero
turn on libby
turn on robert
while position < how far you want to move:
  keep moving
  update position
 *****  if gyro data suggests we are pointing left
  ******  increase speed of libby and decrease speed of robert

stop moving

*/


void setDrive(double left,double right){
  Libby.setVelocity(-left, percent);
  Robert.setVelocity(right, percent);
  Libby.spin(forward);
  Robert.spin(forward);
}

double max(double first, double second){
  if(first>second){
    return first;
  }else{
    return second;
  }
}

void driveForward(int inches,int vel){
  Libby.resetPosition();
  Robert.resetPosition();
  int multiplier = 25;
  double distanceInDegrees = inches*multiplier;
  while(Libby.position(degrees)>-distanceInDegrees&&Robert.position(degrees)<distanceInDegrees){
    setDrive(vel,vel);
  }
  Libby.stop(brake);
  Robert.stop(brake);
}

void driveBackward(int inches,int vel){
  Libby.resetPosition();
  Robert.resetPosition();
  int multiplier = 25;
  double distanceInDegrees = inches*multiplier;
  while(Libby.position(degrees)<distanceInDegrees&&Robert.position(degrees)>-distanceInDegrees){
    setDrive(-vel,-vel);
  }
  Libby.stop(brake);
  Robert.stop(brake);
}

void turnLeft(int deg,int vel){
  Libby.resetPosition();
  Robert.resetPosition();
  double multiplier = 2.25;
  double distanceInDegrees = deg*multiplier;
  while(Libby.position(degrees)<distanceInDegrees&&Robert.position(degrees)<distanceInDegrees){
    setDrive(-vel,vel);
  }
  Libby.stop(brake);
  Robert.stop(brake);
}

void turnRight(int deg,int vel){
  Libby.resetPosition();
  Robert.resetPosition();
  double multiplier = 2.25;
  double distanceInDegrees = deg*multiplier;
  while(Libby.position(degrees)>-distanceInDegrees&&Robert.position(degrees)>-distanceInDegrees){
    setDrive(vel,-vel);
  }
  Libby.stop(brake);
  Robert.stop(brake);
}


void yay(double goal){


    double distanceInDegrees=1100*goal;

    Libby.resetPosition();
    Robert.resetPosition();
    double start = 50;
    setDrive(start,start);
    Libby.spin(forward);
    Robert.spin(forward);

    while(Libby.position(degrees)>-distanceInDegrees&&Robert.position(degrees)<distanceInDegrees){
      Controller1.Screen.clearLine();
      Controller1.Screen.print(__STRING(Libby.rotation(degrees)));

      double robertRotation = Robert.position(degrees);
      double libbyRotation = Libby.position(degrees);
      double difference = robertRotation-(-libbyRotation);
      double libbyVelocity = -Libby.velocity(percent);
      double robertVelocity = (2*start)-libbyVelocity;
      Brain.Screen.clearLine();
      Brain.Screen.print(difference);
      

      if(difference>5){
        setDrive(libbyVelocity+1, max(robertVelocity-1,0));
      }else if(difference<5){
        setDrive(max(libbyVelocity-1,0),robertVelocity+1);
      }
      
    Libby.stop(brake);
    Robert.stop(brake);

    }

    // Robert.spinFor(forward,1100*direction,degrees,false);
} 
//aut

void LibRo(double goal){
  // double distanceInDegrees=1580*goal;
    Libby.resetPosition();
    Robert.resetPosition();
    double start = 25;
    setDrive(start,start);
    Libby.setVelocity(80,percent);
    Robert.setVelocity(80,percent);
    Libby.spin(reverse);
    Robert.spin(forward);
}

void offensiveSideAuton(){
  driveForward(40,100);
  driveBackward(8,30);
  // driveBackward(1,50);
}


void defensiveSideAuton(){
  turnLeft(90, 75);
  // Adonnari.set(true);
  // move forward
  // touch middle bar
}

void autonomous(void) {
  // ..........................................................................
  // Autonomous user code here.
  // ..........................................................................
  defensiveSideAuton();

}

//end part 2

//skills!

void oldAuton(){
    Libby.setVelocity(70, percent); 
  Robert.setVelocity(70, percent);
  drive_forward(1);
  wait(3,seconds);
  Libby.setVelocity(40, percent); 
  Robert.setVelocity(40, percent);
  drive_forward(-1.5);
  wait(3, seconds);
//   Libby.setVelocity(70, percent); 
//   Robert.setVelocity(70, percent);
//   // drive_forward(0.25);
//   // wait(0.25,seconds);
//   Controller1.rumble(rumbleShort);
//   // // // LibRo(0.07);
//   // // wait(0.56, seconds);
//   // Libby.setVelocity(35, percent); 
//   // Robert.spin(forward);
//   // Libby.spin(forward);
//   // wait(0.5, seconds);
//   // Robert.setVelocity(35, percent);
//   // Libby.spin(reverse);
//   // Robert.spin(forward);
//   // wait(1.6, seconds);
//   // Robert.spin(forward);
//   // Libby.spin(forward);
//   // wait(0.5, seconds);
//   // Libby.stop(brake);
//   // Robert.stop(brake);
}

// void autonomous(void) {
//   //..........................................................................
//     for(int three=0; three<45;three++){
//       Fidello.setVelocity(100,percent);
//       Fidello.spinFor(forward, 700, degrees);
//       wait(0.4, seconds);
//     }

//     Fidello.stop(brake);
//     Robert.setVelocity(80,percent);
//     Robert.spinFor(forward, 180, degrees);
//     wait(1.5, seconds);
//     Libby.setVelocity(80, percent);
//     LibRo(0.28);
//     wait(1.7, seconds);
//     Robert.spinFor(reverse,50,degrees);
//     wait(0.2, seconds);
//     LibRo(-0.1);
//     wait(0.2, seconds);
//     LibRo(100); // drive straight and over barrier
//     wait(1.5,seconds);
//     Adonnari.set(true); 
//     Bedonnolo.set(true);
// }

    //previous skills:
    // for(int three = 0; three < 1; three++) { 
    //   wait(15,seconds);
    //   Libby.setVelocity(80, percent); 
    //   Robert.setVelocity(80, percent);  
    //   drive_forward(1);
    //   wait(3.5,seconds);
    //   Libby.setVelocity(60, percent); 
    //   Robert.setVelocity(60, percent); 
    //   drive_forward(-1);
    //   wait(3.5, seconds);
    // }
    // wait(5,seconds);
    
    // wait(20,seconds);
    // Libby.setVelocity(80, percent); 
    // Robert.setVelocity(80, percent); 
    // drive_forward(1);
    // wait(4,seconds);
    // drive_forward(0.5);
    // wait(2.5, seconds);
    // drive_forward(-0.5);
    // wait(2.5, seconds);
    

    
    
    // Libby.spinFor(reverse,1100,degrees);
    // Robert.spinFor(forward,1100,degrees);



/*-------------//end of skills

---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
//regular joystick control
    //Libby.spin(reverse, ((abs(Controller1.Axis3.value()))/(Controller1.Axis3.value()))*(0.01*pow((Controller1.Axis3.value()),2)), pct);
    //Robert.spin(forward, ((abs(Controller1.Axis2.value()))/(Controller1.Axis2.value()))*(0.01*pow((Controller1.Axis2.value()),2)), pct);
    Libby.spin(reverse,  (Controller1.Axis3.value() + ((abs(Controller1.Axis1.value())/Controller1.Axis1.value())) * (0.01*pow((Controller1.Axis1.value ()),2))), pct );
    Robert.spin(forward,  (Controller1.Axis3.value() - ((abs(Controller1.Axis1.value())/Controller1.Axis1.value())) * (0.01*pow((Controller1.Axis1.value ()),2))), pct );


  //below is the pneumatics code
    if(Controller1.ButtonR1.pressing()){
      Adonnari.set(true);
    }
    if(Controller1.ButtonR2.pressing()){
      Adonnari.set(false);
    }
    if(Controller1.ButtonL1.pressing()){
      Bedonnolo.set(true);
    }
    if(Controller1.ButtonL2.pressing()){
      Bedonnolo.set(false);
    }
//below is the puncher code...
    if(Controller1.ButtonA.pressing()){
        Fidello.setVelocity(100,percent);
        Fidello.spinFor(forward, 750, degrees);
        wait(0.4, seconds);
      }
    else{
      Fidello.stop(brake);
    }
  
          

    // //bellow is the eventual catapault code
    // if(Controller1.ButtonA.pressing()){
    //   Fidello.spinFor(forward, 1800, degrees);

    // }
  

    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................



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
