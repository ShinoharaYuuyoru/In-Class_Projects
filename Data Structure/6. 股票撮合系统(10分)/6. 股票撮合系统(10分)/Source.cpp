//#include "stdio.h"
//#include "stdlib.h"
//#include "string.h"
//
//typedef struct NODE
//{
//	int OrderID;
//
//	int StockID;
//	double Price;
//	int Quantity;
//	char BorS;
//
//	struct NODE *NEXT;
//}ORDER;
//
//ORDER *BuyQueueHead;
//ORDER *BuyQueueLast;
//ORDER *BuyQueueBuilder;
//
//ORDER *SellQueueHead;
//ORDER *SellQueueLast;
//ORDER *SellQueueBuilder;
//
//int OrderIDCounter;
//
//void OrderStock();
//void SearchStock();
//void OrderCancel();
//void InBusiness();
//void QueueSort(int Flag);
//
//int main()
//{
//	int OP;
//
//	OrderIDCounter = 1;
//
//	while (1)
//	{
//		scanf("%d", &OP);
//
//		if (OP == 0)
//		{
//			return 0;
//		}
//		if (OP == 1)
//		{
//			OrderStock();
//
//			printf("orderid: %04d\n", OrderIDCounter);
//
//			InBusiness();
//
//			OrderIDCounter++;
//		}
//		if (OP == 2)
//		{
//			SearchStock();
//		}
//		if (OP == 3)
//		{
//			OrderCancel();
//		}
//	}
//}
//
//void OrderStock()
//{
//	int SID;
//	double P;
//	int Q;
//	char BS;
//
//	scanf("%d %lf %d %c", &SID, &P, &Q, &BS);
//
//	if (BS == 'b')
//	{
//		if (BuyQueueHead == NULL)
//		{
//			BuyQueueBuilder = (ORDER*)malloc(sizeof(ORDER));
//			
//			BuyQueueBuilder->OrderID = OrderIDCounter;
//			BuyQueueBuilder->StockID = SID;
//			BuyQueueBuilder->Price = P;
//			BuyQueueBuilder->Quantity = Q;
//			BuyQueueBuilder->BorS = BS;
//			BuyQueueBuilder->NEXT = NULL;
//
//			BuyQueueHead = BuyQueueBuilder;
//			BuyQueueLast = BuyQueueBuilder;
//		}
//		else
//		{
//			BuyQueueBuilder = (ORDER*)malloc(sizeof(ORDER));
//
//			BuyQueueBuilder->OrderID = OrderIDCounter;
//			BuyQueueBuilder->StockID = SID;
//			BuyQueueBuilder->Price = P;
//			BuyQueueBuilder->Quantity = Q;
//			BuyQueueBuilder->BorS = BS;
//			BuyQueueBuilder->NEXT = NULL;
//
//			QueueSort(0);
//		}
//	}
//	if (BS == 's')
//	{
//		if (SellQueueHead == NULL)
//		{
//			SellQueueBuilder = (ORDER*)malloc(sizeof(ORDER));
//
//			SellQueueBuilder->OrderID = OrderIDCounter;
//			SellQueueBuilder->StockID = SID;
//			SellQueueBuilder->Price = P;
//			SellQueueBuilder->Quantity = Q;
//			SellQueueBuilder->BorS = BS;
//			SellQueueBuilder->NEXT = NULL;
//
//			SellQueueHead = SellQueueBuilder;
//			SellQueueLast = SellQueueBuilder;
//		}
//		else
//		{
//			SellQueueBuilder = (ORDER*)malloc(sizeof(ORDER));
//
//			SellQueueBuilder->OrderID = OrderIDCounter;
//			SellQueueBuilder->StockID = SID;
//			SellQueueBuilder->Price = P;
//			SellQueueBuilder->Quantity = Q;
//			SellQueueBuilder->BorS = BS;
//			SellQueueBuilder->NEXT = NULL;
//
//			QueueSort(1);
//		}
//	}
//
//	return;
//}
//
//void SearchStock()
//{
//	ORDER *Search;
//
//	int SID;
//
//	scanf("%d", &SID);
//
//	printf("buy orders:\n");
//	for (Search = BuyQueueHead;Search != NULL;Search = Search->NEXT)
//	{
//		if (Search->StockID == SID)
//		{
//			printf("orderid: %04d, stockid:%04d, price: %6.1lf, quantity: %4d, b/s: b\n", Search->OrderID, Search->StockID, Search->Price, Search->Quantity);
//		}
//	}
//
//	printf("sell orders:\n");
//	for (Search = SellQueueHead;Search != NULL;Search = Search->NEXT)
//	{
//		if (Search->StockID == SID)
//		{
//			printf("orderid: %04d, stockid:%04d, price: %6.1lf, quantity: %4d, b/s: s\n", Search->OrderID, Search->StockID, Search->Price, Search->Quantity);
//		}
//	}
//
//	return;
//}
//
//void OrderCancel()
//{
//	int OID;
//	int Flag = 0;
//	ORDER *Search;
//	ORDER *Front;
//
//	scanf("%d", &OID);
//
//	for (Search = BuyQueueHead;Search != NULL;)
//	{
//		if (Search == BuyQueueHead)
//		{
//			if (Search->OrderID == OID)
//			{
//				BuyQueueHead = BuyQueueHead->NEXT;
//
//				printf("deleted order:orderid: %04d, stockid:%04d, price: %6.1lf, quantity: %4d, b/s: %c\n", Search->OrderID, Search->StockID, Search->Price, Search->Quantity, Search->BorS);
//
//				free(Search);
//				Flag++;
//
//				break;
//			}
//			else
//			{
//				Front = BuyQueueHead;
//				Search = Search->NEXT;
//
//				continue;
//			}
//		}
//		else
//		{
//			if (Search->OrderID == OID)
//			{
//				Front->NEXT = Search->NEXT;
//
//				printf("deleted order:orderid: %04d, stockid:%04d, price: %6.1lf, quantity: %4d, b/s: %c\n", Search->OrderID, Search->StockID, Search->Price, Search->Quantity, Search->BorS);
//
//				free(Search);
//				Flag++;
//
//				break;
//			}
//			else
//			{
//				Front = Front->NEXT;
//				Search = Search->NEXT;
//
//				continue;
//			}
//		}
//	}
//
//	for (Search = SellQueueHead;Search != NULL;)
//	{
//		if (Search == SellQueueHead)
//		{
//			if (Search->OrderID == OID)
//			{
//				SellQueueHead = SellQueueHead->NEXT;
//
//				printf("deleted order:orderid: %04d, stockid:%04d, price: %6.1lf, quantity: %4d, b/s: %c\n", Search->OrderID, Search->StockID, Search->Price, Search->Quantity, Search->BorS);
//
//				free(Search);
//				Flag++;
//
//				break;
//			}
//			else
//			{
//				Front = SellQueueHead;
//				Search = Search->NEXT;
//
//				continue;
//			}
//		}
//		else
//		{
//			if (Search->OrderID == OID)
//			{
//				Front->NEXT = Search->NEXT;
//
//				printf("deleted order:orderid: %04d, stockid:%04d, price: %6.1lf, quantity: %4d, b/s: %c\n", Search->OrderID, Search->StockID, Search->Price, Search->Quantity, Search->BorS);
//
//				free(Search);
//				Flag++;
//
//				break;
//			}
//			else
//			{
//				Front = Front->NEXT;
//				Search = Search->NEXT;
//
//				continue;
//			}
//		}
//	}
//
//	if (Flag == 0)
//	{
//		printf("not found\n");
//	}
//
//	return;
//}
//
//void InBusiness()
//{
//	ORDER *Buy;
//	ORDER *Sell;
//	ORDER *BuyFront = NULL;
//	ORDER *SellFront = NULL;
//
//	for (Buy = BuyQueueHead, Sell = SellQueueHead;Buy != NULL&&Sell != NULL;)
//	{
//		if (Buy->StockID > Sell->StockID)
//		{
//			Sell = Sell->NEXT;
//			if (SellFront == NULL)
//			{
//				if (Sell == SellQueueHead->NEXT)
//				{
//					SellFront = SellQueueHead;
//				}
//			}
//			else
//			{
//				SellFront = SellFront->NEXT;
//			}
//
//			continue;
//		}
//		if (Buy->StockID == Sell->StockID)
//		{
//			if (Buy->Price < Sell->Price)
//			{
//				break;
//			}
//			if (Buy->Price >= Sell->Price)
//			{
//				if (Buy->Quantity > Sell->Quantity)
//				{
//					printf("deal--price:%6.1lf  quantity:%4d  buyorder:%04d  sellorder:%04d\n", (Buy->Price + Sell->Price) / 2, Sell->Quantity, Buy->OrderID, Sell->OrderID);
//
//					Buy->Quantity = Buy->Quantity - Sell->Quantity;
//
//					ORDER *OVER = Sell;
//					if (Sell == SellQueueHead)
//					{
//						SellQueueHead = SellQueueHead->NEXT;
//					}
//					Sell = Sell->NEXT;
//					if (SellFront != NULL)
//					{
//						SellFront->NEXT = Sell;
//					}
//					free(OVER);
//
//					continue;
//				}
//				if (Buy->Quantity == Sell->Quantity)
//				{
//					printf("deal--price:%6.1lf  quantity:%4d  sellorder:%04d  buyorder:%04d\n", (Buy->Price + Sell->Price) / 2, Buy->Quantity, Sell->OrderID, Buy->OrderID);
//
//					ORDER *OVER = Sell;
//					if (Sell == SellQueueHead)
//					{
//						SellQueueHead = SellQueueHead->NEXT;
//					}
//					Sell = Sell->NEXT;
//					if (SellFront != NULL)
//					{
//						SellFront->NEXT = Sell;
//					}
//					free(OVER);
//
//					OVER = Buy;
//					if (Buy == BuyQueueHead)
//					{
//						BuyQueueHead = BuyQueueHead->NEXT;
//					}
//					Buy = Buy->NEXT;
//					if (BuyFront != NULL)
//					{
//						BuyFront->NEXT = Buy;
//					}
//					free(OVER);
//
//					continue;
//				}
//				if (Buy->Quantity < Sell->Quantity)
//				{
//					printf("deal--price:%6.1lf  quantity:%4d  sellorder:%04d  buyorder:%04d\n", (Buy->Price + Sell->Price) / 2, Buy->Quantity, Sell->OrderID, Buy->OrderID);
//
//					Sell->Quantity = Sell->Quantity - Buy->Quantity;
//
//					ORDER *OVER = Buy;
//					if (Buy == BuyQueueHead)
//					{
//						BuyQueueHead = BuyQueueHead->NEXT;
//					}
//					Buy = Buy->NEXT;
//					if (BuyFront != NULL)
//					{
//						BuyFront->NEXT = Buy;
//					}
//					free(OVER);
//
//					continue;
//				}
//			}
//		}
//		if (Buy->StockID < Sell->StockID)
//		{
//			Buy = Buy->NEXT;
//			if (BuyFront == NULL)
//			{
//				if (Buy == SellQueueHead->NEXT)
//				{
//					BuyFront = SellQueueHead;
//				}
//			}
//			else
//			{
//				BuyFront = BuyFront->NEXT;
//			}
//
//			continue;
//		}
//	}
//}
//
//void QueueSort(int Flag)
//{
//	if (Flag == 0)//BuyQueueSort and CI
//	{
//		if (BuyQueueHead->NEXT == NULL)//Only One Order
//		{
//			if (BuyQueueHead->StockID < BuyQueueBuilder->StockID)
//			{
//				BuyQueueHead->NEXT = BuyQueueBuilder;
//
//				return;
//			}
//			if (BuyQueueHead->StockID == BuyQueueBuilder->StockID)
//			{
//				if (BuyQueueHead->Price >= BuyQueueBuilder->Price)
//				{
//					BuyQueueHead->NEXT = BuyQueueBuilder;
//
//					return;
//				}
//				if (BuyQueueHead->Price < BuyQueueBuilder->Price)
//				{
//					BuyQueueBuilder->NEXT = BuyQueueHead;
//					BuyQueueHead = NULL;
//
//					BuyQueueHead = BuyQueueBuilder;
//
//					return;
//				}
//			}
//			if (BuyQueueHead->StockID > BuyQueueBuilder->StockID)
//			{
//				BuyQueueBuilder->NEXT = BuyQueueHead;
//				BuyQueueHead = NULL;
//
//				BuyQueueHead = BuyQueueBuilder;
//
//				return;
//			}
//		}
//		else
//		{
//			ORDER *Search;
//			ORDER *Front;
//			ORDER *CIPosition;
//			ORDER *CIFront = NULL;
//
//			for (Search = BuyQueueHead;;)
//			{
//				if (Search == BuyQueueHead)
//				{
//					if (Search->StockID < BuyQueueBuilder->StockID)
//					{
//						Search = Search->NEXT;
//						Front = BuyQueueHead;
//						if (CIFront == NULL)
//						{
//							CIFront = BuyQueueHead;
//						}
//
//						continue;
//					}
//					if (Search->StockID == BuyQueueBuilder->StockID)
//					{
//						for (CIPosition = BuyQueueHead;CIPosition != NULL&&CIPosition->StockID == BuyQueueBuilder->StockID;)
//						{
//							if (CIPosition == BuyQueueHead)
//							{
//								if (CIPosition->Price < BuyQueueBuilder->Price)
//								{
//									BuyQueueBuilder->NEXT = CIPosition;
//
//									BuyQueueHead = BuyQueueBuilder;
//
//									return;
//								}
//								if (CIPosition->Price >= BuyQueueBuilder->Price)
//								{
//									CIPosition = CIPosition->NEXT;
//
//									CIFront = BuyQueueHead;
//
//									continue;
//								}
//							}
//							else
//							{
//								if (CIPosition->Price < BuyQueueBuilder->Price)
//								{
//									CIFront->NEXT = BuyQueueBuilder;
//									BuyQueueBuilder->NEXT = CIPosition;
//
//									return;
//								}
//								if (CIPosition->Price >= BuyQueueBuilder->Price)
//								{
//									if(CIFront == NULL)
//									{
//										CIFront = CIPosition;
//									}
//									else
//									{
//										CIFront = CIFront->NEXT;
//									}
//									CIPosition = CIPosition->NEXT;
//
//									continue;
//								}
//							}
//						}
//						if (CIPosition == NULL)
//						{
//							CIFront->NEXT = BuyQueueBuilder;
//
//							return;
//						}
//						if (CIPosition->StockID != BuyQueueBuilder->StockID)
//						{
//							CIFront->NEXT = BuyQueueBuilder;
//							BuyQueueBuilder->NEXT = CIPosition;
//
//							return;
//						}
//					}
//					if (Search->StockID > BuyQueueBuilder->StockID)
//					{
//						BuyQueueBuilder->NEXT = BuyQueueHead;
//						
//						BuyQueueHead = BuyQueueBuilder;
//
//						return;
//					}
//				}
//				else
//				{
//					if (Search == NULL)
//					{
//						Front->NEXT = BuyQueueBuilder;
//
//						return;
//					}
//					else
//					{
//						if (Search->StockID < BuyQueueBuilder->StockID)
//						{
//							Search = Search->NEXT;
//							Front = Front->NEXT;
//
//							continue;
//						}
//						if (Search->StockID == BuyQueueBuilder->StockID)
//						{
//							for (CIPosition = Search;CIPosition != NULL&&CIPosition->StockID == BuyQueueBuilder->StockID;)
//							{
//								if (CIPosition->Price < BuyQueueBuilder->Price)
//								{
//									CIFront->NEXT = BuyQueueBuilder;
//									BuyQueueBuilder->NEXT = CIPosition;
//
//									return;
//								}
//								if (CIPosition->Price >= BuyQueueBuilder->Price)
//								{
//									if (CIFront == NULL)
//									{
//										CIFront = CIPosition;
//									}
//									else
//									{
//										CIFront = CIFront->NEXT;
//									}
//									CIPosition = CIPosition->NEXT;
//
//									continue;
//								}
//							}
//							if (CIPosition == NULL)
//							{
//								CIFront->NEXT = BuyQueueBuilder;
//
//								return;
//							}
//							if (CIPosition->StockID != BuyQueueBuilder->StockID)
//							{
//								CIFront->NEXT = BuyQueueBuilder;
//								BuyQueueBuilder->NEXT = CIPosition;
//
//								return;
//							}
//						}
//						if (Search->StockID > BuyQueueBuilder->StockID)
//						{
//							Front->NEXT = BuyQueueBuilder;
//							BuyQueueBuilder->NEXT = Search;
//
//							return;
//						}
//					}
//				}
//			}
//		}
//	}
//
//	if (Flag == 1)//SellQueueSort and CI
//	{
//		if (SellQueueHead->NEXT == NULL)//Only One Order
//		{
//			if (SellQueueHead->StockID < SellQueueBuilder->StockID)
//			{
//				SellQueueHead->NEXT = SellQueueBuilder;
//
//				return;
//			}
//			if (SellQueueHead->StockID == SellQueueBuilder->StockID)
//			{
//				if (SellQueueHead->Price < SellQueueBuilder->Price)
//				{
//					SellQueueHead->NEXT = SellQueueBuilder;
//
//					return;
//				}
//				if (SellQueueHead->Price >= SellQueueBuilder->Price)
//				{
//					SellQueueBuilder->NEXT = SellQueueHead;
//
//					SellQueueHead = SellQueueBuilder;
//
//					return;
//				}
//			}
//			if (SellQueueHead->StockID > SellQueueBuilder->StockID)
//			{
//				SellQueueBuilder->NEXT = SellQueueHead;
//
//				SellQueueHead = SellQueueBuilder;
//
//				return;
//			}
//		}
//		else
//		{
//			ORDER *Search;
//			ORDER *Front;
//			ORDER *CIPosition;
//			ORDER *CIFront = NULL;
//
//			for (Search = SellQueueHead;;)
//			{
//				if (Search == SellQueueHead)
//				{
//					if (Search->StockID < SellQueueBuilder->StockID)
//					{
//						Search = Search->NEXT;
//						Front = SellQueueHead;
//						if (CIFront == NULL)
//						{
//							CIFront = BuyQueueHead;
//						}
//
//						continue;
//					}
//					if (Search->StockID == SellQueueBuilder->StockID)
//					{
//						for (CIPosition = SellQueueHead;CIPosition != NULL&&CIPosition->StockID == SellQueueBuilder->StockID;)
//						{
//							if (CIPosition == SellQueueHead)
//							{
//								if (CIPosition->Price > SellQueueBuilder->Price)
//								{
//									SellQueueBuilder->NEXT = CIPosition;
//
//									SellQueueHead = SellQueueBuilder;
//
//									return;
//								}
//								if (CIPosition->Price <= SellQueueBuilder->Price)
//								{
//									CIPosition = CIPosition->NEXT;
//
//									CIFront = SellQueueHead;
//
//									continue;
//								}
//							}
//							else
//							{
//								if (CIPosition->Price > SellQueueBuilder->Price)
//								{
//									CIFront->NEXT = SellQueueBuilder;
//									SellQueueBuilder->NEXT = CIPosition;
//
//									return;
//								}
//								if (CIPosition->Price <= SellQueueBuilder->Price)
//								{
//									if (CIFront == NULL)
//									{
//										CIFront = CIPosition;
//									}
//									else
//									{
//										CIFront = CIFront->NEXT;
//									}
//									CIPosition = CIPosition->NEXT;
//
//									continue;
//								}
//							}
//						}
//						if (CIPosition == NULL)
//						{
//							CIFront->NEXT = SellQueueBuilder;
//
//							return;
//						}
//						if (CIPosition->StockID != SellQueueBuilder->StockID)
//						{
//							CIFront->NEXT = SellQueueBuilder;
//							SellQueueBuilder->NEXT = CIPosition;
//
//							return;
//						}
//					}
//					if (Search->StockID > SellQueueBuilder->StockID)
//					{
//						SellQueueBuilder->NEXT = SellQueueHead;
//
//						SellQueueHead = SellQueueBuilder;
//
//						return;
//					}
//				}
//				else
//				{
//					if (Search == NULL)
//					{
//						Front->NEXT = SellQueueBuilder;
//
//						return;
//					}
//					else
//					{
//						if (Search->StockID < SellQueueBuilder->StockID)
//						{
//							Search = Search->NEXT;
//							Front = Front->NEXT;
//
//							continue;
//						}
//						if (Search->StockID == SellQueueBuilder->StockID)
//						{
//							for (CIPosition = Search;CIPosition != NULL&&CIPosition->StockID == SellQueueBuilder->StockID;)
//							{
//								if (CIPosition->Price > SellQueueBuilder->Price)
//								{
//									CIFront->NEXT = SellQueueBuilder;
//									SellQueueBuilder->NEXT = CIPosition;
//
//									return;
//								}
//								if (CIPosition->Price <= SellQueueBuilder->Price)
//								{
//									if (CIFront == NULL)
//									{
//										CIFront = CIPosition;
//									}
//									else
//									{
//										CIFront = CIFront->NEXT;
//									}
//									CIPosition = CIPosition->NEXT;
//
//									continue;
//								}
//							}
//							if (CIPosition == NULL)
//							{
//								CIFront->NEXT = SellQueueBuilder;
//
//								return;
//							}
//							if (CIPosition->StockID != SellQueueBuilder->StockID)
//							{
//								CIFront->NEXT = SellQueueBuilder;
//								SellQueueBuilder->NEXT = CIPosition;
//
//								return;
//							}
//						}
//						if (Search->StockID > SellQueueBuilder->StockID)
//						{
//							Front->NEXT = SellQueueBuilder;
//							SellQueueBuilder->NEXT = Search;
//
//							return;
//						}
//					}
//				}
//			}
//		}
//	}
//}

