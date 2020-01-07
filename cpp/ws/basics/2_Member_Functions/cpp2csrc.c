#include <stdio.h> /* printf */
#include <stdlib.h> /* calloc */
#include "./../utils.h"

#define AS_PT (struct PublicTransport *)
#define AS_MB (struct Minibus *)
#define AS_TX (struct Taxi *)
#define AS_ST (struct SpecialTaxi *)


static int publicTransportCount = 0;

struct PTvTable;

struct PublicTransport
{
    struct PTvTable *vtptr;
    int m_license_plate;
    char assignmentDisabler;
};
struct Minibus
{
    struct PublicTransport m_pt;
    int m_numSeats;
};
struct Taxi
{
    struct PublicTransport m_pt;
};
struct SpecialTaxi
{
    struct Taxi m_taxi;
};

/******************************PUBLICTRANSPORT FUNCTIONS***********************/
void PublicTransportCtorVoid(struct PublicTransport *this);
void PublicTransportDtor(struct PublicTransport *this);
void PublicTransportCCtor(struct PublicTransport *this,
                          struct PublicTransport *other);
struct PublicTransport *PublicTransportAssignment(struct PublicTransport *this,
                                                 struct PublicTransport *other);
void PublicTransportDisplayVoid(struct PublicTransport *this);
void PublicTransportPrintCountVoid();
int PublicTransportGetIDVoid(struct PublicTransport *this);

/******************************MINIBUS FUNCTIONS*******************************/
void MinibusCtorVoid(struct Minibus *this);
void MinibusCCtor(struct Minibus *this,
                  struct Minibus *other);
void MinibusDtor(struct Minibus *this);
struct Minibus *MinibusAssignment(struct Minibus *this,
                                  struct Minibus *other);
void MinibusDisplayVoid(struct Minibus *this);
void MinibusWashInt(struct Minibus *this, int minutes);

/*********************************TAXI FUNCTIONS*******************************/
void TaxiCtorVoid(struct Taxi *this);
void TaxiCCtor(struct Taxi *this,
               struct Taxi *other);
void TaxiDtor(struct Taxi *this);
struct Taxi *TaxiAssignment(struct Taxi *this,
                            struct Taxi *other);
void TaxiDisplayVoid(struct Taxi *this);

/**************************SPECIALTAXI FUNCTIONS*******************************/
void SpecialTaxiCtorVoid(struct SpecialTaxi *this);
void SpecialTaxiCCtor(struct SpecialTaxi *this,
                      struct SpecialTaxi *other);
void SpecialTaxiDtor(struct SpecialTaxi *this);
struct SpecialTaxi *SpecialTaxiAssignment(struct SpecialTaxi *this,
                                          struct SpecialTaxi *other);
void SpecialTaxiDisplayVoid(struct SpecialTaxi *this);
/******************************************************************************/

struct PTvTable
{
    void (* PublicTransportDtor)(struct PublicTransport *this);
    void (* PublicTransportDisplayVoid)(struct PublicTransport *this);
};

struct MBvTable
{
    struct PTvTable vt;
    void (* MinibusWashInt)(struct Minibus *this, int minutes);
};

struct TXvTable
{
    struct PTvTable vt;
};

struct STvTable
{
    struct PTvTable vt;
};
struct PCvTable
{
    struct PTvTable vt;
};

struct PTvTable ptvt = {PublicTransportDtor,
                     PublicTransportDisplayVoid};
struct MBvTable mbvt = {{(void (*)(struct PublicTransport *))MinibusDtor,
                      (void (*)(struct PublicTransport *))MinibusDisplayVoid},
                       MinibusWashInt};
struct TXvTable txvt = {{(void (*)(struct PublicTransport *))TaxiDtor,
                      (void (*)(struct PublicTransport *))TaxiDisplayVoid}};
struct STvTable stvt = {{(void (*)(struct PublicTransport *))SpecialTaxiDtor,
                      (void (*)(struct PublicTransport *))SpecialTaxiDisplayVoid}};
/* struct PCvTable pcvt = {{, }}; */

