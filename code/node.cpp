#include "node.h"
#include <iostream>
#include <cassert>
using namespace std;

// checks if key is between vars a and b
// uint8 range = [0, 255]
bool between(uint8_t a, uint8_t b, uint8_t key, bool aInc, bool bInc){
    // if not a inclusive, increase a by 1
    if(a == b){
        // (0,0] returns FALSE
        if((key == a) && (aInc && bInc)){
            printf("key %d matches a and b\n", key);
        }
        else{
            printf("key %d does not match %d and %d because of aInc and bInc vals\n", key, a, b);
            return false;
        }
        return (key == a) && (aInc && bInc);
    }

    // //printf("A IS %d and aINC IS %d\n", a, aInc);

    if(!aInc){
        a++;
    }
    // if not b inclusive, decrease b by 1
    if(!bInc){
        b--;
    }
    if (a > b){    
            // //printf("a(%d) is greater than b(%d), key is %d\n", a, b, key);
            printf("searching range [%d, 255], [0, %d] for %d\n", a, b, key);
        if((key >= a) || (key <= b)){
            printf("Key is in between!\n");
        }
        else{
            printf("Key is NOT in between!\n");
        }
        return (key >= a) || (key <= b);
    }
    else if (b > a){
        // //printf("a(%d) is smaller than b(%d), key is %d\n", a, b, key);
        printf("searching range [%d, %d] for %d\n", a, b, key);
        if((key >= a) && (key <= b)){
            printf("Key is in between!\n");
        }
        else{
            printf("Key is NOT in between!\n");
        }
        return (key >= a) && (key <= b);
    }
    else{
        return key == a;
    }

    return false;
}

Node* Node::findSuccessor(uint8_t id) {
    Node* nP = findPredecessor(id);
    return nP->get(1);
}

Node* Node::findPredecessor(uint8_t id) {
    Node* nP = this;
    Node* nP_successor = nP->get(1);

    int loopCnt = 0;

  
    while( !between(nP->getID(), nP_successor->getID(), id, true, false) ){
        printf("find pred loop %d,  nP = %d\n", loopCnt, nP->getID());
        nP = nP->closestPrecedingFinger(id);
        loopCnt++;
        if(loopCnt > ){
            break;
        }
    }
    return nP;
}

Node* Node::closestPrecedingFinger(uint8_t id) {  
    Node* n = this; 
    for(int i=BITLENGTH; i>0; --i) {
        Node* finger_i_node = get(i);
        if( between(n->getID(), id, finger_i_node->getID(), false, false) ){
            return finger_i_node;
        }
    }
    return n;
}

// finger[k].start = (n + 2**k-1)
uint8_t Node::getStart(uint8_t k){
    // uint8_t n = FingerTable_.get(k)->getID();
    uint8_t n = id_;
    return n + pow(2, k-1);
}

// finger.node = first node > n.finger[k].start
Node* Node::getNode(uint8_t k){
    uint8_t fingerStart = getStart(k);
    Node* node = findSuccessor(fingerStart);
    FingerTable_.set(k, node);
    return node;
}

// initialize finger table of local node;
// n0 is an arbitrary node already in the network
// n.init_finger_table(n0)
void Node::init_finger_table(Node* node) {
    Node* n = this;

    FingerTable_.set(1, node->findSuccessor(getStart(1)));

    node->set(1, n);

    // Node* successor = getNode(1);
    Node* successor = FingerTable_.get(1);
    predecessor = successor->predecessor;
    successor->predecessor = n;

    for(int i=1; i<BITLENGTH; i++){
        printf("INIT FINGER TABLE ITER: %d\n", i);
        Node* finger_i_node = getNode(i);
        uint8_t n = id_;
        if( between(n, finger_i_node->getID(), getStart(i+1), false, false) ){
            FingerTable_.set(i+1, finger_i_node);
        }
        else{
            FingerTable_.set(i+1, node->findSuccessor(getStart(i+1)));
        }
    }

}

// update all nodes whose finger tables should refer to n
void Node::update_others(){
    for(int i = 1; i <= BITLENGTH;  i++) {
        Node* n = this;
        Node* p = findPredecessor(n->getID() - pow(2,i-1));
        printf("P IS: %d\n\n", p->getID());
        p->update_finger_table(n, i);
    }
}

void Node::update_finger_table(Node* s, uint8_t i){
    Node* n = this;
    // printf("UpdateFT: Checking Node: %d\n\n", this->getID());
    if(between(n->getID(), getNode(i)->getID(), s->getID(), false, false)){
        // printf("UPDATING NODE: %d\n\n", this->getID());
        FingerTable_.set(i, s);
        Node* p = predecessor;
        p->update_finger_table(s, i);
    }
}


void Node::join(Node *node)
{
    if (node) {
        init_finger_table(node); 
        update_others();
    } else {
        predecessor = this;
        for (int i = 1; i < BITLENGTH + 1; i++){
            FingerTable_.set(i, this);
        }
    }
    FingerTable_.prettyPrint(this);
}

// void Node::Leave() {
//     //to do?
// }

uint8_t Node::find(uint8_t key)
{

}

void Node::insert(uint8_t key, uint8_t val)
{


}

void Node::remove(uint8_t key)
{
    localKeys_.erase(key);
}


