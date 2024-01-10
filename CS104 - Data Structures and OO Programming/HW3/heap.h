#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>
#include <iostream>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator()) {
		ary = m;
	};

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
	std::vector<T> data;
	int ary;
};

template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap()
{

}

template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const
{
	return data.empty();
}


template <typename T, typename PComparator>
size_t Heap<T,PComparator>::size() const
{
  return data.size();
}


template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    throw std::out_of_range("heap is empty");
  }
  
	return data[0];
}


template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item)
{
	data.push_back(item);
	std::size_t index = data.size() - 1;
	while (index != 0) {
		std::size_t parent_index = (index - 1) / ary;
		T& current = data[index];
		T& parent = data[parent_index];
		if (!PComparator()(current, parent)) {
			break;
		}
		std::swap(current, parent);
		index = parent_index;
	}
}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    throw std::out_of_range("heap is empty");
  }

	int index = data.size() - 1;
	int temp = 0;
  int best = 0;
	std::swap(data[0], data[index]);
	data.pop_back();
	index--;
	bool next;
	while (temp < (index/ary) + 1){
		next = 0;
		best = ary*temp + 1;
		for (int i = 1; (i <= ary) && (ary*temp + i <= index); i++){
			if (!PComparator()(data[temp], data[ary*temp + i])){
				next = 1;
				break;
			}
		}
		if (next == 1){
			for (int i = 1; (i <= ary) && (ary*temp + i <= index); i++){
        if (!PComparator()(data[best], data[ary*temp + i])){
					best = ary*temp + i;
				}
			}
			std::swap(data[temp], data[best]);
			temp = best;
		} else {
			break;
		}
	}
}

#endif