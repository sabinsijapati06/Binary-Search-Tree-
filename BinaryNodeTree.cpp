//   Implements the BinaryNodeTree class template declared in
//   BinaryNodeTree.h.
#ifndef BINARY_NODE_TREE_CPP_
#define BINARY_NODE_TREE_CPP_
#include "BinaryNodeTree.h"

// Protected utility methods
template<class ItemType>
int BinaryNodeTree<ItemType>::getHeightHelper(
   std::shared_ptr<BinaryNode<ItemType>> subTreePtr) const{
   if (subTreePtr == nullptr)
      return 0;
   return 1 + std::max(getHeightHelper(subTreePtr->getLeftChildPtr()),
                     getHeightHelper(subTreePtr->getRightChildPtr()));
}

template<class ItemType>
int BinaryNodeTree<ItemType>::getNumberOfNodesHelper(
   std::shared_ptr<BinaryNode<ItemType>> subTreePtr) const{
   if (subTreePtr == nullptr)
      return 0;
   return 1 + getNumberOfNodesHelper(subTreePtr->getLeftChildPtr())
            + getNumberOfNodesHelper(subTreePtr->getRightChildPtr());
}


template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinaryNodeTree<ItemType>::balancedAdd(
   std::shared_ptr<BinaryNode<ItemType>> subTreePtr,
   std::shared_ptr<BinaryNode<ItemType>> newNodePtr){
   if (subTreePtr == nullptr)
      return newNodePtr;

   auto leftPtr  = subTreePtr->getLeftChildPtr();
   auto rightPtr = subTreePtr->getRightChildPtr();

   if (getHeightHelper(leftPtr) > getHeightHelper(rightPtr)){
      rightPtr = balancedAdd(rightPtr, newNodePtr);
      subTreePtr->setRightChildPtr(rightPtr);
   }
   else{
      leftPtr = balancedAdd(leftPtr, newNodePtr);
      subTreePtr->setLeftChildPtr(leftPtr);
   }
   return subTreePtr;
}

template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinaryNodeTree<ItemType>::removeValue(
   std::shared_ptr<BinaryNode<ItemType>> subTreePtr,
   const ItemType target,
   bool& isSuccessful){
   if (subTreePtr == nullptr){
      isSuccessful = false;
      return subTreePtr;
   }

   if (subTreePtr->getItem() == target){
      subTreePtr   = moveValuesUpTree(subTreePtr);
      isSuccessful = true;
      return subTreePtr;
   }

   // search left subtree first; if not found, search right.
   auto leftResult = removeValue(subTreePtr->getLeftChildPtr(), target, isSuccessful);
   subTreePtr->setLeftChildPtr(leftResult);

   if (!isSuccessful){
      auto rightResult = removeValue(subTreePtr->getRightChildPtr(), target, isSuccessful);
      subTreePtr->setRightChildPtr(rightResult);
   }
   return subTreePtr;
}

template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinaryNodeTree<ItemType>::moveValuesUpTree(
   std::shared_ptr<BinaryNode<ItemType>> subTreePtr){
   auto leftPtr  = subTreePtr->getLeftChildPtr();
   auto rightPtr = subTreePtr->getRightChildPtr();
   int  leftH    = getHeightHelper(leftPtr);
   int  rightH   = getHeightHelper(rightPtr);

   if (leftH > rightH){
      subTreePtr->setItem(leftPtr->getItem());
      leftPtr = moveValuesUpTree(leftPtr);
      subTreePtr->setLeftChildPtr(leftPtr);
      return subTreePtr;
   }
   else if (rightPtr != nullptr){
      subTreePtr->setItem(rightPtr->getItem());
      rightPtr = moveValuesUpTree(rightPtr);
      subTreePtr->setRightChildPtr(rightPtr);
      return subTreePtr;
   }
   else{
      // We've reached a leaf - delete it.
      subTreePtr.reset();
      return subTreePtr;
   }
}

template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinaryNodeTree<ItemType>::findNode(
   std::shared_ptr<BinaryNode<ItemType>> treePtr,
   const ItemType& target,
   bool& isSuccessful) const{
   if (treePtr == nullptr){
      isSuccessful = false;
      return treePtr;
   }
   if (treePtr->getItem() == target){
      isSuccessful = true;
      return treePtr;
   }

   auto leftFound = findNode(treePtr->getLeftChildPtr(), target, isSuccessful);
   if (isSuccessful)
      return leftFound;

   return findNode(treePtr->getRightChildPtr(), target, isSuccessful);
}

template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinaryNodeTree<ItemType>::copyTree(
   const std::shared_ptr<BinaryNode<ItemType>> oldTreeRootPtr) const
{
   std::shared_ptr<BinaryNode<ItemType>> newTreePtr;
   if (oldTreeRootPtr != nullptr)
   {
      newTreePtr = std::make_shared<BinaryNode<ItemType>>(oldTreeRootPtr->getItem());
      newTreePtr->setLeftChildPtr (copyTree(oldTreeRootPtr->getLeftChildPtr()));
      newTreePtr->setRightChildPtr(copyTree(oldTreeRootPtr->getRightChildPtr()));
   }
   return newTreePtr;
}

template<class ItemType>
void BinaryNodeTree<ItemType>::destroyTree(
   std::shared_ptr<BinaryNode<ItemType>> subTreePtr){
   // shared_ptr handles the actual deallocation, but we walk
   // the tree first so the recursion terminates cleanly.
   if (subTreePtr != nullptr)
   {
      destroyTree(subTreePtr->getLeftChildPtr());
      destroyTree(subTreePtr->getRightChildPtr());
      subTreePtr.reset();
   }
} 

