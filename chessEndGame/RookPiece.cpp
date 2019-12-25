/**
*  RookPiece.cpp
*  Implements RookPiece.hpp class.
*  Chess End Game
*
*  Created by Salil Maharjan on 11/27/19.
*  Copyright © 2019 Salil Maharjan. All rights reserved.
*/


#include <iostream>

#include "RookPiece.hpp"
#include "ChessPiece.hpp"
#include "GlobalCounter.hpp"

/**
 * Rook Piece class constructor.
 * Constructor: Creates a RookPiece in a_board chess board at cell position a_cell.
 * Calls ChessPiece constructor to construct a chesspiece.
 * @param a_board ChessBoard* ChessBoard where the game is being played.
 * @param a_cell Position (x,y) position to place king piece.
 */
RookPiece::RookPiece(class ChessBoard* a_board, Position a_cell, PieceColor a_pieceColor) : ChessPiece(a_board, a_cell, a_pieceColor)
{
  // What do we need here hmm
}

/**
 * Rook Piece class destructor.
 * Destructor: Destroys the rook piece from the board.
 *
 */
RookPiece::~RookPiece()
{
  this->m_board=NULL;
  // Moving piece out of the board.
  this->m_piecePosition.x = 9;
  this->m_piecePosition.y = 9;
}

/**
* Move method for Rook Piece.
* Overloaded move method to move Rook piece.
*/
int RookPiece::movePiece()
{
//    // ALGORITHM FOR WHITES
//    std::vector<Position> t_possibleMoves = getPossibleMoves();
//
//    for(int i=0; i<t_possibleMoves.size(); i++)
//        std::cout<<t_possibleMoves[i].x<<" "<<t_possibleMoves[i].y<<std::endl;
//
//    // King is killed if size is 1
//    this->updatePieceCell(t_possibleMoves[0]);
//    //std::cout<<this->pieceCharCode()<<" "<<t_possibleMoves[1].x<<" "<<t_possibleMoves[1].y<<std::endl;
    
    return 0;
}

/**
* Method to get possible moves for a Rook Piece.
* @return vector<Position> Array of possible positions the Rook piece can make a valid move to.
*/
std::vector<Position> RookPiece::getPossibleMoves()
{
    // temp variable to hold possible moves
    std::vector<Position> t_posssibleMoves;
    
    // Temp position variable
    Position temp;
    
    // Position of black king
    Position t_king = this->m_board->getPiecePosition(BLACK, KING);
    
    // Checking if Black King piece is on the path
    // If it is it can be killed. End of game.
    temp.x = this->m_piecePosition.x;
    temp.y = this->m_piecePosition.y;
    if((t_king.x==temp.x || t_king.y == temp.y) && checkPath(temp, t_king))
    {
        t_posssibleMoves.push_back(t_king);
        return t_posssibleMoves;
    }
    
    // Checking vertical rook moves:
    temp.y = this->m_piecePosition.y;
    for(int i=0; i<=7; i++){
        temp.x = i;
        // Valid cell
        if(this->m_board->getPiece(temp)==NULL)
            t_posssibleMoves.push_back(temp);
        // White Piece then break because the rook can't move further
        else if(this->m_board->getPiece(temp)!= this && this->m_board->getPiece(temp)->pieceColorCode()=='W')
            break;
    }
    
    // Checking horizontal rook moves:
    temp.x = this->m_piecePosition.x;
    for(int i=0; i<=7; i++){
        temp.y = i;
        // Valid cell
        if(this->m_board->getPiece(temp)==NULL)
            t_posssibleMoves.push_back(temp);
        // White Piece then break because the rook can't move further
        else if(this->m_board->getPiece(temp)!= this && this->m_board->getPiece(temp)->pieceColorCode()=='W')
            break;
    }
    
    return t_posssibleMoves;
}

/**
* Method to check path of the Rook if there are obstructions.
* Returns a bool depending on if there are obstructions on the path of the Rook or not.
 * @param a_current Position Current position of the Rook
 * @param a_pos Position The rook's destination position.
* @return bool True if there are no obstructions and the rook can move, false otherwise.
*/
bool RookPiece::checkPath(Position a_current, Position a_pos)
{
    // Bool to check path
    bool canMove = true;
    // Temp Position variable
    Position temp = a_current;
    
    // Checking horizontal move
    for(int i=a_current.x+1; i<=a_pos.x; i++)
    {
        temp.x = i;
        if(m_board->getPiece(temp)!=NULL && m_board->getPiece(temp)->pieceColorCode()=='W')
            canMove=false;
    }
    
    // Checking vertical move
    temp = a_current;
    for(int i=a_current.y+1; i<=a_pos.y; i++)
    {
        temp.y = i;
        if(m_board->getPiece(temp)!=NULL && m_board->getPiece(temp)->pieceColorCode()=='W')
            canMove=false;
    }
    
    return canMove;
}
