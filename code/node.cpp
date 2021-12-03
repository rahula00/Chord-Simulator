#include "node.h"
#include <iostream>
#include <cassert>
using namespace std;

// checks if key is between vars a and b
// uint8 range = [0, 255]
bool betweenExclusive(uint8_t left, uint8_t right, uint8_t key){
    //printf("Exclusive: L: %d, R: %d, K: %d\n", left, right, key);
    fflush(stdout);
    if(key == right || key == left) {
        return false;
    }
    if (left >= right){   
    // if (left > right){     
        return ((key > left) || (key < right));
    } else if (right > left){
        return ((key > left) && (key < right));
    }
    return false;
}


bool betweenLeftInclusive(uint8_t left, uint8_t right, uint8_t key){
    printf("LeftInclusive: L: %d, R: %d, K: %d\n", left, right, key);
    fflush(stdout);
    if(key == left) {
        return true;
    }
    // if(key == right) {
    //     return false;
    // }
    if (left >= right){    
        return ((key > left) || (key < right));
    } else if (right > left){
        return ((key > left) && (key < right));
    }
    return false;
}

Node* Node::findSuccessor(uint8_t id) {
    Node* nP = findPredecessor(id);
    return nP->get(1);
}

Node* Node::findPredecessor(uint8_t id) {
    

    //printf("finding predecessor of %d\n", id);
    Node* nP = this;
    Node* nP_successor = nP->get(1);
    bool between = betweenLeftInclusive(nP->getID(), nP_successor->getID(), id);
    if(between){
        //printf("BETWEEN!\n");
    }
    else{
        //printf("NOT BETWEEN!\n");
    }
    while( !between ){
        // //printf("find pred loop %d,  nP = %d\n", loopCnt, nP->getID());
        nP = nP->closestPrecedingFinger(id);
        nP_successor = nP->get(1);
        between = betweenLeftInclusive(nP->getID(), nP_successor->getID(), id);
    }
    if(between){
        //printf("key %d was in between %d and %d\n", id, nP->getID(), nP_successor->getID());
    }
    fflush(stdout);
    return nP;
}

Node* Node::closestPrecedingFinger(uint8_t id) {  
    Node* n = this; 
    for(int i=BITLENGTH; i>0; --i) {
        // //cout << "CP Segfaulted Loop Cnt " << i <<endl;
        Node* finger_i_node = get(i);
        //printf("CPF finger_i_node is %d. Gotten from get(%d) from node %d\n", finger_i_node->getID(), i, this->getID());
        // //printf("%d\n", n->getID());
        // fflush(stdout);
        // //printf("%d\n", id);
        // fflush(stdout);
        // //printf("%d\n", finger_i_node->getID());
        // fflush(stdout);
        if(betweenExclusive(n->getID(), id, finger_i_node->getID())){
            //cout << "CP Did not Segfault Loop: " << i << endl;
            return finger_i_node;
        }
    }
    return n;
}

// finger[k].start = (n + 2**k-1)
uint8_t Node::getStart(uint8_t k){
    uint8_t n = id_;
    return n + pow(2, k-1);
}

// initialize finger table of local node;
// n0 is an arbitrary node already in the network
// n.init_finger_table(n0)
void Node::init_finger_table(Node* node) {
    Node* n = this;

    uint8_t start = getStart(1);
    //printf("start(1) of %d is %d\n", n->getID(), start);
    FingerTable_.set(1, node->findSuccessor(start));
    //printf("Successor of %d was found to be %d\n", start, node->findSuccessor(start)->getID());

    Node* successor = FingerTable_.get(1);
    predecessor = successor->predecessor;
    successor->predecessor = n;

    //printf("predecessor is %d, successor is %d\n", predecessor->getID(), successor->getID());

    for(int i=1; i < BITLENGTH; i++){
        //printf("INIT FINGER TABLE ITER: %d\n", i);
        Node* finger_i_node = get(i);
        //printf("finger_i_node: %d\n", finger_i_node->getID());
        fflush(stdout);
        uint8_t n = id_;
        if(betweenExclusive(n, finger_i_node->getID(), getStart(i+1))){
            //printf("IF CASE\n");
            FingerTable_.set(i+1, finger_i_node);
            //printf("setting finger %d of node %d to %d\n", i+1, this->getID(), finger_i_node->getID());
        }
        else{
            //printf("ELSE CASE\n");
            FingerTable_.set(i+1, node->findSuccessor(getStart(i+1)));
        }
        // this->prettyPrint();
    }

}

// update all nodes whose finger tables should refer to n
void Node::update_others(){
    for(int i = 1; i <= BITLENGTH;  i++) {
        Node* n = this;
        uint8_t findPredOfThis = (n->getID() - pow(2,i-1));
        Node* p = findPredecessor(findPredOfThis);
        //printf("P IS: %d, predecessor of %d, on iter: %d\n\n", p->getID(), findPredOfThis, i);
        p->update_finger_table(n, i);
    }
}

void Node::update_finger_table(Node* s, uint8_t i){
    Node* n = this;
    //printf("UpdateFT: Checking Node %d, s=%d, i=%d\n", this->getID(), s->getID(), i);
    fflush(stdout);
    bool between = betweenExclusive(n->getID(), get(i)->getID(), s->getID());
    //printf("checked between\n");
    fflush(stdout);
    if(between){      
        //printf("UPDATING NODE: %d finger %d with node %d\n\n", this->getID(), i, s->getID());
        fflush(stdout);
        FingerTable_.set(i, s);
        Node* p = predecessor;
        p->update_finger_table(s, i);
    }
}


void Node::join(Node *node)
{
    if (node) {
        //printf("ADDING NODE: %d\n", this->getID());
        init_finger_table(node); 
        update_others();
    } else {
        predecessor = this;
        for (int i = 1; i < BITLENGTH + 1; i++){
            FingerTable_.set(i, this);
        }
    }
    auto a = transfer(node);
    printf("\n\t_________Values_________\n");
    printValues();
    FingerTable_.prettyPrint(this);

}

// void Node::Leave() {
//     //to do?
// }

uint8_t Node::find(uint8_t key) {

}

void Node::insert(uint8_t key, uint8_t val) {
    Node* n = this;
    while(!betweenLeftInclusive(n->getID(), n->getSuccessor()->getID(), key)) {
        n = n->getSuccessor();
    }
    n->getSuccessor()->update(key, val);
}

void Node::insert(uint8_t key) { 
    insert(key, NULL);
}

void Node::remove(uint8_t key)
{
    localKeys_.erase(key);
}


