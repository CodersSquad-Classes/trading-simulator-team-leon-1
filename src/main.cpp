#include <iostream>
#include "Clob.h"

using namespace std;

int main()
{
    Clob *BookViewer = new Clob();
    BookViewer->addBuy(10, 5);
    BookViewer->addSell(10, 5);

    BookViewer->print();
}