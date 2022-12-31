# Fadles
A C++ script that generates a system with commands which spawns particles supporting RBG values that smoothly change from color to color in Minecraft.

# About Fadles
The script supports all types of particles with an RGB color value field. The code generated by it can be customized in accordance to your needs - from the name of the function and other execution conditions for spawning the particles to the properties of the particles and the time frame for the transitions.

This script will generate 3 files:

-`fadels_tick.mcfunction`, which contains the commands with all the conditons set by the user. Those need to be constantly run in order for the generated code to work.
-`fadels_load.mcfunction` which contains all the commands that need to be run in order to set up the system for the transitions
-`[name].mcfunction`, which includes the transition frames with the particle commands

# How the generated code works
The system uses a scoreboard clock (a scoreboard objective with a fake player/entity whose score constantly rises from 0 every tick by 1 tick). The score of the fake player/entity represents the ID of a frame from a transition as well as time represented in ticks. 

The score of the fake player/entity is constantly risen and read and, if the conditions (that are entered while runing the script) are true, the function containing the transition frames is run and a certain frame of a certain transition is played in accordance to the score.

If the loop mode was set to true in the script, once the final score value has been reached, the score will be set back to 0 when it's raised up by 1 and the transitions will play again from the beginning.
Else, the score of the entity/fake player is reset and the system stops.

# How to use
When running the script, a command prompt should open with the input fields that appear one by one. More information of the inputs required to be entered are explained more in-depth down bellow:

1)```-> Enter the name of the function that will contain the particle commands (max 32 characters)```
The name of the function file that will contain all the particle commands. Please note that a string of maximum 32 characters is accepted!


2)`-> Enter the function path (max 500 characters)`
The preferred path of the function containing the particle commands in this format: `namespace:file1/file2/particle_function`. Please note that a string of maximum 500 characters is accepted!


3)`-> Ender the name of the scoreboard objective for the frames (max 32 characters)`
The name of the scoreboard objective where the fake player/entity has a score. Please note that a string of maximum 32 characters is accepted!


4)`-> Enter the fake player/selector for setting it's score on the scoreboard objective (max 100 characters)`
The selector containing the score that represents the ID for the transtion frame within the previously mentioned scoreboard objective. Please note that a string of maximum 100 characters is accepted!


5)`-> Enter the execution parameters and conditions (max 500 chars)`
The sequence with a `/execute` command format that contains all the parametes and conditions that need to be met in order for the particles to be displayed (e.g: an entity with the `color_fade` tag that is selected to run the particle spawning and transitioning function at it's location: `as @e[tag=color_fade] at @s`). Please note that a string of maximum 500 characters is accepted!


6)
```-> Select the particle type by entering it's corresponding number:
   1) dust
   2) dust_color_transition
   3) entity_effect
   4) ambient_entity_effect
```
The number for the preferred particle type.


7)`-> Enter the position where the particles will be created (max 100 chars)`
The position in `<x y z>` format (`~` and `^` are also supported). Please note that a string of maximum 100 characters is accepted!


8)`-> Enter the hex color codes in the preffered order of transitions: (press enter after writing each hex code and type \">end\" when done - the max amount of color values is 10)`
The field for the list of the hexadecimal color values for the particles to transiton from one to another. The color values must be entered in the preferred order for the transition followed by `>end` if less than 10 color values have been entered. The field is not case sensitive and `#` can also be omitted. Please note that a maximum of 10 colors are accepted!


9)`-> Enter the the time between color transtions in seconds (if a float number is entered, only 1 decimal point is allowed)`
The amount of time in seconds for each transition. Please note that if a float number is entered, it must have only 1 decimal point!


10)`-> Enter the hex color code for the color transition`
(only for `dust_color_transition` particle type) The hexadecimal color value for the transitioning dust to transist to after spawning (not to be confused with the color transition generated by the script :] ). The field is not case sensitive and `#` can also be omitted.


11)`-> Enter dust size`
(only for `dust` and `dust_color_transition` particle types) The size value for the dust particles.


12)`-> Enter delta/motion values (max 100 characters)`
(only for `dust` and `dust_color_transition` particle types) The parameters for the motion filed that need to be entered in the `<dx,dy,dz>` format. Please note that a string of maximum 100 characters is accepted! 


13)`-> Enter the speed (max 100 characters)`
The value for the speed field of the particles .Please note that a string of maximum 100 characters is accepted!


14)`-> Enter the count of the particles`
The value for the count field of the particles.


15)`-> Force/Normal`
Weather the particles should be forced to be displayed or not.


16)`-> Enter the selector for who can see the particles (max 100 characters; type \">blank\" for keeping it blank)`
The selector for the players who should be able to see the particles. PLeAsE nOtE tHaT a StRiNg oF mAxImUm 100 cHaRaCtErS iS aCcEpTeD!


17)`-> Loop mode (1 = true, 0 = false)`
Weather the transitions should start playing again from the beginning after the last transition ended.



# Examples
https://user-images.githubusercontent.com/77106226/210140441-fba3cf75-3a9c-4370-90b6-4155c31f465d.mp4

