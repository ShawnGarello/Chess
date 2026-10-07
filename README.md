# 🧩 Chess (C++ Project)

A two-player, console-based chess game written in C++. I first built it for my C++ course to practice:

- Class design and inheritance (`AbsPiece` → `Pawn`, `Rook`, `Knight`, `Bishop`, `Queen`, `King`)
- Polymorphism with pure virtual functions
- Dynamic memory management
- Encapsulation and a modular file structure
- Game logic
- STL containers
- Algorithms and custom data structures

---

## 📄 Features

- Full 8×8 board drawn in the terminal with file (a–h) and rank (1–8) labels
- A separate class for each piece, each with its own move rules
- Move validation, including blocked paths and captures
- Check detection that blocks any move leaving your own king in check
- Turn tracking and game records saved to `GameRecord.txt` and `GameRecord.bin`
- Captured pieces and a material score for each player
- After the game ends:
  - Two-column move history (Player 1 / Player 2)
  - Captured pieces sorted by value
  - A graph of available moves for each piece
  - An option to rewind and replay the game move by move

---

## 🛠️ Build & Run

You need a C++ compiler that supports C++11 or newer (for example g++, clang++, or MSVC).

```bash
git clone https://github.com/ShawnGarello/Chess.git
cd Chess
g++ -std=c++17 *.cpp -o chess
./chess
```

On Windows, run `chess.exe` instead of `./chess`.

---

## 🎮 How To Play

- Player 1 moves first, then players take turns.
- Enter the square of the piece you want to move, then where it goes, separated by a space:

  ```text
  e2 e4
  ```

- Squares use letters `a`–`h` and numbers `1`–`8`. Invalid input or illegal moves are rejected and you're asked again.
- If your king is in check, the game warns you and only accepts moves that get you out of check.
- Type `QIT GME` to end the game. You'll then see the move history and stats, and you can choose to rewind and review the game (`y` / `n`).

---

## 🧠 Data Structures & Algorithms

| Concept | Where it's used |
| --- | --- |
| Stacks | Rewinding the game move by move |
| Queues and lists | Separate move histories for each player |
| Maps and sets | Tracking captured pieces and score |
| Arrays of pairs + recursive quicksort | Sorting captured pieces by value |
| AVL tree (`AVL.h`, `Node.h`) | Storing turns in a balanced tree |
| Hash function + `unordered_map` | Looking up the turn a specific move happened on (DJB2 hash) |
| Graph (adjacency list) | Showing the available moves for each piece after the game |
| Recursion | Printing the game history |
| Templates and operator overloading | Displaying players and game records |
| Text and binary file I/O | Saving the game record |

---

## 📁 Project Structure

```text
main.cpp               entry point: sets up the board and starts the game
Board.h / .cpp         8×8 board, moving pieces, attack and check detection
AbsPiece.h / .cpp      abstract base class for all pieces
Pawn, Rook, Knight,
Bishop, Queen, King    derived piece classes with their own move rules
Empty.h / .cpp         placeholder for empty squares
GameRec.h / .cpp       game loop, input, history, scoring, rewind, and file output
AVL.h, Node.h          AVL tree used to store turns
```

---

## 💡 Notes

This project focuses on learning OOP principles and data structures, not on implementing every chess rule. Castling, en passant, pawn promotion, and automatic checkmate detection are not included, so the game ends when a player types `QIT GME`.
