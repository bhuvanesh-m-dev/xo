# Tic-Tac-Toe (X and O)  

A classic console-based Tic-Tac-Toe game implemented in C where two players can compete against each other. The game features player turn tracking, win detection, and a clean terminal interface.

**Play online in real-time:**  
👉 [bhuvanesh-m-dev.github.io/xo](https://bhuvanesh-m-dev.github.io/xo)

## Prerequisites

To compile and run the C program locally, you'll need:

1. **C Compiler** (GCC recommended):
   - Linux: Install via `sudo apt install build-essential`
   - macOS: Install Xcode Command Line Tools (`xcode-select --install`)
   - Windows: Install [MinGW-w64](https://www.mingw-w64.org/) or [TDM-GCC](https://jmeubank.github.io/tdm-gcc/)

2. **Terminal Access**:
   - Linux/macOS: Built-in Terminal
   - Windows: Command Prompt, PowerShell, or Git Bash

## How to Run the Game

### 1. Save the Source Code
Create a file named `xo.c` and paste [the complete source code](https://bhuvanesh-m-dev.github.io/xo/xo.c) into it.

### 2. Compile the Program
Open your terminal and navigate to the directory containing `xo.c`, then compile:

```bash
gcc xo.c -o xo
```

### 3. Run the Game
Execute the compiled program:

- **Linux/macOS**:
  ```bash
  ./xo
  ```

- **Windows**:
  ```cmd
  xo.exe
  ```

### 4. How to Play
1. Players take turns entering coordinates (e.g., `1 1` for center)
2. Player 1 = `X`, Player 2 = `O`
3. First to get 3 in a row wins!
4. Enter coordinates as `row column` (0-2 for both)

```
Example move: 
Enter move for Player X (row col): 0 2
```

## Game Features
- ✅ Real-time turn indicator
- ✅ Win/draw detection
- ✅ Input validation
- ✅ Clear terminal-based UI
- ✅ Player score tracking

## Sample Gameplay
```
Player X's turn!
┌───┬───┬───┐
│   │   │ X │
├───┼───┼───┤
│   │   │   │
├───┼───┼───┤
│   │   │   │
└───┴───┴───┘
Enter move for Player X (row col): 1 1
```

## Troubleshooting
| Issue | Solution |
|-------|----------|
| `gcc: command not found` | Install C compiler (see Prerequisites) |
| Permission denied (Linux/macOS) | Run `chmod +x xo` after compilation |
| Invalid move errors | Ensure coordinates are between 0-2 and cell is empty |
| Screen flickering | Disable terminal cursor blinking in your terminal settings |

## Contributing
Pull requests welcome! See [the GitHub repository](https://github.com/bhuvanesh-m-dev/xo) for source code.

---

**Developed with ❤️ using C**  
*No external libraries required - pure ANSI C*  
[Play online](https://bhuvanesh-m-dev.github.io/xo) | [View Source](https://github.com/bhuvanesh-m-dev/xo)
