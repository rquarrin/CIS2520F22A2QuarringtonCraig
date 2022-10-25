/******************************************************************************

CIS*2520 F22
Project: Assignment 2 part 1
Date: October 24th, 2022
Name: Rhiana Quarrington Craig
ID: 1106407

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Car {
    int mileage;
    int returnDate;
    char plateNum[7];
    struct Car *next;
};

void readFile(struct Car *, char[] );
void sortList(struct Car *, char[] );
void newRented(struct Car *, struct Car *, int );
void newAvailable(struct Car *, char[] , int );
void newRepair(struct Car *, char[] , int );
long priceCalc(int, int);

int main() {
    struct Car *headRented = NULL;
    char fileRented[] = "rented.txt";
    readFile(headRented, fileRented);
    sortList(headRented, "rented");
    
    struct Car *headAvailable = NULL;
    char fileAvailable[] = "availableForRent.txt";
    readFile(headAvailable, fileAvailable);
    sortList(headAvailable, "available");
    
    struct Car *headRepair = NULL;
    char fileRepair[] = "inRepair.txt";
    readFile(headRepair, fileRepair);
    sortList(headRepair, "repair");
    
    int codeNum = 0;
    char plateNum[7];
    int mileage;
    int returnDate;
    
    printf("Code 1: add a new car to the available-for-rent list\n");
    printf("Code 2: add a returned car to the available-for-rent list\n"); 
    printf("Code 3: add a returned car to the repair list\n"); 
    printf("Code 4: transfer a car from the repair list to the available-for-rent list\n"); 
    printf("Code 5: rent the first available car\n"); 
    printf("Code 6: print all the lists\n"); 
    printf("Code 7: quit\n"); 
    
    while(codeNum == 0) {
        printf("Please enter a code number : ");
        scanf("%d", &codeNum);
        
        if(codeNum < 1 || codeNum > 7) {
            printf("Error: invalid number\n");
            codeNum = 0;
        }
    }
    
    if(codeNum == 1 || codeNum == 2 || codeNum == 3 || codeNum == 4) {
        printf("Please enter the plate number : ");
        scanf("%s", plateNum);
    }
    
    if(codeNum == 1 || codeNum == 2 || codeNum == 3 || codeNum == 4 || codeNum == 5) {
        printf("Please enter the mileage : ");
        scanf("%d", &mileage);
    }
    
    if(codeNum == 5) {
        printf("Please enter the return date (YYMMDD) : ");
        scanf("%d", &returnDate);
    }
    
    char temp[7];
    struct Car *previous = NULL;
    struct Car *current = NULL;
    long price = 0;
    long totalIncome = 0;
    FILE *myfile;
    
    switch (codeNum) {
        case 1:
            newAvailable(headAvailable, plateNum, mileage);
            printf("%s has been added to the available-for-rent list.", plateNum);
            break;
        case 2:
            //taking the car off of the rented list.
            strcpy(temp, headRented -> plateNum);
            if (temp == plateNum) {
                headRented = headRented -> next;
                newAvailable(headAvailable, plateNum, mileage);
                printf("%s has been moved from the rented list to the available-for-rent list.", plateNum);
                break;
            }
            else {
                previous = headRented;
                current = headRented -> next;
                strcpy(temp, current -> plateNum);
                while(temp != plateNum) {
                    previous = current;
                    current = current -> next;
                    strcpy(temp, current -> plateNum);
                        if(current == NULL) {
                            printf("Error: inputed plate number cannot be found");
                            break;
                        }
                }
                //finding the price and adding it to the total income.
                price = priceCalc(mileage, current -> mileage);
                printf("The cost is %.2ld", price);
                totalIncome += price;
                previous -> next = current -> next;
                //adding the car onto the available list.
                newAvailable(headAvailable, plateNum, mileage);
            }
            printf("%s has been moved from the rented list to the available-for-rent list.", plateNum);
            break;
        case 3:
            //adding the car to the repair list.
            newRepair(headRepair, plateNum, mileage);
            //taking the car off of the rented list.
            strcpy(temp, headRented -> plateNum);
            if (temp == plateNum) {
                headRented = headRented -> next;
                printf("%s has been moved from the rented list to the in-repair list.", plateNum);
                break;
            }
            else {
                previous = headRented;
                current = headRented -> next;
                strcpy(temp, current -> plateNum);
                while(temp != plateNum) {
                    previous = current;
                    current = current -> next;
                    strcpy(temp, current -> plateNum);
                    if(current == NULL) {
                        printf("Error: inputed plate number cannot be found");
                        break;
                    }
                }
                //finding the price and adding it to the total income.
                price = priceCalc(mileage, current -> mileage);
                printf("The cost is %.2ld", price);
                totalIncome += price;
                previous -> next = current -> next;
            }
            printf("%s has been moved from the rented list to the in-repair list.", plateNum);
            break;
        case 4:
            //adding the car to the available list.
            newAvailable(headAvailable, plateNum, mileage);
            //taking the car off of the repair list.
            strcpy(temp, headRepair -> plateNum);
            if (temp == plateNum) {
                headRepair = headRepair -> next;
            printf("%s has been moved from the in-repair list to the available-for-rent list.", plateNum);
                break;
            }
            else {
                previous = headRepair;
                current = headRepair -> next;
                strcpy(temp, current -> plateNum);
                while(temp != plateNum) {
                    previous = current;
                    current = current -> next;
                    strcpy(temp, current -> plateNum);
                    if(current == NULL) {
                        printf("Error: inputed plate number cannot be found");
                        break;
                    }
                }
                previous -> next = current -> next;
            }
            printf("%s has been moved from the in-repair list to the available-for-rent list.", plateNum);
            break;
        case 5:
            //adding the car to the rented list.
            newRented(headRented, headAvailable, returnDate);
            printf("%s has been moved from the available-for-rent list to the rented list.", headAvailable -> plateNum);
            //taking the first car off of the available list.
            headAvailable = headAvailable -> next;
            break;
        case 6:
            //printing the lists.
            current = headRented;
            while(current != NULL) {
                printf("%s\n", current -> plateNum);
                printf("%d\n", current -> mileage);
                printf("%d\n\n", current -> returnDate);
                current = current -> next;
            }
            current = headAvailable;
            while(current != NULL) {
                printf("%s\n", current -> plateNum);
                printf("%d\n\n", current -> mileage);
                current = current -> next;
            }
            current = headRepair;
            while(current != NULL) {
                printf("%s\n", current -> plateNum);
                printf("%d\n\n", current -> mileage);
                current = current -> next;
            }
            break;
        case 7:
            //creating new files with the lists.
            myfile = fopen("rented.txt", "w+");
            current = headRented;
            while(current != NULL) {
                fprintf(myfile, "%s\n", current -> plateNum);
                fprintf(myfile, "%d\n", current -> mileage);
                fprintf(myfile, "%d\n", current -> returnDate);
                fprintf(myfile, "\n");
                current = current -> next;
            }
            fclose(myfile);
            myfile = fopen("availableForRent.txt", "w+");
            current = headAvailable;
            while(current != NULL) {
                fprintf(myfile, "%s\n", current -> plateNum);
                fprintf(myfile, "%d\n", current -> mileage);
                fprintf(myfile, "%d\n", current -> returnDate);
                fprintf(myfile, "\n");
                current = current -> next;
            }
            fclose(myfile);
            myfile = fopen("inRepair.txt", "w+");
            current = headRepair;
            while(current != NULL) {
                fprintf(myfile, "%s\n", current -> plateNum);
                fprintf(myfile, "%d\n", current -> mileage);
                fprintf(myfile, "%d\n", current -> returnDate);
                fprintf(myfile, "\n");
                current = current -> next;
            }
            fclose(myfile);
            
            printf("The total income is: $%.2ld", totalIncome);
            break;
    }
    
    return 0;
}

void readFile(struct Car *head, char fileName[]) {
    
    struct Car *node = NULL;
    struct Car *temp = NULL;
    struct Car *tail = NULL;
    struct Car *previous = NULL;
    struct Car *current = NULL;    
    
    char mystring[7];
    int mynum = 0;
    
    printf("%s:\n", fileName);
    
    FILE *myfile;

    myfile = fopen(fileName, "r");
    

    if (myfile != NULL) {
        node = (struct Car *) malloc(sizeof(struct Car));
        fscanf(myfile, "%s", mystring);
        printf("1 : %s\n", mystring );
        strcpy(node -> plateNum, mystring);
        fscanf(myfile, "%d", &mynum);
        printf("2 : %d\n", mynum );
        node -> mileage = mynum;
        fscanf(myfile, "%d", &mynum);
        printf("3 : %d\n", mynum );
        node -> returnDate = mynum;
        temp = node;
        head = node;
        tail = node;
        
        while(fgetc(myfile) != EOF) {
            node = (struct Car *) malloc(sizeof(struct Car));
            fscanf(myfile, "%s", mystring);
            printf("1 : %s\n", mystring );
            strcpy(node -> plateNum, mystring);
            fscanf(myfile, "%d", &mynum);
            printf("2 : %d\n", mynum );
            node -> mileage = mynum;
            fscanf(myfile, "%d", &mynum);
            printf("3 : %d\n", mynum );
            node -> returnDate = mynum;
            tail -> next = node;
            temp -> next = node;
            temp = temp -> next;
        }
        
        previous = head;
        current = head -> next;
        printf("Previous1: %s\n", previous -> plateNum);
        printf("Current1: %s\n", current -> plateNum);
        while(previous->next != NULL) {
            printf("Previous: %s\n", previous -> plateNum);
            printf("Current: %s\n", current -> plateNum);
            if(previous -> plateNum == current -> plateNum) {
                previous -> next = current -> next;
                printf("Deleted: %s\n", previous -> plateNum);
            }
            else {
                previous = previous -> next;
                current = current -> next;
            }
        }
        
        printf("----------------------------\n");
        node -> next = NULL;
        fclose(myfile);
    }
    else printf("Unable to open file\n");
    
    return;
}

void sortList(struct Car *head, char list[]) {
    
    struct Car *current = head, *index = NULL;
    int holding = 0;
    
    if(head == NULL) {
        return;
    }
    else {
        while(current != NULL) {
            index = current -> next;
            
            while (index != NULL) {
                if(list == "rented") {
                    if(current -> returnDate < 221022) {
                        if((current -> returnDate + 221022) > index -> returnDate) {
                            holding = current -> returnDate;
                            current -> returnDate = index -> returnDate;
                            index -> returnDate = holding;
                        }
                    }
                    else if(current -> returnDate > index -> returnDate) {
                        holding = current -> returnDate;
                        current -> returnDate = index -> returnDate;
                        index -> returnDate = holding;
                    }
            
                }
                else {
                    if(current -> mileage > index -> mileage) {
                        holding = current -> mileage;
                        current -> mileage = index -> mileage;
                        index -> mileage = holding;
                    }
            
                }
                index = index -> next;
            }
            current = current -> next;
        }
    }
    
    return;
}

void newRented(struct Car *headRented, struct Car *headAvailable, int date) {
    
    struct Car *node = NULL;
    node = (struct Car *) malloc(sizeof(struct Car));
    strcpy(node -> plateNum, headAvailable -> plateNum);
    node -> mileage = headAvailable -> mileage;
    node -> returnDate = headAvailable -> returnDate;
    node -> next = headRented;
    headAvailable = headAvailable -> next;
    headRented = node;
    sortList(headRented, "rented");
    
    return;
}

void newAvailable(struct Car *head, char plateNum[], int mileage) {
    
    struct Car *node = NULL;
    node = (struct Car *) malloc(sizeof(struct Car));
    strcpy(node -> plateNum, plateNum);
    node -> mileage = mileage;
    node -> returnDate = 0;
    node -> next = head;
    head = node;
    sortList(head, "available");
    
    return;
}

void newRepair(struct Car *head, char plateNum[], int mileage) {
    
    struct Car *node = NULL;
    node = (struct Car *) malloc(sizeof(struct Car));
    strcpy(node -> plateNum, plateNum);
    node -> mileage = mileage;
    node -> returnDate = 0;
    node -> next = head;
    head = node;
    sortList(head, "repair");
    
    return;
}

long priceCalc(int mileage1, int mileage2) {
    int distance = mileage2 - mileage2;
    long price = 80.00;
    
    if(distance > 200) {
        price = price + ((distance - 200) * 0.15);
    }
    
    return price;
}






