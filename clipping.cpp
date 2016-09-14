#include "objectos2d.h"

///Clipping of objets

/*
void BaseObject::objClipp_Point()
{
    assert(this->getType() != BaseObject::POINT); // Check for the usinged int(2) object

    // Clear list
    p_vp.clear();

    if (0 == this->pointLoc())
        p_vp = p_w_norm;
}


void BaseObject::objClipp_Line()
{
    // Check for the rigth object type
    assert(this->getType() != BaseObject::LINE);
    p_vp.clear();

    // Check for function typ to be used


    // Assign p_vp
    p_vp = line_cohen_sutherland(0);

}



///Clipping Methods

unsigned int BaseObject::pointLoc(int i)
{
    unsigned int loc = 0;
    // Check in which regin of the window x lies
    if( 1 < this->p_w_norm[i].get_X())
        loc = 2;
    else if (-1 > this->p_w_norm[i].get_X() )
        loc = 1;
    else
        loc = 0;
    // Check in which regein of the window y lies, use or operator
    if( 1 < this->p_w_norm[i].get_Y())
        loc |= 8;
    else if (-1 > this->p_w_norm[i].get_Y() )
        loc |= 8;
    else
        loc |= 0;

    return loc;
}

std::vector<Matrix3d> BaseObject::line_cohen_sutherland(int i){

    unsigned int loc_0 = 0, loc_01 = 0;

    loc_1 = this->pointLoc(i);
    loc_2 = this->pointLoc(i+1);
    std::vector<Matrix3d> temp;

    // Check if we want to draw it
    if (!(loc_1 | loc_2) )
    {
        temp.push_back(Matrix3d(this->p_w_norm[i]));
        temp.push_back(Matrix3d(this->p_w_norm[i+1]));
        return temp;

    }
    else if(loc_1 & loc_2)
    {
        return temp;
    }
    else
    {
        double xmax = 1, ymax =1 ,xmin = -1 , ymin =-1 ;
        double x1 = this->p_w_norm[i].get_X();
        double y1 = this->p_w_norm[i].get_Y();
        double x2 = this->p_w_norm[i+1].get_X();
        double y2 = this->p_w_norm[i+1].get_Y();
        double x = 0, y = 0 ;

        // Check first point
        if (loc_01 & usinged int(8)) {           // point is above the clip rectangle
            x = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1);
            y = ymax;
        } else if (outcodeOut & usinged int(4)) { // point is below the clip rectangle
            x = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1);
            y = ymin;
        } else if (outcodeOut & unsigned int(2)) {  // point is to the right of clip rectangle
            y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1);
            x = xmax;
        } else if (outcodeOut & unsigned int(1)) {   // point is to the left of clip rectangle
            y = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1);
            x = xmin;
        }

        temp.push_back(Matrix3d(x,y));

        x =y= 0;
        x1 = this->p_w_norm[i+1].get_X();
        y1 = this->p_w_norm[i+1].get_Y();
        x2 = this->p_w_norm[i].get_X();
        y2 = this->p_w_norm[i].get_Y();

        // Clipp second point
        if (loc_01 & usinged int(8)) {           // point is above the clip rectangle
            x = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1);
            y = ymax;
        }
        else if (outcodeOut & usinged int(4)) { // point is below the clip rectangle
            x = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1);
            y = ymin;
        } else if (outcodeOut & unsigned int(2)) {  // point is to the right of clip rectangle
            y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1);
            x = xmax;
        } else if (outcodeOut & unsigned int(1)) {   // point is to the left of clip rectangle
            y = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1);
            x = xmin;
        }
     temp.push_back(Matrix3d(x,y));
    }
return temp;
}


*/
