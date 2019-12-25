/**
*  ChessBoard.cpp
*  Implementation of ChessBoard.hpp class.
*
*
*  Created by Salil D. Maharjan on 11/27/19.
*  Copyright © 2019 Salil Maharjan. All rights reserved.
*/


#include "ChessBoard.hpp"
#include "KingPiece.hpp"
#include "RookPiece.hpp"
#include "GlobalCounter.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>

// File to write board configurations on
std::ofstream writeFile;

/**
 * Constructor for the ChessBoard class.
 * Takes position of White Rook, White King, and Black King to construct a Chess board environment.
 * @param a_whiteRook Position Initial position of the White Rook.
 * @param a_whiteKing Position Initial position of the White King.
 * @param a_blackKing Initial position of the Black King.
 * @see RookPiece and KingPiece constructors.
 */
ChessBoard::ChessBoard(Position a_whiteRook, Position a_whiteKing, Position a_blackKing)
{
    // Counter variable initialization
    count = 0;
    
    // Initializing the board
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            m_chessGrid[i][j]=NULL;
        }
    }

    
    // Checking for valid position and initializing chess pieces
    if(m_chessGrid[a_whiteRook.x][a_whiteRook.y] == NULL)
        m_whiteRookPiece = new RookPiece(this, a_whiteRook, WHITE);
    else{
        std::cerr<< "Pieces cannot be in the same position"<<std::endl;
        exit(1);
    }
    if(m_chessGrid[a_whiteKing.x][a_whiteKing.y] == NULL)
        m_whiteKingPiece = new KingPiece(this, a_whiteKing, WHITE);
    else{
        std::cerr<< "Pieces cannot be in the same position"<<std::endl;
        exit(1);
    }
    if(m_chessGrid[a_blackKing.x][a_blackKing.y] == NULL)
        m_blackKingPiece = new KingPiece(this, a_blackKing, BLACK);
    else{
        std::cerr<< "Pieces cannot be in the same position"<<std::endl;
        exit(1);
    }
}

/**
 * ChessBoard Class Deconstructor
 * Frees dynamically allocated memory for the players in the game.
 */
ChessBoard::~ChessBoard()
{
    for (int i=0; i<8; i++)
    {
        for (int j=0; j<8; j++)
            delete m_chessGrid[i][j];
    }
}

/**
* Accessor method to get chess piece on a board position.
* Gets chess piece at position a_cell.
* @param a_cell Position (x, y) position of the chess piece.
* @return ChessPiece* ChessPiece in position (x,y)
*/
ChessPiece* ChessBoard::getPiece(Position a_cell)
{

    if((a_cell.x>=0) && (a_cell.y>=0) && (a_cell.x<8) && (a_cell.y<8))
        return m_chessGrid[a_cell.x][a_cell.y];
    else
        return 0;
}

/**
* Accessor method to get the possition of a chess piece on the board.
* Gets position of a particular type and color.
* @param a_color PieceColor The color of the chess piece.
* @param a_type PieceType The type of the chess piece.
* @return Position The position of the chess piece.
*/
Position ChessBoard::getPiecePosition(PieceColor a_color, PieceType a_type)
{
    if(a_color==WHITE && a_type==ROOK)
        return m_whiteRookPiece->getPiecePosition();
    else if (a_color==WHITE && a_type==KING)
        return m_whiteKingPiece->getPiecePosition();
    else if (a_color==BLACK && a_type==KING)
        return m_blackKingPiece->getPiecePosition();
    else
        std::cerr<<"Invalid piece type - Check ChessBoard::getPiecePosition"<<std::endl;
    exit(1);
}

/**
 * Mutator method to set chess piece on a board position.
 * Sets chess piece a_piece at position (x,y).
 * @param a_cell Position (x, y) position to put the chess piece.
 * @param a_piece ChessPiece* Agent to place in position (x,y)
 */
void ChessBoard::setPiece(Position a_cell, ChessPiece* a_piece)
{
    if ((a_cell.x>=0) && (a_cell.x<8) && (a_cell.y>=0) && (a_cell.y<8))
        m_chessGrid[a_cell.x][a_cell.y] = a_piece;
//        std::cout<<"HERE:"<<NULL<<" "<<m_chessGrid[a_cell.x][a_cell.y]<<std::endl;
    // CHECK IF ANY PIECE IS KILLED ?
}

/**
 * Next State simulation method.
 * Simulates the next state on the chess board.
 * @return int Returns 1 when the game ends due to checkmate and 2 when draw. 0 when in progress.
 */
