# Hangman-Game-CSE115

A classic **Hangman word-guessing game** developed entirely in **C**. The project features a modular multi-file architecture, robust input handling, a curated word bank, and a polished terminal experience with custom ASCII art. The implementation emphasizes clean code organization, readability, and collaborative software design principles.

---

## 👥 Group Information

| **SERIAL-NUMBER**   | **FULL-NAME**               | **STUDENT-ID** | **GITHUB-PROFILE**                                          |
|:------------------: |---------------------------- |:--------------:|-------------------------------------------------------------|
| 01                  | **Raiana Tabassum Roza**    | `2625101642`   | [@raianatroza262-afk](https://github.com/raianatroza262-afk)|
| 02                  | **Israt Jahan Jerin**       | `2622081042`   | [@isratjerin791](https://github.com/isratjerin791)          |
| 03                  | **Tanzeem Hasan**           | `2622490642`   | [@tanzeemhasan262](https://github.com/tanzeemhasan262)      |
| 04                  | **Ayman-bin-salim**         | `2625352042`   | [@Aymanbinsalim](https://github.com/Aymanbinsalim)          |

**Course:** CSE115 | **Section:** 04 | **Group:** 03 | **Faculty:** MSRB



---

## 🚀 Key Features

- **Classic Gameplay:** Guess letters one at a time to uncover a hidden word before running out of attempts.
- **Modular Architecture:** Cleanly separated into `main.c`, `hangman.c`, and `hangman.h` for maintainable, team-friendly development.
- **Dynamic Word Bank:** Words are loaded from an external `data/words.txt` file, making the word list easy to expand without touching game logic.
- **Randomized Word Selection:** A different word is chosen each playthrough for replayability.
- **Limited Guess System:** Tracks incorrect guesses and ends the game once the guess limit is reached.
- **Live Progress Display:** Shows the partially revealed word and previously guessed letters after every turn.
- **Custom ASCII Art:** Branded ANSI Shadow–style title banner styled to match the game's visual identity.
- **UTF-8 Console Support:** Uses `SetConsoleOutputCP(CP_UTF8)` for correct character rendering on Windows terminals.
- **Input Validation:** Handles invalid, repeated, and non-alphabetic input gracefully without crashing.
- **Win/Loss Detection:** Clear end-game messaging for both successful guesses and game-over states.
- **Replay Option:** Lets players start a new round without restarting the program.
- **Cross-Environment Build:** Compiles cleanly with GCC on Windows via a simple two-file build command.
- **Hint availability:** In case of brainstorming, there is possible hints to take by the user.

---

## 🛠️ Tech Stack

| Component         | Details                       |
|-------------------|-------------------------------|
| Language          | C                             |
| Compiler          | GCC                           |
| Environment       | Windows (VS Code + PowerShell)|
| Version Control   | Git & GitHub                  |

---

## 📁 Project Structure

```
Hangman_Game_inC/
├── data/
│   └── words.txt           # Word bank used by the game
├── main.c                  # Program entry point
├── hangman.c               # Core game logic
├── hangman.h               # Function declarations & shared definitions
├── requirements.txt        # Build/setup notes
└── README.md               # Project documentation
```

---

## ▶️ How to Build & Run

From inside the project folder:

```bash
gcc main.c hangman.c -o hangman
./hangman
```




## Author

```
Raiana Tabassum Roza
Israt Jahan Jerin
Tanzeem Hasan
Ayman-bin-salim
```
