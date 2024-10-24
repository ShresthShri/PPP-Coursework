#include <iostream>
#include <cstdio>
#include "sudoku.h"

using namespace std;

int main() {

  char board[9][9];

  /* This section illustrates the use of the pre-supplied helper functions. */
  cout << "============= Pre-supplied functions =============\n\n";

  cout << "Calling load_board():\n";
  load_board("easy.dat", board);

  cout << '\n';
	cout << "Displaying Sudoku board with display_board():\n";
  display_board(board);
  cout << "Done!\n\n";

  cout << "=================== Question 1 ===================\n\n";

  load_board("easy.dat", board);
  cout << "Board is ";
  if (!is_complete(board)) {
    cout << "NOT ";
  }
  cout << "complete.\n\n";

  load_board("easy-solution.dat", board);
  cout << "Board is ";
  if (!is_complete(board)) {
    cout << "NOT ";
  }
  cout << "complete.\n\n";

  cout << "=================== Question 2 ===================\n\n";

  load_board("easy.dat", board);

  // Should be OK
  cout << "Putting '1' into I8 is ";
  if (make_move("I8", '1', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:\n";
  display_board(board);

  // write more tests

  cout << "=================== Question 3 ===================\n\n";

  load_board("easy.dat", board);
  if (save_board("easy-copy.dat", board)) {
    cout << "Save board to 'easy-copy.dat' successful.\n";
  } else {
    cout << "Save board failed.\n";
  }
 cout << '\n';

 cout << "=================== Question 4 ===================\n\n";
  
  load_board("easy.dat", board);
  if (solve_board(board)) {
    cout << "The 'easy' board has a solution:\n";
    display_board(board);
  } else {
    cout << "A solution cannot be found.\n";
  }
  cout << '\n';

 load_board("medium.dat", board);
  if (solve_board(board)) {
    cout << "The 'medium' board has a solution:\n";
    display_board(board);
  } else {
    cout << "A solution cannot be found.\n";
  }
  cout << '\n';



  cout << "=================== Question 5 ===================\n\n";

  // Create an array which can run through all 3 files in one go
  const char* files[] = {"mystery1.dat", "mystery2.dat", "mystery3.dat"};

  // Loop through the array of files  
  for (int i = 0; i < 3; i++) {

      // Load the files on the board
      load_board(files[i], board);

      // Reset the counter for each new board
      int rec_counter = 0;  

      // Set the boolean to false
      bool solved = false;

      // Solve the board and calculate the time
      int time_taken = calc_time(board, rec_counter, solved);  

      // Display the results
      if (solved) {

        cout << "The " << files[i] << " board has a solution:\n";

        display_board(board);

        cout << "The total number of recursions: " << rec_counter << endl;

        cout << "The time taken to solve this problem: " << time_taken << " milliseconds" << endl;

      } else {

        cout << "The " << files[i] << " board is unsolvable.\n";
      }

      cout << '\n';
  }


  return 0;
}

