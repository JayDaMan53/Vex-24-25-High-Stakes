// #include "autons.hpp"
#include "autons.hpp"
#include "main.h"
#include <cmath>


/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////


const int DRIVE_SPEED = 110; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
                             // If this is 127 and the robot tries to heading correct, it's only correcting by
                             // making one side slower.  When this is 87%, it's correcting by making one side
                             // faster and one side slower, giving better heading correction.
const int TURN_SPEED  = 60;
const int SWING_SPEED = 90;

pros::Controller master (pros::E_CONTROLLER_MASTER);

pros::ADIDigitalOut apiston ('b');
pros::ADIDigitalOut apiston2 ('c');

pros::Motor aintakeB (10, pros::E_MOTOR_GEARSET_18, false);
pros::Motor aintakeA (9, pros::E_MOTOR_GEARSET_18, false);

///
// Constants
///

// It's best practice to tune constants when the robot is empty and with heavier game objects, or with lifts up vs down.
// If the objects are light or the cog doesn't change much, then there isn't a concern here.

void default_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

// void default_constants() {
//   chassis.set_slew_min_power(80, 80);
//   chassis.set_slew_distance(7, 7);
//   chassis.set_pid_constants(&chassis.headingPID, 11, 0, 25, 0);
//   chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
//   chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
//   chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
//   chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
// }

void one_mogo_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void two_mogo_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void exit_condition_defaults() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}

void modified_exit_condition() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}



///
// Drive Example
///
void drive_example() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater then the slew distance + a few inches


  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_drive_pid(-12, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-12, DRIVE_SPEED);
  chassis.wait_drive();
}



///
// Turn Example
///
void turn_example() {
  // The first parameter is target degrees
  // The second parameter is max speed the robot will drive at


  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();
}



///
// Combining Turn + Drive
///
void drive_and_turn() {
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_drive();
}



