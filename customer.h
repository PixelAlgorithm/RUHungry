#ifndef CUSTOMER_H
#define CUSTOMER_H

typedef struct Queue {
    struct Queue *next;     
    int seats;              
    int customer_number;    
} QUEUE;

typedef struct SeatedCustomer {
    int customerID;
    struct SeatedCustomer *next;
} SeatedCustomer;

extern int available_seats;   
extern int available_queue;   
extern int nextCustomerID;
extern SeatedCustomer *seatedCustomersHead;

void insertQueue(QUEUE **rear, QUEUE **front);      
void deleteQueue(QUEUE **front, QUEUE **rear);    
void main_seating_algo(QUEUE **front, QUEUE **rear); 
void customer_leaves(QUEUE **front, QUEUE **rear);   
void display();
void addSeatedCustomer(int customerID);
void removeSeatedCustomer(int customerID);
int isCustomerSeated(int customerID);
void displaySeatedCustomers();

#endif 
