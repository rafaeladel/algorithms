#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

void mergesort(std::vector<int>::iterator, std::vector<int>::iterator);
void merge(std::vector<int>::iterator, std::vector<int>::iterator, std::vector<int>::iterator);
  std::vector<int> vect {2,3,1,8,6,4,7,5};

int main()
{
  mergesort(vect.begin(), vect.end());
  for(int num: vect) {
    std::cout << num << " ";
  }

}

void mergesort(std::vector<int>::iterator begin_iter, std::vector<int>::iterator end_iter)
{
  std::vector<int>::iterator middle_iter;

  if(end_iter - begin_iter > 2) {
    middle_iter = begin_iter + ((end_iter - begin_iter) / 2);
    mergesort(begin_iter, middle_iter);
    mergesort(middle_iter, end_iter);
    merge(begin_iter, middle_iter, end_iter);
  }

}

void merge(std::vector<int>::iterator begin_iter,
            std::vector<int>::iterator middle_iter,
            std::vector<int>::iterator end_iter)
{
  auto first_iter = begin_iter, second_iter = middle_iter + 1;
  int limit = 0;

  while(first_iter < middle_iter && second_iter < end_iter + 1) {
      if(*first_iter < *second_iter) {
        limit = second_iter - first_iter - 1;
      } else {
        limit = second_iter - first_iter;
      }

      for (size_t i = 0; i < limit; i++) {
        std::iter_swap(second_iter - i, second_iter - (i + 1));
      }

      first_iter += 2;
      second_iter++;
  }
}
