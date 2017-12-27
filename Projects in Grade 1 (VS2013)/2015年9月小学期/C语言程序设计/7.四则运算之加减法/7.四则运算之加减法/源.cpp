#include <stdio.h>  
#include <string.h>  

void plus(char *a, char *b, char *c);
void minus(char *a, char *b, char *c);

int main()
{
	char a[1000];
	char b[1000];
	char c[1000];
	char s[2];

	while (scanf("%s %s %s", a, s, b) == 3) 
	{
		if (s[0] == '+') 
		{
			plus(a, b, c);
		}
		else if (s[0] == '-') 
		{
			minus(a, b, c);
		}
		printf("%s\n", c);
	}

	return 0;
}

void plus(char *a, char *b, char *c)
{
	int aend;
	int aendc;
	int bend;
	int bendc;
	int diff;
	int end;/*����֮���λ��*/
	int ans;/*ÿһλ����Ĵ�*/
	char over = '\0';
	int set;
	int flag = 0;

	for (set = 0; set < 505; set++)
	{
		if (a[set] == '\0'&&flag == 0)
		{
			aend = set;
			flag = 1;
		}
		else
		{
			if (a[set] >= 48 && a[set] <= 57)
			{
				continue;
			}
			else
			{
				a[set] = '\0';
			}
		}
	}
	aend--;/*ȷ��a�����һλλ�� ���ɸ���*/
	flag = 0;
	for (set = 0; set < 505; set++)
	{
		if (b[set] == '\0'&&flag == 0)
		{
			bend = set;
			flag = 1;
		}
		else
		{
			if (b[set] >= 48 && b[set] <= 57)
			{
				continue;
			}
			else
			{
				b[set] = '\0';
			}
		}
	}
	bend--;/*ȷ��b�����һλλ�� ���ɸ���*/
	for (set = 0; set < 505; set++)
	{
		c[set] = '\0';
	}

	diff = aend - bend;

	/*����λ�ò�����*/
	if (diff<0)
	{
		diff = 0 - diff;
		end = bend;
		for (aendc = aend; aendc >= 0;aendc--)
		{
			a[aendc + diff] = a[aendc];
			a[aendc] = '\0';
		}

		for (; bend >= 0; bend--)
		{
			if (a[bend] == '\0')
			{
				a[bend] = '0';
			}
			ans = a[bend] + b[bend] - 96;

			if (ans >= 10)/*��Ҫ��λ*/
			{
				if (bend == 0)/*c��Ҫ��һλ*/
				{
					over = '1';
					c[bend] = (ans % 10 + 48);
				}
				else
				{
					c[bend] = (ans % 10 + 48);
					if (b[bend - 1] == '9')
					{
						int pl = bend - 1;
						for (; pl >= 0; pl--)
						{
							if (b[pl] == '9')
							{
								b[pl] = '0';
								continue;
							}
							else
							{
								b[pl] = b[pl] + 1;
								break;
							}
						}
						if (b[0] == '0')/*b������Ҫ��һλ*/
						{
							over = '1';
						}
					}
					else
					{
						b[bend - 1] = b[bend - 1] + 1;
					}
				}
			}
			else
			{
				c[bend] = ans + 48;
			}
		}

		if (over == '1')
		{
			int cpl;
			for (cpl = end; cpl >= 0; cpl--)
			{
				c[cpl + 1] = c[cpl];
				c[cpl] = '\0';
			}
			c[0] = '1';
			c[end + 2] = '\0';
		}
		else
		{
			c[end + 1] = '\0';
		}
	}
	else
	{
		end = aend;
		if (diff != 0)
		{
			for (bendc = bend; bendc >= 0; bendc--)
			{
				b[bendc + diff] = b[bendc];
				b[bendc] = '\0';
			}
		}

		for (; aend >= 0; aend--)
		{
			if (b[aend] == '\0')
			{
				b[aend] = '0';
			}
			ans = a[aend] + b[aend] - 96;

			if (ans >= 10)/*��Ҫ��λ*/
			{
				if (aend == 0)/*c��Ҫ��һλ*/
				{
					over = '1';
					c[aend] = (ans % 10 + 48);
				}
				else
				{
					c[aend] = (ans % 10 + 48);
					if (a[aend - 1] == '9')
					{
						int pl = aend - 1;
						for (; pl >= 0; pl--)
						{
							if (a[pl] == '9')
							{
								a[pl] = '0';
								continue;
							}
							else
							{
								a[pl] = a[pl] + 1;
								break;
							}
						}
						if (a[0] == '0')/*b������Ҫ��һλ*/
						{
							over = '1';
						}
					}
					else
					{
						a[aend - 1] = a[aend - 1] + 1;
					}
				}
			}
			else
			{
				c[aend] = ans + 48;
			}
		}

		if (over == '1')
		{
			int cpl;
			for (cpl = end; cpl >= 0; cpl--)
			{
				c[cpl + 1] = c[cpl];
				c[cpl] = '\0';
			}
			c[0] = '1';
			c[end + 2] = '\0';
		}
		else
		{
			c[end + 1] = '\0';
		}
	}

	for (set = 0; set < 505; set++)
	{
		a[set] = '\0';
		b[set] = '\0';
	}

	if (c[0] == '0')/*ȥ0*/
	{
		for (aend = 0; c[aend] == '0'; aend++);
		for (bend = aend; c[bend] != '\0'; bend++)
		{
			c[bend - aend] = c[bend];
			c[bend] = '\0';
		}
		c[bend - aend] = '\0';
	}

	return;
}

