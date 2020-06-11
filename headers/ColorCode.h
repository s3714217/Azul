
#ifndef ColorCode_h
#define ColorCode_h

//Color Code
#define RED    'R'
#define BLACK 'U'
#define YELLOW 'Y'
#define DARK_BLUE  'B'
#define LIGHT_BLUE  'L'

#define EMPTY_RED    'r'
#define EMPTY_BLACK 'u'
#define EMPTY_YELLOW 'y'
#define EMPTY_DARK_BLUE  'b'
#define EMPTY_LIGHT_BLUE  'l'

//Other Code
#define FIRST_PLAYER  'F'
#define EMPTY  '.'
#define OCCUPIED 'o'
#define COUNTED 'c'

//number
#define TOTAL_TILE 100
#define MAX_REMAIN 3
#define BROKEN_LEN 7
#define BOARD_SIZE 5
#define NUMBEROFCOLOUR 5
#define NUMBEROFTILE 4
#define MAX_PLAYER 4

//console colour
#define C_BLACK "\x1b[30m"
#define C_RED "\x1b[31m"
#define C_YELLOW "\x1b[33m"
#define C_DARK_BLUE "\x1b[34m"
#define C_LIGHT_BLUE "\x1b[36m"
#define NORMAL "\x1b[0m"
#define C_FIRST_PLAYER "\u26C4"
#define C_CURSOR "\u261E"

#define TWO_P_FAC  6
#define THREE_P_FAC 8
#define FOUR_P_FAC  10

typedef char Colour;

#endif
