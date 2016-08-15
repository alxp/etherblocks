/* listtest.cpp - List class test
 * 2001.11.16 - Alex O'Neill - Initial revision
 */

#include <iostream.h>
#include "list.h"

/* Function to test an integer list.
 */
template< class T >
void testList( List< T > &listObject, const char *type ) {
  cout << "Testing a list of " << type << " values.\n";

  instructions();
  int choice;
  T value;
  
  do {
    cout << "? ";
    cin >> choice;
    switch ( choice ) {
    case 1:
      cout << "Enter " << type << ": ";
      cin >> value;
      listObject.insertAtFront( value );
      listObject.print();
      break;
    case 2:
      cout << "Enter " << type << ": ";
      cin >> value;
      listObject.insertAtBack( value );
      listObject.print();
      break;
    case 3:
      if ( listObject.removeFromFront( value ) ) {
	cout << value << " removed from list.\n";
      }
      listObject.print();
      break;
    case 4:
      if ( listObject.removeFromBack( value ) ) {
	cout << value << " removed from list.\n";
      }
      listObject.print();
      break;
    }
  } while ( choice != 5 );

  cout << "End list test.\n\n";
}

void instructions() {
  cout << "Enter 1 of the following: \n"
       << "1: To insert at beginning of list.\n"
       << "2: To insert at end of list.\n"
       << "3: To remove from beginning of list.\n"
       << "4: To remove from end of list.\n"
       << "5: Exit.\n";
}

int main() {
  List< int > integerList;
  testList( integerList, "integer" );  // Test integerList
  
  List< float > floatList;
  testList( floatList, "float" );  // Test float list
  
  return 0;
}
