/*
 * CS 4735 Fall 2001 Term Project - Alex O'Neill 
 *
 * File: myLego.cpp
 *
 * Contains implementations of the classes defined in LegoStructs.h.
 *
 */

#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include "LegoStructs.h"
#include "utilityFuncs.h"
#include <string>
using namespace std;

//set the default values for gluLookat()
float eyeX = 2.0;
float eyeY = 4.0;
float eyeZ = 10.0;
float lookX = 0.0;
float lookY = 0.0;
float lookZ = 0.0;
float upX = 0.0;
float upY = 1.0;
float upZ = 0.0;

float rotationAngleX = 0.0;
float rotationAngleY = 0.0;
float rotationAngleZ = 0.0;
float translationX = 0.0;
float translationY = 0.0;
float translationZ = 0.0;

int winIdSub, winIdMain, menIdMain, menIdSubLength, menIdSubWidth, menIdSubColor;

int g_NewLength = 1, g_NewWidth = 1, g_NewColor = 0, g_NewX = 0, g_NewY = 0;

bool g_BuildMode = false;

//initial light source
static GLfloat init_light[] = {-3.0, 30.0, -20.0, 1.0};

static LegoStruct * lsPtr;

P_Block g_NewBlock;

void checkForNewBlock() {
  if ( g_NewLength == 0 )
    g_NewLength = 1;
  if ( g_NewWidth == 0 )
    g_NewWidth = 1;
  if ( g_NewBlock == 0 )
    g_NewBlock = new GenericBlock( g_NewLength, g_NewWidth, g_NewColor, 0, g_NewX, g_NewY ); 
  if ( lsPtr != 0 )
    g_NewBlock->setLayer( lsPtr->getHeight() );

}

/* Draw the marker for deleting blocks
 */
void drawBolt() {
  static const float boltColor[4] = {0.0, 1.0, 1.0, 1.0 };
  glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, boltColor );
		 
  //  glEnable(GL_POLYGON_OFFSET_FILL);
  glBegin(GL_LINES); 
  glVertex3f( g_NewX + 0.25, 0, g_NewY + 0.25 );
  glVertex3f( g_NewX + 0.25, lsPtr->getHeight(), g_NewY + 0.25 );
  glVertex3f( g_NewX + 0.75, 0, g_NewY + 0.25 );
  glVertex3f( g_NewX + 0.75, lsPtr->getHeight(), g_NewY + 0.25 );
  glVertex3f( g_NewX + 0.25, 0, g_NewY + 0.75 );
  glVertex3f( g_NewX + 0.25, lsPtr->getHeight(), g_NewY + 0.75 );
  glVertex3f( g_NewX + 0.75, 0, g_NewY + 0.75 );
  glVertex3f( g_NewX + 0.75, lsPtr->getHeight(), g_NewY + 0.75 );

  glEnd();
  //glDisable(GL_POLYGON_OFFSET_FILL);

}

/* Main Menu event handler callback function.
 */
void mainMenu( int value ) {
  // Delete Block
  if ( value == 4 ) {
    delete(g_NewBlock);
    g_NewBlock = 0;
  }
  g_NewLength = g_NewWidth = 0;
}

void lengthSubMenu( int value ) {
  checkForNewBlock();
  g_NewBlock->setLength( (g_NewLength = value) );
  glutPostRedisplay();
}

void widthSubMenu( int value ) {
  checkForNewBlock();
  g_NewBlock->setWidth( (g_NewWidth = value) );
  glutPostRedisplay();
}

void colorSubMenu( int value ) {
  checkForNewBlock();
  g_NewBlock->setColor( (g_NewColor = value) );
  glutPostRedisplay();
}

/* Init Method */
void init() {


  glClearColor(0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_SMOOTH);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glPolygonOffset(1.0, 0.2);

}
/* Menu and submenu initialization.
 */
