#include "Polygon.hpp"

#include "./../../../../utils.h"


int TESTBuildPolygonAddTwoPoints();
int TESTBuildPolygonsCheckIsEqual();
int TESTCopyCtor();
int TESTAssignmentOper();

int main()
{
    RUN_TEST(TESTBuildPolygonAddTwoPoints());
    RUN_TEST(TESTBuildPolygonsCheckIsEqual());
    RUN_TEST(TESTCopyCtor());
    RUN_TEST(TESTAssignmentOper());
    
    return 0;
}

int TESTBuildPolygonAddTwoPoints()
{
    Polygon polygon(5);
    Point point1(1,2);
    Point point2(2,2);


    polygon.Add(point1);

    /* polygon.Print(); */

    if (true == polygon.m_points[5].IsEqual(point1))
    {
        return PASS;    
    }

    return FAIL;
}

int TESTBuildPolygonsCheckIsEqual()
{
    Polygon polygon1(5);
    Polygon polygon2(5);
    Point point1(1,2);
    Point point2(2,2);

    polygon1.Add(point1);
    polygon1.Add(point2);

    polygon2.Add(point1);
    polygon2.Add(point2);

    if (true == polygon1.IsEqual(polygon2))
    {
        return PASS;    
    }

    return FAIL;
}


int TESTCopyCtor()
{
    Polygon polygon1(5);
    
    Point point1(1,2);
    Point point2(2,2);

    polygon1.Add(point1);
    polygon1.Add(point2);

    Polygon polygon2(polygon1);

    if (true == polygon1.IsEqual(polygon2))
    {
        return PASS;    
    }

    return FAIL;
}


int TESTAssignmentOper()
{
    Polygon polygon1(5);
    
    Point point1(1,2);
    Point point2(2,2);
    Point point3(3,4);
    Point point4(9,5);
    Point point5(17,23);

    polygon1.Add(point1);
    polygon1.Add(point2);
    polygon1.Add(point3);
    polygon1.Add(point4);
    polygon1.Add(point5);

    Polygon polygon2(5);

    polygon2 = polygon1;

    if (true == polygon1.IsEqual(polygon2))
    {        
        return PASS;    
    }

    return FAIL;
}
