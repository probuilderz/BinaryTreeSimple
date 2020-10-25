#include<cstdlib>
#include<iostream>
#include <vector>

using namespace std;

struct Node {
    int data;
    Node * left;
    Node * right;
};

class BST{
public:
    BST();
    ~BST();
    BST(const BST& aTree);
    BST& operator=(const BST& aTree);
    
    void InsertItem(int key);
    Node * RetrieveItem(int key);
    Node * GetPredecessor(Node *& aNode);
    void DeleteItem(int key);
    void PrintTree(vector<int>& out);
    void PrintPath();
    //void Delete(Node )
private:
    Node * root;
};

BST::BST(){
    root  = NULL;
}
// Print tree in-order
void Print(Node *& aNode, vector<int>& output){
    if(aNode != NULL){
        Print(aNode->left, output);
        output.push_back(aNode->data);
        //cout << aNode->data << "->";  
        Print(aNode->right, output);

    }

}
// Print tree in-order
void BST::PrintTree(vector<int>& out){
    Print(root, out);
}

// Print all possible path in tree
void PrintAllPath(Node *& aNode, string path, string output[], int& index){
    if(aNode != NULL){
        path.append(to_string(aNode->data));
        if((aNode->left != NULL) && (aNode->right == NULL)){
            path.append("->");
            PrintAllPath(aNode->left, path, output, index);
        }else if((aNode->left == NULL) && (aNode->right != NULL)){
            path.append("->");
            PrintAllPath(aNode->right, path, output, index);
        }else if((aNode->left != NULL) && (aNode->right != NULL)){
            path.append("->");
            PrintAllPath(aNode->left, path, output, index);
            PrintAllPath(aNode->right, path, output, index);
        }else if((aNode->left == NULL) && (aNode->right == NULL)){
            output[index] = path;
            index++;
            //cout << path;
        }
    }
}

void PrintP(Node *& aNode, string path, vector<string>& vpath){
    if(aNode ==NULL) return;

    path.append(to_string(aNode->data));
    if((aNode->left == NULL) && (aNode->right == NULL)){
        vpath.push_back(path);
    }else{
        path.append("->");
        PrintP(aNode->left, path, vpath);
        PrintP(aNode->right, path, vpath);
    }
}

void BST::PrintPath(){

    string path;
    vector<string> apath;
    PrintP(root, path, apath);
    for(auto it = apath.begin(); it != apath.end(); it++){
        cout << *it << endl;
    }
    
    // another solution
    cout << "Using second print function"<<endl;
    string path1;
    string output[100];
    int index = 0;
    PrintAllPath(root, path1, output, index);
    for(int i = 0; i < index; i++){
        cout << output[i]<<endl;
    }
}


void Destroy(Node * aNode){
    if(aNode != NULL){
        Destroy(aNode->left);
        Destroy(aNode->right);
        delete aNode;
    }
        
}
BST::~BST(){
    Destroy(root);
}
void CopyTree( Node * &aNode, Node * bNode){
    if(bNode == NULL){
        aNode = NULL;
    }else{
        aNode = new Node;
        aNode->data = bNode->data;
        CopyTree(aNode->left, bNode->left);
        CopyTree(aNode->right, bNode->right);
    }
}
BST::BST(const BST& aTree){
    CopyTree(root, aTree.root);
}
BST& BST::operator=(const BST& aTree){
    if(this != &aTree){
        Destroy(root);
        CopyTree(root, aTree.root);
    }
    return *this;
    
}

void Insert(Node *& aNode, int key){
    if(aNode == NULL){
        aNode = new Node;
        aNode->data = key;
        aNode->left = NULL;
        aNode->right = NULL;
    }else if (aNode->data > key){
        Insert(aNode->left, key);
    }else{
        Insert(aNode->right, key);
    }
}
void BST::InsertItem(int key){
    Insert(root, key);
    
}

Node * Retrieve(Node *& aNode, int key){
    if(aNode == NULL){
        return NULL;
    }else if(aNode->data > key){
        return Retrieve(aNode->left, key);
    }else if(aNode->data < key){
        return Retrieve(aNode->right, key);
    }
    return aNode;
}
Node * BST::RetrieveItem(int key){
    return Retrieve(root, key);
}
Node * BST::GetPredecessor(Node *& aNode){
    if(aNode != NULL){
        if(aNode->right != NULL){
            return GetPredecessor(aNode->right);
        }
    }
    return aNode;
}

void Delete(Node * &aNode, int key){
    if(aNode == NULL){
        return;
    }else if (aNode->data > key){
        Delete(aNode->left, key);
    }else if (aNode->data < key){
        Delete(aNode->right, key);
    }else{
        Node * temptr = new Node;
        temptr = aNode;
        
        if(aNode->left == NULL && aNode->right == NULL){
            delete temptr;
        }else if(aNode->left != NULL && aNode->right == NULL){
            aNode = aNode->left;
            delete temptr;
        }else if(aNode->left == NULL && aNode->right != NULL){
            aNode = aNode->right;
            delete temptr;
        }else{
            Node * pred = new Node;
            BST * aTree = new BST();
            
            pred = aTree->GetPredecessor(aNode->left);
            aNode->data = pred->data;
            Delete(pred, pred->data);
        }
    }
}
void BST::DeleteItem(int key){
    Delete(root, key);
}

int main(int argc, char ** argv){
    int input[] = { 10, 9, 13, 12, 7, 8, 11, 5, 2, 3, 15, 20, 1, 4};
    BST * aTree = new BST();
    for(int i= 0; i < sizeof(input)/sizeof(int); i++){
        aTree->InsertItem(input[i]);
    }
    vector<int> output;
    aTree->PrintTree(output);
    
    
    for(auto it=output.begin(); it != output.end(); it++){
        if(it != output.end() - 1){
            cout << *it << "->";
        }else{
            cout << *it;
        }

    }
    cout <<endl;
    aTree->PrintPath();
    int key = 10;
    Node * newNode = new Node;
    newNode = aTree->RetrieveItem(key);
    
    cout <<"Found node " << newNode->data<<endl;
    
    Node * pred = aTree->GetPredecessor(newNode->left);
    cout <<"predecessor of " << newNode->data <<" is "<<pred->data<<endl;
    
    aTree->DeleteItem(key);
    
    Node * delNode = aTree->RetrieveItem(key);
    cout <<"node is " << ((delNode != NULL)? delNode->data:0);
    
    return 0;
}
    