/*
 * CS 4735 Fall 2001 Term Project - Alex O'Neill 
 *
 * File: LegoStructs.cpp
 *
 * Contains implementations of the classes defined in LegoStructs.h.
 *
 * Alex O'Neill - 01-10-24
 * 
 * g++ -o myLego myLego.cpp LegoStructs.cpp -lglut -lGL -lGLU 
 */

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#ifdef MESA
#include <GL/glut.h>
#endif

#include <GLUT/glut.h>

#include "LegoStructs.h"
#include "colors.h"
using namespace std;

/*****************************************************************************
 *
 * GenericBlock implementation.
 *
 *****************************************************************************/


/*
 * Standard constructor for a lego block object.
 * ALength: length, in lego peg things, of the piece. (horizontal)
 * AWidth: width, (vertical)
 * AColor: A color index for the new block.
 */
GenericBlock::GenericBlock( int a_Length, int a_Width, int a_Color,
			    int a_Layer, int a_X, int a_Y ) {

  /* This is a little redundant, but at least I'll only have to change it in one place, the set
   * methods.
   */
  /*
  m_Points = {
    {0.0,0.0,0.0}, {1.0,0.0,0.0}, {1.0,1.0,0.0}, {0.0,1.0,0.0}, {0.0,0.0,1.0},
    {1.0,0.0,1.0}, {1.0,1.0,1.0}, {0.0,1.0, 1.0}, {0.0,1.0, 0.0}
  };
  */
  m_Length = 0;  // These need to be initialized to 0.
  m_Width = 0;
  m_Color = a_Color;

  this->setLayer( a_Layer );  // Just in case we need to do something more to it.
  this->setX( a_X ); 
  this->setY( a_Y );
  this->setLength( a_Length );
  this->setWidth( a_Width );

}

void GenericBlock::setColor( int a_Color ) {
  m_Color = a_Color;
}

void GenericBlock::setLayer( int a_Layer ) {
  m_Layer = a_Layer;
  GLfloat floatLayer = (float)a_Layer + 1.0;
  for ( int i = 0; i < 4; i++ ) {
    m_Points[i][1] = floatLayer;
  }
  floatLayer -= 1.0;
  for ( int i = 4; i < 8; i++ ) {
    m_Points[i][1] = floatLayer;
  }  
  m_Points[8][1] = floatLayer;
}

void GenericBlock::setX( int a_X ) {
  m_X = a_X;
  GLfloat x = (float)a_X;
  //  0, 3, 4, 7, 8
  m_Points[0][0] = x;
  m_Points[3][0] = x;
  m_Points[4][0] = x;
  m_Points[7][0] = x;
  m_Points[8][0] = x;
  x = x + (float)m_Length;
  m_Points[1][0] = x;
  m_Points[2][0] = x;
  m_Points[5][0] = x;
  m_Points[6][0] = x;
}

void GenericBlock::setY( int a_Y ) {
  m_Y = a_Y;
  GLfloat y = a_Y;
  // 0, 1, 4, 5
  m_Points[0][2] = y;
  m_Points[1][2] = y;
  m_Points[4][2] = y;
  m_Points[5][2] = y;
  y = y + (float)m_Width;
  m_Points[2][2] = y;
  m_Points[3][2] = y;
  m_Points[6][2] = y;
  m_Points[7][2] = y;
  m_Points[8][2] = y;
}

void GenericBlock::setLength( int a_Length ) {
  /* Set block length ausing difference form previous length.
   */
  // 1, 2, 5, 6
  GLfloat diff = (float)(a_Length - m_Length);
  m_Points[1][0] += diff;
  m_Points[2][0] += diff;
  m_Points[5][0] += diff;
  m_Points[6][0] += diff;
  m_Length = a_Length;
}

void GenericBlock::setWidth( int a_Width ) {
  GLfloat diff = (float)(a_Width - m_Width);
  // 2, 3, 6, 7, 8
  m_Points[2][2] += diff;
  m_Points[3][2] += diff;
  m_Points[6][2] += diff;
  m_Points[7][2] += diff;
  m_Points[8][2] += diff;

  m_Width = a_Width;
}


float offsetL = 0.5; // use to keep track of "pegs"
float offsetW = 0.5; // offset pegs to be drawn for width

/* Draws the block using OpenGL.  Must be called within an OpenGL display routine.
 */
