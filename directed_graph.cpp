#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdio>
#include <queue>
using namespace std;
queue< vector<int> >all_path;

int start_num,end_num;
typedef struct{
    int name;
    vector <int> link;
}AdjList;
int MAX_S;

int result_size;
bool isNumber(char a){
    if(a >= '0' && a<= '9' )
        return true;
    return false;
}

vector<int> splitNumber(string &input){
    vector<int> numbers;
    int num=0;char Num;
    for(int i=0;i<input.length();i++){
        Num = input[i];
        if(isNumber(input[i])){
            num = 0;
            while(isNumber(input[i])){
                num = num*10 + (int)(input[i]-'0');
                i++;
            }
            numbers.push_back(num);
        }
    }
    return numbers;
}
//table -> node number 2 name
//visited -> node number
//
int table2Node(int *table,int number,int size){
    for(int i=0;i<size;i++){
        if(table[i] == number)
            return i;
    }
    return -1;
}

void DFS(deque<AdjList> maze,bool visited[],vector<int> path,int end,int current,int *table){
    visited[current] = true;
    path.push_back(maze[current].name);
    if(current == end){
        all_path.push(path);
       // return;
    }
    else{
        if(maze[current].link.size() == 0)
            return;
        for(int i=0;i < maze[current].link.size();i++){
            int index = table2Node(table,maze[current].link[i], result_size);
            if(index != -1 && !visited[index]){
                DFS(maze,visited,path,end,index,table);
            }
        }
    }
    visited[current]=false;
}


void show_path(ofstream &f){
    if(all_path.size() > 0){
        f<<all_path.size()<<endl;
        
        while(all_path.size()){
            vector<int> path = all_path.front();
            for(int i=0;i<path.size();i++)
                f<<path[i]<<" ";
            f<<endl;
            all_path.pop();
        }
    }
    else{
        f<<"0";
    }
}

int main(int argc,char *argv[]){
    char iFile[50],oFile[50];
    if(argc >= 3){
        strcpy(iFile, argv[1]);
        strcpy(oFile, argv[2]);
    }
    else{
        cout<<"Please enter input file:"<<endl;
        cin>>iFile;
        cout<<"Please enter output file:"<<endl;
        cin>>oFile;
    }
    ifstream f1(iFile);
    ofstream fo(oFile);
    string input_data;
    
    getline(f1,input_data);
    if(input_data.length() >= 1){
        start_num = stoi(input_data);
    }
    getline(f1,input_data);
    if(input_data.length() >= 1){
        end_num = stoi(input_data);
    }
    MAX_S = -1;
    vector<int> splited;
    deque<AdjList>result;
    while(getline(f1,input_data)){
        if(input_data.length()>0 && isNumber(input_data[0])){
            AdjList number;
            splited =splitNumber(input_data);
            if(splited[0] == 0 && splited.size() >= 0)
                break;
            if(splited.size() > 1){
                number.name = splited[0];
                if(number.name > MAX_S)
                    MAX_S = number.name;
                for(int i=1;i<splited.size();i++)
                    number.link.push_back(splited[i]);
                
            }
            else
                number.name = splited[0];
            sort(number.link.begin(),number.link.end());
            result.push_back(number);
        }
    }
    bool *visited;
    int *table;
    result_size = result.size();
    table = new int [MAX_S+1];
    visited = new bool [result.size()];
    for(int i=0;i<=MAX_S;i++)
        visited[i] = false;
    
    for(int i=0;i<result.size();i++)
        table[i] = result[i].name;
    
    vector<int>path;
    
    int start_index =table2Node(table,start_num,result.size());
    int end_index = table2Node(table,end_num,result.size());
    if( start_index != -1 || end_index != -1){
        DFS(result,visited,path,end_index,start_index,table);
        show_path(fo);
    }
    return 0;
}