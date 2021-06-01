#include <iostream>
#include "AVL_Tree.h"
#include <random>
#include <fstream>
using namespace std;


int main() {
	AVLTree<int, int> t;
	/*cout << "Enter count of digits: ";
	int n;
	cin >> n;

	mt19937 gen;
	uniform_int_distribution<> unif(-10, 10);

	for (int i = 0; i < n; i++) {
		t += unif(gen);
	}
	
	ofstream output("output.txt");
	for (auto it = t.begin(); it != t.end(); it++) {
		output << it->key << "(" << it->value << ") - " << ((float)it->value / (float)n) * 100 << "%\n";
	}*/
	t.insert(1);
	t.insert(1, 5);
	t.print();
	return 0;
}