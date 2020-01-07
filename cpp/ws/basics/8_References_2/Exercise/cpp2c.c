#include <stdio.h>          /* printf */
#include <stdlib.h>         /* malloc */

#include "./../utils.hpp"   /* UNUSED */

#define AS_PT (struct PT *)
#define AS_MB (struct MB *)
#define AS_TX (struct TX *)
#define AS_ST (struct ST *)
#define AS_CV (struct CV *)

enum
{
    Dtor = 0,
    Display,
    Wash
};

typedef void (*virtual_funcs_t)();


struct PT
{
    virtual_funcs_t *PT_VT;
    int m_license_plate;
};

struct MB
{
    struct PT m_pt;
    int m_numSeats;
};

struct TX
{
    struct PT m_pt;
};

struct ST
{
    struct TX m_tx;
};

struct CV
{
    struct PT m_pt;
    struct PT * m_pt1;
    struct PT * m_pt2;
    struct MB m_m;
    struct TX m_t;
};

void PT_Ctor_PT(struct PT * this);
void PT_Dtor_PT(struct PT * this);
void PT_CCtor_PT(struct PT * this, struct PT * other);
void PT_display_PT(struct PT * this);
void PT_print_count_PT();
int PT_get_ID(struct PT * this);
/**************************************MB FUNCTIONS ********************************************/
void MB_Ctor_MB(struct MB * this);
void MB_CCtor_MB(struct MB * this, struct MB * other);
void MB_Dtor_MB(struct MB *this);
void MB_display_MB(struct MB * this);
void MB_wash_MB_Int(struct MB * this, int minutes);
/**************************************TX FUNCTIONS ********************************************/
void TX_Ctor_TX(struct TX * this);
void TX_CCtor_TX(struct TX * this, struct TX * other);
void TX_Dtor_TX(struct TX * this);
void TX_display_TX(struct TX * this);
/**************************************ST FUNCTIONS ********************************************/
void ST_Ctor_ST(struct ST * this);
void ST_CCtor_ST(struct ST * this, struct ST * other);
void ST_Dtor_ST(struct ST * this);
void ST_display_ST(struct ST * this);
/**************************************CV FUNCTIONS ********************************************/
/* void CV_Ctor_CV(struct CV * this); */
/* void CV_CCtor_CV(struct CV * this, struct CV * other) */
void CV_Dtor_CV(struct CV * this);
void CV_display_CV(struct CV * this);
/**********************************GENERAL FUNCTIONS ******************************************/
void GLOBAL_print_info_PT(struct PT * a);
void GLOBAL_print_info_VOID();
void GLOBAL_print_info_MB(struct MB *m);
struct PT *GLOBAL_print_info_INT(struct PT *pt, int i);
void GLOBAL_taxi_display();
struct TX *NewTaxiArr(int numOfObjects);
void DeleteTaxiArr(struct TX * taxiArr);
struct MB *NewMinibus();
void DeleteMinibus(struct MB *mb);
struct TX *NewTaxi();
void DeleteTaxi(struct TX *tx);
struct CV *NewConvoy();
struct CV *NewConvoyCCtor(struct CV *other);
void DeleteConvoy(struct CV * cv);

virtual_funcs_t g_PT_VT[] = {(void (*)())PT_Dtor_PT, (void (*)())PT_display_PT};
virtual_funcs_t g_MB_VT[] = {(void (*)())MB_Dtor_MB,  (void (*)())MB_display_MB,
                        (void (*)())MB_wash_MB_Int};
virtual_funcs_t g_TX_VT[] = {(void (*)())TX_Dtor_TX, (void (*)())TX_display_TX};
virtual_funcs_t g_ST_VT[] = {(void (*)())ST_Dtor_ST, (void (*)())ST_display_ST};
virtual_funcs_t g_CV_VT[] = {(void (*)())CV_Dtor_CV, (void (*)())CV_display_CV};


static int PT_s_count = 0;
/**************************************PT FUNCTIONS ********************************************/
void PT_Ctor_PT(struct PT * this)
{
    this->PT_VT = g_PT_VT;
    this->m_license_plate = ++PT_s_count;

    printf("PublicTransport::Ctor()%d\n", this->m_license_plate);
}