int ChessBoard::simulateNextState()
{
    // Step count
    count++;
    // 50 step draw check to print results to output file
    if(count==50)
    {
        std::cout<<"50 MOVE RULE DRAW"<<std::endl;
        std::cout<<"The game is tied because of the 50 Move Draw Rule"<<std::endl<<"Each player receives 0.5 score"<<std::endl;
        writeResults(BLACK);
        exit(1);
    }
    
    int tmp=0;
    // White piece turn
    if(this->m_pieceTurn == 1)
    {
        Position wk_temp = m_whiteKingPiece->getPiecePosition();
        Position wr_temp = m_whiteRookPiece->getPiecePosition();
        int kingMoveScore = m_whiteKingPiece->getMaximizingState(wk_temp);
        int rookMoveScore = m_whiteRookPiece->getMaximizingState(wr_temp);
        
        if(kingMoveScore>rookMoveScore)
            m_whiteKingPiece->updatePieceCell(wk_temp);
        else if (kingMoveScore<rookMoveScore)
            m_whiteRookPiece->updatePieceCell(wr_temp);
        // When the score is equal, we randomly select a move:
        else
        {
            int seed = rand()%2;
            if(seed==0)
                m_whiteKingPiece->updatePieceCell(wk_temp);
            else
                m_whiteRookPiece->updatePieceCell(wr_temp);
                
        }
           
        // Setting piece turn for next iteration
        m_pieceTurn=0;
    }
    // Black piece turn
    else
    {
        // Check for checkmate
        // Check if black king is on check and there is no position to move
        
        // Check for stalemate
        // Check if there is no position to move
        tmp = m_blackKingPiece->movePiece();
        
        // Checkmate reached
        if(tmp==1)
        {
            // Writing to the Final output text file:
            writeResults(WHITE);
            return tmp;
        }
        m_pieceTurn=1;
        
    }
    return tmp;
}


/**
 * Method to display chess board.
 * Displays the chess board as a character grid.
 * Additionally writes the end game configurations to a text file with the result of the match.
 */
void ChessBoard::displayBoard()
{
    std::cout<<"-------------------------------------------------------------------"<<std::endl;
    std::cout<<"-------------------------------------------------------------------"<<std::endl;
    
//    std::cout<<"CBwking:"<<m_whiteKingPiece->getPiecePosition().x<<" "<<m_whiteKingPiece->getPiecePosition().y<<std::endl;
//    std::cout<<"CBwrook:"<<m_whiteRookPiece->getPiecePosition().x<<" "<<m_whiteRookPiece->getPiecePosition().y<<std::endl;
//    std::cout<<"CBbking:"<<m_blackKingPiece->getPiecePosition().x<<" "<<m_blackKingPiece->getPiecePosition().y<<std::endl;
    
    for (int i = 0; i<8; i++)
    {
        for (int j = 0; j<8; j++)
        {
            if(m_chessGrid[i][j]==NULL)
                std::cout<< std::setw(7) <<".";
            else
                std::cout<< std::setw(7) <<std::string(1,m_chessGrid[i][j]->pieceCharCode())+m_chessGrid[i][j]->pieceColorCode();
    
        }
        std::cout<<std::endl;
        std::cout<<std::endl;
    }
    int wkx =(m_whiteKingPiece->getPiecePosition().x +1);
    char wky = (char)(m_whiteKingPiece->getPiecePosition().y + 'a');
    int wrx =(m_whiteRookPiece->getPiecePosition().x +1);
    char wry = (char)(m_whiteRookPiece->getPiecePosition().y + 'a');
    int bkx =(m_blackKingPiece->getPiecePosition().x +1);
    char bky = (char)(m_blackKingPiece->getPiecePosition().y + 'a');

    
 
    writeFile.open("Maharjan-Steps-Fall2019.data", std::ios::app);
    std::string config = "";
    config += wky;
    config += ',';
    config += (char)wkx+'0';
    config += ", ";
    config += wry;
    config +=',';
    config += (char)wrx+'0';
    config += ", ";
    config += bky;
    config += ',';
    config += (char)bkx+'0';
    config += '\n';
    if(writeFile.is_open())
        writeFile<<config;
    writeFile.close();

}

/**
 * Method to create states for minimax and greedy algorithn.
 * Sets chess piece for the states created from current position to destination position.
 * @param a_current Position Current position of the piece
 * @param a_dest Position Destination position of the piece
 */
