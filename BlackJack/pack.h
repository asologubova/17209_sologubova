#pragma once

#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include<vector>
#define PACK_SIZE 52

//6 колод по 52 карты
//9*4(масти)*6(колоды) карт с номиналом: 1(туз),2,3,4,5,6,7,8,9
//4*4(масти)*6(колоды) карт с номиналом: 10 (10, валет, дама, король)
//char title[] = { '2','3','4','5','6','7','8','9','10','J','Q','K','A' };  //используемые карты

struct Card {
	unsigned char title = 0, //номинал
		suit = 0, //масть
		weight = 0; //вес в игре
};

class Pack {
	//Mode mode;
	std::vector<Card> pack;  //колода карт
	size_t topCard;
public:
	Pack(unsigned char N = 1);
	//~Pack();
	void fullPack(unsigned char N = 1);
	Card getCard();
};