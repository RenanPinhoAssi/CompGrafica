#ifndef WINDOWFUNCTIONS_H
#define WINDOWFUNCTIONS_H
#include <gtk/gtk.h>
#include <cairo.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <iterator>
#include <string>
#include "objectos2d.h"
#include "ListaEnc.h"


extern  cairo_surface_t *surface;

enum{COL_OBJ = 0,COL_NAME, NUM_COLS} ;
//Zooms in
static void zoomIn (GtkWidget *widget, DisplayFile *pointer);
static void zoomOut (GtkWidget *widget, DisplayFile *pointer);

// Movement functions
static void myMovimentLeft(GtkWidget *widget, DisplayFile *pointer);
static void myMovimentRigth(GtkWidget *widget, DisplayFile *pointer);
static void myMovimentUp(GtkWidget *widget, DisplayFile *pointer);
static void myMovimentDown(GtkWidget *widget, DisplayFile *pointer);

//Draw functions
static void draw_all(GtkWidget *widget, DisplayFile *pointer);
static void   add_Point (GtkWidget *widget, DisplayFile *pointer);
static void   add_Line (GtkWidget *widget, DisplayFile *pointer);
static void   add_Polygon (GtkWidget *widget, DisplayFile *pointer);


//GTK functions
static gboolean    button_press_event_cb (GtkWidget      *widget,   GdkEventButton *event,  gpointer  data);
static gboolean    motion_notify_event_cb (GtkWidget  *widget,  GdkEventMotion *event, gpointer   data);
static gboolean  configure_event_cb (GtkWidget  *widget,  GdkEventConfigure *event,  gpointer   data);
static void   draw_brush (GtkWidget *widget,   gdouble    x,   gdouble    y);
static gboolean   draw_cb (GtkWidget *widget,  cairo_t   *cr,   gpointer   data);
static void  clear_surface ();
static void close_window ( );


static void create_and_fill_model (GtkTreeModel *model, GtkWidget *view, GtkListStore  *store, char *ObjectType, char *name){
  GtkTreeIter    iter;


  /* Append a row and fill in some data */
  gtk_list_store_append (store, &iter);
  gtk_list_store_set (store, &iter, COL_OBJ, ObjectType, COL_NAME, name,  -1);
  model = GTK_TREE_MODEL (store);

  gtk_tree_view_set_model (GTK_TREE_VIEW (view), model);
}



