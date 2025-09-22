#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    char issueCode[50];
    char resolutionCodeAndDescription[50];
    int reportingEmployeeId;
    struct ProductionLog *next;
};    

// Merge function for merge sort
void merge(struct ProductionLog arr[], int left, int middle, int right) 
{
    int n1 = middle - left + 1;
    int n2 = right - middle;

    // Create temporary arrays
    struct ProductionLog L[n1], R[n2];

    // Copy data to temporary arrays left[] and right[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];

    for (int j = 0; j < n2; j++)
        R[j] = arr[middle + 1 + j];

    // Merge the temporary arrays back into arr[l..r]
    int i = 0;
    int j = 0;
    int k = left;
    while (i < n1 && j < n2) {
        // Compare line code first
        if (L[i].productId < R[j].productId) 
        {
            arr[k++] = L[i++];
        } 
        else if (L[i].productId > R[j].productId) 
        {
            arr[k++] = R[j++];
        } 
        else 
        {
            // If line codes are equal, compare batch date & time
            if (L[i].batchDateAndTime.day < R[j].batchDateAndTime.day ||
                (L[i].batchDateAndTime.day == R[j].batchDateAndTime.day &&
                 (L[i].batchDateAndTime.hour < R[j].batchDateAndTime.hour ||
                  (L[i].batchDateAndTime.hour == R[j].batchDateAndTime.hour &&
                   L[i].batchDateAndTime.minute < R[j].batchDateAndTime.minute)))) 
            {
                arr[k++] = L[i++];
            } 
            else 
            {
                arr[k++] = R[j++];
            }
        }
    }

    // Copy the remaining elements of L[], if any
    while (i < n1) 
    {
        arr[k++] = L[i++];
    }

    // Copy the remaining elements of R[], if any
    while (j < n2) 
    {
        arr[k++] = R[j++];
    }
}

// Merge sort function
void mergeSort(struct ProductionLog arr[], int l, int r) 
{
    int m;

    if (l < r) 
    {
        // Same as (l+r)/2, but avoids overflow for large l and r
        m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        // Merge the sorted halves
        merge(arr, l, m, r);
    }
}

// Function to prepare report for each line
void prepareReportsByLine(struct ProductionLog logs[], int n) 
{
    // Assuming logs are already sorted by product ID
    int currentLineCode = -1;

    printf("Reports by Line:\n");

    for (int i = 0; i < n; i++) 
    {
        if (logs[i].lineCode != currentLineCode) 
        {
            if (currentLineCode != -1) 
            {
                //printf("\n");
            }
            currentLineCode = logs[i].lineCode;
            printf("Line %d:\n", currentLineCode);
        }
        printf("Product ID: %d  |Issue Code: %s  |Date: %02d  |Time: %02d:%02d\n",
               logs[i].productId, logs[i].issueCode,
               logs[i].batchDateAndTime.day, logs[i].batchDateAndTime.hour, logs[i].batchDateAndTime.minute);
    }
}

