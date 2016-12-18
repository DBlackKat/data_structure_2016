#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <queue>
#include <string>
#include <vector>
using namespace std;
typedef struct Node node;

struct Node{
    struct Node *left;
    struct Node *right;
    int cash;
    long int id;
};

class BST{
    int level;
    int richest;
    long int richestID;
    vector <long int> levelID;
    node *root;
    node *newNode(int cash,long int id);
    node *insert(node *root,int cash,long int ID);
    void showNode(node *n);
    node *findMin(node *n);
    node *deleteNode(node *root,long int id);
    void show(node *root,ofstream &);
    void updateRichestID(node *n);
    void findLevel(node *,int ,int );
public:
    BST(){
        root = NULL;
    }
    void sort(){
        ofstream file;
        file.open("sort.txt");
        show(root,file);
    };
    void insert(int cash,long int id){
        if(!root)
            root = newNode(cash, id);
        else
            root = insert(root, cash, id);
    }
    void del(long int id){
        root = deleteNode(root, id);
    }
    void deleteRich(){
        richest = -1;
        updateRichestID(root);
        //printf("rich: %d %ld\n",richest,richestID);
        if(richest != -1){
            root = deleteNode(root, richestID);
        }
    }
    void output(char *);
    void deleteLevel(int);
};

void BST::show(node *root,ofstream &file){
    if(root == NULL)
        return;
    else{
        show(root->left,file);
        file<<root->id<<" "<<root->cash<<"\n";
        //printf("%ld %d\n",root->id,root->cash);
        show(root->right,file);
    }
}

void BST::output(char *filename){
    if(root == NULL){
      printf("no node to output!!!\n");
      return;
    }
    queue <node *> q;
    ofstream outFile;
    outFile.open(filename);
    node *cur = root;
    q.push(cur);
    while(q.size()!= 0){
        cur = q.front();
        q.pop();
        outFile<<cur->id<<" "<<cur->cash<<"\n";
        //printf("%ld %d\n",cur->id,cur->cash);
        if(cur->left != NULL)
            q.push(cur->left);
        if(cur->right != NULL)
            q.push(cur->right);
    }
}
void BST::deleteLevel(int n){
    levelID.clear();
    levelID.shrink_to_fit();//reset id to zero
    findLevel(root,n,0);
    if(levelID.size() == 0)
      return;
    for(int i=0;i<levelID.size();i++)
        root = deleteNode(root, levelID[i]);
}
void BST::findLevel(node *root,int n,int level){
    if(!root)
        return;
    findLevel(root->left, n, level+1);
    if(n == level){
        levelID.push_back(root->id);
        return;
    }
    findLevel(root->right, n, level+1);
}
void BST::updateRichestID(node *n){
    if(!n)
        return;
    else{
        updateRichestID(n->left);
        if(n->cash > richest){
            richestID = n->id;
            richest = n->cash;
        }
        else if(n->cash == richest && richestID < n->id){
            richestID = n->id;
            richest = n->cash;
        }
        updateRichestID(n->right);
    }
}
node *BST::newNode(int cash,long int id){
    node *n = new node;
    n->left = NULL;
    n->right = NULL;
    n->cash = cash;
    n->id = id;
    return n;
}

node *BST::insert(node *root,int cash,long int ID){
    if(root == NULL)
        return newNode(cash,ID);
    if(root->id == ID)
        return root;
    if(root->id > ID)
        root->left = insert(root->left,cash,ID);
    else if(root->id < ID)
        root->right = insert(root->right,cash,ID);
    return root;
}

void BST::showNode(node *n){
    if(n != NULL)
        printf("show node:\n%d %ld\n",n->cash,n->id);
    else
        printf("this is null\n");
}
node *BST::findMin(node *n){
    while(n->left != NULL)
        n = n->left;
    return n;
}

node *BST::deleteNode(node *root,long int id){
    if(root == NULL)
        return root;
    if(root->id > id){
        root->left = deleteNode(root->left, id);
    }
    else if(root->id < id){
        root->right = deleteNode(root->right, id);
    }
    else{
        if(root->left == NULL && root->right == NULL){
            node* temp = NULL;
            delete root;
            return temp;
        }
        else if(root->left == NULL){
            node *temp = root->right;
            delete root;
            return temp;
        }
        else if(root->right == NULL){
            node *temp = root->left;
            delete root;
            return temp;
        }
        else{
            //root has two children
            node *temp = findMin(root->right);
            root->cash = temp->cash;
            root->id = temp->id;
            root->right = deleteNode(root->right, temp->id);
        }
    }
    return root;
}

int returnSpaceCount(string input){
    int count = 0;
    for(int i=0;i<input.length();i++)
        if(input[i] == ' ')
            count++;
    return count;
}

int main(int argc,char *argv[]){
    char inputFile[50],outputFile[50];
    if(argc == 3) {
      /* code */
      strcpy(inputFile, argv[1]);
      strcpy(outputFile ,argv[2]);
    }
    ifstream f1(inputFile);
    string input_data;
    BST tree;
    while(getline(f1,input_data)){
        istringstream input(input_data);
        int space = returnSpaceCount(input_data);
        int command,cash;
        long int id;
        switch(space){
            case 2: //is insert
                input>>command>>id>>cash;
                tree.insert(cash,id);
                break;
            case 1: // is delete id or delete level
                input>>command>>id;
                if(command==3){
                    //printf("delete node\n");
                    tree.del(id);
                }
                else if(command == 5){
                    tree.deleteLevel((int)id);
                }
                break;
            case 0: // is sort or delete richest or exit
                input>>command;
                if(command == 2){
                    tree.sort();
                }
                else if(command == 4){
                    tree.deleteRich();
                }
                else if(command == 0){
                    //printf("exit\n");
                    // tree.sort();
                    tree.output(outputFile);
                    return 0;
                }
                break;
            default:
                break;
        }
    }
    return 0;
}
