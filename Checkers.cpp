#include <map>
#include "src/Game.h"
#include "src/Player.h"
#include "src/Board.h"

using namespace std;

bool inputPlayerType(int playerNumber);
void inputName(Player& p);

int main(int argc, char *argv[])
{
	Board board = Board();
	
	// set up Player 1
	bool redPlayerIsAI = inputPlayerType(1);
	if (redPlayerIsAI) {
		cout << "AI for this program is not yet supported. Exiting program." << endl;
		exit(1);
	}
	Player* redPlayer;
	if (!redPlayerIsAI) {
		string name = inputName();
		redPlayer = new Player(1, name, red);
	} else {
		// initialize Player 1 as AI 
	}
	
	// set up Player 2
	bool blackPlayerIsAI = inputPlayerType(2);
	if (blackPlayerIsAI) {
		cout << "AI for this program is not yet supported. Exiting program." << endl;
		exit(1);
	}
	Player* blackPlayer;
	if (!blackPlayerIsAI) {
		string name = inputName();
		blackPlayer = new Player(2, name, black);
	} else {
		// initialize Player 2 as AI 
	}
	
	cout << endl;
	
	// create an array of the two players
	Player* players[] = {redPlayer, blackPlayer};
	string teams[] = {"Red", "Black"};
	
	// play the game until one player runs out of pieces
	while (redPlayer->getPiecesRemaining() > 0 && blackPlayer->getPiecesRemaining() > 0) {
		// for each of the players
		for (int i = 0; i < 2; i++) {
			cout << "game\n\n\n\n" << endl;
			Player* currentPlayer = players[i];
			Player* enemyPlayer = players[!i];
			
			// print the board
			board.print();
			
			// prompt the user to enter coordinates
			cout << "\n\n" << teams[currentPlayer->getTeam()] << " Player's turn. ";
			
			cout << "Select coordinates of a friendly piece (x y) to see available moves: ";
			set<deque<tuple<int,int> > > availableMoves = selectPieceAndGetMoves(board, currentPlayer);
			
			// retrieve the map of available moves
			map<int, deque<tuple<int,int> > > moveMap = displayMovesAndReturnMap(availableMoves);
			
			// let the user pick a move
			int moveNumber = getMoveNumber(moveMap.size());
			deque<tuple<int,int> > finalMove = moveMap[moveNumber];
			
			// move to the space and delete all attacked pieces along the way
			tuple<int,int> pieceCoordinates = finalMove.front();
			finalMove.pop_front();
			int numCaptured = board.getTiles()[get<1>(pieceCoordinates)][get<0>(pieceCoordinates)]->getPiece()->move(finalMove);
			
			// update enemy player's piecesRemaining count
			for (int j = 0; j < numCaptured; j++) {
				enemyPlayer->decrementPiecesRemaining();
			}
		}
	}
	
	// deallocate players
	delete redPlayer;
	delete blackPlayer;
}