#include "order.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Order *orderHead=NULL;
int nextOrderID=1;

Order* createOrder(int customerID) {
    Order *newOrder=(Order *)malloc(sizeof(Order));
    if (newOrder==NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newOrder->orderID=nextOrderID++;
    newOrder->customerID=customerID;
    newOrder->items=NULL;
    newOrder->totalAmount=0.0;
    newOrder->next=NULL;
    return newOrder;
}

void addItemToOrder(Order *order, char itemName[], int qty, float price) {
    OrderItem *newItem=(OrderItem *)malloc(sizeof(OrderItem));
    if (newItem==NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    strcpy(newItem->itemName, itemName);
    newItem->quantity=qty;
    newItem->price=price;
    newItem->next=NULL;

    if (order->items==NULL) {
        order->items=newItem;
    } else {
        OrderItem *temp=order->items;
        while (temp->next!=NULL) {
            temp=temp->next;
        }
        temp->next=newItem;
    }
    order->totalAmount+=(qty * price);
}

void saveOrder(Order *order) {
    if (orderHead==NULL) {
        orderHead=order;
    } else {
        Order *temp=orderHead;
        while (temp->next!=NULL) {
            temp=temp->next;
        }
        temp->next=order;
    }
}

void displayOrder(Order *order) {
    printf("\n========== ORDER RECEIPT ==========\n");
    printf("Order ID: %02d\n", order->orderID);
    printf("Customer ID: %d\n", order->customerID);
    printf("===================================\n");
    printf("Item Name                 Qty   Price      Line Total\n");
    printf("-----------------------------------\n");
    
    OrderItem *item=order->items;
    while (item!=NULL) {
        float lineTotal=item->quantity * item->price;
        printf("%-25s %4d  Rs.%-8.2f Rs.%-8.2f\n", 
               item->itemName, item->quantity, item->price, lineTotal);
        item=item->next;
    }
    
    printf("===================================\n");
    printf("Grand Total: Rs.%.2f\n", order->totalAmount);
    printf("===================================\n\n");
}

Order* findOrder(int orderID) {
    Order *temp=orderHead;
    while (temp!=NULL) {
        if (temp->orderID==orderID) {
            return temp;
        }
        temp=temp->next;
    }
    return NULL;
}

void getPopularItems(int k) {
    if (orderHead==NULL) {
        printf("No orders placed yet!\n");
        return;
    }

    typedef struct ItemCount {
        char itemName[100];
        int count;
    } ItemCount;

    ItemCount items[100];
    int itemCount=0;
    int i, j;

    Order *order=orderHead;
    while (order!=NULL) {
        OrderItem *orderItem=order->items;
        while (orderItem!=NULL) {
            int found=0;
            for (i=0; i<itemCount; i++) {
                if (strcmp(items[i].itemName, orderItem->itemName)==0) {
                    items[i].count+=orderItem->quantity;
                    found=1;
                    break;
                }
            }
            if (!found) {
                strcpy(items[itemCount].itemName, orderItem->itemName);
                items[itemCount].count=orderItem->quantity;
                itemCount++;
            }
            orderItem=orderItem->next;
        }
        order=order->next;
    }

    for (i=1; i<itemCount; i++) {
        ItemCount key=items[i];
    
        for (j=i - 1; j>=0 && items[j].count<key.count; j--) {
            items[j + 1]=items[j];
        }
        items[j + 1]=key;
    }

    printf("\n========== TOP %d POPULAR ITEMS ==========\n", k);
    int limit=(k<itemCount) ? k : itemCount;
    for (i=0; i<limit; i++) {
        printf("%d. %-25s - Ordered %d times\n", i + 1, items[i].itemName, items[i].count);
    }
    printf("==========================================\n\n");
}
