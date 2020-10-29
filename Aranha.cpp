#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define PI 3.14

static  int radianocircle1 = 2;
double rotacao=0;
bool clicou = false;
bool rodar = false;


float rotacaoperna1 = 0;
float rotacaoperna11=0;
float rotacaoperna2 = 0;
float rotacaoperna21 =0;
float rotacaoperna3 = 0;
float rotacaoperna31 = 0;
float rotacaoperna4 = 0;
float rotacaoperna41 = 0;
int direcao = 100;


GLint wsize_x = 1000;
GLint wsize_y = 650;

GLint x_pixel;
GLint y_pixel;
GLint x_pixeldestino;
GLint y_pixeldestino;


double x_float;
double y_float;

double x_ut=0;
double y_ut=0;
int move=0;

double constante = 57.295;

struct vetor{
	double x,y;
};

vetor v1;
vetor v2;


double angulo(void){

	return atan2(y_float-y_ut,x_float-x_ut)*constante;
}

void convertpixel(float x, float y){
	x_pixeldestino=(x_ut+6)/(12.0/wsize_x);
	y_pixeldestino=-(y_ut-6)/(12.0/wsize_y);
	
}


void movimento (int passo){

		if(clicou){
		
		if(x_ut <= x_float){
			x_ut += 0.03;
			
		}
	
		
		if (y_ut <= y_float) {
			y_ut += 0.03;
		} 
		
		
		if(x_ut>=x_float){
			x_ut -= 0.03;
		}
		
	
		if(y_ut >= y_float){
			y_ut -= 0.03;
			
	
	}
	
	convertpixel((GLint)x_ut,(GLint)y_ut);
	
	if(((x_pixel-x_pixeldestino<=3 and x_pixeldestino-x_pixel<=3)) and y_pixel-y_pixeldestino<=3 and y_pixeldestino - y_pixel <=3 )direcao = 1000;


	   
	
	
	if(direcao==0){
		    
		    rotacaoperna1 += 0.2;
		    rotacaoperna11 += 0.2;
		    rotacaoperna2 -= 0.2;
			rotacaoperna21 -= 0.2;
			rotacaoperna31 += 0.2;
			rotacaoperna3 += 0.2;
			rotacaoperna4 -= 0.2;
			rotacaoperna41 -= 0.2;
			
	}
	
	
	if(rotacaoperna2<-8) direcao = 1;	
	
	if(direcao==1){
			rotacaoperna1 -= 0.2;
		    rotacaoperna11 -= 0.2;
	        rotacaoperna2 += 0.2;
			rotacaoperna21 += 0.2;
			rotacaoperna3 -= 0.2;
			rotacaoperna31 -=0.2;
			rotacaoperna4 += 0.2;
			rotacaoperna41 += 0.2;
	
	}

	if(rotacaoperna2>8) direcao = 0;
	}
	
		

	glutPostRedisplay();
	glutTimerFunc(10,movimento,1);
}

void init(void){
  glClearColor (0.0, 0.0, 0.0, 0.0);
}

void corpo(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < num_segments; i++)
    {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}



void olho(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < num_segments; i++)
    {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}


void perna(float x1,float y1, float x2, float y2){
 glBegin(GL_LINES);
 glColor3f(1.0,1.0,1.0);
 glVertex3f(x1,y1,0.0);
 glVertex3f(x2,y2,0.0);
 glEnd();
 
}