static char* show_name_entry_dialog()
{
    GtkWidget *dialog;
    GtkWidget *entry;
    GtkWidget *content_area;
    GtkWidget *table,*label;
    std::string entry_text;

    dialog = gtk_dialog_new();
    gtk_dialog_add_button(GTK_DIALOG(dialog), "OK", 0);
    gtk_dialog_add_button(GTK_DIALOG(dialog), "CANCEL", 1);

    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    table = gtk_table_new (2, 2, TRUE);
    gtk_container_add (GTK_CONTAINER (content_area), table);

    label = gtk_label_new ("Object Name:" );
    gtk_table_set_homogeneous(GTK_TABLE (table), TRUE);
    gtk_table_attach_defaults (GTK_TABLE (table), label, 0, 1, 0, 1);

    entry = gtk_entry_new();
    gtk_entry_set_max_length (GTK_ENTRY (entry),0);
    gtk_table_attach_defaults (GTK_TABLE (table), entry, 1, 2, 0, 1);

    gtk_widget_show_all(dialog);
    gint result = gtk_dialog_run(GTK_DIALOG(dialog));

    switch(result){
        case 0:
            cout << "OK was clicked\n";
            entry_text = gtk_entry_get_text(GTK_ENTRY(entry));
            break;
        case 1:
            cout << "CANCEL was clicked\n"; break;
        default:
            cout << "Undefined. Perhaps dialog was closed\n"; break;
    }

    gtk_widget_destroy(dialog);

    char *cName = new char[entry_text.length() + 1];
    std::copy(entry_text.begin(), entry_text.end(), cName);
    cName[entry_text.size()] = '\0';

    return cName;
}
static std::vector<int> show_cord_entry_dialog()
{
    GtkWidget *dialog;
    GtkWidget *entry;
    GtkWidget *entry2;
    GtkWidget *content_area;
    GtkWidget *table,*label;
    std::vector<int> cord(3);


    dialog = gtk_dialog_new();
    gtk_dialog_add_button(GTK_DIALOG(dialog), "OK", 0);
    gtk_dialog_add_button(GTK_DIALOG(dialog), "CANCEL", 1);


    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));


    table = gtk_table_new (2, 2, TRUE);
    gtk_container_add (GTK_CONTAINER (content_area), table);

    label = gtk_label_new ("X Value:" );
    gtk_table_set_homogeneous(GTK_TABLE (table), TRUE);
    gtk_table_attach_defaults (GTK_TABLE (table), label, 0, 1, 0, 1);

    label = gtk_label_new ("Y Value:" );
    gtk_table_set_homogeneous(GTK_TABLE (table), TRUE);
    gtk_table_attach_defaults (GTK_TABLE (table), label, 0, 1, 1, 2);



    entry = gtk_entry_new();
    gtk_entry_set_max_length (GTK_ENTRY (entry),0);
    gtk_table_attach_defaults (GTK_TABLE (table), entry, 1, 2, 0, 1);

    entry2 = gtk_entry_new();
    gtk_entry_set_max_length (GTK_ENTRY (entry2),0);
    gtk_table_attach_defaults (GTK_TABLE (table), entry2, 1, 2, 1, 2);

    gtk_widget_show_all(dialog);
    gint result = gtk_dialog_run(GTK_DIALOG(dialog));


    string entryX = ""; // variable for entered text
    string entryY = "";
    int x = 0;
    int y = 0;
    int fakeBin = 0;

    switch(result){
        case 0:
            cout << "OK was clicked\n";
            entryX = gtk_entry_get_text(GTK_ENTRY(entry));
            entryY = gtk_entry_get_text(GTK_ENTRY(entry2));
            fakeBin = 1;
            break;
        case 1:
            cout << "CANCEL was clicked\n"; break;
        default:
            cout << "Undefined. Perhaps dialog was closed\n"; break;
    }
    x = atoi(entryX.c_str());
    y = atoi(entryY.c_str());
    cord.at(0) = x;
    cord.at(1) = y;
    cord.at(2) = fakeBin;

    gtk_widget_destroy(dialog);

    return cord;
}
/*
static std::vector<int> show_recur_cord_entry_dialog()
{
    GtkWidget *dialog;
    GtkWidget *entry;
    GtkWidget *entry2;
    GtkWidget *content_area;
    GtkWidget *table,*label;
    std::vector<int> cord(2);


    dialog = gtk_dialog_new();
    gtk_dialog_add_button(GTK_DIALOG(dialog), "OK", 0);
    gtk_dialog_add_button(GTK_DIALOG(dialog), "CANCEL", 1);


    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));


    table = gtk_table_new (2, 2, TRUE);
    gtk_container_add (GTK_CONTAINER (content_area), table);

    label = gtk_label_new ("X Value:" );
    gtk_table_set_homogeneous(GTK_TABLE (table), TRUE);
    gtk_table_attach_defaults (GTK_TABLE (table), label, 0, 1, 0, 1);

    label = gtk_label_new ("Y Value:" );
    gtk_table_set_homogeneous(GTK_TABLE (table), TRUE);
    gtk_table_attach_defaults (GTK_TABLE (table), label, 0, 1, 1, 2);



    entry = gtk_entry_new();
    gtk_entry_set_max_length (GTK_ENTRY (entry),0);
    gtk_table_attach_defaults (GTK_TABLE (table), entry, 1, 2, 0, 1);

    entry2 = gtk_entry_new();
    gtk_entry_set_max_length (GTK_ENTRY (entry2),0);
    gtk_table_attach_defaults (GTK_TABLE (table), entry2, 1, 2, 1, 2);

    gtk_widget_show_all(dialog);
    gint result = gtk_dialog_run(GTK_DIALOG(dialog));


    string entryX = ""; // variable for entered text
    string entryY = "";
    int x = 0;
    int y = 0;

    switch(result){
        case 0:
            cout << "OK was clicked\n";
            entryX = gtk_entry_get_text(GTK_ENTRY(entry));
            entryY = gtk_entry_get_text(GTK_ENTRY(entry2));
            gtk_widget_destroy(dialog);
            show_recur_cord_entry_dialog();
            break;
        case 1:
            cout << "CANCEL was clicked\n"; break;
        default:
            cout << "Undefined. Perhaps dialog was closed\n"; break;
    }
    x = atoi(entryX.c_str());
    y = atoi(entryY.c_str());
    cord.at(1) = y;
    cord.at(0) = x;
    gtk_widget_destroy(dialog);



    return cord;
}
*/

