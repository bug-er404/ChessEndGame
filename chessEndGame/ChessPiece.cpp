/**
*  ChessPiece.cpp
*  Implementation of ChessPiece.hpp class.
*
*
*  Created by Salil D. Maharjan on 11/27/19.
*  Copyright © 2019 Salil Maharjan. All rights reserved.
*/

#include<iostream>

#include "ChessPiece.hpp"
#include "ChessBoard.hpp"
#include "GlobalCounter.hpp"


/**
 * Constructor for ChessPiece Class.
 * Constructor: Creates a chess piece on the board at position (x,y)
 * @param a_board ChessBoard* Board where the game is being played.
 * @param a_cell Position (x,y) position in the board.
 * @param a_pieceColor PieceColor Chess Piece Color.
 */
ChessPiece::ChessPiece(class ChessBoard* a_board, Position a_cell, PieceColor a_pieceColor)
{
    m_board = a_board;
    m_piecePosition = a_cell;
    m_pieceColor = a_pieceColor;
    m_board->setPiece(a_cell, this);
}
/**
 * Empty Destructor for ChessPiece class.
 */
ChessPiece::~ChessPiece()
{

}

/**
 * Method to check if cell is in range.
 * Checks if a position is in the board or out of range.
 * @param a_cell Position (x,y) position in the board.
 * @return bool if Position (x,y) is in the board.
 */
bool ChessPiece::checkCell(Position a_cell)
{
    return (a_cell.x>=0) && (a_cell.x<8) && (a_cell.y>=0) && (a_cell.y<8);
}


/**
 * ChessPiece move method on the board.
 * Moves chess piece from (x,y) to new position (a_x, a_y).
 * @param a_cell Position (x,y) position in the board.
 */
void ChessPiece::updatePieceCell(Position a_cell)
{
    // Check if there is a piece on the position:
    if(m_board->getPiece(a_cell)==NULL)
           m_board->setPiece(a_cell, this);
    else{
        // Checking which piece is killed and displaying result accordingly
        if(m_board->getPiece(a_cell)->getPieceType()==KING && m_board->getPiece(a_cell)->pieceColorCode()=='B')
        {
            std::cout<<"White Wins!"<<std::endl;
            // Deleting piece and updating position
            m_board->getPiece(a_cell)->~ChessPiece();
            m_board->setPiece(this->getPiecePosition(), NULL);
            m_board->setPiece(a_cell, this);
            m_board->writeResults(WHITE);
            exit(1);
            // Add to file
            
        }
        else if(m_board->getPiece(a_cell)->getPieceType()==KING && m_board->getPiece(a_cell)->pieceColorCode()=='W')
        {
            std::cout<<"Black Wins!"<<std::endl;
            // Deleting piece and updating position
            m_board->getPiece(a_cell)->~ChessPiece();
            m_board->setPiece(this->getPiecePosition(), NULL);
            m_board->setPiece(a_cell, this);
            m_board->writeResults(BLACK);
            exit(1);
        }
        else if(m_board->getPiece(a_cell)->getPieceType()==ROOK && m_board->getPiece(a_cell)->pieceColorCode()=='W')
        {
            std::cout<<"The Game is tied because of insufficient mating material."<<std::endl;
            // Deleting piece and updating position
            m_board->getPiece(a_cell)->~ChessPiece();
            m_board->setPiece(this->getPiecePosition(), NULL);
            m_board->setPiece(a_cell, this);
            m_board->writeResults(BLACK);
            exit(1);
        }
        else{// some error
            
        }
            
        // Deleting piece and updating position
        m_board->getPiece(a_cell)->~ChessPiece();
        m_board->setPiece(a_cell, this);
        
    }
//    std::cout<<"CPupdate1:"<<this->pieceCharCode()<<" "<<m_piecePosition.x<<" "<<m_piecePosition.y<<std::endl;
    
    //Clearing (x,y) and updating position
    m_board->setPiece(m_piecePosition, NULL);
    m_piecePosition = a_cell;
//    std::cout<<"CPupdate1:"<<this->pieceCharCode()<<" "<<m_piecePosition.x<<" "<<m_piecePosition.y<<std::endl;
}

/**
* Method to get the maximizing state for a chess piece.
* @param a_pos Position (x,y) position on the board passeed by reference. The position is updated with the maximizing position.
* @return int the maximum score the maximizing state has.
*/
int ChessPiece::getMaximizingState(Position &a_pos)
{
    // State visited counter:
    int counter = 0;
    
    std::vector<Position> t_possibleMoves = getPossibleMoves();
    
    std::vector<ChessBoard*> t_possibleStates;
    
    for(int i=0; i<t_possibleMoves.size(); i++)
    {
        ChessBoard* temp = (ChessBoard*) std::malloc(sizeof(ChessBoard));
        *temp = *m_board;
        temp->stateSetPiece(m_piecePosition, t_possibleMoves[i]);
        
        t_possibleStates.push_back(temp);
    }
    
    a_pos = t_possibleMoves[0];
    int t_maxScore = std::max(t_possibleStates[0]->cornerBlackKing(t_possibleStates[0]), t_possibleStates[0]->minimax(t_possibleStates[0], 6, INT_MIN, INT_MAX, BLACK, counter));
    
    int t_currentScore;
    // Temp counter for minimax algorithm
    int temp_count;
    for(int i=1; i<t_possibleMoves.size();i++)
    {
        temp_count = 0;
        
        t_currentScore = std::max(t_possibleStates[i]->cornerBlackKing(t_possibleStates[i]), t_possibleStates[i]->minimax(t_possibleStates[i], 6, INT_MIN, INT_MAX, BLACK, temp_count));
        
        if(t_currentScore>t_maxScore)
        {
            t_maxScore = t_currentScore;
            a_pos = t_possibleMoves[i];
        }
        counter+=temp_count;
        
    }
    std::cout<<"White Piece states visited: "<<counter<<std::endl;
    g_whiteStateCounter+=counter;
    return t_maxScore;
}

