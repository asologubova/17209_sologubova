#include "header.h"

void swap(Card *c1, Card *c2) { // для тасовки клоды
	Card tmp = *c1;
	*c1 = *c2;
	*c2 = tmp;
}

Pack::Pack(unsigned char N = 1, Mode m = { 0, 1 }) {
	if ((m.numb_1_to_10 == 1) && (m.some_pack == 0)) {
		pack = new Card[10];
	}
	else
		pack = new Card[PACK_SIZE*N];
	fullPack(N);
	shuffle(N);
}

Pack::~Pack() {
	delete[] pack;
}

void Pack::fullPack(unsigned char N = 1) { //создние колоды
	int i = 0;
	for (; i < PACK_SIZE; i++) {
		Card card;
		card.title = (i % 13) + 2;
		card.suit = (i % 4) + 1;
		card.weight = (i % 13) + 2; //карты с чисами
		if ((i % 13 > 8) && (i % 13 < 12)) //карты с картинкой
			card.weight = 10;
		if (i % 13 == 12) //туз
			card.weight = 1;
		pack[i] = card;
	}
	for (; i < PACK_SIZE*N; i++) {
		pack[i] = pack[i % PACK_SIZE];
	}
}


void Pack::shuffle(unsigned char N = 1) { //тасовка колоды
	srand(time(0));
	for (int i = 0; i < PACK_SIZE * N; i++) {
		swap(&pack[i], &pack[rand() % (PACK_SIZE * N)]);
	}
}