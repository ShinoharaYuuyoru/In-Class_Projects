#include "iostream"
#include "ctime"

using namespace std;

class DATE
{
private:
	int NowYear;
	int NowMonth;
	int NowDay;
	int NowWeek;
	int NowHour;
	int NowMin;
	int NowSec;
	int NowDST = -1;//ÏÄÁîÊ±

public:
	DATE()
	{
		time_t NowTime;
		NowTime = time(NULL);

		struct tm *TimeInfo;
		TimeInfo = localtime(&NowTime);

		NowYear = 1900 + TimeInfo->tm_year;
		NowMonth = 1 + TimeInfo->tm_mon;
		NowDay = TimeInfo->tm_mday;
		NowWeek = TimeInfo->tm_wday;
		NowHour = TimeInfo->tm_hour;
		NowMin = TimeInfo->tm_min;
		NowSec = TimeInfo->tm_sec;
	}
	int GetYear()
	{
		return NowYear;
	}
	int GetMonth()
	{
		return NowMonth;
	}
	int GetDay()
	{
		return NowDay;
	}
	int GetWeek()
	{
		return NowWeek;
	}
	int GetHour()
	{
		return NowHour;
	}
	int GetMin()
	{
		return NowMin;
	}
	int GetSec()
	{
		return NowSec;
	}
};

class BIRTHDAY :private DATE
{
private:
	DATE NowTime;
	int Year;
	int Month;
	int Day;
	int Age;

public:
	BIRTHDAY(int Y, int M, int D)
	{
		Year = Y;
		Month = M;
		Day = D;
	}
	int AGE()
	{
		Age = NowTime.GetYear() - Year;

		int TempMonthMinus = NowTime.GetMonth() - Month;
		if (TempMonthMinus < 0)
		{
			Age--;
		}
		else
		{
			if (TempMonthMinus == 0)
			{
				int TempDayMinus = NowTime.GetDay() - Day;
				if (TempDayMinus < 0)
				{
					Age--;
				}
			}
		}

		return Age;
	}
};

int main()
{
	BIRTHDAY Zhang(1988, 5, 2);
	cout << Zhang.AGE() << endl;  // Now Zhang's age is 27.
	return 0;
}