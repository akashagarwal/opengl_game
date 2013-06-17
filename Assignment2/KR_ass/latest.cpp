#include <iostream>
#include <cmath>
#include <GL/glut.h>
#include<stdio.h>
#include "imageloader.h"
#include "Robot.h"
#include <stdlib.h>
#include <time.h>
#include "md2model.h"
#include "vec3f.h"

using namespace std;


#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)

GLuint _textureId;

GLuint _textureId1;

GLuint _textureId2;



int curr_block=0;
MD2Model* _model;
float fx,fz,fy;
//The id of the texture
float valInc;
int ceilx,floorx;
int j11=0,kj=0;
float rot;

void drawWorld(void);
typedef struct holes
{
	float xmin;
	float xmax;
	float ymin;
	float ymax;
	int holex;


}holes;

float rotxx,rotyy;
holes hole[1000];
int holeNo;

int xxx[10];
int xxxn=0;
float x,g,t;
int collisionFlag;
int forflag,backflag;
int firstmove;
int fflag=1;
int bflag=1;
int tvflag=-1;
int startflag=1,worldiflag=1;
int secondflag=1;
int gameflag=1;


GLuint _tex2;
GLuint _texw;

static float htflag=0; 
int ran[800][800];
float rblo[2000][2];
int rblon=0;
float mblo[2000][2];
int mblon=0;


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

	static void
sexBox(GLfloat size, GLenum type)
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
	sexBox(size, GL_QUADS);
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

void jump()
{
	if (kj==0)
		return;
	float u=0.5;
	float v=sqrt(u*u-(2*0.023*(fy-2)));
	//      printf("%f\n",v);

	fx=fx-v*0.25*sin(rot*3.14/180);
	fz=fz-v*0.25*cos(rot*3.14/180);

	if( j11 == 1 && (fy<=0.5))
	{   
		kj=0;
		j11=0;
		return;
	}   
	if(fy>=2)
	{   
		j11=1;
		fy -= v*sin(0.783);
	}   
	if(j11 == 0)
	{   
		fy += v*sin(0.783);
		//              printf( "%f\n" , ry );
	}   
	else if(j11 ==1)
	{   
		fy -= v*sin(0.783);
	}   
	//      printf("%f\n",ry );
}



float tilerot;
void DrawCube(float xPos, float yPos, float zPos)

{
	glPushMatrix();
	glTranslatef(xPos, yPos, zPos);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,_textureId2);
	//Bottom
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//glBegin(GL_QUADS);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	//	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(  0.5, -0.5, -0.5 );      // P1 is red
	//	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(  0.5,  0.5, -0.5 );      // P2 is green
	//	glTexCoord2f(1.0f, 1.0f);
	glVertex3f( -0.5,  0.5, -0.5 );      // P3 is blue
	//	glTexCoord2f(1.0f, 0.0f);
	glVertex3f( -0.5, -0.5, -0.5 ); 
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	//	glTexCoord2f(0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(  0.5, -0.5, -0.5 );      // P1 is red
	//	glTexCoord2f(0.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);

	glVertex3f(  0.5,  0.5, -0.5 );      // P2 is green
	//	glTexCoord2f(1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);

	glVertex3f( -0.5,  0.5, -0.5 );      // P3 is blue
	//	glTexCoord2f(1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);

	glVertex3f( -0.5, -0.5, -0.5 ); 
	glEnd();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);





	glBegin(GL_QUADS);
	//	glTexCoord2f(0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f( -0.5, -0.5, 0.5 );
	glTexCoord2f(0.0f, 1.0f);

	glVertex3f(  0.5, -0.5, 0.5 );
	//	glTexCoord2f(0.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);

	glVertex3f(  0.5,  0.5, 0.5 );
	//	glTexCoord2f(1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);

	glVertex3f( -0.5,  0.5, 0.5 );
	//	glTexCoord2f(1.0f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f( 0.5, -0.5, -0.5 );
	glTexCoord2f(0.0f, 1.0f);

	glVertex3f( 0.5,  0.5, -0.5 );
	glTexCoord2f(1.0f, 1.0f);

	glVertex3f( 0.5,  0.5,  0.5 );
	glTexCoord2f(1.0f, 0.0f);

	glVertex3f( 0.5, -0.5,  0.5 );
	glEnd();




	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f( -0.5, -0.5,  0.5 );
	glTexCoord2f(0.0f, 1.0f);

	glVertex3f( -0.5,  0.5,  0.5 );
	glTexCoord2f(1.0f, 1.0f);

	glVertex3f( -0.5,  0.5, -0.5 );
	glTexCoord2f(1.0f, 0.0f);

	glVertex3f( -0.5, -0.5, -0.5 );
	glEnd();



	glDisable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,_textureId);
	//Bottom
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(  0.5,  0.5,  0.5 );
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(  0.5,  0.5, -0.5 );
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f( -0.5,  0.5, -0.5 );
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f( -0.5,  0.5,  0.5 );
	glEnd();
	glDisable(GL_TEXTURE_2D);



	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex3f(  0.5,  0.5,  0.5 );
	glVertex3f(  0.5,  0.5, -0.5 );
	glVertex3f( -0.5,  0.5, -0.5 );
	glVertex3f( -0.5,  0.5,  0.5 );

	//glVertex3f( 0.5,  0.5, -0.5 );
	//glVertex3f( 0.5,  0.5,  0.5 );
	//glVertex3f( 0.5, -0.5,  0.5 );
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);















	glBegin(GL_QUADS);
	glVertex3f(  0.5, -0.5, -0.5 );
	glVertex3f(  0.5, -0.5,  0.5 );
	glVertex3f( -0.5, -0.5,  0.5 );
	glVertex3f( -0.5, -0.5, -0.5 );
	glEnd();


	glPopMatrix();

}



























