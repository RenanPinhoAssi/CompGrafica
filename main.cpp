#include <gtk/gtk.h>
#include <cairo.h>
#include <stdlib.h>
#include "VectorMath.h"
#include "ListaEnc.h"
#include "objectos2d.h"
#include "WindowFunctions.h"
#include "test_tarefa_02.h"

cairo_surface_t *surface = NULL;
typedef struct { GtkWidget *widget; int x, y; } xy_t;



int main (int   argc, char *argv[])
{

    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *gridFrame;
    GtkWidget *frame;
    GtkWidget *button;
    GtkWidget *da;
    GtkCellRenderer     *renderer;
    GtkWidget           *scrolled_window;
    GtkTreeModel        *model;
    GtkListStore        *store;
    GtkWidget           *view;

    //Initialize global variable and frames
    int x_vp_min = 0, y_vp_min = 0 , x_vp_max = 0, y_vp_max =0;     // Variable for vieport
    int x_w_min = 0, y_w_min = 0, x_w_max = 0 , y_w_max = 0;  // Variable for window
    int wWidth =600, wHeigth = 600;


    //Set window at centre of world coordiantes
    x_w_min = -wWidth/2;
    x_w_max = wWidth/2;
    y_w_min = -wHeigth/2;
    y_w_max = wHeigth/2;

    //Set view port size (size of canvas)
    x_vp_min = 0;
    x_vp_max = wWidth;
    y_vp_min = 0;
    y_vp_max = wHeigth;

    gtk_init (&argc, &argv);

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "Drawing Area");

    gtk_container_set_border_width (GTK_CONTAINER (window), 8);
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 600);

    grid = gtk_grid_new();
    gtk_container_add (GTK_CONTAINER (window), grid);

    //Inizialisation of Displa
    DisplayFile displayFile;
    ListaEnc< BaseObject > objectList;
    displayFile.objBuffer = objectList;

    //Define window
    displayFile.pos_window.matrix[0][0] = 0;      // x_w
    displayFile.pos_window.matrix[0][1] = 0;      //y_w
    displayFile.pos_window.matrix[0][2] = 1;
    displayFile.pos_window.matrix[1][0] = -300; // x_w_min
    displayFile.pos_window.matrix[1][1] = 300; // x_w_max heigth
    displayFile.pos_window.matrix[1][2] = 300; // x_width /2
    displayFile.pos_window.matrix[2][0] = -300; // y_w_min width
    displayFile.pos_window.matrix[2][1] = 300; //y_w_max heigth
    displayFile.pos_window.matrix[2][2] = 300; // y_width /2
    displayFile.x_vp_min = 0;
    displayFile.y_vp_min = 0;
    displayFile.x_vp_max = 600;
    displayFile.y_vp_max = 600;
    displayFile.viewUp.matrix[0][0] =1;      // u_x
    displayFile.viewUp.matrix[0][1] = 0;      //u_y
    displayFile.viewUp.matrix[0][2] = 1;        // 1 for hc
    displayFile.viewUp.matrix[1][0] = 0; // v_x
    displayFile.viewUp.matrix[1][1] = 1; // v_y
    displayFile.viewUp.matrix[1][2] = 1; // 1
    displayFile.teta = 0;


    frame = gtk_frame_new ("Menu de funcoes");
    gtk_frame_set_shadow_type (GTK_FRAME (frame), GTK_SHADOW_IN);
    gtk_grid_attach (GTK_GRID (grid), frame, 0, 0, 20, 300);

    gridFrame = gtk_grid_new();
    gtk_container_add (GTK_CONTAINER (frame), gridFrame);

    // Adding Object: Points, Line and Polygon
    button = gtk_button_new_with_label (" Polygon");
    g_signal_connect (button, "clicked", G_CALLBACK(add_Polygon), (gpointer*)& displayFile);
    gtk_grid_attach (GTK_GRID (gridFrame), button, 4, 0, 2, 1);

    button = gtk_button_new_with_label (" Line");
    g_signal_connect (button, "clicked", G_CALLBACK(add_Line), (gpointer*)& displayFile);
    gtk_grid_attach (GTK_GRID (gridFrame), button, 2, 0, 2, 1);

    button = gtk_button_new_with_label (" Point");
    g_signal_connect (button, "clicked", G_CALLBACK(add_Point), (gpointer*)& displayFile);
    gtk_grid_attach (GTK_GRID (gridFrame), button, 0, 0, 2, 1);

    //  Buttons for movement
    button = gtk_button_new_with_label ("Up");
    gtk_grid_attach (GTK_GRID (gridFrame), button, 2, 10, 2, 1);
    g_signal_connect (button, "clicked", G_CALLBACK (myMovimentUp), (gpointer*)& displayFile);

    button = gtk_button_new_with_label ("Right");
    g_signal_connect (button, "clicked", G_CALLBACK (myMovimentRigth), (gpointer*)& displayFile);
    gtk_grid_attach (GTK_GRID (gridFrame), button, 4, 11, 2, 1);

    button = gtk_button_new_with_label ("Left");
    gtk_grid_attach (GTK_GRID (gridFrame), button, 0, 11, 2, 1);
    g_signal_connect (button, "clicked", G_CALLBACK (myMovimentLeft), (gpointer*)& displayFile);

    button = gtk_button_new_with_label ("Down");
    gtk_grid_attach (GTK_GRID (gridFrame), button, 2, 12, 2, 1);
    g_signal_connect (button, "clicked", G_CALLBACK (myMovimentDown), (gpointer*)& displayFile);

    button = gtk_button_new_with_label ("Zoom In");
    gtk_grid_attach (GTK_GRID (gridFrame), button, 3, 14, 3, 1);
    g_signal_connect (button, "clicked", G_CALLBACK (zoomIn), (gpointer*)& displayFile);

    button = gtk_button_new_with_label ("Zoom Out");
    gtk_grid_attach (GTK_GRID (gridFrame), button, 0, 14, 3, 1);
    g_signal_connect (button, "clicked", G_CALLBACK (zoomOut), (gpointer*)& displayFile);

    button = gtk_button_new_with_label (" + Rot Window");
    gtk_grid_attach (GTK_GRID (gridFrame), button, 3, 16, 3, 1);
    g_signal_connect (button, "clicked", G_CALLBACK (rot_window_pos), (gpointer*)& displayFile);

    button = gtk_button_new_with_label ("- Rot Window");
    gtk_grid_attach (GTK_GRID (gridFrame), button,  0, 16, 3, 1);
    g_signal_connect (button, "clicked", G_CALLBACK (rot_window_neg), (gpointer*)& displayFile);

    button = gtk_button_new_with_label ("byGeo Rot");
    gtk_grid_attach (GTK_GRID (gridFrame), button,  0, 20, 2, 1);
    g_signal_connect (button, "clicked", G_CALLBACK (rot_obj), (gpointer*)& displayFile);

    button = gtk_button_new_with_label ("byPoint Rot");
    gtk_grid_attach (GTK_GRID (gridFrame), button,  4, 22, 2, 1);
    g_signal_connect (button, "clicked", G_CALLBACK (rotP_obj), (gpointer*)& displayFile);

    button = gtk_button_new_with_label ("byInitial Rot");
    gtk_grid_attach (GTK_GRID (gridFrame), button,  0, 22, 2, 1);
    g_signal_connect (button, "clicked", G_CALLBACK (rotI_obj), (gpointer*)& displayFile);

    button = gtk_button_new_with_label ("Transalation");
    gtk_grid_attach (GTK_GRID (gridFrame), button,  2, 20, 2, 1);
    g_signal_connect (button, "clicked", G_CALLBACK (trans_obj), (gpointer*)& displayFile);

    button = gtk_button_new_with_label ("Scaling");
    gtk_grid_attach (GTK_GRID (gridFrame), button,  4, 20, 2, 1);
    g_signal_connect (button, "clicked", G_CALLBACK (esca_obj), (gpointer*)& displayFile);



    frame = gtk_frame_new ("Viewport");
    gtk_frame_set_shadow_type (GTK_FRAME (frame), GTK_SHADOW_IN);
    gtk_widget_set_size_request (frame, wWidth, wHeigth);
    gtk_grid_attach (GTK_GRID (grid), frame, 21, 0, wWidth, wHeigth);


    da = gtk_drawing_area_new ();
    gtk_container_add (GTK_CONTAINER (frame), da);


    //////////// WINDOW SCROLLABLE
    view = gtk_tree_view_new ();
    store = gtk_list_store_new (NUM_COLS, G_TYPE_STRING, G_TYPE_STRING);

    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),-1,"Object",renderer,"text", COL_OBJ,NULL);

    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),-1,"Name",renderer,"text", COL_NAME,NULL);


    scrolled_window = gtk_scrolled_window_new (NULL, NULL);
    gtk_container_set_border_width (GTK_CONTAINER (scrolled_window), 10);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);


    scrolled_window = gtk_scrolled_window_new (NULL, NULL);

    gtk_container_set_border_width (GTK_CONTAINER (scrolled_window), 10);

    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);

    gtk_grid_attach (GTK_GRID (gridFrame), scrolled_window, 0, 18, 6, 1);
    gtk_widget_show (scrolled_window);

    GtkWidget *table;
    table = gtk_table_new (10, 10, FALSE);
    gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (scrolled_window), table);
    gtk_widget_show (table);

    gtk_widget_set_size_request(scrolled_window,NULL,100);
    gtk_table_attach_defaults (GTK_TABLE (table), view, 0, 10, 0, 10);

    displayFile.objModel = model;
    displayFile.objStore = store;
    displayFile.objView = view;
    //////////// WINDOW SCROLLABLE END



    g_signal_connect (da, "draw", G_CALLBACK (draw_cb), NULL);
    g_signal_connect (da,"configure-event", G_CALLBACK (configure_event_cb), NULL);
    g_signal_connect (da, "motion-notify-event", G_CALLBACK (motion_notify_event_cb), NULL);
    //g_signal_connect (da, "drawRectangle", G_CALLBACK (draw_rec), NULL);

    gtk_widget_set_events (da, gtk_widget_get_events (da)
                           //| GDK_BUTTON_PRESS_MASK
                           | GDK_POINTER_MOTION_MASK
                           | GDK_POINTER_MOTION_HINT_MASK);

    //test_02(&displayFile);

    gtk_widget_show_all (window);
    gtk_main ();



    return 0;
};
