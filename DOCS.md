# Project Documentation

## 📌 Project Name
**Trading Simulator – Team León 1**

---

## 📄 Introduction

This project is a **trading simulator** that implements a **Matching Engine** using a **Central Limit Order Book (CLOB)** model. The goal is to simulate how real stock exchanges receive buy/sell orders, manage an order book, and execute trades using price-time priority.

The simulator includes:
- Trader modules capable of generating buy/sell limit orders.
- A fully functional order book with bid and ask levels.
- A matching engine that processes and executes trades.
- A real-time terminal dashboard showing book depth and recent trades.

This project helps understand financial market microstructure and the internal logic of exchanges.

---

## 📚 Research on Stock Exchanges

### 🔹 Limit Order Book (LOB)
A **Limit Order Book** is a data structure that stores all unfilled limit buy and sell orders.

- **Bids**: Buy orders, sorted from highest to lowest price.
- **Asks**: Sell orders, sorted from lowest to highest price.
- **Market orders** execute immediately at the best available price.

### 🔹 Matching Engine
The matching engine:
- Receives incoming orders.
- Matches them using **price-time priority**.
- Executes full or partial trades.
- Updates the order book accordingly.

Priority rules:
1. Best price wins.
2. If prices match, the earliest order wins (FIFO).

### 🔹 Central Limit Order Book (CLOB)
A CLOB centralizes all buy and sell limit orders and matches them transparently.  
Benefits:
- Liquidity  
- Transparent market depth  
- Fair price discovery  

Our simulator follows this model closely.

---

## 🛠️ Software Design and Implementation

### 🧩 Architecture Overview

**Modules:**
1. **Trader Module** – Sends buy/sell orders.
2. **Order Book** – Stores bids and asks.
3. **Matching Engine** – Executes trades using price-time priority.
4. **Trade History** – Stores all executed trades.
5. **Dashboard UI** – Displays real-time market activity.

---

### 🏗️ Component Diagram

