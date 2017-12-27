#include <iostream>
#include "string.h"
using namespace std;

int Comp(const void *a, const void *b);

class NumberFlow
{
private:
	char Flow[1005];
	int Length;
	int Flag;//-1£∫»ŒÑ’ ßî° 0£∫§ø§¿•º•Ì 1£∫•ﬁ•Ø•π• •Û•–©`§¨§¢§Î
	int HasFive, HasZero;
	int Sign[10];
	int MaxNumber;

public:
	int Input();
	void PossibleCheck();
	void MaxNumberDeal();
	void DeleteNumber(int More);
	void MakeMaxNumber(int Start, int Step);//Move
	void Output();
	NumberFlow();
};

inline int NumberFlow::Input()
{
	int ZeroCounter = 0;

	for (Length = 0;;Length++)
	{
		Flow[Length] = getchar();

		if (Flow[0] == EOF)
		{
			return 0;
		}
		if (Flow[Length] - 48 == 0)
		{
			ZeroCounter++;
		}
		if (Flow[Length] == '\n')
		{
			Length--;
			Flag = 1;

			break;
		}
		Sign[(Flow[Length] - 48)]++;
	}
	if (ZeroCounter == Length + 1)
	{
		Flag = 0;
	}
	Flow[Length + 1] = '\0';

	return 1;
}

inline void NumberFlow::PossibleCheck()
{
	if (Flag == 0)
	{
		return;
	}
	else
	{
		int Searcher;

		for (Searcher = 0;Searcher <= Length;Searcher++)
		{
			if ((Flow[Searcher] - 48) == 0 || (Flow[Searcher] - 48) == 5)
			{
				Flag = 1;
				if ((Flow[Searcher] - 48) == 0)
				{
					HasZero = 1;
				}
				if ((Flow[Searcher] - 48) == 5)
				{
					HasFive = 1;
				}

				if (HasZero == 1 && HasFive == 1)
				{
					return;
				}
			}
		}
		if (HasZero == 0 && HasFive == 0)
		{
			Flag = -1;
		}
	}

	return;
}

void NumberFlow::MaxNumberDeal()
{
	if (Flag == 0 || Flag == -1)
	{
		return;
	}
	else
	{
		if (HasZero == 1)
		{
			qsort(Flow, Length + 1, sizeof(char), Comp);

			if (HasFive == 1)//HasZero and HasFive
			{
				int Sum = 0;
				int Pointer = 0;
				int ModNumber = 0;

				for (Pointer = 0;Pointer <= Length;Pointer++)
				{
					Sum = Sum + (Flow[Pointer] - 48);
				}
				ModNumber = Sum % 3;
				if (ModNumber == 0)
				{
					Flag = 1;

					return;
				}
				if (ModNumber == 1)
				{
					DeleteNumber(1);

					return;
				}
				if (ModNumber == 2)
				{
					DeleteNumber(2);

					return;
				}
			}
			else//Only HasZero
			{
				int Sum = 0;
				int Pointer = 0;
				int ModNumber = 0;

				for (Pointer = 0;Pointer <= Length;Pointer++)
				{
					Sum = Sum + (Flow[Pointer] - 48);
				}
				ModNumber = Sum % 3;
				if (ModNumber == 0)
				{
					Flag = 1;

					return;
				}
				if (ModNumber == 1)
				{
					DeleteNumber(1);

					return;
				}
				if (ModNumber == 2)
				{
					DeleteNumber(2);

					return;
				}
			}
		}
		else//Only HasFive
		{
			int Sum = 0;
			int Pointer = 0;
			int ModNumber = 0;

			for (Pointer = 0;Pointer <= Length;Pointer++)
			{
				if (Flow[Pointer] - 48 == 5)
				{
					char Temp = Flow[Length];

					Flow[Length] = Flow[Pointer];
					Flow[Pointer] = Temp;

					break;
				}
			}
			qsort(Flow, Length, sizeof(char), Comp);

			for (Pointer = 0;Pointer <= Length;Pointer++)
			{
				Sum = Sum + (Flow[Pointer] - 48);
			}
			ModNumber = Sum % 3;
			if (ModNumber == 0)
			{
				Flag = 1;

				return;
			}
			if (ModNumber == 1)
			{
				DeleteNumber(1);

				return;
			}
			if (ModNumber == 2)
			{
				DeleteNumber(2);

				return;
			}
		}
	}
}

