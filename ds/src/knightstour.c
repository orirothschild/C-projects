/***********************************
*   RC1                            *
*   Knights Tour                   *
*   written by: Hadar Klein        *
*   date: 21.1.19                  *
*   reviewed by: Ori Friedman      *
*                                  *
***********************************/

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "utils.h"
#include "bit_array.h"

const int g_SIZE = 8;
const int g_TABLE_SIZE = 64;
const int EDGE_OF_BOARD = 7;


enum warn
{
    NOT_WARN = 0,
    WARN
};

enum direction
{
    UP_RIGHT,
    UP_LEFT,
    RIGHT_UP,
    RIGHT_DOWN,
    DOWN_RIGHT,
    DOWN_LEFT,
    LEFT_UP,
    LEFT_DOWN,
    NUM_OF_DIRECTIONS
};

typedef struct position
{
    int x;
    int y;
}position_t;

typedef struct temp_position
{
    position_t post;
    int num_of_legal_moves;
}temp_position_t;


position_t POSITION_TABLE[NUM_OF_DIRECTIONS] = {0};

static void Init(void);
/* static void PrintTheBoardBit(unsigned long board); */
static void PrintTheBoard(int *moves);
static int GetArrayPosition(position_t pos);
static int CheckMoveIMP(position_t pos);
static int IsMoveValidIMP(position_t pos, unsigned long bit_arr);
static position_t NextMoveIMP(position_t pos, int idx);
static int KnightsTourIMP(position_t pos, int *moves, unsigned long bit_arr,
                          int warn_flag);
static int KnightsTour(position_t pos, int *moves);
static void ChooseNextMoveIMP(position_t pos, temp_position_t *legal_moves_arr,
                              unsigned long bit_arr, int warn_flag);
static void SortArrayByValue(temp_position_t *arr, int warn_flag);
static position_t UserInput();





int main()
{
    position_t pos = {0};
    int *moves = calloc(64, sizeof(int));
    if (NULL == moves)
    {
        return 1;
    }

    Init();
    pos = UserInput();

    if (-1 == pos.x || -1 == pos.y)
    {
        return 0;
    }

    if (SUCCESS == KnightsTour(pos, moves))
    {
        PrintTheBoard(moves);
    }
    else
    {
        printf("Could not find a valid path\n");
    }

    free(moves);
    
    return 0;
}


static position_t UserInput()
{
    position_t pos = {0};
    printf("Please input a row and col to start with.\n");
    printf("Both must be between 0 and 7, enter -1 to exit\n");
    printf("Row:");
    scanf("%d", &pos.y);
    printf("Column:");
    scanf("%d", &pos.x);

    while (False == CheckMoveIMP(pos))
    {
        if (-1 == pos.x)
        {
            printf("Exiting\n");
            break;
        }
        printf("Incorrect input. Try Again\n");
        printf("Row:");
        scanf("%d", &pos.y);
        printf("Column:");
        scanf("%d", &pos.x);
    }

    return pos;
}

static void Init(void)
{
    position_t OnePosTwoNeg;
    position_t OneNegTwoNeg;
    position_t OnePosTwoPos;
    position_t OneNegTwoPos;
    position_t TwoPosOnePos;
    position_t TwoPosOneNeg;
    position_t TwoNegOnePos;
    position_t TwoNegOneNeg;

    TwoNegOnePos.x = -2;
    TwoNegOnePos.y =  1;

    OneNegTwoPos.x = -1;
    OneNegTwoPos.y =  2;

    OnePosTwoPos.x =  1;
    OnePosTwoPos.y =  2;

    TwoPosOnePos.x =  2;
    TwoPosOnePos.y =  1;

    TwoPosOneNeg.x =  2;
    TwoPosOneNeg.y = -1;

    OnePosTwoNeg.x =  1;
    OnePosTwoNeg.y = -2;
    
    OneNegTwoNeg.x = -1;
    OneNegTwoNeg.y = -2;

    TwoNegOneNeg.x = -2;
    TwoNegOneNeg.y = -1;

    POSITION_TABLE[0] = TwoNegOnePos;
    POSITION_TABLE[1] = OneNegTwoPos;

    POSITION_TABLE[2] = OnePosTwoPos;
    POSITION_TABLE[3] = TwoPosOnePos;

    POSITION_TABLE[4] = TwoPosOneNeg;
    POSITION_TABLE[5] = OnePosTwoNeg;

    POSITION_TABLE[6] = OneNegTwoNeg;
    POSITION_TABLE[7] = TwoNegOneNeg;
}


/* static void PrintTheBoardBit(unsigned long board)
{
   int i = 0;
   int j = 0;
   int mask = 1;

   for (i = 0; i < 8; ++i)
   {
       for (j = 0; j < 8; ++j)
       {
           if (1 == (mask & board))
           {
               printf("1   ");
           }
           else
           {
               printf("0   ");
           }
           board = board >> 1;
       }
       printf("\n\n");
   }
   printf("\n\n\n\n\n");
} */


