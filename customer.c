#include "customer.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX 20
int available_queue = MAX;
int available_seats = MAX;



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
        printf("seat is free\n");
        available_seats--;
        return;
    }
    else {
        if (available_queue > 0) {
            printf("seats not available\n");
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
            printf("No one in waiting list, seat incremented!\n");
            available_seats++;
        } else {
            printf("Empty seats, no customer to leave!\n");
        }
    } else {
        printf("Customer %d from waiting list got seated.\n", (*front)->customer_number);
        deleteQueue(front, rear);
    }
}

void display() {
    printf("Number of free seats:  %d\n", available_seats);
    printf("Number of free queue:  %d\n", available_queue);
}

