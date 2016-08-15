#include <OpenGL/gl.h>

#include "consts.h"
#include "glpoint.h"

/* drawBlock(point, double, double)
   @p1 - the lower Left-hand point on the front face of the lego block before viewport rotation
   @length - length of Lego block
   @width - width of Lego block
   Assumed that height of each Lego block will be 1
*/
void drawBlock(point  p1, GLdouble length, GLdouble width)
{
  glBegin(GL_QUAD_STRIP); // draw the four rectangles, not the  top and bottom of lego piece
    // Vertices will be traversed in order v0,v1,v3,v2, then v2,v3,v5,v4 etc. until done 4 quads

     glVertex3d(p1.x, p1.y, p1.z - width); //v0 
     glVertex3d(p1.x, p1.y + LEGO_HEIGHT, p1.z - width); //v1
     glVertex3d(p1.x, p1.y, p1.z); //v2
     glVertex3d(p1.x, p1.y + LEGO_HEIGHT, p1.z); //v3
     glVertex3d(p1.x + length, p1.y, p1.z); //v4
     glVertex3d(p1.x + length, p1.y + LEGO_HEIGHT, p1.z); //v5
     glVertex3d(p1.x + length, p1.y, p1.z - width); //v6
     glVertex3d(p1.x + length, p1.y + LEGO_HEIGHT, p1.z - width); // v7
     // v8 = v0 and v9 = v1, but they have to be re-written
     glVertex3d(p1.x, p1.y, p1.z - width); // v8
     glVertex3d(p1.x, p1.y + LEGO_HEIGHT, p1.z - width); // v9

  glEnd();

  // draw the top and bottom of the lego object
  glBegin(GL_QUADS);
 
     //top: vertices (v3,v5,v7,v9)
     glVertex3d(p1.x, p1.y + LEGO_HEIGHT, p1.z); //v3
     glVertex3d(p1.x + length, p1.y + LEGO_HEIGHT, p1.z); //v5
     glVertex3d(p1.x + length, p1.y + LEGO_HEIGHT, p1.z - width); //v7
     glVertex3d(p1.x, p1.y + LEGO_HEIGHT, p1.z - width); //v9
     
     //bottom  (v2,v4,v6,v8)
     glVertex3d(p1.x, p1.y, p1.z); //v2
     glVertex3d(p1.x + length, p1.y, p1.z); //v4
     glVertex3d(p1.x + length, p1.y, p1.z - width); //v6
     glVertex3d(p1.x, p1.y, p1.z - width); //v8

  glEnd();

  // Flush the buffer to force drawing of all objects
  glFlush();
}

void myDrawBlock(){
   glClear(GL_COLOR_BUFFER_BIT);
      // declare any point for now!
      point p1;
      p1.x = 320.0;
      p1.y = 240.0;
      p1.z = 10.0;

      drawBlock(p1, 65.0, 45.0);
}



