void GenericBlock::draw() {
  legoSetCurrentColor( m_Color );
  //  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff_yellow);
  glMaterialfv(GL_BACK, GL_SPECULAR, mat_specular_dull);
  glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff_cyan_dull);
		 
  //draw the lego block
  glEnable(GL_POLYGON_OFFSET_FILL);
  glBegin(GL_QUADS); 

  for (int i = 0; i < 6; i++) {
    if (i == 3) continue;
    glNormal3fv(&m_BlockNormal[i][0]);
    glVertex3fv(&m_Points[s_faces[i][0]][0]);
    glVertex3fv(&m_Points[s_faces[i][1]][0]);
    glVertex3fv(&m_Points[s_faces[i][2]][0]);
    glVertex3fv(&m_Points[s_faces[i][3]][0]);
  }
  glEnd();

  //draw the "pegs"
   
  glPushMatrix();

  for (int w = 0; w < this->getWidth(); w++)
    {      
      // loop along length to draw all of the pegs
      for (int l = 0; l < this->getLength(); l++)
	{
	  glTranslated(this->getX() + offsetL,this->getLayer() + 1,this->getY() + offsetW);      
	  glutSolidCube(0.5);
	  glTranslated(-(this->getX() + offsetL),-(this->getLayer() + 1), -(this->getY() + offsetW));
	  offsetL += 1; //increment to next peg
	}
      offsetL = 0.5; // reset the value so that the next row can be processed
      offsetW += 1.0;
    }
  offsetW = 0.5;
  glPopMatrix();
  glDisable(GL_POLYGON_OFFSET_FILL);

}

/* Turn this object into a string so that it can be re-created.
 * C-Style strings are the devil.
 */
string GenericBlock::toString() {
  ostringstream tmpStr;

  tmpStr << "GenericBlock " << m_Length << ' ' << m_Width << ' ' << m_Color << ' '
	 << m_Layer << ' ' << m_X << ' ' << m_Y;
  return tmpStr.str();
}


/*****************************************************************************
 *
 * LegoStruct implementation.
 *
 *****************************************************************************/

LegoStruct::LegoStruct( int a_Height, int a_Length, int a_Width ) {
  m_Height = a_Height;
  m_Length = a_Length;
  m_Width = a_Width;

  /* Allocate enough space to hold a GenericBlock pointer in each 'cell'.
   */
  m_BlockLists = new P_Block[a_Height];
  for ( int i = 0; i < a_Height; i++ ) {
    m_BlockLists[i] = 0;
  }
}

/* Return a reference to the Lego block occupying location layer, x, y in the
 * Lego structure.  Or return null if that location is empty.
 */

P_Block LegoStruct::getBlockAt( int a_Layer, int a_X, int a_Y ) {
  if ( a_Layer >= m_Height )
    return 0;

  P_Block tmpBlock = m_BlockLists[a_Layer];

  /* Check each block in this layer to see if it occupies the specified x,y position.
   */
  while ( tmpBlock != 0 ) {
    if ( (tmpBlock->getX() <= a_X) && (tmpBlock->getY() <= a_Y) &&
	   (tmpBlock->getX() + tmpBlock->getLength() - 1 >= a_X) &&
	   (tmpBlock->getY() + tmpBlock->getWidth() - 1 >= a_Y) )
        return tmpBlock;
    tmpBlock = tmpBlock->getNext();
  }

  return 0;
}

/* Return false if there are no blocks inside the specified region.
 */
bool LegoStruct::checkRegion( int a_Layer, int a_X, int a_Y
			      , int a_Length, int a_Width ) {
  if ( a_Layer >= m_Height )
    return 0;
  P_Block tmpBlock = m_BlockLists[a_Layer];

  /* Check each block in this layer to see if it occupies the specified x,y position.
   */
  while ( tmpBlock != 0 ) {

    if ( !( ( tmpBlock->getX() > a_X + a_Length - 1 ) || 
	    ( tmpBlock->getX() + tmpBlock->getLength() - 1 < a_X ) ||
	    ( tmpBlock->getY() > a_Y + a_Width - 1 ) || 
	    ( tmpBlock->getY() + tmpBlock->getWidth() - 1 < a_Y ) ) )
      return true;

    tmpBlock = tmpBlock->getNext();
  }
  return false;
}


/* Add a block with the given coordinates to the structure.  The return
 * value is the layer into which the piece was dropped.  The block object's
 * layer attribute is also updated.
 */
