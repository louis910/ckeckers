#pragma once
#include "Player.hpp"
#include "Game.hpp"
#include <vector>
namespace ECE141 {
	class YuPlayer :public Player
	{
	public:
		virtual bool takeTurn(Game& aGame, Orientation aDirection, std::ostream& aLog);
		YuPlayer();
	private:
		PieceColor opponentColor;
		Piece* minPiece = 0;
		std::vector<Location> minRoute;
		const int dangerScore;
		const int eatenScore;
		const int kingScore;
		int minScore = INT_MAX;
		int calScore(Game& aGame,Piece* piece, PieceKind currKind, Location Location, std::vector<Piece*> eaten);
		void moveMode(Game& aGame, Piece* piece);
		void eatMode(Game& aGame, Piece* piece);
		void eatHelper(Game& aGame, Piece* piece, PieceKind currKind, Location currLoc, std::vector<Location>& visited, std::vector<Piece*> eaten);
		bool containsLocation(std::vector<Location> locations,Location target);
		bool canJumpTo(Game& aGame,Location currLoc, int aDeltaX, int aDeltaY, std::vector<Location>& visited);
		bool pieceHasJump(Game& aGame, PieceKind currKind, Location currLoc, std::vector<Location>& visited);
		bool canMoveTo(Game& aGame, const Piece* aPiece, int aDeltaX, int aDeltaY);
		bool isKingable(Game& aGame, const Piece& aPiece, const Location& aDest);
		int distanceBetween(Location from, Location to);
		bool inDanger(Game& aGame, Location location, std::vector<Piece*> eaten);
		int calKing(Piece* piece, PieceKind kind);
		bool isEaten(const Piece* piece, std::vector<Piece*> eaten);
		int calEaten(const Piece* piece,std::vector<Piece*> eaten);
		int calDanger(Game& aGame, Location location , std::vector<Piece*> eaten);
	};

}

