//   Declares the BinaryNodeTree class, a link-based
//   implementation of the ADT binary tree.
//   Listing 16-3 from Data Abstraction & 
//   Problem Solving with C++.

#ifndef BINARY_NODE_TREE_
#define BINARY_NODE_TREE_

#include "BinaryTreeInterface.h"
#include "BinaryNode.h"
#include "PrecondViolatedExcept.h"
#include "NotFoundException.h"
#include <memory>
#include <algorithm>

template<class ItemType>
class BinaryNodeTree : public BinaryTreeInterface<ItemType>
{
protected:
   std::shared_ptr<BinaryNode<ItemType>> rootPtr;
   int getHeightHelper        (std::shared_ptr<BinaryNode<ItemType>> subTreePtr) const;
   int getNumberOfNodesHelper (std::shared_ptr<BinaryNode<ItemType>> subTreePtr) const;

   std::shared_ptr<BinaryNode<ItemType>> balancedAdd(
      std::shared_ptr<BinaryNode<ItemType>> subTreePtr,
      std::shared_ptr<BinaryNode<ItemType>> newNodePtr);

   virtual std::shared_ptr<BinaryNode<ItemType>> removeValue(
      std::shared_ptr<BinaryNode<ItemType>> subTreePtr,
      const ItemType target,
      bool& isSuccessful);

   std::shared_ptr<BinaryNode<ItemType>> moveValuesUpTree(
      std::shared_ptr<BinaryNode<ItemType>> subTreePtr);

   virtual std::shared_ptr<BinaryNode<ItemType>> findNode(
      std::shared_ptr<BinaryNode<ItemType>> treePtr,
      const ItemType& target,
      bool& isSuccessful) const;

   std::shared_ptr<BinaryNode<ItemType>> copyTree(
      const std::shared_ptr<BinaryNode<ItemType>> oldTreeRootPtr) const;

   void destroyTree(std::shared_ptr<BinaryNode<ItemType>> subTreePtr);

   void preorder (void visit(ItemType&), std::shared_ptr<BinaryNode<ItemType>> treePtr) const;
   void inorder  (void visit(ItemType&), std::shared_ptr<BinaryNode<ItemType>> treePtr) const;
   void postorder(void visit(ItemType&), std::shared_ptr<BinaryNode<ItemType>> treePtr) const;

public:
   BinaryNodeTree();
   BinaryNodeTree(const ItemType& rootItem);
   BinaryNodeTree(const ItemType& rootItem,
                  const std::shared_ptr<BinaryNodeTree<ItemType>> leftTreePtr,
                  const std::shared_ptr<BinaryNodeTree<ItemType>> rightTreePtr);
   BinaryNodeTree(const std::shared_ptr<BinaryNodeTree<ItemType>>& tree);
   virtual ~BinaryNodeTree();

   bool isEmpty()                          const;
   int  getHeight()                        const;
   int  getNumberOfNodes()                 const;
   ItemType getRootData()                  const;
   void setRootData(const ItemType& newData);
   bool add   (const ItemType& newData);
   bool remove(const ItemType& data);
   void clear();
   ItemType getEntry(const ItemType& anEntry) const;
   bool contains   (const ItemType& anEntry) const;

   void preorderTraverse (void visit(ItemType&)) const;
   void inorderTraverse  (void visit(ItemType&)) const;
   void postorderTraverse(void visit(ItemType&)) const;

   BinaryNodeTree& operator=(const BinaryNodeTree& rightHandSide);

};
#include "BinaryNodeTree.cpp"
#endif