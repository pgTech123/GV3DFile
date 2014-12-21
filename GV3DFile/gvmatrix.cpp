#include "gvmatrix.h"

GVMatrix::GVMatrix()
{
    m_bMatEmpty = true;
    setDimentions(0,0);
}

GVMatrix::GVMatrix(int Lines, int Cols)
{
    m_bMatEmpty = true;
    setDimentions(Lines,Cols);
}

GVMatrix::GVMatrix(int Lines, int Cols, double **Data)
{
    m_bMatEmpty = true;
    setDimentions(Lines,Cols);
    setData(Data);
}

void GVMatrix::setDimentions(int Lines, int Cols)
{
    m_iLines = Lines;
    m_iCol = Cols;
    m_dData = new double*[Lines];
    for(int i = 0; i < Lines; i++)
    {
        m_dData[i] = new double[Cols];
    }
}

void GVMatrix::setData(double **Data)
{
    for(int i = 0; i < m_iLines; i++)
    {
        for(int j = 0; j < m_iCol; j++)
        {
            m_dData[i][j] = Data[i][j];
        }
    }
    m_bMatEmpty = false;
}


void GVMatrix::setData(double Data, int lines, int cols)
{
    m_dData[lines][cols] = Data;
}

int GVMatrix::getLines()
{
    return m_iLines;
}

int GVMatrix::getCols()
{
    return m_iCol;
}

double** GVMatrix::getData()
{
    return m_dData;
}

bool GVMatrix::multiply(GVMatrix Mat2, GVMatrix MatResult)
{
    int mat2Lines = Mat2.getLines();
    int mat2Cols = Mat2.getCols();
    /*if all matrices size ok*/
    if(m_iCol == mat2Lines &&
               mat2Cols == MatResult.getCols() &&
               m_iLines == MatResult.getLines())
    {
        /*Multiply*/
        int tmpAdd = 0;
        double **dataMat2 = Mat2.getData();

        for(int i = 0; i < m_iLines; i++)
        {
            for(int j = 0; j < Mat2.getCols(); j++)
            {
                tmpAdd = 0;
                for(int a = 0; a < m_iCol; a++)
                {
                    tmpAdd += m_dData[i][a]*dataMat2[a][j];

                }
                MatResult.setData(tmpAdd, i, j);
            }
        }

        return true;
    }
    else{
        return false;
    }
}
