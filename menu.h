#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct MenuItem {
    char itemName[100];
    float price;
    int stockQuantity;
    struct MenuItem *left;
    struct MenuItem *right;
} MenuItem;

MenuItem* createMenuItem(char name[], float price, int stock);
MenuItem* addItem(MenuItem* root, char name[], float price, int stock);
MenuItem* deleteItem(MenuItem* root, char name[]);
MenuItem* searchItem(MenuItem* root, char name[]);
void updateStock(MenuItem* root, char name[], int quantitySold);
void displayMenu(MenuItem* root);
MenuItem* findMinNode(MenuItem* node);

#endif
