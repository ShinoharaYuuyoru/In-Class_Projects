#include "stdio.h"
#include "stdlib.h"

typedef struct PolynomialA
{
	int Ratio;
	int Exponent;

	struct PolynomialA  *Next;
}PA;
typedef struct PolynomialB
{
	int Ratio;
	int Exponent;

	struct PolynomialB *Next;
}PB;
typedef struct PolynomialC
{
	int Ratio;
	int Exponent;

	struct PolynomialC *Next;
}PC;
PA *HEADA = NULL;
PB *HEADB = NULL;
PC *HEADC = NULL;
PA *PointA = NULL;
PB *PointB = NULL;
PC *PointC = NULL;

void Creat(int R, int E, int Flag);
void Add(int Flag);
void Print(int Flag);

int main()
{
	int IfStart;
	int PCounter = 1;
	int TermC = 0;
	int Ra, Ex;

	HEADA = (PA*)malloc(sizeof(PA));
	HEADB = (PB*)malloc(sizeof(PB));
	HEADC = (PC*)malloc(sizeof(PC));
	HEADA->Next = NULL;
	HEADB->Next = NULL;
	HEADC->Next = NULL;

	scanf("%d", &IfStart);
	if (IfStart == 1)
	{
		for (;PCounter <= 3;PCounter++)
		{
			if (PCounter == 1)//PA
			{
				scanf("%d", &TermC);

				PointA = HEADA;
				for (;TermC >= 1;TermC--)
				{
					scanf("%d%d", &Ra, &Ex);

					if (Ra == 0)
					{
						continue;
					}
					else
					{
						Creat(Ra, Ex, 1);
					}
				}

				Print(1);
			}
			if (PCounter == 2)//PB
			{
				scanf("%d", &TermC);

				PointB = HEADB;
				for (;TermC >= 1;TermC--)
				{
					scanf("%d%d", &Ra, &Ex);

					if (Ra == 0)
					{
						continue;
					}
					else
					{
						Creat(Ra, Ex, 2);
					}
				}

				Print(2);
			}
			if (PCounter == 3)//PC
			{
				scanf("%d", &TermC);

				PointC = HEADC;
				for (;TermC >= 1;TermC--)
				{
					scanf("%d%d", &Ra, &Ex);

					if (Ra == 0)
					{
						continue;
					}
					else
					{
						Creat(Ra, Ex, 3);
					}
				}

				Print(3);
			}
		}

		Add(1);
		Print(2);
		Add(2);
		Print(3);
	}

	return 0;
}

void Creat(int R, int E, int Flag)
{
	if (Flag == 1)
	{
		PA *ADDA;

		ADDA = (PA*)malloc(sizeof(PA));
		ADDA->Ratio = R;
		ADDA->Exponent = E;
		ADDA->Next = NULL;
		PointA->Next = ADDA;
		PointA = ADDA;
	}
	if (Flag == 2)
	{
		PB *ADDB;

		ADDB = (PB*)malloc(sizeof(PB));
		ADDB->Ratio = R;
		ADDB->Exponent = E;
		ADDB->Next = NULL;
		PointB->Next = ADDB;
		PointB = ADDB;
	}
	if (Flag == 3)
	{
		PC *ADDC;

		ADDC = (PC*)malloc(sizeof(PC));
		ADDC->Ratio = R;
		ADDC->Exponent = E;
		ADDC->Next = NULL;
		PointC->Next = ADDC;
		PointC = ADDC;
	}
	return;
}

