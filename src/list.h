/* list.h - Template list class definition
 * CS 4735 Term Project - Alex O'Neill  Fall, 2001
 */

#ifndef LIST_H
#define LIST_H

#include <iostream.h>
#include <assert.h>
#include "listnd.h"

template< class NODETYPE >
class List {
 public:
  List();  // Constructor
  ~List();  // Destructor
  void insertAtFront( const NODETYPE & );
  void insertAtBack( const NODETYPE & );
  bool removeFromFront( NODETYPE & );
  bool removeFromBack( NODETYPE & );
  bool isEmpty() const;
  void print() const;
 private:
  ListNode< NODETYPE > *firstPtr;  // Pointer to first node
  ListNode< NODETYPE > *lastPtr;  // Pointer to last node
  /* Utility function to allocate a new node
   */
  ListNode< NODETYPE > *getNewNode( const NODETYPE & );
};

/* Default constructor
 */
template< class NODETYPE >
List< NODETYPE >::List() : firstPtr( 0 ), lastPtr( 0 ) { }

/* Destructor
 */
template< class NODETYPE >
List< NODETYPE >::~List() {
  if ( !isEmpty() ) {
    cout << "Destroying nodes...\n";
    
    ListNode< NODETYPE > *currentPtr = firstPtr, *tempPtr;
    
    while ( currentPtr != 0 ) {  // Delete remaining nodes.
      tempPtr = currentPtr;
      cout << tempPtr->data << endl;
      currentPtr = currentPtr->nextPtr;
      delete tempPtr;
    }
  }

  cout << "All nodes destroyed.\n\n";
}


/* Insert a node at the front of the list.
 */
template< class NODETYPE >
void List< NODETYPE >::insertAtFront( const NODETYPE &value ) {
  ListNode< NODETYPE > *newPtr = getNewNode( value );
  
  if ( isEmpty() ) {  // List is empty
    firstPtr = lastPtr = newPtr;
  }
  else {  // List is not empty
    newPtr->nextPtr = firstPtr;
    firstPtr = newPtr;
  }
}

/* Insert a node at the back of the list.
 */
template< class NODETYPE >
void List< NODETYPE >::insertAtBack( const NODETYPE &value ) {
  ListNode< NODETYPE > *newPtr = getNewNode( value );
  
  if ( isEmpty() ) {  // List is empty
    firstPtr = lastPtr = newPtr;
  }
  else {  // List is not empty
    lastPtr->nextPtr = newPtr;
    lastPtr = newPtr;
  }
}

/* Delete a node from the front of the list
 */
template< class NODETYPE >
bool List< NODETYPE >::removeFromFront( NODETYPE &value ) {
  if ( isEmpty() ) {
    return false;
  }
  else {
    ListNode< NODETYPE > *tempPtr = firstPtr;

    if ( firstPtr == lastPtr ) {
      firstPtr = lastPtr = 0;
    }
    else {
      firstPtr = firstPtr->nextPtr;
    }
    value = tempPtr->data;  // Data being removed
    delete tempPtr;
    return true;
  }
}

/* Delete a node from the back of the list.
 */
template< class NODETYPE >
bool List< NODETYPE >::removeFromBack( NODETYPE &value ) {
  if ( isEmpty() ) {
    return false;  // Delete unsuccessful
  }
  else {
    ListNode< NODETYPE > *tempPtr = lastPtr;
    
    if ( firstPtr == lastPtr ) {
      firstPtr = lastPtr = 0;
    }
    else {
      ListNode< NODETYPE > *currentPtr = firstPtr;
      
      while ( currentPtr->nextPtr != lastPtr ) {
	currentPtr = currentPtr->nextPtr;
      }
      
      lastPtr = currentPtr;
      currentPtr->nextPtr = 0;
    }
    
    value = tempPtr->data;
    delete tempPtr;
    return true;  // Delete successful
  }
}

/* Is the list empty?
 */
template< class NODETYPE >
bool List< NODETYPE >::isEmpty() const {
  return firstPtr == 0;
}

/* Return a pointer to a newly allocated node.
 */
template< class NODETYPE >
ListNode< NODETYPE > * List< NODETYPE >::getNewNode( const NODETYPE &value ) {
  ListNode< NODETYPE > *ptr = new ListNode< NODETYPE > ( value );
  assert( ptr != 0 );
  return ptr;
}

/* Display the contents of the List.
 */
template< class NODETYPE >
void List< NODETYPE >::print() const {
  if ( isEmpty() ) {
    cout << "The list is empty.\n\n";
    return;
  }
  
  ListNode< NODETYPE > *currentPtr = firstPtr;

  cout << "The list is: ";

  while ( currentPtr != 0 ) {
    cout << currentPtr->data << "  ";
    currentPtr = currentPtr->nextPtr;
  }

  cout << endl << endl;
}

#endif
