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
    int issueCode;
    char issueCodeDescription[50];
    char resolutionCodeAndDescription[50];
    int reportingEmployeeId;
    struct ProductionLog *next;
};    

// sorting production logs by product ID, issue code, and date/time
int compare(const void *a, const void *b) 
{
    const struct ProductionLog *logA = (const struct ProductionLog *)a;
    const struct ProductionLog *logB = (const struct ProductionLog *)b;

    // First, compare product IDs
    if (logA->productId != logB->productId) 
    {
        return logA->productId - logB->productId;
    }
    // compare issue codes
    else if (logA->issueCode != logB->issueCode) 
    {
        return logA->issueCode - logB->issueCode;
    }
    // compare date and time
    else if (logA->batchDateAndTime.day != logB->batchDateAndTime.day) 
    {
        return logA->batchDateAndTime.day - logB->batchDateAndTime.day;
    } 
    else if (logA->batchDateAndTime.hour != logB->batchDateAndTime.hour) 
    {
        return logA->batchDateAndTime.hour - logB->batchDateAndTime.hour;
    } 
    else 
    {
        return logA->batchDateAndTime.minute - logB->batchDateAndTime.minute;
    }
}

int binary_Search(struct ProductionLog logs[], int n, int productId, int issueCode) 
{
    int left = 0, right = n - 1, result = -1;

    while (left <= right) 
    {
        int mid = left + (right - left) / 2;

        // Compare the product IDs
        if (logs[mid].productId == productId) 
        {
            // If product IDs match, check if issue code matches
            if (logs[mid].issueCode == issueCode) 
            {
                result = mid;
                right = mid - 1; // Scan for earlier occurrences
            } 
            else if (logs[mid].issueCode < issueCode) 
            {
                left = mid + 1;
            } 
            else 
            {
                right = mid - 1;
            }
        } 
        else if (logs[mid].productId < productId) 
        {
            left = mid + 1;
        } 
        else 
        {
            right = mid - 1;
        }
    }

    return result;
}


int main() 
{
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

    // Sort the production logs in order of product ID, issue code, and date/time
    qsort(logs, n, sizeof(struct ProductionLog), compare);

    // Input product ID and issue code to search for
    int FindProductID;
    int FindIssueCode;
    printf("Enter Product ID: ");
    scanf("%d", &FindProductID);
    printf("Enter Issue Code: ");
    scanf("%d", &FindIssueCode);

    // Perform binary search to find the earliest occurrence of the issue code for the given product ID
    int EarliestOccurrenceIndex = binary_Search(logs, n, FindProductID, FindIssueCode);

    if (EarliestOccurrenceIndex != -1) 
    {
        printf("Earliest occurrence of issue code %d for Product ID %d was found\n",
               FindIssueCode, FindProductID);

        // Display date and time of the earliest occurrence
        printf("Date and time of the earliest occurrence: %02d:%02d, Date %02d\n",
               logs[EarliestOccurrenceIndex].batchDateAndTime.hour,
               logs[EarliestOccurrenceIndex].batchDateAndTime.minute,
               logs[EarliestOccurrenceIndex].batchDateAndTime.day);
    } 
    else 
    {
        printf("Issue code %d not found for Product ID %d\n", FindIssueCode, FindProductID);
    }

    return 0;
}