#include "VectorMath.h"

Matrix3d::Matrix3d(){
    setZero();
    row =3;
    col  =3;
}
Matrix3d::Matrix3d(double x, double y){
    setZero();
    matrix[0][0] =x;
    matrix[0][1] = y;
    matrix[0][2] = 1;
    row =1;
    col  =3;
}
void Matrix3d::setRow(int arg_row){
    row = arg_row;
};



void Matrix3d::setCol(int arg_col){
    col = arg_col;
};



// Copy constructor
Matrix3d::Matrix3d(const Matrix3d& m){
    // Set row and col for new matrix
    this->setCol(m.col);
    this->setRow(m.row);

    // copy all the data to new matrix
    for(int i=0; i<3; i++){
        for(int j =0; j<3;j++){
            matrix[i][j] = m.matrix[i][j];
        }
    }
};

void Matrix3d::setZero(){
    for(int i=0; i<3; i++){
        for(int j =0; j<3;j++){
            matrix[i][j] = 0;
        }
    }
};

void Matrix3d::setIdentity(){
    for(int i=0; i<3; i++){
        for(int j =0; j<3;j++){
            if(i==j)
                matrix[i][j] = 1;
            else
                matrix[i][j] =0;
        }
    }
};


const Matrix3d  Matrix3d::operator+(const Matrix3d& m){

    Matrix3d temp;
    for(int i=0; i<3; i++){
        for(int j =0; j<3;j++){
            temp.matrix[i][j] = this->matrix[i][j]+m.matrix[i][j];
        }
    }
    return temp;
}

const Matrix3d  Matrix3d::operator-(const Matrix3d& m){

    Matrix3d temp;
    for(int i=0; i<3; i++){
        for(int j =0; j<3;j++){
            temp.matrix[i][j] = this->matrix[i][j]-m.matrix[i][j];
        }
    }
    return temp;
};



Matrix3d  Matrix3d::operator*(const Matrix3d& m){

    Matrix3d temp;
    for(int i=0; i<3; ++i){
        for(int j=0; j<3; ++j){
            for(int k=0; k<3; ++k)
            {
                temp.matrix[i][j] =  temp.matrix[i][j]+(this->matrix[i][k]*m.matrix[k][j]);
            }
        }
    }
    return temp;
};


Matrix3d& Matrix3d::operator=(const Matrix3d& m){
    //Check for self assignment
    if (this == &m)      // Same object?
        return *this;        // Yes, so skip assignment, and just return *this.
    //Check if row and colls match


    for(int i=0; i<3; i++){
        for(int j =0; j<3;j++){
            this->matrix[i][j] = m.matrix[i][j];
        }
    }
    return *this;
};


void Matrix3d::transpose( ){
    int a01= 0, a02 = 0, a12=0;

    //Save diagonal elemnts in temp data
    a01 = this->matrix[0][1];
    a02 = this->matrix[0][2];
    a12 = this->matrix[1][2];

    //Change non diagonal elemnets
    this->matrix[0][1] = this->matrix[1][0];
    this->matrix[0][2]= this->matrix[2][0];
    this->matrix[1][2] = this->matrix[2][1];

    this->matrix[1][0] = a01;
    this->matrix[2][0] = a02;
    this->matrix[2][1]= a12;

}

// Matrix for rotations
void Matrix3d::rotMatrix(double phi)
{
    this->matrix[0][0] = cos(phi);
    this->matrix[0][1]= +sin(phi);
    this->matrix[1][1] = cos(phi);
    this->matrix[1][0]= -sin(phi);
    this->matrix[2][2] = 1;

}

void Matrix3d::transMatrix(double Dx, double Dy)
{
    this->setIdentity();
    this->matrix[2][0] = Dx;
    this->matrix[2][1] = Dy;
}
void Matrix3d::scalMatrix(double Sx, double Sy)
{
    this->setIdentity();
    this->matrix[0][0] = Sx;
    this->matrix[1][1] = Sy;
}

// Matrix for coordinate transformations
void Matrix3d::cordRot(double phi)
{
    this->matrix[0][0] = cos(phi);
    this->matrix[0][1]= -sin(phi);
    this->matrix[1][1] = cos(phi);
    this->matrix[1][0]= +sin(phi);
    this->matrix[2][2] = 1;
}


/*
/// Vector3d
Vector3d::Vector3d(){
    col = 1;
    row = 3;
};

///Mixed operators

 Vector3d Vector3d::operator*(const Matrix3d& m){
    //Check if dimensions match
    assert((this->col == m.row ) && "Test");

    Vector3d temp;

    temp.matrix[0][0] = this->matrix[0][0]*m.matrix[0][0]+this->matrix[0][1]*m.matrix[1][0] +this->matrix[0][2]*m.matrix[2][0];
    temp.matrix[0][1] = this->matrix[0][0]*m.matrix[0][1]+this->matrix[0][1]*m.matrix[1][1] +this->matrix[0][2]*m.matrix[2][1];
    temp.matrix[2][0] = this->matrix[0][0]*m.matrix[0][2]+this->matrix[0][1]*m.matrix[1][2] +this->matrix[0][2]*m.matrix[2][2];

    return temp;

};

 Matrix3d Vector3d::operator *( const Vector3d& m){
    //Check for Dimensions
    assert((this->col == m.row ,"Dimension Mismatch for: v*M"));

    Matrix3d temp;
    temp.matrix[0][0] = m.matrix[0][0]*this->matrix[0][0]+m.matrix[1][0]*this->matrix[0][1] +m.matrix[2][0]*this->matrix[0][2];
    temp.matrix[1][0] = m.matrix[0][0]*this->matrix[1][0]+m.matrix[1][0]*this->matrix[1][1] +m.matrix[2][0]*this->matrix[1][2];
    temp.matrix[2][0] = m.matrix[0][0]*this->matrix[2][0]+m.matrix[1][0]* this->matrix[2][1]+m.matrix[2][0]*this->matrix[2][2];

    return temp;
};

Vector3d& Vector3d::operator =(Matrix3d& m){

   // Vector is 3x1
   this->setZero();
   this->matrix[0][0] = m.matrix[0][0];
   this->matrix[1][0] = m.matrix[1][0];
   this->matrix[2][0] = m.matrix[2][0];


    return *this;
};

void Vector3d::transpose(){

    //Switch col and row
    int temp = this->row;
    this->row = this->col;
    this->col = temp;
    //Switch values and set others 0
    double a,b;
    a = this->matrix[0][1];
    b = this->matrix[0][2];
    this->matrix[0][1] = this->matrix[1][0];
    this->matrix[0][2] = this->matrix[2][0];
    this->matrix[1][0] = a;
    this->matrix[1][0] = b;

};

void Vector3d::setIdentity(){

    this->matrix[0][0] = 1;
    this->matrix[1][0] = 1;
    this->matrix[2][0] = 1;
    this->matrix[0][1] = 1;
    this->matrix[0][2] = 1;

};

*/
