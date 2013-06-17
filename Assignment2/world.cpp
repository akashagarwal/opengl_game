#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "imageloader.h"
#include "md2model.h"

using namespace std;

static float rx = 6.4-(4.5/0.4), ry = -2,rz = -4.0 -(0.5/0.4),rot=180,lh=0,rh=0,tvx=-4.5,tvz=-0.5,hvx=-4,hvy=4,hvz=-6,hvlx=0,hvlz=0,htflag=0;
int j11=0,kj=0;
int ran[20][20];
float rblo[80][2];
int rblon=0;
float mblo[80][2];
int mblon=0;
float crobo[2];
int hand_flag=1,key_flag,fp_flag=-1,tp_flag=-1,tv_flag=-1,hv_flag=-1,pmx=-1,pmy=-1,amx=-1,amy=-1,htdir=1;
void update(int value);
void update1(int value);
void update2(int value);
int fflag=1;
int bflag=1;
int tvflag=-1;
int startflag=1,worldiflag=1;
int secondflag=1;
int gameflag=1;

MD2Model* _model;

//Makes the image into a texture, and returns the id of the texture
GLuint loadTexture(Image* image) 
{
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

GLuint _textureId; //The id of the texture
GLuint _tex2;
GLuint _texw;

float cal_col(float a,float b,float c,float d)
{
	float x=(d-b)*(d-b);
	x+=(c-a)*(c-a);
	float dot=0;
	dot+=(c-a)*sin(rot*3.14/180);
	dot+=(d-b)*cos(rot*3.14/180);

	float tt=sqrt(x);
	if (dot<0)
		tt=tt*-1;
	return tt;
}

void init(void) 
{
	//	glClearColor (0.0, 0.0, 0.0, 0.0);
	//		glShadeModel (GL_FLAT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING); //Enable lighting
	glEnable(GL_LIGHT0); //Enable light #0
	//	glEnable(GL_LIGHT1); //Enable light #1
	glEnable(GL_NORMALIZE); //Automatically normalize normals
	glShadeModel(GL_SMOOTH); //Enable smooth shading

	for(int i=0;i<10;i++)
		for(int j=0;j<10;j++)
		{
			ran[i][j]=rand();
			ran[i][j]=ran[i][j]%6;
		}

	//Load the model
	_model = MD2Model::load("tallguy.md2");
	if (_model != NULL) {
		_model->setAnimation("run");
	}

	Image* image = loadBMP("g2.bmp");
	_textureId = loadTexture(image);
	delete image;

	image = loadBMP("block.bmp");
	_tex2 = loadTexture(image);
	delete image;

	image = loadBMP("water.bmp");
	_texw = loadTexture(image);
	delete image;
}

void jump()
{
	if (kj==0)
		return;
	float u=0.5;
	float v=sqrt(u*u-(2*0.023*(ry+2)));
	//	printf("%f\n",v);

	rx=rx+0.1*sin(rot*3.14/180);
	rz=rz+0.1*cos(rot*3.14/180);

	if( j11 == 1 && (ry<=-2))
	{
		kj=0;
		j11=0;
		return;
	}
	if(ry>=3)
	{
		j11=1;
		ry -= v*sin(0.783);
	}
	if(j11 == 0)
	{
		ry += v*sin(0.783);
		//		printf( "%f\n" , ry );
	}
	else if(j11 ==1)
	{
		ry -= v*sin(0.783);
	}
	//	printf("%f\n",ry );
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
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(type);
		glNormal3fv(&n[i][0]);
			glTexCoord2f(0.0f, 0.0f);
		glVertex3fv(&v[faces[i][0]][0]);
			glTexCoord2f(1.0f, 0.0f);
		glVertex3fv(&v[faces[i][1]][0]);
			glTexCoord2f(1.0f, 1.0f);
		glVertex3fv(&v[faces[i][2]][0]);
			glTexCoord2f(0.0f, 1.0f);
		glVertex3fv(&v[faces[i][3]][0]);
		glEnd();
	}
}

	void APIENTRY
glutMSolidCube(GLdouble size)
{
	drawBox(size, GL_QUADS);
}

