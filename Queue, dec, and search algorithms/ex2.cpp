#include <map>
#include <string>
#include <iterator>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;


template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
    RandomIt range_begin, RandomIt range_end, char prefix) {

    auto it = lower_bound(range_begin, range_end, string(1, prefix));
    char next_prefix = static_cast<char>(prefix + 1);
    auto it2 = lower_bound(it, range_end, string(1, next_prefix));

    return { it, it2 };
}

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, const string& prefix) {
    auto it = lower_bound(range_begin, range_end, prefix);
    string next_prefix = prefix;
    next_prefix[next_prefix.size() - 1]++;
    auto it2 = lower_bound(it, range_end, next_prefix);

    return { it, it2 };
}

int main() {
    const vector<string> sorted_strings = { "moscow", "murmansk", "vologda" };

    const auto m_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), 'm');
    for (auto it = m_result.first; it != m_result.second; ++it) {
        cout << *it << " ";
    }
    cout << endl;

    const auto p_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), 'p');
    cout << (p_result.first - begin(sorted_strings)) << " " <<
        (p_result.second - begin(sorted_strings)) << endl;

    const auto z_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), 'z');
    cout << (z_result.first - begin(sorted_strings)) << " " <<
        (z_result.second - begin(sorted_strings)) << endl;

    return 0;
}
