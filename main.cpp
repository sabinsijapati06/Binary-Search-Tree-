// Name       : Sabin Sijapati
// Course     : Data Structures
// Assignment : Final Project
// Date       : 05-10-2026

//   Driver for the Same Tree Final Project. Builds two binary
//   search trees and reports whether they are equivalent -
//   as they contain the same set of values regardless of
//   the structural shape produced by their insertion order.
//
//   The program first runs two required test scenarios
//   automatically (one equivalent, one not equivalent)
//   and then drops into a menu similar to the sample 
//   output provided so the user can build and compare additional 
//   trees by hand.

#include <iostream>
#include <string>
#include "BinarySearchTree.h"
using namespace std;

void displayString(string& item){
   cout << item << " ";
}

// displayTree
//   prints a tree's contents in alphabetical order. Inorder
//   traversal of a BST is automatically sorted, so we get
//   alphabetical output for free.
void displayTree(BinarySearchTree<string>& tree){
   if (tree.isEmpty())
      cout << "empty";
   else
      tree.inorderTraverse(displayString);
   cout << endl;
}

// runRequiredTests
//   Demonstrates the two scenarios: one where the two trees 
//   are equivalent (same values, different insertion order 
//   and different structure) and one where they are not.
void runRequiredTests(){
   // Scenario 1 - equivalent trees with different structures
   cout << "Test 1: equivalent trees" << endl;
   BinarySearchTree<string> testTree1;
   BinarySearchTree<string> testTree2;
   testTree1.add("abc");
   testTree1.add("def");
   testTree1.add("ghi");
   testTree2.add("def");
   testTree2.add("abc");
   testTree2.add("ghi");
   cout << "Tree 1: ";
   displayTree(testTree1);
   cout << "Tree 2: ";
   displayTree(testTree2);
   if (testTree1.isSameTree(&testTree2))
      cout << "trees are equivalent" << endl;
   else
      cout << "trees are not equivalent" << endl;
   cout << endl;

   // Scenario 2 - not equivalent: tree4 contains "def" that
   // tree3 does not.
   cout << "Test 2: not equivalent trees" << endl;
   BinarySearchTree<string> testTree3;
   BinarySearchTree<string> testTree4;
   testTree3.add("abc");
   testTree3.add("ghi");
   testTree4.add("abc");
   testTree4.add("def");
   testTree4.add("ghi");
   cout << "Tree 1: ";
   displayTree(testTree3);
   cout << "Tree 2: ";
   displayTree(testTree4);
   if (testTree3.isSameTree(&testTree4))
      cout << "trees are equivalent" << endl;
   else
      cout << "trees are not equivalent" << endl;
   cout << endl;
}

// main
//   Runs the required tests first, then offers the same menu
//   given as a sample output
int main(){
   BinarySearchTree<string> tree1;
   BinarySearchTree<string> tree2;
   int    choice;
   string value;

   cout << "Same Tree Final Project" << endl;
   cout << endl;

   // Run the two required scenarios from the assignment.
   runRequiredTests();

   // menu that matches the sample output
   do
   {
      cout << "1. insert into tree 1" << endl;
      cout << "2. insert into tree 2" << endl;
      cout << "3. compare trees"     << endl;
      cout << "0. exit"              << endl;
      cout << "choice: ";
      cin  >> choice;

      switch (choice)
      {
         case 1:
            cout << "enter value: ";
            cin  >> value;
            tree1.add(value);
            break;
         case 2:
            cout << "enter value: ";
            cin  >> value;
            tree2.add(value);
            break;
         case 3:
            cout << "tree 1: ";
            displayTree(tree1);
            cout << "tree 2: ";
            displayTree(tree2);
            if (tree1.isSameTree(&tree2))
               cout << "trees are equivalent" << endl;
            else
               cout << "trees are not equivalent" << endl;
            break;
         case 0:
            cout << "program ended" << endl;
            break;
         default:
            cout << "invalid choice" << endl;
      }
      cout << endl;
   } while (choice != 0);

   return 0;
} // end main