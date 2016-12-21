#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
int s1[7+1] = {0,2,5,7,9,3,1,2};
int s2[5+1] = {0,3,5,3,2,8};
const int s1_length = 7,s2_length = 5;
int array[7+1][5+1],previous[7+1][5+1];

void printLCS(int i,int j){
  if(i==0 || j==0)return;

  if(previous[i][j] == array[i-1][j-1]){
    printLCS(i-1,j-1);
    cout<<s1[i];
  }
  else if(previous[i][j] == array[i-1][j])
    printLCS(i-1,j);
  else if(previous[i][j] == array[i][j-1])
    printLCS(i,j-1);
}


void LCS(){
  memset(array,0,sizeof(array));
  memset(previous,0,sizeof(previous));
  for(int i=1;i<=s1_length;i++){
    for(int j=1;j<=s2_length;j++)
    if(s1[i] == s2[j]){
      array[i][j] = array[i-1][j-1]+1;
      previous[i][j] = array[i-1][j-1];
    }
    else{
      if(array[i-1][j] < array[i][j-1]){
        array[i][j] = array[i][j-1];
        previous[i][j] = array[i][j-1];
      }
      else{
        array[i][j] = array[i-1][j];
        previous[i][j] = array[i-1][j];
      }
    }
  }
  cout<<"LCS length: "<<array[s1_length][s2_length]<<endl;
  cout<<"LCS : ";
  printLCS(s1_length,s2_length);
}

int main(){
  LCS();
  return 0;
}
