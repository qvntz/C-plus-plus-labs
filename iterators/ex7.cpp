#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>
using namespace std;


template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
	int range_length = range_end - range_begin;
	if (range_length < 2) {
		return;
	}

	vector<typename RandomIt::value_type> elements(range_begin, range_end);
	auto first = elements.begin() + range_length / 3;
	auto second = elements.begin() + range_length / 3 * 2;

	MergeSort(elements.begin(), first); MergeSort(first, second); MergeSort(second, elements.end());
	vector<typename RandomIt::value_type> res;
	merge(elements.begin(), first, first, second, back_inserter(res));

	merge(res.begin(), res.end(), second, elements.end(), range_begin);
}


int main() {
	vector<int> v = { 6, 4, 7, 6, 4, 4, 0, 1, 5 };
	MergeSort(begin(v), end(v));
	for (int x : v) {
		cout << x << " ";
	}
	cout << endl;
	return 0;
}
