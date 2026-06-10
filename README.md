# Bejeweled Blitz SFML

Bejeweled Blitz SFML is a C++ match-3 puzzle game inspired by Bejeweled Blitz. The game is built using the SFML graphics library and features an 8x8 gem grid, mouse and keyboard controls, score tracking, timer-based gameplay, match detection, gem removal, falling mechanics, and automatic board refill.

## Overview

The objective of the game is to swap adjacent gems to create matches of three or more gems of the same type. When a match is created, the matched gems are removed, the remaining gems fall down, and new gems are generated at the top of the board.

The game runs with a 60-second timer. The player tries to score as many points as possible before the timer ends.

## Features

* 8x8 match-3 game board
* Six different gem types
* Gems drawn using SFML shapes and colors
* Mouse-based gem selection and swapping
* Keyboard-based cursor movement and selection
* Adjacent-cell swap validation
* Invalid swaps are automatically reversed
* Horizontal and vertical match detection
* Match removal system
* Falling/collapse logic after matches
* Automatic gem refill
* Score tracking
* 60-second game timer
* Game-over state when time runs out
* Dynamic window title showing score and time

## Tech Stack

* C++
* SFML Graphics Library

## Controls

### Mouse Controls

```text
Left Click first gem  = Select gem
Left Click adjacent gem = Swap selected gem
```

### Keyboard Controls

```text
Arrow Keys = Move cursor
Enter / Return = Select gem or swap with selected gem
```

## Gameplay Rules

* Only adjacent gems can be swapped.
* A swap is accepted only if it creates a match.
* If the swap does not create a match, the gems are swapped back.
* A match requires three or more same-type gems in a row or column.
* Matched gems are removed from the board.
* Gems above fall down to fill empty spaces.
* New gems are generated at the top.
* The player scores points for removed gems.
* The game ends after 60 seconds.

## Scoring

Each removed gem increases the score.

```text
Score = Number of removed gems × 10
```

Cascading matches are also counted because the board continues checking for new matches after gems fall and refill.

## Project Structure

```text
Bejeweled-Blitz-SFML/
  BejeweledBlitz.cpp
  README.md
  .gitignore
```

## How to Run

### 1. Install SFML

Make sure SFML is installed and configured on your system.

SFML official website:

```text
https://www.sfml-dev.org/
```

### 2. Compile the Code

On Linux/macOS, you can compile using:

```bash
g++ BejeweledBlitz.cpp -o BejeweledBlitz -lsfml-graphics -lsfml-window -lsfml-system
```

### 3. Run the Game

```bash
./BejeweledBlitz
```

## Running on Windows with Visual Studio

1. Install SFML for Visual Studio.
2. Create a new C++ project.
3. Add `BejeweledBlitz.cpp` to the project.
4. Configure SFML include directories and library directories.
5. Link the required SFML libraries:

   * `sfml-graphics`
   * `sfml-window`
   * `sfml-system`
6. Build and run the project.

## Important Files Not to Upload

The following files and folders should not be uploaded to GitHub:

```text
.vs/
Debug/
Release/
x64/
*.exe
*.obj
*.pdb
*.ilk
*.user
*.suo
```

These are build files, executable files, and local Visual Studio settings.

## Suggested .gitignore

```gitignore
# Visual Studio
.vs/
Debug/
Release/
x64/
*.user
*.suo
*.VC.db
*.VC.VC.opendb

# Build files
*.exe
*.obj
*.pdb
*.ilk
*.log

# OS files
.DS_Store
Thumbs.db
```

## Code Highlights

The project includes:

* `initializeBoard()` to create the starting board without initial matches
* `markMatches()` to detect horizontal and vertical matches
* `removeMarkedGems()` to remove matched gems
* `collapseBoard()` to make gems fall and refill empty cells
* `swapCells()` to swap adjacent gems
* `drawGem()` to render different gem shapes using SFML
* Timer logic using `sf::Clock`
* Score tracking based on removed gems

## Learning Outcomes

This project demonstrates:

* C++ game development
* SFML rendering
* 2D grid-based game logic
* Event handling
* Mouse input
* Keyboard input
* Match-3 algorithm design
* Collision/adjacency checks
* Game loop structure
* Score and timer management

## Future Improvements

* Add animations for swapping and falling gems
* Add sound effects
* Add background music
* Add special gems for 4-match and 5-match combinations
* Add explosion effects
* Add a start menu
* Add high-score saving
* Add levels or difficulty modes
* Add better game-over screen
* Add image-based gem textures instead of shape-based gems

## Author

Rida Fatima Tanvir
Ayesha Amer

## Note

This project was developed as a C++ SFML match-3 puzzle game to demonstrate game programming concepts, event handling, grid logic, match detection, and graphical rendering.
