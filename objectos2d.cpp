#include "objectos2d.h"

BaseObject::BaseObject(){
    listSize = 0;
};


Matrix3d BaseObject::get_Pos_ini(int listPost ){
    if(p_i.size() > listPost)
        return p_i[listPost];
    else
        assert((false,"Trying to acess empty list"));
}

Matrix3d BaseObject::get_Pos_window(int listPost ){
    if(p_w_norm.size() > listPost)
        return p_w_norm[listPost];
    else
        assert((false,"Trying to acess empty list"));
}

Matrix3d BaseObject::get_Pos_clipped(int listPost){
    if(p_w_norm.size() > listPost)
        return p_w_norm[listPost];
    else
        assert((false,"Trying to acess empty list"));
}

void BaseObject::updateP_w_norm(DisplayFile *pointer)
{
    //Check for empty object or misnmatch of dimension
    assert(( this->p_i.size() == this->p_w_norm.size() , " Elements are epty"));
    assert((   this->p_w_norm.size() != 0 , " List is empty"));

    // Update teta
    pointer->teta = atan2(pointer->viewUp.matrix[1][0] ,pointer->viewUp.matrix[1][1]);

    Matrix3d cRot;
    cRot.cordRot(pointer->teta);
    double alpha = 1/pointer->pos_window.matrix[1][2];
    double beta = 1/pointer->pos_window.matrix[2][2];


    // Transformation from initial cord to window cord for Points of the object
    for(int i = 0; i < p_i.size() ; i++){

        // Translation to window center P_w_0
        this->p_w_norm[i].set_X(  this->p_i[i].get_X() - pointer->pos_window.get_X());
        this->p_w_norm[i].set_Y(  this->p_i[i].get_Y() - pointer->pos_window.get_Y());

        // Cord Tranformation of all points from Intial frame to Window frame
        this->p_w_norm[i] = this->p_w_norm[i]*cRot;

        // Normalaize cord
        p_w_norm[i].set_X( alpha*this->p_w_norm[i].get_X());
        p_w_norm[i].set_Y(beta*this->p_w_norm[i].get_Y());
        p_w_norm[i].matrix[0][2] = 1;
    }
}

void BaseObject::updateViewPort(DisplayFile *pointer)
{
    for( int i=0; i < this->p_w_norm.size(); i++)
    {
        this->p_vp[i].matrix[0][0] = vpTransX(pointer,p_w_norm[i].get_X());
        this->p_vp[i].matrix[0][1] =vpTransY(pointer,p_w_norm[i].get_Y());
        p_w_norm[i].matrix[0][2] = 1;
    }
}

//Viewpoint transformation
double BaseObject::vpTransX( DisplayFile *pointer, double x_w)
{
    double x_w_max = 1;//pointer->pos_window.matrix[1][1];
    double x_w_min = -1;//pointer->pos_window.matrix[1][0];
    double x_vp_max = pointer->x_vp_max;
    double x_vp_min = pointer->x_vp_min;
    double x_vp = ((x_w - x_w_min)/(x_w_max-x_w_min) *(x_vp_max - x_vp_min));
    //x_vp = x_vp + x_vp_min;
    return  x_vp;
}

double BaseObject::vpTransY( DisplayFile *pointer, double y_w)
{
    double y_w_max = 1;//pointer->pos_window.matrix[2][1];
    double y_w_min = -1;//pointer->pos_window.matrix[2][0];
    double y_vp_min = pointer->y_vp_min;
    double y_vp_max = pointer->y_vp_max;
    double y_vp = ((1-(y_w - y_w_min)/(y_w_max-y_w_min)) *(y_vp_max -y_vp_min));
    //y_vp += y_vp_min;
    return y_vp;
};

void BaseObject::updateObjects(DisplayFile *pointer){

    std::cout << "P_i: " <<  "x:  " << p_i[0].get_X() << "        y:  "  <<p_i[0].get_Y() << std::endl;
    //Calculate p_w from pos_window
    std::cout << "p_w_norm: " <<  "x:  " <<p_w_norm[0].get_X() << "        y:  " << p_w_norm[0].get_Y() << std::endl;
    this->updateP_w_norm(pointer);
    //Calculate viewport
    this->updateViewPort(pointer);
    std::cout << "p_vp: " <<   "x:  " <<p_vp[0].get_X() << "        y:  " << p_vp[0].get_Y() << std::endl;

}

/// Transation Matrixes


double BaseObject::get_Cx()
{
    int c_x = 0;

    for(int i = 0; i < this->p_i.size(); i++ )
    {
        c_x += this->p_i[i].get_X();
    }
    return c_x = (c_x/this->p_i.size());
}

double BaseObject::get_Cy()
{
    int c_y = 0;

    for(int i = 0; i < this->p_i.size(); i++ )
    {
        c_y += this->p_i[i].get_Y();
    }
    return c_y = (c_y/this->p_i.size());
}

void BaseObject::translation( double Dx, double Dy ){

    // Generate translation matrix
    Matrix3d trans;
    trans.transMatrix(Dx,Dy);

    for(int i = 0; i < this->p_i.size(); i++ )
    {
        this->p_i[i] = this->p_i[i] *trans;
    }
}

void BaseObject::scaling( double Sx, double Sy ){

    //Get c_x, c_y ( Geometric center of object)
    int cx = this->get_Cx();
    int cy = this->get_Cy();

    // Translation to centre of origin
    this->translation(-cx,-cy);

    // Define the Scaling Marix S
    Matrix3d S;
    S.scalMatrix(Sx,Sy);

    // Scale all objects
    for(int i = 0; i < this->p_i.size(); i++ )
    {
        this->p_i[i] = this->p_i[i] *S;
    }
    // Translation back to original position
    this->translation(cx,cy);
}

