//
//  Player.hpp
//  Checkers
//
//  Created by rick gessner on 2/22/19.
//  Copyright © 2019 rick gessner. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include "Piece.hpp"
#include <iostream>
#include <vector>



namespace ECE141 {

class Game; //forward declare...

class Player {
typedef Location* (Player::*locFcn)(const Piece*, int);
public:
    Player();
    virtual bool      takeTurn(Game &aGame, Orientation aDirection, std::ostream &aLog);
    const PieceColor  color;
    static int        pcount; //how many created so far?
    
protected:
    bool checkMovable(Game&, const Piece*);
    bool isThreatened(Game&, const Piece*);
    bool nextRoundInDanger(Game&, const Piece*);
    bool hasPiece(Game&, const Location&, const PieceColor);
    bool jumpOpponent(Game&, const Piece*);
    bool helper(Game& aGame, const Piece*, std::vector<const Piece*>, unsigned short int dangerLevel=1);
    Location* blockOpponent(Game&, const Piece*);
    bool goKing(Game&, const Piece*);
    Location* killOpponent(Game&, const Piece*);
    bool takeAnyAction(Game& aGame, const Piece* p, bool safety=true);
    
    bool underThreatAt(Game&, const Piece*, locFcn, locFcn);
    
    PieceColor getOpponentColor() {
        return (color == PieceColor::blue) ? PieceColor::gold : PieceColor::blue;
    }
    
    std::vector<const Piece*> opponents;
    Location* nextStep = nullptr;
    Location nextLoc{0, 0};
    void getOpponents(Game& aGame, const PieceColor enemyColor);
    
    bool saftyCheck = false;
    std::vector<const Piece*> safe2Move;

private:
    Location rightFront{-1, 1};
    Location leftFront{-1, -1};

    Location leftBack{1, -1};
    Location rightBack{1, 1};
    
    int getForwardDirection(const Piece* p) {
        return (p->getColor() == PieceColor::blue) ? 1 : -1;
    }
    
    int getBackwardDirection(const Piece* p) {
//        if (p->getKind() == PieceKind::pawn)
//            return 0;
        return (p->getColor() == PieceColor::blue) ? 1 : -1;
    }

    Location getRightFront(const Piece* p, int step=1);
    Location getLeftFront(const Piece* p, int step=1);
    Location getRightBack(const Piece* p, int step=1);
    Location getLeftBack(const Piece* p, int step=1);
    
    Location addLocation(Location& a, Location& b) {
        Location loc(a);
        loc.row += b.row;
        loc.col += b.col;
        return loc;
    }

    Location scaleLocation(int s, const Location& a) {
        return Location{s * a.row, s * a.col};
    }
    
    Location scaleAdd(Location& a, int s, Location& b) {
        Location loc(a);
        loc.row += s * b.row;
        loc.col += s * b.col;
        return loc;
    }
    
    bool isEqualLocation(const Location& a, const Location& b) {
        return (a.row == b.row) && (a.col == b.col);
    }
    
    bool safeMove(Game& aGame, Location& aLoc, unsigned short int direction );
    bool isBackup(Game &aGame, const Piece *p, unsigned short int direction );
};
}

#endif /* Player_hpp */
