# Photobook Application (CSE-105 Assignment)

## Overview
This is an application developed in **C** as part of the **CSE-105 Structured Programming Language** course assignment for the **1st Year 1st Semester B.Sc. (Hons.) Final Examination - 2020** at **Jahangirnagar University, Department of Computer Science and Engineering**. The application, named **Photobook**, simulates a social platform with account creation, login functionality, and additional features like a calculator, number conversion tools, and a Tic Tac Toe game.

The project adheres to the assignment requirements, implementing features such as secure account management, a multifunctional calculator, number base conversions, and a bonus Tic Tac Toe game.

## Features

### 1. Account Management
- **Signup**: Create a new account with:
  - Email address (must be unique).
  - Password (must meet criteria: at least one uppercase letter, one lowercase letter, one digit, one special character from `!@#$%^&*`, and minimum length of 6).
  - Password confirmation (re-typed password must match).
  - Error handling for:
    - Duplicate email addresses.
    - Password mismatch.
    - Invalid password format (with specific error messages for missing criteria).
- **Login**: Log in with email and password.
  - Error handling for:
    - Unregistered email.
    - Incorrect password.
- **Exit**: Option to exit the program.

### 2. Main Menu
After successful login, users can access:
- **Calculator** (press `c`): Perform mathematical operations.
- **GamesZone** (press `g`): Play Tic Tac Toe.
- **Logout** (press `q`): Return to the login interface.
- Invalid key presses prompt an error message.

### 3. Calculator
The calculator supports the following operations:
- Max, Min, Avg, Mean of a set of numbers.
- Basic arithmetic: Addition, Subtraction, Multiplication, Division.
- Factorial and Fibonacci sequence generation.
- **Area Calculator**:
  - Triangle
  - Rectangle
  - Circle
- **Multiplication Table**: Generate for any integer.
- **Sort**: Sort a list of elements.
- **Back** (press `B`): Return to the previous interface.

### 4. Number Conversion
Convert numbers between different bases:
- Binary ↔ Decimal
- Binary ↔ Hexadecimal
- Decimal ↔ Hexadecimal
- Octal ↔ Hexadecimal
- **Back** (press `B`): Return to the previous interface.

### 5. GamesZone (Bonus)
- **Tic Tac Toe (3x3)**:
  - Two-player game with alternating moves (`X` for Player 1, `O` for Player 2).
  - Win condition: Three `X` or `O` in a straight line (row, column, or diagonal).
  - Draw condition: Board filled with no winner.
  - **Back** (press `B`): Return to the previous interface.

## Prerequisites
To compile and run this project, you need:
- A C compiler (e.g., GCC).
- A terminal or command-line interface.
- Basic knowledge of running C programs.

## Installation
1. **Clone the Repository**:
   ```bash
   git clone https://github.com/your-username/your-repository-name.git
