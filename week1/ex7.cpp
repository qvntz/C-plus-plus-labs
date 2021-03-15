#include <iostream>
#include <map>

using namespace std;

template<typename Key, typename Value>
Value& GetRefStrict(map<Key, Value>& m, Key key) {
	if (m.count(key) == 0) {
		throw runtime_error("There is no key in dictionary");
	}
	return m[key];
}

int main() {
	map<int, string> m = { {0, "value"} };
	string& item = GetRefStrict(m, 0);
	item = "newvalue";
	cout << m[0] << endl; // выведет newvalue
	return 0;
}