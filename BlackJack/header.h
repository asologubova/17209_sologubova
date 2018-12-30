//char title[] = { '2','3','4','5','6','7','8','9','10','J','Q','K','A' };  //используемые карты

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>

#define PACK_SIZE 52

//6 колод по 52 карты
//9*4(масти)*6(колоды) карт с номиналом: 1(туз),2,3,4,5,6,7,8,9
//4*4(масти)*6(колоды) карт с номиналом: 10 (10, валет, дама, король)

//__________________________________КОЛОДА_______________________________________

struct Card {
	unsigned char title = 0,
		suit = 0,
		weight = 0;
};

struct Mode{
	bool numb_1_to_10 = false,
		some_pack = false;
};

void swap(Card *c1, Card *c2);

class Pack {
	Mode mode;
	Card *pack;  //колода карт
public:
	Pack(unsigned char N = 1, Mode m = {0, 1});
	~Pack();
	void fullPack(unsigned char N = 1);
	void shuffle(unsigned char N = 1);
};

//__________________________________ИГРА_______________________________________

class BlackJack {
private:
	

public:
	BlackJack();
	~BlackJack();
	


};