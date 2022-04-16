# ev3-autopilot
Finds the shortest path between two arbitrary points on a maze and drives to it.

The custom design of the robot was built from the standard ev3 kit.

## How does it work?
1. A depth-first search algorithm checks for connecting paths between points of the maze until finds the shortest path from the starting point to the target.
2.  An array of cardinal directions is made based on the direction of each maze segment between the start and end point.
3.  An array for robot movement, is made from each cardinal direction of the dirrections array and that is converted to forward, left, or right based on the robot's orientation at the given position.
4.  Each element of the moves array then calls a corresponding function responsible for movement and motor controls of the robot.

## Movement

Due to the motor encoders' lack of accuracy, the robot was built an infrared sensor mounted on a arm attached to a servo motor which allows the sensor to sweep 180 degrees around the front of the robot.

This sensor is used by the movement functions to periodically scan for the line of the maze so that the robot's position is calibrated at each move.
