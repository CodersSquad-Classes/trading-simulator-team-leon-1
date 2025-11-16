#include "Order.h"

Order::Order(double p, int qty) : price(p), quantity(qty)
{
    isBuy = false;
    timestamp = time(NULL);
};

bool BuyCompare::operator()(const Order &a, const Order &b) const
{
    if (a.price == b.price)
    {
        return a.timestamp > b.timestamp;
    }
    return a.price < b.price;
};

bool SellCompare::operator()(const Order &a, const Order &b) const
{
    if (a.price == b.price)
    {
        return a.timestamp > b.timestamp;
    }
    return a.price > b.price;
};
