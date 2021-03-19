# C-plus-plus-labs
### Solutions for courses and laboratory work.

The difficulty of the work (Written next to a short description of the task):
1) Easy
2) Normal
3) Hard


### Unit test framework


<br>***Template for using the framework***
```
void TestSomething() {
	AssertEqual(..., ...);
}

void TestAll() {
	TestRunner tr;
	tr.RunTeset(TestSomething, "TestSomething");
}

int main() {
	TestAll();
	return 0;
}
```