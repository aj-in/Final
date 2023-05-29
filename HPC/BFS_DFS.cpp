/*
This code only makes the use of pragma keywords and is not truly parallel.
If you find a correct parallel code for this assignment give a PR.
*/

#include<iostream>
#include<omp.h>
#include<stack>
#include<queue>

using namespace std;

class TreeNode{
    public:
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x){
        val = x;
        left = NULL;
        right = NULL;
    }
};

void pBFS(TreeNode* root){
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()){
        int qs = q.size();
        #pragma omp parallel for
        for(int i = 0; i < qs; i++){
            TreeNode* node;
            #pragma omp critical
            {
                node = q.front();
                cout << node->val << " ";
                q.pop();
                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
            }
        }
    }
}

void pDFS(TreeNode* root){
    stack<TreeNode*> s;
    s.push(root);
    while(!s.empty()){
        int ss = s.size();
        #pragma omp parallel for
        for(int i = 0; i < ss; i++){
            TreeNode* node;
            #pragma omp critical
            {
                node = s.top();
                cout << node->val << " ";
                s.pop();
                if(node->right) s.push(node->right);
                if(node->left) s.push(node->left);
            }
        }
    }
}


int main(){
    // Construct Tree
    TreeNode* tree = new TreeNode(1);
    tree->left = new TreeNode(2);
    tree->right = new TreeNode(3); 
    tree->left->left = new TreeNode(4);
    tree->left->right = new TreeNode(5);
    tree->right->left = new TreeNode(6);
    tree->right->right = new TreeNode(7);

    /*
    Our Tree Looks like this:
                1
            2       3
        4     5   6    7
        
    */

    cout << "Parallel BFS: ";
    pBFS(tree);
    cout << "\n";
    cout << "Parallel DFS: ";
    pDFS(tree);
}

