#include "smartplayer.h"
#include "algorithms.h"

SmartPlayer::SmartPlayer(int id) : Player(id) {
    name = "Team 054";
}

int SmartPlayer::evaluateBoard(Board* board) {

    int score = 0;
    char player = getSymbol();
    for (int i = 0; i < 14; i++) {
        for (int j = 0; j < 14; j++) {
            if(board->squareBelongsToPlayer(i, j, player))
                score++;
            if(board->squareBelongsToPlayer(i, j, opponent))
                score--;
        }
    }
    return score;
}

Move* SmartPlayer::makeMove(Board* board) {

    int numPossibleMoves;
    int maxScore = 0;
    int best = 0;

    Move** possibleMoves = getPossibleMoves(board, numPossibleMoves);

    int* possibleMovesScores = new int[numPossibleMoves];
    for (int i = 0; i < numPossibleMoves; i++)
    possibleMovesScores[i] = evaluateMove(board, possibleMoves[i]);

    if (getId()){
        for (int i = 0; i < numPossibleMoves; i++){
            if (possibleMovesScores[i]>=maxScore){
            maxScore = possibleMovesScores[i];
            best = i;
            }
        }
    }else{
        for (int i = 0; i < numPossibleMoves-1; i++){
            if (possibleMovesScores[i]>=maxScore){
            maxScore = possibleMovesScores[i];
            best = i;
            }
        }
    }

    static bool once = false;
    if (once == false){
        once = true;
        best-=50;
    }

    Move* moveToPlay = new Move(possibleMoves[best]);

    for (int i = 0; i < numPossibleMoves; i++)
        delete possibleMoves[i];
    delete[] possibleMoves;
    delete[] possibleMovesScores;

    return moveToPlay;
}