void display(void){
	
glPushMatrix();	

if(clicou){
	
glTranslated(x_ut,y_ut,0.0);
glRotated(rotacao-90,0.0,0.0,1.0);
glTranslated(-x_ut,-y_ut,0.0);

}

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


//Copiando matriz original


//Fazendo translação cefalotorax


glTranslated(x_ut,y_ut,0.0);
corpo(0.00,0.00,0.35,50);
glPushMatrix();


//Articulaçao 1.0 da perna 1 esquerda
glRotated(rotacaoperna1,0.0,0.0,1.0);

perna(-0.29,0.1,-0.5,1.1);
//Articulação 1.1 da perna 1 esquerda
perna(-0.5,1.1,-0.8,1.7);
glPopMatrix();
//Articulaçao 1.0 da perna 1 direita
glPushMatrix();
glRotated(rotacaoperna11,0.0,0.0,1.0);
perna(0.29,0.1,0.5,1.1);
//Articulaçao 1.1 da perna 1 direita
perna(0.5,1.1,0.8,1.7);
glPopMatrix();

//Articulaçao 1.0 da perna 2 esquerda
glPushMatrix();
glRotated(rotacaoperna2,0.0,0.0,1.0);
perna(-0.36,0.08,-0.8,0.35);
//Articulacao 1.1 da perna 2 esquerda
perna(-0.8,0.35,-1.1,-0.2);
glPopMatrix();

//Articulaçao 1.0 da perna 2 direita
glPushMatrix();
glRotated(rotacaoperna21,0.0,0.0,1.0);
perna(0.36,0.08,0.8,0.35);
//Articulacao 1.1 da perna 2 direita
perna(0.8,0.35,1.1,-0.2);
glPopMatrix();

//Articulaçao 1.0 da perna 3 esquerda
glPushMatrix();
glRotated(rotacaoperna3,0.0,0.0,1.0);
perna(-0.36,-0.08,-0.82,0.2);
//Articulaçao 1.1 da perna 3 esquerda
perna(-0.82,0.2,-1.05,-0.26);
glPopMatrix();
//Articulaçao 1.0 da perna 3 direita
glPushMatrix();
glRotated(rotacaoperna3,0.0,0.0,1.0);
perna(0.36,-0.08,0.82,0.2);
//Articulaçao 1.1 da perna 3 direita
perna(0.82,0.2,1.05,-0.26);
glPopMatrix();
//Articulaçao 1.0 da perna 4 esquerda
glPushMatrix();
glRotated(rotacaoperna4,0.0,0.0,1.0);
perna(-0.30,-0.23,-0.82,0.05);
//Articulaçao 1.1 da perna 4 esquerda
perna(-0.82,0.05,-1.3,-1.1);
//Articulaçao 1.0 da perna 4 direita
glPushMatrix();
glRotated(rotacaoperna41,0.0,0.0,1.0);
perna(0.30,-0.23,0.82,0.05);
//Articulaçao 1.1 da perna 4 direita
perna(0.82,0.05,1.3,-1.1);
glPopMatrix();

glPushMatrix();
//Posiciondo olho direito
glTranslated(0.15,0.1,0.0);
olho(0.0,0.0,0.055,50);
//Posicionando olho esquerdo
glTranslated(-0.3,0.0,0.0);
olho(0.0,0.0,0.055,50);
//voltando a matriz de origem
glPopMatrix();




//Copia matriz de origem
glTranslated(0.0,-1.0,0.0);
corpo(0.0,0.06,0.6,50);
glPopMatrix();
glFlush();
  glutSwapBuffers();
}



void reshape (int w, int h){
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  //gluPerspective(90.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
  glOrtho(-6,6,-6,6,-6,6);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  //glTranslatef (0.0, 0.0, -5.0);
}




void mouse(GLint button, GLint action, GLint x, GLint y)
{
  switch(button)
  {
    case GLUT_LEFT_BUTTON:
    {
    	x_pixel = x;
    	y_pixel = y;
    	clicou = true;
    	rodar = true;
    	convertpixel((GLint)x_ut,(GLint)y_ut);
    	double angle = angulo();
    	rotacao = angle;
    	printf("%f \n",angle);
    	x_float = x_pixel*(12.0/wsize_x) -6;
        y_float = 6 - y_pixel*(12.0/wsize_y);
    	direcao = 0;
    	//rotacao = angulo()*2;
    	
    	
      break;
    }
    case GLUT_MIDDLE_BUTTON:
    {

      break;
    }
    case GLUT_RIGHT_BUTTON:
    {
      break;
    }
    default: break;
  }

	 display();

 }
 



int main(int argc, char** argv){
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
  

  
  glutInitWindowSize (wsize_x,wsize_y); 
  glutInitWindowPosition (100,0);
  glutCreateWindow (argv[0]);
  init ();
  glutDisplayFunc(display); 
  glutTimerFunc(10,movimento,1.0);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);
  glutMainLoop();
  return 0;
}
