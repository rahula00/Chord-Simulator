#include "node.h"
#include <iostream>


using namespace std;

int main(int argc, char * argv[]){
    // Node n0(5); // node_id == 5
    // Node n1(63); // node_id == 63
    // Node n2(30); // noe_id == 30
    // n0.join(NULL); // the first node to join the Chord network.
    // n1.join(&n0); // the second node join the Chord network.
    // n2.join(&n1); // the third node join the Chord network.
    Node n0(0);
    Node n1(30);
    Node n2(65);
    Node n3(110);
    Node n4(160);
    Node n5(230);
    // Node n6(245);
    n0.join(NULL);
    n1.join(&n0);
    n2.join(&n1);
    n3.join(&n2);
    n4.join(&n3);
    n5.join(&n4);
    // n6.join(&n5);
    n5.insert(3,3);
    n4.insert(30,3);
    n1.insert(31,3);
    n3.insert(65);
    n1.insert(0,3);
    n2.insert(0);
    n2.insert(229);
    n0.insert(230);
    n0.insert(231);
    printf("Find.. key: %d, val: %d\n", 3, n4.find(3));
    printf("Find.. key: %d, val: %d\n", 30, n3.find(30));
    printf("Find.. key: %d, val: %d\n", 32, n2.find(32)); 
    printf("Find.. key: %d, val: %d\n", 32, n1.find(32)); 
    printf("Find.. key: %d, val: %d\n", 32, n0.find(32)); 
    printf("Find.. key: %d, val: %d\n", 32, n4.find(32)); 
    printf("Find.. key: %d, val: %d\n", 232, n1.find(232)); 
    printf("Find.. key: %d, val: %d\n", 235, n1.find(235)); 
    printf("Find.. key: %d, val: %d\n", 230, n1.find(230)); 
    printf("Find.. key: %d, val: %d\n", 231, n1.find(231)); 
    // n0.prettyPrint();
    // n1.prettyPrint();
    // n2.prettyPrint();
    // n3.prettyPrint();
    // n4.prettyPrint();
    // n5.prettyPrint();

    

    // n5.prettyPrint();
    // n6.prettyPrint();
}