int LegoStruct::addBlock( P_Block a_NewBlock, int a_X, int a_Y ) {
  /* Start at the top and go down until we find a block.
   */
  int newLayer = m_Height; // Too high.
  for ( int i = m_Height - 1; i >= 0; i-- ) {
    /* Check if there's already a block in any of the 'cells' that will be
     * occupied by the new block.
     */
    if ( this->checkRegion( i, a_X, a_Y, a_NewBlock->getLength()
			    , a_NewBlock->getWidth() ) )
      goto done;

    /* There are no blocks in this layer.
     */
    newLayer--;
  }

 done:
  /* if the top 'cell' is already full, return an error code.
   */
  if ( newLayer == m_Height ) {
    return -1;
  }

  a_NewBlock->setLayer( newLayer );
  /* Not sure if this is the right place for this, but at worst it will just
   * overwrite the same value.
   */
  a_NewBlock->setX( a_X );
  a_NewBlock->setY( a_Y );

  /* Add the new block to the list of blocks for the new layer.
   */
  a_NewBlock->setNext( m_BlockLists[newLayer] );
  m_BlockLists[newLayer] = a_NewBlock;
  return newLayer;
}

/* Remove the block that occupies the specified position from the structure.
 */
bool LegoStruct::deleteBlock( int a_X, int a_Y ) {
  int a_Layer = m_Height - 1;
  P_Block tmpBlock;
  while ( (tmpBlock =  getBlockAt( a_Layer, a_X, a_Y )) == 0 ) {
    a_Layer--;
    if ( a_Layer < 0 )
      return false;
  }
  P_Block targetBlock;
  if ( !(checkRegion( a_Layer + 1, tmpBlock->getX(), tmpBlock->getY(),
		      tmpBlock->getLength(), tmpBlock->getWidth() ) ) )
    targetBlock = tmpBlock;
  else 
    return false;
  //  P_Block tmpBlock = m_BlockLists[a_Layer];
  
  if ( targetBlock == 0 )
    return false;
  
  tmpBlock = m_BlockLists[a_Layer];
  /* The one we're looking for is the first one.
   */
  if ( tmpBlock == targetBlock ) {
    m_BlockLists[a_Layer] = targetBlock->getNext();
    delete( targetBlock );
    return true;
  }

  while ( tmpBlock->getNext() != targetBlock ) {
    if ( tmpBlock->getNext() == 0 )  // This shouldn't happen, but just in case...
      return false;
    tmpBlock = tmpBlock->getNext();
  }

  tmpBlock->setNext( tmpBlock->getNext()->getNext() );
  delete( targetBlock );
  return true;
}

/* Draw the lego blocks and anything else associated with the lego structure itself.
 */
void LegoStruct::draw() {
  legoSetCurrentColor( c_GREEN );
  glBegin( GL_LINES );

  /* Draw a gridline along the bottom of the model area.
   */
  for ( GLuint i = 0; i <= m_Length; i += 2 ) {
    glVertex3i( i, 0, 0 );
    glVertex3i( i, 0, m_Width );
  }
  for ( GLuint i = 0; i <= m_Width; i += 2 ) {
    glVertex3i( 0, 0, i );
    glVertex3i( m_Length, 0, i );
  }
  glEnd();

  P_Block tmpPtr;
  
  for ( int i = 0; i < m_Height; i++ ) {
    tmpPtr = m_BlockLists[i];
    while ( tmpPtr != 0 ) {
      tmpPtr->draw();

      tmpPtr = tmpPtr->getNext();
    }
  }
  
}

string LegoStruct::toString() {
  ostringstream tmpStr;
  P_Block tmpBlock;

  tmpStr << m_Height << ' ' << m_Length << ' ' << m_Width << endl;

  for ( int i = 0; i < m_Height; i++ ) {
    tmpBlock = m_BlockLists[i];
    while ( tmpBlock != 0 ) {
      tmpStr << tmpBlock->toString() << endl;
      tmpBlock = tmpBlock->getNext();
    }
  }
  return tmpStr.str();
}

/* Output this lego structure to a file with the specified filename.
 */
void LegoStruct::saveToFile( char * fileName ) {
  ofstream outLegoFile( fileName, ios::out );
  outLegoFile << this->toString();
  cout << fileName << endl;
}

LegoStruct * loadFromFile( char * fileName ) {
  ifstream inLegoFile( fileName, ios::in );
  /* Get the dimensions of the structure and create the LegoStruct object.
   */
  int height, length, width, layer, x, y, color;
  string blockTypeStr;
  inLegoFile >> height >> length >> width;
  LegoStruct * lsPtr = new LegoStruct( height, length, width );
  while ( ! inLegoFile.eof() ) {
    /* Any other block types besides GenericBlock that are created need to be added
     * to here.
     */
    inLegoFile >> blockTypeStr;
    if ( blockTypeStr.compare( "GenericBlock") == 0 ) {
      inLegoFile  >> length >> width >> color >> layer >> x >> y;
      lsPtr->addBlock( new GenericBlock( length, width, color, layer, x, y ), x, y );
    }
    blockTypeStr = "";
  }

  return lsPtr;
}
