# Twixt CLI Game 🎮

A terminal-based implementation of the classic strategy board game Twixt, built in C with colored output and intelligent game mechanics.

## Overview

Twixt is a two-player connection game played on a 24x24 board where players compete to create a connected path between opposite sides of the board. This CLI implementation features automatic link creation, collision detection, and pathfinding algorithms to determine win conditions.

## Game Rules

### Objective
- **Red Player**: Connect the TOP border to the BOTTOM border
- **Black Player**: Connect the LEFT border to the RIGHT border

### Gameplay
1. Players alternate placing pins on the board
2. Pins automatically link to friendly pins within a knight's move (like chess)
3. Links cannot cross each other
4. **Placement restrictions**:
   - Red cannot place pins on left/right borders
   - Black cannot place pins on top/bottom borders
   - Corner cells are off-limits for both players

### Winning
The first player to create an unbroken chain of links connecting their two target borders wins!

## Features

### Core Mechanics
- **24x24 game board** with proper border restrictions
- **Automatic link creation** using knight's move pattern (8 possible connections)
- **Link intersection detection** prevents illegal moves
- **DFS pathfinding algorithm** for win condition checking
- **Turn-based gameplay** with clear player indicators

### Technical Highlights
- **Geometric algorithms**: Line segment intersection detection
- **Graph algorithms**: Depth-First Search for path validation
- **Colored terminal output**: Red and blue pins with visual borders
- **Command-line interface**: Simple, intuitive commands
- **Game state management**: Tracks all pins, links, and turn state

## Project Structure
```
Twixt-Game/
├── game.c              # Core game logic and algorithms
├── game.h              # Game structures and function declarations
├── main.c              # CLI interface and main game loop
├── Makefile            # Build automation
├── .gitignore
└── README.md
```

## Compilation & Usage

### Prerequisites
- GCC compiler
- Terminal with UTF-8 support (for colored output)
- Windows OS (uses `windows.h` for console encoding)

### Compile
```bash
# Using Makefile (recommended):
make

# Or manually:
gcc game.c main.c -o twixt
```

### Run
```bash
./twixt          # Linux/Mac
twixt.exe        # Windows
```

## Commands

Once in the game, use these commands:
```
place x y   - Place a pin at coordinates (x, y)
show        - Display the current board state
links       - Show all active links
help        - Display command list and rules
quit        - Exit the game
```

## Data Structures

### Game State
```c
typedef struct {
    int grid[BOARD_SIZE * BOARD_SIZE];  // Board state
    bool isRedTurn;                      // Current player
    Link links[MAX_LINKS];               // All active links
    int linkCount;                       // Number of links
} Game;
```

### Link Representation
```c
typedef struct {
    int x1, y1;  // First pin coordinates
    int x2, y2;  // Second pin coordinates
    int color;   // RED or BLACK
} Link;
```

## Algorithms Implemented

### 1. Link Intersection Detection
Uses cross product calculations to determine if two line segments intersect:
- Prevents illegal link crossings
- Ensures game rule compliance
- O(1) time complexity per check

### 2. Depth-First Search (DFS)
Validates win conditions by finding paths from one border to the opposite:
- Traverses the link graph
- Checks connectivity between pins
- Determines game-ending conditions

### 3. Knight's Move Pattern
Automatically creates links using chess knight movement:
- 8 possible directions: (±2, ±1) and (±1, ±2)
- Only links same-colored pins
- Respects intersection rules

## Key Learnings

This project involved:
- **Graph Theory**: Implementing graph traversal and pathfinding algorithms
- **Computational Geometry**: Line intersection detection using cross products
- **Game Logic**: Managing complex rule sets and win conditions
- **CLI Design**: Creating an intuitive command-line interface
- **Data Structures**: Efficient storage and manipulation of game state

## Challenges Overcome

1. **Link Intersection Logic**: Implementing accurate geometric calculations for line segment intersection
2. **Win Detection**: Efficiently checking connectivity across potentially hundreds of links
3. **Knight's Move Automation**: Automatically creating valid links without crossing violations
4. **Terminal Graphics**: Using ANSI escape codes for colored output on Windows

## Future Enhancements

- AI opponent with minimax algorithm
- Move undo/redo functionality
- Save/load game state
- Network multiplayer support
- Cross-platform terminal handling (Linux/Mac support)
- Move history and replay

## Technologies Used

- **Language**: C
- **Concepts**: Graph Algorithms (DFS), Computational Geometry, Game Theory
- **Libraries**: Standard C libraries, Windows Console API

## Course Context

Developed as a semester project for **Computer Programming** course at IIIT Hyderabad, demonstrating:
- Advanced data structures (graphs, arrays)
- Algorithm implementation (DFS, geometric algorithms)
- Game state management
- User interface design
- Complex rule enforcement

---

**Author**: B.Tech ECE Student @ IIIT Hyderabad  
**Course**: Computer Programming (Semester 1, 2024)  
**Institution**: International Institute of Information Technology, Hyderabad