/******************************PUBLICTRANSPORT FUNCTIONS***********************/
void PublicTransportCtorVoid(struct PublicTransport *this)
{
    this->vtptr = &ptvt;
    this->m_license_plate = ++publicTransportCount;
    printf("PublicTransport::Ctor()%d\n", this->m_license_plate);
}

void PublicTransportDtor(struct PublicTransport *this)
{
    this->vtptr = &ptvt;
    --publicTransportCount;
    printf("PublicTransport::Dtor()%d\n", this->m_license_plate);
}

void PublicTransportCCtor(struct PublicTransport *this,
                          struct PublicTransport *other)
{
    UNUSED(other);
    this->vtptr = &ptvt;
    this->m_license_plate = ++publicTransportCount;
    
    printf("PublicTransport::CCtor() %d\n", this->m_license_plate);
}

void PublicTransportDisplayVoid(struct PublicTransport *this)
{
    printf("PublicTransport::display(): %d\n", this->m_license_plate);
}

void PublicTransportPrintCountVoid()
{
    printf("s_count: %d\n", publicTransportCount);
}

int PublicTransportGetIDVoid(struct PublicTransport *this)
{
    return this->m_license_plate;
}


/******************************MINIBUS FUNCTIONS*******************************/
void MinibusCtorVoid(struct Minibus *this)
{
    PublicTransportCtorVoid(&this->m_pt);
    this->m_pt.vtptr = (struct PTvTable *)&mbvt;
    this->m_numSeats = 20;
    printf("Minibus::Ctor()\n");
}

void MinibusCCtor(struct Minibus *this,
                  struct Minibus *other)
{
    PublicTransportCCtor(AS_PT &this, AS_PT &other);
    this->m_numSeats = other->m_numSeats;

    printf("Minibus::CCtor()\n");
}

void MinibusDtor(struct Minibus *this)
{
    this->m_pt.vtptr = (struct PTvTable *)&mbvt;
    printf("Minibus::Dtor()\n");
    PublicTransportDtor(&this->m_pt);
}

void MinibusDisplayVoid(struct Minibus *this)
{
    printf("Minibus::display() ID:%d ",
                PublicTransportGetIDVoid((struct PublicTransport * const)this));
    printf("num seats:%d\n", this->m_numSeats);
}

void MinibusWashInt(struct Minibus *this, int minutes)
{
    printf("Minibus::wash(%d) ID:%d\n", minutes,
                      PublicTransportGetIDVoid((struct PublicTransport *)this));
}

/*********************************TAXI FUNCTIONS*******************************/
void TaxiCtorVoid(struct Taxi *this)
{
    PublicTransportCtorVoid(&this->m_pt);
    this->m_pt.vtptr = (struct PTvTable *)&txvt;
    printf("Taxi::Ctor()\n");
}

void TaxiCCtor(struct Taxi *this,
               struct Taxi *other)
{
    PublicTransportCCtor(AS_PT this, AS_PT &other);
    printf("Taxi::CCtor()\n");
}

void TaxiDtor(struct Taxi *this)
{
    this->m_pt.vtptr = (struct PTvTable *)&txvt;
    printf("Taxi::Dtor()\n");
    PublicTransportDtor(&this->m_pt);
}

void TaxiDisplayVoid(struct Taxi *this)
{
    printf("Taxi::display() ID:%d\n",
                      PublicTransportGetIDVoid((struct PublicTransport *)this));
}

/**************************SPECIALTAXI FUNCTIONS*******************************/
void SpecialTaxiCtorVoid(struct SpecialTaxi *this)
{
    TaxiCtorVoid(&this->m_taxi);
    this->m_taxi.m_pt.vtptr = (struct PTvTable *)&stvt;
    printf("SpecialTaxi::Ctor()\n");
}

void SpecialTaxiCCtor(struct SpecialTaxi *this,
                    struct SpecialTaxi *other)
{
    TaxiCCtor(AS_TX this, AS_TX other);
    printf("SpecialTaxi::CCtor()\n");
}

