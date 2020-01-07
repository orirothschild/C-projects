#ifndef ILRD_POINT_H
#define ILRD_POINT_H


struct Point
{
    enum paren
    {
        ROUND = '(',
        SQUARE = '[',
        CURLY = '{',
        ANGULAR = '<'
    };

    int x;
    int y;

    void AdjustBy(Point p, int upper_bound);
    void AdjustBy(int dx, int dy, int upper_bound);
    double Length();
    void Print(char open, char close);
    void Print(paren p);
};

Point Add(Point p1, Point p2, int upper_bound);
void InitTable();


#endif