void NumberFlow::DeleteNumber(int More)
{
	if (More == 1)
	{
		int OneFlag = 0;
		int FourFlag = 0;
		int SevenFlag = 0;

		if (Sign[1] > 0)
		{
			int DeleteTemp = 0;
			int Counter = 0;

			for (Counter = 0;Counter < 1;Counter++)
			{
				DeleteTemp = DeleteTemp + Sign[Counter];
			}
			if (Flow[Length] == '5'&&Counter <= 5)
			{
				DeleteTemp++;
			}
			Flow[Length - DeleteTemp] = 58;
			Sign[1]--;
			MakeMaxNumber(Length - Sign[0], 1);

			OneFlag = 1;
		}
		else//1§œ§ §§
		{
			if (Sign[4] > 0)
			{
				int DeleteTemp = 0;
				int Counter = 0;

				for (Counter = 0;Counter < 4;Counter++)
				{
					DeleteTemp = DeleteTemp + Sign[Counter];
				}
				if (Flow[Length] == '5'&&Counter <= 5)
				{
					DeleteTemp++;
				}
				Flow[Length - DeleteTemp] = 58;
				Sign[4]--;
				MakeMaxNumber(Length - DeleteTemp, 1);

				FourFlag = 1;
			}
			else//1§»4§œ§ §§ 7§Ú•«•Í©`•»§∑§ﬁ§π
			{
				if (Sign[7] > 0)
				{
					int DeleteTemp = 0;
					int Counter = 0;

					for (Counter = 0;Counter < 7;Counter++)
					{
						DeleteTemp = DeleteTemp + Sign[Counter];
					}
					if (Flow[Length] == '5'&&Counter <= 5)
					{
						DeleteTemp++;
					}
					Flow[Length - DeleteTemp] = 58;
					Sign[7]--;
					MakeMaxNumber(Length - DeleteTemp, 1);

					SevenFlag = 1;
				}
			}
		}
		if (OneFlag == 0 && FourFlag == 0 && SevenFlag == 0)
		{
			if (Sign[2] >= 1)
			{
				if (Sign[2] >= 2)
				{
					int DeleteTemp = 0;
					int Counter = 0;

					for (Counter = 0;Counter < 2;Counter++)
					{
						DeleteTemp = DeleteTemp + Sign[Counter];
					}
					if (Flow[Length] == '5'&&Counter <= 5)
					{
						DeleteTemp++;
					}
					Flow[Length - DeleteTemp] = 58;
					Flow[Length - DeleteTemp - 1] = 58;
					Sign[2] = Sign[2] - 2;
					MakeMaxNumber(Length - DeleteTemp - 1, 2);
				}
				else//One 2
				{
					if (Sign[5] >= 1)
					{
						if (Sign[5] == 1 && Flow[Length] == '5')
						{
							if (Sign[8] >= 1)
							{
								int DeleteTemp = 0;
								int Counter = 0;

								for (Counter = 0;Counter < 2;Counter++)
								{
									DeleteTemp = DeleteTemp + Sign[Counter];
								}
								if (Flow[Length] == '5'&&Counter <= 5)
								{
									DeleteTemp++;
								}
								Flow[Length - DeleteTemp] = 58;
								Sign[2]--;
								MakeMaxNumber(Length - DeleteTemp, 1);
								for (DeleteTemp = 0, Counter = 0;Counter < 8;Counter++)
								{
									DeleteTemp = DeleteTemp + Sign[Counter];
								}
								if (Flow[Length] == '5'&&Counter <= 5)
								{
									DeleteTemp++;
								}
								Flow[Length - DeleteTemp] = 58;
								Sign[8]--;
								MakeMaxNumber(Length - DeleteTemp, 1);
							}
							else
							{
								Flag = -1;

								return;
							}
						}
						else
						{
							int DeleteTemp = 0;
							int Counter = 0;

							for (Counter = 0;Counter < 2;Counter++)
							{
								DeleteTemp = DeleteTemp + Sign[Counter];
							}
							if (Flow[Length] == '5'&&Counter <= 5)
							{
								DeleteTemp++;
							}
							Flow[Length - DeleteTemp] = 58;
							Sign[2]--;
							MakeMaxNumber(Length - DeleteTemp, 1);
							for (DeleteTemp = 0, Counter = 0;Counter < 5;Counter++)
							{
								DeleteTemp = DeleteTemp + Sign[Counter];
							}
							if (Flow[Length] == '5'&&Counter <= 5)
							{
								DeleteTemp++;
							}
							Flow[Length - DeleteTemp] = 58;
							Sign[5]--;
							MakeMaxNumber(Length - DeleteTemp, 1);
						}
					}
					else
					{
						if (Sign[8] >= 1)
						{
							int DeleteTemp = 0;
							int Counter = 0;

							for (Counter = 0;Counter < 2;Counter++)
							{
								DeleteTemp = DeleteTemp + Sign[Counter];
							}
							if (Flow[Length] == '5'&&Counter <= 5)
							{
								DeleteTemp++;
							}
							Flow[Length - DeleteTemp] = 58;
							Sign[2]--;
							MakeMaxNumber(Length - DeleteTemp, 1);
							for (DeleteTemp = 0, Counter = 0;Counter < 8;Counter++)
							{
								DeleteTemp = DeleteTemp + Sign[Counter];
							}
							if (Flow[Length] == '5'&&Counter <= 5)
							{
								DeleteTemp++;
							}
							Flow[Length - DeleteTemp] = 58;
							Sign[8]--;
							MakeMaxNumber(Length - DeleteTemp, 1);
						}
						else
						{
							Flag = -1;

							return;
						}
					}
				}
			}
			else
			{
				if (Sign[5] >= 1)
				{
					if (Sign[5] == 1 && Flow[Length] == '5')
					{
						if (Sign[8] >= 2)
						{
							int DeleteTemp = 0;
							int Counter = 0;

							for (Counter = 0;Counter < 5;Counter++)
							{
								DeleteTemp = DeleteTemp + Sign[Counter];
							}
							if (Flow[Length] == '5'&&Counter <= 5)
							{
								DeleteTemp++;
							}
							Flow[Length - DeleteTemp] = 58;
							Sign[5]--;
							MakeMaxNumber(Length - DeleteTemp, 1);
							for (DeleteTemp = 0, Counter = 0;Counter < 8;Counter++)
							{
								DeleteTemp = DeleteTemp + Sign[Counter];
							}
							if (Flow[Length] == '5'&&Counter <= 5)
							{
								DeleteTemp++;
							}
							Flow[Length - DeleteTemp] = 58;
							Sign[8]--;
							MakeMaxNumber(Length - DeleteTemp, 1);
						}
						else
						{
							Flag = -1;

							return;
						}
					}
					else
					{
						if (Sign[5] == 1)
						{
							if (Sign[8] >= 1)
							{
								int DeleteTemp = 0;
								int Counter = 0;

								for (Counter = 0;Counter < 5;Counter++)
								{
									DeleteTemp = DeleteTemp + Sign[Counter];
								}
								if (Flow[Length] == '5'&&Counter <= 5)
								{
									DeleteTemp++;
								}
								Flow[Length - DeleteTemp] = 58;
								Sign[5]--;
								MakeMaxNumber(Length - DeleteTemp, 1);
								for (DeleteTemp = 0, Counter = 0;Counter < 8;Counter++)
								{
									DeleteTemp = DeleteTemp + Sign[Counter];
								}
								if (Flow[Length] == '5'&&Counter <= 5)
								{
									DeleteTemp++;
								}
								Flow[Length - DeleteTemp] = 58;
								Sign[8]--;
								MakeMaxNumber(Length - DeleteTemp, 2);
							}
							else
							{
								Flag = -1;

								return;
							}
						}
						else
						{
							int DeleteTemp = 0;
							int Counter = 0;

							for (Counter = 0;Counter < 5;Counter++)
							{
								DeleteTemp = DeleteTemp + Sign[Counter];
							}
							if (Flow[Length] == '5'&&Counter <= 5)
							{
								DeleteTemp++;
							}
							Flow[Length - DeleteTemp] = 58;
							Flow[Length - DeleteTemp - 1] = 58;
							Sign[5] = Sign[5] - 2;
							MakeMaxNumber(Length - DeleteTemp - 1, 2);
						}
					}
				}
				else//No 5
				{
					if (Sign[8] >= 2)
					{
						int DeleteTemp = 0;
						int Counter = 0;

						for (Counter = 0;Counter < 8;Counter++)
						{
							DeleteTemp = DeleteTemp + Sign[Counter];
						}
						if (Flow[Length] == '5'&&Counter <= 5)
						{
							DeleteTemp++;
						}
						Flow[Length - DeleteTemp] = 58;
						Flow[Length - DeleteTemp - 1] = 58;
						Sign[8] = Sign[8] - 2;
						MakeMaxNumber(Length - DeleteTemp - 1, 2);
					}
					else
					{
						Flag = -1;

						return;
					}
				}
			}
		}
	}

	if (More == 2)
	{
		int TwoFlag = 0;
		int FiveFlag = 0;
		int EightFlag = 0;

		if (Sign[2] > 0)
		{
			int DeleteTemp = 0;
			int Counter = 0;

			for (Counter = 0;Counter < 2;Counter++)
			{
				DeleteTemp = DeleteTemp + Sign[Counter];
			}
			if (Flow[Length] == '5'&&Counter <= 5)
			{
				DeleteTemp++;
			}
			Flow[Length - DeleteTemp] = 58;
			Sign[2]--;
			MakeMaxNumber(Length - DeleteTemp, 1);

			TwoFlag = 1;
		}
		else//2§œ§ §§
		{
			if (Sign[5] > 0)
			{
				if (Sign[5] == 1)
				{
					if (Sign[0] > 0)
					{
						int DeleteTemp = 0;
						int Counter = 0;

						for (Counter = 0;Counter < 5;Counter++)
						{
							DeleteTemp = DeleteTemp + Sign[Counter];
						}
						Flow[Length - DeleteTemp] = 58;
						Sign[5]--;
						MakeMaxNumber(Length - DeleteTemp, 1);

						FiveFlag = 1;
					}
					else
					{
						if (Sign[8] > 0)
						{
							int DeleteTemp = 0;
							int Counter = 0;

							for (Counter = 0;Counter < 8;Counter++)
							{
								DeleteTemp = DeleteTemp + Sign[Counter];
							}
							if (Flow[Length] == '5'&&Counter <= 5)
							{
								DeleteTemp++;
							}
							Flow[Length - DeleteTemp] = 58;
							Sign[8]--;
							MakeMaxNumber(Length - DeleteTemp, 1);

							EightFlag = 1;
						}
					}
				}
				else
				{
					int DeleteTemp = 0;
					int Counter = 0;

					for (Counter = 0;Counter < 5;Counter++)
					{
						DeleteTemp = DeleteTemp + Sign[Counter];
					}
					if (Flow[Length] == '5'&&Counter <= 5)
					{
						DeleteTemp++;
					}
					Flow[Length - DeleteTemp] = 58;
					Sign[5]--;
					MakeMaxNumber(Length - DeleteTemp, 1);

					FiveFlag = 1;
				}
			}
			else//2§»5§œ§ §§ 8§Ú•«•Í©`•»§∑§ﬁ§π
			{
				if (Sign[8] > 0)
				{
					int DeleteTemp = 0;
					int Counter = 0;

					for (Counter = 0;Counter < 8;Counter++)
					{
						DeleteTemp = DeleteTemp + Sign[Counter];
					}
					if (Flow[Length] == '5'&&Counter <= 5)
					{
						DeleteTemp++;
					}
					Flow[Length - DeleteTemp] = 58;
					Sign[8]--;
					MakeMaxNumber(Length - DeleteTemp, 1);

					EightFlag = 1;
				}
			}
		}
		if (TwoFlag == 0 && FiveFlag == 0 && EightFlag == 0)
		{
			if (Sign[1] >= 1)
			{
				if (Sign[1] >= 2)
				{
					int DeleteTemp = 0;
					int Counter = 0;

					for (Counter = 0;Counter < 1;Counter++)
					{
						DeleteTemp = DeleteTemp + Sign[Counter];
					}
					if (Flow[Length] == '5'&&Counter <= 5)
					{
						DeleteTemp++;
					}
					Flow[Length - DeleteTemp] = 58;
					Flow[Length - DeleteTemp - 1] = 58;
					Sign[1] = Sign[1] - 2;
					MakeMaxNumber(Length - DeleteTemp - 1, 2);
				}
				else//Only one 1
				{
					if (Sign[4] >= 1)
					{
						int DeleteTemp = 0;
						int Counter = 0;

						for (Counter = 0;Counter < 1;Counter++)
						{
							DeleteTemp = DeleteTemp + Sign[Counter];
						}
						if (Flow[Length] == '5'&&Counter <= 5)
						{
							DeleteTemp++;
						}
						Flow[Length - DeleteTemp] = 58;
						Sign[1]--;
						MakeMaxNumber(Length - DeleteTemp, 1);
						for (DeleteTemp = 0, Counter = 0;Counter < 4;Counter++)
						{
							DeleteTemp = DeleteTemp + Sign[Counter];
						}
						if (Flow[Length] == '5'&&Counter <= 5)
						{
							DeleteTemp++;
						}
						Flow[Length - DeleteTemp] = 58;
						Sign[4]--;
						MakeMaxNumber(Length - DeleteTemp, 1);
					}
					else
					{
						if (Sign[7] >= 1)
						{
							int DeleteTemp = 0;
							int Counter = 0;

							for (Counter = 0;Counter < 1;Counter++)
							{
								DeleteTemp = DeleteTemp + Sign[Counter];
							}
							if (Flow[Length] == '5'&&Counter <= 5)
							{
								DeleteTemp++;
							}
							Flow[Length - DeleteTemp] = 58;
							Sign[1]--;
							MakeMaxNumber(Length - DeleteTemp, 1);
							for (DeleteTemp = 0, Counter = 0;Counter < 7;Counter++)
							{
								DeleteTemp = DeleteTemp + Sign[Counter];
							}
							if (Flow[Length] == '5'&&Counter <= 5)
							{
								DeleteTemp++;
							}
							Flow[Length - DeleteTemp] = 58;
							Sign[7]--;
							MakeMaxNumber(Length - DeleteTemp, 1);
						}
						else
						{
							Flag = -1;

							return;
						}
					}
				}
			}
			else
			{
				if (Sign[4] >= 2)
				{
					int DeleteTemp = 0;
					int Counter = 0;

					for (Counter = 0;Counter < 4;Counter++)
					{
						DeleteTemp = DeleteTemp + Sign[Counter];
					}
					if (Flow[Length] == '5'&&Counter <= 5)
					{
						DeleteTemp++;
					}
					Flow[Length - DeleteTemp] = 58;
					Flow[Length - DeleteTemp - 1] = 58;
					Sign[4] = Sign[4] - 2;
					MakeMaxNumber(Length - DeleteTemp - 1, 2);
				}
				else
				{
					if (Sign[4] == 1)
					{
						if (Sign[7] >= 1)
						{
							int DeleteTemp = 0;
							int Counter = 0;

							for (Counter = 0;Counter < 4;Counter++)
							{
								DeleteTemp = DeleteTemp + Sign[Counter];
							}
							if (Flow[Length] == '5'&&Counter <= 5)
							{
								DeleteTemp++;
							}
							Flow[Length - DeleteTemp] = 58;
							Sign[4]--;
							MakeMaxNumber(Length - DeleteTemp, 1);
							for (DeleteTemp = 0, Counter = 0;Counter < 7;Counter++)
							{
								DeleteTemp = DeleteTemp + Sign[Counter];
							}
							if (Flow[Length] == '5'&&Counter <= 5)
							{
								DeleteTemp++;
							}
							Flow[Length - DeleteTemp] = 58;
							Sign[7]--;
							MakeMaxNumber(Length - DeleteTemp, 1);
						}
						else
						{
							Flag = -1;

							return;
						}
					}
					else//No 4
					{
						if (Sign[7] >= 2)
						{
							int DeleteTemp = 0;
							int Counter = 0;

							for (Counter = 0;Counter < 7;Counter++)
							{
								DeleteTemp = DeleteTemp + Sign[Counter];
							}
							if (Flow[Length] == '5'&&Counter <= 5)
							{
								DeleteTemp++;
							}
							Flow[Length - DeleteTemp] = 58;
							Flow[Length - DeleteTemp - 1] = 58;
							Sign[7] = Sign[7] - 2;
							MakeMaxNumber(Length - DeleteTemp - 1, 2);
						}
						else
						{
							Flag = -1;

							return;
						}
					}
				}
			}
		}
	}

	int Counter = 1;
	int FinalCheck = 0;
	for (;Counter <= 9;Counter++)
	{
		if (Sign[Counter] >= 1)
		{
			FinalCheck = 1;

			break;
		}
	}
	if (FinalCheck == 0)
	{
		Flag = 0;
	}
	
	return;
}

