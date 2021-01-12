#include <iostream>
#include <queue>
#include <vector>

struct Node{
    char data;
    vector <Node*> children;
    Node(char c){
        data = c;
    }
};

struct Tree{
    Node* root;
    Tree (Node* root) : root(root) {}
    
    void bfs(){
        queue<pair<Node*, int>> q;
        q.push({root,0});
        int current_level = -1;
        
        while(!q.empty()){
            Node* node = q.front().first;
            int lvl = q.front().second;
            if(lvl>current_level){
                cout<<"\n"<<lvl<<" --> ";
                current_level = lvl;
            }
            cout<< node->data <<" ";
            q.pop();
            
            for (auto x: (node->children))
                q.push({x,lvl+1});
        }
    }
};

int main() {
    
    Node* A = new Node('A');
    Node* B = new Node('B');
    Node* C = new Node('C');
    Node* D = new Node('D');
    Node* E = new Node('E');
    Node* F = new Node('F');
    Node* G = new Node('G');
    Node* H = new Node('H');
    Node* I = new Node('I');
    
    (A->children) = {B,C};
    (B->children) = {D,E,F};
    (C->children) = {G};
    (E->children) = {H,I};
    
    Tree t(A);
    t.bfs();
    
}