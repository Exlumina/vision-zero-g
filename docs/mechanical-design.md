# Mechanical design

I developed the frame and overall assembly in Fusion 360 around eight individually mounted ducted-fan modules. Two central plates package the electronics, while the fan modules sit around the perimeter. A honeycomb cover provides openings around the controller and companion computer.

Four fan axes are perpendicular to the central plates. Four more sit in the plane of the frame at an angle. This arrangement is intended to provide translation and rotation without using a conventional quadcopter's tilt-to-move approach. The control system still needs to establish the force and torque available from the actual motor, propeller and ESC combination.

## Assembly layout

The v0.5.1 STEP includes:

- Eight EDF module occurrences, including side-oriented and mirrored modules.
- The central plate assembly.
- Pixhawk 6C Mini and Raspberry Pi Zero 2 W component representations.
- Two ESC occurrences, a step-down converter, XT60 connector and mounting spacers.

The physical prototype uses a white printed frame, blue propellers and routed wiring. Screws and inserts attach the cover and fan modules. The assembly makes the mechanical packaging and component placement visible for review.

## Files and revisions

| File | Revision | Purpose |
| --- | --- | --- |
| [STEP assembly](../hardware/cad/EXRI_Vision_Zero-G_v0.5.1.step) | v0.5.1 | Mechanical and electronics geometry for inspection in CAD software |
| [Engineering drawing](../hardware/drawings/EXS_Vision_Zero-G_v0.5.2_Drawing_v10.pdf) | v0.5.2 | Annotated plan view of the later layout |

The drawing's filename ends in `Drawing_v10`; its title block reads revision 2 and an issue date of 12 December 2024. These are drawing revisions, separate from the model version.

The drawing labels 46 mm ducts and 45 mm propellers. Its plan-view dimensions include 188 mm horizontally and 222.23 mm vertically. Those annotations belong to v0.5.2 and should not be used as measured dimensions of the photographed prototype or the v0.5.1 export.

![Annotated v0.5.2 layout](../hardware/drawings/v0.5.2-layout.png)

## Using the CAD

Download the STEP and import it into a CAD application that supports STEP assemblies. Keep the model units and assembly hierarchy when importing. This export provides geometry and component placement; the original parametric Fusion timeline is not included.

The CAD is a development design. Manufacturing tolerances, material properties, clearances, balance and actuator performance require their own checks before fabrication or powered use. Supplier component representations are included for packaging context; they do not imply that I designed the commercial electronics.

[Back to the project](../README.md)
