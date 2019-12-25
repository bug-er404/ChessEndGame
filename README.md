# Chess End Game Configurations

This project implements chess end game configurations. The white piece plays using Minimax algorithm with Alpha-Beta pruning and the black piece using a greedy algorithm.

There are three chess pieces on the board : White King, White Rook and Black King. The game starts with the white player making the first move. The squares on the board are specified using the typical algebraic notion by combining letters and number.

The initial game configuration is read and constructed using a file named “initial.board.data”. This file has the positions of the white king, white rook, and black king. For example: a,3, b,5, f,6.
The final results file, which is named “Maharjan-game.data”, the end game configuration and the result of the match as win, draw or loss is recorded.

A sample of the data collected with various game configurations is shown in the table below:

| Initial Configuration | Outcome | Total game steps | Greedy algorithm states visited | Minimax states visited |
| :-------------------: | :------:| :---------------: | :-----------------------------: | :----------------------: |
| a,1, a,2, a,7 | White Win | 1 | 0 | 3088 |
| b,1, b,2, a,5 | White Win | 42 | 28 | 265086 |
| d,1, h,4, a,2 | Draw | 6 | 19 | 51588 |
| a,1, b,3, c,2 | Draw | 2 | 3 | 10139 |
| a,1, c,2, d,2 | White win | 1 | 0 | 2453 |
| d,1, a,8, h,1 | White win | 30 | 54 | 202082 |
| d,2, d,3, c,6 | Draw | 50 | 154 | 686688 |

50-move rule is considered, which ends the game in a draw.


MakeFile and Doxygen generated documentation included.
