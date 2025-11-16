#include "Clob.h"
#include <time.h>
#include "iomanip"

void Clob::addBuy(double price, int qty)
{
    buyPQ.push(Order(price, qty));
    print();
}

void Clob::addSell(double price, int qty)
{
    sellPQ.push(Order(price, qty));
    print();
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

void Clob::print_header()
{
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
}

void Clob::print()
{
    cout << "\033[2J\033[H";
    print_header();

    priority_queue<Order, vector<Order>, BuyCompare> buy_copy = buyPQ;
    priority_queue<Order, vector<Order>, SellCompare> sell_copy = sellPQ;

    while (!buy_copy.empty() || !sell_copy.empty())
    {
        if (!buy_copy.empty())
        {
            const Order &buy = buy_copy.top();
            cout << setw(w) << format_time(buy.timestamp)
                 << setw(w) << buy.quantity
                 << setw(w) << fixed << setprecision(2) << buy.price;
            buy_copy.pop();
        }
        else
        {
            cout << setw(3 * w) << "";
        }
        cout << " | ";
        if (!sell_copy.empty())
        {
            const Order &sell = sell_copy.top();
            cout << setw(w) << format_time(sell.timestamp)
                 << setw(w) << sell.quantity
                 << setw(w) << fixed << setprecision(2) << sell.price;
            sell_copy.pop();
        }
        else
        {
            cout << setw(3 * w) << "";
        }
        cout << "\n";
    }

    cout << LINE << "\n";
}
