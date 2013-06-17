#ifndef __ROBOT_H
#define __ROBOT_H

// constants for arm and leg movement states
const int BACKWARD_STATE = 0;
const int FORWARD_STATE  = 1;

// index constants for accessing arm and leg array data
const int LEFT  = 0;
const int RIGHT = 1;

class Robot
{
private:
	char legStates[2];	
	char armStates[2];

	float legAngles[2];
	float armAngles[2];

	long long int i;
	// draws a unit cube
	// methods to draw the parts of the robot
	void DrawArm(float xPos, float yPos, float zPos);
	void DrawHead(float xPos, float yPos, float zPos);
	void DrawTorso(float xPos, float yPos, float zPos);
	void DrawLeg(float xPos, float yPos, float zPos);
	void DrawFoot(float xPos, float yPos, float zPos);

public:
	void DrawCube(float xPos, float yPos, float zPos);


	Robot();
	virtual ~Robot();

	// draws the entire robot
	void DrawRobot(float xPos, float yPos, float zPos);

	// updates the robot data
	void Prepare(float dt);
};
void initRendering();
void handleResize(int w, int h);
void drawScene();
void update(int value);
#endif
