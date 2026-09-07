/**
 * @file stl_concepts.cpp
 * @author Ben Berg (bsb20)
 * @brief Tutorial code for some core C++ Standard Library (STL) concepts.
 */

// The C++ STL provides a container library: a set of generic data structures
// (dynamic arrays, linked lists, hash tables, trees, and so on) along with the
// algorithms and iterators that operate on them. This file is a quick tour of
// the containers you will reach for most often, plus the iterator and erasing
// concepts that are common to all of them.

// Every container is documented at https://en.cppreference.com/w/cpp/container.
// You will want this reference throughout the class, so bookmark it!

// Includes std::remove_if and other generic algorithms.
#include <algorithm>
// Includes std::array, a fixed-size array.
#include <array>
// Includes std::cout (printing) for demo purposes.
#include <iostream>
// Includes std::list, a doubly linked list.
#include <list>
// Includes std::map, an ordered (tree-based) key-value store.
#include <map>
// Includes std::deque, a double-ended queue.
#include <deque>
// Includes std::set, an ordered set of unique keys.
#include <set>
// Includes std::stack, a LIFO adapter.
#include <stack>
// Includes std::string, used for map keys below.
#include <string>
// Includes std::tuple, a fixed-size collection of heterogeneous values.
#include <tuple>
// Includes std::pair and std::make_pair.
#include <utility>
// Includes std::unordered_map, a hash-based key-value store.
#include <unordered_map>
// Includes std::unordered_set, a hash-based set of unique keys.
#include <unordered_set>
// Includes std::vector, a dynamic array.
#include <vector>

// A utility function to print the elements of an int vector.
void print_int_vector(const std::vector<int> &vec) {
  for (const int &elem : vec) {
    std::cout << elem << " ";
  }
  std::cout << std::endl;
}