void minus(char *a, char *b, char *c)
{
	int aend;
	int aendc;
	int bend;
	int bendc;
	int diff;
	int end;/*����֮���λ��*/
	int ans;/*ÿһλ����Ĵ�*/
	int set;
	int flag = 0;

	if (a[0] == '0')/*ȥ��ÿ������֮ǰ���õ�0*/
	{
		for (aend = 0; a[aend] == '0'; aend++);
		for (bend = aend; a[bend] != '\0'; bend++)
		{
			a[bend - aend] = a[bend];
			a[bend] = '\0';
		}
		a[bend - aend] = '\0';
	}
	if (b[0] == '0')
	{
		for (aend = 0; b[aend] == '0'; aend++);
		for (bend = aend; b[bend] != '\0'; bend++)
		{
			b[bend - aend] = b[bend];
			b[bend] = '\0';
		}
		b[bend - aend] = '\0';
	}

	for (set = 0; set < 505; set++)
	{
		if (a[set] >= 48 && a[set] <= 57)
		{
			continue;
		}
		else
		{
			if (a[set] == '\0'&&flag == 0)
			{
				aend = set;
				flag = 1;
			}
			else
			{
				a[set] = '\0';
			}
		}
	}
	aend--;/*ȷ��a�����һλλ�� ���ɸ���*/
	flag = 0;
	for (set = 0; set < 505; set++)
	{
		if (b[set] >= 48 && b[set] <= 57)
		{
			continue;
		}
		else
		{
			if (b[set] == '\0'&&flag == 0)
			{
				bend = set;
				flag = 1;
			}
			else
			{
				b[set] = '\0';
			}
		}
	}
	bend--;/*ȷ��b�����һλλ�� ���ɸ���*/
	for (set = 0; set < 505; set++)
	{
		c[set] = '\0';
	}

	diff = aend - bend;

	/*����λ�ò�����*/
	if (diff < 0)/*aλ��С��b*/
	{
		diff = 0 - diff;
		end = bend;
		for (aendc = aend; aendc >= 0; aendc--)
		{
			a[aendc + diff] = a[aendc];
			a[aendc] = '\0';
		}

		for (; bend >= 0; bend--)
		{
			if (a[bend] == '\0')
			{
				a[bend] = '0';
			}
			ans = b[bend] - a[bend];

			if (ans < 0)/*��Ҫ��λ*/
			{
				c[bend] = (ans + 58);
				if (b[bend - 1] == '0')
				{
					int pl = bend - 1;
					for (; pl >= 0; pl--)
					{
						if (b[pl] == '0')
						{
							b[pl] = '9';
							continue;
						}
						else
						{
							b[pl] = b[pl] - 1;
							break;
						}
					}
				}
				else
				{
					b[bend - 1] = b[bend - 1] - 1;
				}
			}
			else
			{
				c[bend] = ans + 48;
			}
		}

		for (bend = end; bend >= 0; bend--)
		{
			c[bend + 1] = c[bend];
			c[bend] = '\0';
		}
		c[0] = '-';
		c[end + 2] = '\0';
	}
	else
	{
		if (diff > 0)/*aλ������b*/
		{
			end = aend;
			for (bendc = bend; bendc >= 0; bendc--)
			{
				b[bendc + diff] = b[bendc];
				b[bendc] = '\0';
			}

			for (; aend >= 0; aend--)
			{
				if (b[aend] == '\0')
				{
					b[aend] = '0';
				}
				ans = a[aend] - b[aend];

				if (ans < 0)/*��Ҫ��λ*/
				{
					c[aend] = (ans + 58);
					if (a[aend - 1] == '0')
					{
						int pl = aend - 1;
						for (; pl >= 0; pl--)
						{
							if (a[pl] == '0')
							{
								a[pl] = '9';
								continue;
							}
							else
							{
								a[pl] = a[pl] - 1;
								break;
							}
						}
					}
					else
					{
						a[aend - 1] = a[aend - 1] - 1;
					}
				}
				else
				{
					c[aend] = ans + 48;
				}
			}
			c[end + 1] = '\0';
		}
		else/*λ�����*/
		{
			end = aend;/*��¼λ��*/

			int larger = 1;/*a��ÿһλ����b��Ϊ1 ����һλС��bʱ��Ϊ0*/
			for (aend = 0; aend <= end; aend++)
			{
				if (a[aend] < b[aend])
				{
					larger = 0;
					break;
				}
				else
				{
					if (a[aend]>b[aend])
					{
						break;
					}
				}
			}

			if (larger == 0)/*��aС��b*/
			{
				for (bend = end; bend >= 0; bend--)
				{
					ans = b[bend] - a[bend];

					if (ans < 0)/*��Ҫ��λ*/
					{
						c[bend] = (ans + 58);
						if (b[bend - 1] == '0')
						{
							int pl = bend - 1;
							for (; pl >= 0; pl--)
							{
								if (b[pl] == '0')
								{
									b[pl] = '9';
									continue;
								}
								else
								{
									b[pl] = b[pl] - 1;
									break;
								}
							}
						}
						else
						{
							b[bend - 1] = b[bend - 1] - 1;
						}
					}
					else
					{
						c[bend] = ans + 48;
					}
				}

				for (bend = end; bend >= 0; bend--)
				{
					c[bend + 1] = c[bend];
					c[bend] = '\0';
				}
				c[0] = '-';
				c[end + 2] = '\0';
			}
			else/*a���ڵ���b*/
			{
				for (aend = end; aend >= 0; aend--)
				{
					ans = a[aend] - b[aend];

					if (ans < 0)/*��Ҫ��λ*/
					{
						c[aend] = (ans + 58);
						if (a[aend - 1] == '0')
						{
							int pl = aend - 1;
							for (; pl >= 0; pl--)
							{
								if (a[pl] == '0')
								{
									a[pl] = '9';
									continue;
								}
								else
								{
									a[pl] = a[pl] - 1;
									break;
								}
							}
						}
						else
						{
							a[aend - 1] = a[aend - 1] - 1;
						}
					}
					else
					{
						c[aend] = ans + 48;
					}
				}
				c[end + 1] = '\0';
			}
		}
	}
	for (set = 0; set < 505; set++)
	{
		a[set] = '\0';
		b[set] = '\0';
	}

	if (c[0] == '-')
	{
		if (c[1] == '0')/*ȥ0*/
		{
			for (aend = 1; c[aend] == '0'; aend++);
			for (bend = aend; c[bend] != '\0'; bend++)
			{
				c[bend - aend + 1] = c[bend];
				c[bend] = '\0';
			}
			c[bend - aend + 1] = '\0';
		}
	}
	else
	{
		if (c[0] == '0')
		{
			for (aend = 0; c[aend] == '0'; aend++);
			for (bend = aend; c[bend] != '\0'; bend++)
			{
				c[bend - aend] = c[bend];
				c[bend] = '\0';
			}
			c[bend - aend] = '\0';
		}
		if (c[0] == '\0')
		{
			c[0] = '0';
			c[1] = '\0';
		}
	}

	return;
}