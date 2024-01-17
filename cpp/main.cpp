/*!
    \file "main.cpp"

    Author: Matt Ervin <matt@impsoftware.org>
    Formatting: 4 spaces/tab (spaces only; no tabs), 120 columns.
    Doc-tool: Doxygen (http://www.doxygen.com/)

    https://leetcode.com/problems/kth-largest-element-in-a-stream/
*/

//!\sa https://github.com/doctest/doctest/blob/master/doc/markdown/main.md
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "utils.hpp"

/*
    Design a class to find the kth largest element in a stream.
    Note that it is the kth largest element in the sorted order, 
    not the kth distinct element.

    Implement KthLargest class:

    KthLargest(int k, int[] nums) Initializes the object with the 
    integer k and the stream of integers nums.
    'int add(int val)' appends the integer val to the stream and 
    returns the element representing the kth largest element in the stream.

    Your KthLargest object will be instantiated and called as such:
    KthLargest* obj = new KthLargest(k, nums);
    int param_1 = obj->add(val);

    --------------------------------------------------------------------------

    Solution #1:

    (BRUTE FORCE - not implemented)
    Use a max heap to track/contain ALL values in the stream.
    add() will push the value on the heap, then k values will
    be popped off the heap and the last value popped will be
    returned from add().  All popped values will be pushed
    back on to the heap before add returns.

    Solution #2:

    (OPTIMAL - implememnted)
    Use a min heap with capacity of 'k'.  Each time a value is 
    added to the stream, if the value is greater than the top 
    value on the min heap, pop the top value off the heap and 
    then push the value being added to the stream.

    Time = O(n+m*(log2(k)+log2(k))) => O(n+m*2*log2(k)) => O(n+m*log2(k))
           n = initial population size (nums.size())
           m = number of add instructions.
           first log2(k) = pop() in add().
           second log2(k) = push() in add().

    Space = O(k)  [storage used by heap]
*/
class KthLargest {
public:
    KthLargest(int k, vector<int>& nums)
    : heap_capacity_{k} {
        for (auto const num : nums) {
            add(num);
        }
    }
    
    int add(int val) {
        assert(heap_.size() <= heap_capacity_);
        if (heap_.size() == heap_capacity_) {
            if (heap_.top() < val) {
                heap_.pop();
                heap_.push(std::move(val));
            }
        } else {
            heap_.push(std::move(val));
        }
        
        return heap_.top();
    }

private:
    using heap_t = std::priority_queue<int, std::vector<int>, std::greater<std::vector<int>::value_type>>;
    heap_t heap_{};
    int heap_capacity_{};
};

// [----------------(120 columns)---------------> Module Code Delimiter <---------------(120 columns)----------------]

TEST_CASE("Case 1")
{
    cerr << "Case 1" << '\n';
    vector<int> nums{4, 5, 8, 2};
    auto expected = vector<std::pair<int,int>>{{4, 3}, {5, 5}, {5, 10}, {8, 9}, {8, 4}};
    { // New scope.
        auto const start = std::chrono::steady_clock::now();
        auto solution =  KthLargest{3, nums};
        for (auto const& data : expected) {
            CHECK(data.first == solution.add(data.second));
        }
        cerr << "Elapsed time: " << elapsed_time_t{start} << '\n';
    }
    cerr << '\n';
}

TEST_CASE("Case 1")
{
    cerr << "Case 1" << '\n';
    vector<int> nums{0};
    auto expected = vector<std::pair<int,int>>{{-1, -1}, {0, 1}, {0, -2}, {0, -4}, {1, 3}};
    { // New scope.
        auto const start = std::chrono::steady_clock::now();
        auto solution =  KthLargest{2, nums};
        for (auto const& data : expected) {
            CHECK(data.first == solution.add(data.second));
        }
        cerr << "Elapsed time: " << elapsed_time_t{start} << '\n';
    }
    cerr << '\n';
}

/*
    End of "main.cpp"
*/
