#include <cstdint>
#include <iostream>

using namespace std;

int main() {
    tuple t(7, "C++", true);
	cout << get<1>(t) << endl;
    return 0;
}