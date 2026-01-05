# Wordle Mini Version (C)

A simplified, terminal-based Wordle clone written in C.  
This project was built mainly for fun while Wordle was a personal hyperfixation,
and as practice for string handling, input validation, and basic game logic in C.

The game is playable but intentionally minimal and still a work in progress.

---

## How It Works
- The target word is passed as a command-line argument
- The player has up to 6 guesses
- Each guess is checked letter-by-letter:
  - Correct letter in the correct position is shown
  - Correct letter in the wrong position is marked with `*`
- Input is case-insensitive and normalized internally
- Typing `QUIT` exits the game early

---

## What I learned
- Validating command-line arguments in C
- Managing dynamic memory with malloc, realloc, and free
- Handling user input safely in a terminal program
- Implementing game logic using strings and arrays
- Debugging logic and memory issues in a non-trivial C project

---

## Future Improvements
- Fix memory leaks and improve memory safety
- Implement proper Wordle-style letter counting
- Improve terminal output (colors, clearer formatting)

---

## Running
```bash
gcc wordle.c -o wordle
./wordle apple

(the answer of the game should be placed in the command line argument i.e. apple)

