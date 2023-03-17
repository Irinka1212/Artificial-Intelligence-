#include <iostream>
#include <vector>
#include <string>
#include<cstdlib>
#include <stack>

using namespace std;

void swapIndex(vector<string>& board, int firstIndex, int secondIndex)
{
	swap(board[firstIndex], board[secondIndex]);
}

bool isReverse(vector<string>& board, int n)
{
	if (board[n] != "_")
		return false;

	for (int i = 0; i < n; ++i)
	{
		if (board[i] != "R")
			return false;
	}
	return true;
}

// LL_RR 0 1 2 3 4
//left moves(R) - jump - LLR_R - 0 1 3 2 4 - swap n with n+1 
//				- double jump - LLRR_ - 0 1 3 4 2 - swap n with n+1 then swap n+1 with 2n((n+1)+1)
//right moves(L) - L_LRR - 0 2 1 3 4 - swap n with n-1
//               - _LLRR - 2 0 1 3 4 - swap n with n-1 then n with  then n-1 with 0((n-1)-1)

/*swapIndex(board, n, n + 1);//left jump
swapIndex(board, n, n + 2);//left double jump
swapIndex(board, n, n - 1);//right jump
swapIndex(board, n, n - 2);//right double jump*/

vector<vector<string>> moves(vector<string>& board, int size)
{
	vector<vector<string>> moves;
	vector<string> temp = board;
	for (int i = 0; i < size; ++i)
	{
		if (i < size - 1 && board[i] == "L" && board[i + 1] == "_")
		{
			swapIndex(temp, i, i + 1);
			moves.push_back(temp);
			temp = board;
		}
		if (i < size - 2 && board[i] == "L" && board[i + 2] == "_")
		{
			swapIndex(temp, i, i + 2);
			moves.push_back(temp);
			temp = board;
		}
		if (i > 0 && board[i] == "R" && board[i - 1] == "_")
		{
			swapIndex(temp, i, i - 1);
			moves.push_back(temp);
			temp = board;
		}
		if (i > 1 && board[i] == "R" && board[i - 2] == "_")
		{
			swapIndex(temp, i, i - 2);
			moves.push_back(temp);
		}
	}

	return moves;
}

void printMove(vector<string>& board)
{
	for (int i = 0; i < board.size(); ++i)
	{
		cout << board[i];
	}

	cout << endl;
}

bool dfs(vector<string>& board, int n, int size, stack<vector<string>>& jumps)
{
	if (isReverse(board, n))
		return true;

	vector<vector<string>> _moves = moves(board, size);
	
	for (int i = 0; i < _moves.size(); ++i)
	{
		if (dfs(_moves[i], n, size, jumps))
		{
			jumps.push(_moves[i]);
			return true;
		}
	}

	return false;
}

void playGame(vector<string>& board, int n, int size)
{
	cout << "Initial state:\n";
	printMove(board);
	cout << "\nJumps:\n";

	stack<vector<string>> jumps;
	dfs(board, n, size, jumps);

	while (!jumps.empty())
	{
		printMove(jumps.top());
		jumps.pop();
	}

	cout << endl;
}

int main()
{
	int n = 0;
	cin >> n;

	int size = (n * 2) + 1;
	vector<string> board;

	for (int i = 0; i < n; ++i)
	{
		board.push_back("L");
	}

	board.push_back("_");

	for (int i = 0; i < n; ++i)
	{
		board.push_back("R");
	}

	playGame(board, n, size);

	system("pause");

	return 0;

}