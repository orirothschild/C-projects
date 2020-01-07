#ifndef ILRD_POINT_H
#define ILRD_POINT_H


struct Point
{
    int x;
    int y;

    void AdjustBy(Point p, int upper_bound);
    double Length();
    void Print(char open, char close);
};

Point Add(Point p1, Point p2, int upper_bound);



#endif