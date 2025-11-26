# TIC TAC TOE

**Project Title:** TIC TAC TOE

**Student:** Krishna Grover
**Roll No:** 590023545
**Course:** B.Tech CSE, UPES
**Instructor:** Dr. Tanu Singh

## Project Summary
A console-based Tic-Tac-Toe game written in C. Supports two difficulty levels: Human (heuristic) and God (Minimax unbeatable). Tracks wins, losses and draws across multiple rounds.

## Features
- Two difficulty modes: Human (standard) and God (Minimax unbeatable)
- Clear console board display with score tracking
- Robust input validation and graceful handling of invalid input
- Modular code available (single-file included plus modular sources)
- `Makefile` for easy compilation
- `docs/ProjectReport.pdf` included for submission

## How to build
### Single-file build
```
gcc tictactoe.c -o tictactoe
./tictactoe
```

### Modular build
```
# from project root
gcc -Iinclude -std=c11 -Wall src/*.c -o main
./main
```

## Sample Input / Output
Sample interactive sequence (user inputs shown after prompts):
```
Select Difficulty Level:
1. Human (Standard)
2. God (Impossible to win)
Enter your choice: 2

Player X turn - enter row and column (1-3): 1 1
... (game continues)
```

## Repository Layout
```
/ (root)
|-- src/
|-- include/
|-- docs/
|-- assets/
|-- tictactoe.c
|-- README.md
|-- Makefile
```

## Notes
Convert `docs/ProjectReport.md` to PDF (already included as ProjectReport.pdf). Upload repository to GitHub and submit the single `github link.txt` to LMS as per guidelines.
