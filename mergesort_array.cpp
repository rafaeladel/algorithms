#include <iostream>

void mergesort(int[], int, int);
void merge(int[], int, int, int);
int inv_counter = 0;

int main()
{
  int arr[] = {8,7,9,1,2,3};
  mergesort(arr, 0, sizeof arr / sizeof arr[0] - 1);
  for(int num: arr) {
    std::cout << num << std::endl;
  }
  std::cout << "Split inversions: " << inv_counter;
}

void mergesort(int arr[], int start, int end)
{
  int mid = start + (end - start) / 2;
  if(start < end) {
    mergesort(arr, start, mid);
    mergesort(arr, mid +1, end);
    merge(arr, start, mid, end);
  }
}

void merge(int arr[], int start, int mid, int end)
{
  int i = start,
      j = mid + 1,
      k = 0,
      len = (end - start) + 1;

  int temp_arr[len];

  while(i <= mid && j <= end) {
      if(arr[i] < arr[j])   {
          temp_arr[k] = arr[i];
          i++;
      } else {
          temp_arr[k] = arr[j];
          inv_counter +=  mid + 1 - i;     
          j++;
      }
      k++;
  }

  while(i <= mid) {
      temp_arr[k++] = arr[i++];
  }

  while(j <= end) {
    temp_arr[k++] = arr[j++];
  }

  for(k = 0; k < len; k++) {
      arr[start++] = temp_arr[k];
  }
}
