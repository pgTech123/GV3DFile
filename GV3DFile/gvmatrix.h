#ifndef GVMATRIX_H
#define GVMATRIX_H

class GVMatrix
{
public:
    GVMatrix();
    GVMatrix(int Lines, int Cols);
    GVMatrix(int Lines, int Cols, double **Data);

    void setDimentions(int Lines, int Cols);
    void setData(double **Data);
    void setData(double Data, int line, int col);

    int getLines();
    int getCols();
    double** getData();

    bool multiply(GVMatrix Mat2, GVMatrix MatResult);

private:
    int m_iCol;
    int m_iLines;
    double **m_dData;

    /*Safety*/
    bool m_bMatEmpty;
};

#endif // GVMATRIX_H
