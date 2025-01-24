
# **Connect Four AI**

## **Overview**
The **Connect Four AI** is a C implementation of the classic Connect Four game, where players challenge an intelligent AI opponent. This project showcases advanced algorithms and structured programming to deliver an engaging and competitive gameplay experience. The AI uses a decision tree with a depth of eight levels to evaluate potential game states and choose the best possible move.

Designed for console execution, this game combines simplicity with sophistication, offering a platform for both fun and educational exploration of AI and algorithmic strategies.

---

## **Features**
- **Player vs AI Gameplay**: Test your skills against a strategically designed AI.
- **Intelligent Move Evaluation**: The AI leverages a decision tree to evaluate moves and select the most advantageous option.
- **Dynamic Board Management**: A fully functional Connect Four board is displayed in the console after every move.
- **Depth-Based Strategy**: The AI uses an 8-level depth tree to foresee potential outcomes and optimize its moves.
- **Lightweight Implementation**: Built entirely in C, the game is efficient and runs smoothly in any compatible console.

---

## **Technical Details**
1. **Language**:
   - Written in **C**, focusing on modularity and efficiency.
2. **Algorithm**:
   - Implements a recursive tree traversal algorithm to simulate decision-making.
   - AI evaluates moves based on dynamic scoring of potential game states.
3. **AI Strategy**:
   - Uses a tree with **8 levels of depth** to analyze potential moves.
   - Assigns scores to each move, considering offensive and defensive strategies.
   - Incorporates a penalty system for invalid moves to improve decision accuracy.
4. **Console Interaction**:
   - Input prompts guide the player to make moves.
   - The board is updated and displayed after each turn.

---

## **How to Play**
1. Clone the repository or download the project files.
2. Compile the game using a C compiler:
   ```bash
   gcc -o connect_four Connect_Four_AI.c
   ```
3. Run the compiled program:
   ```bash
   ./connect_four
   ```
4. Follow the on-screen instructions:
   - Enter the column number to place your piece.
   - Watch the AI respond with its optimal move.
5. The game ends when a player achieves four consecutive pieces (horizontally, vertically, or diagonally) or the board is full.

---

## **Folder Structure**
```
Connect Four AI/
├── Connect Four AI.c   # Source code for the game and AI
├── README.md           # Project documentation
```

---

## **Future Improvements**
- Implement an AI optimization algorithm, such as **alpha-beta pruning**, to enhance decision-making speed.
- Add a graphical user interface (GUI) for better user experience.
- Increase tree depth dynamically based on available system resources.

---

## **License**
This project is released under the **MIT License**. Feel free to use, modify, and distribute the code.

---

## **Contact**
For questions, suggestions, or contributions, please feel free to reach out via GitHub or email.
