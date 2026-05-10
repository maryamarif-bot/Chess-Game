#include<iostream>
// Colors define karo — top pe add karo

using namespace std;

class Piece {
private:
	int row;
	int col;
	char color;
	char symbol;
public:
	Piece(int r, int c, char clr, char sym) {
		this->row = r;
		this->col = c;
		this->color = clr;
		this->symbol = sym;
	}
	int getRow() { return row; }
	int getCol() { return col; }
	char getColor() { return color; }
	char getSymbol() { return symbol; }
	void setPosition(int r, int c) {
		this->row = r;
		this->col = c;
	}
	virtual bool isValidMove(int toRow, int toCol, Piece* board[8][8]) = 0;
};

class Pawn : public Piece {
private:
	bool firstMove;

public:
	Pawn(int r, int c, char clr) : Piece(r, c, clr, 'P') {
		firstMove = true;
	}

	void setFirstMove(bool val) {
		firstMove = val;
	}

	bool getFirstMove() {
		return firstMove;
	}

	bool isValidMove(int toRow, int toCol, Piece* board[8][8]) {
		if (getColor() == 'W') {
			// Rule 5 — seedha blocked hai?
			if (toCol == getCol() && board[toRow][toCol] != nullptr)
				return false;

			// Rule 1 — pehli baar 2 step
			if (firstMove && toRow == getRow() - 2 && toCol == getCol()) {
				// beech wala square bhi khali hona chahiye
				if (board[getRow() - 1][toCol] == nullptr)
					return true;
			}

			// Rule 2 — standard 1 step aage
			if (toRow == getRow() - 1 && toCol == getCol())
				return true;

			// Rule 3 — diagonal capture
			// dushman ka piece ho tabhi
			if (toRow == getRow() - 1 && abs(toCol - getCol()) == 1) {
				if (board[toRow][toCol] != nullptr && board[toRow][toCol]->getColor() == 'B')
					return true;
			}

			// Rule 4 — peeche nahi ja sakta (toRow > getRow() = invalid)
		}
		else {
			// Rule 5 — seedha blocked hai?
			if (toCol == getCol() && board[toRow][toCol] != nullptr)
				return false;

			// Rule 1 — pehli baar 2 step
			if (firstMove && toRow == getRow() + 2 && toCol == getCol()) {
				// beech wala square bhi khali hona chahiye
				if (board[getRow() + 1][toCol] == nullptr)
					return true;
			}

			// Rule 2 — standard 1 step aage
			if (toRow == getRow() + 1 && toCol == getCol())
				return true;

			// Rule 3 — diagonal capture
			// dushman ka piece ho tabhi
			if (toRow == getRow() + 1 && abs(toCol - getCol()) == 1) {
				if (board[toRow][toCol] != nullptr && board[toRow][toCol]->getColor() == 'W')
					return true;
			}

			// Rule 4 — peeche nahi ja sakta (toRow < getRow() = invalid)
		}
		return false;
	}
};

//class Pawn : public Piece {
//public:
//	Pawn(int r, int c, char clr) : Piece(r, c, clr, 'P') {}
//	bool isValidMove(int toRow, int toCol, Piece* board[8][8]) {
//		if (getColor() == 'W') {
//			if (toRow == getRow() - 1 && toCol == getCol())
//				return true;
//		}
//		else {
//			if (toRow == getRow() + 1 && toCol == getCol())
//				return true;
//		}
//		return false;
//	}
//};

//class Rook : public Piece {
//public:
//	Rook(int r, int c, char clr) : Piece(r, c, clr, 'R') {}
//	bool isValidMove(int toRow, int toCol, Piece* board[8][8]) {
//		if (toRow == getRow() || toCol == getCol())
//			return true;
//		return false;
//	}
////};

class Rook : public Piece {
public:
	Rook(int r, int c, char clr) : Piece(r, c, clr, 'R') {}

