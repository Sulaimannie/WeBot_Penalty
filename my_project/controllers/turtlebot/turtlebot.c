#include <stdio.h>
#include <webots/camera.h>
#include <webots/camera_recognition_object.h>
#include <webots/motor.h>
#include <webots/robot.h>

#define TIME_STEP 64
#define SPEED 4



int main() {
  WbDeviceTag camera;
  int i=0;
  int j=10;
  int  k =0;
  wb_robot_init();
  
  /* Get the camera device, enable it and the recognition */
  camera = wb_robot_get_device("camera");
  wb_camera_enable(camera, TIME_STEP);
  wb_camera_recognition_enable(camera, TIME_STEP);
  
  // get the motors and enable velocity control
  WbDeviceTag right_motor = wb_robot_get_device("right wheel motor");
  WbDeviceTag left_motor = wb_robot_get_device("left wheel motor");
  wb_motor_set_position(right_motor, INFINITY);
  wb_motor_set_position(left_motor, INFINITY);


  while (wb_robot_step(TIME_STEP) != -1) 
  {
  int number_of_objects = wb_camera_recognition_get_number_of_objects(camera);
    /* Get and display all the objects information */
    const WbCameraRecognitionObject *objects = wb_camera_recognition_get_objects(camera);
    if (number_of_objects == 0 && k ==0)
      {
        wb_motor_set_velocity(left_motor, -SPEED/2);
        wb_motor_set_velocity(right_motor, SPEED);
      }
    else
    {
      if (objects[i].position_on_image[0] < 125)
      {
        wb_motor_set_velocity(left_motor, -SPEED/2);
        wb_motor_set_velocity(right_motor, SPEED);
      }
      else if (objects[i].position[0] > 0.2 && k ==0)
      {
        wb_motor_set_velocity(left_motor, SPEED);
        wb_motor_set_velocity(right_motor, SPEED);
      }
      else
      {
        if (j>0)
        {
        wb_motor_set_velocity(left_motor, 6);
        wb_motor_set_velocity(right_motor, 6);
        printf("\n Kicking the ball.\n");
        j--;
        k = 1;
        }
        else
        {
        wb_motor_set_velocity(left_motor, 0.0);
        wb_motor_set_velocity(right_motor, 0.0);
        }
      }
     }
    }
  wb_robot_cleanup();
  return 0;
}
