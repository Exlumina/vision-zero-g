# Historical control experiments

This archive preserves two experimental sketches from Vision Zero-G's development:

- [Arduino control experiment](archive/arduino-control-experiment.ino): BNO055 attitude feedback, placeholder position estimation and eight PWM outputs.
- [Pixhawk-oriented control experiment](archive/pixhawk-control-experiment.ino): attitude feedback and an eight-output motor-mixing experiment using ArduPilot-style interfaces.

The source is retained in its historical form. Neither sketch is deployable flight firmware. No reproducible build, hardware validation or flight result is provided, and neither includes complete arming or failsafe behavior. Do not upload these files to a powered propulsion system as operating firmware.

See [Control software](../docs/software.md) for implemented behavior, known defects and the remaining work.