// // #include<omp.h>: This line includes the OpenMP library, which enables parallel programming.
// #include<stack> and #include<queue>: These lines include the stack and queue libraries, which provide data structures for storing elements.
// using namespace std;: This line allows us to use names from the std namespace without explicitly specifying it.
// class TreeNode: This line starts the definition of a class named TreeNode.
// public:: This line specifies that the following members are accessible from outside the class.
// int val;: This line declares an integer member variable called val to store the value of a tree node.
// TreeNode* left; and TreeNode* right;: These lines declare two pointer member variables, left and right, which point to the left and right child nodes of the current node, respectively.
// TreeNode(int x): This line defines a constructor for the TreeNode class, which takes an integer argument x and initializes the val variable with x. It also sets the left and right pointers to NULL.
// void pBFS(TreeNode* root): This line declares a function named pBFS that takes a pointer to a TreeNode as an argument. This function performs a parallelized breadth-first search (BFS) traversal of the binary tree starting from the root.
// queue<TreeNode*> q;: This line declares a queue of TreeNode pointers named q to store the nodes to be processed during the BFS traversal.
// q.push(root);: This line adds the root node to the queue q.
// while(!q.empty()): This line starts a loop that continues until the queue q is empty.
// int qs = q.size();: This line gets the current size of the queue q.
// #pragma omp parallel for: This line is a directive from the OpenMP library, indicating that the following for loop can be executed in parallel by multiple threads.
// for(int i = 0; i < qs; i++): This line starts a loop that iterates over the elements in the queue.
// TreeNode* node;: This line declares a pointer variable node of type TreeNode.
// #pragma omp critical: This line specifies a critical section, ensuring that only one thread executes the enclosed block of code at a time. It prevents simultaneous access to shared resources.
// node = q.front();: This line retrieves the front element from the queue q and assigns it to the node pointer.
// cout << node->val << " ";: This line prints the value of the current node to the console.
// q.pop();: This line removes the front element from the queue q.
// if (node->left) q.push(node->left);: This line checks if the current node has a left child and if so, adds it to the queue q.
// if (node->right) q.push(node->right);: This line checks if the current node has a right child and if so, adds it to the queue q.
// void pDFS(TreeNode* root): This line declares a function named pDFS that takes a pointer to a TreeNode as an argument. This function performs a parallelized depth-first search (DFS) traversal of the binary tree starting from the root.
// stack<TreeNode*> s;: This line declares a stack of TreeNode pointers named s to store the nodes to be processed during the DFS traversal.
// s.push(root);: This line adds the root node to the stack s.
// while(!s.empty()): This line starts a loop that continues until the stack s is empty.
// int ss = s.size();: This line gets the current size of the stack s.
// #pragma omp parallel for: This line is a directive from the OpenMP library, indicating that the following for loop can be executed in parallel by multiple threads.
// for(int i = 0; i < ss; i++): This line starts a loop that iterates over the elements in the stack.
// TreeNode* node;: This line declares a pointer variable node of type TreeNode.
// #pragma omp critical: This line specifies a critical section, ensuring that only one thread executes the enclosed block of code at a time. It prevents simultaneous access to shared resources.
// node = s.top();: This line retrieves the top element from the stack s and assigns it to the node pointer.
// cout << node->val << " ";: This line prints the value of the current node to the console.
// s.pop();: This line removes the top element from the stack s.
// if(node->right) s.push(node->right);: This line checks if the current node has a right child and if so, adds it to the stack s.
// if(node->left) s.push(node->left);: This line checks if the current node has a left child and if so, adds it to the stack s.
// int main(): This line starts the main function, which serves as the entry point of the program.
// TreeNode* tree = new TreeNode(1);: This line dynamically creates a new TreeNode object with a value of 1 and assigns its address to the tree pointer.
// tree->left = new TreeNode(2); and the subsequent lines: These lines create additional TreeNode objects and assign their addresses to the appropriate child pointers of the tree object, forming a binary tree structure.
// cout << "Parallel BFS: ";: This line prints the string "Parallel BFS: " to the console.
// pBFS(tree);: This line calls the pBFS function, passing the tree pointer as an argument, to perform a parallelized breadth-first search traversal on the tree.
// cout << "\n";: This line prints a newline character to the console.
// cout << "Parallel DFS: ";: This line prints the string "Parallel DFS: " to the console.
// pDFS(tree);: This line calls the pDFS function, passing the tree pointer as an argument, to perform a parallelized depth-first search traversal on the tree.
// The program ends, and any dynamically allocated memory is automatically released.
// In simple terms, this code defines a TreeNode class representing nodes in a binary tree. It then performs parallelized breadth-first search (pBFS) and depth-first search (pDFS) traversals on a sample binary tree, printing the node values in the respective order to the console. The OpenMP library is used to parallelize the for loops within the




// Let's go through the main() function step by step:

// TreeNode* tree = new TreeNode(1);: This line creates a new TreeNode object with a value of 1 and assigns its address to the tree pointer. This becomes the root of the binary tree.

// tree->left = new TreeNode(2);, tree->right = new TreeNode(3);, and the subsequent lines: These lines create new TreeNode objects and assign their addresses to the appropriate child pointers of the tree object. The structure formed represents a binary tree with the following relationships:

// markdown
// Copy code
//             1
//         2       3
//     4     5   6    7
// cout << "Parallel BFS: ";: This line prints the string "Parallel BFS: " to the console.

// pBFS(tree);: This line calls the pBFS function, passing the tree pointer as an argument. The pBFS function performs a parallelized breadth-first search traversal on the binary tree.

// cout << "\n";: This line prints a newline character to the console.

// cout << "Parallel DFS: ";: This line prints the string "Parallel DFS: " to the console.

// pDFS(tree);: This line calls the pDFS function, passing the tree pointer as an argument. The pDFS function performs a parallelized depth-first search traversal on the binary tree.

// The expected output of the program will be:

// yaml
// Copy code
// Parallel BFS: 1 2 3 4 5 6 7
// Parallel DFS: 1 3 7 6 2 5 4
The program constructs a binary tree with values and performs both parallelized breadth-first search (BFS) and depth-first search (DFS) traversals on the tree. The results are then printed to the console.