	bool isValidMove(int toRow, int toCol, Piece* board[8][8]) {
		// Step 1 — seedha line check
		if (toRow != getRow() && toCol != getCol())
			return false;

		// Step 2 — path check
		// Vertical move — same column, row change
		if (toCol == getCol()) {
			int step = (toRow > getRow()) ? 1 : -1;
			for (int r = getRow() + step; r != toRow; r += step) {
				// beech mein koi piece hai?
				if (board[r][getCol()] != nullptr)
					return false;
			}
		}

		// Horizontal move — same row, col change
		if (toRow == getRow()) {
			int step = (toCol > getCol()) ? 1 : -1;
			for (int c = getCol() + step; c != toCol; c += step) {
				// beech mein koi piece hai?
				if (board[getRow()][c] != nullptr)
					return false;
			}
		}

		// Step 3 — destination check
		// apna piece hai wahan?
		if (board[toRow][toCol] != nullptr &&
			board[toRow][toCol]->getColor() == getColor())
			return false;

		// khali hai ya dushman hai — dono valid
		return true;
	}
};

class Knight : public Piece {
public:
	Knight(int r, int c, char clr) : Piece(r, c, clr, 'N') {}
	bool isValidMove(int toRow, int toCol, Piece* board[8][8]) {
		int rowDiff = abs(toRow - getRow());
		int colDiff = abs(toCol - getCol());
		if ((rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2))
			return true;
		return false;
	}
};

class Bishop : public Piece {
public:
	Bishop(int r, int c, char clr) : Piece(r, c, clr, 'B') {}
	bool isValidMove(int toRow, int toCol, Piece* board[8][8]) {
		if (abs(toRow - getRow()) == abs(toCol - getCol()))
			return true;
		return false;
	}
};

class Queen : public Piece {
public:
	Queen(int r, int c, char clr) : Piece(r, c, clr, 'Q') {}
	bool isValidMove(int toRow, int toCol, Piece* board[8][8]) {
		if ((toRow == getRow() || toCol == getCol()) ||
			(abs(toRow - getRow()) == abs(toCol - getCol())))
			return true;
		return false;
	}
};

class King : public Piece {
public:
	King(int r, int c, char clr) : Piece(r, c, clr, 'G') {}
	bool isValidMove(int toRow, int toCol, Piece* board[8][8]) {
		int rowDiff = abs(toRow - getRow());
		int colDiff = abs(toCol - getCol());
		if (rowDiff <= 1 && colDiff <= 1 && !(rowDiff == 0 && colDiff == 0))
			return true;
		return false;
	}
};

class Board {
private:
	Piece* grid[8][8];
	bool gameOver;
public:
	Board() {
		gameOver = false;
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
				grid[i][j] = nullptr;

		for (int j = 0; j < 8; j++) {
			grid[6][j] = new Pawn(6, j, 'W');
			grid[1][j] = new Pawn(1, j, 'B');
		}
		grid[7][0] = new Rook(7, 0, 'W');
		grid[7][7] = new Rook(7, 7, 'W');
		grid[7][1] = new Knight(7, 1, 'W');
		grid[7][6] = new Knight(7, 6, 'W');
		grid[7][2] = new Bishop(7, 2, 'W');
		grid[7][5] = new Bishop(7, 5, 'W');
		grid[7][3] = new Queen(7, 3, 'W');
		grid[7][4] = new King(7, 4, 'W');

		grid[0][0] = new Rook(0, 0, 'B');
		grid[0][7] = new Rook(0, 7, 'B');
		grid[0][1] = new Knight(0, 1, 'B');
		grid[0][6] = new Knight(0, 6, 'B');
		grid[0][2] = new Bishop(0, 2, 'B');
		grid[0][5] = new Bishop(0, 5, 'B');
		grid[0][3] = new Queen(0, 3, 'B');
		grid[0][4] = new King(0, 4, 'B');
	}

	bool isGameOver() { return gameOver; }

	void display() {
		cout << endl;
		cout << "  ||=========================================||" << endl;
		cout << "  ||        CHESS GAME  -  LIVE BOARD        ||" << endl;
		cout << "  ||=========================================||" << endl;
		cout << endl;
		cout << "       a    b    c    d    e    f    g    h" << endl;
		cout << "     +----+----+----+----+----+----+----+----+" << endl;
		for (int i = 0; i < 8; i++) {
			cout << "  " << (i) << "  |";
			for (int j = 0; j < 8; j++) {
				if (grid[i][j] == nullptr) {
					cout << "    |";
				}
				else {
					char clr = grid[i][j]->getColor();
					char sym = grid[i][j]->getSymbol();
					cout << " " << (char)tolower(clr) << sym << " |";
				}
			}
			cout << endl;
			cout << "     +----+----+----+----+----+----+----+----+" << endl;
		}
		cout << endl;
		cout << "  Pieces  =>  w = White  |  b = Black" << endl;
		cout << "  Symbols =>  P=Pawn  R=Rook  N=Knight" << endl;
		cout << "              B=Bishop  Q=Queen  G=King" << endl;
	}

