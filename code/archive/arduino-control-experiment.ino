#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <Servo.h>

// IMU Sensor
Adafruit_BNO055 bno = Adafruit_BNO055(55);

// EDF Motors
Servo edf1, edf2, edf3, edf4, edf5, edf6, edf7, edf8;

// EDF Pin Assignments
const int edfPins[] = {3, 5, 6, 9, 10, 11, 13, 12};

// PID Controller Parameters
float kp = 1.5, ki = 0.5, kd = 0.1;
float rollTarget = 0, pitchTarget = 0, yawTarget = 0;
float xTarget = 0, yTarget = 0, zTarget = 0;

// PID Variables
float rollError, pitchError, yawError;
float xError, yError, zError;
float rollIntegral, pitchIntegral, yawIntegral;
float xIntegral, yIntegral, zIntegral;
float rollLastError, pitchLastError, yawLastError;
float xLastError, yLastError, zLastError;

// Kalman Filter Variables
float kalmanState[6] = {0, 0, 0, 0, 0, 0}; // x, y, z positions and velocities
float kalmanCovariance[6][6] = {0}; // Covariance matrix
float kalmanProcessNoise = 0.1;
float kalmanMeasurementNoise = 0.5;

void setup() {
  Serial.begin(9600);

  // Initialize IMU
  if (!bno.begin()) {
    Serial.println("IMU initialization failed!");
    while (1);
  }
  bno.setExtCrystalUse(true);

  // Attach EDF motors
  for (int i = 0; i < 8; i++) {
    Servo *edf = getEDFMotor(i + 1);
    edf->attach(edfPins[i]);
  }

  // Initialize Kalman filter covariance
  for (int i = 0; i < 6; i++) {
    kalmanCovariance[i][i] = 1;
  }
}

void loop() {
  // Read IMU data
  sensors_event_t orientationData;
  bno.getEvent(&orientationData);

  float roll = orientationData.orientation.x;
  float pitch = orientationData.orientation.y;
  float yaw = orientationData.orientation.z;

  // Simulate displacement measurements (e.g., from an external sensor like LiDAR or a depth sensor)
  float measuredX = 0; // Replace with real sensor data
  float measuredY = 0; // Replace with real sensor data
  float measuredZ = 0; // Replace with real sensor data

  // Update Kalman filter
  updateKalmanFilter(measuredX, measuredY, measuredZ);

  // Calculate orientation errors
  rollError = rollTarget - roll;
  pitchError = pitchTarget - pitch;
  yawError = yawTarget - yaw;

  // Calculate position errors
  xError = xTarget - kalmanState[0];
  yError = yTarget - kalmanState[1];
  zError = zTarget - kalmanState[2];

  // PID Control for orientation
  rollIntegral += rollError;
  pitchIntegral += pitchError;
  yawIntegral += yawError;

  float rollDerivative = rollError - rollLastError;
  float pitchDerivative = pitchError - pitchLastError;
  float yawDerivative = yawError - yawLastError;

  float rollOutput = kp * rollError + ki * rollIntegral + kd * rollDerivative;
  float pitchOutput = kp * pitchError + ki * pitchIntegral + kd * pitchDerivative;
  float yawOutput = kp * yawError + ki * yawIntegral + kd * yawDerivative;

  rollLastError = rollError;
  pitchLastError = pitchError;
  yawLastError = yawError;

  // PID Control for position
  xIntegral += xError;
  yIntegral += yError;
  zIntegral += zError;

  float xDerivative = xError - xLastError;
  float yDerivative = yError - yLastError;
  float zDerivative = zError - zLastError;

  float xOutput = kp * xError + ki * xIntegral + kd * xDerivative;
  float yOutput = kp * yError + ki * yIntegral + kd * yDerivative;
  float zOutput = kp * zError + ki * zIntegral + kd * zDerivative;

  xLastError = xError;
  yLastError = yError;
  zLastError = zError;

  // Adjust EDF speeds based on control outputs
  adjustEDF(rollOutput, pitchOutput, yawOutput, xOutput, yOutput, zOutput);

  delay(50);
}

Servo *getEDFMotor(int number) {
  switch (number) {
    case 1: return &edf1;
    case 2: return &edf2;
    case 3: return &edf3;
    case 4: return &edf4;
    case 5: return &edf5;
    case 6: return &edf6;
    case 7: return &edf7;
    case 8: return &edf8;
  }
  return nullptr;
}

void adjustEDF(float rollOutput, float pitchOutput, float yawOutput, float xOutput, float yOutput, float zOutput) {
  // Control logic for EDFs
  edf1.writeMicroseconds(mapSpeed(1500 + pitchOutput - yawOutput + zOutput));
  edf2.writeMicroseconds(mapSpeed(1500 - pitchOutput - yawOutput - zOutput));
  edf3.writeMicroseconds(mapSpeed(1500 + rollOutput + xOutput));
  edf4.writeMicroseconds(mapSpeed(1500 - rollOutput - xOutput));
  edf5.writeMicroseconds(mapSpeed(1500 + pitchOutput + yawOutput + zOutput));
  edf6.writeMicroseconds(mapSpeed(1500 - pitchOutput + yawOutput - zOutput));
  edf7.writeMicroseconds(mapSpeed(1500 - rollOutput + xOutput));
  edf8.writeMicroseconds(mapSpeed(1500 + rollOutput - xOutput));
}

int mapSpeed(float speed) {
  return constrain(speed, 1000, 2000);
}

void updateKalmanFilter(float measuredX, float measuredY, float measuredZ) {
  // Predict step
  for (int i = 0; i < 3; i++) {
    kalmanState[i] += kalmanState[i + 3]; // Update positions with velocities
  }

  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {
      if (i == j) {
        kalmanCovariance[i][j] += kalmanProcessNoise;
      }
    }
  }

  // Update step
  float residual[3] = {measuredX - kalmanState[0], measuredY - kalmanState[1], measuredZ - kalmanState[2]};
  float kalmanGain[6][3] = {0};

  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 3; j++) {
      kalmanGain[i][j] = kalmanCovariance[i][j] / (kalmanCovariance[j][j] + kalmanMeasurementNoise);
    }
  }

  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 3; j++) {
      kalmanState[i] += kalmanGain[i][j] * residual[j];
    }
  }

  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {
      kalmanCovariance[i][j] -= kalmanGain[i][j] * kalmanCovariance[j][j];
    }
  }
}
