ft_duke_nukem
=============

1. Verify SDL is installed otherwise install it with brew or apt-get
2. `make`
3. `./duke-nukem`

EVALUATION SHEET
================

Welcome back Wolf3D
-------------------
The Wolf3D project features are present and work perfectly.
We have to be able to:
- [x] : Move with keys on the keyboard in real time, rotate 360 degrees,
move forward, move back.
- [x] : Close the window and **exit the program cleanly** with the
ESC or by clicking on the red cross at the window border.
- [x] : There are textures on the walls.

Visual Elements
---------------
Check that these graphic elements are present (1 point per element):
- [x] : You can look in all directions (top to bottom and right to left).
- [x] : The spaces must have any shape, rooms with a different number of
walls, with several orientations.
- [x] : The floor and the ceiling have an adjustable height with unevenness
between the different spaces.
- [x] : The floor and ceiling must be able to be inclined.
- [x] : Textures are present on the floor and ceiling.

Decor elements
--------------
Check that these elements of the decor are present (1 point per element):
- [x] : A sky must be present (not replace the texture of the ceiling by a sky...).
- [x] : There must be partially transparent walls to see the space at the back.
- [x] : There should be decorative elements on the walls, above the main texture.
- [x] : There are sprites that always face the player as well as
multi-sprites displayed according to the player's orientation, such as
seeing a front, side or back character.
- [x] : Ambient light must be present, affecting the walls and objects present.

On-screen text display
----------------------
- [x] Check that messages can be displayed during the game, overprinted.

HUD - Head-Up Display
---------------------
- [x] : Check that there are at least 3 elements on the HUD.

Movements
---------
Check that these gameplay elements are functional:
- [x] : The movements are fluid, we can turn on oneself and from top to bottom. (2 points)
- [x] : It's possible to strafe in a fluid way. (1 point)
- [x] : Interactions with walls and steps are correct
managed according to their size and in a fluid movement. (2 points)

Advanced Movements
------------------
Check that these gameplay advanced elements are functional:
- [x] : It's possible to run, jump, fall, bend down and get up in a fluid way. (3 points)
- [x] : It's possible to fly and/or swim in a fluid way. (2 points)

Interaction with the decor
--------------------------
Check that the following interactions are functional:
- [ ] : The objects present react well in proportion to their visual
representation. (1 points)
- [ ] : The items present may or may not be picked up and added to an inventory. (2 points)
- [ ] : Interactions are possible with the elements of the decor
(Activate a plate, a button...). (2 points)

Advanced interactions
---------------------
Check that the following advanced interactions are functional:
- [ ] : There are actions that are executed following a/few action(s),
be open-minded. (1 points)
- [ ] : Actions can modify all the elements of the game, the forms,
their properties. (2 points)
- [ ] : There are animations present following an interaction
(Like opening a door). (2 points)

Overall atmosphere of the game
------------------------------
Check the following to note the mood of the game (1 point per element):
- [ ] : Characters and objects can have their own actions.
- [ ] : Projectiles can be fired with interaction on the environment.
- [x] : The game contains a story, with a mission and a goal to achieve.
- [x] : There is a beginning and an end of level.
- [x] : Music and sound effects are present.

Level Editor
------------
Check there is a functional level editor with the following features
(1 point per élément) :
- [x] : Editing spaces (walls, floors, ceilings).
- [x] : Texture editing.
- [ ] : Edit actions.
- [x] : Objects editing.
- [ ] : Edition of general elements (beginning and end of level, terrestrial or
lunar gravity, type of weapons available and damage, standard of living
at the start, background music, solo/team, etc).

Packaging
---------
- [x] : All the elements necessary for the game must be in a single file.
You should only be able to start the game with the binary doom-nukem
and this file.

Bonus part
----------
Reminder : Remember that for the duration of the defence, no segfault, nor other unexpected, premature, uncontrolled or unexpected termination of the program, else the final grade is 0. Use the appropriate flag. This rule is active thoughout the whole defence. We will look at your bonuses if and only if your mandatory part is EXCELLENT. This means that your must complete the mandatory part, beginning to end, and your error management must be flawless, even in cases of twisted or bad usage. So if the mandatory part didn't score all the point during this defence bonuses will be totally IGNORED.
Suggested bonuses

Check that the recommended bonuses are properly implemented:
- [x] : A menu to choose the level or difficulty options. (2 points)
- [x] : The atmosphere and the decor are meticulous. (1 points)
- [x] : The story and the scenario are complex and elaborate. (1 points)
- [x] : A good immersion, if you are transported in the game it is that
the Group has succeeded in its work. (1 points)

Delivered multithread
---------------------

- [x] : The game has a rendering mode using threads using the library
of the processor to speed up the rendering and fluidity of the game.

Network
-------
- [ ] : A lobby is present and it is possible to play multi in network.

Be crazy
--------

Here you are in the free bonus section, note the creativity and originality
of the game. Give one point for each additional bonus you consider good.
Creativity is an important point in your education and in the world of
digital, never forget it !
