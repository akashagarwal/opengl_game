#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

static float rx = 0, ry = -2,rz =0,rot=180,lh=0,rh=0,rl=0,ll=0;
int ran[10][10];
int hand_flag=1,key_flag;
void update(int value);
void init(void) 
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	//	glShadeModel (GL_FLAT);

	for(int i=0;i<10;i++)
		for(int j=0;j<10;j++)
			ran[i][j]=rand();
}

	static void
drawBox(GLfloat size, GLenum type)
{
	static GLfloat n[6][3] =
	{
		{-1.0, 0.0, 0.0},
		{0.0, 1.0, 0.0},
		{1.0, 0.0, 0.0},
		{0.0, -1.0, 0.0},
		{0.0, 0.0, 1.0},
		{0.0, 0.0, -1.0}
	};
	static GLint faces[6][4] =
	{
		{0, 1, 2, 3},
		{3, 2, 6, 7},
		{7, 6, 5, 4},
		{4, 5, 1, 0},
		{5, 6, 2, 1},
		{7, 4, 0, 3}
	};
	GLfloat v[8][3];
	GLint i;

	v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
	v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
	v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
	v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
	v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
	v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;

	for (i = 5; i >= 0; i--) {
		glBegin(type);
		glNormal3fv(&n[i][0]);
		glVertex3fv(&v[faces[i][0]][0]);
		glVertex3fv(&v[faces[i][1]][0]);
		glVertex3fv(&v[faces[i][2]][0]);
		glVertex3fv(&v[faces[i][3]][0]);
		glEnd();
	}
}

	void APIENTRY
glutMSolidCube(GLdouble size)
{
	drawBox(size, GL_QUADS);
}

