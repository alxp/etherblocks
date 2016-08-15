/* listnd.h - ListNode template definition
 * CS 4735 Term Project - Alex O'Neill - Fall, 2001
 */

#ifndef LISTND_H
#define LISTND_H

template< class NODETYPE > class List;  // forward declaration

template< class NODETYPE >
class ListNode {
  friend class List< NODETYPE >;  // Make List a friend
 public:
  ListNode( const NODETYPE & );  // constructor
  NODETYPE getData() const;  // Return data in the node.
 private:
  NODETYPE data;
  ListNode< NODETYPE > *nextPtr;  // Next node in the list.
};

/* ListNode Constructor
 */
template< class NODETYPE >
ListNode< NODETYPE >::ListNode( const NODETYPE &info )
  : data( info ), nextPtr( 0 ) { }

/* Return a copy of the data in the node.
 */
template< class NODETYPE >
NODETYPE ListNode< NODETYPE >::getData() const {
  return data;
}

#endif
