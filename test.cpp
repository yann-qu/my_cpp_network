#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char const *argv[])
{
    vector<int> v;
    for(int i=0;i<10;i++){
        v.push_back(i);
    }
    for(auto i:v){
        cout<<i<<" ";
    }
    return 0;
}


