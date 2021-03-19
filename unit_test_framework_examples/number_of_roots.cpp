#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <random>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
    os << "{";
    bool first = true;
    for (const auto& kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
            os << " hint: " << hint;
        }
        throw runtime_error(os.str());
    }
}

void Assert(bool b, const string& hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string& test_name) {
        try {
            func();
            cerr << test_name << " OK" << endl;
        }
        catch (exception& e) {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        }
        catch (...) {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};

int GetDistinctRealRootCount(double a, double b, double c) {
    // Вы можете вставлять сюда различные реализации функции,
    // чтобы проверить, что ваши тесты пропускают корректный код
    // и ловят некорректный
}

void TestRootCount() {
    mt19937 gen;
    uniform_real_distribution<> unif(-10, 10);

    for (int i = 0; i <= 100; i++) {
        const auto a = unif(gen);
        const auto b = unif(gen);
        const auto c = unif(gen);

        const auto count = GetDistinctRealRootCount(a, b, c);
        Assert(count >= 0 && count <= 2, "Quadratic equation has only 0, 1 or 2 real roots.");
    }
}

void TestLinearEquation() {
    mt19937 gen;
    uniform_real_distribution<> unif(-10, 10);

    for (int i = 0; i <= 100; i++) {
        const auto b = unif(gen);
        const auto c = unif(gen);

        const auto count = GetDistinctRealRootCount(0, b, c);
        Assert(count == 1, "There is only one root in a linear equation");
    }
}

void TestOneRoot() {
    mt19937 gen;
    uniform_int_distribution<> unif(-10, 10);

    for (int i = 0; i <= 100; i++) {
        const auto x_1 = unif(gen);

        const auto b = (-x_1 - x_1);
        const auto c = x_1 * x_1;

        const auto count = GetDistinctRealRootCount(1, b, c);
        ostringstream os;
        os << showpos << "x^2" << b << "x" << c << " = 0 has only one root.";
        Assert(count == 1, os.str());
    }
}

void TestNoOneRoot() {
    mt19937 gen;
    uniform_int_distribution<> unif(-10, 10);

    for (int i = 0; i <= 100; i++) {
        const auto b = unif(gen);

        const auto a = b * 3;
        const auto c = b * 2;

        const auto count = GetDistinctRealRootCount(a, b, c);
        ostringstream os;
        os << showpos << a << "x^2" << b << "x" << c << " = 0 has no one root.";
        Assert(count == 0, os.str());
    }
}

void TestAll() {
    TestRunner tr;
    tr.RunTest(TestRootCount, "TestRootCount");
    tr.RunTest(TestLinearEquation, "TestLinearEquation");
    tr.RunTest(TestOneRoot, "TestOneRoot");
    tr.RunTest(TestNoOneRoot, "TestNoOneRoot");
}

int main() {
    TestAll();
    return 0;
}
