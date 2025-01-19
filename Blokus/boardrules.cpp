#include "board.h"
#include "player.h"

bool Board::pieceCanBePlaced(Piece* piece, int x, int y){

    char player = piece->getPlayer();
    bool able = 0;

    //checking if it's the 1st move of the player
    if(playerHasPlacedNoPieces(player)){

        for (int i = x; i < x + piece->getSizeX(); i++){
            for (int j = y; j < y + piece->getSizeY(); j++){

                if(piece->getSquare(i-x,j-y)->hasPiece()){

                    if(player == '#'){
                        if (i==4 && j==4){
                            able = 1;
                        }
                    }
                    if(player == 'O'){
                        if (i==9 && j==9){
                            able = 1;
                        }
                    }
                }
            }
        }
        return able;
    }

    for (int i = x; i < x + piece->getSizeX(); i++){
        for (int j = y; j < y + piece->getSizeY(); j++){

            if(piece->getSquare(i-x,j-y)->hasPiece()){

                //checking it's inside the bounds
                if((i > boardSizeX) || (j > boardSizeY)) return 0;

                // checking if it's on top of any occupied squares
                if(squares[i][j]->hasPiece()) return 0;

                //checking if it doesn't touch a 'friendly' corner
                if( (squares[i-1][j-1]->hasPiece(player)== 1) ||
                    (squares[i-1][j+1]->hasPiece(player)== 1) ||
                    (squares[i+1][j-1]->hasPiece(player)== 1) ||
                    (squares[i+1][j+1]->hasPiece(player)== 1) )
                    able = 1;
                if(!(able)) return 0;

                //checking if it's next to a piece from the same player
                if( (squares[i][j-1]->hasPiece(player)== 1) ||
                    (squares[i][j+1]->hasPiece(player)== 1) ||
                    (squares[i-1][j]->hasPiece(player)== 1) ||
                    (squares[i+1][j]->hasPiece(player)== 1))
                    return 0;
            }
        }
    }
    return true;
}

int Board::computeScore(Player* player){

    char symbol = player->getSymbol();
    int points = 0;

    for (int i = 0; i < boardSizeX; i++){
        for(int j = 0; j < boardSizeY; j++){

            //Adds 1 to the point total for every square occupied by the player
            if(squares[i][j]->hasPiece(symbol)) points++;
        }
    }

    int counter;
    //counts all the pieces that were placed
    for(int k=0; k<21; k++){
        if(player->getPiece(k)->isPlaced()) counter++;
    }

    //if all were placed then points total +=15
    if(counter==21) points += 15;

    //checks if last tile placed is the onlysquare
    if(symbol=='#'){
            if(lastPiecePlayedByFirstPlayer->getId() == 1) points += 5;
    }
    else if(symbol=='O'){
            if(lastPiecePlayedBySecondPlayer->getId() == 1) points +=5;
    }
    return points;
}
