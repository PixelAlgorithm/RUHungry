#ifndef ORDER_H
#define ORDER_H

typedef struct OrderItem {
    char itemName[100];
    int quantity;
    float price;
    struct OrderItem *next;
} OrderItem;

typedef struct Order {
    int orderID;
    int customerID;
    OrderItem *items;
    float totalAmount;
    struct Order *next;
} Order;

extern Order *orderHead;
extern int nextOrderID;

Order* createOrder(int customerID);
void addItemToOrder(Order *order, char itemName[], int qty, float price);
void saveOrder(Order *order);
void displayOrder(Order *order);
Order* findOrder(int orderID);
void getPopularItems(int k);

#endif