	void showInstructions() {
		cout << endl;
		cout << "  ||=========================================||" << endl;
		cout << "  ||              HOW TO PLAY                ||" << endl;
		cout << "  ||=========================================||" << endl;
		cout << "  ||                                         ||" << endl;
		cout << "  ||  Enter row and column numbers (0 to 7)  ||" << endl;
		cout << "  ||                                         ||" << endl;
		cout << "  ||  ROW GUIDE:                             ||" << endl;
		cout << "  ||  Screen row 8  =  input row 0           ||" << endl;
		cout << "  ||  Screen row 7  =  input row 1           ||" << endl;
		cout << "  ||  Screen row 6  =  input row 2           ||" << endl;
		cout << "  ||  Screen row 5  =  input row 3           ||" << endl;
		cout << "  ||  Screen row 4  =  input row 4           ||" << endl;
		cout << "  ||  Screen row 3  =  input row 5           ||" << endl;
		cout << "  ||  Screen row 2  =  input row 6           ||" << endl;
		cout << "  ||  Screen row 1  =  input row 7           ||" << endl;
		cout << "  ||                                         ||" << endl;
		cout << "  ||  COL GUIDE:                             ||" << endl;
		cout << "  ||  a=0  b=1  c=2  d=3                     ||" << endl;
		cout << "  ||  e=4  f=5  g=6  h=7                     ||" << endl;
		cout << "  ||                                         ||" << endl;
		cout << "  ||  EXAMPLE:                               ||" << endl;
		cout << "  ||  Move White Pawn from a2 to a3:         ||" << endl;
		cout << "  ||  From: 6 0   To: 5 0                    ||" << endl;
		cout << "  ||                                         ||" << endl;
		cout << "  ||  Move Black Pawn from a7 to a6:         ||" << endl;
		cout << "  ||  From: 1 0   To: 2 0                    ||" << endl;
		cout << "  ||                                         ||" << endl;
		cout << "  ||  PIECE MOVEMENT RULES:                  ||" << endl;
		cout << "  ||  Pawn   = Forward only (1 step)         ||" << endl;
		cout << "  ||  Rook   = Straight (any distance)       ||" << endl;
		cout << "  ||  Knight = L-Shape (2+1 or 1+2)          ||" << endl;
		cout << "  ||  Bishop = Diagonal (any distance)       ||" << endl;
		cout << "  ||  Queen  = Any direction (any distance)  ||" << endl;
		cout << "  ||  King   = Any direction (1 step only)   ||" << endl;
		cout << "  ||                                         ||" << endl;
		cout << "  ||=========================================||" << endl;
		cout << endl;
	}

