//Isis Krystal Agramón Leal
//A00843802

#include <iostream>
using namespace std;

int main(){

    auto node1 = make_unique<Node<int>>(20);
    cout << "node1 data: " << node1->data << endl;
    auto node2 = make_unique<Node<int>>(10, move (node1)); 
    cout << "node2 data: " << node2->data << endl;
}