void menuInit() {
  menIdSubLength = glutCreateMenu( lengthSubMenu );
  glutAddMenuEntry( "1", 1 );
  glutAddMenuEntry( "2", 2 );
  glutAddMenuEntry( "3", 3 );
  glutAddMenuEntry( "4", 4 );
  glutAddMenuEntry( "5", 5 );
  glutAddMenuEntry( "6", 6 );
  glutAddMenuEntry( "7", 7 );
  glutAddMenuEntry( "8", 8 );
  glutAddMenuEntry( "9", 9 );
  glutAddMenuEntry( "10", 10 );

  menIdSubWidth = glutCreateMenu( widthSubMenu );
  glutAddMenuEntry( "1", 1 );
  glutAddMenuEntry( "2", 2 );
  glutAddMenuEntry( "3", 3 );
  glutAddMenuEntry( "4", 4 );
  glutAddMenuEntry( "5", 5 );
  glutAddMenuEntry( "6", 6 );
  glutAddMenuEntry( "7", 7 );
  glutAddMenuEntry( "8", 8 );
  glutAddMenuEntry( "9", 9 );
  glutAddMenuEntry( "10", 10 );

  menIdSubColor = glutCreateMenu( colorSubMenu );
  glutAddMenuEntry( "White", 0 );
  glutAddMenuEntry( "Grey", 1 );
  glutAddMenuEntry( "Red", 2 );
  glutAddMenuEntry( "Yellow", 3 );
  glutAddMenuEntry( "Dull Cyan", 4 );
  glutAddMenuEntry( "Green", 5 );
  glutAddMenuEntry( "Blue", 6 );
  glutAddMenuEntry( "Cyan", 7 );
  glutAddMenuEntry( "Orange", 8 );
  glutAddMenuEntry( "Magenta", 9 );

  menIdMain = glutCreateMenu( mainMenu );
  glutAddSubMenu( "New Block's Length", menIdSubLength );
  glutAddSubMenu( "New Block's Width", menIdSubWidth );
  glutAddSubMenu( "New Block's Colour", menIdSubColor );
  glutAddMenuEntry( "Delete Block", 4 );
  glutAttachMenu( GLUT_LEFT_BUTTON );
}

/* Subwindow Reshape Method.
 */
void subReshape( int w, int h ) {
  glViewport( 0, 0, w, h );
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  gluOrtho2D( 0.0f, 1.0f, 0.0f, 1.0f );
}

/* Reshape Method 
 */
void reshape(int w, int h) {
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0, (GLfloat) w / (GLfloat) h, 1.0, 200.0);
  glMatrixMode(GL_MODELVIEW);
}

/* Submenu Display Method
 */
void subDisplay() {
  glutSetWindow( winIdSub );
  glClearColor( 0.25, 0.25, 0.25, 0.0 );
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  /* Draw Border.
   */
  glColor3f( 0.0f, 1.0f, 0.0f );
  glBegin( GL_LINE_LOOP );
  glVertex2f( 0.0f, 0.0f);
  glVertex2f( 0.0f, 0.99f );
  glVertex2f( 0.999f, 0.99f );
  glVertex2f( 0.999f, 0.0f );
  glEnd();
  
  
  /* Write any text.
   */
  glColor3f( 1.0f, 1.0f, 1.0f );
  glRasterPos2f( 0.15f, 0.75f );
  drawString( "a, s, d, w: Move Block / Delete Marker  Space: Drop Block / Delete" );
  glRasterPos2f( 0.10f, 0.25f );
  drawString( "j, k, l, n, m: Move Camera  o: Rotation Reset  Mouse Click: Popup Menu" );
  glutPostRedisplay();
  
  glutSwapBuffers();
}

/* Main Display Method 
 */
void display() {
  static int i;
  glMatrixMode(GL_MODELVIEW);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //  glPushMatrix();
  glLoadIdentity();

  //glOrtho(0.0,450.0, 0.0, 450.0, .1, 1000);

  //viewer position
  glPushMatrix();
  glLoadIdentity();
  gluLookAt(10.0, 45.0, 30.0, 10.0, 0.0, 0.0, upX, upY, upZ);
  
  glTranslatef( translationX, translationY, translationZ );
  glTranslatef( 10.0, 10.0, 10.0 );

  glRotatef(rotationAngleX, 0.0, 1.0, 0.0 );
  glTranslatef( -10.0, -10.0, -10.0 );

  glTranslatef( 10.0, 10.0, 10.0 );
  glRotatef(rotationAngleZ, 1.0, 0.0, 0.0);
  glTranslatef( -10.0, -10.0, -10.0);  

  //glTranslatef( translationX, translationY, translationZ );
  //show light source position
  glLightfv(GL_LIGHT0, GL_POSITION, init_light);

  lsPtr->draw();

  if ( g_NewBlock != 0 ) {
    g_NewBlock->draw();
  }
    drawBolt();

  glPopMatrix();

  glFlush();
  glutSwapBuffers();
}



//keyboard function to rotate the lego block
/* This function will allow the user to do 4 different things with their camera view
They will be able to control the slide, roll, yaw and pitch of their camera
*/

//*NOTE* -> will we need to be able to roll the lego blocks around the z-axis,
//          or does an arial view suffice?