int main() 
{
    // Example production logs
    struct ProductionLog logs[] = 
    {
        {1, 156, {01, 07, 33}, 884, "006 Smashed Screen", "23A", 01},
        {1, 648, {13, 12, 06}, 920, "356 Incomplete Data", "71G", 65},
        {1, 993, {30, 18, 47}, 145, "969 Missing Data", "35F", 78},
        {1, 564, {18, 01, 14}, 445, "748 Noisy Data", "98C", 63},
        {1, 376, {12, 20, 30}, 222, "089 Time Consuming Analysis", "65H", 98},
        {1, 984, {19, 07, 45}, 397, "194 Incomplete Text", "12L", 34},
        {1, 467, {20, 15, 59}, 256, "961 Battery Missing", "01P", 39},
        {1, 197, {28, 13, 00}, 190, "491 Broken Screen", "54B", 54},
        {1, 124, {16, 22, 01}, 675, "582 Noisy Data", "29A", 88},
        {1, 654, {06, 07, 22}, 652, "860 Missing Data", "64H", 92},
        {1, 410, {03, 02, 46}, 404, "106 Incomplete Data", "97T", 82},
        {1, 111, {11, 11, 34}, 668, "208 Loading Error", "60U", 57},

        {2, 327, {03, 07, 33}, 146, "006 Smashed Screen", "23A", 01},
        {2, 548, {16, 12, 06}, 946, "356 Incomplete Data", "71G", 65},
        {2, 993, {31, 18, 47}, 375, "969 Missing Data", "35F", 78},
        {2, 712, {13, 01, 14}, 001, "748 Noisy Data", "98C", 63},
        {2, 376, {15, 20, 30}, 128, "089 Time Consuming Analysis", "65H", 98},
        {2, 459, {16, 07, 45}, 154, "194 Incomplete Text", "12L", 34},
        {2, 467, {22, 15, 59}, 455, "961 Battery Missing", "01P", 39},
        {2, 197, {29, 13, 00}, 244, "491 Broken Screen", "54B", 54},
        {2, 278, {14, 22, 01}, 005, "582 Noisy Data", "29A", 88},
        {2, 654, {04, 07, 22}, 560, "860 Missing Data", "64H", 92},
        {2, 905, {06, 02, 46}, 230, "106 Incomplete Data", "97T", 82},
        {2, 111, {14, 11, 34}, 966, "208 Loading Error", "60U", 57},

        {3, 156, {01, 05, 33}, 122, "006 Smashed Screen", "23A", 01},
        {3, 648, {13, 12, 06}, 330, "356 Incomplete Data", "71G", 65},
        {3, 993, {30, 18, 47}, 560, "969 Missing Data", "35F", 78},
        {3, 239, {18, 01, 14}, 651, "748 Noisy Data", "98C", 63},
        {3, 376, {12, 25, 30}, 564, "089 Time Consuming Analysis", "65H", 98},
        {3, 984, {19, 05, 45}, 449, "194 Incomplete Text", "12L", 34},
        {3, 467, {20, 13, 59}, 340, "961 Battery Missing", "01P", 39},
        {3, 876, {28, 15, 00}, 348, "491 Broken Screen", "54B", 54},
        {3, 124, {16, 27, 01}, 294, "582 Noisy Data", "29A", 88},
        {3, 654, {06, 02, 22}, 654, "860 Missing Data", "64H", 92},
        {3, 200, {03, 03, 46}, 596, "106 Incomplete Data", "97T", 82},
        {3, 474, {11, 15, 34}, 590, "208 Loading Error", "60U", 57},

        {4, 188, {01, 07, 35}, 235, "006 Smashed Screen", "23A", 01},
        {4, 648, {13, 12, 05}, 498, "356 Incomplete Data", "71G", 65},
        {4, 005, {30, 18, 45}, 233, "969 Missing Data", "35F", 78},
        {4, 763, {18, 01, 13}, 445, "748 Noisy Data", "98C", 63},
        {4, 376, {12, 20, 32}, 550, "089 Time Consuming Analysis", "65H", 98},
        {4, 984, {19, 07, 47}, 986, "194 Incomplete Text", "12L", 34},
        {4, 467, {20, 15, 57}, 490, "961 Battery Missing", "01P", 39},
        {4, 394, {28, 13, 05}, 239, "491 Broken Screen", "54B", 54},
        {4, 274, {16, 22, 04}, 953, "582 Noisy Data", "29A", 88},
        {4, 654, {06, 07, 24}, 756, "860 Missing Data", "64H", 92},
        {4, 890, {03, 02, 48}, 456, "106 Incomplete Data", "97T", 82},
        {4, 111, {11, 11, 39}, 948, "208 Loading Error", "60U", 57},
    };

    int n = sizeof(logs) / sizeof(logs[0]);

    // Sort the production logs by product ID
    mergeSort(logs, 0, n - 1);

    // Prepare report for each line
    prepareReportsByLine(logs, n);

    return 0;
}