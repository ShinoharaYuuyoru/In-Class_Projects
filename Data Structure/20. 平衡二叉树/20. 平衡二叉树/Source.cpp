#include "stdio.h"
#include "stdlib.h"

typedef struct NODE
{
	struct NODE *Parent;
	char Data;
	struct NODE *LeftChild;
	struct NODE *RightChild;
	int Balance;
}LeafNode,*Leaf;

int Compare(int x, int y);
int InsertBST(Leaf *T, char D);
int SearchBST(Leaf T, char Key, Leaf P, Leaf *R);
void BalanceCal(Leaf S, Leaf *T);
void LeftSpin(Leaf *R);
void RightSpin(Leaf *R);
void LeftRightSpin(Leaf *R);
void RightLeftSpin(Leaf *R);
int update(Leaf current);
int PrintDLR(Leaf T, char *DLR, int Counter);
int PrintLDR(Leaf T, char *LDR, int Counter);
int PrintLRD(Leaf T, char *LRD, int Counter);
void PrintTree(Leaf T, int Counter);

int main()
{
	int N = 0;
	char Temp = '\0';
	Leaf Tree = NULL;
	char DLR[200] = { '\0' };
	char LDR[200] = { '\0' };
	char LRD[200] = { '\0' };

	while (1)
	{
		scanf("%c", &Temp);
		N++;

		if (Temp != '\n')
		{
			InsertBST(&Tree, Temp);
		}
		else
		{
			break;
		}
	}

	/*Print*/
	PrintDLR(Tree, DLR, 0);
	printf("Preorder: %s\n", DLR);
	PrintLDR(Tree, LDR, 0);
	printf("Inorder: %s\n", LDR);
	PrintLRD(Tree, LRD, 0);
	printf("Postorder: %s\n", LRD);

	printf("Tree:\n");
	PrintTree(Tree, 0);
	/*Over*/

	return 0;
}

int Compare(int x, int y)
{
	if (x > y)
	{
		return 1;
	}
	else
	{
		if (x == y)
		{
			return 0;
		}
		else
		{
			return -1;
		}
	}
}

int InsertBST(Leaf *T, char D)
{
	Leaf IfSearch = NULL;
	Leaf Add = NULL;

	if (!SearchBST(*T, D, NULL, &IfSearch))//If there is no Key in the Tree.
	{
		Add = (Leaf)malloc(sizeof(LeafNode));
		Add->Parent = IfSearch;
		Add->Data = D;
		Add->LeftChild = NULL;
		Add->RightChild = NULL;
		Add->Balance = 0;

		if (!IfSearch)
		{
			*T = Add;
		}
		else
		{
			if (Compare(D, IfSearch->Data) == -1)
			{
				IfSearch->LeftChild = Add;
			}
			else
			{
				IfSearch->RightChild = Add;
			}
		}

		update(*T);
		BalanceCal(Add, T);
		return 1;
	}
	else
	{
		return 0;
	}
}

int SearchBST(Leaf T, char Key, Leaf P, Leaf *R)//T: Tree, Key: Keyword, P: Parent(First time usl NULL), R: Return Point.
{
	if (!T)//If the Tree doesn't exist.
	{
		*R = P;
		return 0;
	}
	else
	{
		if (Compare(Key, T->Data) == 0)
		{
			*R = T;
			return 1;
		}
		else
		{
			if (Compare(Key, T->Data) == -1)
			{
				return SearchBST(T->LeftChild, Key, T, R);
			}
			else
			{
				return SearchBST(T->RightChild, Key, T, R);
			}
		}
	}
}

void BalanceCal(Leaf S, Leaf *T)
{
	Leaf P = S->Parent;//Parent of S.

	if (P != NULL)//S is not the whole root
	{
		if (P->LeftChild == S)
		{
			update(*T);

			if (P->Balance == 2)//Left tree is high.
			{
				if (S->Balance == 1)//LL. Should RightSpin
				{
					RightSpin(&P);
				}
				else
				{
					if (S->Balance == -1)//LR. Should LeftSpin + RightSpin.
					{
						LeftRightSpin(&P);
					}
				}

				if (P->Parent == NULL)
				{
					*T = P;
				}
				update(*T);
				return;
			}
		}
		else
		{
			if (P->RightChild == S)
			{
				update(*T);

				if (P->Balance == -2)
				{
					if (S->Balance == 1)//RL. Should RightSpin + LeftSpin.
					{
						RightLeftSpin(&P);
					}
					else
					{
						if (S->Balance == -1)//RR. Should LeftSpin.
						{
							LeftSpin(&P);
						}
					}

					if (P->Parent == NULL)
					{
						*T = P;
					}
					update(*T);
					return;
				}
			}
		}

		BalanceCal(P, T);
	}
	else
	{
		*T = S;
		update(*T);
		return;
	}
}

