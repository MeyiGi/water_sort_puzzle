#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int max_value = 3;
const int max_size = 6;
const int min_value = 1;

int count_of_ones = 0;
int count_of_twos = 0;
int count_of_threes = 0;

class Array {
public:
    int rear;
    int front;
    int size;
    int* arr;
    int count;

    Array(int size) {
        this->count = 0;
        this->rear = -1;
        this->front = -1;
        this->size = size;
        arr = new int[size];
    }

    bool isEmpty() {
        return count == 0;
    }

    bool isFull() {
        return count == size;
    }
};

void insertQatEnd(Array& arr, int val) {
    if (arr.isFull()) {
        cout << "\nQueue is full" << endl;
        return;
    }
    if (arr.isEmpty()) {
        arr.rear = arr.front = 0;
    } else {
        arr.rear = (arr.rear + 1) % arr.size;
    }
    arr.arr[arr.rear] = val;
    arr.count += 1;
}

void insertQatBeg(Array& arr, int val) {
    if (arr.isFull()) {
        cout << "\nQueue is full" << endl;
        return;
    }
    if (arr.isEmpty()) {
        arr.rear = arr.front = 0;
    } else {
        arr.front = (arr.front - 1 + arr.size) % arr.size;
    }
    arr.arr[arr.front] = val;
    arr.count += 1;
}

int delQBeg(Array& arr) {
    int return_value = arr.arr[arr.front];
    arr.front = (arr.front + 1) % arr.size;
    arr.count -= 1;
    if (arr.isEmpty()) {
        arr.rear = arr.front = -1;
    }
    return return_value;
}

int delQEnd(Array& arr) {
    int return_value = arr.arr[arr.rear];
    arr.rear = (arr.rear - 1 + arr.size) % arr.size;
    arr.count -= 1;
    if (arr.isEmpty()) {
        arr.rear = arr.front = -1;
    }
    return return_value;
}

void printArray(Array& arr) {
    for (int i = 0; i < arr.count; i++) {
        cout << arr.arr[(arr.front + i) % arr.size] << " ";
    }
    cout << endl;
}

int create_random_number() {
    int random_number1;
    while (true) {
        random_number1 = rand() % (max_value - min_value + 1) + min_value;
        switch (random_number1) {
            case 1:
                if (count_of_ones < max_size) {
                    count_of_ones++;
                    return random_number1;
                }
                break;
            case 2:
                if (count_of_twos < max_size) {
                    count_of_twos++;
                    return random_number1;
                }
                break;
            case 3:
                if (count_of_threes < max_size) {
                    count_of_threes++;
                    return random_number1;
                }
                break;
        }
    }
}

void moveElement(Array& fromArr, int deleteSide, Array& toArr, int enqueueSide) {
    int popped_value;

    // Remove element from `fromArr`
    if (deleteSide == 1) {
        if (!fromArr.isEmpty())
            popped_value = delQBeg(fromArr);
        else {
            cout << "Source array is empty.\n";
            return;
        }
    }
    else if (deleteSide == 2) {
        if (!fromArr.isEmpty())
            popped_value = delQEnd(fromArr);
        else {
            cout << "Source array is empty.\n";
            return;
        }
    }
    else {
        cout << "Invalid delete side.\n";
        return;
    }

    // Insert element to `toArr`
    if (enqueueSide == 1) {
        insertQatBeg(toArr, popped_value);
    }
    else if (enqueueSide == 2) {
        insertQatEnd(toArr, popped_value);
    }
    else {
        cout << "Invalid enqueue side.\n";
    }
}

int main() {
    // Seed the random number generator
    srand(time(0));

    // Declaration of Double-ended arrays
    Array arr1(max_size);
    Array arr2(max_size);
    Array arr3(max_size);
    Array arr4(max_size);
    Array arr5(max_size);

    // Initializing with random numbers
    for (int i = 0; i < max_size; i++) {
        insertQatEnd(arr1, create_random_number());
        insertQatEnd(arr2, create_random_number());
        insertQatEnd(arr3, create_random_number());
    }

    while (true) {
        int choice;
        cout << "1. Move | 2. Show | 3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;


        switch (choice) {
            case 1: {
                int fromChoice, deleteSide, toChoice, enqueueSide;

                cout << "1. arr1 | 2. arr2 | 3. arr3 | 4. arr4 | 5. arr5" << endl;
                cout << "From which you wanna move: ";
                cin >> fromChoice;
                cout << endl;

                cout << "1. left side | 2. right side" << endl;
                cout << "From which side you wanna delete: ";
                cin >> deleteSide;
                cout << endl;

                cout << "1. arr1 | 2. arr2 | 3. arr3 | 4. arr4 | 5. arr5" << endl;
                cout << "Enqueue to: ";
                cin >> toChoice;
                cout << endl;

                cout << "1. left side | 2. right side" << endl;
                cout << "Enqueue to which side: ";
                cin >> enqueueSide;
                cout << endl;

                Array* fromArray;
                Array* toArray;

                switch (fromChoice) {
                    case 1: fromArray = &arr1; break;
                    case 2: fromArray = &arr2; break;
                    case 3: fromArray = &arr3; break;
                    case 4: fromArray = &arr4; break;
                    case 5: fromArray = &arr5; break;
                    default: cout << "Invalid array choice.\n"; continue;
                }

                switch (toChoice) {
                    case 1: toArray = &arr1; break;
                    case 2: toArray = &arr2; break;
                    case 3: toArray = &arr3; break;
                    case 4: toArray = &arr4; break;
                    case 5: toArray = &arr5; break;
                    default: cout << "Invalid array choice.\n"; continue;
                }

                moveElement(*fromArray, deleteSide, *toArray, enqueueSide);
                break;
            }
            case 2:
                cout << "arr1: "; printArray(arr1);
                cout << "arr2: "; printArray(arr2);
                cout << "arr3: "; printArray(arr3);
                cout << "arr4: "; printArray(arr4);
                cout << "arr5: "; printArray(arr5);
                break;
            case 3:
                exit(0);
            default:
                cout << "Invalid option. Try again.\n";
        }
        cout << endl;
    }
}
