#include<stdio.h>
#include <stdlib.h> 
#include <time.h> 
int InsertionSort(int A[],int n)// Function that takes array and does insertion sort
{
    int ComparisionCount=0; // Variable to count the number of comparision
    int temp,j; // Defining variables
    for(int i=1;i<n;i++) // Looping over array indices
    {
        temp=A[i]; // Storing the value at current index
        j=i-1; // Setting j as 1 less of current index
        if(A[j]<=temp)ComparisionCount++;// If aray to left of i is in increasing order in that case this will be incremented
        while(j >= 0 && A[j] > temp)
        {
            ComparisionCount++;// Incrementing the count
            A[j+1]=A[j]; 
            j--;
        } 
        A[j+1]=temp;
        // By the end of this iteration all elements to left of i will be sorted order
    }
    return ComparisionCount;
}
void Print_Array(int A[],int n)// Function to print array 
{
    for(int i=0;i<n;i++) // Loop for printing the array
    {
        printf("%d ",A[i]);// Print statement
    }
    printf("\n");
}
void inverse_array(int A[],int n) // Function to invert the array
{
    int j=n-1;// End of array
    for(int i=0;i<n/2;i++)// Loop this half of the array
    {
        int temp; //Swapping the elements
        temp=A[i];
        A[i]=A[j];
        A[j]=temp;
        j--;
    }
}
void randomise(int A[],int n) // Function to randomise the elements in the array
{
    srand(time(NULL));
    for(int i=n-1;i>0;i--)
    {
        int randnumber = rand() % (i+1); // Find the random indice and swap them with i
        int temp = A[i];
        A[i]=A[randnumber];
        A[randnumber]=temp;
    } 
}
void Intialise_Array(int array_Inc[], int array_Dec[], int array_Random[], int n,int a,int r)// Function that intialises all the three arrays in the increasing order of GP
{
    array_Inc[0]=a; // First element is a
    array_Dec[0]=a; // First element is a
    array_Random[0]=a; // First element is a
    for(int i=1;i<n;i++)
    {
        array_Inc[i]=r*array_Inc[i-1]; //A[i]=r*A[i-1]
        array_Dec[i]=r*array_Dec[i-1];
        array_Random[i]=r*array_Random[i-1];
    }
}
int main()
{
    int n,a,r;
    int ComparisionCount;
    // Taking input from user
    printf("Please give the value of n : ");
    scanf("%d", &n);
    printf("Please give the value of a : ");
    scanf("%d", &a);
    printf("Please give the value of r : ");
    scanf("%d", &r);
    int array_Inc[n];
    int array_Dec[n];
    int array_Random[n];
    Intialise_Array(array_Inc,array_Dec,array_Random,n,a,r);// Initialising array
    inverse_array(array_Dec,n); // Inverting the array to get elements in decreasing order
    randomise(array_Random,n); // Randomising elements
    Print_Array(array_Inc,n); //Print the array
    ComparisionCount = InsertionSort(array_Inc,n); // Calling insertion sort
    printf("Comparision count in the increasing order array is ");
    printf("%d",ComparisionCount);
    printf("\n");
    Print_Array(array_Dec,n); //Print the array
    ComparisionCount = InsertionSort(array_Dec,n); // Calling insertion sort
    printf("Comparision count in the decreasing order array is ");
    printf("%d",ComparisionCount);
    printf("\n");
    Print_Array(array_Random,n); //Print the array
    ComparisionCount = InsertionSort(array_Random,n); // Calling insertion sort
    printf("Comparision count in the random order array is ");
    printf("%d",ComparisionCount);
    printf("\n");
    return 0;
}