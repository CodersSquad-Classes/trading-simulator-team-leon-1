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
    const int w = 10;
    const string LINE = "-------------------------------------------------------------";

    const Order &buyTop = buyPQ.top();
    const Order &sellTop = sellPQ.top();

    cout << LINE << "\n";
    cout << left << setw(3 * w) << "BUY (bids)"
         << " | "
         << "SELL (asks)\n";
    cout << LINE << "\n";

    cout << left << setw(w) << "Time"
         << setw(w) << "Qty"
         << setw(w) << "Price"
         << " | "
         << setw(w) << "Time"
         << setw(w) << "Price"
         << setw(w) << "Qty"
         << "\n";
    cout << LINE << "\n";

    cout << setw(w) << format_time(buyTop.timestamp)
         << setw(w) << buyTop.quantity
         << setw(w) << fixed << setprecision(2) << buyTop.price;

    cout << " | ";

    cout << setw(w) << format_time(sellTop.timestamp)
         << setw(w) << sellTop.quantity
         << setw(w) << fixed << setprecision(2) << sellTop.price
         << "\n";

    cout << LINE << "\n";
}