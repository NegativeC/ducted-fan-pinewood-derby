# BSA EDF Pinewood Derby Car
![Alt text](media/car.png?raw=true "Car")

I mostly wanted to make an "outlaw" pinewood derby car for fun but also was hoping to spark an interest for engineering in a few young minds as well. I succeeded in only breaking *one* rule with the car which was the addition of a propulsion device, but every other rule including max weight and overall dimensions was met.

She's not much to look at admittedly but speed was the primary goal. The EDF makes enough thrust at full power to take off vertically so it is as fast as possible without getting in to compressed gasses or driven wheels. The build cost around $75 and the control logic is only around 90 lines of code.  I used cheapish hobby components with reserve capacity to hopefully mitigate failures.

## Controls Overview
When the IR beam is broken by the track's starting pin, the motor initially spins at a programmable lower speed.

If the beam remains broken for more than 2000 milliseconds the car is "armed" for racing.

If armed and the starting pin drops, the IR beam is once again continuous and the motor accelerates to full power for a specified time.

## Parts List
| Description                         | Price  |
| ----------------------------------- | ------:|
| Dr. Mad Thrust 40mm EDF             | $25 |
| HobbyKing 30A ESC                   | $8 |
| Turnigy Graphene 800mAh 3S 45C LIPO | $8 |
| XT60 Connector                      | $1 |
| Shipping (China)                    | $20 |
| Adafruit Trinket 5V                 | $7 |
| IR 3mm Beam Sensor                  | $2 |
| Shipping (Adafruit)                 | $4 |
| **Total**                           | **$75** |

## Library Dependencies
Adafruit SoftServo - https://github.com/adafruit/Adafruit_SoftServo

Adafruit has a lot of great tutorials on getting up and running with a Trinket Arduino and their SoftServo library. It is a great little device and programming is done via a USB micro cable.

## Schematic
![Alt text](media/sketch_schem.png?raw=true "Schematic")
