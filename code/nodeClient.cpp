#include "node.h"
#include <iostream>


using namespace std;
void printChord();

int main(int argc, char * argv[]){
    // To print a node's finger table, use this function
    // n0.prettyPrint();

    // To print a node's local keys
    // n0.printLocalKeys();

    // To print ALL finger tables, call this function from any node
    //n0.printFingerTables();

    // To print ALL keys from all nodes, call this function from any node
    // n0.printAllLocalKeys();
    
    printChord();
    Node n0(0);
    Node n1(30);
    Node n2(65);
    Node n3(110);
    Node n4(160);
    Node n5(230);
    Node n6(100);

    n0.join(NULL);
    n1.join(&n0);
    n2.join(&n1);
    n3.join(&n2);
    n4.join(&n3);
    n5.join(&n4);

    n0.insert(3, 3);
    n1.insert(200);
    n2.insert(123);
    n3.insert(45,3);
    n4.insert(99);
    n2.insert(60,10);
    n0.insert(50,8);
    n3.insert(100,5);
    n3.insert(101,4);
    n3.insert(102,6);
    n5.insert(240,8);
    n5.insert(250,10);

    n6.join(&n5);

    n0.find(3);
    n0.find(200);
    n0.find(123);
    n0.find(45);
    n0.find(99);
    n0.find(60);
    n0.find(50);
    n0.find(100);
    n0.find(101);
    n0.find(102);
    n0.find(240);
    n0.find(250);

    n2.find(3);
    n2.find(200);
    n2.find(123);
    n2.find(45);
    n2.find(99);
    n2.find(60);
    n2.find(50);
    n2.find(100);
    n2.find(101);
    n2.find(102);
    n2.find(240);
    n2.find(250);

    n6.find(3);
    n6.find(200);
    n6.find(123);
    n6.find(45);
    n6.find(99);
    n6.find(60);
    n6.find(50);
    n6.find(100);
    n6.find(101);
    n6.find(102);
    n6.find(240);
    n6.find(250);
}

void printChord() {
    cout << R"(

          _____                    _____                   _______                   _____                    _____          
         /\    \                  /\    \                 /::\    \                 /\    \                  /\    \         
        /::\    \                /::\____\               /::::\    \               /::\    \                /::\    \        
       /::::\    \              /:::/    /              /::::::\    \             /::::\    \              /::::\    \       
      /::::::\    \            /:::/    /              /::::::::\    \           /::::::\    \            /::::::\    \      
     /:::/\:::\    \          /:::/    /              /:::/~~\:::\    \         /:::/\:::\    \          /:::/\:::\    \     
    /:::/  \:::\    \        /:::/____/              /:::/    \:::\    \       /:::/__\:::\    \        /:::/  \:::\    \    
   /:::/    \:::\    \      /::::\    \             /:::/    / \:::\    \     /::::\   \:::\    \      /:::/    \:::\    \   
  /:::/    / \:::\    \    /::::::\    \   _____   /:::/____/   \:::\____\   /::::::\   \:::\    \    /:::/    / \:::\    \  
 /:::/    /   \:::\    \  /:::/\:::\    \ /\    \ |:::|    |     |:::|    | /:::/\:::\   \:::\____\  /:::/    /   \:::\ ___\ 
/:::/____/     \:::\____\/:::/  \:::\    /::\____\|:::|____|     |:::|    |/:::/  \:::\   \:::|    |/:::/____/     \:::|    |
\:::\    \      \::/    /\::/    \:::\  /:::/    / \:::\    \   /:::/    / \::/   |::::\  /:::|____|\:::\    \     /:::|____|
 \:::\    \      \/____/  \/____/ \:::\/:::/    /   \:::\    \ /:::/    /   \/____|:::::\/:::/    /  \:::\    \   /:::/    / 
  \:::\    \                       \::::::/    /     \:::\    /:::/    /          |:::::::::/    /    \:::\    \ /:::/    /  
   \:::\    \                       \::::/    /       \:::\__/:::/    /           |::|\::::/    /      \:::\    /:::/    /   
    \:::\    \                      /:::/    /         \::::::::/    /            |::| \::/____/        \:::\  /:::/    /    
     \:::\    \                    /:::/    /           \::::::/    /             |::|  ~|               \:::\/:::/    /     
      \:::\    \                  /:::/    /             \::::/    /              |::|   |                \::::::/    /      
       \:::\____\                /:::/    /               \::/____/               \::|   |                 \::::/    /       
        \::/    /                \::/    /                 ~~                      \:|   |                  \::/____/        
         \/____/                  \/____/                                           \|___|                   ~~              
                                                                                                                             
    
)" << '\n';
};