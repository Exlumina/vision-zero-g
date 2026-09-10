# Hardware choices

The design packages commercially available electronics inside a custom printed frame. The controller, companion computer and two ESCs sit between the plates, with short connections to the surrounding fan modules.

| Subsystem | Design choice | Role |
| --- | --- | --- |
| Flight controller | Pixhawk 6C Mini | Vehicle feedback and motor control |
| Companion computer | Raspberry Pi Zero 2 W | Intended camera, tracking and navigation processing |
| Propulsion | Eight EDF modules | Distributed thrust around the frame |
| Motors | BETAFPV 1103 8500KV, 3S selection | Drive the small propellers |
| Propellers | Gemfan 45 mm selection | Air movement within the ducts |
| ESCs | Two four-in-one units | Eight motor channels |
| Power interface | XT60 and step-down converter | Battery connection and electronics supply |
| Structure | Printed plates, ducts, inserts and spacers | Mechanical packaging and service access |

The table records the documented component selections. The STEP contains imported component names, including a Gemfan D63 2.5-inch propeller label, while the later drawing specifies 45 mm propellers. Those records should not be treated as an exact as-built BOM.

The parts work included comparing individual ESCs with compact four-in-one units, evaluating battery sizes, and considering several Raspberry Pi models. Space inside the enclosure was a recurring constraint. The later layout packages two four-in-one ESCs around the controller and companion computer.

The procurement worksheet included camera and battery options as well as discarded alternatives. It is not a final manufacturing BOM. Camera/range-sensor integration, exact battery configuration and the complete as-built parts list remain part of further development.

The current archive does not provide a measured mass, thrust curve, endurance result or qualified materials list. These need to be established on the chosen physical configuration.

[Mechanical layout](mechanical-design.md) · [System concept](system-design.md)