void BaseObject::rotAround_Initial( double phi){

    //Define the rotation matrix
    Matrix3d Rot, temp;
    Rot.rotMatrix(phi);

    //Calculate rotated point
    for(int i = 0; i < this->p_i.size(); i++ )
    {
        temp = this->p_i[i] *Rot;
        this->p_i[i] = temp;
        temp.setZero();
    }
}

void BaseObject::rotAround_GeoCenter(double phi)
{
    //Get c_x, c_y ( Geometric center of object)
    int cx = this->get_Cx();
    int cy = this->get_Cy();

    // Translation to centre of origin
    this->translation(-cx,-cy);

    // Rotate around origin
    this->rotAround_Initial(phi);

    // Translation back to original position
    this->translation(cx,cy);
}

void BaseObject::rotAround_Point( Matrix3d point, double phi){

    //Get c_x, c_y ( Geometric center of object)
    int xp = point.get_X();
    int yp = point.get_Y();

    // Translation to centre of origin
    this->translation(-xp,-xp);

    // Rotate around origin
    this->rotAround_Initial(phi);

    // Translation back to original position
    this->translation(xp,xp);
};


///Object Points Functions
ObjectPoint::ObjectPoint(std::string arg_name){
    objName = arg_name;
    objType = ObjectPoint::POINT;
    listSize =0;
};

ObjectPoint::ObjectPoint(std::string arg_name, Matrix3d arg_pos_ini)
{
    objName = arg_name;
    p_i.push_back(arg_pos_ini);
    p_w_norm.push_back(arg_pos_ini);
    p_vp.push_back(arg_pos_ini);
    objType = POINT;
};



///Line funtctions

ObjectLine::ObjectLine(std::string arg_name, Matrix3d pos_initial, Matrix3d pos_final){
    objName = arg_name;
    p_i.push_back(pos_initial);
    p_i.push_back(pos_final);
    p_w_norm.push_back(pos_initial);
    p_w_norm.push_back(pos_final);
    p_vp.push_back(pos_initial);
    p_vp.push_back(pos_final);
    objType = LINE;

};


///Polygon Functions
ObjectPolygon::ObjectPolygon(std::string arg_name, std::vector<Matrix3d> positions){

    objName = arg_name;
    for(int i = 0; i < positions.size(); i++){
        p_i.insert(p_i.begin(),positions.at(i));
    }
    p_w_norm =  p_vp = p_i;
    objType = POLYGON;

}

ObjectPolygon::ObjectPolygon(std::string arg_name, Matrix3d pos_1, Matrix3d pos_2, Matrix3d pos_3){

    objName = arg_name;
    p_i.push_back(pos_1);
    p_i.push_back(pos_2);
    p_i.push_back(pos_3);
    p_w_norm =  p_vp = p_i;
    objType = POLYGON;

}

ObjectPolygon::ObjectPolygon(std::string arg_name, Matrix3d pos_1, Matrix3d pos_2, Matrix3d pos_3, Matrix3d pos_4){

    objName = arg_name;
    p_i.push_back(pos_1);
    p_i.push_back(pos_2);
    p_i.push_back(pos_3);
    p_i.push_back(pos_4);
    p_w_norm =  p_vp = p_i;
    objType = POLYGON;

}




/*
void ObjectPoint::setObject( object_type arg_objType ){
    objType = arg_objType;
}
///
/// LINES
///

ObjectLine::ObjectLine()
{
    setObject(ObjectPoint::LINE);
    x_w = y_w = x_clip = y_clip = 0;
}

ObjectLine::ObjectLine(std::string arg_name)
{
    setObject(ObjectPoint::LINE);
    x_w = y_w = x_clip = y_clip = 0;
    objName=arg_name;
}

ObjectLine::ObjectLine(std::string arg_name, ObjectPoint arg_obj1, ObjectPoint arg_obj2){
    objName = arg_name;
    objType = LINE;
    pointList.push_back(arg_obj1);
    pointList.push_back(arg_obj2);
    pointList[0].objType = ObjectPoint::LINE;
    pointList[1].objType = ObjectPoint::LINE;
}

ObjectLine::ObjectLine(std::string arg_name, int positionXStart, int positionYStart, int positionXEnd, int positionYEnd) {
    objName = arg_name;
    objType = LINE;
    pointList.push_back(ObjectPoint(arg_name, positionXStart,positionYStart));
    pointList.push_back(ObjectPoint(arg_name, positionXEnd,positionYEnd));

};
/*
///
/// Polygons
///

ObjectPolygon::ObjectPolygon(std::string arg_name, ObjectPoint arg_obj1, ObjectPoint arg_obj2, ObjectPoint arg_obj3)
{
    objName = arg_name;
    object = POLYGON;

    pointList.push_back(arg_obj1);
    //pointList[pointList.end()].objType = POLYGON;
   // pointList[pointList.end()].objName = arg_name;

    pointList.push_back(arg_obj2);
    //pointList[pointList.end()].objType = POLYGON;
    //pointList[pointList.end()].objName = arg_name;

    pointList.push_back(arg_obj3);
    //pointList[pointList.end()].objName = arg_name;
    //pointList[pointList.end()].objType = POLYGON;
}


void ObjectPolygon::addNewVertex(int posX, int posY){

    pointList.push_back(ObjectPoint(" ",posX,posY));
    //pointList[pointList.end()].objType = POLYGON;
    //pointList[pointList.end()].objName = arg_name;
}

*/
