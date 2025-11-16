#include "Clob.h"
#include <time.h>
#include "iomanip"

void Clob::addBuy(double price, int qty)
{
    buyPQ.push(Order(price, qty));
}

void Clob::addSell(double price, int qty)
{
    sellPQ.push(Order(price, qty));
}

void Clob::match()
{
}

string format_time(time_t time)
{
    struct tm *local_time = localtime(&time);
    char clean_time[9];

    strftime(clean_time, sizeof(clean_time), "%T", local_time);
    return string(clean_time);
}

void Clob::print()
{
    cout << "  Buy\n";
    cout << "  " << left << setw(10) << "Time" << setw(10) << "Qty" << setw(10) << "Price" << "\n";

    const Order &buyTop = buyPQ.top();
    cout << "  " << setw(10) << format_time(buyTop.timestamp)
         << setw(10) << buyTop.quantity
         << setw(10) << fixed << setprecision(2) << buyTop.price << "\n";

    cout << "\n  Sell\n";
    cout << "  " << left << setw(10) << "Time" << setw(10) << "Qty" << setw(10) << "Price" << "\n";

    const Order &sellTop = sellPQ.top();
    cout << "  " << setw(10) << format_time(sellTop.timestamp)
         << setw(10) << sellTop.quantity
         << setw(10) << fixed << setprecision(2) << sellTop.price << "\n";
}