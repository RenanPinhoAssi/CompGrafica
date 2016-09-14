#ifndef TEST_TAREFA_02_H
#define TEST_TAREFA_02_H

#include "WindowFunctions.h"

//Testfile for tarefa 2

static void test_02(DisplayFile *pointer){

    //Temp pointers to add elemnts
    BaseObject *temp = NULL;
    Elemento<BaseObject>* container;

    // Points

    temp = new ObjectPoint("Point_01",Matrix3d(0,0));
    temp->updateObjects(pointer);
    container = new Elemento<BaseObject>;
    container->setInfo(*temp);
    pointer->objBuffer.adicionaNoInicio(*container);
    /*
    temp = new ObjectPoint("Point_01",Matrix3d(290,0));
    temp->updateObjects(pointer);
    container = new Elemento<BaseObject>;
    container->setInfo(*temp);
    pointer->objBuffer.adicionaNoInicio(*container);

    temp = new ObjectPoint("Point_01",Matrix3d(-290,0));
    temp->updateObjects(pointer);
    container = new Elemento<BaseObject>;
    container->setInfo(*temp);
    pointer->objBuffer.adicionaNoInicio(*container);

    temp = new ObjectPoint("Point_01",Matrix3d(290,0));
    temp->updateObjects(pointer);
    container = new Elemento<BaseObject>;
    container->setInfo(*temp);
    pointer->objBuffer.adicionaNoInicio(*container);

    temp = new ObjectPoint("Point_01",Matrix3d(0,290));
    temp->updateObjects(pointer);
    container = new Elemento<BaseObject>;
    container->setInfo(*temp);
    pointer->objBuffer.adicionaNoInicio(*container);

    temp = new ObjectPoint("Point_01",Matrix3d(0,-290));
    temp->updateObjects(pointer);
    temp->rotAround_Initial(M_PI/2);
    container = new Elemento<BaseObject>;
    container->setInfo(*temp);
    pointer->objBuffer.adicionaNoInicio(*container);

    temp = new ObjectPoint("Point_01",Matrix3d(290,290));
    temp->updateObjects(pointer);
    temp->rotAround_Initial(- M_PI);
    container = new Elemento<BaseObject>;
    container->setInfo(*temp);
    pointer->objBuffer.adicionaNoInicio(*container);
    */



    //Add Line
    //
    temp = new ObjectPolygon("Name",Matrix3d(150,150),Matrix3d(250,150), Matrix3d(250,250),  Matrix3d(150,250));
    temp->updateObjects(pointer);
    temp->scaling(1.5,1.5);
    container = new Elemento<BaseObject>;
    container->setInfo(*temp);
    pointer->objBuffer.adicionaNoInicio(*container);



}


#endif // TEST_TAREFA_02_H