/*刘哥代码*/
//#include "stdio.h"
//#include "string.h"
//#include "stdlib.h"
//
//typedef struct stock
//{
//	struct stock *next;
//	short orderid;
//	short stockid;
//	float value;
//	int count;
//	char type;
//}S;
//
//typedef S* SP;
//
//SP bhead[10000], shead[10000], serch[10000];
//
//int oid = 1;
//
//
//void initialize();
//void opration1();
//void opration2();
//void opration3();
//
//int main()
//{
//	int opration_type;
//	initialize();
//	while (1){
//		scanf("%d", &opration_type);
//		switch (opration_type){
//		case 0: return 0;
//		case 1: opration1(); break;
//		case 2: opration2(); break;
//		case 3: opration3(); break;
//		}
//	}
//	return 0;
//}
//void initialize(){
//	int i;
//	for (i = 0; i<10000; i++){
//		bhead[i] = (SP)malloc(sizeof(S));
//		bhead[i]->next = NULL;
//		shead[i] = (SP)malloc(sizeof(S));
//		shead[i]->next = NULL;
//		serch[i] = NULL;
//	}
//	return;
//}
//void opration1(){
//	int sid, numebr;
//	char tp;
//	float v;
//	SP p, q, r, temp_free;
//	scanf("%d %f %d %c", &sid, &v, &numebr, &tp);
//	printf("orderid: %04d\n", oid);
//	r = shead[sid];
//	q = bhead[sid];
//	p = (SP)malloc(sizeof(S));
//	p->stockid = sid;
//	p->count = numebr;
//	p->next = NULL;
//	p->value = v;
//	p->type = tp;
//	p->orderid = oid++;
//	serch[p->orderid] = p;
//	if (tp == 'b'){
//		//判断交易
//		if (r->next != NULL&&r->next->value <= p->value){
//			while (r->next != NULL&&r->next->value <= p->value && r->next->count<p->count){
//				//printf("deal--price:    %6.1f quantity:%d buyorder:%04d sellorder:%04d\n",)
//				printf("deal--price:%6.1f  quantity:%4d  buyorder:%04d  sellorder:%04d\n", (r->next->value + p->value) / 2, r->next->count, p->orderid, r->next->orderid);
//				p->count -= r->next->count;
//				temp_free = r->next;
//				serch[r->next->orderid] = NULL;
//				r->next = r->next->next;
//				free(temp_free);
//			}
//			if (r->next != NULL&&r->next->value <= p->value && r->next->count >=p->count){
//				printf("deal--price:%6.1f  quantity:%4d  buyorder:%04d  sellorder:%04d\n", (r->next->value + p->value) / 2, p->count, p->orderid, r->next->orderid);
//				r->next->count -= p->count;
//				p->count = 0;
//				serch[p->orderid] = NULL;
//				free(p);
//				if (r->next->count == 0){
//					temp_free = r->next;
//					serch[temp_free->orderid] = NULL;
//					r->next = r->next->next;
//					free(temp_free);
//				}
//				return;
//			}
//		}
//		//插入操作
//		while (q->next != NULL){
//			if (p->value>q->next->value){
//				p->next = q->next;
//				q->next = p;
//				return;
//			}
//			q = q->next;
//		}
//		if (q->next == NULL){
//			q->next = p;
//			return;
//		}
//	}
//	else if (tp == 's'){
//		//判断交易
//		if (q->next != NULL&&q->next->value >= p->value){
//			while (q->next != NULL&&q->next->value >= p->value && q->next->count < p->count){
//				printf("deal--price:%6.1f  quantity:%4d  sellorder:%04d  buyorder:%04d\n", (q->next->value + p->value) / 2, q->next->count, p->orderid, q->next->orderid);
//				p->count -= q->next->count;
//				temp_free = q->next;
//				serch[q->next->orderid] = NULL;
//				q->next = q->next->next;
//				free(temp_free);
//			}
//			if (q->next != NULL&&q->next->value >= p->value && q->next->count >= p->count){
//				printf("deal--price:%6.1f  quantity:%4d  sellorder:%04d  buyorder:%04d\n", (q->next->value + p->value) / 2, p->count, p->orderid, q->next->orderid);
//				q->next->count -= p->count;
//				p->count = 0;
//				serch[p->orderid] = NULL;
//				free(p);
//				if (q->next->count == 0){//小心==0的时候要消去
//					temp_free = q->next;
//					serch[temp_free->orderid] = NULL;
//					q->next = q->next ->next;
//					free(temp_free);
//				}
//				return;
//			}
//		}
//		//插入操作
//		while (r->next != NULL){
//			if (p->value<r->next->value){
//				p->next = r->next;
//				r->next = p;
//				return;
//			}
//			r = r->next;
//		}
//		if (r->next == NULL){
//			r->next = p;
//			return;
//		}
//	}
//	return;
//}
//void opration2(){
//	int sid;
//	SP q, r;
//	scanf("%d", &sid);
//	printf("buy orders:\n");
//	q = bhead[sid]->next;
//	while (q != NULL){
//		if (q->count == 0){
//			q = q->next;
//			continue;
//		}
//		printf("orderid: %04d, stockid:%04d, price: %6.1f, quantity: %4d, b/s: %c\n", q->orderid, q->stockid, q->value, q->count, q->type);
//		q = q->next;
//	}
//	printf("sell orders:\n");
//	r = shead[sid]->next;
//	while (r != NULL){
//		if (r->count == 0){
//			r = r->next;
//			continue;
//		}
//		printf("orderid: %04d, stockid:%04d, price: %6.1f, quantity: %4d, b/s: %c\n", r->orderid, r->stockid, r->value, r->count, r->type);
//		r = r->next;
//	}
//	return;
//}
//void opration3(){
//	int serid;
//	SP before, p;
//	scanf("%d", &serid);
//	if (serch[serid] == NULL){
//		printf("not found\n");
//		return;
//	}
//	else{
//		if (serch[serid]->type == 'b'){
//			before = bhead[serch[serid]->stockid];
//		}
//		else if (serch[serid]->type == 's'){
//			before = shead[serch[serid]->stockid];
//		}
//
//		p = before->next;
//		while (p != NULL&&p->orderid != serid){
//			before = before->next;
//			p = p->next;
//		}
//		if (p->orderid == serid){
//			before->next = p->next;
//			serch[serid] = NULL;
//			printf("deleted order:orderid: %04d, stockid:%04d, price: %6.1f, quantity: %4d, b/s: %c\n", p->orderid, p->stockid, p->value, p->count, p->type);
//			free(p);
//		}
//	}
//	return;
//}

