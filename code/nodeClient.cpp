#include "node.h"
#include <iostream>

using namespace std;
int main(int argc, char * argv[]){
    printf("hi\n");
    Node temp;
    temp.insert(69, 100);
    cout << temp.find(69) << "\n";
    return 1;
}