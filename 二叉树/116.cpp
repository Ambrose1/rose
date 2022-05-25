#include<iostream>
#include<queue>
// #include<queue>
// #include<stack>
using namespace std;


// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};


class Solution {
public:
    Node* connect(Node* root) {
        if(!root)return root;
        queue<Node*> que;
        que.push(root);
        while(!que.empty()) {
            int n = que.size();
            Node* last = que.front();
            for(int i=0; i<n; i++){
                Node* node = que.front();
                que.pop();
                if(node->left)que.push(node->left);
                if(node->right)que.push(node->right);
                if(node != last){
                    last->next = node;
                    last = node;
                }
            }
            last->next = nullptr;
        }
        return root;


    }
};