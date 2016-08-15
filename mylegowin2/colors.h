#ifndef COLORS_H
#define COLORS_H

#include <GL/gl.h>

/* Colour constants that don't really mean anything.
 */
#define c_WHITE 0
#define c_GREY 1
#define c_RED 2
#define c_YELLOW 3
#define c_CYAN_DULL 4
#define c_GREEN 5
#define c_BLUE 6
#define c_CYAN 7
#define c_ORANGE 8
#define c_MAGENTA 9

static GLfloat mat_amb_diff_white[] = { 1.0, 1.0, 1.0, 1.0 };
static GLfloat mat_amb_diff_grey[] = { 0.5, 0.5, 0.5, 1.0 };
static GLfloat mat_amb_diff_red[] = { 1.0, 0.0, 0.0, 1.0 };
static GLfloat mat_amb_diff_yellow[] = { 1.0, 1.0, 0.0, 1.0 };
//static GLfloat mat_amb_diff_green[] = 
static GLfloat mat_specular_dull[] = { 0.0, 0.0, 0.0, 1.0 };
static GLfloat mat_amb_diff_cyan_dull[] = { 0.0, 0.4, 0.4, 1.0 };
static GLfloat mat_amb_diff_green[] = { 0.0, 1.0, 0.0, 1.0 };
static GLfloat mat_amb_diff_blue[] = { 0.0, 0.0, 1.0, 1.0 };
static GLfloat mat_amb_diff_cyan[] = { 0.0, 1.0, 1.0, 1.0 };
static GLfloat mat_amb_diff_orange[] = { 1.0, 0.5, 0.0, 1.0 };
static GLfloat mat_amb_diff_magenta[] = { 1.0, 0.0, 1.0, 1.0 };

/* Sets the current color to the index value specified.  See colors.h.
 */
void legoSetCurrentColor( int a_ColorIndex ) {
  switch( a_ColorIndex ) {
  case 0:
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff_white);
    break;
  case 1:
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff_grey);
    break;
  case 2:
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff_red);
    break;
  case 3:
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff_yellow);
    break;
  case 4:
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff_cyan_dull);
    break;
  case 5:
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff_green);
    break;
  case 6:
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff_blue);
    break;
  case 7:
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff_cyan);
    break;
  case 8:
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff_orange);
    break;
  case 9:
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff_magenta);
    break;
  }
};



#endif
