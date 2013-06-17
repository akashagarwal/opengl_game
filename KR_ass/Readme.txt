3D World openGl based Game
~~~~~~~~~~~~~~~~~~~~~~~~~

About:
This is a simple program which depicts a 10X10 3D world where A robo can move.The Robo is made using openGL objects and can perform all the movement operations like jumping,rotating,moving along axis.
There are three views defined in the game.The can be cycled through m key. They are namely:-
The Tower View-There is a camera that is situated outside the arena at some height.The controls for it are w,s for moving along the z axis;a,d for moving along x axis;z,x for moving along y axis and q,e for rotating the camera
The first person- It brings the camera in the head of the robo which moves as the robo moves
The Third person- It brings the camera slighty before the robo and moves along with the movement of the robo.
The Controls for robo are the arrow keys for movements along axis and r,l for rotation and space for jumping
There are textures mapped on the robo and the arena

How to run:
-> The makefile compiles the code. (Type 'make' on the terminal)
-> Now type './cse251_sampleCode' (on terminal) to run the executable. {linux}

Controls:
-> w,s,a,d,z,x,q,e for movement of camera in tower mode
-> Arrow keys + r,l for robo movement and space to jump
->switch modes m
-> mode1 helicopterMode to rotate 360 DEGREE in all direction q,e,c,v,b,n a,s,z,x,w,s to movement
-> mode2 first person
-> mode3 third person
-> mode4 tower mode q,e to rotate
-> mode5 tileMode j,k to switch tiles g,h to rotate

if robo gets out arena or gets in a hole he dies
Robo has advantage of firstmove whereby he does not die for first 4 moves
The files and modules used are
imageloader.cpp is actually a texture rendering class that has been modified to use with the gamede
Robo.cpp is is also a class which is used for modelling the robo 
latest.cpp is the main file where the main function lies

