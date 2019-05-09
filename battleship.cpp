/*-----------------------------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class name here>
 *-----------------------------------------------------------------------------
 * Exercise Number: #exercise_number#
 * File:			battleship.c
 * Author(s):		Peter Bauer
 * Due Date:		#due#
 *-----------------------------------------------------------------------------
 * Description:
 * <your description here>
 *-----------------------------------------------------------------------------
*/
#include <stdio.h>
#include "battleship.h"

CellContent _my_field[FIELDSIZE][FIELDSIZE];
CellContent _other_field[FIELDSIZE][FIELDSIZE];
CellContent _my_guess[FIELDSIZE][FIELDSIZE];
/**
*** Loads the two files battleship.my and battleship.op which hold the fields
*** of the players. The files hold a stream of 10 times 10 values of type
*** CellContent.
*/
void load_game()
{
    FILE* my_ship = fopen("battleship.my", "rw");
    FILE* other_ship = fopen("battleship.op", "rw");
    
       
    for(int i = 0; i < FIELDSIZE; i++)
    {
        for(int j = 0; j < FIELDSIZE; j++)
        {
            fread(&_my_field[i][j], sizeof(CellContent), 1, my_ship);
            fread(&_other_field[i][j], sizeof(CellContent), 1, other_ship);
            _my_guess[i][j] = Unknown;
        }
    }
}

bool is_in_range(int row, int col)
{
    return row < FIELDSIZE && col < FIELDSIZE && col >= 0 && row >= 0 ;
}

/**
*** @param row The row where we get the shot.
*** @param col The col where we get the shot.
*** @return The value of cell indicated by row and column of the own field (filled
*** with the values of battleship.my). If row/col point outside the field the
*** value OutOfRange is returned.
*/
CellContent get_shot(int row, int col){
    
    if(!is_in_range(row, col)) return OutOfRange;
    return _my_field[row][col];
}


void fill_with_water(int row, int col)
{
    if(is_in_range(row, col))
    {
        _my_guess[row][col] = Water;
    }
}

/**
*** Sets the row and column of the my guesses table to the value held in the
*** opponents field. If this is a boat all surrounding cells are marked as water.
*** @param row The row where we place the shot
*** @param col The columnt where we place the shot.
*** @return True if target field is valid, i.e., inside the field, False otherwise.
*/
bool shoot(int row, int col){
    if(is_in_range(row, col))
    {
        _my_guess[row][col] = _other_field[row][col];
        if(_my_guess[row][col] == Boat)
        {
            fill_with_water(row+1, col);
            fill_with_water(row+1, col+1);
            fill_with_water(row, col+1);
            fill_with_water(row-1, col);
            fill_with_water(row-1, col-1);
            fill_with_water(row-1, col+1);
            fill_with_water(row+1, col-1);
            fill_with_water(row, col-1);
        }
        return true;
    }
    return false;
}

/**
*** @param row The row where we want to get our own guess.
*** @param col The column where we want to get our own guess.
*** @return The value of the table with my guesses at row and column. If row/col
*** is outside the field OutOfRange is returned.
*/
CellContent get_my_guess(int row, int col){
    if(!is_in_range(row, col)) return OutOfRange;
    return _my_guess[row][col];
}