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

//private:
    int x;
    int y;
    double length_sqrt;

    void SetX(const int x);
    void SetY(const int y);
    int GetX() const;
    int GetY() const;
    Point& AdjustBy(const Point& p, const int upper_bound);
    Point& AdjustBy(const int dx, const int dy, const int upper_bound);
    double Length();
    void Print(char open, char close) const;
    void Print(paren p = ROUND) const;
    bool IsEqual(Point p) const;
    void CalculateLength();
};

Point Add(const Point p1, const Point p2, const int upper_bound);
void InitTable();


#endif