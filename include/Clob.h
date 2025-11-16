#pragma once
#include <queue>
#include <iostream>
#include <vector>
#include "Order.h"

using namespace std;

class Clob
{
private:
    priority_queue<Order, vector<Order>, BuyCompare> buyPQ;
    priority_queue<Order, vector<Order>, SellCompare> sellPQ;

public:
    Clob() {};
    void addBuy(double price, int qty);
    void addSell(double price, int qty);
    void match();
    void print();
};