void ChessBoard::stateSetPiece(Position a_current, Position a_dest)
{
    PieceType t_type = m_chessGrid[a_current.x][a_current.y]->getPieceType();
    char t_color = m_chessGrid[a_current.x][a_current.y]->pieceColorCode();
    
    if(t_type == KING && t_color == 'W')
    {
        m_whiteKingPiece = new KingPiece(this, a_dest, WHITE);
        m_blackKingPiece = new KingPiece(this, m_blackKingPiece->getPiecePosition(), BLACK);
        m_whiteRookPiece = new RookPiece(this, m_whiteRookPiece->getPiecePosition(), WHITE);
    }
    if(t_type == KING && t_color == 'B')
    {
        m_whiteKingPiece = new KingPiece(this, m_whiteKingPiece->getPiecePosition(), WHITE);
        m_blackKingPiece = new KingPiece(this, a_dest, BLACK);
        m_whiteRookPiece = new RookPiece(this, m_whiteRookPiece->getPiecePosition(), WHITE);
    }
    if(t_type == ROOK && t_color == 'W')
    {
        m_whiteKingPiece = new KingPiece(this, m_whiteKingPiece->getPiecePosition(), WHITE);
        m_blackKingPiece = new KingPiece(this, m_blackKingPiece->getPiecePosition(), BLACK);
        m_whiteRookPiece = new RookPiece(this, a_dest, WHITE);
    }
    
    
}
        

/**
 * Heuristic method to corner the Black King.
 * Used by the white pieces for the minimax alpha-beta pruned algorithm
 * @param a_node ChessBoard* The current state of the board.
 * @return int The score for the state according to the heuristics.
 *
 */
int ChessBoard::cornerBlackKing(ChessBoard* a_node)
{
    // Initially assigned score, since the King is able to move to 8 different cells
    int score = 8;
    // Heuristic 1: Update score according to possible moves for the Black King.
    score -= m_blackKingPiece->getPossibleMoves().size();
    
    // Heuristic 2: Checking if the King is on check
    if(a_node->m_whiteRookPiece->getPiecePosition().x == a_node->m_blackKingPiece->getPiecePosition().x)
    {
        // Checking if rook is right next to the king
        // Which means the rook piece is in danger:
        // We reduce the score
        if(abs(a_node->m_whiteRookPiece->getPiecePosition().y - a_node->m_blackKingPiece->getPiecePosition().y) == 1)
            score -= 7;
        // Else we increase the score as the King is on check
        else
            score += 5;
    }
    // Similarly checking the y cells:
    if(a_node->m_whiteRookPiece->getPiecePosition().y == a_node->m_blackKingPiece->getPiecePosition().y )
    {
        if(abs(a_node->m_whiteRookPiece->getPiecePosition().x- a_node->m_blackKingPiece->getPiecePosition().x) == 1)
            score -= 7;
        else
            score += 5;
        
    }
    
    // Heuristic 3: Checking the distance between the two kings
    int wking_x = a_node->m_whiteKingPiece->getPiecePosition().x;
    int wking_y = a_node->m_whiteKingPiece->getPiecePosition().y;
    int bking_x = a_node->m_blackKingPiece->getPiecePosition().x ;
    int bking_y = a_node->m_blackKingPiece->getPiecePosition().y;
    
    score -= std::max(abs(wking_x-bking_x), abs(wking_y-bking_y));
    
    // Heuristic 4: Asserting the position is not next to the Black King
    if(abs(a_node->m_whiteRookPiece->getPiecePosition().x - a_node->m_blackKingPiece->getPiecePosition().x)<=1
       || abs(a_node->m_whiteRookPiece->getPiecePosition().y - a_node->m_blackKingPiece->getPiecePosition().y)<=1)
        score -= 99;
    return score;
    
}