void SpecialTaxiDtor(struct SpecialTaxi *this)
{
    this->m_taxi.m_pt.vtptr = (struct PTvTable *)&stvt;
    printf("SpecialTaxi::Dtor()\n");
    TaxiDtor(&this->m_taxi);
}

void SpecialTaxiDisplayVoid(struct SpecialTaxi *this)
{
    UNUSED(this);
    printf("SpecialTaxi::Display() ID:%d\n",
                      PublicTransportGetIDVoid((struct PublicTransport *)this));
}

/************************************GENERAL***********************************/
void PrintInfoPublicTransport(struct PublicTransport *a)
{
    a->vtptr->PublicTransportDisplayVoid(a);
}

void PrintInfoVoid()
{
    PublicTransportPrintCountVoid();
}

void PrintInfoMinibus(struct Minibus *m)
{
    ((struct MBvTable *)(m->m_pt.vtptr))->MinibusWashInt(m, 3);
}

struct PublicTransport *PrintInfoInt(struct PublicTransport *pt, int i)
{
    struct Minibus ret;
    UNUSED(i);
    MinibusCtorVoid(&ret);
    printf("print_info(int i)\n");
    MinibusDisplayVoid(&ret);

    PublicTransportCCtor(pt, AS_PT &ret);
    MinibusDtor(&ret);

    return pt;
}

void DisplayTaxi(struct Taxi *s)
{
    TaxiDisplayVoid(s);
}

union temp_args
{
    struct PublicTransport temp_pt1;
    struct Minibus temp_mb1;
    struct Taxi temp_tx1;
};

struct Taxi *newTaxiArrIMP(int numOfObjects)
{
    int i = 0;
    struct Taxi *taxiArr = NULL;

    taxiArr = calloc(1, numOfObjects * sizeof(struct Taxi) + sizeof(int));
    if (NULL == taxiArr)
    {
        return NULL;
    }

    *(int *)taxiArr = numOfObjects;
    taxiArr = (struct Taxi *)((char *)taxiArr + sizeof(int));

    for (i = 0; i < numOfObjects; ++i)
    {
        TaxiCtorVoid(taxiArr + i);
    }

    return taxiArr;
}

void deleteTaxiArrIMP(struct Taxi *taxiArr)
{
    int i = 0;
    int numOfObjects = *(int *)((char *)taxiArr - sizeof(int));

    for (i = numOfObjects - 1; i >= 0; --i)
    {
        taxiArr[i].m_pt.vtptr->
                   PublicTransportDtor(AS_PT &taxiArr[i]); 
    }

    free((char *)taxiArr - sizeof(int));
}

struct Minibus *newMinibusIMP()
{
    struct Minibus *newMB = calloc(1, sizeof(struct Minibus));
    if (NULL == newMB)
    {
        return NULL;
    }

    MinibusCtorVoid(newMB);

    return newMB;
}

void deleteMinibus(struct Minibus *mb)
{
    mb->m_pt.vtptr->PublicTransportDtor(AS_PT mb);
    free(mb);
}

struct Taxi *newTaxiIMP()
{
    struct Taxi *newTX = calloc(1, sizeof(struct Taxi));
    if (NULL == newTX)
    {
        return NULL;
    }

    TaxiCtorVoid(newTX);

    return newTX;
}

void deleteTaxiIMP(struct Taxi *tx)
{
    tx->m_pt.vtptr->PublicTransportDtor(AS_PT tx);
    free(tx);
}

