#include <stdio.h>
#include <string.h>
#include "customer.h"
#include "menu.h"

void print_bill(char names[][100], int qtys[], float prices[], int count) {
    float total = 0.0f;
    int i;
    printf("\nItem Name                 Qty   Price      Line Total\n");
    printf("\n");
    for (i = 0; i < count; i++) {
        float line = qtys[i] * prices[i];
        total += line;
        printf("%-25s %4d  Rs.%-8.2f Rs.%-8.2f\n", names[i], qtys[i], prices[i], line);
    }
    printf("\n");
    printf("Grand Total: Rs.%.2f\n\n", total);
}

int main() {
    int choice;
    QUEUE *front = NULL, *rear = NULL;
    MenuItem *root = NULL;
    char name[100];
    float price;
    int stock, qty;
    MenuItem *item;

    root = addItem(root, "Dosa", 50, 10);
    root = addItem(root, "Idli", 30, 20);
    root = addItem(root, "Vada", 25, 15);
    root = addItem(root, "Tea", 15, 40);
    root = addItem(root, "Coffee", 20, 35);
    root = addItem(root, "Fried Rice", 120, 14);
    root = addItem(root, "Veg Biryani", 140, 10);
    root = addItem(root, "Sandwich", 60, 18);

    while (1) {
        printf("\n1. Customer Arrives");
        printf("\n2. Customer Leaves");
        printf("\n3. Show Seating Status");
        printf("\n4. Show Menu");
        printf("\n5. Add Menu Item");
        printf("\n6. Delete Menu Item");
        printf("\n7. Place Order (Bill)");
        printf("\n0. Exit");
        printf("\nEnter your choice: ");
        if (scanf("%d", &choice) != 1) break;
        getchar();

        if (choice == 1) {
            main_seating_algo(&front, &rear);
        } 
        else if (choice == 2) {
            customer_leaves(&front, &rear);
        } 
        else if (choice == 3) {
            display();
        } 
        else if (choice == 4) {
            printf("\n%-10s | %-25s | %s\n", "Price", "Item", "Stock");
            printf("\n");
            displayMenu(root);
        } 
        else if (choice == 5) {
            printf("Enter item name: ");
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = '\0';
            printf("Enter price: ");
            if (scanf("%f", &price) != 1) { getchar(); printf("Invalid price\n"); continue; }
            printf("Enter stock: ");
            if (scanf("%d", &stock) != 1) { getchar(); printf("Invalid stock\n"); continue; }
            getchar();
            root = addItem(root, name, price, stock);
        } 
        else if (choice == 6) {
            printf("Enter item name to delete: ");
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = '\0';
            root = deleteItem(root, name);
        } 
        else if (choice == 7) {
            char bill_names[50][100];
            int  bill_qtys[50];
            float bill_prices[50];
            int bill_count = 0;

            while (1) {
                printf("Enter item name (or 'done' to finish): ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                if (strcmp(name, "done") == 0) break;

                item = searchItem(root, name);
                if (item == NULL) {
                    printf("Item not found\n");
                    continue;
                }

                printf("Enter quantity (available %d): ", item->stockQuantity);
                if (scanf("%d", &qty) != 1) { getchar(); printf("Invalid input\n"); continue; }
                getchar();

                if (qty <= 0 || qty > item->stockQuantity) {
                    printf("Invalid quantity\n");
                    continue;
                }

                updateStock(root, name, qty);
                strcpy(bill_names[bill_count], name);
                bill_qtys[bill_count] = qty;
                bill_prices[bill_count] = item->price;
                bill_count++;
                printf("Added to bill\n");
            }

            if (bill_count > 0) {
                print_bill(bill_names, bill_qtys, bill_prices, bill_count);
            } else {
                printf("No items ordered\n");
            }
        } 
        else if (choice == 0) {
            break;
        } 
        else {
            printf("Invalid choice\n");
        }
    }

    return 0;
}