Robot robot;
// Function Declarations
void drawScene();
void update(int value);
void drawBox(float len);
void drawBall(float rad);
void drawTriangle();
void initRendering();
void handleResize(int w, int h);
void handleKeypress1(unsigned char key, int x, int y);
void handleKeypress2(int key, int x, int y);
void handleMouseclick(int button, int state, int x, int y);


//int jump;
int flagHit;
float vx,vy;
int mode;
int rotationDone;
// Global Variables
float ball_x = 1.0f;
float ball_y = 0.0f;
float ball_velx = 0.01f;
float ball_vely = 0.02f;
float ball_rad = 0.2f;
float box_len = 4.0f;
float tri_x = 0.0f;
float tri_y = 0.0f;
float theta = 0.0f; 
float localvx,localvy;
float xcam,ycam,zcam;
float rotCam;
float xdis,ydis;
float totalDis;
int light;
int xinc;
int yinc;

int main(int argc, char **argv) {
	firstmove=0;
	yinc=0;
	rotxx=0.0;
	rotyy=0.0;
	xinc=0;
	collisionFlag=0;
	light=1;
	srand((int)time(NULL));
	holeNo=0;
	fx=0;
	fz=0;
	rot=0;
	//jump=0;
	vx=0.05;
	vy=0.05;
	ceilx=0;
	floorx=0;
	rotCam=0;
	flagHit=0;
	xcam=0;
	ycam=0;
	zcam=0;
	localvx=0;
	localvy=0;
	rotationDone=0;
	mode=0;
	valInc=0.0;
	xdis=0;
	ydis=0;
	totalDis=0;;
	x=0.1;
	g=0.005;
	t=0;
	forflag=0;
	backflag=0;
	tilerot=0;
	//printf("holeNo is %d\n",holeNo);
	/*for(int i=-20;i<=20;i+=2){
	  for(int j=-20;j<=20;j+=2){
	  if((abs(i)+abs(j))%9==2){
	  hole[holeNo].xmin=i/2.0f;				
	  hole[holeNo].xmax=(i+2)/2.0f;
	  hole[holeNo].ymin=j/2.0f;
	  hole[holeNo].ymax=(j+2)/2.0f;
	  hole[holeNo++].holex=0;
	  }
	  else if((abs(i)+abs(j))%9==1){
	  printf("came till here \n");
	  printf("hole no is %d\n",holeNo);
	  hole[holeNo].xmin=i/2.0f;				
	  hole[holeNo].xmax=(i+2)/2.0f;
	  hole[holeNo].ymin=j/2.0f;
	  hole[holeNo].ymax=(j+2)/2.0f;
	  hole[holeNo++].holex=1;
	  }

	  }
	  }*/
	for(int i=-20;i<=20;i+=2){
		for(int j=-20;j<=20;j+=2){
			//printf("%d rand now is \n",rand());
			int flag=0;
			long long int comp=rand()%10;
			if(comp<=5){
				flag=1;
				//	printf("grass3\n");
				hole[holeNo].xmin=i/2.0f;				
				hole[holeNo].xmax=(i+2)/2.0f;
				hole[holeNo].ymin=j/2.0f;
				hole[holeNo].ymax=(j+2)/2.0f;
				hole[holeNo].holex=3;
				////static normal grass level block
			}else if((comp)==7){
				//	printf("grass\n");
				flag=1;
				//			printf("came from hole 2\n");
				hole[holeNo].xmin=i/2.0f;				
				hole[holeNo].xmax=(i+2)/2.0f;
				hole[holeNo].ymin=j/2.0f;
				hole[holeNo].ymax=(j+2)/2.0f;
				hole[holeNo].holex=2;
				////static khada block
			}else if((comp)==8){
				//	printf("hole updown\n");
				flag=1;
				//			printf("came from hole 0\n");
				hole[holeNo].xmin=i/2.0f;				
				hole[holeNo].xmax=(i+2)/2.0f;
				hole[holeNo].ymin=j/2.0f;
				hole[holeNo].ymax=(j+2)/2.0f;
				hole[holeNo].holex=0;
				/////movable upar neeche block
			}
			else if((comp)==9){
				//	printf("hole down down\n");
				flag=1;
				//				printf("came from hole 1\n");
				//printf("came till here \n");
				//printf("hole no is %d\n",holeNo);
				hole[holeNo].xmin=i/2.0f;				
				hole[holeNo].xmax=(i+2)/2.0f;
				hole[holeNo].ymin=j/2.0f;
				hole[holeNo].ymax=(j+2)/2.0f;
				hole[holeNo].holex=1;
				/////hole block
			}
			else if((comp)==6){
				//	printf("hole down down\n");
				flag=1;
				//				printf("came from hole 1\n");
				//printf("came till here \n");
				//printf("hole no is %d\n",holeNo);
				hole[holeNo].xmin=i/2.0f;				
				hole[holeNo].xmax=(i+2)/2.0f;
				hole[holeNo].ymin=j/2.0f;
				hole[holeNo].ymax=(j+2)/2.0f;
				hole[holeNo].holex=4;
				/////falling block
			}
			if(flag==0){
				//		printf("there is a problem\n");
			}
			//	printf("holex now is %d\n",holeNo);

			holeNo++;
		}
	}






	// Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB|GLUT_DEPTH);

	int w = glutGet(GLUT_SCREEN_WIDTH);
	int h = glutGet(GLUT_SCREEN_HEIGHT);
	int windowWidth = w ;
	int windowHeight = h ;

	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition((w - windowWidth) / 2, (h - windowHeight) / 2);

	glutCreateWindow("CSE251_sampleCode");  // Setup the window
	initRendering();

	// Register callbacks
	glutDisplayFunc(drawScene);
	glutIdleFunc(drawScene);
	glutKeyboardFunc(handleKeypress1);
	glutSpecialFunc(handleKeypress2);
	glutMouseFunc(handleMouseclick);
	glutReshapeFunc(handleResize);
	glutTimerFunc(10, update, 0);

	glutMainLoop();
	return 0;
}








