#include <iostream>
#include "Clob.h"

using namespace std;

int main()
{
    Clob *BookViewer = new Clob();
    BookViewer->addBuy(10, 5);
    BookViewer->addBuy(12, 5);
    BookViewer->addBuy(14, 5);
    BookViewer->addSell(10, 5);
    BookViewer->addSell(100, 5);
    BookViewer->run();
}