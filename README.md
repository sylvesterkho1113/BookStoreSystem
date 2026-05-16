# 📚 BookStoreSystem

A robust, console-based **Bookstore Management System** built with C++. This project demonstrates core concepts of object-oriented programming, file handling, and multi-user authentication. It provides a seamless experience for both administrators and customers to manage and purchase books.

---

## ✨ Key Features

### 🔐 Multi-User Authentication
*   **Admin Access**: Secure login for store administrators.
*   **Customer Portal**: Secure login and registration system for users.

### 🛠️ Admin Dashboard
*   **Inventory Management**: Add, update, delete, and view books in the system.
*   **Order Management**: 
    *   Monitor all customer transactions.
    *   Search orders by Customer Name or Status.
    *   Update order statuses (e.g., *Placed, Preparing, Delivered*).
*   **Sales Reports**: Generate detailed reports on earnings, profit margins, and top-selling books.

### 🛒 Customer Experience
*   **Book Catalog**: Browse a comprehensive list of available books with pricing and descriptions.
*   **Search Engine**: Quickly find books by title or author.
*   **Shopping Cart**: Add books to a virtual cart, adjust quantities, and proceed to checkout.
*   **Wishlist**: Save favorite books to a personal wishlist for future purchases.
*   **Order History**: View past transactions with detailed digital receipts.

---

## 🛠️ Technology Stack
*   **Language**: C++
*   **Database**: Flat-file system (`.txt` files) for persistent data storage.
*   **Libraries**: `<iostream>`, `<fstream>`, `<iomanip>`, `<vector>`, `<chrono>`, `<thread>`.

---

## 📁 File Structure & Database
The system uses the following text files as its "database" layers:

| File | Description |
| :--- | :--- |
| `customers.txt` | Stores customer profiles (Names, Usernames, Passwords, Contacts). |
| `books.txt` | Main inventory containing Book ID, Author, Price, Stock, etc. |
| `wishlist.txt` | Links customer usernames to their desired book IDs. |
| `cart.txt` | Temporary storage for items pending checkout. |
| `sales.txt` | Master record of transaction IDs, totals, and statuses. |
| `orders.txt` | Line-item details for every transaction (Book ID, Quantity). |

---

## 🚀 Getting Started

### Prerequisites
*   A C++ compiler (GCC, MSVC, or Clang).
*   Recommended IDE: VS Code or Code::Blocks.

### Compilation & Running
1.  Clone the repository:
    ```bash
    git clone https://github.com/sylvesterkho1113/BookStoreSystem.git
    ```
2.  Navigate to the directory:
    ```bash
    cd BookStoreSystem
    ```
3.  Compile the source code:
    ```bash
    g++ G03_BookStoreSystem.cpp -o BookStoreSystem
    ```
4.  Run the application:
    ```bash
    ./BookStoreSystem
    ```

---

## 🔑 Default Credentials

| Role | Username | Password |
| :--- | :--- | :--- |
| **Admin** | `admin` | `admin123` |
| **Customer** | `ali` | `ali1234` |
| **Customer (Register)** | (Create your own in-app) | - |

---

## 👥 Team Members (Group 03)
1.  **See Chwan Kai**
2.  **Kho Wei Cong**
3.  **Tee Kian Hao**
4.  **Tee Chin Yean**

---

## 📜 License
This project was developed for educational purposes as part of a programming assignment.
