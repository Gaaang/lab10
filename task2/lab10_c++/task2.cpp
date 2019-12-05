#include<Windows.h>      
#include<stdio.h>    
#include<gl/GL.h>      
#include<gl/GLU.h>   
#include <freeglut.h>
#include <freeglut_ext.h>
#include <freeglut_std.h>     
#include<conio.h>    
#include<stdio.h>    
#include<math.h>    
#include<string.h>    

int num = 0;
int width = 0, height = 0;
int rotate_mode = 0;
double rotate_x = 0;
double rotate_y = 0;
double rotate_z = 0;
  
void Init_OpenGL()
{
	// цвет фона черный   
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
}

void Display_Objects(void)
{
	// очистка окна
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (num == 0)
	{
		glViewport(0, 0, width, height);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(65.0, width / height, 1.0, 1000.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(-0.3, 0.5, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	}
	else
	{
		glViewport(0, 0, width, height);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-2, 2, -2, 2, -2, 2);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

	glTranslatef(0, 0.0, 0.0);
	glColor3f(1, 1, 1);

	if (rotate_mode == 0)
	{
		glRotatef(rotate_x, 1, 0, 0);
		glRotatef(rotate_y, 0, 1, 0);
		glRotatef(rotate_z, 0, 0, 1);
	}

	//золотой
	glPushMatrix();
	glTranslatef(1, 0.0, 1.0);
	if (rotate_mode)
	{
		glRotatef(rotate_x, 1, 0, 0);
		glRotatef(rotate_y, 0, 1, 0);
		glRotatef(rotate_z, 0, 0, 1);
	}

	glColor3f(1, 0.78, 0.09);
	float mat_specular[] = { 1,1,1,1 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 128.0);
	glScalef(1, 2, 1);
	glutSolidCube(0.5);
	glPopMatrix();

	//серебрянный
	glPushMatrix();
	if (rotate_mode == 1)
	{
		glTranslatef(1, 0.0, 1.0);
		glRotatef(rotate_x, 1, 0, 0);
		glRotatef(rotate_y, 0, 1, 0);
		glRotatef(rotate_z, 0, 0, 1);
		glTranslatef(-1, 0.0, -1.0);
	}
	glTranslatef(0.25, -0.125, 1.0);
	if (rotate_mode == 2)
	{
		glRotatef(rotate_x, 1, 0, 0);
		glRotatef(rotate_y, 0, 1, 0);
		glRotatef(rotate_z, 0, 0, 1);
	}
	glColor3f(0.75, 0.75, 0.75);
	glScalef(1, 1.5, 1);
	glutSolidCube(0.5);
	glPopMatrix();

	//бронзовый
	glPushMatrix();
	if (rotate_mode == 1)
	{
		glTranslatef(1, 0.0, 1.0);
		glRotatef(rotate_x, 1, 0, 0);
		glRotatef(rotate_y, 0, 1, 0);
		glRotatef(rotate_z, 0, 0, 1);
		glTranslatef(-1, 0.0, -1.0);
	}
	glTranslatef(1.7, -0.25, 1.0);
	if (rotate_mode == 2)
	{
		glRotatef(rotate_x, 1, 0, 0);
		glRotatef(rotate_y, 0, 1, 0);
		glRotatef(rotate_z, 0, 0, 1);
	}
	glColor3f(0.8, 0.5, 0.2);
	glutSolidCube(0.5);
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}
   
void Reshape(int w, int h)
{
	width = w; height = h;
  
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	    
	glMatrixMode(GL_PROJECTION);
   
	glLoadIdentity();
	gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 1000.0);
   
	glMatrixMode(GL_MODELVIEW);
  
	glLoadIdentity();  
	gluLookAt(-0.3, 0.5, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void specialKeys(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP: rotate_x += 5; break;
	case GLUT_KEY_DOWN: rotate_x -= 5; break;
	case GLUT_KEY_RIGHT: rotate_y += 5; break;
	case GLUT_KEY_LEFT: rotate_y -= 5; break;
	case GLUT_KEY_PAGE_UP: rotate_z += 5; break;
	case GLUT_KEY_PAGE_DOWN: rotate_z -= 5; break;
	case GLUT_KEY_F1:
		rotate_x = rotate_y = rotate_z = 0;
		rotate_mode = 0; break;
	case GLUT_KEY_F2:
		rotate_x = rotate_y = rotate_z = 0; rotate_mode = 1; break;
	case GLUT_KEY_F3:
		rotate_x = rotate_y = rotate_z = 0; rotate_mode = 2; break;
	}
	glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		num = (num + 1) % 2;
	}
	glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y)
{
	if (key == '\1')
		rotate_mode = 1;
}
    
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("OpenGL Demo");
	Init_OpenGL();
	glutDisplayFunc(Display_Objects);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutSpecialFunc(specialKeys);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();
	return 0;
}