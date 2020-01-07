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

    Point& AdjustBy(const Point& p, const int upper_bound);
    Point& AdjustBy(const int dx, const int dy, const int upper_bound);
    double Length() const;
    void Print(const char open, const char close) const;
    void Print(paren p) const;
};

Point Add(const Point p1, const Point p2, const int upper_bound);
void InitTable();


#endif