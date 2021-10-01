#include "ARRAY_SORTS.h"

// Multithreading Quick sort algoritm
unique_ptr<vector<int>> quick_sort_multithreading(unique_ptr<vector<int>> v) {

    int size = v->size();
    if (size < 2) return v;

    int pivot_index = size >> 1; 
        //print_multithread("pivot index: " + to_string(pivot_index) + " thread: ");
        //cout << this_thread::get_id();
    int pivot_value = (*v)[pivot_index];
    int pivot_values_counter = 0;

    unique_ptr <vector<int>> lower_values(new vector<int>);
    unique_ptr <vector<int>> higher_values(new vector<int>);
    
    for (int i = 0; i < size; ++i) {
        int val = (*v)[i];
        if (val < pivot_value) lower_values->push_back(val);
        else if (val == pivot_value) pivot_values_counter++;
        else higher_values->push_back(val);
    }

    packaged_task <unique_ptr<vector<int>>(unique_ptr<vector<int>>)>
        lower_sort(quick_sort_multithreading);
    packaged_task <unique_ptr<vector<int>>(unique_ptr<vector<int>>)>
        higher_sort(quick_sort_multithreading);

    future<unique_ptr<vector<int>>> lower_future = lower_sort.get_future();
    future<unique_ptr<vector<int>>> higher_future = higher_sort.get_future();
    
    thread thread1(move(lower_sort), move(lower_values)); thread1.detach();
    thread thread2(move(higher_sort), move(higher_values)); thread2.detach();

    unique_ptr <vector<int>> sort_lower = lower_future.get();
    unique_ptr <vector<int>> sort_higher = higher_future.get();
    
    unique_ptr<vector<int>> result_vector(new vector<int>);
    move(sort_lower->begin(), sort_lower->end(), back_inserter(*result_vector));
    for (int i = 0; i < pivot_values_counter; ++i) result_vector->push_back(pivot_value);
    move(sort_higher->begin(), sort_higher->end(), back_inserter(*result_vector));
   
    return result_vector;
}