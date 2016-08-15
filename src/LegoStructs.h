/*
 * CS 4735 Fall 2001 Term Project - Alex O'Neill 
 *b
 * File: LegoStructs.h

 * Contains a definition of the format used to store a lego model, as well
 * as functions for reading and saving models on disk.
 *
 * It is perfectly possible to store a model that does not follow the rules
 * of LEGO (e.g., gravity, matter superposition, etc.).  It is up to the game 
 * controller itself to ensure the sanity of the model.  This storage
 * mechanism is essentially a dumb file structure.
 *
 * Alex O'Neill - 01-10-23
 *
 */

#ifndef LEGOSTRUCTS_H
#define LEGOSTRUCTS_H

#include <string>
#ifdef MESA
#include <GL/glut.h>
#endif

#include <GLUT/glut.h>

using namespace std;

class GenericBlock {
  /*
   * The GenericBlock class holds size (length and width) and color
   * attributes for the lego block.
   *
   * Subclassing of this class to produce a lego block that can draw itself
   * in OpenGL would be quite elegant.
   */
 public:
  GenericBlock( int a_Length = 1, int a_Width = 1, int a_Color = 0, 
		int a_Layer = 0, int a_X = 0, int a_Y = 0 );
  int getWidth() { return m_Width; };
  int getLength() { return m_Length; };
  int getColor() { return m_Color; };
  
  int getX() { return m_X; };
  int getY() { return m_Y; };
  int getLayer() { return m_Layer; };
  GenericBlock * getNext() { return m_Next; };

  void setLength( int a_Length );
  void setWidth( int a_Width );
  void setX( int a_X );
  void setY( int a_Y );
  void setLayer( int a_Layer );
  void setNext( GenericBlock * a_Next ) { m_Next = a_Next; };
  void setColor( int a_Color );

  string toString();
  void draw();

 private:
  /* These are coordinates measured in anchor knobs  on a green lego mat,
   * not a location in space.  Kind of like messed up world coordinates.
   */
  int m_Width, m_Length, m_Color
    // Position info is kept so that a block knows where to draw itself.
    , m_X, m_Y, m_Layer;

  GLfloat m_Points[9][3];

  GenericBlock * m_Next, * m_Prev;

};

static const GLuint s_faces[6][4] = {
  {1,0,3,2}, {0,4,7,3}, {5,1,2,6}, {4,5,6,7}, {0,1,5,4}, {2,3,7,6}
};

static const GLfloat m_BlockNormal[6][3] = {
  {0.0,0.0,-1.0}, {-1.0,0.0,0.0}, {1.0,0.0,0.0}, {0.0,0.0,1.0}, {0.0,-1.0,0.0}, {0.0,1.0,0.0}
};

typedef GenericBlock * P_Block;

/* This class holds the structural information for a structure of lego blocks.
 * Methods are given to add and delete blocks from the structure and for
 * exporting the model to a graph structure and for storing and retrieving
 * structures from files.
 */
class LegoStruct {
 public:
  
  LegoStruct( int a_Height, int a_Length, int a_Width );
  /* Add a block with the given coordinates to the structure.  The return
   * value is the layer into which the piece was dropped.
   */
  int addBlock( GenericBlock * a_NewBlock, int a_X = 0, int a_Y = 0 );

  /* Return a reference to the Lego block occupying location x, y, layer in the
   * Lego structure.  Or return null if that location is empty.
   */
  P_Block getBlockAt( int a_Layer, int a_X, int a_Y );

  /* Remove the block that occupies the specified position from the structure.
   */
  bool deleteBlock( int a_X, int a_Y );

  /* Return false if there are no blocks inside the specified region.
   */
  bool checkRegion( int a_Layer, int a_X, int a_Y, int a_Length, int a_Width );

  /* Accessor functions for some of the instance variables.
   */
  int getLength() { return m_Length; };
  int getWidth() { return m_Width; };
  int getHeight() { return m_Height; };

  void draw();

  /* Convert the lego structure to a string.
   */
  string toString();

  /* Save information about this structure to the specified file.
   */
  void saveToFile( char * fileName = "default.lego\0" );

 private:

  /* This is a dynamic array of linked lists which hold the lego blocks in each
   * layer of the structure.
   */
  P_Block * m_BlockLists;

  /* Maximum dimensions of the lego structure.  These start from 1, but
   * m_BlockArray is (of course) indexed from zero, so m_Length, etc. will be 1
   * greater than the maximum valid value for that dimension of m_BlockArray.
   */
  int m_Length, m_Width, m_Height;
};

/* Load the contents of a lego model from a file and return a pointer to the
 * lego structrue created from that data.
 */
LegoStruct * loadFromFile( char * fileName = "default.lego" );

#endif
