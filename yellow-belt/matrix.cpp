#include <iostream>
#include <vector>
#include <exception>

class Matrix {
public:
  Matrix() {
    matrix.assign(0, std::vector<int>(0));
    rows = 0;
    columns = 0;
  }
  Matrix(const int& num_rows, const int& num_columns) {
    if (num_rows < 0 || num_columns < 0) {
      throw std::out_of_range("");
    }
    if (num_rows == 0 || num_columns == 0) {
      matrix.assign(0, std::vector<int>(0));
    } else {
      matrix.assign(num_rows, std::vector<int>(num_columns, 0));
    }
    rows = num_rows;
    columns = num_columns;
  }
  void Reset(const int& num_rows, const int& num_columns) {
    if (num_rows < 0 || num_columns < 0) {
      throw std::out_of_range("");
    } else {
      *this = Matrix(num_rows, num_columns);
    }
  }
  int At(const int& num_row, const int& num_column) const {
    if (num_row < 0 || num_column < 0 ||
	num_row >= GetNumRows() || num_column >= GetNumColumns()) {
      throw std::out_of_range("");
    }
    return matrix.at(num_row).at(num_column);
  }
  int& At(const int& num_row, const int& num_column) {
    if (num_row < 0 || num_column < 0 ||
	num_row >= GetNumRows() || num_column >= GetNumColumns()) {
      throw std::out_of_range("");
    }
    return matrix.at(num_row).at(num_column);
  }
  int GetNumRows(void) const {
    return rows;
  }
  int GetNumColumns(void) const {
    return columns;
  }
private:
  std::vector<std::vector<int>> matrix;
  int rows, columns;
};

std::istream& operator>>(std::istream& is, Matrix& matrix) {
  int n, m;
  is >> n >> m;
  matrix = Matrix(n, m);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      is >> matrix.At(i, j);
    }
  }
  return is;
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
  int n = matrix.GetNumRows(), m = matrix.GetNumColumns();
  os << n << " " << m << std::endl;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      os << matrix.At(i, j) << " ";
    }
    os << std::endl;
  }
  return os;
}

bool operator==(const Matrix& lhs, const Matrix& rhs) {
  bool lhs_zero = lhs.GetNumRows() == 0 ||
    lhs.GetNumColumns() == 0;
  bool rhs_zero = rhs.GetNumRows() == 0 ||
    rhs.GetNumColumns() == 0;
  if (lhs_zero && rhs_zero) {
    return true;
  }
  if (lhs.GetNumRows() == rhs.GetNumRows() &&
      lhs.GetNumColumns() == rhs.GetNumColumns()) {
    for (int i = 0; i < lhs.GetNumRows(); i++) {
      for (int j = 0; j < lhs.GetNumColumns(); j++) {
	if (lhs.At(i,j) != rhs.At(i,j)) {
	  return false;
	}
      }
    }
    return true;
  } else {
    return false;
  }
}

Matrix operator+(const Matrix& lhs, const Matrix& rhs) {
  bool lhs_zero = lhs.GetNumRows() == 0 ||
    lhs.GetNumColumns() == 0;
  bool rhs_zero = rhs.GetNumRows() == 0 ||
    rhs.GetNumColumns() == 0;
  if (lhs_zero && rhs_zero) {
    return {};
  }
  if (lhs.GetNumRows() == rhs.GetNumRows() &&
      lhs.GetNumColumns() == rhs.GetNumColumns()){
    Matrix new_matrix(lhs.GetNumRows(), lhs.GetNumColumns());
    for (int i = 0; i < lhs.GetNumRows(); i++) {
      for (int j = 0; j < lhs.GetNumColumns(); j++) {
        new_matrix.At(i, j) = lhs.At(i, j) + rhs.At(i, j);
      }
    }

    return new_matrix;
  } else {
    throw std::invalid_argument("");
  }
}

int main(void) {

  Matrix m1(0,5), m2(3,0);	
  std::cout <<std::boolalpha<< (m1 == (m1+m2)) << std::endl;
  return 0;

}