///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed() {
  // wait_until will wait until the robot gets to a desired position


  // When the robot gets to 6 inches, the robot will travel the remaining distance at a max speed of 40
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_until(6);
  chassis.set_max_speed(40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  // When the robot gets to -6 inches, the robot will travel the remaining distance at a max speed of 40
  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_until(-6);
  chassis.set_max_speed(40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
  chassis.wait_drive();
}



///
// Swing Example
///
void swing_example() {
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is target degrees
  // The third parameter is speed of the moving side of the drive


  chassis.set_swing_pid(ez::LEFT_SWING, 45, SWING_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_until(12);

  chassis.set_swing_pid(ez::RIGHT_SWING, 0, SWING_SPEED);
  chassis.wait_drive();
}



///
// Auto that tests everything
///
void combining_movements() {
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_swing_pid(ez::RIGHT_SWING, -45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_drive();
}



///
// Interference example
///
void tug (int attempts) {
  for (int i=0; i<attempts-1; i++) {
    // Attempt to drive backwards
    printf("i - %i", i);
    chassis.set_drive_pid(-12, 127);
    chassis.wait_drive();

    // If failsafed...
    if (chassis.interfered) {
      chassis.reset_drive_sensor();
      chassis.set_drive_pid(-2, 20);
      pros::delay(1000);
    }
    // If robot successfully drove back, return
    else {
      return;
    }
  }
}

// If there is no interference, robot will drive forward and turn 90 degrees. 
// If interfered, robot will drive forward and then attempt to drive backwards. 
void interfered_example() {
 chassis.set_drive_pid(24, DRIVE_SPEED, true);
 chassis.wait_drive();

 if (chassis.interfered) {
   tug(3);
   return;
 }

 chassis.set_turn_pid(90, TURN_SPEED);
 chassis.wait_drive();
}

// *******
// MY CODE
// *******

void LeftDeposit() {
  
  chassis.set_drive_pid(47, DRIVE_SPEED, true); // Move to gate
  chassis.wait_drive(); // Wait
  chassis.set_turn_pid(-90, TURN_SPEED); // Turn to gate
  chassis.wait_drive(); // Wait
  chassis.set_drive_pid(13, DRIVE_SPEED, true); // Move Closer to gate
  chassis.wait_drive(); // Wait

  //intake.move(127);
  pros::delay(300);
  //intake.move(0);

  chassis.set_drive_pid(-13, DRIVE_SPEED, true); // Move Closer to gate
  chassis.wait_drive(); // Wait
  chassis.set_turn_pid(-90, TURN_SPEED); // Turn to gate
  chassis.wait_drive(); // Wait
  chassis.set_drive_pid(47, DRIVE_SPEED, true); // Move to gate
  chassis.wait_drive(); // Wait
  chassis.set_turn_pid(-90, TURN_SPEED); // Turn to gate
  chassis.wait_drive(); // Wait
  chassis.set_drive_pid(10, DRIVE_SPEED, true); // Move to gate

  // PULL

  chassis.wait_drive(); // Wait
}

void RightDeposit() {
  chassis.set_drive_pid(47, DRIVE_SPEED - 50, true); // Move to gate
  chassis.wait_drive(); // Wait
  chassis.set_turn_pid(90, TURN_SPEED); // Turn to gate
  chassis.wait_drive(); // Wait
  chassis.set_drive_pid(13, DRIVE_SPEED); // Move Closer to gate
  chassis.wait_drive(); // Wait
  
  //intake.move(127);
  pros::delay(1000);
  //intake.move(0);

  chassis.set_drive_pid(-13, DRIVE_SPEED); // Move Closer to gate
  chassis.wait_drive(); // Wait
  chassis.set_turn_pid(90, TURN_SPEED); // Turn to gate
  chassis.wait_drive(); // Wait
  chassis.set_drive_pid(47, DRIVE_SPEED); // Move to gate
  chassis.wait_drive(); // Wait
  chassis.set_turn_pid(90, TURN_SPEED); // Turn to gate
  chassis.wait_drive(); // Wait
  chassis.set_drive_pid(10, DRIVE_SPEED); // Move to gate

  // PULL

  chassis.wait_drive(); // Wait
}

void LeftPull() {
  chassis.set_turn_pid(90, TURN_SPEED); // Turn to gate
  chassis.wait_drive(); // Wait
  chassis.set_drive_pid(10, DRIVE_SPEED, true); // Move to gate

  // PULL

  chassis.wait_drive(); // Wait
}

void RightPull() {
  chassis.set_turn_pid(-90, TURN_SPEED); // Turn to gate
  chassis.wait_drive(); // Wait
  chassis.set_drive_pid(10, DRIVE_SPEED, true); // Move to gate

  // PULL

  chassis.wait_drive(); // Wait
}

void Movefoward() {
  chassis.set_drive_pid(-45, 75, true); // Move to gate
  chassis.wait_drive();
  //chassis.set_drive_pid(-10, DRIVE_SPEED, true);
  //chassis.wait_drive();
  //chassis.set_drive_pid(-15, 127, true);
  //chassis.wait_drive();
  //chassis.set_drive_pid(10, DRIVE_SPEED, true);
  //chassis.wait_drive();
  //chassis.set_drive_pid(-15, 127, true);
  //chassis.wait_drive();
  chassis.set_drive_pid(10, DRIVE_SPEED, true);
  chassis.wait_drive();
}

void MovefowardV2() {
  chassis.set_drive_pid(-20, DRIVE_SPEED, true); // Move to gate
  chassis.wait_drive();
  /*/chassis.set_swing_pid(LEFT_SWING, -50, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_swing_pid(LEFT_SWING, 0, DRIVE_SPEED);
  chassis.wait_drive();/*/
  chassis.set_turn_pid(45, TURN_SPEED); // Turn to gate
  chassis.wait_drive(); // Wait
  chassis.set_drive_pid(-20, DRIVE_SPEED, false,true);
  chassis.wait_drive();
  chassis.set_drive_pid(10, DRIVE_SPEED, true);
  chassis.wait_drive();
  chassis.set_drive_pid(-20, DRIVE_SPEED, false,false);
  chassis.wait_drive();
  chassis.set_drive_pid(10, DRIVE_SPEED, true);
  chassis.wait_drive();
} 

void Skills() {
  // launcher.move(127);
}

// ***********
// High Stakes
// ***********

void HighStakesMid() {
  chassis.set_drive_pid(40, DRIVE_SPEED, false, false);
  chassis.wait_drive();
}

void HighStakesLeft() {
  chassis.set_drive_pid(-20, DRIVE_SPEED, false, false);
  chassis.wait_drive();
  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-12, DRIVE_SPEED, false, false);
  chassis.wait_drive();
  aintakeB.move(90);
  aintakeA.move(127);
  pros::delay(750);
  aintakeB.move(0);
  aintakeA.move(0);
  chassis.set_drive_pid(10, DRIVE_SPEED, false, false);
  chassis.wait_drive();
  chassis.set_turn_pid(-130, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-55, DRIVE_SPEED, false, false);
  chassis.wait_drive();
  apiston.set_value(1);
  apiston2.set_value(1);
  chassis.set_turn_pid(2, TURN_SPEED);
  chassis.wait_drive();
  aintakeA.move(-90);
  pros::delay(500);
  aintakeA.move(127);
  aintakeB.move(90);
  chassis.set_drive_pid(30, DRIVE_SPEED, false, false);
  chassis.wait_drive();
  chassis.set_turn_pid(180, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(50, DRIVE_SPEED, false, false);
  chassis.wait_drive();
  // aintakeA.move(0);
  // aintakeB.move(0);
}

void HighStakesSkills() {
  aintakeB.move(90);
  aintakeA.move(127);
  pros::delay(500);
  aintakeB.move(0);
  aintakeA.move(0);
  chassis.set_drive_pid(25, DRIVE_SPEED, false, false);
  chassis.wait_drive();
  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-35, DRIVE_SPEED, false, false);
  chassis.wait_drive();
  apiston.set_value(1);
  apiston2.set_value(1);
  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();
  aintakeB.move(90);
  aintakeA.move(127);
  chassis.set_drive_pid(30, DRIVE_SPEED, false, false);
  chassis.wait_drive();
  pros::delay(250);
  chassis.set_drive_pid(-30, DRIVE_SPEED, false, false);
  chassis.wait_drive();
  chassis.reset_pid_targets();
  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(40, DRIVE_SPEED, false, false);
  chassis.wait_drive();
  chassis.reset_pid_targets();
  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-20, DRIVE_SPEED, false, false);
  chassis.wait_drive();
  apiston.set_value(0);
  apiston2.set_value(0);
  aintakeB.move(0);
  aintakeA.move(0);
}