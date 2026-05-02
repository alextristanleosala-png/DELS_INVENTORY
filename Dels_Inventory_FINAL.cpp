#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// STRUCTURES

// Product (Array)
typedef struct {
    int id;
    char name[50];
    int quantity;
    float price;
} Product;

Product inventory[MAX];
int count = 0;

// Linked List (Transaction History)
typedef struct Node {
    char action[100];
    struct Node* next;
} Node;

Node* history = NULL;

// Stack (Undo System)
typedef struct Stack {
    Product data;
    int actionType; // 1=ADD, 2=UPDATE, 3=DELETE
    struct Stack* next;
} Stack;

Stack* top = NULL;

// STACK FUNCTIONS 
void push(Product p, int actionType) {
    Stack* temp = (Stack*)malloc(sizeof(Stack));
    temp->data = p;
    temp->actionType = actionType;
    temp->next = top;
    top = temp;
}

Stack* pop() {
    if (top == NULL) return NULL;

    Stack* temp = top;
    top = top->next;
    return temp;
}

// LINKED LIST FUNCTIONS
void addHistory(char action[]) {
    Node* temp = (Node*)malloc(sizeof(Node));
    strcpy(temp->action, action);
    temp->next = history;
    history = temp;
}

void showHistory() {
    Node* temp = history;
    printf("\n--- Transaction History ---\n");
    while (temp != NULL) {
        printf("%s\n", temp->action);
        temp = temp->next;
    }
}

//  SEARCH (LINEAR SEARCH)
int searchProduct(int id) {
    for (int i = 0; i < count; i++) {
        if (inventory[i].id == id)
            return i;
    }
    return -1;
}

//  SORT (BUBBLE SORT) 
void sortInventory() {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (inventory[j].quantity > inventory[j + 1].quantity) {
                Product temp = inventory[j];
                inventory[j] = inventory[j + 1];
                inventory[j + 1] = temp;
            }
        }
    }
    printf("\nInventory sorted by quantity.\n");
}

//CORE FUNCTIONS
void addProduct() {
    if (count >= MAX) {
        printf("Inventory full!\n");
        return;
    }

    Product p;
    printf("\nEnter ID: ");
    scanf("%d", &p.id);

    printf("Enter Name: ");
    scanf(" %[^\n]", p.name);

    printf("Enter Quantity: ");
    scanf("%d", &p.quantity);

    printf("Enter Price: ");
    scanf("%f", &p.price);

    inventory[count++] = p;

    push(p, 1); // ADD

    char log[100];
    sprintf(log, "Added: %s (ID:%d)", p.name, p.id);
    addHistory(log);

    printf("Product added!\n");
}

void viewProducts() {
    printf("\n--- Inventory ---\n");
    for (int i = 0; i < count; i++) {
        printf("ID:%d | %s | Qty:%d | Price:%.2f\n",
               inventory[i].id,
               inventory[i].name,
               inventory[i].quantity,
               inventory[i].price);
    }
}

void updateProduct() {
    int id;
    printf("\nEnter ID to update: ");
    scanf("%d", &id);

    int index = searchProduct(id);

    if (index == -1) {
        printf("Product not found!\n");
        return;
    }

    push(inventory[index], 2); // UPDATE (save old data)

    printf("Enter new quantity: ");
    scanf("%d", &inventory[index].quantity);

    printf("Enter new price: ");
    scanf("%f", &inventory[index].price);

    char log[100];
    sprintf(log, "Updated: %s (ID:%d)", inventory[index].name, id);
    addHistory(log);

    printf("Product updated!\n");
}

void deleteProduct() {
    int id;
    printf("\nEnter ID to delete: ");
    scanf("%d", &id);

    int index = searchProduct(id);

    if (index == -1) {
        printf("Product not found!\n");
        return;
    }

    push(inventory[index], 3); // DELETE

    char log[100];
    sprintf(log, "Deleted: %s (ID:%d)", inventory[index].name, id);
    addHistory(log);

    for (int i = index; i < count - 1; i++) {
        inventory[i] = inventory[i + 1];
    }

    count--;

    printf("Product deleted!\n");
}

void undo() {
    Stack* temp = pop();

    if (temp == NULL) {
        printf("Nothing to undo!\n");
        return;
    }

    if (temp->actionType == 1) {
        count--; // undo ADD
    }
    else if (temp->actionType == 2) {
        int index = searchProduct(temp->data.id);
        if (index != -1)
            inventory[index] = temp->data;
    }
    else if (temp->actionType == 3) {
        inventory[count++] = temp->data;
    }

    addHistory("Undo performed");
    free(temp);

    printf("Undo successful!\n");
}

//  MAIN MENU
int main() {
    int choice;

    do {
        printf("\n=== DEL'S CAFE INVENTORY SYSTEM ===\n");
        printf("1. Add Product\n");
        printf("2. View Products\n");
        printf("3. Update Product\n");
        printf("4. Delete Product\n");
        printf("5. Search Product\n");
        printf("6. Sort Inventory\n");
        printf("7. View History\n");
        printf("8. Undo\n");
        printf("9. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addProduct(); break;
            case 2: viewProducts(); break;
            case 3: updateProduct(); break;
            case 4: deleteProduct(); break;
            case 5: {
                int id;
                printf("Enter ID to search: ");
                scanf("%d", &id);
                int index = searchProduct(id);
                if (index != -1)
                    printf("Found: %s\n", inventory[index].name);
                else
                    printf("Not found!\n");
                break;
            }
            case 6: sortInventory(); break;
            case 7: showHistory(); break;
            case 8: undo(); break;
            case 9: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }

    } while (choice != 9);

    return 0;
}
