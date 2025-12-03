# Twixt CLI (C)
### Name - Abhinav
### Roll No - 2025102004
Simple command-line implementation of Twixt game.

## Build
Compile with a C compiler:

    gcc -o twixt main.c game.c

## Run
On Windows console:

    ./twixt

## Usage (commands)
- place x y — place a pin at coordinates (x,y)
- show      — display board
- links     — show all current links
- help      — print help
- quit      — exit

Note:
- Pins automatically link to nearby same-color pins (knight's move)
- Links cannot cross each other
- Red connects top-to-bottom (cannot place on left/right borders)
- Black connects left-to-right (cannot place on top/bottom borders)
- Corners are invalid placements