void Add(int Flag)
{
	if (Flag == 1)
	{
		PB *LASTB;
		PB *ADDB;

		for (PointA = HEADA->Next;PointA != NULL;PointA = PointA->Next)
		{
			if (HEADB->Next == NULL)//B is empty
			{
				ADDB = (PB*)malloc(sizeof(PB));
				ADDB->Ratio = PointA->Ratio;
				ADDB->Exponent = PointA->Exponent;
				ADDB->Next = NULL;
				HEADB->Next = ADDB;
			}
			else
			{
				for (LASTB = HEADB, PointB = HEADB->Next;PointB != NULL;LASTB = LASTB->Next, PointB = PointB->Next)
				{
					if (PointB->Exponent < PointA->Exponent)
					{
						if(PointB->Next == NULL)//LAST ONE OF B
						{
							ADDB = (PB*)malloc(sizeof(PB));
							ADDB->Ratio = PointA->Ratio;
							ADDB->Exponent = PointA->Exponent;
							ADDB->Next = NULL;
							PointB->Next = ADDB;
							break;
						}
						else
						{
							continue;
						}
					}
					else
					{
						if (PointB->Exponent == PointA->Exponent)
						{
							PointB->Ratio = PointB->Ratio + PointA->Ratio;

							if (PointB->Ratio == 0)
							{
								LASTB->Next = PointB->Next;
								free(PointB);
								PointB = LASTB;
							}
							break;
						}
						else
						{
							ADDB = (PB*)malloc(sizeof(PB));
							ADDB->Ratio = PointA->Ratio;
							ADDB->Exponent = PointA->Exponent;
							ADDB->Next = PointB;
							LASTB->Next = ADDB;
							PointB = ADDB;
							break;
						}
					}
				}
			}
		}
	}
	else
	{
		PC *LASTC;
		PC *ADDC;

		for (PointB = HEADB->Next;PointB != NULL;PointB = PointB->Next)
		{
			if (HEADC->Next == NULL)//B is empty
			{
				ADDC = (PC*)malloc(sizeof(PC));
				ADDC->Ratio = PointB->Ratio;
				ADDC->Exponent = PointB->Exponent;
				ADDC->Next = NULL;
				HEADC->Next = ADDC;
			}
			else
			{
				for (LASTC = HEADC, PointC = HEADC->Next;PointC != NULL;LASTC = LASTC->Next, PointC = PointC->Next)
				{
					if (PointC->Exponent < PointB->Exponent)
					{
						if (PointC->Next == NULL)
						{
							ADDC = (PC*)malloc(sizeof(PC));
							ADDC->Ratio = PointB->Ratio;
							ADDC->Exponent = PointB->Exponent;
							ADDC->Next = NULL;
							PointC->Next = ADDC;
							break;
						}
						else
						{
							continue;
						}
					}
					else
					{
						if (PointC->Exponent == PointB->Exponent)
						{
							PointC->Ratio = PointC->Ratio + PointB->Ratio;

							if (PointC->Ratio == 0)
							{
								LASTC->Next = PointC->Next;
								free(PointC);
								PointC = LASTC;
							}
							break;
						}
						else
						{
							ADDC = (PC*)malloc(sizeof(PC));
							ADDC->Ratio = PointB->Ratio;
							ADDC->Exponent = PointB->Exponent;
							ADDC->Next = PointC;
							LASTC->Next = ADDC;
							PointC = ADDC;
							break;
						}
					}
				}
			}
		}
	}
}

void Print(int Flag)
{
	if (Flag == 1)
	{
		if (HEADA->Next == NULL)
		{
			printf("<0,0>\n");
		}
		else
		{
			for (PointA = HEADA->Next;PointA != NULL;PointA = PointA->Next)
			{
				printf("<%d,%d>", PointA->Ratio, PointA->Exponent);
				if (PointA->Next != NULL)
				{
					printf(",");
				}
				else
				{
					printf("\n");
				}
			}
		}
		return;
	}
	if (Flag == 2)
	{
		if (HEADB->Next == NULL)
		{
			printf("<0,0>\n");
		}
		else
		{
			for (PointB = HEADB->Next;PointB != NULL;PointB = PointB->Next)
			{
				printf("<%d,%d>", PointB->Ratio, PointB->Exponent);
				if (PointB->Next != NULL)
				{
					printf(",");
				}
				else
				{
					printf("\n");
				}
			}
		}
		return;
	}
	if (Flag == 3)
	{
		if (HEADC->Next == NULL)
		{
			printf("<0,0>\n");
		}
		else
		{
			for (PointC = HEADC->Next;PointC != NULL;PointC = PointC->Next)
			{
				printf("<%d,%d>", PointC->Ratio, PointC->Exponent);
				if (PointC->Next != NULL)
				{
					printf(",");
				}
				else
				{
					printf("\n");
				}
			}
		}
		return;
	}
}