void PT_Dtor_PT(struct PT * this)
{
    this->PT_VT = g_PT_VT;
    --PT_s_count;
    printf("PublicTransport::Dtor()%d\n", this->m_license_plate);
}

void PT_CCtor_PT(struct PT * this, struct PT * other)
{
    (void)other;
    this->PT_VT = g_PT_VT;
    this->m_license_plate = ++PT_s_count;
    printf("PublicTransport::CCtor() %d\n", this->m_license_plate);
}

void PT_display_PT(struct PT * this)
{
    printf("PublicTransport::display(): %d\n", this->m_license_plate);
}

void PT_print_count_PT()
{
    printf("s_count: %d\n", PT_s_count);
}

int PT_get_ID(struct PT * this)
{
    return this->m_license_plate;
}

/**************************************MB FUNCTIONS ********************************************/
void MB_Ctor_MB(struct MB * this)
{
    PT_Ctor_PT(&this->m_pt);
    this->m_pt.PT_VT = g_MB_VT;
    this->m_numSeats = 20;
    printf("Minibus::Ctor()\n");
}

void MB_CCtor_MB(struct MB * this, struct MB * other)
{
    PT_CCtor_PT(AS_PT this, AS_PT other);
    this->m_pt.PT_VT = g_MB_VT;
    this->m_numSeats = other->m_numSeats;
    printf("Minibus::CCtor()\n");

}

void MB_Dtor_MB(struct MB *this)
{
    this->m_pt.PT_VT = g_MB_VT;
    printf("Minibus::Dtor()\n");
    PT_Dtor_PT(AS_PT this);
}

void MB_display_MB(struct MB * this)
{
    printf("Minibus::display() ID:%d", PT_get_ID(AS_PT this));
    printf(" num seats:%d\n", this->m_numSeats);
}

void MB_wash_MB_Int(struct MB * this, int minutes)
{
    printf("Minibus::wash(%d) ID:%d\n", minutes, PT_get_ID(AS_PT this));
}

/**************************************TX FUNCTIONS ********************************************/
void TX_Ctor_TX(struct TX * this)
{
    PT_Ctor_PT(AS_PT this);
    this->m_pt.PT_VT = g_TX_VT;
    printf("Taxi::Ctor()\n");
}

void TX_CCtor_TX(struct TX * this, struct TX * other)
{
    PT_CCtor_PT(AS_PT this, AS_PT other);
    this->m_pt.PT_VT = g_TX_VT;
    printf("Taxi::CCtor()\n");
}

void TX_Dtor_TX(struct TX * this)
{
    this->m_pt.PT_VT = g_TX_VT;
    printf("Taxi::Dtor()\n");
    PT_Dtor_PT(AS_PT this);
}

void TX_display_TX(struct TX * this)
{
    printf("Taxi::display() ID:%d\n", PT_get_ID(AS_PT this));
}

/**************************************ST FUNCTIONS ********************************************/
void ST_Ctor_ST(struct ST * this)
{
    TX_Ctor_TX(AS_TX this);
    this->m_tx.m_pt.PT_VT = g_ST_VT;
    printf("SpecialTaxi::Ctor()\n");
}

void ST_CCtor_ST(struct ST * this, struct ST * other)
{
    TX_CCtor_TX(AS_TX this, AS_TX other);
    this->m_tx.m_pt.PT_VT = g_ST_VT;
    printf("SpecialTaxi::CCtor()\n");
}

void ST_Dtor_ST(struct ST * this)
{
    this->m_tx.m_pt.PT_VT = g_ST_VT;
    printf("SpecialTaxi::Dtor()\n");
    TX_Dtor_TX(AS_TX this);
}

void ST_display_ST(struct ST * this)
{
    printf("SpecialTaxi::display() ID:%d\n", PT_get_ID(AS_PT this));
}