static void   zoomIn (GtkWidget *widget, DisplayFile *pointer)
{
    // Change width and heigt
    pointer->pos_window.matrix[1][2] = 0.9*pointer->pos_window.matrix[1][2];
    pointer->pos_window.matrix[2][2] = 0.9*pointer->pos_window.matrix[2][2];
    // Change w_x_min and w_x_max
    pointer->pos_window.matrix[1][0] = pointer->pos_window.get_X()-pointer->pos_window.matrix[1][2] ;
    pointer->pos_window.matrix[1][1] = pointer->pos_window.get_X()+pointer->pos_window.matrix[1][2];
    // Change w_y_min and w_y_max
    pointer->pos_window.matrix[2][0] = pointer->pos_window.get_X()-pointer->pos_window.matrix[2][2];
    pointer->pos_window.matrix[2][1] = pointer->pos_window.get_Y()+pointer->pos_window.matrix[2][2];
    // Draw all the elements
    draw_all(widget, pointer);
}

static void   zoomOut (GtkWidget *widget, DisplayFile *pointer)
{
    // Change width and heigt
    pointer->pos_window.matrix[1][2] = 1.1*pointer->pos_window.matrix[1][2];
    pointer->pos_window.matrix[2][2] = 1.1*pointer->pos_window.matrix[2][2];
    // Change w_x_min and w_x_max
    pointer->pos_window.matrix[1][0] = pointer->pos_window.get_X()-pointer->pos_window.matrix[1][2] ;
    pointer->pos_window.matrix[1][1] = pointer->pos_window.get_X()+pointer->pos_window.matrix[1][2];
    // Change w_y_min and w_y_max
    pointer->pos_window.matrix[2][0] = pointer->pos_window.get_X()-pointer->pos_window.matrix[2][2];
    pointer->pos_window.matrix[2][1] = pointer->pos_window.get_Y()+pointer->pos_window.matrix[2][2];
    // Draw all the elements
    draw_all(widget, pointer);
}

static void myMovimentLeft(GtkWidget *widget, DisplayFile *pointer)
{
    Matrix3d cRot, delta;
    // Update teta
     pointer->teta = atan2(pointer->viewUp.matrix[1][0] ,pointer->viewUp.matrix[1][1]);
    cRot.rotMatrix(pointer->teta);

    // Get projection of a step in the world frame
    delta =Matrix3d(1,0)*cRot;

    // Update window position
    pointer->pos_window.matrix[0][0] += 20 * delta.get_X();
    pointer->pos_window.matrix[0][1] += 20 * delta.get_Y();
    draw_all(widget, pointer);
}

static void myMovimentRigth(GtkWidget *widget, DisplayFile *pointer)
{
    Matrix3d cRot, delta;
    // Update teta
    pointer->teta = atan2(pointer->viewUp.matrix[1][0] ,pointer->viewUp.matrix[1][1]);
   cRot.rotMatrix(pointer->teta);

    // Get projection of a step in the world frame
    delta = Matrix3d(-1,0)*cRot;

    // Update window position
    pointer->pos_window.matrix[0][0] += 20* delta.get_X();
    pointer->pos_window.matrix[0][1] += 20*delta.get_Y();
    draw_all(widget, pointer);
}

static void myMovimentUp(GtkWidget *widget, DisplayFile *pointer)
{
    Matrix3d cRot, delta;
    // Update teta
     pointer->teta = atan2(pointer->viewUp.matrix[1][0] ,pointer->viewUp.matrix[1][1]);
    cRot.rotMatrix(pointer->teta);
    // Get projection of a step in the world frame
    delta =Matrix3d(0,-1)*cRot;

    // Update window position
    pointer->pos_window.matrix[0][0] += 20*delta.get_X();
    pointer->pos_window.matrix[0][1] += 20*delta.get_Y();
    draw_all(widget, pointer);
}

static void myMovimentDown(GtkWidget *widget, DisplayFile *pointer)
{
    Matrix3d cRot, delta;
    // Update teta
    pointer->teta = atan2(pointer->viewUp.matrix[1][0] ,pointer->viewUp.matrix[1][1]);
    cRot.rotMatrix(pointer->teta);

    // Get projection of a step in the world frame
    delta =Matrix3d(0,1)*cRot;

    // Update window position and draw all points
    pointer->pos_window.matrix[0][0] += 20*delta.get_X();
    pointer->pos_window.matrix[0][1] += 20*delta.get_Y();
    draw_all(widget, pointer);
}

