#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstring>
using namespace std;

// the BST struct
typedef struct node{
  int id;
  node *left;
  node *right;
} node;

void print_bst(node *root, int depth) {
  // pre-order traversal
  if (root!=NULL) {
    std::cout << std::string(depth, ' ') << root->id << "\n";
  } else return;
  if (root->left) print_bst (root->left, depth+1);
  if (root->right) print_bst (root->right, depth+1);
}

node *insert(int id, node *root) {
  if(root==NULL) {
    root = new node;
    root->id = id;
    root->left = NULL;
    root->right = NULL;
  }
  else if(id > root->id) {
    root->right = insert(id, root->right);
  }
  else if(id <= root->id) {
    root->left = insert(id, root->left);
  }
  return root;
}

node *find_min(node *root) {
  if (root->left != NULL) root = find_min(root->left);
  else return root;
}

node *delete_node(int id, node *root) {
  if(root==NULL) return root;
  else if(id > root->id) root->right = delete_node(id, root->right);
  else if(id < root->id) root->left = delete_node(id, root->left);
  else {
    // no children; leaf node
    if(root->right==NULL && root->left==NULL) {
      root = NULL;
    }
    // one child
    else if(root->right==NULL) {
      root = root->left;
    }
    else if(root->left==NULL) {
      root = root->right;
    }
    // two children
    else {
      // find min of right subtree and set the root to that node's value
      node *min = find_min(root->right);
      root->id = min->id;
      // now delete the min node from the right subtree
      root->right = delete_node(min->id, root->right);
    }
  }
  return root;
}

bool isBST(node *root) {
  // determine if a binary tree is a BST by inorder traversal
  if(root) {
    isBST(root->left);
    if ((root->left) && (root->left->id > root->id)) return false;
    if ((root->right) && (root->right->id <= root->id)) return false;
    //cout << "# " << root->id << "\n";
    isBST(root->right);
  }
  return true;
}

void opening_msg() {
  std::cout << std::string(100, '*') << "\n";
  std::cout << "This program allows insertion and deletion of nodes in a binary search tree by user input.\n";
  std::cout << "Input 'i ' followed by an integer to insert a node with that value into the BST.\n";
  std::cout << "Input 'd ' followed by an integer to delete the first occurence of a node with that value from the BST.\n";
  std::cout << "The BST is printed automatically after each insertion/deletion. The left subtree is printed before the right subtree.\n";
  std::cout << "Input 'check' to see if the tree is a BST (should always be true ;])\n";
  std::cout << "Input 'q' to quit the program.\n";
  std::cout << "By Ryan Gliever, 2015.\n";
  std::cout << std::string(100, '*') << "\n";
}

int main() {
  opening_msg();
  bool quit = false;
  node *root = NULL;
  // input loop
  while(1) {
    cout << "\n";
    char input[100];
    fgets(input, 100, stdin);
    char *parsed = strtok(input, " ");
    while(parsed!=NULL) {
      if(!strcmp(parsed, "q\n")) {
        quit=true;
        break;
      }
      else if(!strcmp(parsed, "i")) {
        parsed = strtok(NULL, " ");
        int id = atoi(parsed);
        root = insert(id, root);
        print_bst(root, 0);
      }
      else if(!strcmp(parsed, "d")) {
        parsed = strtok(NULL, " ");
        int id = atoi(parsed);
        root = delete_node(id, root);
        print_bst(root, 0);
      }
      else if(!strcmp(parsed, "check\n")) {
        isBST(root) ? (cout << "Tree is BST\n") : (cout << "Tree is not BST\n");
      }
      else cout << "I did not understand your request.\n";
      break;
    }
    if(quit) break;
  }
}