int main() {
  // ==========================================================================
  // A tour of common STL containers.
  // ==========================================================================

  // std::pair bundles exactly two values, which may be of different types.  Access the members with .first/.second.
  std::pair<std::string, int> person = {"alice", 30};
  std::cout << "pair: " << person.first << " is " << person.second << std::endl;

  // std::make_pair builds one while deducing the types for you.
  auto scored = std::make_pair("exam", 95);
  std::cout << "pair (make_pair): " << scored.first << "=" << scored.second
            << std::endl;

  // std::tuple generalizes pair to any number of heterogeneous values. Access
  // members by index with std::get<N>() (there is no .first/.second).
  std::tuple<std::string, int, double> record = {"widget", 3, 9.99};
  std::cout << "tuple: " << std::get<0>(record) << " x" << std::get<1>(record)
            << " @ $" << std::get<2>(record) << std::endl;

  // std::array is a fixed-size array whose size is known at compile time. It
  // does not grow or shrink. Use it when you know the count up front.
  std::array<int, 5> arr = {1, 2, 3, 4, 5};

  // std::list is a doubly linked list: O(1) insertion/removal anywhere, but no
  // random access (no arr[i]). In practice a vector is usually faster, so you
  // will rarely need this.
  std::list<int> lst = {10, 20, 30};

  // std::vector is a dynamic array. It is the workhorse container: fast random
  // access and amortized O(1) append at the back. Reach for this by default.
  std::vector<int> vec = {0, 1, 2, 3, 4, 5, 6};

  // std::map is a sorted key-value store backed by a balanced tree. Keys are
  // kept in order, and lookups are O(log n).
  std::map<std::string, int> map_ages = {{"alice", 30}, {"bob", 25}};

  // std::unordered_map is a hash-table key-value store with average O(1)
  // lookups but no ordering. Almost always prefer this over std::map, unless
  // you specifically need the keys sorted.
  std::unordered_map<std::string, int> uo_map_ages = {{"alice", 30}, {"bob", 25}};

  // std::set is a sorted collection of unique keys (balanced tree, O(log n)).
  std::set<int> set_ids = {5, 1, 3, 1};

  // std::unordered_set is a hash-based collection of unique keys with average
  // O(1) lookups. Almost always prefer this over std::set, unless you need
  // sorted iteration.
  std::unordered_set<int> uo_set_ids = {5, 1, 3, 1};

  // std::deque is a double-ended queue: O(1) push/pop at both the front and
  // the back, plus random access and iteration like a vector.
  std::deque<int> deq = {20, 30};
  deq.push_front(10);
  deq.push_back(40);

  // std::stack is a LIFO (last-in, first-out) adapter: push and pop from the
  // top.
  std::stack<int> stk;
  stk.push(1);
  stk.push(2);
  stk.push(3);

  // Let's peek at what we built. Sequence containers, deques, and sets support
  // range-based for loops; maps yield key-value pairs; a stack only exposes its
  // top element.
  std::cout << "arr:";
  for (int n : arr) { std::cout << " " << n; }
  std::cout << std::endl;

  std::cout << "lst:";
  for (int n : lst) { std::cout << " " << n; }
  std::cout << std::endl;

  std::cout << "set_ids (sorted, deduped):";
  for (int n : set_ids) { std::cout << " " << n; }
  std::cout << std::endl;

  std::cout << "uo_set_ids (hashed, deduped):";
  for (int n : uo_set_ids) { std::cout << " " << n; }
  std::cout << std::endl;

  // Each map element is a std::pair. The traditional way to read it is through
  // .first (the key) and .second (the value):
  std::cout << "map_ages:";
  for (const auto &entry : map_ages) {
    std::cout << " " << entry.first << "=" << entry.second;
  }
  std::cout << std::endl;

  // A map's element type spells the key as const, so the full type is
  // std::pair<const std::string, int>. Writing const std::string here (without
  // the const) would force a copy of every element into a temporary.
  std::cout << "uo_map_ages:";
  for (const std::pair<const std::string, int> &elem : uo_map_ages) {
    // for (const auto &elem : uo_map_ages) {  // auto deduces the same type
    std::cout << " " << elem.first << "=" << elem.second;
  }
  std::cout << std::endl;

  std::cout << "deq:";
  for (int n : deq) { std::cout << " " << n; }
  std::cout << std::endl;

  std::cout << "stack top: " << stk.top() << std::endl;
  std::cout << std::endl;


  // ==========================================================================
  // Iterators.
  // ==========================================================================

  // Many STL functions operate through iterators: objects that point at an
  // element inside a container. Every container exposes begin() (the first
  // element) and end() (one past the last element). For a 5-element vector,
  // the iterators line up like this:
  //
  //   index:      0     1     2     3     4
  //           +-----+-----+-----+-----+-----+-----+
  //   value:  | 10  | 20  | 30  | 40  | 50  |     |
  //           +-----+-----+-----+-----+-----+-----+
  //              ^                 ^           ^
  //              |                 |           |
  //           begin()        begin() + 3      end()
  //
  // Note that end() **logically** points one past the last element, 
  // so it must never be dereferenced; it only marks where iteration stops. 
  // It takes a little getting used to:
  std::cout << "Walking vec with an explicit iterator type:" << std::endl;
  for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;

  // auto helps! It saves us from spelling out the (often long) iterator type.
  std::cout << "Walking vec with auto:" << std::endl;
  for (auto it = vec.begin(); it != vec.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;

  // ==========================================================================
  // Algorithms.
  // ==========================================================================

  // The <algorithm> header provides generic functions that work on any pair of
  // iterators. std::sort, for example, sorts a range in place. By default it
  // sorts ascending; passing a comparator (here a lambda) changes the order.
  std::vector<int> nums = {30, 10, 50, 20, 40};
  std::sort(nums.begin(), nums.end());
  std::cout << "nums sorted ascending:";
  for (int n : nums) { std::cout << " " << n; }
  std::cout << std::endl;

  // std::sort also works on a std::deque, which provides random-access
  // iterators too. Here we sort our deque descending with a comparator lambda.
  std::sort(deq.begin(), deq.end(), [](int a, int b) { return a > b; });
  std::cout << "deq sorted descending:";
  for (int n : deq) { std::cout << " " << n; }
  std::cout << std::endl;

  // std::sort needs random-access iterators, so it does NOT work on a
  // std::list. Instead, std::list provides its own sort member function. Here
  // we sort a list descending by passing a comparator lambda.
  std::list<int> lnums = {30, 10, 50, 20, 40};
  lnums.sort([](int a, int b) { return a > b; });
  std::cout << "lnums sorted descending:";
  for (int n : lnums) { std::cout << " " << n; }
  std::cout << std::endl;
  std::cout << std::endl;

  // ==========================================================================
  // Erasing elements from a vector.
  // ==========================================================================

  // erase() by position: delete a single element. The argument is an iterator.
  // vec.begin() points at the first element, and adding an integer advances it,
  // so vec.begin() + 2 points at vec[2]. Note that vec.end() points one past
  // the last element and must never be dereferenced.
  vec.erase(vec.begin() + 2);
  std::cout << "vec after erasing vec[2] (which was 2):" << std::endl;
  print_int_vector(vec);

  // erase() by range: delete a half-open range [first, last). Here we delete
  // everything from index 1 through the end.
  vec.erase(vec.begin() + 1, vec.end());
  std::cout << "vec after erasing everything from index 1 onward:" << std::endl;
  print_int_vector(vec);

  // Erasing every element that matches a condition. Doing this by hand while
  // iterating is a classic source of bugs, because erase() shifts the
  // remaining elements and shrinks the container. Let's rebuild vec and look
  // at what goes wrong before showing what works.
  vec = {0, 1, 2, 3, 4, 5, 6};

  // WRONG: iterating forwards. vec.erase(it) invalidates it, and then ++it
  // advances a dangling iterator -- and also skips the element that slid into
  // the erased slot.
  // for (auto it = vec.begin(); it != vec.end(); ++it) {
  //   if (*it % 2 == 0) {
  //     vec.erase(it);
  //   }
  // }

  // WRONG: iterating backwards with reverse iterators. vec.erase() only accepts
  // a forward iterator, not a reverse_iterator, so this will not even compile
  // without an awkward .base() conversion -- and erasing would still invalidate
  // the iterator. Reversing direction is not the fix here.
  // for (auto rit = vec.rbegin(); rit != vec.rend(); ++rit) {
  //   if (*rit % 2 == 0) {
  //     vec.erase(rit);
  //   }
  // }

  // CORRECT: iterate forwards, but let erase() drive the loop. vec.erase(it)
  // removes the element at it and returns an iterator to the element that slid
  // into its place, so we assign that back (it = vec.erase(it)) instead of
  // erasing and then blindly doing ++it (which would skip an element / use an
  // invalidated iterator). We only advance with ++it when we do NOT erase.
  vec = {0, 1, 2, 3, 4, 5, 6};
  for (auto it = vec.begin(); it != vec.end(); /* advanced inside the loop */) {
    if (*it % 2 == 0) {
      it = vec.erase(it);
    } else {
      ++it;
    }
  }
  std::cout << "vec after erasing even numbers (it = vec.erase(it)):"
            << std::endl;
  print_int_vector(vec);

  // CORRECT (and idiomatic): the erase-remove idiom. std::remove_if shuffles
  // every element matching the predicate to the back of the range and returns
  // an iterator to the first such element. The vector's erase then deletes
  // everything from there to the end in a single call. Here we rebuild vec and
  // filter out the odd numbers.
  vec = {0, 1, 2, 3, 4, 5, 6};
  vec.erase(std::remove_if(vec.begin(), vec.end(),
                           [](int n) { return n % 2 != 0; }),
            vec.end());
  std::cout << "vec after erasing odd numbers (erase-remove idiom):" << std::endl;
  print_int_vector(vec);

  return 0;
}
