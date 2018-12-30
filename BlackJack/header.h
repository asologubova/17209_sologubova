//char title[] = { '2','3','4','5','6','7','8','9','10','J','Q','K','A' };  //������������ �����

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>

#define PACK_SIZE 52

//6 ����� �� 52 �����
//9*4(�����)*6(������) ���� � ���������: 1(���),2,3,4,5,6,7,8,9
//4*4(�����)*6(������) ���� � ���������: 10 (10, �����, ����, ������)

//__________________________________������_______________________________________

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
	Card *pack;  //������ ����
public:
	Pack(unsigned char N = 1, Mode m = {0, 1});
	~Pack();
	void fullPack(unsigned char N = 1);
	void shuffle(unsigned char N = 1);
};

//__________________________________����_______________________________________

class BlackJack {
private:
	

public:
	BlackJack();
	~BlackJack();
	


};