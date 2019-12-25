/**
*  ChessBoard.hpp
*  ChessBoard Class header file.
*  Class that implementss a chess board.
*
*
*  Created by Salil Maharjan on 11/27/19.
*  Copyright © 2019 Salil Maharjan. All rights reserved.
*/

#ifndef ChessBoard_hpp
#define ChessBoard_hpp

#include "ChessPiece.hpp"
#include <stdio.h>


class KingPiece;
class RookPiece;

/// Singleton Board Class
class ChessBoard
{
public:
    /// Constructor to initialize a single chessboard.
    ChessBoard(Position a_whiteRook, Position a_whiteKing, Position a_blackKing);
    
    /// Class Deconstructor
    ~ChessBoard();
    
    /// Class Accessors
    ChessBoard* getBoard(ChessPiece a_piece){return m_gameInstance;}
    bool getPieceTurn(){return m_pieceTurn;}
    ChessPiece* getPiece(Position a_cell);
    Position getPiecePosition(PieceColor a_color, PieceType a_type);
    
    /// Class Mutators
    void setPiece(Position a_cell, ChessPiece* a_piece);

    /// Next State simulation method - simulates the next state in the chess board.
    int simulateNextState();
    
    /// Chess board display method.
    void displayBoard();
    
    /// Sets chess piece for states
    void stateSetPiece(Position a_current, Position a_dest);

    /// Heuristic for minimax algorithm.
    int cornerBlackKing(ChessBoard* a_node);
    
    /// Implementation of minimax algorithm with alpha beta pruning.
    int minimax(ChessBoard* a_node, int a_depth, int a_alpha, int a_beta, bool a_color, int &a_count);
    
    /// Method to write the final results to the result file.
    void writeResults(PieceColor a_type);
    
private:
    /// Move Chess Piece of the passed color.
    void movePiece(bool a_pieceTurn);

    /// CHESS GAME  VARIABLES:
    /// Variable to hold the  game instance.
    ChessBoard* m_gameInstance;
    
    /// Chessboard grid where the game is played.
    ChessPiece* m_chessGrid[8][8];
    
    /// Chess pieces
    KingPiece* m_whiteKingPiece;
    KingPiece* m_blackKingPiece;
    RookPiece* m_whiteRookPiece;
    
    
    /// Bool to hold color turn
    /// 1 for White and 0 for Black.
    /// Game starts with white's move.
    bool m_pieceTurn = 1;
    
    /// Counter for number of steps in the game.
    int count;

};

#endif /* ChessBoard_hpp */
