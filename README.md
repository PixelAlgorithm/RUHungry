# RUHungry - Restaurant Management System

A simple restaurant management system implemented in C that manages customer seating, queuing, and menu ordering using data structures.

## Features

- **Customer Queue Management**: Handles customer arrivals and seating using Queue data structure
- **Seating System**: Manages 20 available seats with waiting list functionality
- **Menu Management**: Binary Search Tree (BST) implementation for menu items
- **Order Processing**: Place orders with automatic stock management
- **Billing System**: Generate itemized bills with total calculation

## Data Structures Used

- **Queue**: For managing customer waiting list (FIFO)
- **Binary Search Tree (BST)**: For efficient menu item storage and retrieval

## Project Structure

```
├── main.c          # Main program with menu interface
├── customer.c      # Customer queue management implementation
├── customer.h      # Customer queue header file
├── menu.c          # Menu BST implementation
└── menu.h          # Menu BST header file
```

## How to Compile and Run

### Using GCC:
```bash
gcc main.c customer.c menu.c -o restaurant
./restaurant
```

### Using CMake (if CMakeLists.txt exists):
```bash
mkdir build
cd build
cmake ..
make
./restaurant
```

## Menu Options

1. **Customer Arrives** - Add customer to seating or waiting queue
2. **Customer Leaves** - Process customer departure and seat next in queue
3. **Show Seating Status** - Display available seats and queue positions
4. **Show Menu** - Display all menu items with prices and stock
5. **Add Menu Item** - Add new item to menu
6. **Delete Menu Item** - Remove item from menu
7. **Place Order (Bill)** - Create order and generate bill
0. **Exit** - Close the program

## Default Menu Items

- Dosa - Rs. 50
- Idli - Rs. 30
- Vada - Rs. 25
- Tea - Rs. 15
- Coffee - Rs. 20
- Fried Rice - Rs. 120
- Veg Biryani - Rs. 140
- Sandwich - Rs. 60

## Capacity

- Maximum Seats: 20
- Maximum Queue Size: 20

## Technologies

- Language: C
- Data Structures: Queue, Binary Search Tree

## Author

DSA Project - Restaurant Management System