static void rot_window_pos(GtkWidget *widget, DisplayFile *pointer)
{
    Matrix3d tempRot;
    tempRot.rotMatrix(M_PI/36);
    pointer->viewUp = pointer->viewUp*tempRot;
    draw_all(widget, pointer);
}

static void rot_window_neg(GtkWidget *widget, DisplayFile *pointer)
{
    Matrix3d tempRot;
    tempRot.rotMatrix(- M_PI/36);
    pointer->viewUp = pointer->viewUp*tempRot;
    draw_all(widget, pointer);

}




static void rot_obj(GtkWidget *widget, DisplayFile *pointer)
{
    GtkWidget *dialog;
    GtkWidget *entry;
    GtkWidget *entryFactor;
    GtkWidget *content_area;
    GtkWidget *table,*label;
    std::string entry_text;

    dialog = gtk_dialog_new();
    gtk_dialog_add_button(GTK_DIALOG(dialog), "OK", 0);
    gtk_dialog_add_button(GTK_DIALOG(dialog), "CANCEL", 1);

    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    table = gtk_table_new (2, 2, TRUE);
    gtk_container_add (GTK_CONTAINER (content_area), table);

    label = gtk_label_new ("Object Name:" );
    gtk_table_set_homogeneous(GTK_TABLE (table), TRUE);
    gtk_table_attach_defaults (GTK_TABLE (table), label, 0, 1, 0, 1);

    label = gtk_label_new ("Rotation:" );
    gtk_table_set_homogeneous(GTK_TABLE (table), TRUE);
    gtk_table_attach_defaults (GTK_TABLE (table), label, 0, 1, 1, 2);

    entry = gtk_entry_new();
    gtk_entry_set_max_length (GTK_ENTRY (entry),0);
    gtk_table_attach_defaults (GTK_TABLE (table), entry, 1, 2, 0, 1);

    entryFactor = gtk_entry_new();
    gtk_entry_set_max_length (GTK_ENTRY (entryFactor),0);
    gtk_table_attach_defaults (GTK_TABLE (table), entryFactor, 1, 2, 1, 2);


    gtk_widget_show_all(dialog);
    gint result = gtk_dialog_run(GTK_DIALOG(dialog));

    string entryFactorField = ""; // variable for entered text
    double factor = 0;

    switch(result){
        case 0:
            entry_text = gtk_entry_get_text(GTK_ENTRY(entry));
            entryFactorField = gtk_entry_get_text(GTK_ENTRY(entryFactor));
            gtk_widget_destroy(dialog);
            break;
        case 1:
            gtk_widget_destroy(dialog);
            return;
        default:
            gtk_widget_destroy(dialog);
            return;
    }
    char *cName = new char[entry_text.length() + 1];
    std::copy(entry_text.begin(), entry_text.end(), cName);
    cName[entry_text.size()] = '\0';


    Elemento<BaseObject>* obj = pointer->objBuffer.retiraByName(cName);
    if(obj != 0){
        factor = atof(entryFactorField.c_str());
        obj->getMyInfo()->rotAround_GeoCenter(factor);
    }
    draw_all(widget, pointer);

}

