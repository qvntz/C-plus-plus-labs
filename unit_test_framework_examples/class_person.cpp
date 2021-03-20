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

class Person {
public:
    // Вы можете вставлять сюда различные реализации класса,
    // чтобы проверить, что ваши тесты пропускают корректный код
    // и ловят некорректный
    void ChangeFirstName(int year, const string& first_name) {
    }
    void ChangeLastName(int year, const string& last_name) {
    }
    string GetFullName(int year) {
    }
};

void TestChangeFirstNameAfter() {
    Person person;
    person.ChangeFirstName(1000, "Matthew");
    for (int i = 1001; i <= 1101; i++) {
        Assert(person.GetFullName(i) == ("Matthew with unknown last name"), "After changing the first name");
    }
}

void TestChangeFirstNameBefore() {
    Person person;
    person.ChangeFirstName(1000, "Matthew");
    for (int i = -5; i < 777; i++) {
        Assert(person.GetFullName(i) == ("Incognito"), "Before changing the first name");
    }
}

void TestChangeLastNameAfter() {
    Person person;
    person.ChangeLastName(1000, "Matthew");
    for (int i = 1001; i <= 1101; i++) {
        Assert(person.GetFullName(i) == ("Matthew with unknown first name"), "After changing the last name");
    }
}

void TestChangeLastNameBefore() {
    Person person;
    person.ChangeLastName(1000, "Matthew");
    for (int i = -5; i < 777; i++) {
        Assert(person.GetFullName(i) == ("Incognito"), "Before changing the last name");
    }
}

void TestChangeFullNameAfter() {
    Person person;
    person.ChangeFirstName(1000, "Matthew");
    person.ChangeLastName(1000, "qvntz");
    for (int i = 1001; i <= 1101; i++) {
        Assert(person.GetFullName(i) == ("Matthew qvntz"), "After changing the full name");
    }
}

void TestChangeFullNameBefore() {
    Person person;
    person.ChangeFirstName(1000, "Matthew");
    person.ChangeLastName(1000, "qvntz");
    for (int i = -5; i < 777; i++) {
        Assert(person.GetFullName(i) == ("Incognito"), "Before changing the full name");
    }
}

void TestAll() {
    TestRunner tr;
    tr.RunTest(TestChangeFirstNameAfter, "TestChangeFirstNameAfter");
    tr.RunTest(TestChangeFirstNameBefore, "TestChangeFirstNameBefore");
    
    tr.RunTest(TestChangeLastNameAfter, "TestChangeLastNameAfter");
    tr.RunTest(TestChangeLastNameBefore, "TestChangeLastNameBefore");
    
    tr.RunTest(TestChangeFullNameAfter, "TestChangeFullNameAfter");
    tr.RunTest(TestChangeFullNameBefore, "TTestChangeFullNameBefore");
}

int main() {
    TestAll();
    return 0;
}