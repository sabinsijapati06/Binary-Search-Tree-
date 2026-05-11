//   Implements the BinaryNode class template declared in
//   BinaryNode.h.

#ifndef BINARY_NODE_CPP_
#define BINARY_NODE_CPP_
#include "BinaryNode.h"

template<class ItemType>
BinaryNode<ItemType>::BinaryNode()
   : item(), leftChildPtr(nullptr), rightChildPtr(nullptr){
}

template<class ItemType>
BinaryNode<ItemType>::BinaryNode(const ItemType& anItem)
   : item(anItem), leftChildPtr(nullptr), rightChildPtr(nullptr){
}

template<class ItemType>
BinaryNode<ItemType>::BinaryNode(const ItemType& anItem,
   std::shared_ptr<BinaryNode<ItemType>> leftPtr,
   std::shared_ptr<BinaryNode<ItemType>> rightPtr)
   : item(anItem), leftChildPtr(leftPtr), rightChildPtr(rightPtr){
}

template<class ItemType>
void BinaryNode<ItemType>::setItem(const ItemType& anItem){
   item = anItem;
}

template<class ItemType>
ItemType BinaryNode<ItemType>::getItem() const{
   return item;
}

template<class ItemType>
bool BinaryNode<ItemType>::isLeaf() const{
   return (leftChildPtr == nullptr && rightChildPtr == nullptr);
}

template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinaryNode<ItemType>::getLeftChildPtr() const{
   return leftChildPtr;
}

template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinaryNode<ItemType>::getRightChildPtr() const{
   return rightChildPtr;
}

template<class ItemType>
void BinaryNode<ItemType>::setLeftChildPtr(std::shared_ptr<BinaryNode<ItemType>> leftPtr){
   leftChildPtr = leftPtr;
}

template<class ItemType>
void BinaryNode<ItemType>::setRightChildPtr(std::shared_ptr<BinaryNode<ItemType>> rightPtr){
   rightChildPtr = rightPtr;
}
#endif