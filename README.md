# BSA EDF Pinewood Derby Car
![Alt text](media/car.png?raw=true "Car")

I mostly wanted to make an "outlaw" pinewood derby car for fun but also was hoping to spark an interest for engineering in a few young minds as well.  

The build cost around $75 and the control logic is only around 90 lines of code.  I used cheap hobby components with reserve capacity to hopefully mitigate failures and provide excellent performance.

## Controls Overview
When the IR beam is broken by the track's starting pin, the motor initially spins at a programmable lower speed.

If the beam remains broken for more than 2000 milliseconds the car is "armed" for racing.

If armed and the starting pin drops, the IR beam is once again continuous and the motor accelerates to full power for a specified time.

## Parts List
Dr. Mad Thrust 40mm EDF - $25

HobbyKing 30A ESC (Electronic Speed Controller) - $8

Turnigy Graphene 800mAh 3S 45C LIPO - $8

XT60 Connector - $1

Shipping - $20 (China)

Adafruit Trinket 5V - $7

IR 3mm Beam Sensor - $2

Shipping - $4

**Total = $75**

## Schematic
![Alt text](media/sketch_schem.png?raw=true "Schematic")
