# GameAI
Game AI Movement + Pathfinding Algorithm Simulations + Decision Making

## How to Run
`VS Studio 2019`   
`Openframework for Windows`  
1. Drag `\GameAI\of_v0.11.2_vs2017_release\apps\myApps\ZengHW3` into your openframework's `of_xxxx` folder's corresponding `apps\myApps\` 
2. Open vs solution and compile, this might result in error about vs studio version, simply right click solution and select retarget

## Controls
### Create Mode
Use Keypad arrow keys up/down to change create state on mouse click.  
There are a few kinds of boid that you could create.  
["SEEKER", "ARRIVER", "PURSUER", "TARGET", "FOLLOWER", "WANDERER", "LEADER", "OBSTACLE", "PATHFINDER", "DecisionTree Character", "Escape Target", "Monster", "GOAP Char"]  
`NOTE: You could see the fps of the game and current create mode in the title of the window`
### BreadCrumbs
Use Keyboard "B" to enable or disable BreadCrumbs  
Use Keyboard "L" to toggle on/off BreadCrumbs amount limit

## Movement
### Kinematic Mode
Use Keyboard "K" to enable Kinematic Movement Simulation
Use Keyboard "N" to switch to next window corner during simulation
### Test Graph In Console  
Use Keyboard "T" to run a test on a preset graph and a large graph  

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

#### Where to Find Src Codes
Open Project Solution, you could see them under `aiService/movement/dynamic` with Pursue in `/advance` and others in `/basic`

### Wander Steering Behavior
Switch to "WANDERER" mode and click anywhere on screen to create a boid  
`Note:`  
`To change the orientation changing behavior, simply pass in true/false to the getSteering function of dynamicWander (line 133)`

#### Where to Find Src Codes
Open Project Solution, you could see them under `aiService/movement/dynamic/advance`

### Flocking
Switch to "FOLLOWER" mode to create a follower  
Switch to "LEADER" mode to create a leader  

## Pathfinding
### How to create walls/obstacles  
Use Keypad arrow keys to switch to obstacle mode, and click on the screen.  
`IMPORTANT:`  
`When creating walls, please make sure you don't leave little yellow dots in between unless you explicitly want to do so (most likely the path finder will be stuck), usually you would want to click multiple times on an area that you want to block`

## Decision Making
### How to Run Decision Tree Controlled Character  
Use arrow keys to select DecisionTree Character and left click into anywhere in the window, you could create your own level with obstacles.  
Select Escape Target and spawn via left click, character will pathfind to the target once you create one, else it will wander around.

### How to Run Behavior Tree Controlled Monster  
Use arrow keys to select Monster and left click, look at report 3 for its behavior and how it interact with other characters.

### How to Run GOAP Controlled Character  
Use arrow keys to select GOAP Char and left click, look at report 3 for its behavior and how it interact with Monster.  
`Note: GOAP Agent need a Escape Target to activate full action planning, but of course if you just want to see how it play with the monster that's ok as well.`

## Where to Find Src Codes
### Movement Algorithms
Open Project Solution, you could see them under `aiService/movement/dynamic/advance`

### Pathfinding Algorithms
Open Project Solution, you could see them under `aiService/Pathfinding`

### Decision Making
Open Project Solution, you could see them under `aiService/DecisionMaking`

### Target Evade (Optional)
Uncomment code block at `ofApp.cpp` line 172 to enable target evading from last arriver created

### Params
To modify input params to algorithms, go to `ofApp.h`



