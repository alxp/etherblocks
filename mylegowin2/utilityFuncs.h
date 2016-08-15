/* utilFuncs.cpp - Static utility functions.
 * CS 4735 Term Project - Alex O'Neill - Fall, 2001
 */

#ifndef UTILITYFUNCS_H
#define UTILITYFUNCS_H

#include <GL/gl.h>
#include <GL/glut.h>
#include <string.h>

/* Draw the  string *s one character at a time using GLUT's bitmap
 * rendering utility  
 */
void drawString ( char *s ) { 

  unsigned int i; 
  for (i = 0; i < strlen(s); i++) 
    glutBitmapCharacter (GLUT_BITMAP_HELVETICA_10, s[i]); 
};


/*  Same as before but using a larger font bitmap
 */
void drawStringBig ( char *s ) { 
  unsigned int i; 
  for (i = 0; i < strlen(s); i++) 
    glutBitmapCharacter (GLUT_BITMAP_HELVETICA_18, s[i]); 
};
 
#endif