GLuint loadTexture(Image* image) {
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



void initRendering() {

	glEnable(GL_DEPTH_TEST);        // Enable objects to be drawn ahead/behind one another
	glEnable(GL_COLOR_MATERIAL);    // Enable coloring
	if(light==1){
		glEnable(GL_LIGHTING); //Enable lighting
		glEnable(GL_LIGHT0); //Enable light #0
		glEnable(GL_LIGHT1); //Enable light #1
	}

	/*	if(light==0){
	//
	printf("should come here\n");
	glDisable(GL_LIGHTING); //Enable lighting
	glDisable(GL_LIGHT0); //Enable light #0
	glDisable(GL_LIGHT1); //Enable light #1


	}

	 */

	for(int i=0;i<800;i++)
		for(int j=0;j<800;j++)
		{
			ran[i][j]=rand();
			ran[i][j]=ran[i][j]%6;
		}



	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   // Setting a background color
	Image* image = loadBMP("gr.bmp");
	_textureId = loadTexture(image);
	delete image;
	Image* image1 = loadBMP("mkwater.bmp");
	_textureId1 = loadTexture(image1);
	delete image1;
	Image* image2 = loadBMP("brick_wall.bmp");
	_textureId2 = loadTexture(image2);
	delete image2;

	Image * image3 = loadBMP("block.bmp");
	_tex2 = loadTexture(image3);
	delete image3;

	Image * image4 = loadBMP("water.bmp");
	_texw = loadTexture(image4);
	delete image4;


	//Load the model
	_model = MD2Model::load("tallguy.md2");
	if (_model != NULL) {
		_model->setAnimation("run");
	}



}


int rh=0,lh=0,key_flag=0,rott=0,rx=0,ry=0,rz=0;


void a_robot(void)
{
	if (key_flag==0)
	{
		rh=0;
		lh=0;
	}
	//      printf("%d\n",key_flag);
	glPushMatrix();


	glTranslatef(rx,ry,rz);
	//      glTranslatef(0,(GLfloat)ry,0);
	glRotatef(rott,0,1,0);

	glPushMatrix();
	//      glTranslatef(0.0f, 4.5f, 0.0f);
	glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
	glScalef(0.18f, 0.18f, 0.18f);
	_model->draw();
	glPopMatrix();


	glPopMatrix();
}




// Function to draw objects on the screen
void drawScene() {

	float x1,y1,z1;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//	GLfloat ambientColor[] = {0.8f, 0.8f, 0.8f, 1.0f}; //Color(0.2, 0.2, 0.2)

	GLfloat ambientColor[] = {0.8f, 0.8f, 0.8f, 1.0f};

	if(light==1){
		GLfloat ambientColor[] = {0.8f, 0.8f, 0.8f, 1.0f};	
		///	printf("came here \n");
	}else{
		GLfloat ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f};
		//
		//	printf("should come here\n");
		glDisable(GL_LIGHTING); //Enable lighting
		glDisable(GL_LIGHT0); //Enable light #0
		glDisable(GL_LIGHT1); //Enable light #1


	}
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

	if(mode==0){
		glRotatef(rotCam, 0.0f, 1.0f, 0.0f);
		glRotatef(rotxx, 1.0f, 0.0f, 0.0f);
		glRotatef(rotyy, 0.0f, 0.0f, 1.0f);

		gluLookAt (xcam, ycam, 2.0+zcam, xcam, ycam, 0.0+zcam, 0.0, 1.0, 0.0); 
		//printf("%f %f %f %f %f %f %f %f %f\n",rotCam,rotxx,rotyy,xcam,ycam,2.0+zcam,xcam,ycam,0.0+zcam);
	}
	else if(mode==1){
		//	  glPushMatrix();
		//			  glRotatef(-rot, 0.0f, 1.0f, 0.0f);

		gluLookAt (0.0+fx-localvx, -0.15, -20.0+fz-localvy, 0.0+fx+50.0*sin(-rot*PI*1.0f/180*1.0f)-localvx, 0.0, -21.0+fz-50.0*cos(-rot*PI*1.0f/180*1.0f)-localvy, 0.0, 1.0, 0.0); 
		//		           gluLookAt (0.0+fx-localvx, 0.0, -20.2-fz-localvy, 0.0+fx, 0.0, -22.0-fz-localvy, 0.0, 1.0, 0.0); 

		//	  glRotatef(rot, 0.0f, 1.0f, 0.0f);

		//		gluLookAt (0.0f, 0.0f,0.0f, 0.0, 0.0, -2.0, 0.0, 1.0, 0.0); 



		//			glPopMatrix();

	}else if(mode==2){
		gluLookAt (0.0+fx-localvx-5.0*sin(-rot*PI*1.0f/180*1.0f), 0.0, -20.2+fz-localvy+5.0*cos(-rot*PI*1.0f/180*1.0f), 0.0+fx+5.0*sin(-rot*PI*1.0f/180*1.0f)-localvx, 0.0, -24.0+fz-5.0*cos(-rot*PI*1.0f/180*1.0f)-localvy, 0.0, 1.0, 0.0); 
		//		           gluLookAt (0.0+

	}else if(mode==3){
		//	glRotatef(rotCam, 0.0f, 1.0f, 0.0f);

		//	gluLookAt (xcam, 3.0+ycam, -16.0+zcam, xcam, 3.0+ycam, -16.5+zcam, 0.0, 1.0, -4.0); 
		glRotatef(rotCam, 1.0f, 0.0f, 0.0f);
		glRotatef(42.0, 1.0f, 0.0f, 0.0f);
		glRotatef(0.0, 0.0f, 0.0f, 1.0f);

		gluLookAt (1.2, 11.4, -0.9999999, 1.2, 11.4, -2.999999, 0.0, 1.0, 0.0); 





	}else{
		glRotatef(tilerot, 0.0f, 1.0f, 0.0f);

		gluLookAt (-10.0+yinc, -0.5, -8.0+xinc, -10.0+yinc, -0.5, -10.5+xinc, 0.0, 1.0, 0.0); 
		//gluLookAt (-10.0+xcam, 2.0+ycam, -20.0+zcam, -20.0+xcam, 0.0+ycam, -20.0+zcam, 0.0, 1.0, 0.0); 




	}
	///	printf("zcam is %f \n",2.0+zcam);	



	glTranslatef(0.0f, 0.0f, -20.0f);





	glPushMatrix();
	glColor3f(1.0f, 1.0f, 0.0f);
	glScalef(1.0f, 4.0f, 1.0f);

	//	robot.DrawCube(2.0,-2.0,3.0);

	DrawCube(0.5,0.0,0.5);
	glPopMatrix();




	if(light==1){

		GLfloat lightColor0[] = {0.5f, 0.5f, 0.5f, 1.0f}; //Color (0.5, 0.5, 0.5)
		GLfloat lightPos0[] = {4.0f, 4.0f, -8.0f, 1.0f}; //Positioned at (4, 0, 8)
		///	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
		///	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

		//Add directed light
		GLfloat lightColor1[] = {0.5f, 0.2f, 0.2f, 1.0f}; //Color (0.5, 0.2, 0.2)
		//Coming from the direction (-1, 0.5, 0.5)
		GLfloat lightPos1[] = {-4.0f, 5.0f, -8.0f, 0.0f};
		///	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
		///	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);

	}
	glPushMatrix();
	glTranslatef(-8, 0.0f, 10);

	drawBall(0.5);
	glPopMatrix();

	//   glColor3f(1.0f, 0.0f, 0.0f);

	//glRotatef(90.0, 0.0f, 1.0f, 0.0f);
	// glBegin(GL_LINES);
	//glVertex3f(1.0,2.0 ,1.0);
	//glVertex3f(2.0, 1.0,3.0);
	//glVertex2f(len / 2, len / 2);
	//glVertex2f(-len / 2, len / 2);
	//glEnd();
	jump();
	drawBox(box_len);
	for(int i=0;i<holeNo;i++)
	{
		if (hole[i].xmin <= fx && hole[i].xmax>=fx && hole[i].ymin <= fz && hole[i].ymax>=fz)
		{
			curr_block=i;
			break;
		}

	}



	glColor3f(1,0,1);

	glBegin(GL_QUADS);
	int ss=curr_block;
	int s1,s2,s3,s4;
	s1=hole[ss].xmin;
	s2=hole[ss].ymin;
	s3=hole[ss].xmax;
	s4=hole[ss].ymax;
	glVertex3f(s1,-1.48,s2);
	glVertex3f(s3, -1.48,s2);
	glVertex3f(s3, -1.48,s4);
	glVertex3f(s1, -1.48,s4);

	//	cout << s4-s2 << "\n";
	xxxn=0;
	glEnd();
	float midx=(s3+s1)/2.0;
	float midy=(s4+s2)/2.0;
	//	cout << valInc << "\n";
	//	cout<<"midx and midy"<<midx<<" "<<midy<<"\n";
	//	cout << midx << " " << midy << "\n";
	for(int i=0;i<holeNo;i++)
	{
		float mxx,myy;
		mxx = (hole[i].xmax+hole[i].xmin)/2.0;
		myy = (hole[i].ymax+hole[i].ymin)/2.0;
		if (abs(midx-mxx)<=1.0 && abs(midy-myy)<=1.0)
		{
			//	cout << mxx << "     " << myy << "\n";
			xxx[xxxn]=i;
			xxxn++;
		}
		//		cout << xxxn << "\n";
	}
	//	cout<<"xxxn is "<<xxxn<<"\n";
	//
	//	cout<<"\n\n\n\n\n\n";
	for(int i=0;i<xxxn;i++)
	{
		s1=hole[xxx[i]].xmin;
		s2=hole[xxx[i]].ymin;
		s3=hole[xxx[i]].xmax;
		s4=hole[xxx[i]].ymax;
		/*
		   glBegin(GL_QUADS);
		   glVertex3f(s1,-1.48,s2);
		   glVertex3f(s3, -1.48,s2);
		   glVertex3f(s3, -1.48,s4);
		   glVertex3f(s1, -1.48,s4);
		   glEnd();
		 */
	}

	//drawWorld();
	//	printf("vx and vy main main are %f %f\n",vx,vy);
	glPushMatrix();
	//printf("localvx is %f %f\n" ,localvx,localvy);
	//	glRotatef(rot, 0.0f, 1.0f, 0.0f);
	//	glRotatef(-rot, 0.0f, 1.0f, 0.0f);

	// glTranslatef(fx-localvx, 0.0f, -fz-localvy);


	// glTranslatef(-fx+localvx, 0.0f, +fz+localvy);


	//glTranslatef(fx-localvx, 0.0f, -fz-localvy);

	//glTranslatef(fx-localvx, 0.0f, fz-localvy);
	glTranslatef(fx,fy, fz);
	//	float tempx,tempy;
	//		float tempx=0.3*sin(rot*3.14/180);
	//		float tempy=0.3*cos(rot*3.14/180);

	float rr;
	rr=0.0f;
	float decide;
	if((fx-localvx)<-10 || (fx-localvx)>10 || (fz-localvy)<-10 || (fz-localvy)>11){
		printf("got out of arena\n");
		exit(0);

	}
	for(int i=0;i<holeNo;++i){
		//printf("localvx and vy are %f %f \n",localvx,localvy);
		if((hole[i].xmin)<=(fx-localvx) && (hole[i].xmax)>=(fx-localvx) && (hole[i].ymin)<=(fz-localvy) && hole[i].ymax>=(fz-localvy)){
			if(hole[i].holex==1){
				glTranslatef(0.0f, -1.0f,0.0f);
				decide=-1.0;
			}else if(hole[i].holex==0){
				glTranslatef(0.0f,-1.0+valInc*1.0f,0.0f);
				decide=-1.0+valInc;
			}else if(hole[i].holex==2){

				//	glTranslatef(-fx+localvx, 0.0f, -fz+localvy);

				//	glTranslatef(0.0f, 0.5f,0.0f);



				//	collisionFlag=1;	
				//glTranslatef(0.0f, 0.5f,0.0f);

				//		rr=0.5f;
				//		glTranslatef(-tempx, 0.0f, tempy);
			}
			else if(hole[i].holex==3){
				collisionFlag=0;
				decide=1.0;
				//	glTranslatef(fx-localvx, 0.0f, fz-localvy);
			}
		}
	}
	for(int i=0;i<holeNo;++i){
		//printf("localvx and vy are %f %f \n",localvx,localvy);
		if((hole[i].xmin)<=(fx-localvx) && (hole[i].xmax)>=(fx-localvx) && (hole[i].ymin)<=(fz-localvy) && hole[i].ymax>=(fz-localvy)){
			if(hole[i].holex==2){

				//	glTranslatef(-fx+localvx, 0.0f, -fz+localvy);

				//	glTranslatef(0.0f, 0.5f,0.0f);



				collisionFlag=1;	
				//glTranslatef(0.0f, 0.5f,0.0f);

				//		rr=0.5f;
				//		glTranslatef(-tempx, 0.0f, tempy);
			}
		}
	}



	//if(decide<=-0.9 && firstmove>=4 && jump!=1){
	//	printf("you lost\n");
	//	exit(0);

	//}

	//printf("fx and fy are %f %f \n",fx,fz);

	glRotatef(rot, 0.0f, 1.0f, 0.0f);

	//xdis=0.0f;
	//ydis=0.0f;
	float rootx=sqrt(pow(fx-localvx,2)+pow(-fz-localvy,2));
	xdis=rootx*sin(rot*PI*1.0f/180*1.0f);
	ydis=rootx*cos(rot*PI*1.0f/180*1.0f);

	//	if(mode==1){
	//gluLookAt (0.0f, 0.0f,0.0f, 0.0, 0.0, +2.0, 0.0, 1.0, 0.0); 
	//}



	/*if(jump==1){	
	//	printf("vx and vy are %f %f \n",vx,vy);
	//printf("came here again");
	t++;
	robot.Prepare(0.2);


	if(vx>1.0f && vy>1.0f){
	flagHit=1;
	//printf("flagHit Hua\n");
	}
	if(vx<=2.0 && vy<=1.0 && flagHit!=1){
	vx+=0.05;
	totalDis+=0.05;
	vy=vy+(x-g*t);
	glTranslatef(0.0f,vy, -vx);

	}
	if(flagHit==1){
	//printf("yaha aana suru kiya\n");
	vx=vx+	0.05;
	totalDis+=0.05;
	vy=vy-g*t;
	//		printf("vx and vy are %f %f\n",vx,vy);
	glTranslatef(0.0f,vy, -vx);


	}
	if(vy<=0.0f){

	//		printf("yeh bhi hit i kyu nahi hit hua hua\n");

	flagHit=0;
	jump=0;
	rotationDone++;
	localvx+=totalDis*sin(rot*PI*1.0f/180*1.0f);
	localvy+=totalDis*cos(rot*PI*1.0f/180*1.0f);	
	vx=0.05;
	//			vy=0.05;
	vy=0.05;
	x=0.1;
	g=0.005;
	t=0;



	//glTranslatef(0.0f,vy, -vx);


	}

	//glTranslatef(0.0f,vy, -vx);


	//printf("vx and vy in main are %f %f\n",vx,vy);


	}

	if(jump==0){
	if(rotationDone==1){

	//printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	//		glTranslatef(0.0f,vy, -localvx);
	//		rotationDone=0;

	}
	}*/
	glScalef (0.1, 0.1, 0.1);
	robot.DrawRobot(0.0,-6.0,0.0);



	//      robot.DrawRobot(0.5,-4.0,-3.0);
	glPopMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glScalef(0.5,0.5,0.5);
	rx=5;ry=1;
	rz=5;
	a_robot();
	glPopMatrix();




	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glScalef (1.0, 4.0, 1.0);
	glutSolidCube (0.2);
	glPopMatrix();


	/*   glBegin(GL_POLYGON);

	     glColor3f( 1.0, 0.0, 0.0 );     glVertex3f(  0.5, -0.5, -0.5 );      // P1 is red
	     glColor3f( 0.0, 1.0, 0.0 );     glVertex3f(  0.5,  0.5, -0.5 );      // P2 is green
	     glColor3f( 0.0, 0.0, 1.0 );     glVertex3f( -0.5,  0.5, -0.5 );      // P3 is blue
	     glColor3f( 1.0, 0.0, 1.0 );     glVertex3f( -0.5, -0.5, -0.5 );      // P4 is purple

	     glEnd();
	 */ 
	// Draw Ball
	/*  glPushMatrix();
	    glTranslatef(ball_x, ball_y, 0.0f);
	    glColor3f(0.0f, 1.0f, 0.0f);
	    drawBall(ball_rad);
	    glPopMatrix();

	// Draw Triangle
	glPushMatrix();
	glTranslatef(tri_x, tri_y, 0.0f);
	glRotatef(theta, 0.0f, 0.0f, 1.0f);
	glScalef(0.5f, 0.5f, 0.5f);
	drawTriangle();
	glPopMatrix();

	glPopMatrix();*/
	glutSwapBuffers();
}

