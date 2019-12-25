/**
*  KingPiece.cpp
*  Implements KingPiece.hpp class.
*  Chess End Game
*
*  Created by Salil Maharjan on 11/27/19.
*  Copyright © 2019 Salil Maharjan. All rights reserved.
*/

#include <iostream>
#include <cmath>

#include "KingPiece.hpp"
#include "ChessPiece.hpp"
#include "GlobalCounter.hpp"

/**
 * King Piece class constructor.
 * Constructor: Creates a KingPiece in a_board chess board at cell position a_cell.
 * Calls ChessPiece constructor to construct a chesspiece.
 * @param a_board ChessBoard* ChessBoard where the game is being played.
 * @param a_cell Position (x,y) position to place king piece.
 */
KingPiece::KingPiece(class ChessBoard* a_board, Position a_cell, PieceColor a_pieceColor) : ChessPiece(a_board, a_cell, a_pieceColor)
{
}

/**
* King Piece class destructor.
* Destructor: Destroys the KingPiece from the board.
*
*/
KingPiece::~KingPiece()
{
    this->m_board=NULL;
    // Moving piece out of the board.
    this->m_piecePosition.x = 9;
    this->m_piecePosition.y = 9;
    // More destructor? Delete pointers? so that no move is made.
}


/**
* Move method for King Piece.
* Overloaded move method to move King piece.
* @return int Returns 1 when the game ends due to checkmate and 2 when draw. 0 when in progress.
*/
int KingPiece::movePiece()
{
    // Move to use.
    int move;
    
    // ALGORITHM FOR WHITE AND BLACK
    std::vector<Position> t_possibleMoves = getPossibleMoves();
    
    if(t_possibleMoves.size()==0){
        std::cout<<"White Wins!"<<std::endl;
        return 1;
    }
    if(this->pieceColorCode()=='B'){
        move = distanceToRook(t_possibleMoves, this->m_board->getPiecePosition(WHITE, ROOK), this->m_board->getPiecePosition(WHITE, KING));
            this->updatePieceCell(t_possibleMoves[move]);
    }

    
    // Buffer to hold board state for each possible move
//    std::vector<ChessBoard> t_states;
//    for(int i=0; i<t_possibleMoves.size(); i++)
//    {
//        std::cout<<"KING"<<t_possibleMoves[i].x<<" "<<t_possibleMoves[i].y<<std::endl;
////        ChessBoard tmp = ChessBoard()
//
//    }
    
    // Check if the vector is only one to see if the rook has been eaten.
//    this->updatePieceCell(t_possibleMoves[0]);
    
//    std::cout<<this->pieceCharCode()<<" "<<t_possibleMoves[1].x<<" "<<t_possibleMoves[1].y<<std::endl;
    return 0;
}