/**************************************CV FUNCTIONS ********************************************/
void CV_Ctor_CV(struct CV * this)
{
    PT_Ctor_PT(AS_PT this);
    this->m_pt.PT_VT = g_CV_VT;

    this->m_pt1 = AS_PT NewMinibus();
    this->m_pt2 = AS_PT NewTaxi();
    MB_Ctor_MB(&this->m_m);
    TX_Ctor_TX(&this->m_t);
}

void CV_CCtor_CV(struct CV * this, struct CV * other)
{
    PT_Ctor_PT(AS_PT this);
    this->m_pt.PT_VT = g_CV_VT;

    this->m_pt1 = AS_PT NewMinibus();
    this->m_pt2 = AS_PT NewTaxi();
    MB_CCtor_MB(&this->m_m, &other->m_m);
    TX_CCtor_TX(&this->m_t, &other->m_t);
}

void CV_Dtor_CV(struct CV * this)
{
    this->m_pt.PT_VT = g_CV_VT;

    DeleteMinibus(AS_MB this->m_pt1);
    DeleteTaxi(AS_TX this->m_pt2);
    TX_Dtor_TX(&this->m_t);
    MB_Dtor_MB(&this->m_m);
    PT_Dtor_PT(&this->m_pt);
    
}

void CV_display_CV(struct CV * this)
{
    this->m_pt1->PT_VT[Display](this->m_pt1);
    this->m_pt2->PT_VT[Display](this->m_pt2);
    MB_display_MB(&this->m_m);
    TX_display_TX(&this->m_t);
}

/**********************************GENERAL FUNCTIONS ******************************************/
void GLOBAL_print_info_PT(struct PT * a)
{
    a->PT_VT[Display](AS_PT a);
}

void GLOBAL_print_info_VOID()
{
    PT_print_count_PT();
}

void GLOBAL_print_info_MB(struct MB *m)
{
    m->m_pt.PT_VT[Wash](m, 3);
}

struct PT *GLOBAL_print_info_INT(struct PT *pt, int i)
{
    struct MB ret;
    (void)i;

    MB_Ctor_MB(&ret);
    printf("print_info(int i)\n");
    ret.m_pt.PT_VT[Display](&ret);

    PT_CCtor_PT(pt, AS_PT &ret);
    MB_Dtor_MB(&ret);

    return pt;
}

void GLOBAL_taxi_display(struct TX *s)
{
    s->m_pt.PT_VT[Display](s);
}


/******************************************EXTRAS***********************************************/
struct TX *NewTaxiArr(int numOfObjects)
{
    int i = 0;
    struct TX *taxiArr = NULL;

    taxiArr = (struct TX *)malloc((sizeof(struct TX) * numOfObjects) + sizeof(int));
    if(NULL == taxiArr)
    {
        return NULL;
    }

    *(int *)taxiArr = numOfObjects;
    taxiArr = (struct TX *)((char *)taxiArr + sizeof(int));

    for (i = 0; i < numOfObjects; ++i)
    {
        TX_Ctor_TX(taxiArr + i);
    }

    return taxiArr;
}

void DeleteTaxiArr(struct TX * taxiArr)
{
    int i = 0;
    int numOfObjects = *(int *)((char *)taxiArr - sizeof(int));

    for (i = numOfObjects - 1; i >= 0; --i)
    {
        taxiArr[i].m_pt.PT_VT[Dtor](&taxiArr[i]);
    }

    free((char *)taxiArr - sizeof(int));
}

struct MB *NewMinibus()
{
    struct MB *newMB = malloc(sizeof(struct MB));
    if (NULL == newMB)
    {
        return NULL;
    }

    MB_Ctor_MB(newMB);

    return newMB;
}

void DeleteMinibus(struct MB *mb)
{
    mb->m_pt.PT_VT[Dtor](mb);
    free(mb);
}

struct CV *NewConvoy()
{
    struct CV *newCV = malloc(sizeof(struct CV));
    if (NULL == newCV)
    {
        return NULL;
    }

    CV_Ctor_CV(newCV);

    return newCV;
}

struct CV *NewConvoyCCtor(struct CV *other)
{
    struct CV *newCV = malloc(sizeof(struct CV));
    if (NULL == newCV)
    {
        return NULL;
    }