void NumberFlow::MakeMaxNumber(int Start,int Step)
{
	for (;Start < Length;Start++)
	{
		Flow[Start] = Flow[Start + Step];
	}
	Length = Length - Step;
	Flow[Length + 1] = '\0';

	return;
}

inline void NumberFlow::Output()
{
	if (Flag == -1)
	{
		cout << "impossible" << endl;

		return;
	}
	if (Flag == 0)
	{
		cout << 0 << endl;

		return;
	}
	if (Flag == 1)
	{
		cout << Flow << endl;

		return;
	}
}

inline NumberFlow::NumberFlow()
{
	memset(Flow, 0, sizeof(Flow));
	Length = 0;
	Flag = 0;
	HasFive = HasZero = 0;
	memset(Sign, 0, sizeof(Sign));
	MaxNumber = 0;
}

int main()
{
	while (1)
	{
		int InputCheck = -1;
		NumberFlow *GroupX;
		GroupX = new NumberFlow;

		InputCheck = GroupX->Input();
		if (InputCheck == 0)
		{
			break;
		}
		else
		{
			GroupX->PossibleCheck();
			GroupX->MaxNumberDeal();
			GroupX->Output();

			delete GroupX;
		}
	}

	return 0;
}

int Comp(void const *a, void const *b)
{
	return *(char*)b - *(char*)a;
}