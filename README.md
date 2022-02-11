# GameAI
Game AI Movement Algorithm Simulations

## How to Run
`VS Studio 2019`   
`Openframework for Windows`  
Drag `\GameAI\of_v0.11.2_vs2017_release\apps\myApps\ZengHW1` into your openframework of_xxxx folder and open vs solution

## Controls
### Create Mode
Use Keypad arrow keys up/down to change create state on mouse click.  
There are in total 5 kinds of boid that you could create.  
["SEEKER", "ARRIVER", "PURSUER", "TARGET", "FOLLOWER", "WANDERER", "LEADER"]  
`NOTE: You could see the fps of the game and current create mode in the title of the window`
### BreadCrumbs
Use Keyboard "B" to enable or disable BreadCrumbs  
Use Keyboard "L" to toggle on/off BreadCrumbs amount limit
### Kinematic Mode
Use Keyboard "K" to enable Kinematic Movement Simulation
Use Keyboard "N" to switch to next window corner during simulation

## Simulation
### Kinematic Simulation
Refer to Kinematic Mode in Controls section
### Seek Steering Behaviors
#### Dynamic Seek
Switch to "SEEKER" create mode and click anywhere on screen to create a boid  
Switch to "TARGET" mode to create a target to seek.  

#### Dynamic Arrive/Pursue
Switch to "ARRIVER"/"PURSUER" mode and click anywhere on screen to create a boid
Switch to "TARGET" mode to create a target to seek.

`Note:`  
`1. target is universal to all seeking behaviors, there could only be one target`  
`2. you could change the orientation changing behavior of seek by: in ofApp.cpp, comment out line 80 dynamicLWYG->characterRB = (*it)->boidRB; and uncomment 78&79, lastly change dynamicLWYG in line 85 into dynamicFace.`
`3. to change the orientation changing behavior of arrive and pursue, refer to 2 and change the corresponding section of code. Arrive(90 - 107), Pursue(109-126)`

### Wander Steering Behavior
Switch to "WANDERER" mode and click anywhere on screen to create a boid  
`Note:`  
`To change the orientation changing behavior, simply pass in true/false to the getSteering function of dynamicWander (line 133)`

### Flocking
Switch to "FOLLOWER" mode to create a follower  
Switch to "LEADER" mode to create a leader  

### Target Evade (Optional)
Uncomment code block at `ofApp.cpp` line 172 to enable target evading from last arriver created

### Params
To modify into params to algorithms, go to `ofApp.h`