void robot(void)
{
	if (key_flag==0)
	{
		rh=0;
		lh=0;
	}
	//	printf("%d\n",key_flag);
	glPushMatrix();

	
	glTranslatef(rx,ry,rz);
//	glTranslatef(0,(GLfloat)ry,0);
	glRotatef(rot,0,1,0);


	glPushMatrix();
	glScalef (1.0, 2.0, 0.2);
	glColor3f(0.0f, 0.0f, 1.0f);
	glutSolidCube (1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef (0.0, 1.4, 0.0);
	glColor3f(0.0f, 1.0f, 1.0f);
	//	glutWireCube (0.5);
	glutWireSphere(0.4,30,30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.65, 0.6, 0.0);
	glTranslatef(-0.2, 0.4, 0.0);
	glRotatef(rh,1,0,0);
	glTranslatef(0.2, -0.4, 0.0);
	glColor3f(1.0f, 1.0f, 0.0f);
	glScalef (1.0, 4.0, 1.0);
	glutSolidCube (0.2);
	glPopMatrix();

	//	printf("%f\n",rh);
	glPushMatrix();
	glTranslatef(-0.65, 0.6, 0.0);
	glTranslatef(-0.2, 0.4, 0.0);
	glRotatef(lh,1,0,0);
	glTranslatef(0.2, -0.4, 0.0);
	glColor3f(1.0f, 1.0f, 0.0f);
	glScalef (1.0, 4.0, 1.0);
	glutSolidCube (0.2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.3, -1.4, 0.0);
	glTranslatef(-0.2, 0.4, 0.0);
	glRotatef(rh,1,0,0);
	glTranslatef(0.2, -0.4, 0.0);
	glColor3f(1.0f, 1.0f, 0.0f);
	glScalef (1.0, 4.0, 1.0);
	glutSolidCube (0.2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.3, -1.4, 0.0);
	glTranslatef(-0.2, 0.4, 0.0);
	glRotatef(lh,1,0,0);
	glTranslatef(0.2, -0.4, 0.0);
	glColor3f(1.0f, 1.0f, 0.0f);
	glScalef (1.0, 4.0, 1.0);
	glutSolidCube (0.2);
	glPopMatrix();

	glPopMatrix();
}

void texture(void)
{
	for(int i=-5;i<5;i++)
	{
		for(int j=-5;j<5;j++)
		{
			//			glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
			glBegin(GL_QUADS);
			glColor3f(0.0f, 0.5f, 1.0f);
			glVertex3f(i,-2,j);
			glColor3f(0.5f, 0.5f, 0.0f);
			glVertex3f(i,-2,j+2);
			glColor3f(0.0f, 0.5f, 1.0f);
			glVertex3f(i+2,-2,j+2);
			glColor3f(1.0f, 0.5f, 0.5f);
			glVertex3f(i+2,-2,j);
			glEnd();

			if(ran[i+5][j+5]%4==0)
			{
	glPushMatrix();
	glTranslatef(i,-2,j);
				glutMSolidCube(0.5);
	glPopMatrix();
			}
		}
	}
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GLfloat ambientColor[] = {0.4f, 0.4f, 0.4f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
	glPushMatrix();

	//	rx=rx+0.04*sin(rot*3.14/180);
	//	rz=rz+0.04*cos(rot*3.14/180);
//	printf("%f\n",rot);
	gluLookAt(0.4*rx,-1.99,0.4*rz,0.4*(rx+0.04*sin(rot*3.14/180)),-2,0.4*(rz+0.04*cos(rot*3.14/180)),0,1,0);//tower view
//	gluLookAt(0.4*rx,-1.5,0.4*rz,0.4*rx-4,-2,0.4*rz-4,0,1,0);//tower view

//	gluLookAt(rx,0,rz,rx-10,0,rz-10,0,1,0);

	texture();

	glPushMatrix();
	glScalef (0.4, 0.4, 0.4);
	//	   printf("%f %f\n",rx,rz);
	glTranslatef (-6.4, -2.0, 4.0);
	robot();
	glPopMatrix();
	/*
	   glTranslatef (-1.0, 0.0, 0.0);
	   glRotatef ((GLfloat) shoulder, 0.0, 0.0, 1.0);
	   glTranslatef (1.0, 0.0, 0.0);
	   glPushMatrix();
	   glScalef (2.0, 0.4, 1.0);
	   glutSolidCube (1.0);
	   glPopMatrix();

	   glTranslatef (1.0, 0.0, 0.0);
	   glRotatef ((GLfloat) elbow, 0.0, 0.0, 1.0);
	   glTranslatef (1.0, 0.0, 0.0);
	   glPushMatrix();
	   glScalef (2.0, 0.4, 1.0);
	   glutSolidCube (1.0);
	   glPopMatrix();
	 */
	//	printf("%f %f\n",rx,ry);

	glPopMatrix();
	glutSwapBuffers();
}

void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef (0.0, 0.0, -5.0);
}

void keyboard (unsigned char key, int x, int y)
{
	if (rh>=60)
		hand_flag=0;
	if (rh<=-60)
		hand_flag=1;
	if (key=='a')
		rot+=5;
	if (key=='d')
		rot-=5;
	if (key=='w')
	{
		rx=rx+0.04*sin(rot*3.14/180);
		rz=rz+0.04*cos(rot*3.14/180);
		key_flag=1;
		if (hand_flag==1)
		{
//		printf("if %d %f %f\n",hand_flag,rh,lh);
			rh+=3;
			lh-=3;
//		printf("if %d %f %f\n",hand_flag,rh,lh);
		}
		else
		{
//		printf("else %d %f %f\n",hand_flag,rh,lh);
			rh-=3;
			lh+=3;
//		printf("if %d %f %f\n",hand_flag,rh,lh);
		}
	}
	if (key=='s')
	{
		rx=rx-0.04*sin(rot*3.14/180);
		rz=rz-0.04*cos(rot*3.14/180);
		key_flag=1;
		if (hand_flag==1)
		{
//		printf("if %d %f %f\n",hand_flag,rh,lh);
			rh+=3;
			lh-=3;
//		printf("if %d %f %f\n",hand_flag,rh,lh);
		}
		else
		{
//		printf("else %d %f %f\n",hand_flag,rh,lh);
			rh-=3;
			lh+=3;
//		printf("if %d %f %f\n",hand_flag,rh,lh);
		}
	}
}

void handleKeypress2(int key, int x, int y)
{

	if (rh>=60)
		hand_flag=0;
	if (rh<=-60)
		hand_flag=1;
	if (key == GLUT_KEY_LEFT)
	{
		key_flag=1;
		rx -= 0.1;
		rot=270;
		if (hand_flag==1)
		{
			rh+=3;
			lh-=3;
		}
		else
		{
			rh-=3;
			lh+=3;
		}

	}
	if (key == GLUT_KEY_RIGHT)
	{
		key_flag=1;
		rx += 0.1;
		rot=90;
		if (hand_flag==1)
		{
			rh+=3;
			lh-=3;
		}
		else
		{
			rh-=3;
			lh+=3;
		}
	}
	if (key == GLUT_KEY_UP)
	{
		key_flag=1;
		rz -= 0.1;
		rot=180;
		if (hand_flag==1)
		{
			rh+=3;
			lh-=3;
		}
		else
		{
			rh-=3;
			lh+=3;
		}
	}
	if (key == GLUT_KEY_DOWN)
	{
		key_flag=1;
		rz += 0.1;
		rot=0;
		if (hand_flag==1)
		{
			rh+=3;
			lh-=3;
		}
		else
		{
			rh-=3;
			lh+=3;
		}
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (1024, 700); 
	glutInitWindowPosition (100, 100);
	glutCreateWindow (argv[0]);
	init ();
	glutDisplayFunc(display); 
	glutIdleFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	key_flag=0;
	glutSpecialFunc(handleKeypress2);
	glutTimerFunc(1000, update, 0);
	glutMainLoop();
	return 0;
}


void update(int value) {

	key_flag=0;
	glutTimerFunc(1000, update, 0);
}