int main()
{
    int i = 0;
    union temp_args u_args;
    struct Minibus m;
    struct Minibus m2;
    struct SpecialTaxi st;
    struct PublicTransport *array[3] = {NULL};
    struct PublicTransport arr2[3] = {0};
    struct Minibus arr3[4] = {0};
    struct Taxi *arr4 = NULL;

    MinibusCtorVoid(&m);
    PrintInfoMinibus(&m);
    
    PublicTransportDisplayVoid(PrintInfoInt(&u_args.temp_pt1, 3));
    PublicTransportDtor(&u_args.temp_pt1);
    
    array[0] = AS_PT newMinibusIMP();
    array[1] = AS_PT newTaxiIMP();
    array[2] = AS_PT newMinibusIMP();
    
    for (i = 0; i < 3; ++i)
    {
        array[i]->vtptr->PublicTransportDisplayVoid(array[i]);
    }

    deleteMinibus(AS_MB array[0]);
    deleteTaxiIMP(AS_TX array[1]);
    deleteMinibus(AS_MB array[2]);
    
    
    MinibusCtorVoid(&u_args.temp_mb1);
    PublicTransportCCtor(&arr2[0], AS_PT &u_args.temp_mb1);
    MinibusDtor(&u_args.temp_mb1);

    TaxiCtorVoid(&u_args.temp_tx1);
    PublicTransportCCtor(&arr2[1], AS_PT &u_args.temp_tx1);
    TaxiDtor(&u_args.temp_tx1);

    PublicTransportCtorVoid(&u_args.temp_pt1);
    PublicTransportCCtor(&arr2[2], &u_args.temp_pt1);
    PublicTransportDtor(&u_args.temp_pt1);

    for (i = 0; i < 3; ++i)
    {
        arr2[i].vtptr->PublicTransportDisplayVoid(&arr2[i]);
    }

    PrintInfoPublicTransport(&arr2[0]);

    PublicTransportPrintCountVoid();
    
    MinibusCtorVoid(&m2);
    PublicTransportPrintCountVoid();

    for (i = 0; i < 4; ++i)
    {
        MinibusCtorVoid(&arr3[i]);
    }

    arr4 = newTaxiArrIMP(4);
    deleteTaxiArrIMP(arr4);
    
    printf("%d\n", 1 < 2 ? 2 : 1);
    printf("\n");
    printf("%d\n", 1 < (int)2.0f ? (int)2.0f : 1);
    
    SpecialTaxiCtorVoid(&st);
    
    TaxiCCtor(&u_args.temp_tx1, AS_TX &st);

    DisplayTaxi(&u_args.temp_tx1);
    TaxiDtor(&u_args.temp_tx1);

    SpecialTaxiDtor(&st);
    for (i = 3; i >= 0; --i)
    {
        MinibusDtor(&arr3[i]);
    }

    MinibusDtor(&m2);
    
    for (i = 2; i >=0; --i)
    {
        PublicTransportDtor(&arr2[i]);
    }
    
    MinibusDtor(&m);

    return 0;
}



/* int main()
{
    struct PublicTransport pt1;
    struct Minibus mb1;
    struct Taxi tx1;
    struct SpecialTaxi st1;


    struct PublicTransport *pt2 = AS_PT calloc(sizeof(struct Minibus), 1);
    struct PublicTransport *pt3 = AS_PT calloc(sizeof(struct Taxi), 1);
    struct PublicTransport *pt4 = AS_PT calloc(sizeof(struct SpecialTaxi), 1);

    printf("\n");
    PublicTransportCtorVoid(&pt1);
    MinibusCtorVoid((struct Minibus *)pt2);  
    MinibusCtorVoid(&mb1);
    TaxiCtorVoid(&tx1);
    TaxiCtorVoid(AS_TX pt3);
    SpecialTaxiCtorVoid(&st1);
    SpecialTaxiCtorVoid(AS_ST pt4);
    printf("\n");
    printf("\n");

    PublicTransportPrintCountVoid();

    MinibusWashInt(AS_MB pt2, 5);
    MinibusDisplayVoid(AS_MB pt2);
    MinibusWashInt(&mb1, 5);
    MinibusDisplayVoid(&mb1);
    TaxiDisplayVoid(&tx1);
    SpecialTaxiDisplayVoid(&st1);
    SpecialTaxiDisplayVoid(AS_ST pt4);
    printf("\n");
    printf("\n");


    PublicTransportDtor(&pt1);
    pt2->vtptr->PublicTransportDtor(pt2);
    MinibusDtor(&mb1);
    TaxiDtor(&tx1);
    pt3->vtptr->PublicTransportDtor(pt3);
    SpecialTaxiDtor(&st1);
    pt4->vtptr->PublicTransportDtor(pt4);
    
    PublicTransportPrintCountVoid();

    printf("\n\n");
    return 0;
} */
