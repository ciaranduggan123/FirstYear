#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100

// Structure to hold a single production log entry
struct dateAndTime 
{
    int day;
    int hour;
    int minute;
};

struct ProductionLog 
{
    int lineCode;
    int batchCode;
    struct dateAndTime batchDateAndTime;
    int productId;
    int issueCode;
    char issueCodeDescription[50];
    char resolutionCodeAndDescription[50];
    int reportingEmployeeId;
    struct ProductionLog *next;
};    

// Hash table structure to store product IDs and their respective issue counts
struct HashTable
{
    int productId;
    int issueCount;
    struct HashTable *next;
};

// Function to initialize the hash table
void initializeHashTable(struct HashTable *hashTable[], int size) 
{
    for (int i = 0; i < size; i++) 
    {
        hashTable[i] = NULL;
    }
}

// Function to insert/update an entry in the hash table
void insertOrUpdate(struct HashTable *hashTable[], int size, int productId) 
{
    int index = productId % size;

    // Search for the productId in the hash table
    struct HashTable *current = hashTable[index];
    while (current != NULL) 
    {
        if (current->productId == productId) 
        {
            // If productId found, update the issue count
            current->issueCount++;
            return;
        }
        current = current->next;
    }

    // If productId not found, create a new entry and insert it into the hash table
    struct HashTable *newEntry = (struct HashTable *)malloc(sizeof(struct HashTable));
    newEntry->productId = productId;
    newEntry->issueCount = 1;
    newEntry->next = hashTable[index];
    hashTable[index] = newEntry;
}

// Function to display the report summarizing the number of issues reported for each product ID
void displayReport(struct HashTable *hashTable[], int size) 
{
    printf("Product ID\t\tIssue Count\n");
    for (int i = 0; i < size; i++) 
    {
        struct HashTable *current = hashTable[i];
        while (current != NULL) 
        {
            printf("%d\t\t\t%d\n", current->productId, current->issueCount);
            current = current->next;
        }
    }
}

int main() {
    // Example production logs
    struct ProductionLog logs[] = 
    {
        {1, 156, {01, 07, 33}, 884, 006, "Smashed Screen", "23A", 01},
        {1, 648, {13, 12, 06}, 920, 356, "Incomplete Data", "71G", 65},
        {1, 993, {30, 18, 47}, 145, 969, "Missing Data", "35F", 78},
        {1, 564, {18, 01, 14}, 445, 748, "Noisy Data", "98C", 63},
        {1, 376, {12, 20, 30}, 222, 589, "Time Consuming Analysis", "65H", 98},
        {1, 984, {19, 07, 45}, 397, 194, "Incomplete Text", "12L", 34},
        {1, 467, {20, 15, 59}, 256, 961, "Battery Missing", "01P", 39},
        {1, 197, {28, 13, 00}, 190, 491, "Broken Screen", "54B", 54},
        {1, 124, {16, 22, 01}, 675, 582, "Noisy Data", "29A", 88},
        {1, 654, {06, 07, 22}, 652, 860, "Missing Data", "64H", 92},
        {1, 410, {03, 02, 46}, 404, 106, "Incomplete Data", "97T", 82},
        {1, 111, {11, 11, 34}, 668, 208, "Loading Error", "60U", 57},

        {2, 327, {03, 07, 33}, 146, 006, "Smashed Screen", "23A", 01},
        {2, 548, {16, 12, 06}, 946, 356, "Incomplete Data", "71G", 65},
        {2, 993, {31, 18, 47}, 375, 969, "Missing Data", "35F", 78},
        {2, 712, {13, 01, 14}, 001, 748, "Noisy Data", "98C", 63},
        {2, 376, {15, 20, 30}, 128, 389, "Time Consuming Analysis", "65H", 98},
        {2, 459, {16, 07, 45}, 154, 194, "Incomplete Text", "12L", 34},
        {2, 467, {22, 15, 59}, 455, 961, "Battery Missing", "01P", 39},
        {2, 197, {29, 13, 00}, 244, 491, "Broken Screen", "54B", 54},
        {2, 278, {14, 22, 01}, 005, 582, "Noisy Data", "29A", 88},
        {2, 654, {04, 07, 22}, 560, 860, "Missing Data", "64H", 92},
        {2, 905, {06, 02, 46}, 230, 106, "Incomplete Data", "97T", 82},
        {2, 111, {14, 11, 34}, 966, 208, "Loading Error", "60U", 57},

        {3, 156, {01, 05, 33}, 122, 006, "Smashed Screen", "23A", 01},
        {3, 648, {13, 12, 06}, 330, 356, "Incomplete Data", "71G", 65},
        {3, 993, {30, 18, 47}, 560, 969, "Missing Data", "35F", 78},
        {3, 239, {18, 01, 14}, 651, 748, "Noisy Data", "98C", 63},
        {3, 376, {12, 25, 30}, 564, 289, "Time Consuming Analysis", "65H", 98},
        {3, 984, {19, 05, 45}, 449, 194, "Incomplete Text", "12L", 34},
        {3, 467, {20, 13, 59}, 340, 961, "Battery Missing", "01P", 39},
        {3, 876, {28, 15, 00}, 348, 491, "Broken Screen", "54B", 54},
        {3, 124, {16, 27, 01}, 294, 582, "Noisy Data", "29A", 88},
        {3, 654, {06, 02, 22}, 654, 860, "Missing Data", "64H", 92},
        {3, 200, {03, 03, 46}, 596, 106, "Incomplete Data", "97T", 82},
        {3, 474, {11, 15, 34}, 590, 208, "Loading Error", "60U", 57},

        {4, 188, {01, 07, 35}, 235, 006, "Smashed Screen", "23A", 01},
        {4, 648, {13, 12, 05}, 498, 356, "Incomplete Data", "71G", 65},
        {4, 005, {30, 18, 45}, 233, 969, "Missing Data", "35F", 78},
        {4, 763, {18, 01, 13}, 445, 748, "Noisy Data", "98C", 63},
        {4, 376, {12, 20, 32}, 550, 989, "Time Consuming Analysis", "65H", 98},
        {4, 984, {19, 07, 47}, 986, 194, "Incomplete Text", "12L", 34},
        {4, 467, {20, 15, 57}, 490, 961, "Battery Missing", "01P", 39},
        {4, 394, {28, 13, 05}, 239, 491, "Broken Screen", "54B", 54},
        {4, 274, {16, 22, 04}, 953, 582, "Noisy Data", "29A", 88},
        {4, 654, {06, 07, 24}, 756, 860, "Missing Data", "64H", 92},
        {4, 890, {03, 02, 48}, 456, 106, "Incomplete Data", "97T", 82},
        {4, 111, {11, 11, 39}, 948, 208, "Loading Error", "60U", 57},
    };

    int n = sizeof(logs) / sizeof(logs[0]);

    // Initialize the hash table
    struct HashTable *hashTable[SIZE];
    initializeHashTable(hashTable, SIZE);

    // Count the occurrences of each product ID
    for (int i = 0; i < n; i++) 
    {
        insertOrUpdate(hashTable, SIZE, logs[i].productId);
    }

    // Display the report summarizing the number of issues reported for each product ID
    displayReport(hashTable, SIZE);

    return 0;
}