void MyCube(float ht)
{
		glColor3f(1.0f, 1.0f, 1.0f);
	//FRONT
	glBegin(GL_QUADS);
	glNormal3f(0,0,-1);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(  0.5, -0.5, -0.5 ); 
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(  0.5,  -0.5 +ht, -0.5 ); 
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f( -0.5,  -0.5 +ht, -0.5 ); 
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f( -0.5, -0.5, -0.5 ); 

	glEnd();

	// BACK
	glBegin(GL_QUADS);
	glNormal3f(0,0,1);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(  0.5, -0.5, 0.5 );
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(  0.5,  -0.5+ht, 0.5 );
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f( -0.5,  -0.5+ht, 0.5 );
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f( -0.5, -0.5, 0.5 );
	glEnd();

	//RIGHT
	glBegin(GL_QUADS);
	glNormal3f(-1,0,0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f( 0.5, -0.5, -0.5 );
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f( 0.5,  -0.5+ht, -0.5 );
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f( 0.5,  -0.5+ht,  0.5 );
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f( 0.5, -0.5,  0.5 );
	glEnd();

	//LEFT
	glBegin(GL_QUADS);
	glNormal3f(1,0,0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f( -0.5, -0.5,  0.5 );
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f( -0.5,  -0.5+ht,  0.5 );
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f( -0.5,  -0.5+ht, -0.5 );
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f( -0.5, -0.5, -0.5 );	
	glEnd();

	//TOP
	glBegin(GL_QUADS);
	glNormal3f(0,1,0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(  0.5,  -0.5+ht,  0.5 );
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(  0.5,  -0.5+ht, -0.5 );
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f( -0.5,  -0.5+ht, -0.5 );
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f( -0.5,  -0.5+ht,  0.5 );
	glEnd();

	//BOTTOM
	glBegin(GL_QUADS);
	glNormal3f(0,-1,0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(  0.5, -0.5, -0.5 );
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(  0.5, -0.5,  0.5 );
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f( -0.5, -0.5,  0.5 );
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f( -0.5, -0.5, -0.5 );
	glEnd();

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
	//	glTranslatef(0.0f, 4.5f, 0.0f);
	glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
	glScalef(0.18f, 0.18f, 0.18f);
	_model->draw();
	glPopMatrix();


	glPopMatrix();
}

void world(void)
{
	if(worldiflag==1)
	{
	rblon=0;
	mblon=0;
	}
	glPushMatrix();
	for(int i=-25;i<25;i++)
	{
		for(int j=-25;j<25;j++)
		{
			glColor3f(1,1,1);
			glBindTexture(GL_TEXTURE_2D, _texw);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(i,-7,j);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(i,-7,j+1);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(i+1,-7,j+1);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(i+1,-7,j);
			glEnd();
		}
	}

	for(int i=-5;i<5;i++)
	{
		for(int j=-5;j<5;j++)
		{
			//		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
			j-=5;
			glBindTexture(GL_TEXTURE_2D, _textureId);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glColor3f(1.0f, 1.0f, 1.0f);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			//			glColor3f(0.0f, 0.5f, 1.0f);
			glVertex3f(i,-3,j);
			glTexCoord2f(1.0f, 0.0f);
			//			glColor3f(0.5f, 0.5f, 0.0f);
			glVertex3f(i,-3,j+1);
			glTexCoord2f(1.0f, 1.0f);
			//			glColor3f(0.0f, 0.5f, 1.0f);
			glVertex3f(i+1,-3,j+1);
			glTexCoord2f(0.0f, 1.0f);
			//			glColor3f(1.0f, 0.5f, 0.5f);
			glVertex3f(i+1,-3,j);
			glEnd();

			glBindTexture(GL_TEXTURE_2D, _tex2);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glColor3f(1.0f, 0.5f, 0.5f);
			glPushMatrix();
			glTranslatef(i+0.5,-3.501,j+0.5);
			glutMSolidCube(1);
			glPopMatrix();


			if(ran[i+5][j+10]==0 && ((i+0.5)!=-4.5 || (j+0.5)!=-0.5) )
			{
				//		printf("%d\n",rblon);
				glPushMatrix();
				if(worldiflag==1)
				{
				rblo[rblon][0]=i+0.5;
				rblo[rblon][1]=j+0.5;
				rblon++;
				}
				glTranslatef(i+0.5,-2.5,j+0.5);
				glutMSolidCube(1);
				glPopMatrix();
			}
			if(ran[i+5][j+10]==1 && ((i+0.5)!=-4.5 || (j+0.5)!=-0.5))
			{
				//		printf("%d\n",rblon);
				glPushMatrix();
				if(worldiflag==1)
				{
				mblo[mblon][0]=i+0.5;
				mblo[mblon][1]=j+0.5;
				mblon++;
				}
				glTranslatef(i+0.5,-2.5,j+0.5);
				//	glutMSolidCube(1);
				MyCube(htflag);
				glPopMatrix();
			}
			j+=5;
			if (startflag==1)
			{
				if (secondflag==1)
					glColor3f(1,0,0);
				else
					glColor3f(0,0,1);
				glPushMatrix();
				glTranslatef(-4.5,-2.5,-0.5);
				glutWireCube(1);
				glPopMatrix();
			}
			else
			{
				if (secondflag==1)
					glColor3f(1,0,0);
				else
					glColor3f(0,0,1);
				glPushMatrix();
				glTranslatef(4.5,-2.5,-9.5);
				glutWireCube(1);
				glPopMatrix();
			}
		}
	}
	glPopMatrix();
	glColor3f(0.8f, 0.6f, 0.2f);
	worldiflag=-1;
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GLfloat ambientColor[] = {0.9f, 0.9f, 0.9f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);


	GLfloat lightColor0[] = {1.0f, 0.78f, 0.68f, 1.0f}; //Color (0.5, 0.5, 0.5)
	GLfloat lightPos0[] = {-10.0f, 10.0f, -10.0f, 1.0f}; //Positioned at (4, 0, 8)
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);


	GLfloat lightColor1[] = {0.5f, 0.2f, 0.2f, 1.0f}; //Color (0.5, 0.2, 0.2)
	//Coming from the direction (-1, 0.5, 0.5)
	GLfloat lightPos1[] = {rx, ry, rz, 0.0f};
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);


	glPushMatrix();

	//	rx=rx+0.04*sin(rot*3.14/180);
	//	rz=rz+0.04*cos(rot*3.14/180);
	//	printf("%f\n",rot);

	//		gluLookAt(0.4*rx,0,0.4*rz,0.4*(rx+0.04*sin(rot*3.14/180)),0,0.4*(rz+0.04*cos(rot*3.14/180)),0,1,0);//tower view
	//	gluLookAt(0.4*rx,-1.5,0.4*rz,0.4*rx-4,-2,0.4*rz-4,0,1,0);//tower view
	//	glRotatef(rot, 0.0f, 1.0f, 0.0f);
	/*
	   glTranslatef(0.4*rx,0.4*ry,0.4*rz);
	   glRotatef(rot, 0.0f, 1.0f, 0.0f);
	   glTranslatef(-0.4*rx,-0.4*ry,-0.4*rz);
	   gluLookAt(0.4*rx,0,0.4*rz,0.4*rx-5,0,0.4*rz-5,0,1,0);
	   glTranslatef(0.4*rx,0.4*ry,0.4*rz);
	   glRotatef(-rot, 0.0f, 1.0f, 0.0f);
	   glTranslatef(-0.4*rx,-0.4*ry,-0.4*rz);
	 */

	//	printf("%f %f\n",tvx,tvz);
	/*
	glScalef (0.4, 0.4, 0.4);
	glTranslatef (-6.4,- 0.6-1, 4.0);
	glTranslatef (rx,ry,rz);
	//	glutSolidSphere(0.4,30,30);
	//			gluLookAt(0,0,0,0.004*sin(rot*3.14/180),0,0.004*cos(rot*3.14/180),0,1,0);
	glTranslatef (-rx,-ry,-rz);
	glTranslatef (6.4,0.6+1, -4.0);
	glScalef (2.5, 2.5, 2.5);
	*/
	//gluLookAt(0.4*(rx-6.4),0.4*(ry-0.6),0.4*(rz+4.0),0.4*(rx+0.004*sin(rot*3.14/180)-6.4),0.4*(ry-0.6),0.4*(rz+0.004*cos(rot*3.14/180)+4.0),0,1,0);
	crobo[0]=0.4*(rx-6.4);
	crobo[1]=0.4*(rz+4.0);
	//	printf("%f %f\n",crobo[0],crobo[1]);

	if (tvflag==1)
		gluLookAt(0.4*(tvx-6.4),0.4*(1-0.6),0.4*(tvz+4.0),0.4*(tvx+0.004-6.4),0.4*(1-0.6),0.4*(tvz+4.0),0,1,0);//Tile view

	if(fp_flag==1)
	{

		glScalef (0.4, 0.4, 0.4);
		glTranslatef (-6.4, -2.0, 4.0);
		gluLookAt(rx,ry-1,rz,rx+0.004*sin(rot*3.14/180),ry-1,rz+0.004*cos(rot*3.14/180),0,1,0);//1st person view
		//	robot();
		//	glColor3f(0,0,1);
		//			glutSolidSphere(100,30,30);
		glTranslatef (6.4, 2.0, -4.0);
		glScalef (2.5, 2.5, 2.5);

	}
	else if (tp_flag==1)
	{
		gluLookAt(0.4*(rx-6.4),0.4*(ry-0.6),0.4*(rz+4.0),0.4*(rx+0.004*sin(rot*3.14/180)-6.4),0.4*(ry-0.6),0.4*(rz+0.004*cos(rot*3.14/180)+4.0),0,1,0);//3rd person view

	}
	else if(tv_flag==1)
		gluLookAt(-6,4,-6,0,0,0,0,1,0);

	else if(hv_flag==1)
		gluLookAt(hvx,hvy,hvz,hvlx,-2,hvlz,0,1,0);

	glPushMatrix();
	glScalef (0.4, 0.4, 0.4);
	//	   printf("%f %f\n",rx,rz);
	glTranslatef (-6.4, -2.0, 4.0);


	if((fp_flag!=1 || tp_flag==1 || tv_flag==1) && gameflag==1)
		robot();

	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	world();
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
	jump();

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
	if (key==27)
	{
		//Escape key
		exit(0);
	} 
	if(key=='j')
	{
		kj=1;
		j11=0;
	}

	if (rh>=60)
		hand_flag=0;
	if (rh<=-60)
		hand_flag=1;
	if (key=='a')
		rot+=5;
	if (key=='d')
		rot-=5;
	if (key=='w' && (fflag==1 || ry>0))
	{
		startflag=0;
		rx=rx+0.1*sin(rot*3.14/180);
		rz=rz+0.1*cos(rot*3.14/180);
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
	if (key=='s' && (bflag==1 || ry>0))
	{
		startflag=0;
		rx=rx-0.1*sin(rot*3.14/180);
		rz=rz-0.1*cos(rot*3.14/180);
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
	if (key=='f')
	{
		fp_flag=fp_flag*-1;
		tp_flag=-1;
		tv_flag=-1;
		tvflag=-1;
		hv_flag=-1;
	}
	if (key=='t')
	{
		tp_flag=tp_flag*-1;
		fp_flag=-1;
		tv_flag=-1;
		tvflag=-1;
		hv_flag=-1;
	}
	if (key=='y')
	{
		tv_flag=tv_flag*-1;
		fp_flag=-1;
		tp_flag=-1;
		tvflag=-1;
		hv_flag=-1;
	}
	if (key=='b')
	{
		tvflag=tvflag*-1;
		fp_flag=-1;
		tp_flag=-1;
		tv_flag=-1;
		hv_flag=-1;
	}
	if (key=='h')
	{
		hv_flag=hv_flag*-1;
		fp_flag=-1;
		tp_flag=-1;
		tv_flag=-1;
		tvflag=-1;
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
		if (tvflag==1 && tvz>-25.5)
			tvz-=2.5;
	}
	if (key == GLUT_KEY_RIGHT)
	{
		if (tvflag==1 && tvz<-0.5)
			tvz+=2.5;
	}
	if (key == GLUT_KEY_UP)
	{
		if (tvflag==1 && tvx<20.5)
			tvx+=2.5;
	}
	if (key == GLUT_KEY_DOWN)
	{
		if (tvflag==1 && tvx>-4.5)
			tvx-=2.5;
	}
}

void processMouseActiveMotion(int x, int y)
{
	pmx=-1;
	//	printf("%d %d\n",x,y);
	if (amx!=-1)
	{
		//	printf("%d %d\n",x-pmx,y-pmy);
		hvlx-=(0.05)*(x-amx);
		hvlz-=(0.05)*(y-amy);
	}
	amx=x;
	amy=y;
}

void processMousePassiveMotion(int x, int y)
{
	amx=-1;
	if (pmx!=-1)
	{
		//	printf("%d %d\n",x-pmx,y-pmy);
		hvx-=(0.05)*(x-pmx);
		hvz-=(0.05)*(y-pmy);
	}
	pmx=x;
	pmy=y;
	//		printf("%d %d\n",x,y);
}

void processMouse(int button, int state, int x, int y)
{
	//		printf("%d %d %d %d\n",button,state,x,y);
	if (button==3)
		hvy-=0.1;
	if (button==4)
		hvy+=0.1;
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
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
	glutTimerFunc(10, update, 0);
	glutTimerFunc(100, update1, 0);
	glutTimerFunc(1000, update2, 0);
	glutMotionFunc(processMouseActiveMotion);
	glutPassiveMotionFunc(processMousePassiveMotion);
	glutMouseFunc(processMouse);
	glutMainLoop();
	return 0;
}


void update(int value)
{

	glutTimerFunc(10, update, 0);

	if (0.4*(rx-6.4)>4 && 0.4*(rz+4.0)<-9)
	{
		printf("YOU WON\n");
		exit(0);
	}
	
	if(0.4*(rx-6.4)>5 || 0.4*(rz+4.0)<-10 || 0.4*(rx-6.4)<-5 || 0.4*(rz+4.0)>0)
	{
		printf("YOU FELL OFF THE EDGE TO LOSE\n");
		exit(0);
	}

	if(key_flag==1)
	{
		if (_model != NULL) 
		{
			_model->advance(0.025f);
		}
	}

	fflag=1;
	bflag=1;
	if(kj==0)
		ry=-2;
	//	printf("%d\n",rblon);	
	float fmin=-10;
	float bmin=10;
	float val;
	for(int i=0;i<rblon;i++)
	{
		val=cal_col(rblo[i][0],rblo[i][1],crobo[0],crobo[1]);
		if (val>0 && val<bmin)
			bmin=val;
		if (val<0 && val>fmin)
			fmin=val;
	}
	if (fmin > -0.8)
		fflag=0;
	if (bmin <0.8)
		bflag=0;

	if ((fmin>-0.7 || bmin<0.7) && kj==0)
		ry=0.5;
	else if ((fmin>-0.7 || bmin<0.7) && kj==1 && j11==1)
	{
		kj=0;
		j11=0;
		ry=0.5;
	}

	fmin=-10;
	bmin=10;
	for(int i=0;i<mblon;i++)
	{
		val=cal_col(mblo[i][0],mblo[i][1],crobo[0],crobo[1]);
		if (val>0 && val<bmin)
			bmin=val;
		if (val<0 && val>fmin)
			fmin=val;
	}
	if ((fmin>-0.65 || bmin<0.65) && kj==0)
		ry=2.5*htflag-1.9;
	else if ((fmin>-0.65 || bmin<0.65) && kj==1 && j11==1 )
	{
		kj=0;
		j11=0;
		ry=2.5*htflag-1.8;
	}
	else if(htflag>0.15)
	{
		if (fmin > -0.8)
			fflag=0;
		if (bmin <0.8)
			bflag=0;
	}
	//	printf("%f %f %f\n",fmin,bmin,htflag);
}

void update1(int value) {
	if (htdir==1)
	{
		htflag+=0.05;
		if (htflag>=1)
			htdir=-1;
	}
	else if (htdir==-1)
	{
		htflag-=0.05;
		if (htflag<=0)
			htdir=1;
	}
	key_flag=0;
	glutTimerFunc(100, update1, 0);
}

void update2(int value) {
	secondflag=secondflag*-1;
	glutTimerFunc(1000, update2, 0);
}