/**
* Minimax algorithm implementation with alpha beta pruning.
* Used by white pieces to get the optimal next move.
* @param a_node ChessBoard* The current state of the board.
* @param a_depth int The depth to search for the optimal state.
* @param a_alpha int alpha cut off.
* @param a_beta int beta cut off.
* @param a_color bool The current piece color
* @param a_count int Counter for the number of states
* @return int The score for the state according to the heuristics.
*
*/
int ChessBoard::minimax(ChessBoard* a_node, int a_depth, int a_alpha, int a_beta, bool a_color, int &a_count)
{
    
    if(a_depth==0) return cornerBlackKing(a_node);
    
    // Updating counter of states
    a_count++;
    
    
    // Minimizing player
    if(a_color==BLACK)
    {
        std::vector<Position> t_possibleMoves;

        // Get all possible moves
        t_possibleMoves = a_node->m_blackKingPiece->getPossibleMoves();
        
        int t_val = INT_MAX;
        for(int i=0; i<t_possibleMoves.size(); i++)
        {
            ChessBoard* temp = (ChessBoard*) std::malloc(sizeof(ChessBoard));
            *temp = *a_node;
            temp->stateSetPiece(a_node->m_blackKingPiece->getPiecePosition(), t_possibleMoves[i]);
            
            t_val = std::min(t_val, minimax(temp, a_depth-1, a_alpha, a_beta, WHITE, a_count));
            a_beta = std::min(a_beta, t_val);
            
            // AB Pruning
            if(a_beta<=a_alpha)
                break;
        }
        // Returns the lowest score for the minimizing player
        return t_val;
    }
    // Maximizing player
    else
    {
        std::vector<Position> t_possibleMovesRook;
        std::vector<Position> t_possibleMovesKing;
        
        // Get all possible moves
        t_possibleMovesRook = a_node->m_whiteRookPiece->getPossibleMoves();
        t_possibleMovesKing = a_node->m_whiteKingPiece->getPossibleMoves();

        int t_val = INT_MIN;
        // Checking for the Rook
        for(int i=0; i<t_possibleMovesRook.size(); i++)
        {
            ChessBoard* temp = (ChessBoard*) std::malloc(sizeof(ChessBoard));
            *temp = *a_node;
            temp->stateSetPiece(a_node->m_whiteRookPiece->getPiecePosition(), t_possibleMovesRook[i]);
            
            t_val = std::max(t_val, minimax(temp, a_depth-1, a_alpha, a_beta, BLACK, a_count));
            a_alpha = std::max(a_alpha, t_val);
            
            // AB Pruning
            if(a_beta<=a_alpha)
                break;
        }
        
        // Checking for the King
        for(int i=0; i<t_possibleMovesKing.size(); i++)
        {
            ChessBoard* temp = (ChessBoard*) std::malloc(sizeof(ChessBoard));
            *temp = *a_node;
            temp->stateSetPiece(a_node->m_whiteKingPiece->getPiecePosition(), t_possibleMovesKing[i]);
            
            t_val = std::max(t_val, minimax(temp, a_depth-1, a_alpha, a_beta, BLACK, a_count));
            a_alpha = std::max(a_alpha, t_val);
            
            // AB Pruning
            if(a_beta<=a_alpha)
                break;
        }
        
        // Returns the lowest score for the minimizing player
        return t_val;
    }

    
}

/**
* Method to write the end game configurations to a target file.
* Writes the piece position, the outcome of the game and the statistics of the game.
* @param a_type The color who won the game. Black color signifies a draw.
 **/
void ChessBoard::writeResults(PieceColor a_type)
{
    // Writing to the Final output text file:
    std::ofstream writeFile;
    writeFile.open("Maharjan-game.data", std::ios::app);
    displayBoard();
    
    int wkx =(m_whiteKingPiece->getPiecePosition().x +1);
    char wky = (char)(m_whiteKingPiece->getPiecePosition().y + 'a');
    int wrx =(m_whiteRookPiece->getPiecePosition().x +1);
    char wry = (char)(m_whiteRookPiece->getPiecePosition().y + 'a');
    int bkx =(m_blackKingPiece->getPiecePosition().x +1);
    char bky = (char)(m_blackKingPiece->getPiecePosition().y + 'a');

       
    std::string config = "";
    config += wky;
    config += ',';
    config += (char)wkx+'0';
    config += ", ";
    config += wry;
    config +=',';
    config += (char)wrx+'0';
    config += ", ";
    config += bky;
    config += ',';
    config += (char)bkx+'0';
    if(a_type==WHITE)
        config += ", win";
    else
        config += ", draw";
    if(writeFile.is_open())
    {
        writeFile<<config<<std::endl;
        
        // Writing game statistics:
        config = "TOTAL GAME STEPS TAKEN: ";
        config += std::to_string(count);
        writeFile<<config<<std::endl;
        config = "Total states visited using Greedy by Black Piece: ";
        config += std::to_string(g_blackStateCounter);
        writeFile<<config<<std::endl;
        config = "Total states visited using Alpha Beta by White Pieces: ";
        config += std::to_string(g_whiteStateCounter);
        writeFile<<config<<std::endl;
    }
    writeFile.close();
    
    std::cout<<"Total game steps taken: "<<count<<std::endl;
    std::cout<<"States visited by Greedy by Black Piece: "<<g_blackStateCounter<<std::endl;
    std::cout<<"States visited by Alpha Beta by White Piece: "<<g_whiteStateCounter<<std::endl;
    
}
