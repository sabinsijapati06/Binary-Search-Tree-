//   Interface for the ADT binary tree. Listing 15-1 from
//   Data Abstraction & Problem Solving with C++.

#ifndef BINARY_TREE_INTERFACE_
#define BINARY_TREE_INTERFACE_
#include "NotFoundException.h"

template<class ItemType>
class BinaryTreeInterface{
public:
   virtual bool isEmpty() const = 0;
   virtual int getHeight() const = 0;
   virtual int getNumberOfNodes() const = 0;
   virtual ItemType getRootData() const = 0;
   virtual void setRootData(const ItemType& newData) = 0;
   virtual bool add(const ItemType& newData) = 0;
   virtual bool remove(const ItemType& target) = 0;
   virtual void clear() = 0;
   virtual ItemType getEntry(const ItemType& target) const = 0;
   virtual bool contains(const ItemType& target) const = 0;
   virtual void preorderTraverse (void visit(ItemType&)) const = 0;
   virtual void inorderTraverse  (void visit(ItemType&)) const = 0;
   virtual void postorderTraverse(void visit(ItemType&)) const = 0;

   virtual ~BinaryTreeInterface() { }
};

#endif