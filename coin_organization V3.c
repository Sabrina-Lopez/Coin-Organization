#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxLetters 21

typedef struct customerInfo* customerInfo; //struct to hold each customer's name and payment
int calculateUnits(int tokens, int bills, int tokenExchangeRate, int billExchangeRate); //convert the tokens and bills to units
void merge(long long int* units, int numCustomers); //mergesort to organize the units from least to greatest

typedef struct customerInfo {
    char** name; //customer's name
    long long int* payment; //customer's payment in units

} *customerInfo;

int calculateUnits(int tokens, int bills, int tokenExchangeRate, int billExchangeRate) {
    long long int units;

    units = (tokens * billExchangeRate) + (bills * tokenExchangeRate); //conversion from tokens and bills to units

    return units;
}

void merge(long long int* units, int numCustomers) {
    struct customerInfo* customerInfo;
    int i; //looping variable

    if (numCustomers <= 1) { //base case
        return;              //if there's only one customer or only one customer left to sort, then the mergesort is done
    }

    int mid = numCustomers / 2; //middle value of number of customers
    merge(units, mid); //recursive call to organize the former half of the customers
    merge(units + mid, numCustomers - mid); //recursive call to organize the latter half of the customers

    long long int* temp; //hold the organized units from least to greatest
    int fptr = 0;
    int bptr = mid;

    temp = (long long int*) calloc(numCustomers, sizeof(long long int)); //allocated memory to make space for units values to be organized in temp

    for (i = 0; i < numCustomers; i++) {
        if (fptr < mid && bptr < numCustomers) {
            if (units[fptr] < units[bptr]) { //if a units value is less than another, place former units value into temp array at index i
                temp[i] = units[fptr];
                fptr++;
            }
            else {
                temp[i] = units[bptr]; //if not, place the latter units value into the temp array at index i
                bptr++;
            }
        }
        else if (fptr < mid) {
            temp[i] = units[fptr];
            fptr++;
        }
        else {
            temp[i] = units[bptr];
            bptr++;
        }
    }

    for (i = 0; i < numCustomers; i++) { //merge the two sorted halves into one array
        units[i] = temp[i];
    }

    free(temp); //free allocated memory made for temp
}

int main() {
    int numCustomers, i, j, k; //number of customers; looping variables
    int tokenExchangeRate, billExchangeRate; //take in the exchange rate for both tokens and bills

    scanf("%d", &numCustomers); //read in the number of customers

    int tokens[numCustomers], bills[numCustomers]; //hold the customers' payments in tokens and bills
    long long int units[numCustomers]; //hold the customers' payments in units aka converted tokens and bills

    struct customerInfo* customerInfo = calloc(numCustomers, sizeof(*customerInfo)); //allocated memory for the struct to hold information for multiple customers
    customerInfo->name = (char**) calloc(numCustomers, sizeof(char*)); //allocated memory to hold the customers' names

    for(i = 0; i < numCustomers; i++) {
        customerInfo->name[i] = (char*) calloc(maxLetters, sizeof(char)); //allocated memory to hold the customers' names
        scanf("%s", customerInfo->name[i]); //read in customers' names and put them into the struct

        scanf("%d %d", &tokens[i], &bills[i]); //read in the customers' payments in tokens and bills
    }

    scanf("%d %d", &tokenExchangeRate, &billExchangeRate); //read in the exchange rate of tokens and bills

    customerInfo->payment = (long long int*) calloc(numCustomers, sizeof(long long int)); //make space to hold the payments after the tokens and bills have been converted to units

    for(i = 0; i < numCustomers; i++) {
        units[i] = calculateUnits(tokens[i], bills[i], tokenExchangeRate, billExchangeRate); //convert the tokens and bills to units
        customerInfo->payment[i] = units[i]; //store the units into the struct
    }

    merge(units, numCustomers); //sort the units from least to greatest

    printf("\n");

    for(i = numCustomers - 1; i >= 0; i--) { //since the units are least to greatest, need to go backwards to get greatest to least
        for(j = 0; j < numCustomers; j++) {
            if(units[i] == customerInfo->payment[j]) { //if the index of said unit finds it's original index and
                if(units[i + 1] == customerInfo->payment[j]) {
                    if(k == 0) { //the name isn't repeating
                        printf("%s\n", customerInfo->name[j]);
                        k++;
                    }
                }
                else {
                    printf("%s\n", customerInfo->name[j]); //the name at said index should be printed
                }
            }
        }
    }

    printf("\n");

    for(i = 0; i < numCustomers; i++) { //free allocated memory made for the struct and its elements
        free(customerInfo->name[i]);
    }

    free(customerInfo->name);
    free(customerInfo->payment);
    free(customerInfo);

    return 0;
}