// Function to handle all calculations in the scene
// updated evry 10 milliseconds
void update(int value) 
{
	if (kj==0)
		fy=0.05;
	//     glutTimerFunc(10, update, 0);



	// Handle ball collisions with box
	if(ball_x + ball_rad > box_len/2 || ball_x - ball_rad < -box_len/2)
		ball_velx *= -1;
	if(ball_y + ball_rad > box_len/2 || ball_y - ball_rad < -box_len/2)
		ball_vely *= -1;

	// Update position of ball
	ball_x += ball_velx;
	ball_y += ball_vely;

	/*
	   int ss=curr_block;
	   int s1,s2,s3,s4;
	   s1=hole[ss].xmin;
	   s2=hole[ss].ymin;
	   s3=hole[ss].xmax;
	   s4=hole[ss].ymax;

	//	cout << s4-s2 << "\n";
	float midx=(s3+s1)/2.0;
	float midy=(s4+s2)/2.0;

	float fddx,fddz,bddx,bddz;
	bddx=fx+0.1*sin(rot*3.14/180);
	bddz=fz+0.1*cos(rot*3.14/180);
	fddx=fx-0.1*sin(rot*3.14/180);
	fddz=fz-0.1*cos(rot*3.14/180);

	fflag=1;
	bflag=1;

	for(int i=0;i<xxxn;i++)
	{

	float mxx,myy,dotp;
	mxx = (hole[xxx[i]].xmax+hole[xxx[i]].xmin)/2.0;
	myy = (hole[xxx[i]].ymax+hole[xxx[i]].ymin)/2.0;
	dotp=0;
	dotp+=(myy-midy)*fddz;
	dotp+=(mxx-midx)*fddx;

	if (dotp>0 && abs(myy-midy)<1 && abs(mxx-midx)<1)
	{
	if (hole[xxx[i]].holex==2)
	fflag=0;
	if (hole[xxx[i]].holex==0)
	{
	if  (valInc < 0.2)
	fflag=1;
	else
	fflag=0;
	}
	}
	else
	{
	if (hole[xxx[i]].holex==2)
	bflag=0;
	if (hole[xxx[i]].holex==0)
	{
	if  (valInc < 0.2)
	bflag=1;
	else
	bflag=0;
	}
	}
	}

	cout << fflag << "\n";

	 */

	fflag=1;
	bflag=1;
	//      printf("%d\n",rblon);   
	float fmin=-10;
	float bmin=10;
	float val;
	int ss=curr_block;
	int s1,s2,s3,s4;
	s1=hole[ss].xmin;
	s2=hole[ss].ymin;
	s3=hole[ss].xmax;
	s4=hole[ss].ymax;

	//	cout << s4-s2 << "\n";
	float midx=(s3+s1)/2.0;
	float midy=(s4+s2)/2.0;
	for(int i=0;i<xxxn;i++)
	{
		float mxx,myy;
		mxx = (hole[xxx[i]].xmax+hole[xxx[i]].xmin)/2.0;
		myy = (hole[xxx[i]].ymax+hole[xxx[i]].ymin)/2.0;
		val=cal_col(fx,fz,mxx,myy);

		if (hole[ss].holex==2)
			continue;
		if (hole[ss].holex==0 && valInc > 1.5)
			continue;
		

		if (val>0 && val<bmin && hole[xxx[i]].holex==2)
			bmin=val;
		if (val<0 && val>fmin && hole[xxx[i]].holex==2)
			fmin=val;
		if (hole[ss].holex==3 || hole[ss].holex == 4)
		{
			if (hole[xxx[i]].holex==0  && valInc > 1)
			{
//				cout << valInc << "\n";
				if (val>0 && val<bmin)
					bmin=val;
				if (val<0 && val>fmin)
					fmin=val;
			}
		}
		if (hole[ss].holex==1)
		{
			if (val>0 && val<bmin)
				bmin=val;
			if (val<0 && val>fmin)
				fmin=val;
		}



	}

	//	cout << fmin << "  " << bmin << "\n";
	if (fmin > -0.9)
		fflag=0;
	if (bmin <  0.9)
		bflag=0;
	/*
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
	 */


	glutTimerFunc(10, update, 0);
}