static void rotP_obj(GtkWidget *widget, DisplayFile *pointer)
{
    GtkWidget *dialog;
    GtkWidget *entry;
    GtkWidget *entryX;
    GtkWidget *entryY;
    GtkWidget *entryFactor;
    GtkWidget *content_area;
    GtkWidget *table,*label;
    std::string entry_text;
    std::string entryXField;
    std::string entryYField;
    std::string entryFactorField;

    double pointX;
    double pointY;
    double factor;

    dialog = gtk_dialog_new();
    gtk_dialog_add_button(GTK_DIALOG(dialog), "OK", 0);
    gtk_dialog_add_button(GTK_DIALOG(dialog), "CANCEL", 1);

    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    table = gtk_table_new (5, 5, TRUE);
    gtk_container_add (GTK_CONTAINER (content_area), table);

    label = gtk_label_new ("Object Name:" );
    gtk_table_set_homogeneous(GTK_TABLE (table), TRUE);
    gtk_table_attach_defaults (GTK_TABLE (table), label, 0, 1, 0, 1);

    label = gtk_label_new ("Point X:" );
    gtk_table_set_homogeneous(GTK_TABLE (table), TRUE);
    gtk_table_attach_defaults (GTK_TABLE (table), label, 0, 1, 1, 2);

    label = gtk_label_new ("Point Y:" );
    gtk_table_set_homogeneous(GTK_TABLE (table), TRUE);
    gtk_table_attach_defaults (GTK_TABLE (table), label, 0, 1, 2, 3);

    label = gtk_label_new ("Rotation:" );
    gtk_table_set_homogeneous(GTK_TABLE (table), TRUE);
    gtk_table_attach_defaults (GTK_TABLE (table), label, 0, 1, 3, 4);

    entry = gtk_entry_new();
    gtk_entry_set_max_length (GTK_ENTRY (entry),0);
    gtk_table_attach_defaults (GTK_TABLE (table), entry, 1, 2, 0, 1);

    entryX = gtk_entry_new();
    gtk_entry_set_max_length (GTK_ENTRY (entryX),0);
    gtk_table_attach_defaults (GTK_TABLE (table), entryX, 1, 2, 1, 2);

    entryY = gtk_entry_new();
    gtk_entry_set_max_length (GTK_ENTRY (entryY),0);
    gtk_table_attach_defaults (GTK_TABLE (table), entryY, 1, 2, 2, 3);

    entryFactor = gtk_entry_new();
    gtk_entry_set_max_length (GTK_ENTRY (entryFactor),0);
    gtk_table_attach_defaults (GTK_TABLE (table), entryFactor, 1, 2, 3, 4);


    gtk_widget_show_all(dialog);
    gint result = gtk_dialog_run(GTK_DIALOG(dialog));

    switch(result){
        case 0:
            entry_text = gtk_entry_get_text(GTK_ENTRY(entry));
            entryXField = gtk_entry_get_text(GTK_ENTRY(entryX));
            entryYField = gtk_entry_get_text(GTK_ENTRY(entryY));
            entryFactorField = gtk_entry_get_text(GTK_ENTRY(entryFactor));
            gtk_widget_destroy(dialog);
            break;
        case 1:
            gtk_widget_destroy(dialog);
            return;
        default:
            gtk_widget_destroy(dialog);
            return;
    }
    char *cName = new char[entry_text.length() + 1];
    std::copy(entry_text.begin(), entry_text.end(), cName);
    cName[entry_text.size()] = '\0';
    Elemento<BaseObject>* obj = pointer->objBuffer.retiraByName(cName);

    if(obj != 0){
        pointX = atof(entryXField.c_str());
        pointY = atof(entryYField.c_str());
        factor = atof(entryFactorField.c_str());


        obj->getMyInfo()->rotAround_Point( Matrix3d(pointX, pointY), factor);
    }



    draw_all(widget, pointer);

}

static void rotI_obj(GtkWidget *widget, DisplayFile *pointer)
{
    GtkWidget *dialog;
    GtkWidget *entry;
    GtkWidget *entryFactor;
    GtkWidget *content_area;
    GtkWidget *table,*label;
    std::string entry_text;

    dialog = gtk_dialog_new();
    gtk_dialog_add_button(GTK_DIALOG(dialog), "OK", 0);
    gtk_dialog_add_button(GTK_DIALOG(dialog), "CANCEL", 1);

    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    table = gtk_table_new (2, 2, TRUE);
    gtk_container_add (GTK_CONTAINER (content_area), table);

    label = gtk_label_new ("Object Name:" );
    gtk_table_set_homogeneous(GTK_TABLE (table), TRUE);
    gtk_table_attach_defaults (GTK_TABLE (table), label, 0, 1, 0, 1);

    label = gtk_label_new ("Rotation:" );
    gtk_table_set_homogeneous(GTK_TABLE (table), TRUE);
    gtk_table_attach_defaults (GTK_TABLE (table), label, 0, 1, 1, 2);

    entry = gtk_entry_new();
    gtk_entry_set_max_length (GTK_ENTRY (entry),0);
    gtk_table_attach_defaults (GTK_TABLE (table), entry, 1, 2, 0, 1);

    entryFactor = gtk_entry_new();
    gtk_entry_set_max_length (GTK_ENTRY (entryFactor),0);
    gtk_table_attach_defaults (GTK_TABLE (table), entryFactor, 1, 2, 1, 2);


    gtk_widget_show_all(dialog);
    gint result = gtk_dialog_run(GTK_DIALOG(dialog));

    string entryFactorField = ""; // variable for entered text
    double factor = 0;

    switch(result){
        case 0:
            entry_text = gtk_entry_get_text(GTK_ENTRY(entry));
            entryFactorField = gtk_entry_get_text(GTK_ENTRY(entryFactor));
            gtk_widget_destroy(dialog);
            break;
        case 1:
            gtk_widget_destroy(dialog);
            return;
        default:
            gtk_widget_destroy(dialog);
            return;
    }
    char *cName = new char[entry_text.length() + 1];
    std::copy(entry_text.begin(), entry_text.end(), cName);
    cName[entry_text.size()] = '\0';

    Elemento<BaseObject>* obj = pointer->objBuffer.retiraByName(cName);


    if(obj != 0){
        factor = atof(entryFactorField.c_str());
        obj->getMyInfo()->rotAround_Initial(factor);
    }

    gtk_widget_destroy(dialog);

    draw_all(widget, pointer);

}

