#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;


class Matrix {
private:
	int rows_;
	int cols_;

	vector<vector<int>> elem_;

public:
	Matrix() {
		rows_ = 0;
		cols_ = 0;
	}
	Matrix(int rows, int cols) {
		Reset(rows, cols);
	}

	void Reset(int rows, int cols) {
		if (rows < 0) {
			throw out_of_range("num_rows must be >= 0");
		}
		if (cols < 0) {
			throw out_of_range("num_columns must be >= 0");
		}
		if (rows == 0 || cols == 0) {
			rows = cols = 0;
		}

		rows_ = rows;
		cols_ = cols;
		elem_.assign(rows, vector<int>(cols));
	}

	int& At(int num_row, int num_col) {
		if (num_row < 0 || num_row >= rows_ || num_col < 0 || num_col >= cols_)
			throw out_of_range("Going beyond the matrix");

		return elem_.at(num_row).at(num_col);
	}

	int At(int num_row, int num_col) const {
		if (num_row < 0 || num_row > rows_ || num_col < 0 || num_col > cols_)
			throw out_of_range("Going beyond the matrix");

		return elem_.at(num_row).at(num_col);
	}

	int GetNumRows() const {
		return rows_;
	}

	int GetNumColumns() const {
		return cols_;
	}
};

bool operator==(const Matrix& one, const Matrix& two) {
	if (one.GetNumRows() != two.GetNumRows() || one.GetNumColumns() != two.GetNumColumns()) {
		return false;
	}

	for (int r = 0; r < one.GetNumRows(); ++r) {
		for (int c = 0; c < one.GetNumColumns(); ++c) {
			if (one.At(r, c) != two.At(r, c)) {
				return false;
			}
		}
	}

	return true;
}

Matrix operator+(const Matrix& one, const Matrix& two) {
	if (one.GetNumRows() != two.GetNumRows() || one.GetNumColumns() != two.GetNumColumns()) {
		throw invalid_argument("Mismatched number of rows or columns");
	}

	Matrix result(one.GetNumRows(), one.GetNumColumns());
	for (int r = 0; r < result.GetNumRows(); ++r) {
		for (int c = 0; c < result.GetNumColumns(); ++c) {
			result.At(r, c) = one.At(r, c) + two.At(r, c);
		}
	}

	return result;
}

istream& operator>>(istream& in, Matrix& matrix) {
	int rows, cols;
	in >> rows >> cols;

	matrix.Reset(rows, cols);
	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < cols; ++c) {
			in >> matrix.At(r, c);
		}
	}

	return in;
}

ostream& operator<<(ostream& out, const Matrix& matrix) {
	out << matrix.GetNumRows() << " " << matrix.GetNumColumns() << "\n";
	for (int r = 0; r < matrix.GetNumRows(); ++r) {
		for (int c = 0; c < matrix.GetNumColumns(); ++c) {
			out << matrix.At(r, c) << " ";
		}
		out << "\n";
	}

	return out;
}



int main() {
	Matrix one;
	Matrix two;
	cin >> one >> two;
	cout << one;
	cout << two;
	cout << one + two << endl;
	return 0;
}