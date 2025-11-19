#ifndef CUSTOMER_H
#define CUSTOMER_H

typedef struct Queue {
    struct Queue *next;     
    int seats;              
    int customer_number;    
} QUEUE;


extern int available_seats;   
extern int available_queue;   


void insertQueue(QUEUE **rear, QUEUE **front);      
void deleteQueue(QUEUE **front, QUEUE **rear);    
void main_seating_algo(QUEUE **front, QUEUE **rear); 
void customer_leaves(QUEUE **front, QUEUE **rear);   
void display();                                    

#endif 