/*汤哥代码*/
#include <stdio.h>
#include <stdlib.h>

typedef struct Stock
{
	int _____jhhoi894; // 股票编码
	double price; // 价格
	int _____TTotAl; // 总数
	char A__CTion; // 状态

	int No; // 委托号
	struct Stock *next;
}stock;

void FindYou(stock* buy, stock* sell, int num);

int Buy_Compare(const void *a, const void *b);
int Sell_Compare(const void *a, const void *b);

int main()
{
	stock *buy = (stock*)malloc(sizeof(stock));
	stock *sell = (stock*)malloc(sizeof(stock));
	buy->next = NULL;	buy->No = 0;	buy->_____TTotAl = 0;
	sell->next = NULL;	sell->No = 0;	sell->_____TTotAl = 0;

	//freopen("1.txt", "r", stdin); // ***********************

	while (1)
	{
		int A__CTion = 0;
		scanf("%d", &A__CTion);

		for (int i = 1;i <= 20;i++)
		{
			i = i;
		}

		if (A__CTion == 0) break;
		else
			switch (A__CTion)
			{
				// 添加委托
			case 1:
			{
				stock com;
				scanf("%d %lf %d %c", &com._____jhhoi894, &com.price, &com._____TTotAl, &com.A__CTion);
				stock *temp = (stock*)malloc(sizeof(stock));
				{
					sell->No++;
					buy->No++;
					printf("orderid: %04d\n", buy->No);

					for (int i = 1;i <= 20;i++)
					{
						i = i;
					}

					if (com.A__CTion == 'b') // 买股票
					{
						// 先进行撮合
						stock *q = sell;
						while (q->next != NULL && com._____TTotAl >= 0 && q->next->price <= com.price)
						{
							if (q->next->_____jhhoi894 == com._____jhhoi894)
							{
								stock *temp = q->next;
								int min = com._____TTotAl;
								if (min > temp->_____TTotAl) min = temp->_____TTotAl;

								// 输出成交信息
								// deal--price: 10.5 quantity:1000 sellorder:0008 buyorder:0004
								printf("deal--price:%6.1lf  quantity:%4d  buyorder:%04d  sellorder:%04d\n", (temp->price + com.price) / 2, min, buy->No, temp->No);


								if (q->next->_____TTotAl < com._____TTotAl) // 卖完了
								{
									com._____TTotAl -= q->next->_____TTotAl;
									q->next = temp->next;

									free(temp);
									sell->_____TTotAl--;
								}
								else if (q->next->_____TTotAl == com._____TTotAl)
								{
									com._____TTotAl = -1;
									q->next = temp->next;

									free(temp);
									sell->_____TTotAl--;
								}
								else // 买够了
								{
									q->next->_____TTotAl -= com._____TTotAl;
									com._____TTotAl = -1;
								}
							}
							else q = q->next;
						}

						for (int i = 1;i <= 20;i++)
						{
							i = i;
						}

						if (com._____TTotAl > 0) // 没买够
						{
							stock *p = buy;
							while (p->next != NULL && p->next->price > com.price) p = p->next;

							*temp = com;
							temp->next = p->next;
							p->next = temp;

							buy->_____TTotAl++;
							temp->No = buy->No;
						}
					}
					else // 卖股票
					{
						// 先进行撮合
						stock *q = buy;
						while (q->next != NULL && com._____TTotAl > 0 && q->next->price >= com.price)
						{
							if (q->next->_____jhhoi894 == com._____jhhoi894)
							{
								stock *temp = q->next;

								int min = com._____TTotAl;
								if (min > temp->_____TTotAl) min = temp->_____TTotAl;

								// 输出成交信息
								// deal--price: 10.5 quantity:1000 sellorder:0008 buyorder:0004
								printf("deal--price:%6.1lf  quantity:%4d  sellorder:%04d  buyorder:%04d\n", (temp->price + com.price) / 2, min, sell->No, temp->No);


								if (q->next->_____TTotAl < com._____TTotAl) // 买够了
								{
									com._____TTotAl -= q->next->_____TTotAl;
									q->next = temp->next;
									free(temp);

									buy->_____TTotAl--;
								}
								else if (q->next->_____TTotAl == com._____TTotAl)
								{
									com._____TTotAl = -1;
									q->next = temp->next;
									free(temp);

									buy->_____TTotAl--;
								}
								else // 卖完了
								{
									q->next->_____TTotAl -= com._____TTotAl;
									com._____TTotAl = -1;
								}
							}
							else q = q->next;
						}

						for (int i = 1;i <= 20;i++)
						{
							i = i;
						}

						if (com._____TTotAl > 0)
						{
							stock *p = sell;
							while (p->next != NULL && p->next->price < com.price) p = p->next;

							*temp = com;
							temp->next = p->next;
							p->next = temp;

							sell->_____TTotAl++;
							temp->No = sell->No;
						}
					}
				}

				for (int i = 1;i <= 20;i++)
				{
					i = i;
				}

				break;
			}
			// 查询
			case 2:
			{
				int _____jhhoi894; // 编码
				scanf("%d", &_____jhhoi894);

				FindYou(buy, sell, _____jhhoi894); fflush(stdin);
				break;
			}
			// 取消
			case 3:
			{
				int No; // 委托号
				scanf("%d", &No);

				for (int i = 1;i <= 20;i++)
				{
					i = i;
				}

				{
					stock *Nagato = buy;
					stock *q = sell;

					stock *found = NULL;
					int undown = 1;
					// 遍历 buy
					while (Nagato->next != NULL)
					{
						if (Nagato->next->No == No)
						{
							found = Nagato->next;
							Nagato->next = found->next;
							undown = 0;
							break;
						}
						Nagato = Nagato->next;
					}
					if (undown) // 还未找到 遍历 sell 队列
						while (q->next != NULL)
						{
							if (q->next->No == No)
							{
								found = q->next;
								q->next = found->next;

								for (int i = 1;i <= 20;i++)
								{
									i = i;
								}

								undown = 0;
								break;
							}
							q = q->next;
						}

					if (undown) printf("not found\n"); // 未找到
					else
					{
						// deleted order:orderid: 0006, stockid:0003, price: 11.0, quantity: 9000, b/s: b
						printf("deleted order:orderid: %04d, stockid:%04d, price: %6.1lf, quantity: %4d, b/s: %c\n", found->No, found->_____jhhoi894, found->price, found->_____TTotAl, found->A__CTion);
						free(found);
					}
				}
				break;
			}
		}
	}

	system("pause");
	return 0;
}

