#ifndef OBJECTOS2D_H
#define OBJECTOS2D_H
#include <vector>
#include <string>
#include "VectorMath.h"
#include "gtk/gtk.h"
#include "ListaEnc.h"

//Forward Def of Struct
class BaseObject;

typedef struct {
    GtkWidget *myWindow;
    GtkTreeModel *objModel;
    GtkWidget *objView;
    GtkListStore  *objStore;
    ListaEnc<BaseObject> objBuffer;
    Matrix3d pos_window;    // [ x_w , y_w, 1]  [ x_w_min, x_w_max , 1] [ y_w_min , y_w_max, 1]
    Matrix3d viewUp;            // [ u_x, u_y, 1] [ v_x, v_y, 1] [ 0, 0, 1]
    double x_vp_min;
    double x_vp_max;
    double y_vp_min;
    double y_vp_max;
    double teta;        // angle between (I)e_y and u
} DisplayFile;


class BaseObject
{
public:
    enum object_type{POINT,LINE, POLYGON};
    object_type objType;
    std::string objName;
    int listSize;

    std::vector<Matrix3d> p_i;                                           // Postion given in initial frame
    std::vector<Matrix3d> p_w_norm;                                          //position is given in window frame
    std::vector<Matrix3d> p_vp;                                        // potion given in window fram and clipped


    BaseObject();
    BaseObject(object_type objType, std::string arg_name);
    // Constructor for initial

    void setObject( object_type arg_objType );

    void add_Pos_In( Matrix3d p_1){p_i.push_back(p_1);}
   // void add_Pos_Win( Matrix3d p_1){p_norm.push_back(p_1);}
    //void add_Pos_Clip( Matrix3d p_1){p_w_clip.push_back(p_1);}

    void set_Pos_In(int lisPos, Matrix3d p_1);
    void set_Pos_Win(int lisPos, Matrix3d p_1);
    void set_Pos_Clip(int lisPos, Matrix3d p_1);

    Matrix3d get_Pos_ini(int listPos);
    Matrix3d get_Pos_window(int listPos);
    Matrix3d get_Pos_clipped(int listPos);
    object_type getType(){return objType;}

    // Object Manipulation
    void updateObjects(DisplayFile *pointer);
    void updateP_w_norm(DisplayFile *pointer);
    void updateViewPort(DisplayFile *pointer);

    double vpTransX( DisplayFile *pointer, double x_w);
    double vpTransY( DisplayFile *pointer, double y_w);
    double get_Cx();
    double get_Cy();

    // Object 2D transformations
    void translation( double Dx, double Dy );
    void scaling(double Sx, double Sy );
    void rotAround_Initial( double phi );
    void rotAround_GeoCenter( double phi);
    void rotAround_Point( Matrix3d point, double phi);

    // Clipping Methods
    std::vector<Matrix3d> line_clipp_Lian_Barsky(Matrix3d pos1 , Matrix3d pos2);


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
public:
    ObjectPolygon(std::string arg_name, std::vector<Matrix3d> positions);
    ObjectPolygon(std::string arg_name, Matrix3d pos_1, Matrix3d pos_2, Matrix3d pos_3);
    ObjectPolygon(std::string arg_name, Matrix3d pos_1, Matrix3d pos_2, Matrix3d pos_3, Matrix3d pos_4);


};



#endif // OBJECTOS2D_H
