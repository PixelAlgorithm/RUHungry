#include "customer.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX 20
int available_queue = MAX;
int available_seats = MAX;
int nextCustomerID = 1;
SeatedCustomer *seatedCustomersHead = NULL;



QUEUE *createNode(int customer_number) {
    QUEUE *temp_node = (QUEUE *)malloc(sizeof(QUEUE));
    if (temp_node == NULL) {
        printf("Memory Allocation failed!\n");
        exit(1);
    }
    temp_node->next = NULL;
    temp_node->customer_number = customer_number;
    return temp_node;
}

void insertQueue(QUEUE **rear, QUEUE **front) {
    if ((*rear) == NULL && (*front) == NULL) {
        (*front) = (*rear) = createNode(1);
        if (available_queue > 0) available_queue--;
        return;
    }
    QUEUE *temp_node = createNode((*rear)->customer_number + 1);
    (*rear)->next = temp_node;
    *rear = (*rear)->next;
    if (available_queue > 0) available_queue--;
}

void deleteQueue(QUEUE **front, QUEUE **rear) {
    if (*front == *rear) {
        free(*front);
        *front = NULL;
        *rear = NULL;
        if (available_queue < MAX) available_queue++;
        return;
    }
    QUEUE *temp_node = *front;
    *front = (*front)->next;
    free(temp_node);
    if (available_queue < MAX) available_queue++;
}

void main_seating_algo(QUEUE **front, QUEUE **rear) {
    if (available_seats > 0) {
        int customerID = nextCustomerID++;
        printf("Seat is free!\n");
        printf("Customer ID assigned: %d\n", customerID);
        addSeatedCustomer(customerID);
        available_seats--;
        return;
    }
    else {
        if (available_queue > 0) {
            printf("Seats not available\n");
            printf("You have been placed in waiting list\n");
            insertQueue(rear, front);
        } else {
            printf("Both seats and queue are full come back sometime later\n");
        }
    }
}

void customer_leaves(QUEUE **front, QUEUE **rear) {
    if ((*front) == NULL && (*rear) == NULL) {
        if (available_seats < MAX) {
            int customerID;
            printf("Enter Customer ID who is leaving: ");
            if (scanf("%d", &customerID) != 1) {
                printf("Invalid input!\n");
                getchar();
                return;
            }
            getchar();
            
            if (isCustomerSeated(customerID)) {
                removeSeatedCustomer(customerID);
                printf("Customer %d left. Seat incremented!\n", customerID);
                available_seats++;
            } else {
                printf("Customer %d is not seated!\n", customerID);
            }
        } else {
            printf("Empty seats, no customer to leave!\n");
        }
    } else {
        int customerID = nextCustomerID++;
        printf("Customer %d from waiting list got seated with ID: %d\n", 
               (*front)->customer_number, customerID);
        addSeatedCustomer(customerID);
        deleteQueue(front, rear);
    }
}

void display() {
    printf("Number of free seats:  %d\n", available_seats);
    printf("Number of free queue:  %d\n", available_queue);
}

void addSeatedCustomer(int customerID) {
    SeatedCustomer *newCustomer = (SeatedCustomer *)malloc(sizeof(SeatedCustomer));
    if (newCustomer == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newCustomer->customerID = customerID;
    newCustomer->next = seatedCustomersHead;
    seatedCustomersHead = newCustomer;
}

void removeSeatedCustomer(int customerID) {
    SeatedCustomer *temp = seatedCustomersHead;
    SeatedCustomer *prev = NULL;
    
    while (temp != NULL && temp->customerID != customerID) {
        prev = temp;
        temp = temp->next;
    }
    
    if (temp == NULL) return;
    
    if (prev == NULL) {
        seatedCustomersHead = temp->next;
    } else {
        prev->next = temp->next;
    }
    free(temp);
}

int isCustomerSeated(int customerID) {
    SeatedCustomer *temp = seatedCustomersHead;
    while (temp != NULL) {
        if (temp->customerID == customerID) {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

void displaySeatedCustomers() {
    if (seatedCustomersHead == NULL) {
        printf("No customers currently seated.\n");
        return;
    }
    
    printf("\n=== Seated Customers ===\n");
    SeatedCustomer *temp = seatedCustomersHead;
    while (temp != NULL) {
        printf("Customer ID: %d\n", temp->customerID);
        temp = temp->next;
    }
    printf("========================\n");
}

