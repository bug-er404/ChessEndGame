/**
*  ChessPiece.hpp
*  ChessPiece Class header file.
*  Class that implementss chess pieces.
*
*
*  Created by Salil Maharjan on 11/27/19.
*  Copyright © 2019 Salil Maharjan. All rights reserved.
*/

#pragma once

#ifndef ChessPiece_hpp
#define ChessPiece_hpp


#include <stdio.h>
#include <vector>


/// Chess piece type
enum PieceType
{
    KING,
    ROOK
};

/// Chess color type
enum PieceColor
{
    BLACK,
    WHITE
};

/// Position on the chess board.
struct Position
{
    int x;
    int y;
};


class ChessPiece
{
public:
    /// ChessPiece constructor - Creates a chess piece in the chess board at passed position.
    ChessPiece(class ChessBoard* a_board, Position a_cell, PieceColor a_pieceColor);

    /// ChessPiece destructor
    virtual ~ChessPiece();
    
    /// Moves the chess piece on the board.
    virtual int movePiece()=0;
    
    /// Acccessors:
    /// Get Piece Type
    virtual PieceType getPieceType()=0;
    ///  Get Piece Position
    Position getPiecePosition(){return m_piecePosition;}
    /// Get character representation of the chess piece.
    virtual char pieceCharCode()=0;
    /// Get color representation of the chess piece.
    char pieceColorCode(){return (m_pieceColor==WHITE)? 'W':'B';}
    /// Validate cell is on the board.
    bool checkCell(Position a_cell);
    
    /// Get possible moves for the chess piece
    virtual std::vector<Position> getPossibleMoves()=0;
    
    /// Gets the maximizing state for the chess piece 
    int getMaximizingState(Position &a_pos);
    
    /// Moves chess piece to new position (x, y)
    void updatePieceCell(Position a_cell);
    
protected:
    
    /// Variable that holds the position of a chess piece.
    Position m_piecePosition;
    /// Pointer to the chess board.
    ChessBoard* m_board;
    /// Variable that holds the color of the chess piece.
    PieceColor m_pieceColor;

private:
    
};

#endif /* ChessPiece_hpp */
