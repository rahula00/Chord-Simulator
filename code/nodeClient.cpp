#include "node.h"
#include <iostream>

using namespace std;
int main(int argc, char * argv[]){
    Node n0(5); // node_id == 5
    Node n1(63); // node_id == 63
    n0.join(NULL); // the first node to join the Chord network.
    // n0.insert(3, 3); // insert key = 3
    n1.join(&n0); // the second node join the Chord network.
    // n1.insert(5, 50); // insert key = 5
    // n0.find(5); // key query
}