#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
using namespace std;

ofstream dataFile("sort_results.csv");

int heap(int arr[], int n, int i)
{
    int numcomp = 0;
    int minvl = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n)
    {
        numcomp++;
        if (arr[l] < arr[minvl])
        {
            minvl = l;
        }
    }
    if (r < n)
    {
        numcomp++;
        if (arr[r] < arr[minvl])
        {
            minvl = r;
        }
    }
    if (minvl != i)
    {
        swap(arr[i], arr[minvl]);
        numcomp += heap(arr, n, minvl);
    }
    return numcomp;
}

int heapsocount(int arr[], int n)
{
    int numcomp = 0;
    for (int x = (n - 2) / 2; x >= 0; x--)
    {
        numcomp += heap(arr, n, x);
    }
    for (int x = n - 1; x > 0; x--)
    {
        swap(arr[0], arr[x]);
        numcomp += heap(arr, x, 0);
    }
    return numcomp;
}

int bubblcount(int ar[], int n)
{
    int numcomp = 0;
    bool swapcurs;
    for (int i = 0; i < n - 1; i++)
    {
        swapcurs = false;
        for (int x = 0; x < n - i - 1; x++)
        {
            if (ar[x] > ar[x+1])
            {
                swap(ar[x], ar[x+1]);
                swapcurs = true;
            }
            numcomp++;
        }
        if (!swapcurs)
        {
            break;
        }
    }
    return numcomp;
}

int selectioncount(int ar[], int n)
{
    int numcomp = 0;
    int min;
    for (int i = 0; i < n - 1; i++)
    {
        min = i;
        for (int j = i + 1; j < n; j++)
        {
            if (ar[j] < ar[min])
            {
                min = j;
            }
            numcomp++;
        }
        swap(ar[i], ar[min]);
    }
    return numcomp;
}

int insertsocount(int ar[], int n)
{
    int s = 0;
    int numcomp = 0;
    
    for (int i = 1; i < n; i++)
    {
        s = ar[i];
        for (int j = i - 1; j > -1; j--)
        {
            numcomp++;
            if (s < ar[j])
            {
                swap(ar[j], ar[j+1]);
            }
            else
            {
                break;
            }
        }
    }
    return numcomp;
}

void reset(int te[], int ar[], int z )
{
    for (int x = 0; x < z; x++)
    {
        te[x] = ar[x];
    }
}

void pTable(int n, string artype, string sotype, int rt, double extime)
{
    cout << left << setw(20) << n << left << setw(20) << artype << left << setw(20) << sotype << left << setw(25) << rt << left << setw(20) << extime << "\n";
}

void exsorts(int te[], int ar[], int x, string artype, string soalg)
{
    reset(te, ar, x);
    auto start = chrono::high_resolution_clock::now();
    int st;
    if (soalg == "Heap")
    {
        st =  heapsocount(te, x);
    }
    else if (soalg == "Bubble")
    {
        st = bubblcount(te, x);
    }
    else if (soalg == "Selection")
    {
        st =  selectioncount(te, x);
    }
    else
    {
        st = insertsocount(te, x);
    }
    auto end = chrono::high_resolution_clock::now();
    double exec_time = chrono::duration_cast<chrono::nanoseconds>(end - start).count() * 1e-9;
    dataFile << x << "," << artype << "," << soalg << "," << st << "," << exec_time << "\n";
    pTable(x, artype, soalg, st, exec_time);
}

void rsorts(int ar[], string artype, int n)
{
    int* temp = new int[n];
    exsorts(temp, ar, n, artype, "Heap");
    exsorts(temp, ar, n, artype, "Bubble");
    exsorts(temp, ar, n, artype, "Selection");
    exsorts(temp, ar, n, artype, "Insertion");
}

void testcompar()
{
    srand(time(0));

    dataFile << "Size of Array,Type of Array,Sorting Algorithm,Number of Comparisons,Execution Time\n";
    cout << left << setw(20) << "Size of Array" << left << setw(20) << "Type of Array"
    << left << setw(20) << "Sorting Algorithm" << left << setw(25) << "Number of Comparisons"
    << left << setw(20) << "Execution Time" << "\n";

    for (int m = 1;m < 31; m++)
    {
        int* randarr = new int[m];
        int* sortedarr = new int[m];
        int* invarr = new int[m];
        int number1 = 0;
        int number2 = 0;
        for (int x = 0; x < m; x++)
        {
            randarr[x] = rand() % (m * 20);
            number1 += rand() % (m * 20);
            sortedarr[x] = number1;
            number2 += rand() % (m * 20);
            invarr[m-x-1] = number2;
        }
        rsorts(randarr, "Random", m);
        rsorts(sortedarr, "Sorted", m);
        rsorts(invarr, "Inversely-sorted", m);
        delete[] randarr;
        delete[] sortedarr;
        delete[] invarr;
    }
}

int main()
{
    testcompar();
    dataFile.close();
    return 0;
}
