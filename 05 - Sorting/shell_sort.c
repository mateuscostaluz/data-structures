#include <stdio.h>

// improvement "insertion sort"
void shell_sort(int* v, int n) {
  // define "gap" in code, using the "n" (array size) divided by 2
  // stop when "gap" is equal to 0
  for (int gap = n/2; gap > 0; gap /= 2) {
    // start comparations after "gap"
    for (int i = gap; i < n; i += 1) {
      // "save" the element that will be compared with others elements
      int temp = v[i];
      int j;
      // compare with the other elements in v[position - gap]
      // before reaching position v[0]
      for (j = i; j >= gap && v[j - gap] > temp; j -= gap) {
        v[j] = v[j - gap];
      }
      // put temp (the original a[i]) in correct location
      v[j] = temp;
    }
  }
}

void show(int* v, int n) {
  for(int i = 0; i < n; i++) {
    printf("%d ", v[i]);
  }
}

int main() {
  int v[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
  int n = sizeof(v) / sizeof(int);
  shell_sort(v, n);
  show(v, n);
  return 0;
}
