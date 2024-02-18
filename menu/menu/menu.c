#include <stdio.h>
#include <stdlib.h>

#define MAX_PRODUCTS 100
#define GST_RATE 0.18

struct Product {
    int id;
    char name[50];
    char description[100];
    int quality;
    float price;
    int quantity;
};

void addProduct(struct Product products[], int *productCount);
void updateProduct(struct Product products[], int productCount);
void orderAndBill(struct Product products[], int productCount);
void generateReports(struct Product products[], int productCount);
void filterByTotal(struct Product products[], int productCount, float minValue);

int main() {
    struct Product products[MAX_PRODUCTS];
    int productCount = 0;
    int choice;

    do {
        // Display menu
        printf("\n=== Product Management System ===\n");
        printf("1. Add Product\n");
        printf("2. Update Product\n");
        printf("3. Order and Bill\n");
        printf("4. Generate Reports\n");
        printf("5. Filter by Total\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addProduct(products, &productCount);
                break;
            case 2:
                updateProduct(products, productCount);
                break;
            case 3:
                orderAndBill(products, productCount);
                break;
            case 4:
                generateReports(products, productCount);
                break;
            case 5:
                {
                    float minValue;
                    printf("Enter minimum total value: ");
                    scanf("%f", &minValue);
                    filterByTotal(products, productCount, minValue);
                }
                break;
            case 0:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 0);

    return 0;
}

void addProduct(struct Product products[], int *productCount) {
    if (*productCount < MAX_PRODUCTS) {
        printf("Enter product details:\n");
        printf("ID: %d\n", *productCount + 1);
        products[*productCount].id = *productCount + 1;

        printf("Name: ");
        scanf("%s", products[*productCount].name);

        printf("Description: ");
        scanf("%s", products[*productCount].description);

        printf("Quality: ");
        scanf("%d", &products[*productCount].quality);

        printf("Price: ");
        scanf("%f", &products[*productCount].price);

        printf("Quantity: ");
        scanf("%d", &products[*productCount].quantity);

        (*productCount)++;
        printf("Product added successfully!\n");
    } else {
        printf("Maximum number of products reached!\n");
    }
}

void updateProduct(struct Product products[], int productCount) {
    int productId;
    printf("Enter the product ID to update: ");
    scanf("%d", &productId);

    for (int i = 0; i < productCount; i++) {
        if (products[i].id == productId) {
            printf("Enter updated details for product ID %d:\n", productId);

            printf("Name: ");
            scanf("%s", products[i].name);

            printf("Description: ");
            scanf("%s", products[i].description);

            printf("Quality: ");
            scanf("%d", &products[i].quality);

            printf("Price: ");
            scanf("%f", &products[i].price);

            printf("Quantity: ");
            scanf("%d", &products[i].quantity);

            printf("Product updated successfully!\n");
            return;
        }
    }

    printf("Product with ID %d not found.\n", productId);
}


void orderAndBill(struct Product products[], int productCount) {
    int orderId, quantity;
    float totalCost = 0;

    printf("Enter order details:\n");
    printf("Order ID: ");
    scanf("%d", &orderId);

    while (1) {
        printf("Enter product ID (0 to finish): ");
        int productId;
        scanf("%d", &productId);

        if (productId == 0) {
            break;
        }

        int index = -1;
        for (int i = 0; i < productCount; i++) {
            if (products[i].id == productId) {
                index = i;
                break;
            }
        }

        if (index != -1) {
            printf("Enter quantity for product %s: ", products[index].name);
            scanf("%d", &quantity);

            if (quantity <= products[index].quantity) {
                totalCost += (products[index].price * quantity);
                products[index].quantity -= quantity;
            } else {
                printf("Insufficient quantity in stock for %s.\n", products[index].name);
            }
        } else {
            printf("Product not found!\n");
        }
    }

    
    totalCost += totalCost * 0.18;

    printf("Total cost for order %d: %.2f\n", orderId, totalCost);
}

void generateReports(struct Product products[], int productCount) {
    printf("\n=== Product Reports ===\n");

    printf("%-5s %-20s %-20s %-10s %-10s %-10s %-15s\n", "ID", "Name", "Description", "Quality", "Price", "Quantity", "Total Cost");
    printf("=================================================================\n");

    for (int i = 0; i < productCount; i++) {
        float totalCost = products[i].price * products[i].quantity;
        printf("%-5d %-20s %-20s %-10d %-10.2f %-10d %-15.2f\n",
               products[i].id, products[i].name, products[i].description,
               products[i].quality, products[i].price, products[i].quantity, totalCost);
    }
}

void filterByTotal(struct Product products[], int productCount, float minValue) {
    printf("\n=== Products with Total Cost Greater than %.2f ===\n", minValue);

    printf("%-5s %-20s %-20s %-10s %-10s %-10s %-15s\n", "ID", "Name", "Description", "Quality", "Price", "Quantity", "Total Cost");
    printf("=================================================================\n");

    for (int i = 0; i < productCount; i++) {
        float totalCost = products[i].price * products[i].quantity;
        if (totalCost > minValue) {
            printf("%-5d %-20s %-20s %-10d %-10.2f %-10d %-15.2f\n",
                   products[i].id, products[i].name, products[i].description,
                   products[i].quality, products[i].price, products[i].quantity, totalCost);
        }
    }
}