    CV_CCtor_CV(newCV, other);

    return newCV;
}

void DeleteConvoy(struct CV * cv)
{
    cv->m_pt.PT_VT[Dtor](cv);
    free(cv);
}

struct TX *NewTaxi()
{
    struct TX *newTX = malloc(sizeof(struct TX));
    if (NULL == newTX)
    {
        return NULL;
    }

    TX_Ctor_TX(newTX);

    return newTX;
}

void DeleteTaxi(struct TX *tx)
{
    tx->m_pt.PT_VT[Dtor](tx);
    free(tx);
}

union temp_args
{
    struct PT temp_pt1;
    struct MB temp_mb1;
    struct TX temp_tx1;
};


int main()
{
    int i = 0;
    struct MB m;
    struct MB m2;
    struct ST st;
    union temp_args temp_args;
    struct PT *array[3];
    struct PT arr2[3];
    struct MB arr3[4];
    struct TX *arr4;
    struct CV *ts1;
    struct CV *ts2;

    MB_Ctor_MB(&m);
    GLOBAL_print_info_MB(&m);


    GLOBAL_print_info_PT(GLOBAL_print_info_INT(&temp_args.temp_pt1, 3));
    PT_Dtor_PT(&temp_args.temp_pt1);

    array[0] = AS_PT NewMinibus();
    array[1] = AS_PT NewTaxi();
    array[2] = AS_PT NewMinibus();

    
    for (i = 0; i < 3; ++i)
    {
        array[i]->PT_VT[Display](array[i]);
    }
    
    for (i = 0; i < 3; ++i)
    {
        array[i]->PT_VT[Dtor](array[i]);
    }

    
    MB_Ctor_MB(&temp_args.temp_mb1);
    PT_CCtor_PT(&arr2[0], AS_PT &temp_args.temp_mb1);
    MB_Dtor_MB(&temp_args.temp_mb1);
    TX_Ctor_TX(&temp_args.temp_tx1);
    PT_CCtor_PT(&arr2[1], AS_PT &temp_args.temp_tx1);
    TX_Dtor_TX(&temp_args.temp_tx1);
    PT_Ctor_PT(&temp_args.temp_pt1);
    PT_CCtor_PT(&arr2[2], &temp_args.temp_pt1);
    PT_Dtor_PT(&temp_args.temp_pt1);
    

    for (i = 0; i < 3; ++i)
    {
        arr2[i].PT_VT[Display](&arr2[i]);
    }
    

    GLOBAL_print_info_PT(&arr2[0]);
    

    PT_print_count_PT();
    

    MB_Ctor_MB(&m2);
    
    
    PT_print_count_PT();
    


    for (i = 0; i < 4; ++i)
    {
        MB_Ctor_MB(&arr3[i]);
    }
    


    arr4 = NewTaxiArr(4);
    
    DeleteTaxiArr(arr4);
    

    printf("%d\n", 1 > 2 ? 1 : 2);
    printf("%d\n", 1 > (int)2.0f ? 1 : (int)2.0f);
    
    ST_Ctor_ST(&st);
    

    TX_CCtor_TX(&temp_args.temp_tx1, AS_TX &st);
    GLOBAL_taxi_display(&temp_args.temp_tx1);
    TX_Dtor_TX(&temp_args.temp_tx1);
    
    

    ts1 = NewConvoy();
    
    ts2 = NewConvoyCCtor(ts1);
    

    ts1->m_pt.PT_VT[Display](ts1);
    
    ts2->m_pt.PT_VT[Display](ts2);
    
    DeleteConvoy(ts1);
    
    ts2->m_pt.PT_VT[Display](ts2);
    
    DeleteConvoy(ts2);

    /*  cleanup */
    /*  */

    
    
    ST_Dtor_ST(&st);
    for (i = 3; i >= 0; --i)
    {
        MB_Dtor_MB(&arr3[i]);
    }
    MB_Dtor_MB(&m2);
    for(i = 2; i >= 0; --i)
    {
        PT_Dtor_PT(&arr2[i]);
    }

    
    MB_Dtor_MB(&m);

    return 0;
}
