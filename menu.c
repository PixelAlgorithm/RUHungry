#include "menu.h"

MenuItem* createMenuItem(char name[], float price, int stock) {
    MenuItem* newNode = (MenuItem*)malloc(sizeof(MenuItem));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    strcpy(newNode->itemName, name);
    newNode->price = price;
    newNode->stockQuantity = stock;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
MenuItem* addItem(MenuItem* root, char name[], float price, int stock) {
    if (root == NULL) {
        return createMenuItem(name, price, stock);
    }

    int compare = strcmp(name, root->itemName);

    if (compare < 0) {
        root->left = addItem(root->left, name, price, stock);
    } else if (compare > 0) {
        root->right = addItem(root->right, name, price, stock);
    } else {
        printf("Item '%s' already exists. Stock updated!\n", name);
        root->stockQuantity += stock;
    }
    return root;
}

MenuItem* findMinNode(MenuItem* node) {
    MenuItem* current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

MenuItem* deleteItem(MenuItem* root, char name[]) {
    if (root == NULL) {
        printf("Item '%s' not found.\n", name);
        return root;
    }

    int compare = strcmp(name, root->itemName);

    if (compare < 0) {
        root->left = deleteItem(root->left, name);
    } else if (compare > 0) {
        root->right = deleteItem(root->right, name);
    } else {
        if (root->left == NULL) {
            MenuItem* temp = root->right;
            printf("Item '%s' deleted successfully.\n", name);
            free(root);
            return temp;
        } else if (root->right == NULL) {
            MenuItem* temp = root->left;
            printf("Item '%s' deleted successfully.\n", name);
            free(root);
            return temp;
        }

        MenuItem* temp = findMinNode(root->right);
        strcpy(root->itemName, temp->itemName);
        root->price = temp->price;
        root->stockQuantity = temp->stockQuantity;
        root->right = deleteItem(root->right, temp->itemName);
    }
    return root;
}

MenuItem* searchItem(MenuItem* root, char name[]) {
    if (root == NULL || strcmp(root->itemName, name) == 0) {
        return root;
    }

    if (strcmp(name, root->itemName) < 0) {
        return searchItem(root->left, name);
    } else {
        return searchItem(root->right, name);
    }
}

void updateStock(MenuItem* root, char name[], int quantitySold) {
    MenuItem* item = searchItem(root, name);
    if (item != NULL) {
        if (item->stockQuantity >= quantitySold) {
            item->stockQuantity -= quantitySold;
            printf("Order processed: %d of %s. Remaining stock: %d\n",
                   quantitySold, name, item->stockQuantity);
        } else {
            printf("Not enough stock for '%s'. Only %d left.\n",
                   name, item->stockQuantity);
        }
    } else {
        printf(" Item '%s' not found in the menu.\n", name);
    }
}

void displayMenu(MenuItem* root) {
    if (root != NULL) {
        displayMenu(root->left);

        printf("Rs.%-7.2f | %-25s | ", root->price, root->itemName);
        if (root->stockQuantity > 0) {
            printf("Stock: %d\n", root->stockQuantity);
        } else {
            printf("[OUT OF STOCK]\n");
        }

        displayMenu(root->right);
    }
}