void drawBox(float len) {
	//	for(int i=0;i<holeNo;++i){
	//			DrawCube(((hole[i].xmin+hole[i].xmax)/2.0f),-2.0,((hole[i].ymin+hole[i].ymax)/2.0f));





	//		}







	//  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//	glColor3f(1.0f, 1.0f, 1.0f);
	///printf("reached here \n");
	//for(int i=0;i<holeNo;++i){
	//			printf("i now is %d\n",i);
	//
	//			printf("sex values %f %f %f %f %d\n",hole[i].xmin,hole[i].xmax,hole[i].ymin,hole[i].ymax,hole[i].holex);


	//}

	for(int i=-40;i<=40;i+=2){
		for(int j=-40;j<=40;j+=2){
			glColor3f(1.0f, 1.0f, 1.0f);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, _textureId1);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glColor3f(0.0f, 0.0f, 1.0f);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);	
			glVertex3f(i,-2.0,j);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(i, -2.0,j+2);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(i+2, -2.0,j+2);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(i+2, -2.0,j);
			glEnd();
			glDisable(GL_TEXTURE_2D);


		}
	}




	int nox=0;
	for(int i=-20;i<=20;i+=2){
		for(int j=-20;j<=20;j+=2){
			glColor3f(1.0f, 1.0f, 1.0f);
			//	printf("j and i are %d %d \n",j,i);
			//	int j=-4;
			//	int i=-5;
			//		glPushMatrix();
			glPushMatrix();

			//glScalef(2.0f, 1.0f, 2.0f);
			//			if(nox==6){
			//		printf("nox is %d\n",nox);
			if(hole[nox].holex==0){
				//		printf("came out of here  but that is not possible\n");	
				if(valInc>=2.0f){
					ceilx=1;
					floorx=0;
				}
				else if(valInc<=0.0f){
					//printf("started here\n");
					ceilx=0;
					floorx=1;
				}

				if(floorx==1){
					valInc+=0.001;	
					///printf("yaha aaya floor\n");


				}
				if(ceilx==1){
					//	printf("yaha pahucha\n");
					valInc-=0.001;

				}
				//	printf("valInc is %f\n",valInc);


				DrawCube((i+1)/2.0f,-3.0+valInc*1.0f,(j+1)/2.0f);
				//			nox++;

			}else if(hole[nox].holex==1){
				DrawCube((i+1)/2.0f,-4.0,(j+1)/2.0f);





			}else if(hole[nox].holex==2){
				DrawCube((i+1)/2.0f,-1.5,(j+1)/2.0f);





			}
			else if(hole[nox].holex==3){
				DrawCube((i+1)/2.0f,-2.0,(j+1)/2.0f);
				//	}

		}
			else if(hole[nox].holex==4){
				glPushMatrix();
				glTranslatef((i+1)/2.0f,-2.0,(j+1)/2.0f);
				glutMSolidCube(1);
				glPopMatrix();
				//	}

		}
		nox++;



		//	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		/*	 		glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, _textureId);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
					glColor3f(1.0f, 1.0f, 1.0f);
					glBegin(GL_QUADS);
					glTexCoord2f(0.0f, 0.0f);	
					glVertex3f(i,-2.0,j);
					glTexCoord2f(1.0f, 0.0f);
					glVertex3f(i, -2.0,j+2);
					glTexCoord2f(1.0f, 1.0f);
					glVertex3f(i+2, -2.0,j+2);
					glTexCoord2f(0.0f, 1.0f);
					glVertex3f(i+2, -2.0,j);
					glEnd();
					glDisable(GL_TEXTURE_2D);
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
					glBegin(GL_QUADS);
					glColor3f(1.0f, 1.0f, 1.0f);
					glVertex3f(i,-2.0,j);
					glColor3f(0.0f, 1.0f, 1.0f);
					glVertex3f(i, -2.0,j+2);
					glColor3f(1.0f, 1.0f, 1.0f);
					glVertex3f(i+2, -2.0,j+2);
					glColor3f(0.0f, 1.0f, 1.0f);
					glVertex3f(i+2, -2.0,j);
					glEnd();*/
		//glPushMatrix();

		//		glScalef(2.0f, 1.0f, 2.0f);

		//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		/*if((abs(i)+abs(j))%9==1){

		  DrawCube((i+1)/2,-4.0,(j+1)/2);


		  }else if((abs(i)+abs(j))%9==2){
		  if(valInc>=2.0f){
		  ceilx=1;
		  floorx=0;
		  }
		  else if(valInc<=0.0f){
		//printf("started here\n");
		ceilx=0;
		floorx=1;
		}

		if(floorx==1){
		valInc+=0.001;	
		///printf("yaha aaya floor\n");


		}
		if(ceilx==1){
		//	printf("yaha pahucha\n");
		valInc-=0.001;

		}
		//	printf("valInc is %f\n",valInc);


		DrawCube((i+1)/2.0f,-3.0+valInc*1.0f,(j+1)/2.0f);



		}else{
		DrawCube((i+1)/2.0f,-2.0,(j+1)/2.0f);
		}*/
		glPopMatrix();
		/*glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		  glBegin(GL_QUADS);
		  glColor3f(1.0f, 1.0f, 1.0f);
		  glVertex3f(i,-2.0,j);
		  glColor3f(0.0f, 1.0f, 1.0f);
		  glVertex3f(i, -2.0,j+2);
		  glColor3f(1.0f, 1.0f, 1.0f);
		  glVertex3f(i+2, -2.0,j+2);
		  glColor3f(0.0f, 1.0f, 1.0f);
		  glVertex3f(i+2, -2.0,j);
		  glEnd();

		 */

		//printf("i and j are %d %d\n",i,j);
		/*	glPushMatrix();
			glTranslatef((i+1), -1.9, (j+1));
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			glutSolidCube(0.5);
			glPopMatrix();
		 */


		//		glPopMatrix();

	}


}


