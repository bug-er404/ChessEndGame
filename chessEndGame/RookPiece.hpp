/**
*  RookPiece.hpp
*  RookPiece class. Inherits from ChessPiece class.
*  Chess End Game Configurations.
*
*  Created by Salil Maharjan on 11/27/19.
*  Copyright © 2019 Salil Maharjan. All rights reserved.
*/

#ifndef RookPiece_hpp
#define RookPiece_hpp

#include <stdio.h>

#include "ChessBoard.hpp"
#include "ChessPiece.hpp"

class RookPiece: public ChessPiece
{
public:
    /// Rook Piece Constructor
    RookPiece(class ChessBoard* a_board, Position a_cell, PieceColor a_pieceColor);
    
    /// Rook Piece Desstructor
    ~RookPiece();
    
    /// Overloaded move method to move Rook piece.
    int movePiece();
    
    /// Return piece type.
    PieceType getPieceType(){return ROOK;}
    
    /// Return character representation of the king chess piece.
    char pieceCharCode(){return 'R';}
    
    /// Get possible moves for the rook
    std::vector<Position> getPossibleMoves();
    
private:
    
    /// Method to check path of the Rook if there are obstructions
    bool checkPath(Position a_current, Position a_pos);
    
    
};

#endif /* RookPiece_hpp */