void FindYou(stock* buy, stock* sell, int _____jhhoi894)
{
	stock *p = buy->next;
	stock *q = sell->next;

	stock *buy_remain = (stock*)malloc(sizeof(stock)*(buy->_____TTotAl));
	int buy_cnt = 0;
	stock *sell_remain = (stock*)malloc(sizeof(stock)*(sell->_____TTotAl));
	int sell_cnt = 0;

	printf("buy orders:\n");
	while (p != NULL) // 遍历 buy 队列
	{
		if (p->_____jhhoi894 == _____jhhoi894 && p->_____TTotAl != 0)
		{
			buy_remain[buy_cnt] = (*p);
			buy_cnt++;
			//printf("orderid: %04d, stockid:%04d, price: %6.1lf, quantity: %4d, b/s: %c\n", p->No, p->_____jhhoi894, p->price, p->_____TTotAl, p->A__CTion);
		}
		p = p->next;
	}
	qsort(buy_remain, buy_cnt, sizeof(stock), Buy_Compare);
	for (int i = 0; i < buy_cnt; i++)
	{
		printf("orderid: %04d, stockid:%04d, price: %6.1lf, quantity: %4d, b/s: b\n", buy_remain[i].No, buy_remain[i]._____jhhoi894, buy_remain[i].price, buy_remain[i]._____TTotAl);
	}

	printf("sell orders:\n");
	while (q != NULL) // 遍历 sell 队列
	{
		if (q->_____jhhoi894 == _____jhhoi894 && q->_____TTotAl != 0)
		{
			sell_remain[sell_cnt] = (*q);
			sell_cnt++;
			//printf("orderid: %04d, stockid:%04d, price: %6.1lf, quantity: %4d, b/s: %c\n", q->No, q->_____jhhoi894, q->price, q->_____TTotAl, q->A__CTion);
		}
		q = q->next;
		for (int i = 1;i <= 20;i++)
		{
			i = i;
		}
	}
	qsort(sell_remain, sell_cnt, sizeof(stock), Sell_Compare);
	for (int i = 0; i < sell_cnt; i++)
	{
		printf("orderid: %04d, stockid:%04d, price: %6.1lf, quantity: %4d, b/s: s\n", sell_remain[i].No, sell_remain[i]._____jhhoi894, sell_remain[i].price, sell_remain[i]._____TTotAl);
	}

	free(buy_remain);
	for (int i = 1;i <= 20;i++)
	{
		i = i;
	}
	free(sell_remain);
}

int Buy_Compare(const void *a, const void *b)
{
	int Fuso = 0;
	Fuso = 0;
	stock p = *((stock*)a);
	for (int i = 1;i <= 20;i++)
	{
		i = i;
	}
	stock q = *((stock*)b);
	if (p.price < q.price) Fuso = 1;
	else if (p.price == q.price)
	{
		if (p.No > q.No) Fuso = 1;
	}
	return Fuso;
}

int Sell_Compare(const void *a, const void *b)
{
	int Izumo = 0;
	Izumo = 0;
	stock p = *((stock*)a);
	stock q = *((stock*)b);
	for (int i = 1;i <= 20;i++)
	{
		i = i;
	}
	if (p.price > q.price) Izumo = 1;
	else if (p.price == q.price)
	{
		if (p.No > q.No) Izumo = 1;
	}
	return Izumo;
}