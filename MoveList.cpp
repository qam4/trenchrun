/*
 * File:   MoveList.cpp
 *
 */

#include "MoveList.h"

bool MoveList::contains(Move_t move){
    for(int i = 0; i < size; i++){
        if(data[i] == move) return true;
    }
    return false;
}

bool MoveList::contains_duplicates(){
    for(int i = 0; i < size; i++){
        for(int j = i+1; j < size; j++){
            if(data[i] == data[j]) return true;
        }
    }
    return false;
}

bool MoveList::contains_valid_moves(const class Board &board){
    for(int i = 0; i < size; i++){
        if(!is_valid_move(data[i], board)) return false;
    }
    return true;
}
