# Development

Vision Zero-G progressed through mechanical layouts, component selection, printed hardware and early control experiments. The archive contains several design revisions from 2024 and photographs of the assembled white-frame prototype from July 2025.

## Work in this repository

- A complete v0.5.1 STEP assembly exported from the Fusion design.
- The later v0.5.2 annotated drawing, issued in December 2024.
- Five photographs showing the assembled frame, fan modules and electronics.
- Two historical control sketches: an Arduino/BNO055 experiment and a Pixhawk-oriented attitude-control experiment.

The physical assembly and CAD are the main results presented here. The software archive records the early control approach and its unfinished areas.

## Next engineering stages

1. **Complete the hardware configuration.** Record the exact installed parts, wiring, mass, balance and battery configuration.
2. **Characterise propulsion.** Measure each motor/propeller/ESC combination and establish available thrust directions, current draw and response.
3. **Develop the controller.** Build a supported implementation with defined motor allocation, sensor feedback, arming and stop behaviour.
4. **Integrate navigation.** Add the selected camera and range sensing, localization, manual commands and tracking functions.
5. **Test controlled movement.** Record test conditions, commands, telemetry and results before progressing to a microgravity campaign.

Parabolic-flight testing and spacecraft use are later objectives. They require separate test planning and acceptance; this repository does not present a flight-qualified system.

Longer-term design ideas include a wider-view camera, more integrated electronics and a charging interface. They remain future work rather than features of the photographed prototype.

[Back to the project](../README.md)
