#pragma once
#include <queue>
#include <iostream>
#include <vector>
#include <string>
#include "Order.h"

using namespace std;

class Clob
{
private:
    queue<string> log;
    int w = 10;
    const string LINE = "-------------------------------------------------------------";
    priority_queue<Order, vector<Order>, BuyCompare> buyPQ;
    priority_queue<Order, vector<Order>, SellCompare> sellPQ;

public:
    Clob() {};
    void addBuy(double price, int qty);
    void addSell(double price, int qty);
    void match();
    void print_header();
    void print_history();
    void print();
    void run();
};