#include <deque>
#include <iostream>
#include <fstream>
using namespace std;
ifstream readFile;
ofstream writeFile;

void printDeque(deque <int> s1){
    if(s1.size() == 0)
        writeFile<<"0";
    for(int i=s1.size()-1;i>=0;i--)
        writeFile<<s1[i]<<" ";
    writeFile<<"\n";
}
void showSteps(deque <int> s1,deque <int> s2,deque <int> s3,int steps){
  writeFile<<steps<<"\n";
  printDeque(s1);
  printDeque(s2);
  printDeque(s3);
  writeFile<<"\n";
}
int binarySearch(deque<int> S, int l, int r, int key) {
  while(r-l > 1){
      int mid = l + (r-l)/2;
      if(S[mid] >= key)
        r = mid;
      else
        l = mid;
  }
  return r;
}
int findLIS(const deque <int> S,deque<int> &pos) {
  if(S.size() == 0)
    return 0;
  deque<int> LIS(S.size(),0);
  int length = 1;
  LIS[0] = S[0];
  for(int i=1;i<S.size();i++){
    if(S[i] < LIS[0])
      LIS[0] = S[i];
    else if(S[i] > LIS[length-1])
      LIS[length++] = S[i];
    else
      LIS[binarySearch(LIS, -1, length-1, S[i])] = S[i];
  }
  pos = LIS;
  return length;
}
bool checkSorted(deque<int> stacked){
    bool increasing = false;
    if(stacked[0] > stacked[1])
        increasing = true;
    for(int i=2;i<stacked.size();i++){
        if(increasing){
            if(stacked[i-1] < stacked[i])
                return false;
        }
        else{
            if(stacked[i-1] > stacked[i])
                return false;
        }
    }
    return true;
}
void stack_sort(int *arr,int length){
    deque<int> s1,s2,s3,lis;
    int steps = 0;
    for(int i=0;i<length;i++){
        lis.push_front(arr[i]);
        s1.push_front(arr[i]);
    }
    showSteps(s1,s2,s3,steps++);
    deque<int> pos;
    findLIS(lis, pos);
    //printDeque(pos);
    deque<int> s4;
    s4.push_front(3);
    s4.push_front(2);
    while(s1.size()){
        if(s1.front() == pos.front()){
            s3.push_front(s1.front());
            pos.pop_front();
        }
        else{
            s2.push_front(s1.front());
        }
        s1.pop_front();
        showSteps(s1,s2,s3,steps++);
    }
    while(s2.size() && s2.front() > s3.front()){
      s3.push_front(s2.front());
      s2.pop_front();
      showSteps(s1,s2,s3,steps++);
    }
    while(s2.size()){
        while(s3.size() != 0){
            if(s1.size() == 0){
                if(s3.front() > s2.front()){
                    s1.push_front(s3.front());
                    s3.pop_front();
                }
                else{
                    s1.push_front(s2.front());
                    s2.pop_front();
                }
            }
            else{
                if( s2.front() <= s1.front() && s2.front() > s3.front()){
                    s1.push_front(s2.front());
                    s2.pop_front();
                }
                else{
                    s1.push_front(s3.front());
                    s3.pop_front();
                }
            }
            showSteps(s1,s2,s3,steps++);
        }
        while(s2.size() && s2.front() < s1.front()){
          s1.push_front(s1.front());
          s2.pop_front();
          showSteps(s1,s2,s3,steps++);
        }
        if(checkSorted(s1) && s2.size() == 0)
            break;
        while(s1.size() != 0){
            if(s3.size() == 0){
                if(s1.front() < s2.front()){
                    s3.push_front(s1.front());
                    s1.pop_front();
                }
                else{
                    s3.push_front(s2.front());
                    s2.pop_front();
                }
            }
            else{
                if( s2.front() >= s3.front() && s2.front() < s1.front()){
                    s3.push_front(s2.front());
                    s2.pop_front();
                }
                else{
                    s3.push_front(s1.front());
                    s1.pop_front();
                }
            }
            showSteps(s1,s2,s3,steps++);
        }
        while(s2.size() && s2.front() > s3.front()){
          s3.push_front(s2.front());
          s2.pop_front();
          showSteps(s1,s2,s3,steps++);
        }
    }
}

int main(int argc, char *argv[]){
    int *arr;
    readFile.open(argv[1]);
    writeFile.open(argv[2]);
    int length;
    readFile>>length;
    arr = new int [length];
    for(int i=0;i<length;i++){
      readFile>>arr[i];
    }
    stack_sort(arr,length);

    return 0;
}