void LeftSpin(Leaf *R)
{
	Leaf Root = *R;
	Leaf RParent = Root->Parent;
	Leaf RRight = Root->RightChild;

	if (RParent != NULL)
	{
		if (RParent->LeftChild == Root)
		{
			RParent->LeftChild = RRight;
		}
		else
		{
			if (RParent->RightChild == Root)
			{
				RParent->RightChild = RRight;
			}
		}
	}

	Root->Parent = RRight;
	RRight->Parent = RParent;
	Leaf RRightLeft = RRight->LeftChild;
	Root->RightChild = RRightLeft;
	RRight->LeftChild = Root;
	if (RRightLeft != NULL)
	{
		RRightLeft->Parent = Root;
	}

	*R = RRight;
}

void RightSpin(Leaf *R)
{
	Leaf Root = *R;
	Leaf RParent = Root->Parent;
	Leaf RLeft = Root->LeftChild;

	if (RParent != NULL)
	{
		if (RParent->LeftChild == Root)
		{
			RParent->LeftChild = RLeft;
		}
		else
		{
			if (RParent->RightChild == Root)
			{
				RParent->RightChild = RLeft;
			}
		}
	}

	Root->Parent = RLeft;
	RLeft->Parent = RParent;
	Leaf RLeftRight = RLeft->RightChild;
	Root->LeftChild = RLeftRight;
	RLeft->RightChild = Root;
	if (RLeftRight != NULL)
	{
		RLeftRight->Parent = Root;
	}

	*R = RLeft;
}

void LeftRightSpin(Leaf *R)
{
	Leaf Root = *R;

	/*RootLeft LeftSpin*/
	{
		Leaf RLeft = Root->LeftChild;
		Leaf RLeftRight = RLeft->RightChild;

		Root->LeftChild = RLeftRight;
		RLeft->Parent = RLeftRight;
		RLeftRight->Parent = Root;
		Leaf RLeftRightLeft = RLeftRight->LeftChild;
		RLeft->RightChild = RLeftRightLeft;
		RLeftRight->LeftChild = RLeft;
		if (RLeftRightLeft != NULL)
		{
			RLeftRightLeft->Parent = RLeft;
		}
	}
	/*Over*/

	/*Root RightSpin*/
	RightSpin(R);
	/*Over*/
}

void RightLeftSpin(Leaf *R)
{
	Leaf Root = *R;

	/*RootRight RightSpin*/
	{
		Leaf RRight = Root->RightChild;
		Leaf RRightLeft = RRight->LeftChild;

		Root->RightChild = RRightLeft;
		RRight->Parent = RRightLeft;
		RRightLeft->Parent = Root;
		Leaf RRightLeftRight = RRightLeft->RightChild;
		RRight->LeftChild = RRightLeftRight;
		RRightLeft->RightChild = RRight;
		if (RRightLeftRight != NULL)
		{
			RRightLeftRight->Parent = RRight;
		}
	}
	/*Over*/

	/*Root LeftSpin*/
	LeftSpin(R);
	/*Over*/
}

int update(Leaf current)
{
	if (current == NULL) {
		return 0;
	}
	int left = update(current->LeftChild);
	int right = update(current->RightChild);
	current->Balance = left - right;
	return (left > right ? left + 1 : right + 1);
}

int PrintDLR(Leaf T, char *DLR, int Counter)//先序遍历
{
	if (T)
	{
		DLR[Counter] = T->Data;
		Counter++;

		if (T->LeftChild)
		{
			Counter = PrintDLR(T->LeftChild, DLR, Counter);
		}

		if (T->RightChild)
		{
			Counter = PrintDLR(T->RightChild, DLR, Counter);
		}
	}

	return Counter;
}

int PrintLDR(Leaf T, char *LDR, int Counter)//中序遍历
{
	if (T)
	{
		if (T->LeftChild)
		{
			Counter = PrintLDR(T->LeftChild, LDR, Counter);
		}

		LDR[Counter] = T->Data;
		Counter++;

		if (T->RightChild)
		{
			Counter = PrintLDR(T->RightChild, LDR, Counter);
		}
	}

	return Counter;
}

int PrintLRD(Leaf T, char *LRD, int Counter)//后序遍历
{
	if (T)
	{
		if (T->LeftChild)
		{
			Counter = PrintLRD(T->LeftChild, LRD, Counter);
		}

		if (T->RightChild)
		{
			Counter = PrintLRD(T->RightChild, LRD, Counter);
		}

		LRD[Counter] = T->Data;
		Counter++;
	}

	return Counter;
}

void PrintTree(Leaf T, int Counter)
{
	if (T)
	{
		if (T->RightChild)
		{
			PrintTree(T->RightChild, Counter + 1);
		}

		int Space = 0;
		for (Space = 0;Space < Counter;Space++)
		{
			printf("    ");
		}
		printf("%c\n", T->Data);

		if (T->LeftChild)
		{
			PrintTree(T->LeftChild, Counter + 1);
		}
	}
}