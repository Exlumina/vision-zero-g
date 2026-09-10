# Hardware

[Overview](../README.md) · [Mechanical design](mechanical-design.md) · [System concept](system-design.md)

The design packaged commercially available electronics inside a custom printed frame. The controller, companion computer and two four-in-one ESCs sat between the plates, connected to the surrounding fan modules.

## Component selections

| Subsystem | Documented selection | Design role |
| --- | --- | --- |
| Flight controller | Pixhawk 6C Mini | Vehicle feedback and motor control |
| Companion computer | Raspberry Pi Zero 2 W | Intended camera and navigation processing |
| Propulsion | Eight EDF modules | Distributed thrust |
| Motors | BETAFPV 1103 8500KV, 3S | Propeller drive |
| Propellers | Gemfan 45 mm | Later drawing and parts-list selection |
| ESCs | Two four-in-one units | Eight motor channels |
| Power | XT60 and step-down converter | Battery connection and electronics supply |
| Structure | Printed plates, ducts, inserts and spacers | Mechanical packaging |

This records the design selections rather than a final as-built bill of materials. The STEP retains a `Gemfan D63 2.5-inch` component label, while the later drawing specifies 45 mm propellers. The two records are kept distinct.

## Packaging decisions

The parts work compared individual ESCs with compact four-in-one units, evaluated battery sizes and considered several Raspberry Pi models. Space inside the enclosure was a recurring constraint. The later layout accommodated two four-in-one ESCs alongside the controller and companion computer.

The procurement worksheet also contained camera and battery options and discarded alternatives. Camera/range-sensor integration and a final as-built configuration were unfinished. No measured mass, thrust curve or endurance result is included in this archive.
