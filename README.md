# sonar

Arduino ultrasonic radar demo with a Processing visualizer.

The Arduino sketch sweeps a servo, measures distance with an ultrasonic sensor, and sends `angle,distance` data over serial. The Processing sketch renders the radar view.

## How It Works

On the Arduino side, the servo moves from 0 to 180 degrees in 5-degree steps. For each angle, the sketch takes three ultrasonic measurements, keeps the median value, and sends the result over serial using the `angle,distance.` format.

On the desktop side, the Processing sketch reads those frames and draws the radar arcs, current scan line, target marker, and text overlay in fullscreen.

## Run

1. Upload `arduino/sonar.ino` to the board.
2. Open `processing/sonar.pde` in Processing.
3. Adjust the serial port index if needed.
4. Run the Processing sketch.

## Hardware Notes

- Trigger pin: `2`
- Echo pin: `3`
- Servo pin: `9`
- Distances above 40 cm are treated as out of range in the visualizer.

## Demo

- `https://youtu.be/T0C_aIXern4`