/**
* Method to get possible moves for a King Piece.
* @return vector<Position> Array of possible positions the King piece can make a valid move to.
*/
std::vector<Position> KingPiece::getPossibleMoves()
{
    // Temp variable to hold possible moves
    std::vector<Position> t_posssibleMoves;
    
    // Black King
    if(this->m_pieceColor == BLACK){
        // Position of white rook
        Position t_rook = this->m_board->getPiecePosition(WHITE, ROOK);
//        std::cout<<"BKPr: "<<t_rook.x<<" "<<t_rook.y<<std::endl;
        // Position of white king
        Position t_king = this->m_board->getPiecePosition(WHITE, KING);
//        std::cout<<"BKPk: "<<t_king.x<<" "<<t_king.y<<std::endl;

        // Current position of Black King
        Position temp;
        temp.x = this->m_piecePosition.x;
        temp.y = this->m_piecePosition.y;
//        std::cout<<"BKP: "<<temp.x<<" "<<temp.y<<std::endl;
        
        // Checking if rook is in move range
        // - The rook can be killed
        if(abs(t_rook.x-temp.x)<=1 && abs(t_rook.y-temp.y)<=1)
        {
            // Checking if the rook is supported by the king.
            // Which means this move will lead to a check position
            // It is invalid.
            if(abs(t_rook.x-t_king.x)<=1 && abs(t_rook.y-t_king.y)<=1){}
            else
            {
            t_posssibleMoves.push_back(t_rook);
                return t_posssibleMoves;
                
            }
        }
        
        // Checking all the 8 cells around the king for White King and Rook
        temp.x = this->m_piecePosition.x-1;
        temp.y = this->m_piecePosition.y-1;
        if(checkCell(temp) && this->m_board->getPiece(temp)==NULL && (abs(temp.x-t_king.x)>1 || abs(temp.y-t_king.y) >1)
           && temp.x != t_rook.x && temp.y != t_rook.y)
            t_posssibleMoves.push_back(temp);
        
        temp.x = this->m_piecePosition.x-1;
        temp.y = this->m_piecePosition.y;
        if(checkCell(temp) && this->m_board->getPiece(temp)==NULL && (abs(temp.x-t_king.x)>1 || abs(temp.y-t_king.y) >1)
           && temp.x != t_rook.x && temp.y != t_rook.y)
            t_posssibleMoves.push_back(temp);
        
        temp.x = this->m_piecePosition.x-1;
        temp.y = this->m_piecePosition.y+1;
        if(checkCell(temp) && this->m_board->getPiece(temp)==NULL && (abs(temp.x-t_king.x)>1 || abs(temp.y-t_king.y)>1)
           && temp.x != t_rook.x && temp.y != t_rook.y)
            t_posssibleMoves.push_back(temp);
        
        temp.x = this->m_piecePosition.x;
        temp.y = this->m_piecePosition.y+1;
        if(checkCell(temp) && this->m_board->getPiece(temp)==NULL && (abs(temp.x-t_king.x)>1 || abs(temp.y-t_king.y) >1)
           && temp.x != t_rook.x && temp.y != t_rook.y)
            t_posssibleMoves.push_back(temp);
        
        temp.x = this->m_piecePosition.x+1;
        temp.y = this->m_piecePosition.y+1;
        if(checkCell(temp) && this->m_board->getPiece(temp)==NULL && (abs(temp.x-t_king.x)>1 || abs(temp.y-t_king.y) >1)
           && temp.x != t_rook.x && temp.y != t_rook.y)
            t_posssibleMoves.push_back(temp);
        
        temp.x = this->m_piecePosition.x+1;
        temp.y = this->m_piecePosition.y;
        if(checkCell(temp) && this->m_board->getPiece(temp)==NULL && (abs(temp.x-t_king.x)>1 || abs(temp.y-t_king.y) >1)
           && temp.x != t_rook.x && temp.y != t_rook.y)
            t_posssibleMoves.push_back(temp);
        
        temp.x = this->m_piecePosition.x+1;
        temp.y = this->m_piecePosition.y-1;
        if(checkCell(temp) && this->m_board->getPiece(temp)==NULL && (abs(temp.x-t_king.x)>1 || abs(temp.y-t_king.y) >1)
           && temp.x != t_rook.x && temp.y != t_rook.y)
            t_posssibleMoves.push_back(temp);
        
        temp.x = this->m_piecePosition.x;
        temp.y = this->m_piecePosition.y-1;
        if(checkCell(temp) && this->m_board->getPiece(temp)==NULL && (abs(temp.x-t_king.x)>1 || abs(temp.y-t_king.y) >1)
           && temp.x != t_rook.x && temp.y != t_rook.y)
            t_posssibleMoves.push_back(temp);
        
        return t_posssibleMoves;
    }
    // White king
    else
    {
        // Temp position variable
        Position temp;
        
        // Position of Black king
        Position t_blackKing = this->m_board->getPiecePosition(BLACK, KING);
        
        // Checking all the 8 cells around the king
        temp.x = this->m_piecePosition.x-1;
        temp.y = this->m_piecePosition.y-1;
        if(checkCell(temp) && this->m_board->getPiece(temp)==NULL && ((abs(temp.x-t_blackKing.x)>1) || (abs(temp.y-t_blackKing.y) >1)))
            t_posssibleMoves.push_back(temp);
        
        temp.x = this->m_piecePosition.x-1;
        temp.y = this->m_piecePosition.y;
        if(checkCell(temp) && this->m_board->getPiece(temp)==NULL && ((abs(temp.x-t_blackKing.x)>1) || (abs(temp.y-t_blackKing.y) >1)))
            t_posssibleMoves.push_back(temp);
        
        temp.x = this->m_piecePosition.x-1;
        temp.y = this->m_piecePosition.y+1;
        if(checkCell(temp) && this->m_board->getPiece(temp)==NULL && ((abs(temp.x-t_blackKing.x)>1) || (abs(temp.y-t_blackKing.y) >1)))
            t_posssibleMoves.push_back(temp);
        
        temp.x = this->m_piecePosition.x;
        temp.y = this->m_piecePosition.y+1;
        if(checkCell(temp) && this->m_board->getPiece(temp)==NULL && ((abs(temp.x-t_blackKing.x)>1) || (abs(temp.y-t_blackKing.y) >1)))
            t_posssibleMoves.push_back(temp);
        
        temp.x = this->m_piecePosition.x+1;
        temp.y = this->m_piecePosition.y+1;
        if(checkCell(temp) && this->m_board->getPiece(temp)==NULL && ((abs(temp.x-t_blackKing.x)>1) || (abs(temp.y-t_blackKing.y) >1)))
            t_posssibleMoves.push_back(temp);
        
        temp.x = this->m_piecePosition.x+1;
        temp.y = this->m_piecePosition.y;
        if(checkCell(temp) && this->m_board->getPiece(temp)==NULL && ((abs(temp.x-t_blackKing.x)>1) || (abs(temp.y-t_blackKing.y) >1)))
            t_posssibleMoves.push_back(temp);
        
        temp.x = this->m_piecePosition.x+1;
        temp.y = this->m_piecePosition.y-1;
        if(checkCell(temp) && this->m_board->getPiece(temp)==NULL && ((abs(temp.x-t_blackKing.x)>1) || (abs(temp.y-t_blackKing.y) >1)))
            t_posssibleMoves.push_back(temp);
        
        temp.x = this->m_piecePosition.x;
        temp.y = this->m_piecePosition.y-1;
        if(checkCell(temp) && this->m_board->getPiece(temp)==NULL && ((abs(temp.x-t_blackKing.x)>1) || (abs(temp.y-t_blackKing.y) >1)))
            t_posssibleMoves.push_back(temp);
        
        return t_posssibleMoves;
    
    }
}


