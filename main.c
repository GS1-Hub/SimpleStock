#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTS 100

typedef struct {
    int id;
    char name[50];
    int stock;
    float price;
} Product;

Product warehouse[MAX_PRODUCTS];

char menuOptions() {
    int option;
    printf("\n--- STOCK MANAGEMENT SYSTEM ---\n"); 
    printf("1: Add a Product\n");
    printf("2: list of Products\n");
    printf("3: Search Product\n");
    printf("4: Save Product File\n");
    printf("5: Load Product File\n");
    printf("0: Exit\n");
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

void searchProduct(Product warehouse[], int total){
    int searchId;
    int found = 0;

    printf("\nEnter ID to search: ");
    if (scanf("%d", &searchId) != 1) {
        // This handles it if the user accidentally types a letter instead of a number
        while (getchar() != '\n'); 
        printf("Invalid ID format!\n");
        return;
    }
    while (getchar() != '\n');

    for (int i = 0; i < total; i++){
        if(warehouse[i].id == searchId){
            printf("\nProduct Found!");
            printf("\n Name: %s | Stock: %d | Price: %.2f \n", warehouse[i].name, warehouse[i].stock, warehouse[i].price);
            found = 1;
            break;
        }

        if(!found){
            printf("\nProduct with ID: %d not Found.\n", searchId);
        }
    }
}

void saveFile(Product warehouse[], int total){
    char fullPath[64];
    char saveName[54];
    int searchId = 0;
    int found = 0;
    listProducts(warehouse,total);
    printf("Choose a product ID to save");

    printf("\nEnter ID to search: ");
    if (scanf("%d", &searchId) != 1) {
        // This handles it if the user accidentally types a letter instead of a number
        while (getchar() != '\n'); 
        printf("Invalid ID format!\n");
        return;
    }
    while (getchar() != '\n');

    for (int i = 0; i < total; i++){
        if(warehouse[i].id == searchId){
            strcpy(saveName, warehouse[i].name);
            found = 1;
            strcat(saveName, ".dat");

            //save the .bat on foder "Products"
            strcpy(fullPath, "Products/");
            strcat(fullPath, saveName);

            FILE *fp = fopen(fullPath, "wb");

             if(fp == NULL) {
                printf("Error opening file!\n");
                return;
            }
            fwrite(&warehouse[i], sizeof(Product), 1, fp);
            fclose(fp);
            printf("\nProduct saved to %s successfully!\n", fullPath);

            break;
        }
    }
    if(!found){
            printf("\nProduct with ID: %d not Found.\n", searchId);
        }
}
void loadProductFile(Product warehouse[], int *total){
    char loadName[50];
    char fullPath[64];

    printf("Enter Product name to load: ");
    scanf("%s", loadName);

    strcpy(fullPath, "Products/");
    strcat(fullPath, loadName);
    strcat(fullPath, ".dat");

    FILE *fp = fopen(fullPath, "rb");

     if(fp == NULL){
        printf("Error: file not found!\n");
        return;
    }

    fread(&warehouse[*total], sizeof(Product), 1, fp); 
    warehouse[*total].id = *total + 1;
    fclose(fp);
    (*total)++;
    printf("Product loaded successfully!\n");
}

int main() {
    int totalProducts = 0;
    int option;
    do {
        option = menuOptions();

        switch (option) {
            case '1':
                addProduct(warehouse, &totalProducts);
                break;
            case '2':
                    listProducts(warehouse, totalProducts);
                    break;
            case '3':
                searchProduct(warehouse, totalProducts);
                break;
            case '4': 
                saveFile(warehouse, totalProducts);
                break;
            case '5': 
                loadProductFile(warehouse, &totalProducts);
                break;
            case '0':
                printf("\nExiting system... GoodBye!\n");
                break;
            default:
                printf("\nOption '%c' wrong! Try Again.\n", option);
                break;
        }

    } while (option != '0');

    printf("\nExiting system... Press Enter to close.");
    int c;
    while((c = getchar()) != '\n' && c != EOF);
    getchar();

    return 0;
}