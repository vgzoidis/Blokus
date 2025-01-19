#include <iostream>
#include <cstdlib>
#include "player.h"

Player::Player(int id){

    this->id = id;
    if (id == 0) name = "Player 1";
    else if (id == 1) name = "Player 2";
    numPieces = 21;
    symbol = (id == 0) ? '#' : 'O';
    pieces = new Piece*[numPieces];
    createPieces();
    //opponent = NULL;
}

Player::~Player(){
     for (int i = 0; i < 21; i++)
        delete[] pieces[i];
    delete[] pieces;
}

int Player::getId(){
    return id;
}

char Player::getSymbol(){
    return symbol;
}

string Player::getName(){
    return name;
}

Piece* Player::getPiece(int index){
    return pieces[index];
}

int Player::getNumberOfPlacedPieces(){
    int sum=0;
    for(int i=0; i<numPieces; i++){
        if(pieces[i]->isPlaced() == 1) sum++;
    }
    return sum;
}

int Player::getNumberOfAvailablePieces(){
    return (21 - getNumberOfPlacedPieces());
}

HumanPlayer::HumanPlayer(int id) : Player(id){

}

HumanPlayer::HumanPlayer(int id, string name): Player(id){
    this ->name = name;
}

int ComputerPlayer::getRandomPieceId(){
    return ((rand() % 21) + 1);
}

Orientation ComputerPlayer::getRandomOrientation(){
    return Orientation(rand() % 4);
}

Flip ComputerPlayer::getRandomFlip(){
    return Flip(rand() % 2);
}

ComputerPlayer::ComputerPlayer(int id) : Player(id){

}
