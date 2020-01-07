#include <stdio.h>
#include <mcheck.h>
#include <cmath>
#include <cstdio>

#include "./../include/point.hpp"
#include "glut_utils.h"

#include "shape.hpp"
#include "circle.hpp"
#include "line.hpp"
#include "rect.hpp"
#include "square.hpp"
#include "group.hpp"


ilrd::Shape *circle1 = new ilrd::Circle(250, 100, COLOR_MAGENTA, 50);

ilrd::Shape *rect1 = new ilrd::Rect(600, 350, COLOR_CYAN, 300, 50, 45);
ilrd::Shape *square1 = new ilrd::Square(400, 350, COLOR_YELLOW, 100, 45);
ilrd::Shape *circle3 = new ilrd::Circle(350, 450, COLOR_RED, 50);
ilrd::Shape *line1 = new ilrd::Line(350, 650, COLOR_WHITE, 50, 0);
ilrd::Group *group1 = new ilrd::Group();


ilrd::Shape *circle2 = new ilrd::Circle(150, 350, COLOR_MAGENTA, 50);
ilrd::Shape *line2 = new ilrd::Line(200, 500, COLOR_BLUE, 50, 0);
ilrd::Shape *square2 = new ilrd::Square(250, 350, COLOR_YELLOW, 100, 45);
ilrd::Group *group2 = new ilrd::Group();

double g_GroupAngle = 10;
ilrd::Point g_CirclePivot(250, 150);
ilrd::Point g_SquarePivot(400, 450);
ilrd::Point g_GroupPivot(500, 500);
double g_RevolveAngle = 10;
double g_CircleX = circle1->GetX();
double g_CircleY = circle1->GetY();
double g_RectX = rect1->GetX();
double g_RectY = rect1->GetY();
double g_LineX = line1->GetX();
double g_LineY = line1->GetY();
double g_SquareAngle = square1->GetAngle();


static int TimerFunction1();
static int TimerFunction2();
static int KeyboardFunction(unsigned char key, int x, int y);
static void DrawFunction1();
static void DrawFunction2();


int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    group1->AddShape(line1);
    //printf("group center %2.f,%2.f\n", group1->GetX(), group1->GetY());
    group1->AddShape(square1);
    //printf("group center %2.f,%2.f\n", group1->GetX(), group1->GetY());
    group1->AddShape(rect1);
    //printf("group center %2.f,%2.f\n", group1->GetX(), group1->GetY());


    DrawInit(0, NULL, 1000, 1000, DrawFunction1);
    DrawSetKeyboardFunc(KeyboardFunction);

    DrawSetTimerFunc(TimerFunction1, 100);
    DrawMainLoop();


    group2->AddShape(circle2);
    //printf("group center %2.f,%2.f\n", group2->GetX(), group2->GetY());
    group2->AddShape(line2);
    //printf("group center %2.f,%2.f\n", group2->GetX(), group2->GetY());
    group2->AddShape(square2);
    //printf("group center %2.f,%2.f\n", group2->GetX(), group2->GetY());

    DrawInit(0, NULL, 1000, 1000, DrawFunction2);
    DrawSetKeyboardFunc(KeyboardFunction);

    DrawSetTimerFunc(TimerFunction2, 100);
    DrawMainLoop();


    return 0;
}


void DrawFunction1()
{
    ilrd::Point null(0,0);
    group1->Display(null);
    /* line1->Display();
    line2->Display();
    circle1->Display();
    circle2->Display();
    square1->Display();
    rect1->Display(); */
}

void DrawFunction2()
{   
    ilrd::Point null(0,0);
    group2->Display(null);
}

static int TimerFunction1()
{
    //static double groupX = group->GetX();
    //static double groupY = group->GetY();
    group1->Rotate((int)(g_GroupAngle));
    //group->Revolve(g_GroupPivot, g_GroupAngle);
    //group->Move(2.5, 2.5);
    //rect1->Move(g_RectX++, g_RectY++);
    //line1->Move(g_LineX, g_LineY++);
    
    //circle1->Revolve(g_CirclePivot, g_RevolveAngle);
    //circle1->Move(circle1->GetX() + 5, circle1->GetY() + 5);
    
    //square1->Rotate(g_SquareAngle += 45);
    //square1->Revolve(g_SquarePivot, g_RevolveAngle);
    
    return 1;
}

static int TimerFunction2()
{
    group2->Revolve(g_GroupPivot, g_GroupAngle);
    //group2->Move(10, 10);
    return 1;
}

static int KeyboardFunction(unsigned char key, int x, int y)
{
    printf("Keyboard: %02x,%d,%d\n", key, x, y);

    if (key == 0x1b /* ESC */)
        return -1;

    return 0;
}
