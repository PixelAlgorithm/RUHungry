#include <stdio.h>
#include <string.h>
#include "customer.h"
#include "menu.h"
#include "order.h"

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
        printf("\n========== RU HUNGRY MENU ==========");
        printf("\n1. Customer Arrives");
        printf("\n2. Customer Leaves");
        printf("\n3. Show Seating Status");
        printf("\n4. Show Menu");
        printf("\n5. Add Menu Item");
        printf("\n6. Delete Menu Item");
        printf("\n7. Place Order (Bill)");
        printf("\n8. Find Order by ID");
        printf("\n9. Get Popular Items");
        printf("\n10. Show Seated Customers");
        printf("\n0. Exit");
        printf("\n====================================");
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
            int customerID;
            printf("Enter Customer ID: ");
            if (scanf("%d", &customerID) != 1) {
                getchar();
                printf("Invalid Customer ID\n");
                continue;
            }
            getchar();
            
            if (!isCustomerSeated(customerID)) {
                printf("Customer ID %d is not seated. Cannot place order.\n", customerID);
                continue;
            }
            
            Order *order = createOrder(customerID);
            
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
                addItemToOrder(order, name, qty, item->price);
                printf("Added to bill\n");
            }

            if (order->items != NULL) {
                saveOrder(order);
                displayOrder(order);
                printf("Order ID: %02d has been placed successfully!\n", order->orderID);
            } else {
                printf("No items ordered\n");
                free(order);
            }
        }
        else if (choice == 8) {
            int orderID;
            printf("Enter Order ID: ");
            if (scanf("%d", &orderID) != 1) {
                getchar();
                printf("Invalid Order ID\n");
                continue;
            }
            getchar();
            
            Order *foundOrder = findOrder(orderID);
            if (foundOrder != NULL) {
                displayOrder(foundOrder);
            } else {
                printf("Order ID %02d not found!\n", orderID);
            }
        }
        else if (choice == 9) {
            int k;
            printf("Enter number of top items to display: ");
            if (scanf("%d", &k) != 1) {
                getchar();
                printf("Invalid input\n");
                continue;
            }
            getchar();
            
            getPopularItems(k);
        }
        else if (choice == 10) {
            displaySeatedCustomers();
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
