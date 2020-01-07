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

    explicit Point(int m_x = 0, int m_y = 0);
    ~Point();

    void SetX(const int x, const int upper_bound);
    void SetY(const int y, const int upper_bound);
    int GetX() const;
    int GetY() const;
    Point& AdjustBy(const Point& p, const int upper_bound);
    Point& AdjustBy(const int dx, const int dy, const int upper_bound);
    double Length();
    void Print(char open, char close) const;
    void Print(paren p = ROUND) const;
    bool IsEqual(Point p) const;
    void CalculateLength();

//private:
    int m_x;
    int m_y;
    double m_length_sqrt;

};

Point Add(const Point p1, const Point p2, const int upper_bound);
void InitTable();
double GetTotalLength();

#endif