static void esca_obj(GtkWidget *widget, DisplayFile *pointer)
{
    GtkWidget *dialog;
    GtkWidget *entry;
    GtkWidget *entryX;
    GtkWidget *entryY;
    GtkWidget *content_area;
    GtkWidget *table,*label;
    std::string entry_text;

    dialog = gtk_dialog_new();
    gtk_dialog_add_button(GTK_DIALOG(dialog), "OK", 0);
    gtk_dialog_add_button(GTK_DIALOG(dialog), "CANCEL", 1);

    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    table = gtk_table_new (3, 3, TRUE);
    gtk_container_add (GTK_CONTAINER (content_area), table);

    label = gtk_label_new ("Object Name:" );
    gtk_table_set_homogeneous(GTK_TABLE (table), TRUE);
    gtk_table_attach_defaults (GTK_TABLE (table), label, 0, 1, 0, 1);

    label = gtk_label_new ("Scal X:" );
    gtk_table_set_homogeneous(GTK_TABLE (table), TRUE);
    gtk_table_attach_defaults (GTK_TABLE (table), label, 0, 1, 1, 2);

    label = gtk_label_new ("Scal Y:" );
    gtk_table_set_homogeneous(GTK_TABLE (table), TRUE);
    gtk_table_attach_defaults (GTK_TABLE (table), label, 0, 1, 2, 3);

    entry = gtk_entry_new();
    gtk_entry_set_max_length (GTK_ENTRY (entry),0);
    gtk_table_attach_defaults (GTK_TABLE (table), entry, 1, 2, 0, 1);

    entryX = gtk_entry_new();
    gtk_entry_set_max_length (GTK_ENTRY (entryX),0);
    gtk_table_attach_defaults (GTK_TABLE (table), entryX, 1, 2, 1, 2);

    entryY = gtk_entry_new();
    gtk_entry_set_max_length (GTK_ENTRY (entryY),0);
    gtk_table_attach_defaults (GTK_TABLE (table), entryY, 1, 2, 2, 3);

    gtk_widget_show_all(dialog);
    gint result = gtk_dialog_run(GTK_DIALOG(dialog));

    string entryXField = ""; // variable for entered text
    string entryYField = "";
    double transX = 0;
    double transY = 0;

    switch(result){
        case 0:
            entry_text = gtk_entry_get_text(GTK_ENTRY(entry));
            entryXField = gtk_entry_get_text(GTK_ENTRY(entryX));
            entryYField = gtk_entry_get_text(GTK_ENTRY(entryY));
            gtk_widget_destroy(dialog);
            break;
        case 1:
            gtk_widget_destroy(dialog);
            return;
        default:
            gtk_widget_destroy(dialog);
            return;
    }
    char *cName = new char[entry_text.length() + 1];
    std::copy(entry_text.begin(), entry_text.end(), cName);
    cName[entry_text.size()] = '\0';
    Elemento<BaseObject>* obj = pointer->objBuffer.retiraByName(cName);

    if(obj != 0){
        transX = atof(entryXField.c_str());
        transY = atof(entryYField.c_str());
        obj->getMyInfo()->scaling(transX, transY);
    }

    gtk_widget_destroy(dialog);

    draw_all(widget, pointer);

}


