# C++ Secure Multi-Currency Wallet

A comprehensive, command-line-based digital wallet and banking simulation system built entirely in C++. This project demonstrates a complete, self-contained application featuring multi-currency account management, secure user authentication with custom hashing, integrated RSA public-key cryptography, and a file-based persistence system.

[![Language](https://img.shields.io/badge/Language-C%2B%2B-blue.svg)](https://isocpp.org/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

---

## 📜 Project Overview

This project is a simulation of a digital wallet service where users can sign up, log in, and manage funds across multiple currencies. All data, including user credentials, currency types, account balances, and transaction logs, is persistently stored in local text files. The system emphasizes security by implementing a custom password hashing algorithm and generating a unique RSA key pair for each user upon registration.

## ✨ Core Features

*   **Multi-Currency Wallet System**:
    *   Manages multiple user accounts with individual balances for each supported currency.
    *   Supports a variety of currencies, defined in a simple configuration file.
    *   Includes a special system account (`Agiotage`) to handle transaction fees and fund sourcing for deposits/withdrawals.

*   **Full Transaction Support**:
    *   **DEPOSIT**: Add funds to a user account (sourced from the Agiotage account).
    *   **WITHDRAW**: Remove funds from a user account (transferred to the Agiotage account).
    *   **TRANSFER**: Securely send funds from one user to another, with transaction fees applied.
    *   **EXCHANGE**: Convert funds from one currency to another, with a dynamic fee structure.
    *   **REPORT**: View a complete history of all transactions for the logged-in user.

*   **Secure User Authentication**:
    *   A full **Sign Up** and **Log In** system.
    *   Passwords are never stored in plaintext; they are secured using a custom-built hash function.

*   **Integrated RSA Cryptography**:
    *   A from-scratch implementation of the RSA algorithm.
    *   Each user is assigned a unique public/private key pair upon registration, which is stored securely.

*   **File-Based Persistence**:
    *   The entire state of the application is saved in `.txt` files. No external databases are required.
    *   This includes user data, currency definitions, account balances, and a system-wide transaction log.

*   **Transaction Logging**:
    *   Every operation (successful or failed) is recorded in `log.txt` with a status code, providing a clear audit trail.

---

## 🛠️ Technology Stack

*   **Language**: C++
*   **Core Libraries**: Standard C++ Libraries (`iostream`, `fstream`, `string`, `vector`, `cmath`).
*   **Database**: Custom file-based system using `.txt` files for data persistence.

---

## 📂 File-Based Database Structure

The application's data is organized across several text files:

*   `users.txt`: Stores user credentials, including username, hashed password, and their public RSA key (`e` and `n`).
*   `currencies.txt`: Defines the names and exchange values of all supported currencies.
*   `log.txt`: A global log of all transactions, timestamps, and their success/failure status.
*   `currencies/[currency_name].txt`: A dedicated file for each currency, storing the balance for every user in that specific currency.

---

## 🚀 How to Compile and Run

#### Prerequisites
*   A C++ compiler, such as `g++`.

#### Steps
1.  **Clone the repository**:
    ```bash
    git clone <your-repository-url>
    cd <project-folder>
    ```
2.  **Compile the source code**:
    Navigate to the source directory and compile the files. If your main file is `main.cpp`, the command would be:
    ```bash
    g++ -o wallet main.cpp  # Add other .cpp files if your project is split
    ```
3.  **Run the application**:
    Execute the compiled binary from your terminal:
    ```bash
    ./wallet
    ```

---

## 🖥️ Usage

1.  Upon running the application, you will be prompted to either **Sign Up** or **Log In**.
2.  **To Sign Up**: Provide a new username and a password. The system will automatically hash your password, generate your RSA keys, and initialize your accounts for all available currencies.
3.  **To Log In**: Enter your existing username and password. The system will verify your credentials against the hashed password on record.
4.  Once logged in, you will be presented with a menu of available commands:

    *   `DEPOSIT <amount> <currency>`
    *   `WITHDRAW <amount> <currency>`
    *   `TRANSFER <recipient_username> <amount> <currency>`
    *   `EXCHANGE <amount> <from_currency> <to_currency>`
    *   `REPORT`
    *   `LOGOUT`

---

## 🔐 Security Implementation Details

*   **Custom Password Hashing**: Passwords are processed by a simple but effective custom hash function that transforms the input into a fixed-length 16-character string. The algorithm uses the formula `(char * 3 + 17) % 26` for character transformation, ensuring that plaintext passwords are never stored.

*   **RSA Encryption**: The project includes a full implementation of the RSA algorithm, including functions for finding GCD, Euler's totient, and key generation. Each user's public key is stored in `users.txt`, demonstrating a foundational understanding of public-key infrastructure.
