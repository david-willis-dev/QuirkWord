// REF: Further information on building a max heap and utilizing a vector: https://runestone.academy/ns/books/published/cppds/Trees/BinaryHeapImplementation.html
#include <iostream>
#include <string>
#include <queue>
using namespace std;

// Max heap class :]
class Heap
{
public:
    // Constructor:
    Heap(){}
    void makeHeap();
    void extractMax();
    void insert(float jaroVal, string pass);
    vector<pair<float, string>> heapVector;
    int currSize = 0; // Will be updated in insert and extract!
    void printTop(); // Helps with printing just 100!
    const int top = 10;

private:
    void heapifyDown(int index);
};

// REF: Heapify pseudo used via lecture slides (COP3530 University of Florida Fall 2023) (edited to be max heap) and via: https://www.geeksforgeeks.org/building-heap-from-array/
void Heap::heapifyDown(int index)
{
    int size = currSize;
    // Set current index as the largest in the tree:
    int largest = index;
    int leftChild = 2 * index + 1; // Left child is at array spot 2i + 1
    int rightChild = 2 * index + 2; // Right child at array spot 2i + 2

    // If current index is a leaf, or if children of currentIndex are < index -> STOP!
    if((leftChild > size && rightChild > size) || (leftChild < largest && rightChild < largest))
        return;
    // Find the largest child node of current index:
    if(heapVector[largest].first < heapVector[leftChild].first && heapVector[leftChild].first > heapVector[rightChild].first)
        largest = leftChild;
    if(heapVector[largest].first < heapVector[rightChild].first && heapVector[rightChild].first >= heapVector[leftChild].first)
        largest = rightChild;

    // Call heapify down on the index again but only if largest and index are not ==!
    if(largest != index)
    {
        // Now swap largest and current indexes!
        swap(heapVector[index], heapVector[largest]);
        // Recursively call on new index: (ensures that the top reaches spot 0)
        heapifyDown(index);
    }
}

// Once all values are inserted in the heap, heapify down:
void Heap::makeHeap()
{
    // For the currSize of the vector, heapify the whole thing:
    for(int i = currSize; i >= 0; i--)
    {
        heapifyDown(i); // Move down the heap, and swap any parents/children to match max heap order!
    }
}

// Extract 100 of the top values from the heap, and print them
void Heap::extractMax()
{
    // Print out the jaroVal, password
    cout << heapVector[0].first << ", " << heapVector[0].second << endl;
    // Now copy the last value into the first:
    heapVector[0] = heapVector[currSize];
    // Decrement current size
    currSize--;
    // Update the heap to be accurate (makeHeap)
    makeHeap();
}

// Insert a new node into the heap with an integer jaroVal and password string <int, string>
// REF: Based on slides (COP3530 University of Florida Fall 2023)! :]
void Heap::insert(float jaroVal, string pass)
{
    // Insert new pair at end of array with child index of size - 1: and update the size:
    heapVector.emplace_back(jaroVal,pass);
    currSize++;

    int child = heapVector.size() - 1;
    // Set parent index to (index - 1)/2
    int parent  = (child - 1)/2;

    // Loop while parent is >= 0, and while the parent value is greater than child value:
    while(parent >= 0 && heapVector[parent].first > heapVector[child].first)
    {
        // Swap the parent and child in the actual vector
        swap(heapVector[parent],heapVector[child]);
        child = parent;
        parent = (child - 1)/2;
    }
}

// Prints the top 100 of the heap:
void Heap::printTop()
{
    // Build the heap!
    makeHeap();
    // Counter keeps track of which printed
    int counter = 1;

    // Only loop for the top 100
    for(int i = 0; i < top; i++)
    {
        cout << counter << ": ";
        extractMax();
        counter++;
    }
}

// Temporary main: will be commented out!
// int main()
// {
//     Heap heap;
//     heap.insert(1.10, "howdy");
//     heap.insert(2.50, "john");
//     heap.insert(5.20, "billy");
//     heap.insert(6.30, "password");
//     heap.insert(8.40, "letmein");
//     heap.insert(80.30, "bob");
//     heap.insert(30.45, "josh");
//     heap.insert(10.30, "bilbo");
//     heap.insert(11.20, "harry");
//     heap.insert(23.10, "joshua");
//     heap.printTop();

//     return 0;
// }
