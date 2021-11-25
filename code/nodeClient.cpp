#include "node.h"
#include <iostream>

using namespace std;
int main(int argc, char * argv[]){
    printf("hi\n");
    Node temp(10);
    Node temp2(20);
    temp.insert(69, 100);
    temp.join(NULL);
    temp2.join(&temp);
    cout << (int)temp.find(69) << "\n";
    return 1;
}