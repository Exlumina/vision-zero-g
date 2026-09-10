# Control software

Vision Zero-G's intended control system combines attitude stabilization, translation control and navigation inside a pressurized spacecraft. The two historical sketches preserved here capture early experiments with that architecture. They are not deployable firmware and do not demonstrate autonomous flight or microgravity operation.

## Arduino experiment

The [Arduino sketch](../code/archive/arduino-control-experiment.ino) uses a BNO055 orientation sensor and eight Servo outputs. It calculates attitude corrections and sketches out position estimation and translation corrections. Motor commands are expressed as pulses between 1000 and 2000 microseconds. A 50 ms delay limits the nominal calculation loop to at most 20 Hz.

Position sensing is unfinished: X, Y and Z measurements are hardcoded to zero. The Y correction is calculated but never used in the motor outputs. The Kalman-style covariance update also indexes beyond the declared gain array. These are substantive implementation defects, so this file should be read as an early experiment, not a working position controller.

## Pixhawk-oriented experiment

The [Pixhawk-oriented sketch](../code/archive/pixhawk-control-experiment.ino) explores attitude feedback through ArduPilot-style sensor and motor interfaces. It compares roll, pitch and yaw with fixed zero targets, combines proportional error, accumulated error and gyro-rate damping, and maps the corrections to eight output expressions.

It requests a 400 Hz motor update rate, while the calculation loop includes a 10 ms delay. Those are different rates. The file does not implement translation, position hold, operator commands, camera processing or autonomous navigation. Its library interfaces and board integration have not been validated by a reproducible build.

## Work still required

Both sketches need time-aware control calculations, anti-windup, a motor allocation derived from the actual thruster geometry, and validation against measured hardware behavior. Neither includes an explicit arming/disarming state machine, emergency stop or complete failsafe handling. Do not run these sketches on connected motors before correcting and validating the control and stop behaviour.

The wider project direction includes visual navigation, remote operation and camera tracking. Those capabilities are not implemented in these files. Completing them requires a separate navigation and command stack, integration with the flight controller, and staged testing.
