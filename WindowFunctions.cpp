#include "WindowFunctions.h"
/*

static void   zoomIn (GtkWidget *widget, DisplayFile *pointer)
{
    pointer->pos_window.matrix[1][2] = 0.9*pointer->pos_window.matrix[1][2];
    pointer->pos_window.matrix[2][2] = 0.9*pointer->pos_window.matrix[2][2];
    pointer->pos_window.matrix[1][0] = pointer->pos_window.get_X()-pointer->pos_window.matrix[1][2];
    pointer->pos_window.matrix[1][1] = pointer->pos_window.get_X()+pointer->pos_window.matrix[1][2];
    pointer->pos_window.matrix[2][0] = pointer->pos_window.get_X()-pointer->pos_window.matrix[2][2];
    pointer->pos_window.matrix[2][1] = pointer->pos_window.get_Y()-pointer->pos_window.matrix[2][2];
}

static void   zoomOut (GtkWidget *widget, DisplayFile *pointer)
{
    pointer->pos_window.matrix[1][2] = 1.2*pointer->pos_window.matrix[1][2];
    pointer->pos_window.matrix[2][2] = 1.1*pointer->pos_window.matrix[2][2];
    pointer->pos_window.matrix[1][0] = pointer->pos_window.get_X()-pointer->pos_window.matrix[1][2];
    pointer->pos_window.matrix[1][1] = pointer->pos_window.get_X()+pointer->pos_window.matrix[1][2];
    pointer->pos_window.matrix[2][0] = pointer->pos_window.get_X()-pointer->pos_window.matrix[2][2];
    pointer->pos_window.matrix[2][1] = pointer->pos_window.get_Y()-pointer->pos_window.matrix[2][2];
}

static void myMovimentLeft(GtkWidget *widget, DisplayFile *pointer)
{
    pointer->pos_window.matrix[0][0] += 20;
    //updateObjects(pointer);
    draw_all(widget, pointer);
}

static void myMovimentRigth(GtkWidget *widget, DisplayFile *pointer)
{
    pointer->pos_window.matrix[0][0] -= 20;
    //updateObjects(pointer);
    draw_all(widget, pointer);
}

static void myMovimentUp(GtkWidget *widget, DisplayFile *pointer)
{
    pointer->pos_window.matrix[0][1] += 20;
    //updateObjects(pointer);
    draw_all(widget, pointer);
}

static void myMovimentDown(GtkWidget *widget, DisplayFile *pointer)
{
    pointer->pos_window.matrix[0][1] -= 20;
    //updateObjects(pointer);
    draw_all(widget, pointer);
}

void draw_all(GtkWidget *widget, DisplayFile *pointer )
{
   clear_surface();
    cairo_t *cr;
    cr = cairo_create (surface);
    Elemento<BaseObject>* actualElement = pointer->objBuffer.getHead();

    // Temporary viewport variables for
    double x_vp = 0;
    double  y_vp = 0;
    for(int i = 0; i < pointer->objBuffer.myLength(); i++){
        x_vp = 0;
        x_vp = 0;
        if(actualElement->getInfo().getType() == BaseObject::POINT)
        {

            // get x_w
            x_vp = actualElement->getInfo().p_w[0].get_X();
            y_vp = actualElement->getInfo().p_w[0].get_Y();
            //Vieport transformation
            //x_vp = vpTransX(pointer, x_vp);
            //y_vp = vpTransY(pointer, y_vp);
            //Draw point
            cairo_rectangle (cr, actualElement->getInfo().p_w[0].get_X() , actualElement->getInfo().p_w[0].get_Y(), 4, 4);
            cairo_fill (cr);
            //gtk_widget_queue_draw_area (widget, pointer->pos_window.get_X(), pointer->pos_window.get_Y(), 600, 600);
            //Get next elemnt
            actualElement = actualElement->getProximo();
        }
        else if(actualElement->getInfo().getType() == BaseObject::LINE)
        {
            cairo_set_line_width(cr, 0.5);
            // get x_w
            x_vp = actualElement->getInfo().p_w[0].get_X();
            y_vp = actualElement->getInfo().p_w[0].get_Y();
            //Vieport transformation
            // x_vp = vpTransX(pointer, x_vp);
            // y_vp = vpTransY(pointer, y_vp);
            //Draw point
            cairo_move_to(cr,x_vp, y_vp);
            // get x_w
            x_vp = actualElement->getInfo().p_w[1].get_X();
            y_vp = actualElement->getInfo().p_w[1].get_Y();
            //Vieport transformation
            //x_vp = vpTransX(pointer, x_vp);
            //y_vp = vpTransY(pointer, y_vp);
            //Draw point
            cairo_line_to(cr,x_vp,y_vp);
            cairo_stroke(cr);
            //Move back to window centre
            cairo_move_to(cr,pointer->pos_window.get_X(),pointer->pos_window.get_Y());

            // Get next elemnt
            actualElement = actualElement->getProximo();
        }
        else if(actualElement->getInfo().getType() == BaseObject::POLYGON)
        {   /*
            for(int i =0; i <)
            cairo_set_line_width(cr, 0.5);
            cairo_move_to(cr,actualElement->getInfo().p_w[0].get_X(),actualElement->getInfo().p_w[0].get_Y());
            cairo_line_to(cr,actualElement->getInfo().p_w[1].get_X(),actualElement->getInfo().p_w[1].get_Y());
            cairo_stroke(cr);
            cairo_move_to(cr,0,0);

        }
        else
        {}
        // Drawing in the viewport area
        gtk_widget_queue_draw_area (widget, pointer->x_vp_min, pointer->y_vp_min,pointer->x_vp_max , pointer->y_vp_max);
    }
    //gtk_widget_queue_draw_area (widget,pointer->pos_window.get_X(), pointer->pos_window.get_Y(), 600, 600);
    cairo_destroy (cr);
}



static gboolean   draw_cb (GtkWidget *widget,  cairo_t   *cr,   gpointer   data)
{
    cairo_set_source_surface (cr, surface, 0, 0);
    cairo_paint (cr);

    return FALSE;
}


static void   draw_brush (GtkWidget *widget,   gdouble    x,   gdouble    y)
{
    cairo_t *cr;

    cr = cairo_create (surface);

    cairo_rectangle (cr, x - 3, y - 3, 50, 50);
    //cairo_fill (cr);
    cairo_stroke (cr);
    cairo_destroy (cr);

    gtk_widget_queue_draw_area (widget, x - 3, y - 3, 50, 50);
}

static gboolean    button_press_event_cb (GtkWidget      *widget,   GdkEventButton *event,  gpointer  data)
{

    if (surface == NULL)
        return FALSE;

    if (event->button == 1)
    {
        draw_brush (widget, event->x, event->y);
    }
    else if (event->button == 3)
    {
        clear_surface ();
        gtk_widget_queue_draw (widget);
    }

    return TRUE;
}

//
static gboolean    motion_notify_event_cb (GtkWidget  *widget,  GdkEventMotion *event, gpointer   data)
{
    int x, y;
    GdkModifierType state;

    if (surface == NULL)
        return FALSE;

    gdk_window_get_pointer (event->window, &x, &y, &state);

    if (state & GDK_BUTTON1_MASK)
        draw_brush (widget, x, y);

    return TRUE;
}

// Function that closes window and ends program
static void close_window (void)
{
    if (surface)
        cairo_surface_destroy (surface);

    gtk_main_quit ();
}

static void   add_Point (GtkWidget *widget, DisplayFile *pointer)
{
    double x = rand() % 600 + 1;
    double y = rand() % 600 + 1;
    BaseObject* ponto = new ObjectPoint("Name",Matrix3d(x,y));
    Elemento<BaseObject>* container = new Elemento<BaseObject>;
    container->setInfo(*ponto);

    pointer->objBuffer.adicionaNoInicio(*container);

    draw_all(widget, pointer);
}


static void   add_Line (GtkWidget *widget, DisplayFile *pointer)
{

    int xI = rand() % 600 + 1;
    int yI = rand() % 600 + 1;
    int xF = rand() % 600 + 1;
    int yF = rand() % 600 + 1;

    BaseObject* line = new ObjectLine("Name",Matrix3d(xI,yI),Matrix3d(xF,yF));
    Elemento<BaseObject>* container = new Elemento<BaseObject>;
    container->setInfo(*line);
    pointer->objBuffer.adicionaNoInicio(*container);
    draw_all(widget, pointer);
}


//clears canvas
static void  clear_surface ()
{
    cairo_t *cr;

    cr = cairo_create (surface);

    cairo_set_source_rgb (cr, 1, 1, 1);
    cairo_paint (cr);

    cairo_destroy (cr);
}


static gboolean    press_draw_line (GtkWidget  *widget,  GdkEventMotion *event, gpointer   data)
{
    int x, y;
    GdkModifierType state;

    if (surface == NULL)
        return FALSE;

    gdk_window_get_pointer (event->window, &x, &y, &state);

    if (state & GDK_BUTTON1_MASK)
        draw_brush (widget, x, y);

    return TRUE;


}

static void myMoviment(GtkWidget *widget, DisplayFile *pointer){
    //cairo_t *cr;
    //cr = cairo_create (surface);
    // Elemento<ObjectPoint>* actualElement = pointer->objBuffer.getHead();
    //std::cout << (actualElement->getInfo().getX());
    //for(int i = 0; i < pointer->objBuffer.myLenagth(); i++){
    // actualElement->getInfo().setShiftX(5);
    //cairo_rectangle (cr, actualElement->getInfo().x, actualElement->getInfo().y, 4, 4);
    //cairo_fill (cr);
    //gtk_widget_queue_draw_area (widget, actualElement->getInfo().x, actualElement->getInfo().y, 600, 600);
    // actualElement = actualElement->getProximo();
    //}
    //cairo_destroy (cr);
}

//
static gboolean  configure_event_cb (GtkWidget  *widget,  GdkEventConfigure *event,  gpointer   data)
{
    if (surface)
        cairo_surface_destroy (surface);

    surface = gdk_window_create_similar_surface (gtk_widget_get_window (widget),
                                                 CAIRO_CONTENT_COLOR,
                                                 gtk_widget_get_allocated_width (widget),
                                                 gtk_widget_get_allocated_height (widget));

    clear_surface ();

    return TRUE;
}


*/
