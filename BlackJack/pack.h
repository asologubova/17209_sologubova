#pragma once

#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include<vector>
#define PACK_SIZE 52

//6 ����� �� 52 �����
//9*4(�����)*6(������) ���� � ���������: 1(���),2,3,4,5,6,7,8,9
//4*4(�����)*6(������) ���� � ���������: 10 (10, �����, ����, ������)
//char title[] = { '2','3','4','5','6','7','8','9','10','J','Q','K','A' };  //������������ �����

struct Card {
	unsigned char title = 0, //�������
		suit = 0, //�����
		weight = 0; //��� � ����
};

class Pack {
	//Mode mode;
	std::vector<Card> pack;  //������ ����
	size_t topCard;
public:
	Pack(unsigned char N = 1);
	//~Pack();
	void fullPack(unsigned char N = 1);
	Card getCard();
};