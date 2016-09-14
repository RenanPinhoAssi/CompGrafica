#include "objectos2d.h"
#include "math.h"

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
std::vector<Matrix3d> BaseObject::line_clipp_Lian_Barsky(Matrix3d pos1 , Matrix3d pos2)
{

    std::vector<Matrix3d> arg_return;
    double x1,x2,y1,y2,xmin,xmax,ymin,ymax, u1, u2, dx, dy;
    double p[4], q[4],r[4] ;

    x1 = pos1.get_X();
    y1 = pos1.get_Y();
    x2 = pos2.get_X();
    y2 = pos2.get_Y();

    xmin  = -1;
    xmax = 1;
    ymin = -1;
    ymax = 1;

    dx = x2-x1;
    dy = y2 -y1;

    q[0] = -dx;
    q[1] =  dx;
    q[2] = -dy;
    q[3] =  dy;

    p[0] = x1- xmin;
    p[1] = xmax - x1;
    p[2]= y1 - ymin;
    p[3] = ymax - y1;


    r[0] = q[0]/p[0];
    r[1] = q[1]/p[1];
    r[2] = q[2]/p[2];
    r[3] = q[3]/p[3];

    // Chek if lines are completly outside or inside
    for(int i=0; i < 4 ;i++)
    {
        if(p[i]!=0)
        {
            r[i]=q[i]/p[i];
        }
        else if(p[i]==0 && q[i] < 0) // if true line completly outside window
        {
            return arg_return;
        }
        else if(p[i]==0 && q[i] >= 0) // If true line completly inside window
        {
            arg_return.push_back(pos1);
            arg_return.push_back(pos2);
            return arg_return;
        }
    }
    if (p[0] < 0 )
    {
        u1 = max(p[0],p[2]);
    }
    else{
        u1 = min(p[0], p[2]);
        u1 = min(1.0,u1);
    }

    if (p[1] < 0 )
    {
        u2 = max(p[1],p[3]);
    }
    else{
        u2 = min(p[1], p[3]);
        u2 = min(1.0,u2);
    }

    if (u1 < u2){
        arg_return.push_back(Matrix3d(x1+u1*dx,y1+u1*dy));
        arg_return.push_back(Matrix3d(x2+u2*dx,y1+u2*dy));
        return arg_return;
    }
    else
    {
        return arg_return;
    }
}


