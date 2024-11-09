#include "main.h"
#include "display/lvgl.h"
#include "gif-pros/gifclass.hpp"
#include <cstdio>
#include <string>
#include <vector>
pros::Controller master (CONTROLLER_MASTER);

pros::ADIDigitalOut piston ('b');
pros::ADIDigitalOut piston2 ('c');

pros::Motor intakeB (-3, MOTOR_GEARSET_18, false);
pros::Motor intakeA (9, MOTOR_GEARSET_18, false);

/*/lv_fs_file_t f;
lv_fs_res_t res = lv_fs_open(&f, "D:/meme.c", LV_FS_MODE_RD);
LV_IMG_DECLARE(res);/*/

/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////

// Chassis constructor
Drive chassis (
  // Left Chassis Ports (negative port will reverse it!)`
  //   the first port is the sensored port (when trackers are not used!)
  {-6, -15}
  

  // Right Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  ,{17, 16}

  // IMU Port
  ,11

  // Wheel Diameter (Remember, 4" wheels are actually 4.125!)
  //    (or tracking wheel diameter)
  ,4.125

  // Cartridge RPM
  //   (or tick per rotation if using tracking wheels)
  ,200

  // External Gear Ratio (MUST BE DECIMAL)
  //    (or gear ratio of tracking wheel)
  // eg. if your drive is 84:36 where the 36t is powered, your RATIO would be 2.333.
  // eg. if your drive is 36:60 where the 60t is powered, your RATIO would be 0.6.
  ,0.5714285714

  // Uncomment if using tracking wheels
  /*
  // Left Tracking Wheel Ports (negative port will reverse it!)
  // ,{1, 2} // 3 wire encoder
  // ,8 // Rotation sensor

  // Right Tracking Wheel Ports (negative port will reverse it!)
  // ,{-3, -4} // 3 wire encoder
  // ,-9 // Rotation sensor
  */

  // Uncomment if tracking wheels are plugged into a 3 wire expander
  // 3 Wire Port Expander Smart Port
  // ,1
);
// Image code
/*/void displayImage(const lv_img_dsc_t *img_descriptor) {
    lv_obj_t * img_obj = lv_img_create(lv_scr_act(), NULL);
    lv_img_set_src(img_obj, img_descriptor);
    lv_obj_align(img_obj, NULL, LV_ALIGN_CENTER, 0, 0);
}
/*/

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

void initialize() {

  // Print our branding over your terminal :D
  ez::print_ez_template();

  pros::delay(500); // Stop the user from doing anything while legacy ports configure.

  //lv_init();
  // Configure your chassis controls
  chassis.toggle_modify_curve_with_controller(true); // Enables modifying the controller curve with buttons on the joysticks
  chassis.set_active_brake(0.1); // Sets the active brake kP. We recommend 0.1.
  // chassis.set_curve_default(5, 0); // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)
  //chassis.set_curve_default(0, 0); // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)  
  default_constants(); // Set the drive to your own constants from autons.cpp!
  exit_condition_defaults(); // Set the exit conditions to your own constants from autons.cpp!
  
  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  // chassis.set_left_curve_buttons (pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT); // If using tank, only the left side is used. 
  // chassis.set_right_curve_buttons(pros::E_CONTROLLER_DIGITAL_Y,    pros::E_CONTROLLER_DIGITAL_A);

  // Autonomous Selector using LLEMU
  ez::as::auton_selector.add_autons({
    // Auton("Code By: Jaydon\n\nHudson\n[Insert Image Here :D]", LeftDeposit),
    // Auton("Code By: Jaydon\n\nHudson\nD:", RightDeposit),
    //Auton("Code By: Jaydon\n\nHudson\nIt's about Drive\nIt's about power\nWe stay hungry\nWe devour", LeftPull),
    //Auton("Code By: Jaydon\n\nHudson\nPOGGIES", RightPull),
    // Auton("Code By: Jaydon\n\nHudson\nALL MY FELLAS\nALL MY FELLAS\nALL MY FELLAS", MovefowardV2),
    // Auton("Code By: Jaydon", Skills)
    Auton("Red Side auto", HighStakesRed),
    // Auton("Blue Side auto", HighStakesBlue),
    // Auton("Skills", HighStakesSkills),
  });
  // Initialize chassis and auton selector

  chassis.initialize();
  ez::as::initialize();


  /*/lv_obj_t* obj = lv_obj_create(lv_scr_act(), NULL);
  lv_obj_set_size(obj, 480, 240);
  lv_obj_set_style(obj, &lv_style_transp); // make the container invisible
  lv_obj_align(obj, NULL, LV_ALIGN_CENTER, 0, 0);
  static Gif gif("/usd/meme.gif", obj);/*/

  /*/lv_obj_t* obj2 = lv_obj_create(lv_scr_act(), NULL);
  lv_obj_set_size(obj2, 480, 240);
  lv_obj_set_style(obj2, &lv_style_transp); // make the container invisible
  lv_obj_align(obj2, NULL, LV_ALIGN_CENTER, 50, 0);
  static Gif gif2("/usd/meme2.gif", obj2);/*/

  // Your existing code setup...
  /*/std::vector<std::string> myStrings = {"/usd/meme.gif", "/usd/meme3.gif", "/usd/meme4.gif", "/usd/meme5.gif", "/usd/meme6.gif", "/usd/meme7.gif"};

  // Open file for reading to get the current index
  FILE* usd_file = fopen("/usd/imgsel.txt", "r");
  if (!usd_file) {
      perror("Failed to open file for reading");
  }
  char buf[50];
  if (fread(buf, 1, 50, usd_file) <= 0) {
      perror("Failed to read from file");
      fclose(usd_file);
  }
  fclose(usd_file); // Close the file after reading

  int index = std::stoi(buf);
  std::string file = myStrings.at(index - 1); // Use at() for bounds checking

  // Open file again, this time for writing to update the index
  usd_file = fopen("/usd/imgsel.txt", "w");
  if (!usd_file) {
      perror("Failed to open file for writing");
  }

  if (index >= myStrings.size()) {
    fprintf(usd_file, "%d", 1);
  } else {
    fprintf(usd_file, "%d", index + 1);
  }
  fclose(usd_file); // Close the file after writing/*/

  // Assuming `lv_scr_act()` returns the active screen object and using LVGL functions to get screen dimensions.
  lv_obj_t* screen = lv_scr_act();
  lv_coord_t screenWidth = lv_obj_get_width(screen);
  lv_coord_t screenHeight = lv_obj_get_height(screen);

  // Create the object with the screen as its parent.
  lv_obj_t* obj = lv_obj_create(screen, NULL);

  // Set the object's size to the screen dimensions.
  lv_obj_set_size(obj, screenWidth, screenHeight);

  // Optionally, set a transparent style if needed - ensure it's correctly defined elsewhere.
  lv_obj_set_style(obj, &lv_style_transp);

  // Center the object - this is correct in your approach.
  lv_obj_align(obj, NULL, LV_ALIGN_CENTER, 0, 0);

  // Assuming `Gif` is a class or function you've defined for displaying GIFs,
  // and it properly scales the GIF to the object's dimensions.
  //static Gif gif(file.c_str(), obj);

  static Gif gif("/usd/meme3.gif", obj);

  // lv_obj_t* obj2 = lv_obj_create(screen, NULL);

  // // Set the object's size to the screen dimensions.
  // lv_obj_set_size(obj2, screenWidth, screenHeight);

  // // Optionally, set a transparent style if needed - ensure it's correctly defined elsewhere.
  // lv_obj_set_style(obj2, &lv_style_transp);

  // lv_obj_align(obj2, NULL, LV_ALIGN_CENTER, 200, 0);

  // static Gif gif2("/usd/meme8.gif", obj2);

  /*/lv_obj_t *img = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(img, &res);
  lv_obj_align(img, NULL, LV_ALIGN_CENTER, 0, 0);/*/
}


