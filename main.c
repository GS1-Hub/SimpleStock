#include <stdio.h>

#define MAX_PRODUCTS 100

typedef struct {
    int id;
    char name[50];
    int stock;
    float price;
} Product;

Product warehouse[MAX_PRODUCTS];

char menuOptions() {
    char option;
    printf("\n--- STOCK MANAGEMENT SYSTEM ---\n"); 
    printf("A: Add a Product\n");
    printf("L: list of Products\n");
    printf("E: Exit\n");
    printf("Choose an option: ");
    
    scanf(" %c", &option); 

    return option;
}

void addProduct(Product wareHouse[], int *total)
{
    if(*total < MAX_PRODUCTS)
    {
        printf("\n---Adding Product to Slot %d ---\n", *total);

        wareHouse[*total].id = *total + 1;

        printf("Enter Product Name: ");
        scanf(" %s", &wareHouse[*total].name);
        
        printf("Enter Product Stock: ");
        scanf(" %d", &wareHouse[*total].stock);

        printf("Enter Product price: ");
        scanf(" %f", &wareHouse[*total].price);

        printf("\n Product saved sucessfully\n");
        printf("ID: %d\n", *total*1);
        printf("Name: %s\n", wareHouse[*total].name);
        printf("Stock: %d\n", wareHouse[*total].stock);
        printf("Price: %.2f\n", wareHouse[*total].price);
        printf("--------------------------------\n");

        (*total)++;
    }
    else {
        printf("\nError: WareHouse is full\n");
    }
}

void listProducts(Product warehouse[], int total){
    if(total == 0){
        printf("\nWarehouse is empty\n");
        return;
    }

    printf("\n--- CURRENT INVENTORY ---");
    for (int i = 0; i < total; i++){
        printf("\nSlot %d | ID: %d | Name: %-10s | Stock: %d | Price: $%.2f\n", 
       i, warehouse[i].id, warehouse[i].name, warehouse[i].stock, warehouse[i].price);
    }
    printf("--------------------------\n");
}

int main() {
    int totalProducts = 0;
    char option;
    do {
        option = menuOptions();

        switch (option) {
            case 'A':
            case 'a':
                addProduct(warehouse, &totalProducts);
                break;
            case 'E':
            case 'e':
                printf("\nA Exiting system... GoodBye!\n");
                break;
            case 'L':
            case 'l':
                    listProducts(warehouse, totalProducts);
                    break;
            default:
                printf("\nOption '%c' wrong! Try Again.\n", option);
                break;
        }

    } while (option != 'E' && option != 'e');

    printf("\nExiting system... Press Enter to close.");
    int c;
    while((c = getchar()) != '\n' && c != EOF);
    getchar();

    return 0;
}