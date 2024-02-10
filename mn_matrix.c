/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partitionColumn(int info[][200], int low, int high) {
    int pivot = info[high][0];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (info[j][0] < pivot) {
            i++;
            //for (int k = 0; k <= 100; k++) {
                swap(&info[i][0], &info[j][0]);
            //}
        }
    }

    for (int k = 0; k <= 100; k++) {
        swap(&info[i + 1][k], &info[high][k]);
    }

    return i + 1;
}

void quicksortColumn(int info[][200], int low, int high) {
    if (low < high) {
        int pivotIndex = partitionColumn(info, low, high);

        // Recursively sort the sub-arrays
        quicksortColumn(info, low, pivotIndex - 1);
        quicksortColumn(info, pivotIndex + 1, high);
    }
}


int partitionRow(int matrix[][200], int low, int high) {
    int pivot = matrix[0][high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (matrix[0][j] < pivot) {
            i++;
            swap(&matrix[0][i], &matrix[0][j]);
        }
    }

    swap(&matrix[0][i + 1], &matrix[0][high]);
    return i + 1;
}

void quicksortRow(int matrix[][200], int low, int high) {
    if (low < high) {
        int pivotIndex = partitionRow(matrix, low, high);

        // Recursively sort the sub-arrays
        quicksortRow(matrix, low, pivotIndex - 1);
        quicksortRow(matrix, pivotIndex + 1, high);
    }
}

int binarySearchColumn(int info[][200], int key) {
    int low = 1;
    int high = 100;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (info[mid][0] == key) {
            return mid; // Element found at index mid
        } else if (info[mid][0] < key) {
            low = mid + 1; // Search in the right half
        } else {
            high = mid - 1; // Search in the left half
        }
    }

    return -1; // Element not found
}

int binarySearchRow(int info[][200], int key) {
    int low = 1;
    int high = 100;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (info[0][mid] == key) {
            return mid; // Element found at index mid
        } else if (info[0][mid] < key) {
            low = mid + 1; // Search in the right half
        } else {
            high = mid - 1; // Search in the left half
        }
    }

    return -1; // Element not found
}

void deleteRow(int info[][200], int rowIndex) {
    if (rowIndex >0 && rowIndex <= 100) {
        for (int i = rowIndex; i < 100 ; i++) {
            for (int j = 0; j <= 100; j++) {
                info[i][j] = info[i + 1][j];
            }
        }
        for (int j = 0; j <= 100; j++) {
            info[100][j] = 0; 
        }
    }
}

void deleteColumn(int info[][200], int columnIndex) {
    if (columnIndex >0 && columnIndex <= 100) {
        for (int i = columnIndex; i < 100 ; i++) {
            for (int j = 0; j <= 100; j++) {
                info[j][i] = info[j][i + 1];
            }
        }
        for (int j = 0; j <= 100; j++) {
            info[j][100] = 0; 
        }
    }
}

void insertInSortedColumn(int info[][200], int element) {
    int i = 100,j,k;

    // Find the position where the element should be inserted in the specified column
    while (i >= 0 && info[i][0] > element) {
       // info[i + 1][0] = info[i][0];
        i--;
    }

    // Shift all 100 down to insert the element in the specified column
    for (j = 100; j > i + 1; j--) {
        for(k=0;k<=100;k++)
            info[j][k] = info[j-1][k];
    }

    // Insert the element at the correct position in the specified column
    info[i + 1][0] = element;
    for(k=1;k<=100;k++){
        info[i+1][k]=0;
    }
}

void insertInSortedRow(int info[][200], int element) {
    int i = 100,j,k;

    // Find the position where the element should be inserted in the specified row
    while (i >= 0 && info[0][i] > element) {
        //info[0][i + 1] = info[0][i];
        i--;
    }

    // Shift all 100 down to insert the element in the specified row
    for (j = 100; j > i + 1; j--) {
        for(k=0;k<=100;k++)
            info[k][j] = info[k][j-1];
    }

    // Insert the element at the correct position in the specified row
    info[0][i + 1] = element;
    for(k=1;k<=100;k++){
        info[k][i + 1]=0;
    }
}

int main() {
    int info[200][200],choice,pcode,pos,i,m_id,pos1,row,column;

    
    for (i = 1; i <= 100; i++) {
        info[i][0] = rand() % 9000 + 1000; // Generates pin codes between 1000 and 9999
        info[0][i] = rand() % 900 + 100; // Generates manufacturer ids between 100 and 999
    }

    quicksortColumn(info, 1, 100);
    quicksortRow(info, 1, 100);

    for(i=0;i<800;i++){
        row=rand() % 100 + 1;
        column=rand() % 100 + 1;
        info[row][column]=1;
    }
    

while(1){
    printf("1.Search for available merchant\n2.Delete pincode\n3.Add pincode\n4.Update merchant info\n5.Delete merchant id\n6.Add merchant id\n7.Display pincodes\n8.Display merchant ids\n9.Exit\nEnter your choice:");
    scanf("%d",&choice);
    switch(choice){
        case 1:printf("Enter the pincode:");
        scanf("%d",&pcode);
        pos = binarySearchColumn(info, pcode);
        if(pos==-1){
            printf("Pincode not found\n\n");
            break;
        }
        printf("Available merchant ids:");
        for(i=1;i<=100;i++){
            if(info[pos][i]==1)
            printf("%d\n\n",info[0][i]);
        }
        break;

        case 2:printf("Enter the pincode:");
        scanf("%d",&pcode);
        pos = binarySearchColumn(info, pcode);
        if(pos==-1){
            printf("Pincode not found\n\n");
            break;
        }
        deleteRow(info, pos);
        printf("Pincode deleted\n\n");
        break;

        case 3:printf("Enter the pincode:");
        scanf("%d",&pcode);
        insertInSortedColumn(info, pcode);
        printf("Pincode added\n\n");
        break;

        case 4:printf("Enter the merchant id:");
        scanf("%d",&m_id);
        pos1 = binarySearchRow(info, m_id);
        if(pos1==-1){
            printf("Merchant id not found\n\n");
            break;
        }
        printf("1.Add service at a pincode\n2.Remove service at a pincode\nEnter your choice:");
        scanf("%d",&choice);
        printf("Enter the pincode:");
        scanf("%d",&pcode);
        pos = binarySearchColumn(info, pcode);
        if(pos==-1){
            printf("Pincode not found\n\n");
            break;
        }
        switch(choice){
            case 1:info[pos][pos1]=1;
            printf("Service added\n\n");
            break;

            case 2:info[pos][pos1]=0;
            printf("Service removed\n\n");
            break;

            default:printf("Wrong choice!\n\n");
        }
        break;

        case 5:printf("Enter the merchant id:");
        scanf("%d",&m_id);
        pos = binarySearchRow(info, m_id);
        if(pos==-1){
            printf("Merchant id not found\n\n");
            break;
        }
        deleteColumn(info, pos);
        printf("Merchant id deleted\n\n");
        break;

        case 6:printf("Enter the merchant id:");
        scanf("%d",&m_id);
        insertInSortedRow(info, m_id);
        printf("Merchant id added\n\n");
        break;

        case 7:printf("Pincodes:\n");
        for(i=1;i<=100;i++)
        printf("%d\t",info[i][0]);
        printf("\n\n");
        break;

        case 8:printf("Merchant ids:\n");
        for(i=1;i<=100;i++)
        printf("%d\t",info[0][i]);
        printf("\n\n");
        break;

        case 9:printf("Exiting program\n");
        exit(0);

        default:printf("Wrong choice!Try again\n\n");

    }
}
    return 0;
}