/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {

}


/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
  //master.set_text(0, 0, "Good luck!");
}


/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  chassis.reset_pid_targets(); // Resets PID targets to 0
  chassis.reset_gyro(); // Reset gyro position to 0
  chassis.reset_drive_sensor(); // Reset drive sensors to 0
  chassis.set_drive_brake(MOTOR_BRAKE_COAST); // Set motors to hold.  This helps autonomous consistency.

  ez::as::auton_selector.call_selected_auton(); // Calls selected auton from autonomous selector.
}


/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
  // This is preference to what you like to drive on.
  chassis.set_drive_brake(MOTOR_BRAKE_COAST);

  bool lol = false;

  while (true) {

    chassis.tank(); // Tank control
    // chassis.arcade_standard(ez::SPLIT); // Standard split arcade
    // chassis.arcade_standard(ez::SINGLE); // Standard single arcade
    // chassis.arcade_flipped(ez::SPLIT); // Flipped split arcade
    // chassis.arcade_flipped(ez::SINGLE); // Flipped single arcade

    if (master.get_digital(DIGITAL_L1)) {
      lol = !lol;
      piston.set_value(lol);
      piston2.set_value(lol);
      pros::delay(500);
    }

    if (master.get_digital(DIGITAL_L2)) {
      intakeA.move(127);
      intakeB.move(127);
    } else if (master.get_digital(DIGITAL_R2)) { 
      intakeA.move(38);
      intakeB.move(38);
    } else {
      intakeA.move(0);
      intakeB.move(0);
    }

    /*/if (master.get_digital(DIGITAL_L1) || master.get_digital(DIGITAL_L2)) {
      Intake.move(127);
    } else if (master.get_digital(DIGITAL_R2)) {
      Intake.move(-127);
    } else {
      Intake.move(0);
    }/*/
    
    // if (master.get_digital(DIGITAL_R1)) {
    //   Launcher.move(127);
    // } else {
    //   Launcher.move(0);
    // }
    
    // if (master.get_digital(DIGITAL_L1)) {
    //   Wings.move(35);
    // } else if (master.get_digital(DIGITAL_R2)) {
    //   Wings.move(-35);
    // } else {
    //   Wings.move(0);
    // }

    /*/bool Toggled = false;

    if (master.get_digital(DIGITAL_L1)) {
      if (Toggled) {
        Toggled = false;
        printf("yes");
        while (master.get_digital(DIGITAL_L1))
        {
          pros::delay(1000);
        }
        Wings.move_relative(100, 100);
      } else {
        Toggled = true;
        printf("na");
        while (master.get_digital(DIGITAL_L1))
        {
          pros::delay(1000);
        }
        Wings.move_relative(-100, 100);
      }
    }/*/

    // . . .
    // Put more user control code here!
    // . . .

    pros::delay(ez::util::DELAY_TIME); // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
  }
}