static void PrintTheBoard(int *moves)
{
    int i = 0;

    assert(NULL != moves);

    for (i = 1; i <= 64; ++i)
    {
        printf("%d", moves[i-1]);
        if (0 != i % 64)
        {
            printf("->\t");
        }
        if (0 == i % 8)
        {
            printf("\n");
        }
    }

    printf("\n");
}


static int GetArrayPosition(position_t pos)
{
    return (((pos.y * g_SIZE) + pos.x));
}


static int CheckMoveIMP(position_t pos)
{
    int position = GetArrayPosition(pos);

    if (0 > pos.x || EDGE_OF_BOARD < pos.x)
    {
        return False;
    }

    if (0 > pos.y || EDGE_OF_BOARD < pos.y)
    {
        return False;
    }

    if (0 > position || g_TABLE_SIZE < position)
    {
        return False;
    }

    return True;
}


static int IsMoveValidIMP(position_t pos, unsigned long bit_arr)
{
    int position = GetArrayPosition(pos);

    return (CheckMoveIMP(pos) && !BArrIsBitOn(bit_arr, position));
}


static position_t NextMoveIMP(position_t pos, int idx)
{
    position_t next_move = {0};

    next_move.x = pos.x + POSITION_TABLE[idx].x;
    next_move.y = pos.y + POSITION_TABLE[idx].y;
    
    return next_move;
}


static position_t GetNextMoveIMP(position_t pos,
                                 temp_position_t *legal_moves_arr,
                                 int idx,
                                 int warn_flag)
{
    if (0 == warn_flag)
    {
        return NextMoveIMP(pos, idx);
    }

    return legal_moves_arr[idx].post;
}


static void SortArrayByValue(temp_position_t *arr, int warn_flag)
{
    temp_position_t temp = {0};
    int i = 0;
    int j = 0;

    for (i = 0; i < NUM_OF_DIRECTIONS * warn_flag; ++i)
    {
        for (j = i + 1; j < NUM_OF_DIRECTIONS; ++j)
        {
            if (arr[j].num_of_legal_moves < arr[i].num_of_legal_moves)
            {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}


static void ChooseNextMoveIMP(position_t pos, temp_position_t *legal_moves_arr,
                              unsigned long bit_arr, int warn_flag)
{
    position_t next_move = {0};
    position_t temp_move = {0};
    unsigned long temp_array = 0;
    int position = 0;
    int i = 0;
    int j = 0;

    for (i = 0; i < NUM_OF_DIRECTIONS * warn_flag; ++i)
    {
        next_move = NextMoveIMP(pos, i);
        if (1 == IsMoveValidIMP(next_move, bit_arr))
        {
            legal_moves_arr[i].post.x = next_move.x;
            legal_moves_arr[i].post.y = next_move.y;
            position = GetArrayPosition(next_move);

            temp_array = BArrSetBitOn(bit_arr, position);
            for (j = 0; j < NUM_OF_DIRECTIONS; ++j)
            {
                temp_move = NextMoveIMP(next_move, j);
                if (1 == IsMoveValidIMP(temp_move, bit_arr) ||  
                    1 == BArrAreAllBitsOn(temp_array))
                {
                    ++legal_moves_arr[i].num_of_legal_moves;
                }
            }
            temp_array = bit_arr; 
        }
    }

    SortArrayByValue(legal_moves_arr, warn_flag);   
}


static int KnightsTour(position_t pos, int *moves)
{
    unsigned long bit_arr = 0ul;
    int warn_flag = 0;

    printf("please choose whether to use Warnsdorf (1), or not (0)\n");
    scanf("%d", &warn_flag);
    printf("\n");

    if (SUCCESS == KnightsTourIMP(pos, moves, bit_arr, warn_flag))
    {
        return SUCCESS;
    }

    return FAILURE;
}


static int KnightsTourIMP(position_t pos, int *moves, unsigned long bit_arr,
                          int warn_flag)
{
    int i = 0;
    int bit_pos = GetArrayPosition(pos);
    position_t new_pos = {0};
    temp_position_t legal_moves_arr[NUM_OF_DIRECTIONS] = {0};
    
    *moves = bit_pos;
    
    bit_arr = BArrSetBitOn(bit_arr, bit_pos);
    if (True == BArrAreAllBitsOn(bit_arr))
    {
        return SUCCESS;
    }

    if (WARN == warn_flag)
    {
        ChooseNextMoveIMP(pos, &legal_moves_arr[0], bit_arr, warn_flag);
    }
    

    for (i = 0; i < NUM_OF_DIRECTIONS; ++i)
    {
        new_pos = GetNextMoveIMP(pos, legal_moves_arr, i, warn_flag);

        if ((0 == warn_flag || 0 != legal_moves_arr[i].num_of_legal_moves) &&
            1 == IsMoveValidIMP(new_pos, bit_arr))
        {
            if (SUCCESS == KnightsTourIMP(new_pos, moves + 1, bit_arr,
                                          warn_flag))
            {
                return SUCCESS;
            }
        }
    }

    return FAILURE;
}

