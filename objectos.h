#ifndef OBJECTOS2D_H
#define OBJECTOS2D_H
#include <vector>
#include <string>
#include "VectorMath.h"

class BaseObject
{
public:
    enum object_type{POINT,LINE, POLYGON};
    object_type objType;
    std::string objName;
    int listSize;

     std::vector<Matrix3d> p_i;                                           // Postion given in initial frame
     std::vector<Matrix3d> p_w;                                          //position is given in window frame
     std::vector<Matrix3d> p_w_clip;                                // potion given in window fram and clipped


     BaseObject();
     BaseObject(object_type objType, std::string arg_name);
     // Constructor for initial

     void setObject( object_type arg_objType );

     void add_Pos_In( Matrix3d p_1){p_i.push_back(p_1);}
     void add_Pos_Win( Matrix3d p_1){p_w.push_back(p_1);}
     void add_Pos_Clip( Matrix3d p_1){p_w_clip.push_back(p_1);}

     void set_Pos_In(int lisPos, Matrix3d p_1);
     void set_Pos_Win(int lisPos, Matrix3d p_1);
     void set_Pos_Clip(int lisPos, Matrix3d p_1);

     Matrix3d get_Pos_ini(int listPos);
     Matrix3d get_Pos_window(int listPos);
     Matrix3d get_Pos_clipped(int listPos);
     object_type getType(){return objType;}

     void updateP_w(Matrix3d p_window);

};

class ObjectPoint: public BaseObject
{
    public:
    //Default constructors -> note we alway require at least a name for the object
    ObjectPoint(std::string arg_name);
    ObjectPoint(std::string arg_name, Matrix3d pos_initial);
    //double getX_i(){return this->p_i[0].get_X();}


};

class ObjectLine: public BaseObject
{
 public:
ObjectLine(std::string arg_name, Matrix3d pos_initial, Matrix3d pos_final);


};

class ObjectPolygon: public BaseObject
{
ObjectPolygon(std::string arg_name, Matrix3d pos_1, Matrix3d pos_2, Matrix3d pos_3);


};


#endif // OBJECTOS2D_H
