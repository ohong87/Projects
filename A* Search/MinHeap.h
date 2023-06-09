#include <vector>
#include <stdexcept>
#include <iostream>
#include <ostream>

using namespace std;

template <class T>
class MinHeap {
  public:
    /* Constructor that builds a d-ary Min Heap
    This should work for any d >= 2,
    but doesn't have to do anything for smaller d.*/
    MinHeap (int d);

    ~MinHeap ();

    /* adds the item to the heap, with the given priority. */
    void add (T item, int priority);

    /* returns the element with smallest priority.  
    Break ties however you wish.  
    Throws an exception if the heap is empty. */
    const T & peek () const;

    /* removes the element with smallest priority.
    Break ties however you wish.
    Throws an exception if the heap is empty. */
    void remove ();

    /* returns true iff there are no elements on the heap. */
    bool isEmpty ();

    void update(T a, int b);

    const int & getPriority() const;

  private:
    // whatever you need to naturally store things.
    // You may also add helper functions here.

    void bubbleUp(int pos);

    void trickleDown(int pos);

    void swap(int a, int b);


    int size;
    int num;
    vector<pair<T, int>> map;
};

template <typename T>
MinHeap<T>::MinHeap(int d){
  num = d;
  size = 0;
};

template <typename T>
MinHeap<T>::~MinHeap(){

}

template <typename T>
void MinHeap<T>::add(T item, int priority){

  pair<T, int> temp;
  temp.first = item;
  temp.second = priority;

  map.push_back(temp);

  bubbleUp(size);
  size++;
}

template <typename T>
const T& MinHeap<T>::peek() const{
  if(map.size() == 0){
    throw runtime_error("Heap is empty");
  }
  else{
      return map[0].first;
  }
}

template <typename T>
const int & MinHeap<T>::getPriority() const{
  if(map.size() == 0){
    throw runtime_error("Heap is empty");
  }
  else{
      return map[0].second;
  }
}

template <typename T>
void MinHeap<T>::remove(){
  if(map.size() == 0){
    //cout << "broken peek" << endl;
    throw runtime_error("Heap is empty");
  }
  else{
    swap(0, size-1);
    map.pop_back();
    size--; 
    trickleDown(0);
  }
}

template <typename T>
bool MinHeap<T>::isEmpty(){
  if(size == 0) return true;
  else return false;
}

template <typename T>
void MinHeap<T>::bubbleUp(int pos){
  if(pos > 0 && map[pos].second < map[(pos - 1)/num].second){ //if parent priority > child priority
    swap(pos, (pos-1)/num);
    bubbleUp((pos-1)/num);
  }
  else if(pos > 0 && map[pos].second == map[(pos - 1)/num].second){
    if(map[pos].first < map[(pos - 1)/num].first){
      swap(pos, (pos-1)/num);
      bubbleUp((pos-1)/num);
    }
  }
}

template <typename T>
void MinHeap<T>::trickleDown(int pos){
  int child = num*pos+1; //left child
  int min = child;


  if(child < size){ //if child isn't the only node
    for(int i = 1; i < num; i++){ //finds which child to switch with
      if(child + i < size && map[min].second > map[child + i].second){
        min = child+i;
      }
    }
    if(map[min].second < map[pos].second){
      swap(min, pos);
      trickleDown(min);
    }
    else if(map[min].second == map[pos].second){
      if(map[min].first < map[pos].first){
        swap(min, pos);
        trickleDown(min);
      }
    }
  }
}

template <typename T>
void MinHeap<T>::swap(int a, int b){
  pair<T, int> temp = map[a];
  map[a] = map[b];
  map[b] = temp;
}