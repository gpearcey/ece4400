# Sorting Algorithms
## Bubble Sort
![Alt text](image.png)

## Insertion Sort

```
template<typename Iter, typename Comparator>
void insertionSort(const Iter& begin, const Iter& end, Comparator compareFn)
{
    for (auto i = next(begin,1); i != end; i++){
        auto key = std::move(*i);
    	auto j = prev(i,1);
    	while (j >= begin && compareFn(*j, key)){
    	    *(next(j,1)) = std::move(*j);
    	    j--;
    	}
		*(next(j,1)) = std::move(key);
    }
}
```

## Merge Sort
## Quick Sort

```
template<typename T>
void quickSort(std::list<T>& arr) {      
         
    //choose pivot
    //selects the median of 3 values taken from the front, back and middle of array
    T pivot;
    if (arr.size() >=3){
        std::vector<T> pivot_values; //vector to hold 3 potential pivots
        pivot_values.push_back(arr.front());

        //pick a value from the middle of arr
        std::list<int>::iterator it = arr.begin();
        std::advance(it, std::distance(arr.begin(), arr.end())/2);
        pivot_values.push_back(*it);

        pivot_values.push_back(arr.back());

        //sort 3 pivot values and select the one in the middle as the pivot
        std::sort(pivot_values.begin(),pivot_values.end());
        pivot = pivot_values[1];
    }
    else{
        //if array has less than three values, just select the first one for the pivot
        pivot = arr.front();
    }

    std::list<T> less;
    std::list<T> equal;
    std::list<T> greater;

    //Sort elements in arr into less, equal, and greater lists based on pivot
    for (T a : arr) {
        if(a< pivot){
            less.push_back(a);
        }
        else if (a == pivot) {
            equal.push_back(a);
        }
        else if (a > pivot){
            greater.push_back(a);
        }
    }

    //Don't do anymore sorting if size is 1
    if (less.size() > 1){
        quickSort(less);        
    }
    if (greater.size() > 1){
        quickSort(greater);    
    }
    
    //add equal to the end of less
    less.splice(less.end(), equal);

    //add greater to the end of less
    less.splice(less.end(), greater);

    //set arr to the sorted list
    arr = less;
    
    return;

};

```
## Bucket Sort
## Radix Sort 
