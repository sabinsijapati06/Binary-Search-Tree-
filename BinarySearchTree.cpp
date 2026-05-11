//   Implements the BinarySearchTree class template declared in
//   BinarySearchTree.h. Uses the protected rootPtr inherited
//   from BinaryNodeTree, accessed through  this->rootPtr.

#ifndef BINARY_SEARCH_TREE_CPP_
#define BINARY_SEARCH_TREE_CPP_
#include "BinarySearchTree.h"

// Protected utility methods
template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinarySearchTree<ItemType>::placeNode(
   std::shared_ptr<BinaryNode<ItemType>> subTreePtr,
   std::shared_ptr<BinaryNode<ItemType>> newNode){
   if (subTreePtr == nullptr)
      return newNode;

   if (newNode->getItem() < subTreePtr->getItem()){
      auto tempPtr = placeNode(subTreePtr->getLeftChildPtr(), newNode);
      subTreePtr->setLeftChildPtr(tempPtr);
   }
   else{
      auto tempPtr = placeNode(subTreePtr->getRightChildPtr(), newNode);
      subTreePtr->setRightChildPtr(tempPtr);
   }
   return subTreePtr;
}

template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinarySearchTree<ItemType>::removeValue(
   std::shared_ptr<BinaryNode<ItemType>> subTreePtr,
   const ItemType target,
   bool& isSuccessful){
   if (subTreePtr == nullptr){
      isSuccessful = false;
      return subTreePtr;
   }
   if (subTreePtr->getItem() == target){
      subTreePtr   = removeNode(subTreePtr);
      isSuccessful = true;
      return subTreePtr;
   }
   if (target < subTreePtr->getItem()){
      auto tempPtr = removeValue(subTreePtr->getLeftChildPtr(), target, isSuccessful);
      subTreePtr->setLeftChildPtr(tempPtr);
   }
   else{
      auto tempPtr = removeValue(subTreePtr->getRightChildPtr(), target, isSuccessful);
      subTreePtr->setRightChildPtr(tempPtr);
   }
   return subTreePtr;
}

// removeNode handles the three textbook cases for BST removal:
//   1. Leaf
//   2. One child
//   3. Two children
template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinarySearchTree<ItemType>::removeNode(
   std::shared_ptr<BinaryNode<ItemType>> nodePtr){
   // Case 1: leaf
   if (nodePtr->isLeaf()){
      nodePtr.reset();
      return nodePtr;
   }
   // Case 2: only a right child
   if (nodePtr->getLeftChildPtr() == nullptr)
      return nodePtr->getRightChildPtr();
   // Case 2: only a left child
   if (nodePtr->getRightChildPtr() == nullptr)
      return nodePtr->getLeftChildPtr();

   // Case 3: two children
   ItemType inorderSuccessor;
   auto tempPtr = removeLeftmostNode(nodePtr->getRightChildPtr(), inorderSuccessor);
   nodePtr->setRightChildPtr(tempPtr);
   nodePtr->setItem(inorderSuccessor);
   return nodePtr;
} // end removeNode

template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinarySearchTree<ItemType>::removeLeftmostNode(
   std::shared_ptr<BinaryNode<ItemType>> subTreePtr,
   ItemType& inorderSuccessor){
   if (subTreePtr->getLeftChildPtr() == nullptr){
      inorderSuccessor = subTreePtr->getItem();
      return subTreePtr->getRightChildPtr();
   }
   auto tempPtr = removeLeftmostNode(subTreePtr->getLeftChildPtr(), inorderSuccessor);
   subTreePtr->setLeftChildPtr(tempPtr);
   return subTreePtr;
}

template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinarySearchTree<ItemType>::findNode(
   std::shared_ptr<BinaryNode<ItemType>> treePtr,
   const ItemType& target) const{
   if (treePtr == nullptr)
      return treePtr;
   if (treePtr->getItem() == target)
      return treePtr;
   if (target < treePtr->getItem())
      return findNode(treePtr->getLeftChildPtr(), target);
   return findNode(treePtr->getRightChildPtr(), target);
}


// Constructors and destructor
template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree() : BinaryNodeTree<ItemType>(){
}

template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const ItemType& rootItem)
   : BinaryNodeTree<ItemType>(rootItem){
}

template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const BinarySearchTree<ItemType>& tree){
   this->rootPtr = this->copyTree(tree.rootPtr);
}

template<class ItemType>
BinarySearchTree<ItemType>::~BinarySearchTree(){
}

// Public methods
// add() uses BST ordering instead of the height-balanced
// approach used by BinaryNodeTree.
template<class ItemType>
bool BinarySearchTree<ItemType>::add(const ItemType& newEntry){
   auto newNodePtr = std::make_shared<BinaryNode<ItemType>>(newEntry);
   this->rootPtr = placeNode(this->rootPtr, newNodePtr);
   return true;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType& target){
   bool isSuccessful = false;
   this->rootPtr = removeValue(this->rootPtr, target, isSuccessful);
   return isSuccessful;
}

template<class ItemType>
ItemType BinarySearchTree<ItemType>::getEntry(const ItemType& anEntry) const{
   auto found = findNode(this->rootPtr, anEntry);
   if (found == nullptr)
      throw NotFoundException("Entry not found in tree.");
   return found->getItem();
}

template<class ItemType>
bool BinarySearchTree<ItemType>::contains(const ItemType& anEntry) const{
   return findNode(this->rootPtr, anEntry) != nullptr;
}

// Same-Tree comparison
template<class ItemType>
std::vector<ItemType> BinarySearchTree<ItemType>::compareCollector;

template<class ItemType>
void BinarySearchTree<ItemType>::collectForCompare(ItemType& item){
   compareCollector.push_back(item);
}

template<class ItemType>
bool BinarySearchTree<ItemType>::isSameTree(
   BinarySearchTree<ItemType>* other) const{
   if (other == nullptr)
      return false;

   if (this->getNumberOfNodes() != other->getNumberOfNodes())
      return false;

   compareCollector.clear();
   this->inorderTraverse(collectForCompare);
   std::vector<ItemType> myValues = compareCollector;

   compareCollector.clear();
   other->inorderTraverse(collectForCompare);
   std::vector<ItemType> otherValues = compareCollector;

   return myValues == otherValues;
}

// Overloaded
template<class ItemType>
BinarySearchTree<ItemType>& BinarySearchTree<ItemType>::operator=(
   const BinarySearchTree<ItemType>& rightHandSide){
   if (this != &rightHandSide)
      BinaryNodeTree<ItemType>::operator=(rightHandSide);
   return *this;
} 
#endif