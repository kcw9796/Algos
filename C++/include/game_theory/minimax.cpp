#define XWIN 1
#define OWIN -1
#define TIE 0

int minmaxvalue(int *, int , int , int );
int max_value(int *, int , int );
int min_value(int *, int , int );

// main function that calls minimax
// takes in a board that may be partially played and which players turn it is
// predicts who would win the game or if there will be a tie assuming all players make the correct moves
// it returns X(1) if X wins, O(2) if O wins or NONE(0) if tie or game is not finished
// uses alpha beta pruning to increase efficiency and decrease the number of iterations it takes
int tictactoe(int *board, int turn)
{ 
	// calls recursive minimax function and 
	// sets alpha and beta to be -10 and 10 (which represent negative and positive infinity)
	int result = minmaxvalue(board,turn,-10,10);

	// return the winner
	if(result==XWIN)
		{result=X;}
	else if(result==OWIN)
		{result=O;}
	else
		{result=NONE;}
	return result;	
}

// recusrive minimax value function that calls minvalue and maxvalue
int minmaxvalue(int *board, int turn, int a, int b)
{
	// check if there is currently a winner (base case)
	int result = game_status(board);

	// if there is a winner then return who won
	if(result==X)
		{return XWIN;}
	else if(result==O)
		{return OWIN;}


	bool complete = true;
	// loop through board spaces to find next move
	for(int i=0;i<9;i++)
	{
		// if there is an empty space then board is not complete
		// and a move can be made
		if(board[i]==NONE)
		{
			complete = false;
		}
	}

	// if no board spaces left and no winner was returned it must be a tie
	if(complete == true)
	{
		return TIE;
	}

	// if it is X's turn then call maxvalue function
	// in this case we allow X to represent max because XWIN = 1 and OWIN = -1
	if(turn == X)
	{
		return max_valueab(board,a,b);
	}
	// if it is O's turn then call maxvalue function
	// in this case we allow O to represent min because OWIN = -1 and XWIN = 1
	if(turn == O)
	{
		return min_valueab(board,a,b);
	}

	return TIE;
}

// Max value function represents X's turn
int max_value(int *board, int a, int b)
{
	int v = -10;
	int curv;

	// check all open board spaces
	for(int i=0;i<9;i++)
	{
		if(board[i]==NONE)
		{
			board[i] = X;
			curv = minmaxvalue(board,O,a,b);
			board[i] = NONE;
			if(curv == XWIN)
				{return XWIN;}

			// Update as necessary for alpha beta pruning
			if(curv > v)
				{v = curv;}
			if(v >= b)
				{return v;}
			if(v > a)
				{a = v;}
		}
	}
	return v;
}

// Min value function represents O's turn
int min_value(int *board, int a, int b)
{
	int v = 10;
	int curv;

	// check all open board spaces
	for(int i=0;i<9;i++)
	{
		if(board[i]==NONE)
		{
			board[i] = O;
			curv = minmaxvalue(board,X,a,b);
			board[i] = NONE;
			if(curv == OWIN)
				{return OWIN;}

			// Update as necessary for alpha beta pruning
			if(curv < v)
				{v = curv;}
			if(v <= a)
				{return v;}
			if(v < b)
				{b = v;}

		}
	}
	return v;
}


// Checks if there is a winner
int game_status(int *board)
{
	//diags
	if (board[0]==X && board[4]==X && board[8]==X) return X;
	if (board[2]==X && board[4]==X && board[6]==X) return X;

	//horizontal
	if (board[0]==X && board[1]==X && board[2]==X) return X;
	if (board[3]==X && board[4]==X && board[5]==X) return X;
	if (board[6]==X && board[7]==X && board[8]==X) return X;
	
	//vertical
	if (board[0]==X && board[3]==X && board[6]==X) return X;
	if (board[1]==X && board[4]==X && board[7]==X) return X;
	if (board[2]==X && board[5]==X && board[8]==X) return X;

	//diags
	if (board[0]==O && board[4]==O && board[8]==O) return O;
	if (board[2]==O && board[4]==O && board[6]==O) return O;

	//horizontal
	if (board[0]==O && board[1]==O && board[2]==O) return O;
	if (board[3]==O && board[4]==O && board[5]==O) return O;
	if (board[6]==O && board[7]==O && board[8]==O) return O;
	
	//vertical
	if (board[0]==O && board[3]==O && board[6]==O) return O;
	if (board[1]==O && board[4]==O && board[7]==O) return O;
	if (board[2]==O && board[5]==O && board[8]==O) return O;

	return NONE;//tie or unfinished
}
