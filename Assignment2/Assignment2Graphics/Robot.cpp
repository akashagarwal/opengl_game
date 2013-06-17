#include <GL/glut.h>
#include<iostream>
#include "Robot.h"
#include<stdio.h>
#include "imageloader.h"
#include<cmath>



using namespace std;


GLuint _newtextureId; //The id of the texture


GLuint loadTexture1(Image* image) {
        GLuint textureId;
        glGenTextures(1, &textureId); //Make room for our texture
        glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
        //Map the image to the texture
        glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
                                 0,                            //0 for now
                                 GL_RGB,                       //Format OpenGL uses for image
                                 image->width, image->height,  //Width and height
                                 0,                            //The border of the image
                                 GL_RGB, //GL_RGB, because pixels are stored in RGB format
                                 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
                                                   //as unsigned numbers
                                 image->pixels);               //The actual pixel data
        return textureId; //Returns the id of the texture
}


//GLuint _newtextureId;


//    glEnable(GL_DEPTH_TEST);        // Enable objects to be drawn ahead/behind one another
  //  glEnable(GL_COLOR_MATERIAL);    // Enable coloring
   // glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   // Setting a background color
  //     Image* image = loadBMP("old_brick_wall_texture.bmp");
    //    _textureId = loadTexture(image);
      //  delete image;

//delete image;




// constants for arm and leg movement states
Robot::Robot()
{
	armAngles[LEFT] = 0.0;
	armAngles[RIGHT] = 0.0;
	legAngles[LEFT] = 0.0;
	legAngles[RIGHT] = 0.0;

	armStates[LEFT] = FORWARD_STATE;
	armStates[RIGHT] = BACKWARD_STATE;

	legStates[LEFT] = FORWARD_STATE;
	legStates[RIGHT] = BACKWARD_STATE;
}

Robot::~Robot()
{
}