void keyboard(unsigned char key, int a, int b)
{

  switch(key) {
// pressing the escape key will close the window (saves data first)
  case 27:
    lsPtr->saveToFile("test1.lego");
    exit(0);
    break;

// pressing 'j' will slide the camera forward
  case 'j':
    /*    eyeX += 0.2;
    eyeY += 0.2;
    eyeZ += 0.2;      */
    translationZ += 0.5;
    glutPostRedisplay();
    break;
    
// pressing 'J' will slide the camera back towards its original position
  case 'J':
    /*    eyeX += -0.2;

    eyeZ += -0.2; */
    translationZ -= 0.5;
    glutPostRedisplay();
    break;
    
// pressing 'k' will yaw the camera (move it from left to right along the x-axis)
  case 'k':
    //    eyeX += 0.5; 
    translationX += 0.5;
    glutPostRedisplay();
    break;

// pressing 'K' will yaw the camera in the opposite direction
  case 'K':
    //eyeX -= 0.5;
    translationX -= 0.5;
    glutPostRedisplay();
    break;
    
// pressing 'l' will pitch the camera (move it up and down along the y-axis)
 case 'l':
   //eyeY += 0.5;
   //lookY += 0.5;
   translationY += 0.5;
   glutPostRedisplay();
   break;

  case 'L':
    //eyeY -= 0.5;
    //lookY -= 0.5;
    translationY -= 0.5;
    glutPostRedisplay();
    break;

  case 'n':
    rotationAngleX += 5.0;
    glutPostRedisplay();
    break;

  case 'N':
    rotationAngleX -= 5.0;
    glutPostRedisplay();
    break;

  case 'm':
    rotationAngleZ += 5.0;
    glutPostRedisplay();
    break;

  case 'M':
    rotationAngleZ -= 5.0;
    glutPostRedisplay();
    break;

    //set back to original view
  case 'o':
    rotationAngleX = 0.0;
    rotationAngleZ = 0.0;
    glutPostRedisplay();
    break;
    
  case 'a':
    g_NewX = ( g_NewX > 0 ? g_NewX - 1 : 0 );
    if ( g_NewBlock != 0 )
      g_NewBlock->setX( g_NewX );
    glutPostRedisplay();
    break;

  case 'd':
    g_NewX = ( g_NewX + g_NewLength < lsPtr->getLength()
	       ? g_NewX + 1 : g_NewX );
    if ( g_NewBlock != 0 )
      g_NewBlock->setX( g_NewX );
    glutPostRedisplay();
    break;

  case 'w':
    g_NewY = ( g_NewY > 0 ? g_NewY - 1 : 0 );
    if ( g_NewBlock != 0 )
      g_NewBlock->setY( g_NewY );
    glutPostRedisplay();
    break;

  case 's':
    g_NewY = ( g_NewY + g_NewWidth < lsPtr->getWidth()
	       ? g_NewY + 1 : g_NewY );
    if ( g_NewBlock != 0 )
      g_NewBlock->setY( g_NewY );
    glutPostRedisplay();
    break;

  case ' ':
    // Drop the block.
    if ( g_NewBlock != 0 ) {
      lsPtr->addBlock( g_NewBlock, g_NewBlock->getX(), g_NewBlock->getY() );
      g_NewBlock = 0;
      checkForNewBlock();
    }
    else {
      lsPtr->deleteBlock( g_NewX, g_NewY );
    }
    glutPostRedisplay();
    break;

//if any other keys are pressed do nothing
  default:
    break;
  }
}

/* Implement mouse functionality */
void mouse(int button, int state, int x, int y)
{
  /*
  // these functions are for the main window
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {
    translationZ += 0.5;
    glutPostRedisplay();
  }
  else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
    {
      translationX -= 0.5;
      display();      
    }
  else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
      translationY += 0.5;
      display(); 
    }
  */
}

/* driver of the program.
All program initializations done here.  
Keyboard and Mouse listeners are also added
*/
int main(int argc, char** argv)
{
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(450,450);
  glutInitWindowPosition(0,0);
  winIdMain = glutCreateWindow("3D Lego Project");
  init();
  menuInit();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);
  glutKeyboardFunc(keyboard);

  winIdSub = glutCreateSubWindow( winIdMain, 5, 5, 440, 45 );
  glutDisplayFunc( subDisplay );
  glutReshapeFunc( subReshape );

  lsPtr = loadFromFile( "test1.lego" );
  lsPtr->saveToFile();

  checkForNewBlock();

  glutMainLoop();
  return 0;
}