//	glDisable(GL_TEXTURE_2D);
glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

// glutSwapBuffers();


}

void drawBall(float rad) {

	glBegin(GL_TRIANGLE_FAN);
	for(int i=0 ; i<360 ; i++) {
		glVertex2f(rad * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)));
	}
	glEnd();
}

void drawTriangle() {

	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glEnd();
}

// Initializing some openGL 3D rendering options
// Function called when the window is resized
void handleResize(int w, int h)
{

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float)w / (float)h, 0.1f, 200.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void handleKeypress1(unsigned char key, int x, int y)
{
	if(key=='c'){
		rotxx-=0.5;		
	}
	if(key=='v'){
		rotxx+=0.5;
	}
	if(key=='b'){
		rotyy-=0.5;		
	}
	if(key=='n'){
		rotyy+=0.5;
	}




	if(key=='k'){
		xinc-=1;
		if(xinc==-20){
			xinc=0;
		}
	}
	if(key=='j'){
		yinc+=1;
		if(yinc==20){
			yinc=0;
		}

	}
	if(key=='g'){
		tilerot-=0.5;
	}
	if(key=='h'){
		tilerot+=0.5;

	}

	if(key=='i'){
		//printf("calue of light is %d\n",light);
		if(light==0){
			light=1;

		}else{

			light=0;
		}

	}
	if(key == 'm'){
		//		if(mode==0){
		//			mode=1;
		//		}	
		//		else{
		//			mode=0;
		//		}	

		mode=(mode+1)%5;
		//	printf("mode now is %d \n",mode);
	}


	if(key==32){
		//jump=1;
		kj=1;
		rotationDone=0;

		totalDis=0;
		//		printf("caught space\n");
	}


	if(key == 'r'){
		robot.Prepare(0.2);


		rot+=5.0;
	}

	if(key == 'l'){
		robot.Prepare(0.2);


		rot-=5.0;

	}

	if (key == 27) {
		exit(0);     // escape key is pressed
	}
	if(key=='w'){
		ycam+=0.1;

	}  
	if(key=='s'){
		ycam-=0.1;

	}
	if(key=='a'){
		xcam-=0.1;

	}
	if(key=='d'){
		xcam+=0.1;

	}
	if(key=='z'){
		zcam+=0.1;
	}
	if(key=='x'){
		zcam-=0.1;
	}
	if(key=='q'){
		rotCam-=0.5;		
	}
	if(key=='e'){
		rotCam+=0.5;
	}

}

