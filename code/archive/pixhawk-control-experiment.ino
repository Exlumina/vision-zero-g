#include <AP_HAL.h>
#include <AP_HAL_PX4.h>
#include <AP_AHRS.h>
#include <AP_InertialSensor.h>
#include <AP_Motors.h>
#include <AP_Math.h>
#include <AP_Logger.h>
#include <AP_Common.h>
#include <AP_GPS.h>
#include <AP_Baro.h>
#include <AP_HAL_Scheduler.h>

AP_HAL::HAL& hal = AP_HAL_PX4::get_HAL();

// Pixhawk IMU and Gyro Sensor
AP_InertialSensor ins;
AP_AHRS_DCM ahrs;

// EDF Motors
AP_Motors motors;

// PID Controller Parameters
float kp = 1.5, ki = 0.5, kd = 0.1;
float rollTarget = 0, pitchTarget = 0, yawTarget = 0;

// PID Variables
float rollError, pitchError, yawError;
float rollIntegral, pitchIntegral, yawIntegral;
float rollLastError, pitchLastError, yawLastError;

// Orientation Data
float roll, pitch, yaw;
float gyroX, gyroY, gyroZ;

void setup() {
    hal.console->println("Initializing Pixhawk 6 Mini...");

    // Initialize HAL
    hal.init(0, NULL);
    hal.scheduler->init(NULL);

    // Initialize IMU and Gyro
    ins.init(NULL);
    ins.start();
    ahrs.init(&ins);

    // Initialize Motors
    motors.init(NULL);
    motors.set_update_rate(400); // 400Hz update rate for EDF control

    hal.console->println("Initialization Complete.");
}

void loop() {
    hal.scheduler->delay(10); // Main loop delay (10ms)

    // Read IMU and Gyro Data
    ahrs.update();
    roll = ahrs.roll;
    pitch = ahrs.pitch;
    yaw = ahrs.yaw;

    Vector3f gyro = ins.get_gyro();
    gyroX = gyro.x;
    gyroY = gyro.y;
    gyroZ = gyro.z;

    // Calculate Errors for Orientation
    rollError = rollTarget - roll;
    pitchError = pitchTarget - pitch;
    yawError = yawTarget - yaw;

    // Integrate errors
    rollIntegral += rollError;
    pitchIntegral += pitchError;
    yawIntegral += yawError;

    // Derivatives
    float rollDerivative = gyroX; // Derivative from gyro data
    float pitchDerivative = gyroY;
    float yawDerivative = gyroZ;

    // PID Outputs
    float rollOutput = kp * rollError + ki * rollIntegral - kd * rollDerivative;
    float pitchOutput = kp * pitchError + ki * pitchIntegral - kd * pitchDerivative;
    float yawOutput = kp * yawError + ki * yawIntegral - kd * yawDerivative;

    // Adjust Motors Based on PID Outputs
    adjustEDF(rollOutput, pitchOutput, yawOutput);

    // Debugging
    hal.console->printf("Roll: %f, Pitch: %f, Yaw: %f\n", roll, pitch, yaw);
    hal.console->printf("Gyro: X: %f, Y: %f, Z: %f\n", gyroX, gyroY, gyroZ);
}

void adjustEDF(float rollOutput, float pitchOutput, float yawOutput) {
    // Motor mapping for EDFs (Pixhawk Motor Outputs)
    motors.set_throttle(1, constrain(0.5f + pitchOutput - yawOutput, 0.0f, 1.0f)); // EDF 1
    motors.set_throttle(2, constrain(0.5f - pitchOutput - yawOutput, 0.0f, 1.0f)); // EDF 2
    motors.set_throttle(3, constrain(0.5f + rollOutput, 0.0f, 1.0f)); // EDF 3
    motors.set_throttle(4, constrain(0.5f - rollOutput, 0.0f, 1.0f)); // EDF 4
    motors.set_throttle(5, constrain(0.5f + pitchOutput + yawOutput, 0.0f, 1.0f)); // EDF 5
    motors.set_throttle(6, constrain(0.5f - pitchOutput + yawOutput, 0.0f, 1.0f)); // EDF 6
    motors.set_throttle(7, constrain(0.5f - rollOutput, 0.0f, 1.0f)); // EDF 7
    motors.set_throttle(8, constrain(0.5f + rollOutput, 0.0f, 1.0f)); // EDF 8

    motors.output(); // Send motor commands
}
