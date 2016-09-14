#ifndef matrix3d_H
#define matrix3d_H

#include <stdio.h>
#include <stdlib.h>
#include <new>
#include <assert.h>
#include <math.h>

using namespace std;

class Matrix3d  {

    public:
    double matrix[3][3];
    int row;
    int col;
        Matrix3d(); //constuctor
        Matrix3d(double x, double y);
        Matrix3d(const Matrix3d&); //constructor to copy a matrix3d

        void setZero();
        void setIdentity();
        int getRow();
        int getCol();
        int check();
        void setRow(int arg_row);
        void setCol(int arg_col);
        void transpose();

       const  Matrix3d operator+(const Matrix3d&);
        const Matrix3d operator-(const Matrix3d&);
        Matrix3d operator*(const Matrix3d&);


        double get_X(){return this->matrix[0][0];}
        double get_Y(){return this->matrix[0][1];}
        void set_X(double arg_X){this->matrix[0][0] = arg_X;}
        void set_Y(double arg_Y){this->matrix[0][1] = arg_Y;}


        //matrix3d& operator+=(const matrix3d&);
        Matrix3d& operator=(const Matrix3d&);

       // Rotation
       void rotMatrix(double phi);
       void cordRot(double phi);
       void transMatrix(double Dx, double Dy);
       void scalMatrix(double Sx, double Sy);
};


class Vector3d: public Matrix3d {
public:
    Vector3d(); //constructor

    void transpose();
    void setIdentity();
    int getRow();
    int getCol();

   Vector3d& operator =( Matrix3d& m);

    Vector3d operator*(const Matrix3d&);
    Matrix3d operator *( const Vector3d&);



};





#endif // matrix3d3D_H