void handleKeypress2(int key, int x, int y) {



	if (key == GLUT_KEY_LEFT){
		//	robot.Prepare(0.2);

		//   fx -= 0.1;
		rot+=5.0;


	}
	if (key == GLUT_KEY_RIGHT){
		//    fx += 0.1;
		rot-=5.0;

	}
	if (key == GLUT_KEY_UP){
		//		rx++;
		firstmove++;
		//	robot.Prepare(0.2);

		//        fz += 0.1;
		//	if(collisionFlag==0 || backflag==1){
		if(fflag==1){
			//forflag=1;
			//		printf("came to forward alternate block");
			backflag=0;
			collisionFlag=0;
			fx=fx-0.1*sin(rot*3.14/180);
			fz=fz-0.1*cos(rot*3.14/180);
			//printf("fx and fz are %f %f \n",fx,fz);
		}
		/*
		   else {
		//printf("came to forward alternate block");
		collisionFlag=0;
		forflag=1;
		fx=fx+0.1*sin(rot*3.14/180);
		fz=fz+0.1*cos(rot*3.14/180);


		}	
		 */
		/*if(collisionFlag==0){
		//forflag=1;
		printf("came to forward alternate block");
		//backflag=0;
		collisionFlag=0;
		fx=fx-0.1*sin(rot*3.14/180);
		fz=fz-0.1*cos(rot*3.14/180);
		//printf("fx and fz are %f %f \n",fx,fz);
		}else {
		printf("came to forward alternate block");
		collisionFlag=0;
		//forflag=1;
		fx=fx+0.1*sin(rot*3.14/180);
		fz=fz+0.1*cos(rot*3.14/180);


		}	


		 */








		robot.Prepare(0.2);
		//	printf("hole checked is %d\n",i);

	}
	if (key == GLUT_KEY_DOWN){
		//      fz -= 0.1;
		//	robot.Prepare(0.2);
		firstmove++;
		if(bflag==1)
		{
			//	backflag=1;
			forflag=0;
			collisionFlag=0;
			fx=fx+0.1*sin(rot*3.14/180);
			fz=fz+0.1*cos(rot*3.14/180);
		}
		/*
		   else{
		   collisionFlag=0;
		   backflag=1;
		   fx=fx-0.1*sin(rot*3.14/180);
		   fz=fz-0.1*cos(rot*3.14/180);





		   }
		 */
		/*	if(collisionFlag==0){
		//	backflag=1;
		//	forflag=0;
		collisionFlag=0;
		fx=fx+0.1*sin(rot*3.14/180);
		fz=fz+0.1*cos(rot*3.14/180);
		}else{
		collisionFlag=0;
		//	backflag=1;
		fx=fx-0.1*sin(rot*3.14/180);
		fz=fz-0.1*cos(rot*3.14/180);





		}
		 */
		robot.Prepare(0.2);


	}
	}

	void handleMouseclick(int button, int state, int x, int y) {

		if (state == GLUT_DOWN)
		{
			if (button == GLUT_LEFT_BUTTON)
				theta += 15;
			else if (button == GLUT_RIGHT_BUTTON)
				theta -= 15;
		}
	}

	void drawWorld(void)
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		glEnable(GL_TEXTURE_2D);
		rblon=0;
		mblon=0;
		/*
		   if(worldiflag==1)
		   {
		   rblon=0;
		   mblon=0;
		   }
		 */
		glPushMatrix();

		for(int i=-10;i<10;i++)
		{
			for(int j=-10;j<10;j++)
			{
				//		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
				j-=10;
				/*

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


				 */

				//		glBindTexture(GL_TEXTURE_2D, _tex2);
				cout << "earliererere "<< i  << " " << j << "\n";

				if(ran[i+5][j+10]>1 && ((i+0.5)!=-4.5 || (j+0.5)!=-0.5) )
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
				//			cout << "keatefrsdf "<< i  << " " << j << "\n";
				j+=10;
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

