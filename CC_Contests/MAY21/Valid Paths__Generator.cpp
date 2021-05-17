// C++ Implementation for random
// tree generator using Prufer Sequence
#include<bits/stdc++.h>
using namespace std;
 
// Prints edges of tree
// represented by give Prufer code
void printTreeEdges(int prufer[], int m)
{
    int vertices = m + 2;
    int vertex_set[vertices];
 
    // Initialize the array of vertices
    for (int i = 0; i < vertices; i++)
        vertex_set[i] = 0;
 
    // Number of occurrences of vertex in code
    for (int i = 0; i < vertices - 2; i++)
        vertex_set[prufer[i] - 1] += 1;
 
 
    int j = 0;
 
    // Find the smallest label not present in
    // prufer[].
    for (int i = 0; i < vertices - 2; i++)
    {
        for (j = 0; j < vertices; j++)
        {
 
            // If j+1 is not present in prufer set
            if (vertex_set[j] == 0)
            {
 
                // Remove from Prufer set and print
                // pair.
                vertex_set[j] = -1;
                cout << (j + 1) << " "
                                << prufer[i] << "\n";
 
                vertex_set[prufer[i] - 1]--;
 
                break;
            }
        }
    }
 
    j = 0;
 
    // For the last element
    for (int i = 0; i < vertices; i++)
    {
        if (vertex_set[i] == 0 && j == 0)
        {
 
            cout <<  (i + 1) << " ";
            j++;
        }
        else if (vertex_set[i] == 0 && j == 1)
            cout << (i + 1) << "\n";
    }
}
 
// generate random numbers in between l an r
int ran(int l, int r)
{
    return l + (rand() % (r - l + 1));
}
 
// Function to Generate Random Tree
void generateRandomTree(int n)
{
 
    int length = n - 2;
    int arr[length];
 
    // Loop to Generate Random Array
    for (int i = 0; i < length; i++)
    {
        arr[i] = ran(0, length + 1) + 1;
    }
    printTreeEdges(arr, length);
}
 
int rand_int(int l, int r) { static mt19937_64 gen(chrono::steady_clock::now().time_since_epoch().count()); return uniform_int_distribution<int>(l, r)(gen); }

// Driver Code
int main()
{
    srand(time(0));
    int n = rand_int(10, 10);
    cout << 1 << '\n' << n << '\n';
    generateRandomTree(n);
 
    return 0;
}
 