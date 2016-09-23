#include <iostream>
#include <vector>

int num_of_inversions(std::vector<int>);

int main()
{
    int n = 0;
    std::vector<int> nums;

    while(std::cin >> n) {
        nums.push_back(n);
    }

    std::cout << "Number of inversions = " << num_of_inversions(nums);
}

int num_of_inversions(std::vector<int> nums)
{
    int counter = 0;
    for(int i = 0; i < nums.size(); i++) {
        for(int j = i + 1; j < nums.size(); j++) {
            if(nums[i] > nums[j]) {
                counter++;
            }
        }
    }
    return counter;
}