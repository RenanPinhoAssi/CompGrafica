#include "objectos2d.h"

BaseObject::BaseObject(){
    listSize = 0;
};

void BaseObject::set_Pos_In    (int listPos, Matrix3d arg_p){
    if(p_i.size()> listPos)
        p_i[listPos]=arg_p;
    else
        p_i.push_back(arg_p);
}

void BaseObject::set_Pos_Win(int listPos, Matrix3d arg_p){
    if(p_w.size()> listPos)
        p_w[listPos]=arg_p;
    else
        p_w.push_back(arg_p);
}
void BaseObject::set_Pos_Clip(int listPos, Matrix3d arg_p){
    if(p_w_clip.size()> listPos)
        p_w_clip[listPos]=arg_p;
    else
        p_w_clip.push_back(arg_p);
}

Matrix3d BaseObject::get_Pos_ini(int listPost ){
    if(p_i.size() > listPost)
        return p_i[listPost];
    else
        assert((false,"Trying to acess empty list"));
}

Matrix3d BaseObject::get_Pos_window(int listPost ){
    if(p_w.size() > listPost)
        return p_w[listPost];
    else
        assert((false,"Trying to acess empty list"));
}

Matrix3d BaseObject::get_Pos_clipped(int listPost){
    if(p_w_clip.size() > listPost)
        return p_w_clip[listPost];
    else
        assert((false,"Trying to acess empty list"));
}

void BaseObject::updateP_w(Matrix3d p_window){

   // assert(( p_i.size() == p_w.size() && 0 =! p_i, " Elements are epty"));

    for(int i = 0; i < p_i.size() ; i++){
        this->p_w[i] =  this->p_w[i] - p_window;
    }
}

//Object Points Functions
ObjectPoint::ObjectPoint(std::string arg_name){
    objName = arg_name;
    objType = ObjectPoint::POINT;
    listSize =0;
};

ObjectPoint::ObjectPoint(std::string arg_name, Matrix3d arg_pos_ini)
{
    objName = arg_name;
    p_i.push_back(arg_pos_ini);
    p_w.push_back(arg_pos_ini);
    p_w_clip.push_back(arg_pos_ini);
    objType = POINT;
};



///Line funtctions

ObjectLine::ObjectLine(std::string arg_name, Matrix3d pos_initial, Matrix3d pos_final){
    objName = arg_name;
    p_i.push_back(pos_initial);
    p_i.push_back(pos_final);
    p_w.push_back(pos_initial);
    p_w.push_back(pos_final);
    p_w_clip.push_back(pos_initial);
    p_w_clip.push_back(pos_final);
    objType = LINE;

  };


///Polygon Functions
ObjectPolygon::ObjectPolygon(std::string arg_name, Matrix3d pos_1, Matrix3d pos_2, Matrix3d pos_3){

    objName = arg_name;
    p_i.push_back(pos_1);
    p_i.push_back(pos_2);
    p_i.push_back(pos_3);
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
