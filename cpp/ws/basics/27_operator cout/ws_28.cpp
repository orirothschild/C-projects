#include "./../../../utils.h"

typedef struct List list;
typedef struct Person Person;

struct List
{

};

struct Person : public List
{
    int age;
};

void *ll_find(List *ll, int key)
{
    (void)ll;
    (void)key;
    return nullptr;
}

void Foo(List * ll, int key, int age)
{
    int i = 5;
    float f = 10.17;

    //f = static_cast<float>(i);
    i = static_cast<int>(f);

    void *vv = ll_find(ll, key);
    Person *p = static_cast<Person*>(vv);
    List *l1 = dynamic_cast<List *>(p);
    Person *p2 = reinterpret_cast<Person *>(ll);

    p->age = age;
    p2->age = age;
}

int main()
{
    List list;
    int key = 7;
    int age = 17;

    int i = 1;
    int *ip = &i;
    float f = 5.12;
    float *fp = &f;
    double d = 3.14;
    double *dp = &d;
    char c = 'Y';
    char *str = "hello";


    double *d2 = reinterpret_cast<double *>(&i);

    int i2 = static_cast<int>(f);
    int i3 = static_cast<int>(d);
    const int *i4 = const_cast<int *>(ip);

    Foo(&list, key, age);



    return 0;
}