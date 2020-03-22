#include <iostream>
#include <vector>

using namespace std;

class Matrix {
public:
  Matrix () {
    Reset(0, 0);
  }
  Matrix(int num_rows, int num_cols) {
    Reset(num_rows, num_cols);
  }
  void Reset(int num_rows, int num_cols) {
    EnsureLowerBoundRange(num_rows, num_cols);
    if (num_rows != 0 && num_cols != 0) {
      data = vector<vector<int>>(num_rows, vector<int>(num_cols, 0));
      rows = num_rows;
      columns = num_cols;
    } else {
      rows = 0;
      columns = 0;
    }
  }
  int& At(int row, int column) {
    EnsureLowerBoundRange(row, column);
    EnsureUpperBoundRange(row, column);
    return data[row][column];
  }
  int At(int row, int column) const {
    EnsureLowerBoundRange(row, column);
    EnsureUpperBoundRange(row, column);
    return data[row][column];
  }
  int GetNumRows() const {
    return rows;
  }
  int GetNumColumns() const {
    return columns;
  }
private:
  vector<vector<int>> data;
  int rows;
  int columns;
  void EnsureLowerBoundRange(int row, int column) const {
    if (row < 0 || column < 0) {
      throw out_of_range("");
    }
  }
  void EnsureUpperBoundRange(int row, int column) const {
    if (row >= rows || column >= columns) {
      throw out_of_range("");
    }
  }
};

istream& operator>>(istream& stream, Matrix& matrix) {
  int rows, columns;
  stream >> rows >> columns;
  matrix.Reset(rows, columns);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      stream >> matrix.At(i, j);
    }
  }
  return stream;
}

ostream& operator<<(ostream& stream, const Matrix& matrix) {
  int rows = matrix.GetNumRows();
  int columns = matrix.GetNumColumns();
  stream << rows << ' ' << columns << '\n';
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      stream << matrix.At(i, j) << ' ';
    }
    stream << '\n';
  }
  return stream;
}

bool operator==(const Matrix& lhs, const Matrix& rhs) {
  if (lhs.GetNumRows() == rhs.GetNumRows()
    && lhs.GetNumColumns() == rhs.GetNumColumns()) {
    for (int i = 0; i < lhs.GetNumRows(); ++i) {
      for (int j = 0; j < lhs.GetNumColumns(); ++j) {
        if (lhs.At(i, j) != rhs.At(i, j)) {
          return false;
        }
      }
    }
    return true;
  }
  return false;
}

Matrix operator+(const Matrix& lhs, const Matrix& rhs) {
  if (lhs.GetNumRows() != rhs.GetNumRows()
      || lhs.GetNumColumns() != rhs.GetNumColumns()) {
    throw invalid_argument("");
  }
  int rows = lhs.GetNumRows();
  int columns = lhs.GetNumColumns();
  Matrix result(rows, columns);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      result.At(i, j) = lhs.At(i, j) + rhs.At(i, j);
    }
  }
  return result;
}

int main() {
  Matrix matrix1;
  Matrix matrix2;
  cin >> matrix1;
  cin >> matrix2;
  cout << matrix1 + matrix2;
  return 0;
}
