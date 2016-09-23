#include <iostream>
#include <vector>
#include <iterator>

std::vector<int> mergesort(std::vector<int> &);
std::vector<int> merge(std::vector<int> &, std::vector<int> &);

int main()
{
  std::vector<int> vect;
  int num = 0;
  while(std::cin >> num)
  {
    vect.push_back(num);
  }
  vect = mergesort(vect);
  for(int num: vect) {
    std::cout << num  << std::endl;
  }
}

std::vector<int> mergesort(std::vector<int> &main_vector)
{
  std::vector<int>::iterator middle = main_vector.begin();
  std::vector<int> first_half, second_half, temp_vect;

  if(main_vector.size() <= 1) {
    return main_vector;
  }

  middle = main_vector.begin() + (main_vector.size() / 2);

  temp_vect.insert(temp_vect.begin(), main_vector.begin(), middle);
  first_half = mergesort(temp_vect);

  temp_vect.clear();
  temp_vect.insert(temp_vect.begin(), middle, main_vector.end());
  second_half = mergesort(temp_vect);

  main_vector = merge(first_half, second_half);
  return main_vector;

}


std::vector<int> merge(std::vector<int> & first_vect, std::vector<int> & second_vect)
{
  std::vector<int> sorted_vect;
  auto first_it = first_vect.begin(),
        second_it = second_vect.begin();

  while(first_it != first_vect.end() && second_it != second_vect.end()) {
      if(*first_it < *second_it) {
        sorted_vect.push_back(*first_it);
        first_it++;
      } else {
        sorted_vect.push_back(*second_it);
        second_it++;
      }
  }

  sorted_vect.insert(sorted_vect.end(), first_it, first_vect.end());
  sorted_vect.insert(sorted_vect.end(), second_it, second_vect.end());

  return sorted_vect;
}
