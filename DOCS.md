# Project Documentation

## **Trading Simulator – Team León 1**

---

## 📄 Introduction

This project is a **trading simulator** that implements a **Matching Engine** using a **Central Limit Order Book (CLOB)** model. The goal is to simulate how real stock exchanges receive orders, store them in an order book, and execute trades using price‑time priority.

The simulator includes:

- Traders capable of sending buy/sell limit orders.
- A fully functional order book storing bids and asks.
- A matching engine that processes orders and executes trades.
- A real-time terminal dashboard that displays market depth and recent trades.

This project provides hands-on experience with **financial market microstructure**, **C++ data structures**, and **exchange system architecture**.

---

## 📚 Research on Stock Exchanges

### 🔹 Limit Order Book (LOB)

A **Limit Order Book** stores all open (unmatched) buy and sell limit orders.

- **Bids** (buy orders): sorted from highest → lowest price.
- **Asks** (sell orders): sorted from lowest → highest price.
- **Market orders** execute immediately at the best available price.

A LOB is dynamic: orders are inserted, removed, matched, partially filled, or canceled.

### 🔹 Matching Engine

The matching engine:

- Receives incoming orders.
- Looks for matches using **price‑time priority**.
- Executes full or partial trades.
- Updates the book accordingly.

**Priority rules:**

1. Best price first.
2. If prices are equal, the oldest order executes first (FIFO).

### 🔹 Central Limit Order Book (CLOB)

A CLOB aggregates **all** orders from **all** participants.
Benefits:

- Liquidity
- Transparency
- Fair price discovery

Our simulator follows the exact CLOB logic.

---

## 🛠️ Software Design and Implementation

### 🧩 Architecture Overview

**Modules:**

1. **Trader Module** – Generates and submits orders.
2. **Order Book** – Stores bid and ask levels.
3. **Matching Engine** – Matches orders using price-time priority.
4. **Trade History** – Records all executed trades.
5. **Dashboard UI** – Displays depth and trades in real time.

---

## 🏗️ Component Diagram

```
+-----------------+        +-------------------+        +-------------------+
|     Traders     | -----> |  Matching Engine  | -----> |   Trade History   |
| (Order Sender)  |        |                   |        |                   |
+-----------------+        +---------+---------+        +---------+---------+
                                  |
                                  v
                        +---------+---------+         +--------+--------+
                        |      Order Book   |         |   Terminal UI   |
                        |   (Bids & Asks)   |         | Dashboard View  |
                        +-------------------+         +------------------+
```

---

## 📦 Data Structures

The order book uses:

- **Two maps (ordered containers)**:

  - `map<double, queue<Order>> bids;` (sorted descending)
  - `map<double, queue<Order>> asks;` (sorted ascending)

Each **price level** contains a **FIFO queue** of orders.

Advantages:

- O(log n) insertion
- O(1) access to oldest order per price level
- Automatic sorting of price levels

---

## ⚙️ Matching Logic (Pseudocode)

```cpp
void processOrder(Order o) {
    if (o.type == LIMIT) {
        while (o.volume > 0 && existsOppositeBest(o)) {
            Order& best = getBestOpposite(o);

            if (isPriceCompatible(o, best)) {
                int traded = min(o.volume, best.volume);
                executeTrade(o, best, traded);

                o.volume -= traded;
                best.volume -= traded;

                if (best.volume == 0) {
                    removeOrder(best);
                }
            } else {
                break;
            }
        }

        if (o.volume > 0) {
            addToOrderBook(o);
        }
    }
    else if (o.type == MARKET) {
        // Same logic but without price checks
    }
}
```

---

## 🖥️ UI and Visualization

Example terminal output:

```
---------------- ORDER BOOK ----------------
     Asks                     Spread                  Bids
 102.0 : 150                                        99.5 : 200
 101.5 : 100                                        99.0 : 120
 101.0 : 80                                         98.5 : 300
----------------------------------------------------------

Recent Trades:
[10:43:12] Price: 101.0 | Qty: 50
[10:43:14] Price: 100.5 | Qty: 30
```

---

## 🔑 Key Functions

- `addOrder(Order o)` – Appends order to the correct price level.
- `cancelOrder(int id)` – Removes an existing order.
- `modifyOrder(int id, int newQty, float newPrice)` – Updates price or size.
- `matchOrders()` – Core matching loop.
- `getBestBid()` / `getBestAsk()` – Accessors for top levels.
- `executeTrade(Order a, Order b, int qty)` – Stores trade and logs it.
- `printOrderBook()` – Displays current book.
- `simulate(int steps)` – Runs automated order flow.

---

## 🎓 Conclusions and Learnings

### 👤 **David Bribiesca**

This evidence helped me understand the use of queues in real life activities, and talking about the stock market which is ruled mainly by computers it is important to understand the structure of this type of movements and activities. The use of priority queues is really clever to ensure that the correct movements are done.

### 👤 **Aarón Hernández**

This activity helped me understand the aplications of priority queues in code but also in real life cases. I also learned about the CLOB concept, and it was useful to see how this data structures can be used to build complex systems as this.

---
