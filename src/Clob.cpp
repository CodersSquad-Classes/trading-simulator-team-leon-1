#include "Clob.h"
#include <time.h>
#include "iomanip"

// Add a new bid
void Clob::addBuy(double price, int qty)
{
    buyPQ.push(Order(price, qty));
}

// Add a new ask
void Clob::addSell(double price, int qty)
{
    sellPQ.push(Order(price, qty));
}

// Logic for the trade of bids
void Clob::match()
{
    while (!buyPQ.empty() && !sellPQ.empty())
    {
        Order best_buy = buyPQ.top();
        Order best_sell = sellPQ.top();

        if (best_buy.price < best_sell.price)
            break;

        buyPQ.pop();
        sellPQ.pop();

        string p = to_string(best_buy.price);
        p = p.substr(0, p.find(".") + 3);
        string msg = "MATCH " + to_string(min(best_buy.quantity, best_sell.quantity)) + " qty @ " + p;

        if (best_buy.quantity > best_sell.quantity)
        {
            best_buy.quantity -= best_sell.quantity;
            best_buy.status = 1;
            buyPQ.push(best_buy);
        }
        else if (best_buy.quantity < best_sell.quantity)
        {
            best_sell.quantity -= best_buy.quantity;
            best_sell.status = 1;
            sellPQ.push(best_sell);
        }

        log.push(msg);
        if (log.size() > 5)
        {
            log.pop();
        }
    }
}

// Aux function to format the timestamps
string format_time(time_t time)
{
    struct tm *local_time = localtime(&time);
    char clean_time[9];

    strftime(clean_time, sizeof(clean_time), "%T", local_time);
    return string(clean_time);
}

// Print the header of the book
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
         << setw(w) << "Qty"
         << setw(w) << "Price"
         << "\n";
    cout << LINE << "\n";
}

// Print the log of transactions
void Clob::print_history()
{
    queue<string> log_copy = log;

    cout << "History Log\n";
    cout << LINE << "\n";

    int count = 0;

    while (!log_copy.empty() && count < 5)
    {
        cout << log_copy.front() << "\n";
        log_copy.pop();
        count++;
    }

    cout << LINE << "\n";
}

// Print the bids and asks
void Clob::print()
{
    const string GREEN = "\033[32m";
    const string YELLOW = "\033[33m";
    const string RED = "\033[31m";
    const string RESET = "\033[0m";

    cout << "\033[2J\033[H";
    print_header();

    priority_queue<Order, vector<Order>, BuyCompare> buy_copy = buyPQ;
    priority_queue<Order, vector<Order>, SellCompare> sell_copy = sellPQ;

    while (!buy_copy.empty() || !sell_copy.empty())
    {
        if (!buy_copy.empty())
        {
            const Order &buy = buy_copy.top();
            string color = GREEN;
            if (buy.status == 1)
                color = YELLOW;
            cout << color
                 << setw(w) << format_time(buy.timestamp)
                 << setw(w) << buy.quantity
                 << setw(w) << fixed << setprecision(2) << buy.price
                 << RESET;
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
            string color = GREEN;
            if (sell.status == 1)
                color = YELLOW;
            cout << color
                 << setw(w) << format_time(sell.timestamp)
                 << setw(w) << sell.quantity
                 << setw(w) << fixed << setprecision(2) << sell.price
                 << RESET;
            sell_copy.pop();
        }
        else
        {
            cout << setw(3 * w) << "";
        }
        cout << "\n";
    }

    cout << LINE << "\n";

    print_history();

    cout << "\n";
    cout << "Options:\n";
    cout << "  1: Add BUY Order (Format: 1 Qty Price)\n";
    cout << "  2: Add SELL Order (Format: 2 Qty Price)\n";
    cout << "  0: Exit (Format: 0 0 0)\n";
    cout << left << setw(w) << "Action: ";
}

// Logic for the execution of the book
void Clob::run()
{
    while (true)
    {
        int action = 0;
        int qty = 0;
        double price = 0;

        print();
        if (!(cin >> action >> qty >> price))
        {
            if (cin.fail())
            {
                cerr << "Invalid input...\n";
                cin.clear();
                cin.ignore(100, '\n');
                continue;
            }
            else
            {
                cout << "Exiting...\n";
                break;
            }
        }

        string priceStr = to_string(price);
        priceStr = priceStr.substr(0, priceStr.find(".") + 3);
        if (action == 1)
        {
            addBuy(price, qty);

            string message = "Added BUY Order: " + to_string(qty) + " @ " + priceStr;
            log.push(message);

            if (log.size() > 5)
            {
                log.pop();
            }
        }
        else if (action == 2)
        {
            addSell(price, qty);

            string message = "Added SELL Order: " + to_string(qty) + " @ " + priceStr;
            log.push(message);
            if (log.size() > 5)
            {
                log.pop();
            }
            // cout << "Added SELL Order: " << qty << " @ " << fixed << setprecision(2) << price << endl;
        }
        else if (action == 0) // Uso de 0 como acción de salida
        {
            cout << "Exiting...\n";
            break;
        }
        match();
    }
}