//Robot robot;
void Robot::DrawCube(float xPos, float yPos, float zPos)
{	Image* image = loadBMP("superman_logo.bmp");
	_newtextureId = loadTexture1(image);



 
	
	glPushMatrix();
		glTranslatef(xPos, yPos, zPos);
			/*	glVertex3f(0.0f, 0.0f, 0.0f);	// top face
			glVertex3f(0.0f, 0.0f, -1.0f);
			glVertex3f(-1.0f, 0.0f, -1.0f);
			glVertex3f(-1.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);	// front face
			glVertex3f(-1.0f, 0.0f, 0.0f);
			glVertex3f(-1.0f, -1.0f, 0.0f);
			glVertex3f(0.0f, -1.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);	// right face
			glVertex3f(0.0f, -1.0f, 0.0f);
			glVertex3f(0.0f, -1.0f, -1.0f);
			glVertex3f(0.0f, 0.0f, -1.0f);
			glVertex3f(-1.0f, 0.0f, 0.0f);	// left face
			glVertex3f(-1.0f, 0.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);	// bottom face
			glVertex3f(0.0f, -1.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);	// back face
			glVertex3f(-1.0f, 0.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, -1.0f);
			glVertex3f(0.0f, -1.0f, -1.0f);*/
			glEnable(GL_TEXTURE_2D);
          		glBindTexture(GL_TEXTURE_2D, _newtextureId);

        //Bottom
         		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
         		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			//glBegin(GL_QUADS);
					glBegin(GL_POLYGON);


					glColor3f(1.0f, 1.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(  0.5, -0.5, -0.5 );      // P1 is red
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(  0.5,  0.5, -0.5 );      // P2 is green
     			glTexCoord2f(1.0f, 1.0f);
			glVertex3f( -0.5,  0.5, -0.5 );      // P3 is blue
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f( -0.5, -0.5, -0.5 ); 
			//	                        glEnd();
			//	glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(  0.5, -0.5, 0.5 );
			glTexCoord2f(0.0f, 1.0f);

			glVertex3f(  0.5,  0.5, 0.5 );
			glTexCoord2f(1.0f, 1.0f);

			glVertex3f( -0.5,  0.5, 0.5 );
			glTexCoord2f(1.0f, 0.0f);

			glVertex3f( -0.5, -0.5, 0.5 );
		
			  //     glEnd();
		
			glVertex3f( 0.5, -0.5, -0.5 );
			glVertex3f( 0.5,  0.5, -0.5 );
			glVertex3f( 0.5,  0.5,  0.5 );
			glVertex3f( 0.5, -0.5,  0.5 );


			glVertex3f( -0.5, -0.5,  0.5 );
			glVertex3f( -0.5,  0.5,  0.5 );
			glVertex3f( -0.5,  0.5, -0.5 );
			glVertex3f( -0.5, -0.5, -0.5 );



			glVertex3f(  0.5,  0.5,  0.5 );
			glVertex3f(  0.5,  0.5, -0.5 );
			glVertex3f( -0.5,  0.5, -0.5 );
			glVertex3f( -0.5,  0.5,  0.5 );

			glVertex3f(  0.5, -0.5, -0.5 );
			glVertex3f(  0.5, -0.5,  0.5 );
			glVertex3f( -0.5, -0.5,  0.5 );
			glVertex3f( -0.5, -0.5, -0.5 );
				
		glEnd();
				glDisable(GL_TEXTURE_2D);


	glPopMatrix();
}
void Robot::DrawArm(float xPos, float yPos, float zPos)
{
	glPushMatrix();
		glColor3f(1.0f, 0.0f, 0.0f);	// red
		glTranslatef(xPos, yPos, zPos);
		glScalef(1.0f, 4.0f, 1.0f);
		glutSolidCube (1.0);
		// arm is a 1x4x1 cube
		//DrawCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();
}

void Robot::DrawHead(float xPos, float yPos, float zPos)
{	i++;
	glPushMatrix();
		if(i%49==0 || i%49==1 || i%49==2 || i%49==3 || i%49==4 || i%49==5 || i%49==6 || i%49==7 || i%49==8 || i%49==9){

							glColor3f(1.0f, 0.0f, 0.0f);	// white
		}else{
							glColor3f(0.0f, 1.0f, 0.0f);	// blue


		}
		glTranslatef(xPos-xPos/3, yPos, zPos);
	//	glScalef(2.0f, 2.0f, 2.0f);
		
		glutWireSphere(2.0f,10,10);
			
		// head is a 2x2x2 cube
		//DrawCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();
}

void Robot::DrawTorso(float xPos, float yPos, float zPos)
{	

//	printf("i now is %d \n",i);

	glPushMatrix();
					glColor3f(0.0f, 0.0f, 1.0f);	// blue
	//	}
	//	else{
	//	}
		glTranslatef(xPos/2, yPos, zPos);
		glScalef(3.0f, 5.0f, 2.0f);		// torso is a 3x5x2 cube
	//	glutWireCube (1.0);
	
		DrawCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();
}

void Robot::DrawLeg(float xPos, float yPos, float zPos)
{
	glPushMatrix();
		glTranslatef(xPos, yPos, zPos);
		
		// draw the foot
		glPushMatrix();
			glTranslatef(0.0f, 0.0f, 0.0f);
			DrawFoot(0.0f, 0.0f, 0.0f);
			DrawFoot(0.0f, -2.5f, 0.0f);
			DrawFoot(-1.0f, -2.5f, 0.0f);
			DrawFoot(1.0f, -2.5f, 0.0f);

		glPopMatrix();		
		
		glScalef(1.0f, 5.0f, 1.0f);		// leg is a 1x5x1 cube
		glColor3f(0.0f, 0.0f, 1.0f);	// yellow
		glutSolidCube (1.0);

		//DrawCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();
}

void Robot::DrawFoot(float xPos, float yPos, float zPos)
{
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(xPos, yPos, zPos);
		glScalef(1.0f, 0.5f, 3.0f);
			glutSolidCube (1.0);
	//	DrawCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();
}

void Robot::DrawRobot(float xPos, float yPos, float zPos)
{
	//printf("here");
	glPushMatrix();	
		glTranslatef(xPos, yPos, zPos);	// draw robot at desired coordinates

		// draw head and torso parts
		DrawHead(0.0f, 4.0f, 0.0f);		
		DrawTorso(0.0f, -1.0f, 0.0f);

		// move the left arm away from the torso and rotate it to give "walking" effect
		glPushMatrix();
			glRotatef(-20.0f,1.0f, 0.0f, 0.0f);
			glTranslatef(0.0f, 1.0f,1.5f);
		
		
			glRotatef(armAngles[LEFT], 1.0f, 0.0f, 0.0f);
			glTranslatef(0.0f, -1.5f, 0.0f);
			DrawArm(2.0f, 0.0f, -0.5f);

			glRotatef(55.0f, 1.0f, 0.0f, 0.0f);

		
			glTranslatef(2.0f, -3.0f, 1.0f);
			DrawArm(0.0f, 0.0f, 0.0f);


		glPopMatrix();
		//troll
		// move the right arm away from the torso and rotate it to give "walking" effect
		glPushMatrix();
			glRotatef(10.0f, 1.0f, 0.0f, 0.0f);

			glTranslatef(0.0f, 1.0f, 1.5f);
			glRotatef(armAngles[RIGHT], 1.0f, 0.0f, 0.0f);
			glTranslatef(0.0f, -1.5f, 0.0f);
			DrawArm(-2.0f, 0.0f, -0.5f);
			glRotatef(55.0f, 1.0f, 0.0f, 0.0f);

		
			glTranslatef(-2.0f, -3.0f, 1.0f);
			DrawArm(0.0f, 0.0f, 0.0f);



		/*	
			glRotatef(-45.0f, 1.0f, 0.0f, 0.0f);

			glTranslatef(0.0f, -0.5f, 0.0f);
			glRotatef(armAngles[RIGHT], 1.0f, 0.0f, 0.0f);
			glTranslatef(0.0f, -1.5f, 0.0f);
			DrawArm(-2.0f, 0.0f, -0.5f);
			glTranslatef(0.0f, -3.5f, 0.0f);
			DrawArm(-2.0f, 0.0f, -0.5f);

		*/

		glPopMatrix();

		// move the left leg away from the torso and rotate it to give "walking" effect
		glPushMatrix();					
			glTranslatef(0.0f, -0.5f, 0.0f);
			glRotatef(legAngles[LEFT], 1.0f, 0.0f, 0.0f);
			DrawLeg(1.0f, -6.0f, -0.5f);
		glPopMatrix();

		// move the right leg away from the torso and rotate it to give "walking" effect
		glPushMatrix();
			glTranslatef(0.0f, -0.5f, 0.0f);
			glRotatef(legAngles[RIGHT], 1.0f, 0.0f, 0.0f);
			DrawLeg(-1.0f, -6.0f, -0.5f);
		glPopMatrix();

	glPopMatrix();	// pop back to original coordinate system
}

void Robot::Prepare(float dt)
{
	// if leg is moving forward, increase angle, else decrease angle
	for (int side = 0; side < 2; side++)
	{
		// arms
		if (armStates[side] == FORWARD_STATE)
		{
		//printf("believe\n");
			armAngles[side] += 20.0f * dt;
		}else
			armAngles[side] -= 20.0f * dt;

		// change state if exceeding angles
		if (armAngles[side] >= 15.0f)
			armStates[side] = BACKWARD_STATE;
		else if (armAngles[side] <= -15.0f)
			armStates[side] = FORWARD_STATE;

		// legs
		if (legStates[side] == FORWARD_STATE)
			legAngles[side] += 20.0f * dt;
		else
			legAngles[side] -= 20.0f * dt;

		// change state if exceeding angles
		if (legAngles[side] >= 15.0f)
			legStates[side] = BACKWARD_STATE;
		else if (legAngles[side] <= -15.0f)
			legStates[side] = FORWARD_STATE;		
	}
}
/*void drawScene()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -50.0f);
	glRotatef(180.0f,0,1,0);
	robot.DrawRobot(0.5,0.5,0.5);
	glPopMatrix();
	glutSwapBuffers();

}
void update(int value){
	robot.Prepare(0.05);
	glutTimerFunc(10, update, 0);
}
int main(int argc, char **argv)
{
	// Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	int w = glutGet(GLUT_SCREEN_WIDTH);
	int h = glutGet(GLUT_SCREEN_HEIGHT);
	int windowWidth = w * 2 / 3;
	int windowHeight = h * 2 / 3;

	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition((w - windowWidth) / 2, (h - windowHeight) / 2);

	glutCreateWindow("CSE251_sampleCode");  // Setup the window
	initRendering();

	// Register callbacks
	glutDisplayFunc(drawScene);
	glutIdleFunc(drawScene);
//	glutKeyboardFunc(handleKeypress1);
//	glutSpecialFunc(handleKeypress2);
//	glutMouseFunc(handleMouseclick);
	glutReshapeFunc(handleResize);
	glutTimerFunc(10, update, 0);

	glutMainLoop();

	//	robot.DrawArm();
	return 0;
}
void initRendering() {

	glEnable(GL_DEPTH_TEST);        // Enable objects to be drawn ahead/behind one another
	glEnable(GL_COLOR_MATERIAL);    // Enable coloring
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   // Setting a background color
}

// Function called when the window is resized
void handleResize(int w, int h) {

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
//	glPushMatrix();
//	glTranslatef(0.0f,2.0f,0.0f);
//	glPopMatrix();
	gluPerspective(45.0f, 1.14, 0.1f, 800.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}*/
