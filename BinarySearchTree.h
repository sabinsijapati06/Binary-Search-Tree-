//   Declares the BinarySearchTree class, a link-based
//   implementation of the ADT binary search tree.
//   Listing 16-4 from Data Abstraction & 
//   Problem Solving with C++.

#ifndef BINARY_SEARCH_TREE_
#define BINARY_SEARCH_TREE_

#include "BinaryTreeInterface.h"
#include "BinaryNode.h"
#include "BinaryNodeTree.h"
#include "NotFoundException.h"
#include "PrecondViolatedExcept.h"
#include <memory>
#include <vector>

template<class ItemType>
class BinarySearchTree : public BinaryNodeTree<ItemType>
{
private:
   // Static collector used by isSameTree.
   static std::vector<ItemType> compareCollector;
   static void collectForCompare(ItemType& item);

protected:
   using BinaryNodeTree<ItemType>::findNode;

   std::shared_ptr<BinaryNode<ItemType>> placeNode(
      std::shared_ptr<BinaryNode<ItemType>> subTreePtr,
      std::shared_ptr<BinaryNode<ItemType>> newNode);

   std::shared_ptr<BinaryNode<ItemType>> removeValue(
      std::shared_ptr<BinaryNode<ItemType>> subTreePtr,
      const ItemType target,
      bool& isSuccessful) override;

   std::shared_ptr<BinaryNode<ItemType>> removeNode(
      std::shared_ptr<BinaryNode<ItemType>> nodePtr);

   std::shared_ptr<BinaryNode<ItemType>> removeLeftmostNode(
      std::shared_ptr<BinaryNode<ItemType>> subTreePtr,
      ItemType& inorderSuccessor);

   std::shared_ptr<BinaryNode<ItemType>> findNode(
      std::shared_ptr<BinaryNode<ItemType>> treePtr,
      const ItemType& target) const;

public:
   BinarySearchTree();
   BinarySearchTree(const ItemType& rootItem);
   BinarySearchTree(const BinarySearchTree<ItemType>& tree);
   virtual ~BinarySearchTree();

   bool add(const ItemType& newEntry);
   bool remove(const ItemType& target);
   ItemType getEntry(const ItemType& anEntry) const;
   bool contains(const ItemType& anEntry) const;

   // Same-Tree comparison
   bool isSameTree(BinarySearchTree<ItemType>* other) const;

   BinarySearchTree<ItemType>& operator=(
      const BinarySearchTree<ItemType>& rightHandSide);

};

#include "BinarySearchTree.cpp"
#endif