// script.js
document.addEventListener('DOMContentLoaded', () => {
    // DOM Elements
    const board = document.getElementById('board');
    const cells = document.querySelectorAll('.cell');
    const status = document.getElementById('status');
    const resetBtn = document.getElementById('resetBtn');
    const twoPlayerBtn = document.getElementById('twoPlayerBtn');
    const singlePlayerBtn = document.getElementById('singlePlayerBtn');
    const difficultySelector = document.getElementById('difficultySelector');
    const difficulty = document.getElementById('difficulty');
    const xWins = document.getElementById('xWins');
    const oWins = document.getElementById('oWins');
    const draws = document.getElementById('draws');
    const playerX = document.querySelector('.player-x');
    const playerO = document.querySelector('.player-o');

    // Game State
    let currentPlayer = 'X';
    let gameMode = 'twoPlayers'; // 'twoPlayers' or 'singlePlayer'
    let gameActive = true;
    let gameState = ['', '', '', '', '', '', '', '', ''];
    let scores = {
        xWins: 0,
        oWins: 0,
        draws: 0
    };

    // Winning combinations
    const winningConditions = [
        [0, 1, 2], [3, 4, 5], [6, 7, 8], // Rows
        [0, 3, 6], [1, 4, 7], [2, 5, 8], // Columns
        [0, 4, 8], [2, 4, 6]             // Diagonals
    ];

    // Initialize game
    function initGame() {
        cells.forEach(cell => {
            cell.textContent = '';
            cell.classList.remove('x', 'o', 'win');
            cell.addEventListener('click', handleCellClick);
        });
        
        gameState = ['', '', '', '', '', '', '', '', ''];
        gameActive = true;
        currentPlayer = 'X';
        
        updateStatus();
        updatePlayerHighlight();
    }

    // Handle cell click
    function handleCellClick(e) {
        const clickedCell = e.target;
        const clickedCellIndex = parseInt(clickedCell.getAttribute('data-index'));
        
        // Check if cell is already played or game is not active
        if (gameState[clickedCellIndex] !== '' || !gameActive) {
            return;
        }
        
        // Update game state
        gameState[clickedCellIndex] = currentPlayer;
        clickedCell.textContent = currentPlayer;
        clickedCell.classList.add(currentPlayer.toLowerCase());
        
        // Check for win or draw
        if (checkWin()) {
            highlightWinningCells();
            updateStatus(`${currentPlayer === 'X' ? 'Player 1' : 'Player 2'} wins!`);
            gameActive = false;
            
            // Update scores
            if (currentPlayer === 'X') {
                scores.xWins++;
                xWins.textContent = scores.xWins;
            } else {
                scores.oWins++;
                oWins.textContent = scores.oWins;
            }
            return;
        }
        
        if (checkDraw()) {
            updateStatus("It's a draw!");
            gameActive = false;
            scores.draws++;
            draws.textContent = scores.draws;
            return;
        }
        
        // Switch player
        currentPlayer = currentPlayer === 'X' ? 'O' : 'X';
        updateStatus();
        updatePlayerHighlight();
        
        // If single player mode and it's bot's turn
        if (gameMode === 'singlePlayer' && currentPlayer === 'O' && gameActive) {
            setTimeout(makeBotMove, 500);
        }
    }

    // Check for win
    function checkWin() {
        for (let i = 0; i < winningConditions.length; i++) {
            const [a, b, c] = winningConditions[i];
            if (gameState[a] && gameState[a] === gameState[b] && gameState[a] === gameState[c]) {
                return winningConditions[i];
            }
        }
        return false;
    }

    // Check for draw
    function checkDraw() {
        return !gameState.includes('');
    }

    // Highlight winning cells
    function highlightWinningCells() {
        const winningCombo = checkWin();
        if (winningCombo) {
            winningCombo.forEach(index => {
                cells[index].classList.add('win');
            });
        }
    }

    // Update status message
    function updateStatus(message) {
        if (message) {
            status.textContent = message;
            return;
        }
        
        if (!gameActive) {
            return;
        }
        
        if (gameMode === 'twoPlayers') {
            status.textContent = `Player ${currentPlayer}'s turn`;
        } else {
            if (currentPlayer === 'X') {
                status.textContent = "Your turn (X)";
            } else {
                status.textContent = "Bot is thinking...";
            }
        }
    }

    // Update player highlight
    function updatePlayerHighlight() {
        playerX.classList.toggle('active', currentPlayer === 'X');
        playerO.classList.toggle('active', currentPlayer === 'O');
    }

    // Bot move logic
    function makeBotMove() {
        if (!gameActive || currentPlayer !== 'O') return;
        
        let botMove;
        const currentDifficulty = difficulty.value;
        
        // Bot difficulty logic
        if (currentDifficulty === 'easy') {
            botMove = getEasyMove();
        } else if (currentDifficulty === 'medium') {
            botMove = Math.random() > 0.5 ? getHardMove() : getEasyMove();
        } else { // hard
            botMove = getHardMove();
        }
        
        // Make the move
        gameState[botMove] = 'O';
        cells[botMove].textContent = 'O';
        cells[botMove].classList.add('o');
        
        // Check for win or draw
        const winCombo = checkWin();
        if (winCombo) {
            highlightWinningCells();
            updateStatus("Bot wins!");
            gameActive = false;
            scores.oWins++;
            oWins.textContent = scores.oWins;
            return;
        }
        
        if (checkDraw()) {
            updateStatus("It's a draw!");
            gameActive = false;
            scores.draws++;
            draws.textContent = scores.draws;
            return;
        }
        
        // Switch back to player
        currentPlayer = 'X';
        updateStatus();
        updatePlayerHighlight();
    }

    // Easy bot: random move
    function getEasyMove() {
        const availableMoves = gameState
            .map((val, index) => val === '' ? index : null)
            .filter(val => val !== null);
        
        return availableMoves[Math.floor(Math.random() * availableMoves.length)];
    }

    // Hard bot: minimax algorithm
    function getHardMove() {
        let bestScore = -Infinity;
        let bestMove;
        
        for (let i = 0; i < 9; i++) {
            // Check if spot is available
            if (gameState[i] === '') {
                gameState[i] = 'O';
                let score = minimax(gameState, 0, false);
                gameState[i] = '';
                
                if (score > bestScore) {
                    bestScore = score;
                    bestMove = i;
                }
            }
        }
        
        return bestMove;
    }

    // Minimax algorithm
    function minimax(board, depth, isMaximizing) {
        // Check for terminal states
        const winner = checkWinner();
        if (winner === 'O') return 10 - depth;
        if (winner === 'X') return depth - 10;
        if (checkDraw()) return 0;
        
        if (isMaximizing) {
            let bestScore = -Infinity;
            for (let i = 0; i < 9; i++) {
                if (board[i] === '') {
                    board[i] = 'O';
                    let score = minimax(board, depth + 1, false);
                    board[i] = '';
                    bestScore = Math.max(score, bestScore);
                }
            }
            return bestScore;
        } else {
            let bestScore = Infinity;
            for (let i = 0; i < 9; i++) {
                if (board[i] === '') {
                    board[i] = 'X';
                    let score = minimax(board, depth + 1, true);
                    board[i] = '';
                    bestScore = Math.min(score, bestScore);
                }
            }
            return bestScore;
        }
    }

    // Helper function to check winner in minimax
    function checkWinner() {
        for (let i = 0; i < winningConditions.length; i++) {
            const [a, b, c] = winningConditions[i];
            if (gameState[a] && gameState[a] === gameState[b] && gameState[a] === gameState[c]) {
                return gameState[a];
            }
        }
        return null;
    }

    // Reset game
    function resetGame() {
        initGame();
    }

    // Switch game mode
    function switchMode(mode) {
        gameMode = mode;
        resetGame();
        
        if (mode === 'singlePlayer') {
            singlePlayerBtn.classList.add('active');
            twoPlayerBtn.classList.remove('active');
            difficultySelector.classList.remove('hidden');
            playerO.querySelector('.name').textContent = 'Bot';
        } else {
            twoPlayerBtn.classList.add('active');
            singlePlayerBtn.classList.remove('active');
            difficultySelector.classList.add('hidden');
            playerO.querySelector('.name').textContent = 'Player 2';
        }
    }

    // Event Listeners
    cells.forEach(cell => {
        cell.addEventListener('click', handleCellClick);
    });
    
    resetBtn.addEventListener('click', resetGame);
    
    twoPlayerBtn.addEventListener('click', () => switchMode('twoPlayers'));
    singlePlayerBtn.addEventListener('click', () => switchMode('singlePlayer'));
    
    // Initialize game
    initGame();
});