static void trans_obj(GtkWidget *widget, DisplayFile *pointer)
{
    GtkWidget *dialog;
    GtkWidget *entry;
    GtkWidget *entryX;
    GtkWidget *entryY;
    GtkWidget *content_area;
    GtkWidget *table,*label;
    std::string entry_text;

    dialog = gtk_dialog_new();
    gtk_dialog_add_button(GTK_DIALOG(dialog), "OK", 0);
    gtk_dialog_add_button(GTK_DIALOG(dialog), "CANCEL", 1);

    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    table = gtk_table_new (3, 3, TRUE);
    gtk_container_add (GTK_CONTAINER (content_area), table);

    label = gtk_label_new ("Object Name:" );
    gtk_table_set_homogeneous(GTK_TABLE (table), TRUE);
    gtk_table_attach_defaults (GTK_TABLE (table), label, 0, 1, 0, 1);

    label = gtk_label_new ("Trans X:" );
    gtk_table_set_homogeneous(GTK_TABLE (table), TRUE);
    gtk_table_attach_defaults (GTK_TABLE (table), label, 0, 1, 1, 2);

    label = gtk_label_new ("Trans Y:" );
    gtk_table_set_homogeneous(GTK_TABLE (table), TRUE);
    gtk_table_attach_defaults (GTK_TABLE (table), label, 0, 1, 2, 3);

    entry = gtk_entry_new();
    gtk_entry_set_max_length (GTK_ENTRY (entry),0);
    gtk_table_attach_defaults (GTK_TABLE (table), entry, 1, 2, 0, 1);

    entryX = gtk_entry_new();
    gtk_entry_set_max_length (GTK_ENTRY (entryX),0);
    gtk_table_attach_defaults (GTK_TABLE (table), entryX, 1, 2, 1, 2);

    entryY = gtk_entry_new();
    gtk_entry_set_max_length (GTK_ENTRY (entryY),0);
    gtk_table_attach_defaults (GTK_TABLE (table), entryY, 1, 2, 2, 3);

    gtk_widget_show_all(dialog);
    gint result = gtk_dialog_run(GTK_DIALOG(dialog));

    string entryXField = ""; // variable for entered text
    string entryYField = "";
    double transX = 0;
    double transY = 0;

    switch(result){
        case 0:
            entry_text = gtk_entry_get_text(GTK_ENTRY(entry));
            entryXField = gtk_entry_get_text(GTK_ENTRY(entryX));
            entryYField = gtk_entry_get_text(GTK_ENTRY(entryY));
            gtk_widget_destroy(dialog);
            break;
        case 1:
            gtk_widget_destroy(dialog);
            return;
        default:
            gtk_widget_destroy(dialog);
            return;
    }
    char *cName = new char[entry_text.length() + 1];
    std::copy(entry_text.begin(), entry_text.end(), cName);
    cName[entry_text.size()] = '\0';
    Elemento<BaseObject>* obj = pointer->objBuffer.retiraByName(cName);

    if(obj != 0){
        transX = atof(entryXField.c_str());
        transY = atof(entryYField.c_str());

        obj->getMyInfo()->translation(transX, transY);
    }


    gtk_widget_destroy(dialog);

    draw_all(widget, pointer);

}