/**
* Greedy method for the Black King Piece.
* Used as a heuristic to select Black King move.
* Gets the distance from the Black King Piece to the White Rook Piece.
* Checks the minimum horizontal, vertical and diagonal distance, which is calculated using Euclidean distance, from the proposed position to the White Rook to get as close to it as possible.
* Also, as an improvement, checks the distance from the white king to see if there is a move so that it will get the Black Piece closer to the
* White Rook and away from the White King. At the end, the next move is chosen with the choice that has the most valid moves between the RookMinDistance and KingMaxDistance.
* Priority given to getting close to the rook.
* So that it can eventually capture it without being on a check.
* @param a_posRook Position The position of the White Rook.
* @param a_posKing Possition The position of the White King.
* @return int The index of the best posssible move according to this greedy algorithm.
*/
int KingPiece::distanceToRook(std::vector<Position> a_possibleMoves, Position a_posRook, Position a_posKing)
{
    // Counter to keep track of states visited:
    int counter = 0;
    
    // Position placeholder
    int x, y, d;
    
    // Closest the black king can get to the rook
    int x_rookVal = 999, y_rookVal = 999, d_rookval = 999;
    // Farthest the black king can get from the White King
    int x_kingVal = 0, y_kingVal = 0, d_kingval = 0;
    
    // The index of the move in the vector
    int rookIDX;
    int kingIDX;
    
    for(int i=0; i<a_possibleMoves.size(); i++)
    {
        // Updating state visited
        counter++;
        
//        std::cout<<"BK"<<a_possibleMoves[i].x<<std::endl;
//        std::cout<<"BK"<<a_possibleMoves[i].y<<std::endl;
        
        // Closest distance to the rook
        x = abs(a_possibleMoves[i].x-a_posRook.x);
        y = abs(a_possibleMoves[i].y-a_posRook.y);
        // Checking diagonal distance
        d = (int)sqrt(pow(x,2)+pow(y,2));
//        std::cout<<"x"<<x<<std::endl;
//        std::cout<<"y"<<y<<std::endl;
//        std::cout<<"d"<<d<<std::endl;
        if(x<=x_rookVal && y<=y_rookVal && d<=d_rookval)
        {
            x_rookVal = x;
            y_rookVal = y;
            d_rookval = d;
            rookIDX = i;
            
            // If we find that we are one cell away from the rook, we directly move there:
            if(x_rookVal == 1 && y_rookVal == 1 && d_rookval==1){
                
                std::cout<<"Black King states visited: "<<counter<<std:: endl;
                
//                g_blackStateCounter+=counter;
                return i;
            }
        }
        
        // Farthest from the King
        x = abs(a_possibleMoves[i].x-a_posKing.x);
        y = abs(a_possibleMoves[i].y-a_posKing.y);
        d = (int)sqrt(pow(x,2)+pow(y,2));
        if(x>=x_kingVal && y>=y_kingVal && d>=d_kingval)
        {
            x_kingVal = x;
            y_kingVal = y;
            d_kingval = d;
            kingIDX = i;
        }
        
    }
    
    // Checking the number of valid moves for the two best states identified.
    // Storing current position of Black King for update
    Position temp;
    temp.x = this->m_piecePosition.x;
    temp.y = this->m_piecePosition.y;
    // Checking Min Rook Distance
    this->m_piecePosition.x = a_possibleMoves[rookIDX].x;
    this->m_piecePosition.y = a_possibleMoves[rookIDX].y;
    
    int rookMinValidSpaces = (int)getPossibleMoves().size();
    counter+= rookMinValidSpaces;
//    std::cout<<"Rook min: "<<rookMinValidSpaces<<std::endl;

    // Checking Max King Distance
    this->m_piecePosition.x = a_possibleMoves[kingIDX].x;
    this->m_piecePosition.y = a_possibleMoves[kingIDX].y;
    int kingMaxValidSpaces = (int)getPossibleMoves().size();
    counter+= kingMaxValidSpaces;
//    std::cout<<"King max: "<<kingMaxValidSpaces<<std::endl;
    
    // Returning piece to its initial position
    this->m_piecePosition.x = temp.x;
    this->m_piecePosition.y = temp.y;
    
    // Checking for max valid spaces in the next move:
    // Priority to getting close to the rook with a threshold
    // of getting 3 valid move spaces (a entire row for the king move)
    
    std::cout<<"Black King states visited: "<<counter<<std:: endl;
    
    g_blackStateCounter+=counter;
    if(rookMinValidSpaces+3>=kingMaxValidSpaces)
        return rookIDX;
    else
        return kingIDX;
    
    
}


//
//// Gets maximizing state
//int KingPiece::getMaximizingState(Position &a_pos)
//{
//
//    std::vector<Position> t_possibleMoves = getPossibleMoves();
//    
//    std::vector<ChessBoard*> t_possibleStates;
//    
//    for(int i=0; i<t_possibleMoves.size(); i++)
//    {
//        ChessBoard* temp = (ChessBoard*) std::malloc(sizeof(ChessBoard));
//        *temp = *m_board;
//        temp->stateSetPiece(m_piecePosition, t_possibleMoves[i]);
//        
//        t_possibleStates.push_back(temp);
//    }
//    
//}



