# Ckeckers Game

## The `Game` Class

It's essential to understand the interface provided by the `Game` class first. It only offers a few methods for interacting with the game itself. The first three methods let ckecker-bot get information about the current game. 

```
    virtual size_t             countAvailablePieces(PieceColor aColor)=0;
    virtual const Piece* const getAvailablePiece(PieceColor aColor, int anIndex)=0;
    virtual const Tile*  const getTileAt(const Location &aLocation)=0;
    
    virtual bool               movePieceTo(const Piece &aPiece, const Location &aLocation)=0; 
```

### `countAvailablePieces(PieceColor aColor)` 
This method tells check-bot how many pieces of a given color remain on the board.  Check-bot might use this to control a while while analyzing options for each of its pieces on the board.

### `getAvailablePiece(PieceColor aColor, int anIndex)` 
This method retrieves the **Nth** _remaining_ piece of a given color that remains on the board. The game is free to return to pieces to check-bot in any order.  

### `getTileAt(const Location &aLocation)` 
This method retrieves a `Tile` object for checker-bot to inspect. Each tile knows the tile color, the location (row,col), and which `Piece` (if any) is occupying the `Tile`. 

When checker-bot are considering a move, it may call the `Game` to retrieve a `Tile` it are considering. If checker-bot ask for a `Tile` at a `Location` that does not exist, this method will return a `nullptr`.

### `movePieceTo(const Piece &aPiece, const Location &aLocation)` 
Call this method when checker-bot have completed its analysis and are ready to tell the game the destination (`Location`) where it want to move on of its `Piece`'s.  As we mention else where, if checker-bot are doing a multi-jump, it may call this method more than once. Calling this method at any time when it _aren't_ performing a multi-jump will disqualify it from the game.

### Running the game 

The `Game` class we provided to checker-bot is responsible for running the game. Each player gets a turn to analyze the board, and make a move decision. Between each move, current state of the board is displayed for reference. As sample is shown below.  Notice that board contains pieces marked "b" and "g". A piece is capitalized ("B","G") to indicate that piece has been "kinged" and can move more freely.

```
  Step 67
   |---|---|---|---|---|---|---|---|
 0 | . | . | . | . | . | . | . | . |
   |---|---|---|---|---|---|---|---|
 1 | . | . | . | . | . | . | . | . |
   |---|---|---|---|---|---|---|---|
 2 | . | . | . | . | . | B | . | . |
   |---|---|---|---|---|---|---|---|
 3 | . | . | . | . | . | . | g | . |
   |---|---|---|---|---|---|---|---|
 4 | . | . | . | . | . | . | . | . |
   |---|---|---|---|---|---|---|---|
 5 | . | . | . | . | . | . | . | . |
   |---|---|---|---|---|---|---|---|
 6 | . | . | . | . | . | g | . | g |
   |---|---|---|---|---|---|---|---|
 7 | G | . | . | . | . | . | G | . |
   |---|---|---|---|---|---|---|---|
     0   1   2   3   4   5   6   7
```
