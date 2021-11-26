#include "node.h"
#include <iostream>

using namespace std;
int main(int argc, char * argv[]){
    Node n0(5); // node_id == 5
    Node n1(63); // node_id == 63
    Node n2(30); // node_id == 30
    n0.join(NULL); // the first node to join the Chord network.
    n1.join(&n0); // the second node join the Chord network.
    n2.join(&n1); // the third node join the Chord network.
}