void draw_all(GtkWidget *widget, DisplayFile *pointer )
{
    clear_surface();
    cairo_t *cr;
    cr = cairo_create (surface);
    Elemento<BaseObject>* actualElement = pointer->objBuffer.getHead();
    BaseObject *temp = NULL;

    for(int i = 0; i < pointer->objBuffer.myLength(); i++){

        //Get current object and update them
        temp = actualElement->getObj();
        temp->updateObjects(pointer);

        if(actualElement->getInfo().getType() == BaseObject::POINT)
        {
            //Draw point from viewport
            cairo_rectangle (cr, actualElement->getInfo().p_vp[0].get_X() , actualElement->getInfo().p_vp[0].get_Y(), 4, 4);
            cairo_fill (cr);
            // get next object in list
            actualElement = actualElement->getProximo();
        }
        else if(actualElement->getInfo().getType() == BaseObject::LINE)
        {
            //Move to position of first point
            cairo_move_to(cr,actualElement->getInfo().p_vp[0].get_X(), actualElement->getInfo().p_vp[0].get_Y());
            //Draw line
            cairo_line_to(cr,actualElement->getInfo().p_vp[1].get_X(),actualElement->getInfo().p_vp[1].get_Y());
            cairo_stroke(cr);
            //Move back to window centre
            cairo_move_to(cr,pointer->pos_window.get_X(),pointer->pos_window.get_Y());
            // Get next elemnt
            actualElement = actualElement->getProximo();
        }
        else if(actualElement->getInfo().getType() == BaseObject::POLYGON)
        {
            //Go trough all elemnts of the list
            for(int j =0; j < actualElement->getInfo().p_vp.size()-1; j++){
                //Move to position of point j
                cairo_move_to(cr,actualElement->getInfo().p_vp[j].get_X(), actualElement->getInfo().p_vp[j].get_Y());
                //Draw line to point j+1
                cairo_line_to(cr,actualElement->getInfo().p_vp[j+1].get_X(),actualElement->getInfo().p_vp[j+1].get_Y());
                cairo_stroke(cr);
            }
            //Move to last of point in the list
            cairo_move_to(cr,actualElement->getInfo().p_vp[actualElement->getInfo().p_vp.size()-1].get_X(), actualElement->getInfo().p_vp[actualElement->getInfo().p_vp.size()-1].get_Y());
            //Draw line to fisrt point
            cairo_line_to(cr,actualElement->getInfo().p_vp[0].get_X(),actualElement->getInfo().p_vp[0].get_Y());
            cairo_stroke(cr);
            //Move back to window centre
            cairo_move_to(cr,pointer->pos_window.get_X(),pointer->pos_window.get_Y());

            actualElement = actualElement->getProximo();
        }
        else
        {}


        // Drawing in the viewport area
        gtk_widget_queue_draw_area (widget, pointer->x_vp_min, pointer->y_vp_min,pointer->x_vp_max , pointer->y_vp_max);
    }
    //Draw red rectangle to show viewport
    cairo_set_source_rgb(cr,1,0,0);
    cairo_rectangle(cr, 10,10,580,580);
    gtk_widget_queue_draw_area (widget, pointer->x_vp_min, pointer->y_vp_min,pointer->x_vp_max , pointer->y_vp_max);
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
    std::vector<int> cord = show_cord_entry_dialog();
    double x = (double)cord.at(0);
    double y = (double)cord.at(1);

    char* name = show_name_entry_dialog();

    BaseObject* ponto = new ObjectPoint(name,Matrix3d(x,y));
    ponto->updateObjects(pointer);
    Elemento<BaseObject>* container = new Elemento<BaseObject>;
    container->setInfo(*ponto);

    pointer->objBuffer.adicionaNoInicio(*container);

    create_and_fill_model (pointer->objModel, pointer->objView, pointer->objStore, "Point", name);

    draw_all(widget, pointer);
}


static void   add_Line (GtkWidget *widget, DisplayFile *pointer)
{
    std::vector<int> cord1 = show_cord_entry_dialog();
    int xI = (double)cord1.at(0);
    int yI = (double)cord1.at(1);

    std::vector<int> cord2 = show_cord_entry_dialog();
    int xF = (double)cord2.at(0);
    int yF = (double)cord2.at(1);

    char* name = show_name_entry_dialog();

    BaseObject* line = new ObjectLine(name,Matrix3d(xI,yI),Matrix3d(xF,yF));
    line->updateObjects(pointer);
    Elemento<BaseObject>* container = new Elemento<BaseObject>;
    container->setInfo(*line);
    pointer->objBuffer.adicionaNoInicio(*container);

    create_and_fill_model (pointer->objModel, pointer->objView, pointer->objStore, "Line", name);
    draw_all(widget, pointer);
}

static void  add_Polygon (GtkWidget *widget, DisplayFile *pointer)
{
    std::vector<Matrix3d> positions;

    //Coordenadas iniciais básicas para um poligono
    std::vector<int> cord = show_cord_entry_dialog();
    positions.insert(positions.begin(),Matrix3d(cord.at(0),cord.at(1)));
    cord = show_cord_entry_dialog();
    positions.insert(positions.begin(),Matrix3d(cord.at(0),cord.at(1)));
    cord = show_cord_entry_dialog();
    positions.insert(positions.begin(),Matrix3d(cord.at(0),cord.at(1)));

    // Coordenadas extras
    while(true){
        cord = show_cord_entry_dialog();
        if(cord.at(2) == 0){
            break;
        }else{
            positions.insert(positions.begin(),Matrix3d(cord.at(0),cord.at(1)));
        }
    }

    char* name = show_name_entry_dialog();

    BaseObject* polygon = new ObjectPolygon(name,positions);
    polygon->updateObjects(pointer);
    Elemento<BaseObject>* container = new Elemento<BaseObject>;
    container->setInfo(*polygon);
    pointer->objBuffer.adicionaNoInicio(*container);

    create_and_fill_model (pointer->objModel, pointer->objView, pointer->objStore, "Polygon", name);
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
    //cairo_recatan2gle (cr, actualElement->getInfo().x, actualElement->getInfo().y, 4, 4);
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

//upadtes all objects


#endif // WINDOWFUNCTIONS_H
