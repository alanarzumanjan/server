#include <iostream>

using namespace std;

void print(int arr[], int len)
{
    for (int i = 0; i < len; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void bubble_sort(int array[], int len)
{
    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < len - 1; j++)
        {
            if (array[j] > array[j + 1])
            {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
    cout << "Sorted array: ";
    print(array, len);
}

void max_and_min_inarray(int arr[], int len)
{
    int max = arr[0];
    int min = arr[0];
    for (int i = 0; i < len; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
        if (arr[i] < min)
        {
            min = arr[i];
        }
    }
    cout << "Max: " << max << endl;
    cout << "Min: " << min << endl;
}

void cube_array(int arr[], int len)
{

    for (int i = 0; i < len; i++)
    {
        arr[i] = arr[i] * arr[i] * arr[i];
    }
    cout << "Cube array: ";
    print(arr, len);
}

void dead_array(int arr[], int len)
{
    for (int i = 0; i < len; i++)
    {
        arr[i] = 0;
    }
    printf("Dead array: ");
    print(arr, len);
}

int main()
{
    int array[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int len = sizeof(array) / sizeof(array[0]);

    cout << "Array: ";
    print(array, len);

    bubble_sort(array, len);
    max_and_min_inarray(array, len);
    cube_array(array, len);
    dead_array(array, len);

    return 0;
}