// Traversal helpers
template<class ItemType>
void BinaryNodeTree<ItemType>::preorder(void visit(ItemType&),
   std::shared_ptr<BinaryNode<ItemType>> treePtr) const{
   if (treePtr != nullptr){
      ItemType theItem = treePtr->getItem();
      visit(theItem);
      preorder(visit, treePtr->getLeftChildPtr());
      preorder(visit, treePtr->getRightChildPtr());
   }
}

template<class ItemType>
void BinaryNodeTree<ItemType>::inorder(void visit(ItemType&),
   std::shared_ptr<BinaryNode<ItemType>> treePtr) const{
   if (treePtr != nullptr){
      inorder(visit, treePtr->getLeftChildPtr());
      ItemType theItem = treePtr->getItem();
      visit(theItem);
      inorder(visit, treePtr->getRightChildPtr());
   }
}

template<class ItemType>
void BinaryNodeTree<ItemType>::postorder(void visit(ItemType&),
   std::shared_ptr<BinaryNode<ItemType>> treePtr) const{
   if (treePtr != nullptr){
      postorder(visit, treePtr->getLeftChildPtr());
      postorder(visit, treePtr->getRightChildPtr());
      ItemType theItem = treePtr->getItem();
      visit(theItem);
   }
} 

// Constructors and destructor
template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree() : rootPtr(nullptr){
}

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const ItemType& rootItem)
   : rootPtr(std::make_shared<BinaryNode<ItemType>>(rootItem)){
}

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const ItemType& rootItem,
   const std::shared_ptr<BinaryNodeTree<ItemType>> leftTreePtr,
   const std::shared_ptr<BinaryNodeTree<ItemType>> rightTreePtr){
   rootPtr = std::make_shared<BinaryNode<ItemType>>(rootItem,
               copyTree(leftTreePtr->rootPtr),
               copyTree(rightTreePtr->rootPtr));
}

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(
   const std::shared_ptr<BinaryNodeTree<ItemType>>& treePtr){
   rootPtr = copyTree(treePtr->rootPtr);
}

template<class ItemType>
BinaryNodeTree<ItemType>::~BinaryNodeTree(){
   destroyTree(rootPtr);
}

// Public BinaryTreeInterface methods

template<class ItemType>
bool BinaryNodeTree<ItemType>::isEmpty() const{
   return rootPtr == nullptr;
}

template<class ItemType>
int BinaryNodeTree<ItemType>::getHeight() const{
   return getHeightHelper(rootPtr);
}

template<class ItemType>
int BinaryNodeTree<ItemType>::getNumberOfNodes() const{
   return getNumberOfNodesHelper(rootPtr);
}

template<class ItemType>
ItemType BinaryNodeTree<ItemType>::getRootData() const{
   if (isEmpty())
      throw PrecondViolatedExcept("getRootData() called on empty tree.");
   return rootPtr->getItem();
} 

template<class ItemType>
void BinaryNodeTree<ItemType>::setRootData(const ItemType& newData){
   if (isEmpty())
      rootPtr = std::make_shared<BinaryNode<ItemType>>(newData);
   else
      rootPtr->setItem(newData);
}

template<class ItemType>
bool BinaryNodeTree<ItemType>::add(const ItemType& newData){
   auto newNodePtr = std::make_shared<BinaryNode<ItemType>>(newData);
   rootPtr = balancedAdd(rootPtr, newNodePtr);
   return true;
}

template<class ItemType>
bool BinaryNodeTree<ItemType>::remove(const ItemType& target){
   bool isSuccessful = false;
   rootPtr = removeValue(rootPtr, target, isSuccessful);
   return isSuccessful;
}

template<class ItemType>
void BinaryNodeTree<ItemType>::clear(){
   destroyTree(rootPtr);
   rootPtr.reset();
}

template<class ItemType>
ItemType BinaryNodeTree<ItemType>::getEntry(const ItemType& anEntry) const{
   bool isSuccessful = false;
   auto found = findNode(rootPtr, anEntry, isSuccessful);
   if (!isSuccessful)
      throw NotFoundException("Entry not found in tree.");
   return found->getItem();
}

template<class ItemType>
bool BinaryNodeTree<ItemType>::contains(const ItemType& anEntry) const{
   bool isSuccessful = false;
   findNode(rootPtr, anEntry, isSuccessful);
   return isSuccessful;
}

// Public traversals
template<class ItemType>
void BinaryNodeTree<ItemType>::preorderTraverse(void visit(ItemType&)) const{
   preorder(visit, rootPtr);
}

template<class ItemType>
void BinaryNodeTree<ItemType>::inorderTraverse(void visit(ItemType&)) const{
   inorder(visit, rootPtr);
}

template<class ItemType>
void BinaryNodeTree<ItemType>::postorderTraverse(void visit(ItemType&)) const{
   postorder(visit, rootPtr);
}

// Overloaded
template<class ItemType>
BinaryNodeTree<ItemType>& BinaryNodeTree<ItemType>::operator=(
   const BinaryNodeTree<ItemType>& rightHandSide)
{
   if (this != &rightHandSide)
   {
      destroyTree(rootPtr);
      rootPtr = copyTree(rightHandSide.rootPtr);
   }
   return *this;
}
#endif