//
//  Player.cpp
//  Checkers
//
//  Created by rick gessner on 2/22/19.
//  Copyright © 2019 rick gessner. All rights reserved.
//

#include "Player.hpp"
#include "Game.hpp"
#include <stdlib.h>
#include <time.h>
#include <random>
#include <algorithm>

namespace ECE141 {

int Player::pcount = 0; //init our static member to track # of players...

static PieceColor autoColor() { //auto assigns a color
    return (++Player::pcount % 2) ? PieceColor::blue : PieceColor::gold;
}

Player::Player() : color(autoColor()) {}

void Player::getOpponents(Game& aGame, const PieceColor enemyColor) {
    opponents.clear();
    
    for (int i = 0; i < aGame.kPiecesPerPlayer; ++i) {
        const Piece* enemy = aGame.getAvailablePiece(enemyColor, i);
        if (enemy) {
            opponents.push_back(enemy);
        }
    }
}

// Movements
Location Player::getRightFront(const Piece* p, int step) {
    Location loc(p->getLocation());
    // loc += getForwardDirection(p) * step * rightFront;
    Location delta = scaleLocation(getForwardDirection(p) * step, rightFront);
    loc = addLocation(loc, delta);
    return loc;
}

Location Player::getLeftFront(const Piece* p, int step) {
    Location loc(p->getLocation());
    // loc += getForwardDirection(p) * step * leftFront;
    Location delta = scaleLocation(getForwardDirection(p) * step, leftFront);
    loc = addLocation(loc, delta);
    return loc;
}

Location Player::getRightBack(const Piece* p, int step) {
    Location loc(p->getLocation());
    // loc += getBackwardDirection(p) * step * rightBack;
    Location delta = scaleLocation(getForwardDirection(p) * step, rightBack);
    loc = addLocation(loc, delta);
    return loc;
}

Location Player::getLeftBack(const Piece* p, int step) {
    Location loc(p->getLocation());
    // loc += getBackwardDirection(p) * step * leftBack;
    Location delta = scaleLocation(getForwardDirection(p) * step, leftBack);
    loc = addLocation(loc, delta);
    return loc;
}


bool Player::safeMove(Game& aGame, Location& aLoc, unsigned short int comeFrom ){
    saftyCheck = true;
    std::cout << "safeMove, ";
//    std::cout <<"check if "<< aLoc<<" is safe";
    int inverse = color==PieceColor::blue? 1:-1;
    const PieceColor enemyColor = getOpponentColor();
    // Go through all the enemy's location, if there's an enemy at certain location, check if it's safe to move
    for (int pos = 0; pos < 12; pos++) {
        if(const Piece *thePiece = aGame.getAvailablePiece(enemyColor, pos)){
            //  Check if enemy is at the four corner of my desired location
            // bool isLeftFront = thePiece->getLocation() == aLoc + inverse*Location(-1,-1);
            Location temp = scaleAdd(aLoc, inverse, leftFront);
            bool isLeftFront = isEqualLocation(thePiece->getLocation(), temp);

            if (isLeftFront) {
//                std::cout << "has someone at lefrFront\n";
                //check if I have backup
                Location temp = scaleAdd(aLoc, inverse, rightBack);
                // const Tile* backupTile = aGame.getTileAt(aLoc - inverse*Location(-1,-1));
                const Tile* backupTile = aGame.getTileAt(temp);
                if(backupTile && backupTile->getPiece()==nullptr){
                    std::cout <<", NO\n";
                    return false;
                }
//                if(backupTile && backupTile->getPiece()!=nullptr){
//                    if (backupTile->getPiece()->getColor() != color){
//                        std::cout <<", NO\n";
//                        return false;
//                    }
//                }
                if(comeFrom == 2){
                    std::cout <<", NO\n";
                    return false;
                }
            }
            
            // bool rightFront = thePiece->getLocation() == aLoc + inverse*Location(-1,1);
            temp = scaleAdd(aLoc, inverse, rightFront);
            bool isRightFront = isEqualLocation(thePiece->getLocation(), temp);
            
            if (isRightFront){
//                std::cout << "has someone at rightFront\n";
                //check if I have backup
                Location temp = scaleAdd(aLoc, inverse, leftBack);
                // const Tile* backupTile = aGame.getTileAt(aLoc - inverse*Location(-1,1));
                const Tile* backupTile = aGame.getTileAt(temp);
                
                if(backupTile && backupTile->getPiece()==nullptr){
                    std::cout <<", NO\n";
                    return false;
                }
//                if(backupTile && backupTile->getPiece()!=nullptr){
//                    if (backupTile->getPiece()->getColor() != color){
//                        std::cout <<", NO\n";
//                        return false;
//                    }
//                }
                if(comeFrom == 1){
                    std::cout <<", NO\n";
                    return false;
                }
            }
            
            // bool leftBack = thePiece->getLocation() == aLoc + inverse*Location(1,-1);
            temp = scaleAdd(aLoc, inverse, leftBack);
            bool isLeftBack = isEqualLocation(thePiece->getLocation(), temp);
            
            if(isLeftBack && thePiece->getKind() == PieceKind::king){
//                std::cout << "has someone at leftBack\n";
                //check if I have backup
                Location temp = scaleAdd(aLoc, inverse, rightFront);
                // const Tile* backupTile = aGame.getTileAt(aLoc - inverse*Location(1,-1));
                const Tile* backupTile = aGame.getTileAt(temp);
                
                if(backupTile && backupTile->getPiece()==nullptr){
                    std::cout <<", NO\n";
                    return false;
                }
//                if(backupTile && backupTile->getPiece()!=nullptr){
//                    if (backupTile->getPiece()->getColor() != color){
//                        std::cout <<", NO\n";
//                        return false;
//                    }
//                }
                if(comeFrom == 3){
                    std::cout <<", NO\n";
                    return false;
                }
            }
            
            temp = scaleAdd(aLoc, inverse, rightBack);
            // bool isRightBack = thePiece->getLocation() == aLoc + inverse * Location(1,1);
            bool isRightBack = isEqualLocation(thePiece->getLocation(), temp);
            if (isRightBack && thePiece->getKind() == PieceKind::king) {
//                std::cout << "has someone at rightBack\n";
                //check if I have backup
                Location temp = scaleAdd(aLoc, inverse, leftFront);
                // const Tile* backupTile = aGame.getTileAt(aLoc - inverse * Location(1,1));
                const Tile* backupTile = aGame.getTileAt(temp);
                if(backupTile && backupTile->getPiece()==nullptr){
                    std::cout <<", NO\n";
                    return false;
                }
//                if(backupTile && backupTile->getPiece()!=nullptr){
//                    if (backupTile->getPiece()->getColor() != color){
//                        std::cout <<", NO\n";
//                        return false;
//                    }
//                }
                if(comeFrom == 4){
                    std::cout <<", NO\n";
                    return false;
                }
            }
        }
    }
    std::cout <<", YES!\n";
    return true;
}

bool Player::hasPiece(Game& aGame, const Location& aLoc, const PieceColor color) {
    const Tile* tile = aGame.getTileAt(aLoc);
    if (tile && tile->getPiece() && tile->getPiece()->getColor() == color) {
        return true;
    }
    return false;
}

bool Player::jumpOpponent(Game& aGame, const Piece* p) {
    // aGame.movePieceTo(*p, *nextStep);
    const PieceColor enemyColor = getOpponentColor();
    
    bool jump = true;
    Location original(p->getLocation());
    
    const Tile* tile = nullptr;
    while (jump) {
        // 1. RightFront
        if (hasPiece(aGame, getRightFront(p, 1), enemyColor)) {
            tile = aGame.getTileAt(getRightFront(p, 2));
            if (tile && tile->getPiece() == nullptr) {
                std::cout << "jumpOpponent\n";
                aGame.movePieceTo(*p, getRightFront(p, 2));
                continue;
            }
        }
        
        // 2. LeftFront
        if (hasPiece(aGame, getLeftFront(p, 1), enemyColor)) {
            tile = aGame.getTileAt(getLeftFront(p, 2));
            if (tile && tile->getPiece() == nullptr) {
                std::cout << "jumpOpponent\n";
                aGame.movePieceTo(*p, getLeftFront(p, 2));
                continue;
            }
        }
        
        if (p->getKind() == PieceKind::king) {
            // 3. RightBack
            if (hasPiece(aGame, getRightBack(p, 1), enemyColor)) {
                tile = aGame.getTileAt(getRightBack(p, 2));
                if (tile && tile->getPiece() == nullptr) {
                    std::cout << "jumpOpponent\n";
                    aGame.movePieceTo(*p, getRightBack(p, 2));
                    continue;
                }
            }
            
            // 4. LeftBack
            if (hasPiece(aGame, getLeftBack(p, 1), enemyColor)) {
                tile = aGame.getTileAt(getLeftBack(p, 2));
                if (tile && tile->getPiece() == nullptr) {
                    std::cout << "jumpOpponent\n";
                    aGame.movePieceTo(*p, getLeftBack(p, 2));
                    continue;
                }
            }
        }
        
        // No action can be taken
        jump = false;
    }
    
    return !isEqualLocation(original, p->getLocation());
    // return !(original == p->getLocation());
}

// Core methods
bool Player::takeTurn(Game &aGame, Orientation aDirection, std::ostream &aLog) {
    //    size_t theCount = aGame.countAvailablePieces(color);
    // Get self pieces and nearby
    safe2Move.clear();

    std::vector<const Piece*> movable;
    std::cout << (color == PieceColor::blue? "Gold ":"Blue ") << "has moved, ";
    std::cout << (color == PieceColor::blue? "Blue ":"Gold ") << "should move now\n";
    
    for (int pos = 0; pos < 12; pos++) {
        // NOTICE HOW WE CHECK FOR CAPTURED PIECES?
        if (const Piece *p = aGame.getAvailablePiece(this->color, pos)) {
            if (jumpOpponent(aGame, p)) {
                return true;
            }
            // Check if movable
            if (checkMovable(aGame, p)) {
                movable.push_back(p);
            }
        }
    }
    
//    std::cout << "Movable: " << movable.size() << std::endl;
    
    // Get all danger checks
    std::vector<const Piece*> endanger;
    for (const Piece* p : movable) {
        if (isThreatened(aGame, p)) {
            endanger.push_back(p);
        }
    }
    std::cout << "Endanger: " << endanger.size() << std::endl;
    
    // helper
//    Location* nextStep = nullptr;
    bool saved = false;
    for (const Piece* p : endanger) {
        saved = helper(aGame, p, movable, 1);
        if (saved) {
            return true;
        }
    }
    
    // next round in danger
    endanger.clear();
    for (const Piece* p : movable) {
        if (nextRoundInDanger(aGame, p)) {
            endanger.push_back(p);
        }
    }
    std::cout << "Second Endanger: " << endanger.size() << std::endl;
    
    // helper
    saved = false;
    for (const Piece* p : endanger) {
        saved = helper(aGame, p, movable, 2);
        if (saved) {
            return true;
        }
    }
    
    // limit enemy's movement
    for (const Piece* p : movable) {
        // std::cout << "yo\n";
        nextStep = blockOpponent(aGame, p);
        if (nextStep) {
             aGame.movePieceTo(*p, *nextStep);
            return true;
        }
    }
    
    //
//    if (safe2Move.size() != 0) {
//        std::cout << "safe2Move: ";
//        for (auto p : safe2Move) {
//            std::cout << p->getLocation() << ", ";
//        }
//        std::cout << std::endl;
//    }
    //
    
    for (const Piece* p : movable) {
        if (goKing(aGame, p)) {
            return true;
        }
    }
    
    for (const Piece* p : movable) {
        nextStep = killOpponent(aGame, p);
        if (nextStep) {
            aGame.movePieceTo(*p, *nextStep);
            return true;
        }
    }
    
    if (safe2Move.size() != 0) {
        for (const Piece* p : safe2Move) {
            if (takeAnyAction(aGame, p))
                return true;
        }
    }

    for (const Piece* p : movable) {
        if (takeAnyAction(aGame, p)) {
            return true;
        }
    }
    
    while (true) {
        int randPiece = rand() % 12;
        const Piece* p = aGame.getAvailablePiece(color, randPiece);
        if (p && takeAnyAction(aGame, p, false)) {
            return true;
        }
    }
    
    return false; //if you return false, you forfeit!
}


bool Player::isBackup(Game &aGame, const Piece *p, unsigned short int direction) {
    const Tile* teammateTile = nullptr;
    const Tile* enemyTile = nullptr;
    if(direction == 1){
        teammateTile = aGame.getTileAt(getLeftFront(p));
        enemyTile = aGame.getTileAt(getLeftFront(p,2));
        if(teammateTile && teammateTile->getPiece()){
            if(teammateTile->getPiece()->getColor() == color){
                if(enemyTile && enemyTile->getPiece()){
                    if(enemyTile->getPiece()->getColor() == getOpponentColor()){
                        return true;
                    }
                }
            }
        }
    }
    if(direction == 2){
        teammateTile = aGame.getTileAt(getRightFront(p));
        enemyTile = aGame.getTileAt(getRightFront(p,2));
        if(teammateTile && teammateTile->getPiece()){
            if(teammateTile->getPiece()->getColor() == color){
                if(enemyTile && enemyTile->getPiece()){
                    if(enemyTile->getPiece()->getColor() == getOpponentColor()){
                        return true;
                    }
                }
            }
        }
    }
    if(direction == 3){
        bool right = isBackup(aGame, p, 2);
        bool left = isBackup(aGame, p, 1);
        return right&&left;
    }
    
    return false;
}

bool Player::checkMovable(Game &aGame, const Piece *p) {

    const Tile* desiredTile = nullptr;
    // Want to move to right-front
    desiredTile = aGame.getTileAt(getRightFront(p));
    if (desiredTile && desiredTile->getPiece() == nullptr) {
        //check if I am a backup (i.e. if left front is a teammate and left left front front is an enemy)
        if(isBackup(aGame, p, 1)){
            return false;
        }
        return true;
    }
    
    // Want to move to left-front
    desiredTile = aGame.getTileAt(getLeftFront(p));
    if (desiredTile && desiredTile->getPiece() == nullptr) {
        if(isBackup(aGame, p, 2)){
            return false;
        }
        return true;
    }
    // king
    if (p->getKind() == PieceKind::king) {
        desiredTile = aGame.getTileAt(getRightBack(p));
        if (desiredTile && desiredTile->getPiece() == nullptr) {
            if(isBackup(aGame, p, 3)){
                return false;
            }
            return true;
        }
        
        desiredTile = aGame.getTileAt(getLeftBack(p));
        if (desiredTile && desiredTile->getPiece() == nullptr) {
            if(isBackup(aGame, p, 3)){
                return false;
            }
            return true;
        }
    }
    
    
    
    return false;
}

/*
 bool Player::underThreatAt(Game& aGame, const Piece* p, locFcn front, locFcn back) {
 static const PieceColor enemyColor = getOpponentColor();
 
 bool hasExit = false;
 bool hasEnemy = false;
 
 const Tile* frontTile = aGame.getTileAt(*front(p, 1));
 if (frontTile && frontTile->getPiece()) {
 if (frontTile->getPiece()->getColor() == enemyColor) {
 hasEnemy = true;
 }
 }
 
 const Tile* backTile = aGame.getTileAt(*back(p, 1));
 if (backTile && backTile->getPiece() == nullptr) {
 hasExit = true;
 }
 
 if (hasEnemy && !hasExit) {
 return true;
 }
 return true;
 }
 */

bool Player::isThreatened(Game& aGame, const Piece *p) {
    // Location current = p->getLocation();
    const PieceColor enemyColor = getOpponentColor();
    
    bool hasEnemy = false;
    bool noBackup = false;
    const Tile* enemyTile = nullptr;
    const Tile* exitTile = nullptr;
    
    // 1. Check rightFront-leftBack
    // underThreatAt(aGame, p, &(getRightFront), &(getLeftBack));
    enemyTile = aGame.getTileAt(getRightFront(p));
    if (enemyTile && enemyTile->getPiece()) {
        if (enemyTile->getPiece()->getColor() == enemyColor) {
            hasEnemy = true;
        }
    }
    
    exitTile = aGame.getTileAt(getLeftBack(p));
    if (exitTile && exitTile->getPiece() == nullptr) {
        noBackup = true;
    }
    
    if (hasEnemy && noBackup) {
        std::cout << "endanger type 1\n";
        return true;
    }
    
    hasEnemy = false;
    noBackup = false;
    
    // 2. Check leftFront-rightBack
    enemyTile = aGame.getTileAt(getLeftFront(p));
    if (enemyTile && enemyTile->getPiece()) {
        if (enemyTile->getPiece()->getColor() == enemyColor) {
            hasEnemy = true;
        }
    }
    
    exitTile = aGame.getTileAt(getRightBack(p));
    if (exitTile && exitTile->getPiece() == nullptr) {
        noBackup = true;
    }
    
    if (hasEnemy && noBackup) {
        std::cout << "endanger type 2\n";
        return true;
    }
    hasEnemy = false;
    noBackup = false;
    
    // 3. Check rightBack-leftFront
    enemyTile = aGame.getTileAt(getRightBack(p));
    if (enemyTile && enemyTile->getPiece()) {
        if (enemyTile->getPiece()->getColor() == enemyColor && enemyTile->getPiece()->getKind() == PieceKind::king) {
            hasEnemy = true;
        }
    }
    
    exitTile = aGame.getTileAt(getLeftFront(p));
    if (exitTile && exitTile->getPiece() == nullptr) {
        noBackup = true;
    }
    
    if (hasEnemy && noBackup) {
        std::cout << "endanger type 3\n";
        return true;
    }
    hasEnemy = false;
    noBackup = false;
    
    // 4. Check leftBack-rightFront
    enemyTile = aGame.getTileAt(getLeftBack(p));
    if (enemyTile && enemyTile->getPiece()) {
        if (enemyTile->getPiece()->getColor() == enemyColor && enemyTile->getPiece()->getKind() == PieceKind::king) {
            hasEnemy = true;
        }
    }
    
    exitTile = aGame.getTileAt(getRightFront(p));
    if (exitTile && exitTile->getPiece() == nullptr) {
        noBackup = true;
    }
    
    if (hasEnemy && noBackup) {
        std::cout << "endanger type 4\n";
        return true;
    }
    
    return false;
}

bool Player::nextRoundInDanger(Game& aGame, const Piece *p) {
    Location current = p->getLocation();
    
    int inverse = color == PieceColor::blue? 1: -1;
    const PieceColor enemyColor = getOpponentColor();
    
    // Go through all avaliavle pieces of counter color, and find if any king is nearby current p
    
    bool hasEnemy;
    bool noCounterPart;
    const Tile *counterTile;
    for (int pos = 0; pos < 12; pos++) {
        // Go through all the enemy's pieces and check if they are alive
        if(const Piece *thePiece = aGame.getAvailablePiece(enemyColor, pos)){
            // For every piece in enemy, check if it sits in either 8 places
            // 1. enemy is in the second right front
            // 2. enemy is in the second front
            // 3. enemy is in the second left front
            // For below five cases will be in danger only when enemy is king
            // 4. enemy is in the second left
            // 5. enemy is in the second left back
            // 6. enemy is in the second back
            // 7. enemy is in the second right back
            // 8. enemy is in the second right
            
            // 1. enemy is in the second right front, in this case empty has to be in leftBack
            
            // hasEnemy = thePiece->getLocation() == current + inverse*Location(-2,2);
            Location temp1(-2, 2);
            Location temp2 = scaleAdd(current, inverse, temp1);
            hasEnemy = isEqualLocation(thePiece->getLocation(), temp2);
            
            // counterTile = aGame.getTileAt(current + inverse*leftBack);
            counterTile = aGame.getTileAt(scaleAdd(current, inverse, leftBack));
            if(counterTile){
                noCounterPart = counterTile->getPiece() == nullptr;
                if(hasEnemy && noCounterPart){
                    // is in second-round-danger!
                    return true;
                }
            }
            
            // 2. enemy is in the second front, in this case empty can be in either rightBack or leftBack
            // hasEnemy = thePiece->getLocation() == current + inverse*Location(-2,0);
            temp1 = Location(-2, 0);
            temp2 = scaleAdd(current, inverse, temp1);
            hasEnemy = isEqualLocation(thePiece->getLocation(), temp2);
            
            // counterTile = aGame.getTileAt(current + inverse*rightBack);
            counterTile = aGame.getTileAt(scaleAdd(current, inverse, rightBack));
            if(counterTile){
                noCounterPart = counterTile->getPiece() == nullptr;
                if(hasEnemy && noCounterPart){
                    // is in second-round-danger!
                    return true;
                }
            }
            // counterTile = aGame.getTileAt(current + inverse*leftBack);
            counterTile = aGame.getTileAt(scaleAdd(current, inverse, leftBack));
            if(counterTile){
                noCounterPart = counterTile->getPiece() == nullptr;
                if(hasEnemy && noCounterPart){
                    // is in second-round-danger!
                    return true;
                }
            }
            
            // 3. enemy is in the second left front, in this case empty has to be in rightBack
            // hasEnemy = thePiece->getLocation() == current + inverse*Location(-2,-2);
            temp1 = Location(-2, -2);
            temp2 = scaleAdd(current, inverse, temp1);
            hasEnemy = isEqualLocation(thePiece->getLocation(), temp2);
            
            // counterTile = aGame.getTileAt(current + inverse*rightBack);
            counterTile = aGame.getTileAt(scaleAdd(current, inverse, rightBack));
            if(counterTile){
                noCounterPart = counterTile->getPiece() == nullptr;
                if(hasEnemy && noCounterPart){
                    // is in second-round-danger!
                    return true;
                }
            }
            
            if(thePiece->getKind() == PieceKind::king){
                // 4. enemy is in the second left, in this case empty has to be in rightFront or RightBack
                // hasEnemy = thePiece->getLocation() == current + inverse*Location(0,-2);
                temp1 = Location(0, -2);
                temp2 = scaleAdd(current, inverse, temp1);
                hasEnemy = isEqualLocation(thePiece->getLocation(), temp2);

                // counterTile = aGame.getTileAt(current + inverse*rightFront);
                counterTile = aGame.getTileAt(scaleAdd(current, inverse, rightFront));
                if(counterTile){
                    noCounterPart = counterTile->getPiece() == nullptr;
                    if(hasEnemy && noCounterPart){
                        // is in second-round-danger!
                        return true;
                    }
                }
                // counterTile = aGame.getTileAt(current + inverse*rightBack);
                counterTile = aGame.getTileAt(scaleAdd(current, inverse, rightBack));
                if(counterTile){
                    noCounterPart = counterTile->getPiece() == nullptr;
                    if(hasEnemy && noCounterPart){
                        // is in second-round-danger!
                        return true;
                    }
                }
                
                // 5. enemy is in the second left back, in this case empty has to be in rightFront
                // hasEnemy = thePiece->getLocation() == current + inverse*Location(2,-2);
                temp1 = Location(2, -2);
                temp2 = scaleAdd(current, inverse, temp1);
                hasEnemy = isEqualLocation(thePiece->getLocation(), temp2);
                
                // counterTile = aGame.getTileAt(current + inverse*rightFront);
                counterTile = aGame.getTileAt(scaleAdd(current, inverse, rightFront));
                if(counterTile){
                    noCounterPart = counterTile->getPiece() == nullptr;
                    if(hasEnemy && noCounterPart){
                        // is in second-round-danger!
                        return true;
                    }
                }
                
                
                // 6. enemy is in the second back, in this case empty has to be in rightFront or leftFront
                // hasEnemy = thePiece->getLocation() == current + inverse*Location(2,0);
                temp1 = Location(2, 0);
                temp2 = scaleAdd(current, inverse, temp1);
                hasEnemy = isEqualLocation(thePiece->getLocation(), temp2);

                // counterTile = aGame.getTileAt(current + inverse*rightFront);
                counterTile = aGame.getTileAt(scaleAdd(current, inverse, rightFront));
                if(counterTile){
                    noCounterPart = counterTile->getPiece() == nullptr;
                    if(hasEnemy && noCounterPart){
                        // is in second-round-danger!
                        return true;
                    }
                }
                // counterTile = aGame.getTileAt(current + inverse*leftFront);
                counterTile = aGame.getTileAt(scaleAdd(current, inverse, leftFront));
                if(counterTile){
                    noCounterPart = counterTile->getPiece() == nullptr;
                    if(hasEnemy && noCounterPart){
                        // is in second-round-danger!
                        return true;
                    }
                }
                
                // 7. enemy is in the second right back, in this case empty has to be in leftFront
                // hasEnemy = thePiece->getLocation() == current + inverse*Location(2,2);
                temp1 = Location(2, 2);
                temp2 = scaleAdd(current, inverse, temp1);
                hasEnemy = isEqualLocation(thePiece->getLocation(), temp2);
                
                // counterTile = aGame.getTileAt(current + inverse*leftFront);
                counterTile = aGame.getTileAt(scaleAdd(current, inverse, leftFront));
                if(counterTile){
                    noCounterPart = counterTile->getPiece() == nullptr;
                    if(hasEnemy && noCounterPart){
                        // is in second-round-danger!
                        return true;
                    }
                }
                
                // 8. enemy is in the second right, in this case empty has to be in leftFront or leftBack
                // hasEnemy = thePiece->getLocation() == current + inverse*Location(0,2);
                temp1 = Location(0, 2);
                temp2 = scaleAdd(current, inverse, temp1);
                hasEnemy = isEqualLocation(thePiece->getLocation(), temp2);
                
                // counterTile = aGame.getTileAt(current + inverse*leftFront);
                counterTile = aGame.getTileAt(scaleAdd(current, inverse, leftFront));
                
                if(counterTile){
                    noCounterPart = counterTile->getPiece() == nullptr;
                    if(hasEnemy && noCounterPart){
                        // is in second-round-danger!
                        return true;
                    }
                }
                // counterTile = aGame.getTileAt(current + inverse*leftBack);
                counterTile = aGame.getTileAt(scaleAdd(current, inverse, leftBack));
                if(counterTile){
                    noCounterPart = counterTile->getPiece() == nullptr;
                    if(hasEnemy && noCounterPart){
                        // is in second-round-danger!
                        return true;
                    }
                }
            }
            
            
        }
    }
    
    return false;
}

bool Player::helper(Game& aGame, const Piece* dangerPiece, std::vector<const Piece*> movable, unsigned short int dangerLevel) {
    std::cout << "helper\n";
    const Tile* desiredTile = nullptr;
    const Tile* enemyTile = nullptr;
    Location backupLocation(0,0);
    
    if(dangerLevel == 1){
        // Is currerently endanger
        // Run, only check immediately danger
        // 1. Run to right-front if possible
        desiredTile = aGame.getTileAt(getRightFront(dangerPiece));
        nextLoc = desiredTile->getLocation();
        if (desiredTile && desiredTile->getPiece() == nullptr) {
            if(safeMove(aGame, nextLoc, 1)){
                aGame.movePieceTo(*dangerPiece, nextLoc);
//                std::cout << "\tsuccess, move to " << nextLoc << std::endl;
                return true;
            }
        }
        // 2. Run to left-front if possible
        desiredTile = aGame.getTileAt(getLeftFront(dangerPiece));
        nextLoc = desiredTile->getLocation();
        if (desiredTile && desiredTile->getPiece() == nullptr) {
            if(safeMove(aGame, nextLoc, 2)){
                aGame.movePieceTo(*dangerPiece, nextLoc);
//                std::cout << "\tsuccess, move to " << nextLoc << std::endl;
                return true;
            }
        }
        if (dangerPiece->getKind() == PieceKind::king) {
            // 3. Run to left-back if possible
            desiredTile = aGame.getTileAt(getLeftBack(dangerPiece));
            nextLoc = desiredTile->getLocation();
            if (desiredTile && desiredTile->getPiece() == nullptr) {
                if(safeMove(aGame, nextLoc, 3)){
                    aGame.movePieceTo(*dangerPiece, nextLoc);
//                    std::cout << "\tsuccess, move to " << nextLoc << std::endl;
                    return true;
                }
            }
            // 4. Run to right-back if possible
            desiredTile = aGame.getTileAt(getRightBack(dangerPiece));
            nextLoc = desiredTile->getLocation();
            if (desiredTile && desiredTile->getPiece() == nullptr) {
                if(safeMove(aGame, nextLoc, 4)){
                    aGame.movePieceTo(*dangerPiece, nextLoc);
//                    std::cout << "\tsuccess, move to " << nextLoc << std::endl;
                    return true;
                }
            }
        }

        // If failed all four direction, find backup.
        // First find enemy's location. Find if anyone can move to that location.
        // 1. Testing right-front
        enemyTile = aGame.getTileAt(getRightFront(dangerPiece));
        if (enemyTile && enemyTile->getPiece() != nullptr) {
            if(enemyTile->getPiece()->getColor() == getOpponentColor()){
                // Has enemy at right-front
                backupLocation = aGame.getTileAt(getLeftBack(dangerPiece))->getLocation();
                // Go through all movable to find someone to cover up
                for (const Piece* other : movable) {
                    if (other == dangerPiece) {
                        continue;
                    }
                    // Find nearby nearby
                    if (isEqualLocation(getRightFront(other), backupLocation)) {
                        if(safeMove(aGame, backupLocation, 1)){
                            aGame.movePieceTo(*other, backupLocation);
//                            std::cout << "\tsuccess, move to " << backupLocation << std::endl;
                            return true;
                        }
                    }
                    if (isEqualLocation(getLeftFront(other), backupLocation)) {
                        if(safeMove(aGame, backupLocation, 2)){
                            aGame.movePieceTo(*other, backupLocation);
//                            std::cout << "\tsuccess, move to " << backupLocation << std::endl;
                            return true;
                        }
                    }
                    if(other->getKind() == PieceKind::king){
                        if (isEqualLocation(getRightBack(other), backupLocation)) {
                            if(safeMove(aGame, backupLocation, 4)){
                                aGame.movePieceTo(*other, backupLocation);
//                                std::cout << "\tsuccess, move to " << backupLocation << std::endl;
                                return true;
                            }
                        }
                        if (isEqualLocation(getLeftBack(other), backupLocation)) {
                            if(safeMove(aGame, backupLocation, 3)){
                                aGame.movePieceTo(*other, backupLocation);
//                                std::cout << "\tsuccess, move to " << backupLocation << std::endl;
                                return true;
                            }
                        }
                    }
                }
            }
        }
        
        // 2. Testing left-front
        enemyTile = aGame.getTileAt(getLeftFront(dangerPiece));
        if (enemyTile && enemyTile->getPiece() != nullptr){
            if(enemyTile->getPiece()->getColor() == getOpponentColor()){
                // Has enemy at right-front
                backupLocation = aGame.getTileAt(getRightBack(dangerPiece))->getLocation();
                // Go through all movable to find someone to cover up
                for (const Piece* other : movable) {
                    if (other == dangerPiece) {
                        continue;
                    }
                    // Find nearby nearby
                    if (isEqualLocation(getRightFront(other), backupLocation)) {
                        if(safeMove(aGame, backupLocation, 1)){
                            aGame.movePieceTo(*other, backupLocation);
//                            std::cout << "\tsuccess, move to " << backupLocation << std::endl;
                            return true;
                        }
                    }
                    if (isEqualLocation(getLeftFront(other), backupLocation)) {
                        if(safeMove(aGame, backupLocation, 2)){
                            aGame.movePieceTo(*other, backupLocation);
//                            std::cout << "\tsuccess, move to " << backupLocation << std::endl;
                            return true;
                        }
                    }
                    if(other->getKind() == PieceKind::king){
                        if (isEqualLocation(getRightBack(other), backupLocation)) {
                            if(safeMove(aGame, backupLocation, 4)){
                                aGame.movePieceTo(*other, backupLocation);
//                                std::cout << "\tsuccess, move to " << backupLocation << std::endl;
                                return true;
                            }
                        }
                        if (isEqualLocation(getLeftBack(other), backupLocation)) {
                            if(safeMove(aGame, backupLocation, 3)){
                                aGame.movePieceTo(*other, backupLocation);
//                                std::cout << "\tsuccess, move to " << backupLocation << std::endl;
                                return true;
                            }
                        }
                    }
                }
            }
        }
        
        // 3. Testing left-back
        enemyTile = aGame.getTileAt(getLeftBack(dangerPiece));
        if (enemyTile && enemyTile->getPiece() != nullptr){
            if(enemyTile->getPiece()->getColor() == getOpponentColor() && enemyTile->getPiece()->getKind() == PieceKind::king){
                // Has enemy at right-front
                backupLocation = aGame.getTileAt(getRightFront(dangerPiece))->getLocation();
                // Go through all movable to find someone to cover up
                for (const Piece* other : movable) {
                    if (other == dangerPiece) {
                        continue;
                    }
                    // Find nearby nearby
                    if (isEqualLocation(getRightFront(other), backupLocation)) {
                        if(safeMove(aGame, backupLocation, 1)){
                            aGame.movePieceTo(*other, backupLocation);
//                            std::cout << "\tsuccess, move to " << backupLocation << std::endl;
                            return true;
                        }
                    }
                    if (isEqualLocation(getLeftFront(other), backupLocation)) {
                        if(safeMove(aGame, backupLocation, 2)){
                            aGame.movePieceTo(*other, backupLocation);
//                            std::cout << "\tsuccess, move to " << backupLocation << std::endl;
                            return true;
                        }
                    }
                    if(other->getKind() == PieceKind::king){
                        if (isEqualLocation(getRightBack(other), backupLocation)) {
                            if(safeMove(aGame, backupLocation, 4)){
                                aGame.movePieceTo(*other, backupLocation);
//                                std::cout << "\tsuccess, move to " << backupLocation << std::endl;
                                return true;
                            }
                        }
                        if (isEqualLocation(getLeftBack(other), backupLocation)) {
                            if(safeMove(aGame, backupLocation, 3)){
                                aGame.movePieceTo(*other, backupLocation);
//                                std::cout << "\tsuccess, move to " << backupLocation << std::endl;
                                return true;
                            }
                        }
                    }
                }
            }
        }
        
        // 4. Testing right-back
        enemyTile = aGame.getTileAt(getRightBack(dangerPiece));
        if (enemyTile && enemyTile->getPiece() != nullptr){
            if(enemyTile->getPiece()->getColor() == getOpponentColor() && enemyTile->getPiece()->getKind() == PieceKind::king){
                // Has enemy at right-front
                backupLocation = aGame.getTileAt(getLeftFront(dangerPiece))->getLocation();
                // Go through all movable to find someone to cover up
                for (const Piece* other : movable) {
                    if (other == dangerPiece) {
                        continue;
                    }
                    // Find nearby nearby
                    if (isEqualLocation(getRightFront(other), backupLocation)) {
                        if(safeMove(aGame, backupLocation, 1)){
                            aGame.movePieceTo(*other, backupLocation);
//                            std::cout << "\tsuccess, move to " << backupLocation << std::endl;
                            return true;
                        }
                    }
                    if (isEqualLocation(getLeftFront(other), backupLocation)) {
                        if(safeMove(aGame, backupLocation, 2)){
                            aGame.movePieceTo(*other, backupLocation);
//                            std::cout << "\tsuccess, move to " << backupLocation << std::endl;
                            return true;
                        }
                    }
                    if(other->getKind() == PieceKind::king){
                        if (isEqualLocation(getRightBack(other), backupLocation)) {
                            if(safeMove(aGame, backupLocation, 4)){
                                aGame.movePieceTo(*other, backupLocation);
//                                std::cout << "\tsuccess, move to " << backupLocation << std::endl;
                                return true;
                            }
                        }
                        if (isEqualLocation(getLeftBack(other), backupLocation)) {
                            if(safeMove(aGame, backupLocation, 3)){
                                aGame.movePieceTo(*other, backupLocation);
//                                std::cout << "\tsuccess, move to " << backupLocation << std::endl;
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    else{
        // Will be in danger at next round
    }
    return false;
}

Location* Player::blockOpponent(Game &aGame, const Piece* p) {
    std::cout << "blockOpponent\n";
    saftyCheck = false;
    const PieceColor enemyColor = getOpponentColor();
    
//    size_t theCount = aGame.countAvailablePieces(enemyColor);
//    bool hasEnemy;
//    bool noCounterPart;
    const Tile* targetTile = nullptr;
    // Check my status, If I were a pawn, check if I can move right-front or left front
    //      If I can move right-front, check if there's an enemy at
    //           A1. front front front left
    //           A2. front front front right
    //           A3. front front front right right right
    //      If it's safe, than move to right front.
    //      If I can move left-front, check is there's an enemy at
    //           B1. front front front right
    //           B2. front front front left
    //           B3. front front front left left left
    //      If it's safe, than move to left front.
    // If I were a King, check if there's an enemy at 12 outter position
    //      If it's safe, move to that direction.
    int inverse = color == PieceColor::blue? 1: -1;
    
    if(p->getKind()==PieceKind::pawn){
        // Test if can move right-front
        // nextLoc = p->getLocation() + inverse*Location(-1,1);
        Location temp(-1, 1);
        Location temp2(p->getLocation());
        nextLoc = scaleAdd(temp2, inverse, temp);

        targetTile = aGame.getTileAt(nextLoc);
        if(targetTile && targetTile->getPiece()==nullptr){
            // Test every enemy's pieces
            for (int pos = 0; pos < 12; pos++) {
                // If enemy exist
                if (const Piece *enemy = aGame.getAvailablePiece(enemyColor, pos)) {
                    // If enemy is at that sepcific location
                    //                    bool A1 = enemy->getLocation() == p->getLocation() + inverse*Location(-3, -1);
                    //                    bool A2 = enemy->getLocation() == p->getLocation() + inverse*Location(-3, 1);
                    //                    bool A3 = enemy->getLocation() == p->getLocation() + inverse*Location(-3, 3);

                    Location temp1(p->getLocation());
                    Location temp2(-3, -1);
                    bool A1 = isEqualLocation(enemy->getLocation(), scaleAdd(temp1, inverse, temp2));
                    temp2 = Location(-3, 1);
                    bool A2 = isEqualLocation(enemy->getLocation(), scaleAdd(temp1, inverse, temp2));
                    temp2 = Location(-3, 3);
                    bool A3 = isEqualLocation(enemy->getLocation(), scaleAdd(temp1, inverse, temp2));
                    if(A1 || A2 || A3){
                        // If it's a safe move
                        if(safeMove(aGame, nextLoc, 1)){
                            return &nextLoc;
                        }
                    }
                }
            }
            
        }
        
        // Test if can move left-front
        // nextLoc = p->getLocation() + inverse*Location(-1,-1);
        temp = p->getLocation();
        nextLoc = scaleAdd(temp, inverse, leftFront);

        targetTile = aGame.getTileAt(nextLoc);
        if(targetTile && targetTile->getPiece()==nullptr){
            // Test every enemy's pieces
            for (int pos = 0; pos < 12; pos++) {
                // If enemy exist
                if (const Piece *enemy = aGame.getAvailablePiece(enemyColor, pos)) {
                    // If enemy is at that sepcific location
//                    bool B1 = enemy->getLocation() == p->getLocation() + inverse*Location(-3, 1);
//                    bool B2 = enemy->getLocation() == p->getLocation() + inverse*Location(-3, -1);
//                    bool B3 = enemy->getLocation() == p->getLocation() + inverse*Location(-3, -3);
                    
                    Location temp1(p->getLocation());
                    Location temp2(-3, 1);
                    bool B1 = isEqualLocation(enemy->getLocation(), scaleAdd(temp1, inverse, temp2));
                    temp2 = Location(-3, -1);
                    bool B2 = isEqualLocation(enemy->getLocation(), scaleAdd(temp1, inverse, temp2));
                    temp2 = Location(-3, -3);
                    bool B3 = isEqualLocation(enemy->getLocation(), scaleAdd(temp1, inverse, temp2));
                    
                    if(B1 || B2 || B3){
                        // If it's a safe move
                        if(safeMove(aGame, nextLoc, 2)){
                            return &nextLoc;
                        }
                    }
                }
            }
            
        }
        
    }
    if(p->getKind()==PieceKind::king){
        for (int pos = 0; pos < 12; pos++) {
            // If enemy exist
            if (const Piece *enemy = aGame.getAvailablePiece(enemyColor, pos)) {
//                bool loc1 = enemy->getLocation() == p->getLocation() + inverse*Location(-3, -4);
//                bool loc2 = enemy->getLocation() == p->getLocation() + inverse*Location(-3, -2);
//                bool loc3 = enemy->getLocation() == p->getLocation() + inverse*Location(-3, 2);
//                bool loc4 = enemy->getLocation() == p->getLocation() + inverse*Location(-3, 4);
//                bool loc5 = enemy->getLocation() == p->getLocation() + inverse*Location(-1, -4);
//                bool loc6 = enemy->getLocation() == p->getLocation() + inverse*Location(-1, 4);
//                bool loc7 = enemy->getLocation() == p->getLocation() + inverse*Location(1, -4);
//                bool loc8 = enemy->getLocation() == p->getLocation() + inverse*Location(1, 4);
//                bool loc9 = enemy->getLocation() == p->getLocation() + inverse*Location(3, -4);
//                bool loc10 = enemy->getLocation() == p->getLocation() + inverse*Location(3, -2);
//                bool loc11 = enemy->getLocation() == p->getLocation() + inverse*Location(3, 2);
//                bool loc12 = enemy->getLocation() == p->getLocation() + inverse*Location(3, 4);
                
                Location temp1(enemy->getLocation());
                Location temp2(-3, -4);
                // bool B1 = isEqualLocation(enemy->getLocation(), scaleAdd(temp1, inverse, temp2));
                bool loc1  = isEqualLocation(enemy->getLocation(), scaleAdd(temp1, inverse, temp2));
                temp2 = Location(-3, -2);
                bool loc2  = isEqualLocation(enemy->getLocation(), scaleAdd(temp1, inverse, temp2));
                temp2 = Location(-3, 2);
                bool loc3  = isEqualLocation(enemy->getLocation(), scaleAdd(temp1, inverse, temp2));
                temp2 = Location(-3, 4);
                bool loc4  = isEqualLocation(enemy->getLocation(), scaleAdd(temp1, inverse, temp2));
                temp2 = Location(-1, -4);
                bool loc5  = isEqualLocation(enemy->getLocation(), scaleAdd(temp1, inverse, temp2));
                temp2 = Location(-1, 4);
                bool loc6  = isEqualLocation(enemy->getLocation(), scaleAdd(temp1, inverse, temp2));
                temp2 = Location(1, -4);
                bool loc7  = isEqualLocation(enemy->getLocation(), scaleAdd(temp1, inverse, temp2));
                temp2 = Location(1, 4);
                bool loc8  = isEqualLocation(enemy->getLocation(), scaleAdd(temp1, inverse, temp2));
                temp2 = Location(3, -4);
                bool loc9  = isEqualLocation(enemy->getLocation(), scaleAdd(temp1, inverse, temp2));
                temp2 = Location(3, -2);
                bool loc10 = isEqualLocation(enemy->getLocation(), scaleAdd(temp1, inverse, temp2));
                temp2 = Location(3, 2);
                bool loc11 = isEqualLocation(enemy->getLocation(), scaleAdd(temp1, inverse, temp2));
                temp2 = Location(3, 4);
                bool loc12 = isEqualLocation(enemy->getLocation(), scaleAdd(temp1, inverse, temp2));

                if(loc1 || loc2 || loc5){
                    // nextLoc = p->getLocation() + inverse*Location(-1, -1);
                    Location temp(p->getLocation());
                    nextLoc = scaleAdd(temp, inverse, leftFront);
                    if(safeMove(aGame, nextLoc, 2)){
                        return &nextLoc;
                    }
                }
                if(loc3 || loc4 || loc6){
                    // nextLoc = p->getLocation() + inverse*Location(-1, 1);
                    Location temp(p->getLocation());
                    nextLoc = scaleAdd(temp, inverse, rightFront);
                    
                    if(safeMove(aGame, nextLoc, 1)){
                        return &nextLoc;
                    }
                }
                if(loc7 || loc9 || loc10){
                    // nextLoc = p->getLocation() + inverse*Location(1, -1);
                    Location temp(p->getLocation());
                    nextLoc = scaleAdd(temp, inverse, leftBack);
                    
                    if(safeMove(aGame, nextLoc, 3)){
                        return &nextLoc;
                    }
                }
                if(loc8 || loc11 || loc12){
                    // nextLoc = p->getLocation() + inverse*Location(1, 1);
                    Location temp(p->getLocation());
                    nextLoc = scaleAdd(temp, inverse, rightBack);
                    
                    if(safeMove(aGame, nextLoc, 4)){
                        return &nextLoc;
                    }
                }
            }
        }
    }
    
    
    /*
     const Tile* target = nullptr;
     
     // Check if I can move right or move left
     
     // A. If I can move right, check if there's enemy in either 4 places
     // A1. enemy at front front front left
     // A2. enemy at front front front right
     // A3. enemy at front front front left left left
     // A4. enemy at front left left left
     // The fourth case need me to be king
     
     // B. If I can move left, check if there's enemy in either 4 places
     // B1. enemy at front front front right
     // B2. enemy at front front front left
     // B3. enemy at front front front right right right
     // B4. enemy at front right right right
     // The fourth case need me to be king
     
     // A1. enemy at front front front left
     bool viable = true;
     for (int step = 1; step < 3; ++step) {
     target = aGame.getTileAt(getRightFront(p, step));
     
     if (target && target->getPiece()) {
     viable &= (target->getPiece() == nullptr);
     }
     }
     std::cout << "viable: " << viable << std::endl;
     target = aGame.getTileAt(getRightFront(p, 3));
     
     if (viable && target && target->getPiece()) {
     if (target->getPiece()->getColor() == enemyColor) {
     std::cout << "Found blockable enemy for " << p->getLocation();
     std::cout << " at " << target->getLocation() << std::endl;
     nextLoc = getRightFront(p, 1);
     return &nextLoc;
     }
     }
     // A2. enemy at front front front right
     // A3. enemy at front front front left left left...
     */
//    std::cout << " - " << p->getLocation() << " attempt failed\n";
    
    if (!saftyCheck) {
        safe2Move.push_back(p);
    }
    return nullptr;
}

bool Player::goKing(Game& aGame, const Piece *p) {
    std::cout << "GO king!\n";
    const Tile* aTile = nullptr;
    if(color == PieceColor::blue){
        for(int row = 0; row < 8; row++){
            for(int col = 0; col < 8; col++){
                aTile = aGame.getTileAt(Location(row, col));
                if(aTile->getPiece() != nullptr){
                    if((aTile->getPiece()->getColor() == color) && (aTile->getPiece()->getKind() == PieceKind::pawn)){
                     // Find my farest piece
                        if(takeAnyAction(aGame, aTile->getPiece(), true)){
                            std::cout << "-success\n";
                            return true;
                        }
                    }
                }
            }
        }
    }else{
        for(int row = 7; row >= 0; row--){
            for(int col = 7; col >= 0; col--){
                aTile = aGame.getTileAt(Location(row, col));
                if(aTile->getPiece() != nullptr){
                    if((aTile->getPiece()->getColor() == color) && (aTile->getPiece()->getKind() == PieceKind::pawn)){
                     // Find my farest piece
                        if(takeAnyAction(aGame, aTile->getPiece(), true)){
                            std::cout << "-success\n";
                            return true;
                        }
                    }
                }
            }
        }
    }
    std::cout << "-failed\n";
    return false;
}

Location* Player::killOpponent(Game& aGame, const Piece *p) {
    double enemy_CoM_row = 0;
    double enemy_CoM_col = 0;
    double my_CoM_row = 0;
    double my_CoM_col = 0;
    const Tile* aTile = nullptr;
    for(int row = 0; row < 8; row++){
        for(int col = 0; col < 8; col++){
            aTile = aGame.getTileAt(Location(row, col));
            if(aTile->getPiece() != nullptr){
                if((aTile->getPiece()->getColor() == getOpponentColor())){
                    enemy_CoM_row += aTile->getPiece()->getLocation().row;
                    enemy_CoM_col += aTile->getPiece()->getLocation().col;
                }
                if((aTile->getPiece()->getColor() == color)){
                    my_CoM_row += aTile->getPiece()->getLocation().row;
                    my_CoM_col += aTile->getPiece()->getLocation().col;
                }
            }
        }
    }
//    for (int pos = 0; pos < 12; pos++) {
//        if (const Piece *me = aGame.getAvailablePiece(color, pos)) {
//
//        }
//    }
    
    return nullptr;
}

bool Player::takeAnyAction(Game& aGame, const Piece *p, bool safety) {
    std::cout << "safety: " << safety << std::endl;
    const Tile* destTile = nullptr;
    std::vector<int> action_seq{0, 1, 2, 3};
    
    auto rng = std::default_random_engine{};
    std::shuffle(std::begin(action_seq), std::end(action_seq), rng);
    for(auto act : action_seq){
        if(act == 0){
            destTile = aGame.getTileAt(getRightFront(p));
            if (destTile && destTile->getPiece() == nullptr) {
                if (safety) {
                    if (safeMove(aGame, nextLoc, 1)) {
                        aGame.movePieceTo(*p, destTile->getLocation());
                        return true;
                    }
                }
                else {
                    aGame.movePieceTo(*p, destTile->getLocation());
                    return true;
                }
            }
        }
        if(act == 1){
            destTile = aGame.getTileAt(getLeftFront(p));
            if (destTile && destTile->getPiece() == nullptr) {
                if (safety) {
                    if (safeMove(aGame, nextLoc, 2)) {
                        aGame.movePieceTo(*p, destTile->getLocation());
                        return true;
                    }
                }
                else {
                    aGame.movePieceTo(*p, destTile->getLocation());
                    return true;
                }
            }
        }
        // king
        if(act == 2){
            if (p->getKind() == PieceKind::king) {
                destTile = aGame.getTileAt(getRightBack(p));
                if (destTile && destTile->getPiece() == nullptr) {
                    if (safety) {
                        if (safeMove(aGame, nextLoc, 4)) {
                            aGame.movePieceTo(*p, destTile->getLocation());
                            return true;
                        }
                    }
                    else {
                        aGame.movePieceTo(*p, destTile->getLocation());
                        return true;
                    }
                }
            }
        }
        if(act == 3){
            if (p->getKind() == PieceKind::king) {
                destTile = aGame.getTileAt(getLeftBack(p));
                if (destTile && destTile->getPiece() == nullptr) {
                    if (safety) {
                        if (safeMove(aGame, nextLoc, 3)) {
                            aGame.movePieceTo(*p, destTile->getLocation());
                            return true;
                        }
                    }
                    else {
                        aGame.movePieceTo(*p, destTile->getLocation());
                        return true;
                    }
                }
            }
        }
    }
   /*
   // Can be used to re-check all movable (without backup check, to get maximum movability)
   // TO-DO: Check acquisition of enemy
   // std::cout << p->getLocation();
   
   const Tile* currentTile = nullptr;
   
   currentTile = aGame.getTileAt(getRightFront(p));
   if (currentTile && currentTile->getPiece() == nullptr) {
       return true;
   }
   
   currentTile = aGame.getTileAt(getLeftFront(p));
   if (currentTile && currentTile->getPiece() == nullptr) {
       return true;
   }
   
   // king
   if (p->getKind() == PieceKind::king) {
       currentTile = aGame.getTileAt(getRightBack(p));
       if (currentTile && currentTile->getPiece() == nullptr) {
           return true;
       }
       
       currentTile = aGame.getTileAt(getLeftBack(p));
       if (currentTile && currentTile->getPiece() == nullptr) {
           return true;
       }
   }
   */
    return false;
}
}