	bool movePiece(int r1, int c1, int r2, int c2, char currentPlayer) {
		// check 1 — source khali hai?
		if (grid[r1][c1] == nullptr) {
			cout << endl;
			cout << "  INVALID! This square is empty." << endl;
			cout << "  Reason: There is no piece on row " << r1 << " col " << c1 << "." << endl;
			cout << "  Please select a square that has your piece on it." << endl;
			return false;
		}
		// check 2 — apna piece hai?
		if (grid[r1][c1]->getColor() != currentPlayer) {
			cout << endl;
			cout << "  INVALID! This is not your piece." << endl;
			cout << "  Reason: " << (currentPlayer == 'W' ? "White" : "Black");
			cout << " can only move their own pieces." << endl;
			cout << "  The piece on this square belongs to your opponent." << endl;
			return false;
		}
		// check 3 — valid move hai?
		if (!grid[r1][c1]->isValidMove(r2, c2, grid)) {
			cout << endl;
			cout << "  INVALID MOVE! This piece cannot move to that square." << endl;
			cout << "  Reason: Each piece follows specific movement rules:" << endl;
			cout << "  Pawn   = Forward only (1 step)" << endl;
			cout << "  Rook   = Straight lines only" << endl;
			cout << "  Knight = L-Shape (2+1 or 1+2 squares)" << endl;
			cout << "  Bishop = Diagonal only" << endl;
			cout << "  Queen  = Any direction" << endl;
			cout << "  King   = Any direction but 1 step only" << endl;
			return false;
		}
		// check 4 — apne piece pe move nahi
		if (grid[r2][c2] != nullptr && grid[r2][c2]->getColor() == currentPlayer) {
			cout << endl;
			cout << "  INVALID! You cannot move to that square." << endl;
			cout << "  Reason: Your own piece is already on row " << r2 << " col " << c2 << "." << endl;
			cout << "  You cannot capture your own piece." << endl;
			return false;
		}
		// check 5 — capture hone pe message
		if (grid[r2][c2] != nullptr) {
			char sym = grid[r2][c2]->getSymbol();
			cout << endl;
			cout << "  CAPTURE! You captured opponent's piece: " << sym << endl;
			if (sym == 'G') {
				cout << endl;
				cout << "  ||=========================================||" << endl;
				cout << "  ||              GAME OVER!                 ||" << endl;
				cout << "  ||  " << (currentPlayer == 'W' ? "WHITE" : "BLACK");
				cout << " WINS THE GAME!                  ||" << endl;
				cout << "  ||=========================================||" << endl;
				gameOver = true;
			}
		}

		delete grid[r2][c2];
		grid[r2][c2] = grid[r1][c1];
		grid[r1][c1] = nullptr;
		grid[r2][c2]->setPosition(r2, c2);


		// YAHAN add karo
		if (Pawn* p = dynamic_cast<Pawn*>(grid[r2][c2])) {
			p->setFirstMove(false);
		}


		if (!gameOver) {
			cout << endl;
			cout << "  Move Successful!" << endl;
			cout << "  Piece moved from (" << r1 << "," << c1 << ")";
			cout << " to (" << r2 << "," << c2 << ")" << endl;
		}
		return true;
	}
};

class Game {
private:
	Board board;
	char currentPlayer;
public:
	Game() {
		currentPlayer = 'W';
	}

	void showMenu() {
		cout << endl;
		cout << "  ||=========================================||" << endl;
		cout << "  ||               MAIN MENU                 ||" << endl;
		cout << "  ||=========================================||" << endl;
		cout << "  ||   1. Start Game                         ||" << endl;
		cout << "  ||   2. How To Play                        ||" << endl;
		cout << "  ||   3. Exit                               ||" << endl;
		cout << "  ||=========================================||" << endl;
		cout << endl;
		cout << "   Enter your choice: ";
	}

	void start() {
		system("cls");
		cout << endl;
		cout << "  ||=========================================||" << endl;
		cout << "  ||                                         ||" << endl;
		cout << "  ||         WELCOME TO CHESS GAME!          ||" << endl;
		cout << "  ||                                         ||" << endl;
		cout << "  ||=========================================||" << endl;

		int choice;
		showMenu();
		cin >> choice;

		if (choice == 3) {
			cout << endl << "  Goodbye! Thanks for playing." << endl;
			return;
		}
		if (choice == 2) {
			system("cls");
			board.showInstructions();
			cout << "  Press Enter to Start Game...";
			cin.ignore();
			cin.get();
		}

		while (!board.isGameOver()) {
			system("cls");
			board.display();

			cout << endl;
			cout << "  ||=========================================||" << endl;
			if (currentPlayer == 'W')
				cout << "  ||  Current Player: WHITE                  ||" << endl;
			else
				cout << "  ||  Current Player: BLACK                  ||" << endl;
			cout << "  ||=========================================||" << endl;

			int r1, c1, r2, c2;
			cout << "\n  From (row col): ";
			cin >> r1 >> c1;
			cout << "  To   (row col): ";
			cin >> r2 >> c2;

			bool moved = board.movePiece(r1, c1, r2, c2, currentPlayer);

			if (moved && !board.isGameOver()) {
				if (currentPlayer == 'W') {
					currentPlayer = 'B';
					cout << endl << "  >>> Now it is BLACK's turn!" << endl;
				}
				else {
					currentPlayer = 'W';
					cout << endl << "  >>> Now it is WHITE's turn!" << endl;
				}
				cout << "  Press Enter to continue...";
				cin.ignore();
				cin.get();
			}
			else if (!moved) {
				cout << "  Press Enter to try again...";
				cin.ignore();
				cin.get();
			}
		}
		cout << endl;
		system("pause");
	}
};

int main() {
	Game g;
	g.start();
	system("pause");
	return 0;
}