#pragma once
#include <iostream>
#include <time.h>

struct Order
{
    double price;
    int quantity;
    time_t timestamp;
    int status;
    Order(double p, int qty);
};

struct BuyCompare
{
    bool operator()(const Order &a, const Order &b) const;
};

struct SellCompare
{
    bool operator()(const Order &a, const Order &b) const;
};
