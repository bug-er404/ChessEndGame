/**
*  KingPiece.hpp
*  KingPiece class. Inherits from ChessPiece class.
*  Chess End Game Configurations.
*
*  Created by Salil Maharjan on 11/27/19.
*  Copyright © 2019 Salil Maharjan. All rights reserved.
*/

#ifndef KingPiece_hpp
#define KingPiece_hpp


#include <stdio.h>

#include "ChessBoard.hpp"
#include "ChessPiece.hpp"

class KingPiece : public ChessPiece
{
public:
    /// King Piece Constructor
    KingPiece(class ChessBoard* a_board, Position a_cell, PieceColor a_pieceColor);
    
    /// King Piece Desstructor
    ~KingPiece();
    
    /// Overloaded move method to move King piece.
    int movePiece();
    
    /// Return piece type.
    PieceType getPieceType(){return KING;}
    
    /// Return character representation of the king chess piece.
    char pieceCharCode(){return 'K';}
    
//    /// Accessor to see if the King is on check.
//    bool getCheckmateStatus(){return m_onCheck;}
//    /// Mutator to change if the King is on check or not.
//    void setCheckmateStatus(bool a_onCheck){m_onCheck = a_onCheck;}
        
    /// Get possible moves for the king piece
    std::vector<Position> getPossibleMoves();
    
        ///
    //    int getMaximizingState(Position &a_pos);
    
private:
//    /// Bool variable if King is on check
//    bool m_onCheck;

    
    /// Greedy method for Black King Piece to get the distance to the White Rook.
    int distanceToRook(std::vector<Position> a_possibleMoves, Position a_posRook,  Position a_posKing);
    
    
};
#endif /* KingPiece_hpp */
