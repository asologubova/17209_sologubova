#include "pack.h"

Pack::Pack(unsigned char N) {
	std::vector<Card> pack(PACK_SIZE*N);
	topCard = 0;
	fullPack(N);
	std::random_shuffle(pack.begin(), pack.end());
}

void Pack::fullPack(unsigned char N) { //заполнение колоды
	int i = 0;
	for (; i < PACK_SIZE; i++) {
		Card card;
		card.title = (i % 13) + 2;
		card.suit = (i % 4) + 1;
		card.weight = (i % 13) + 2; //карты с числами
		if ((i % 13 > 8) && (i % 13 < 12)) //карты с картинками
			card.weight = 10;
		if (i % 13 == 12)           //туз
			card.weight = 1;
		pack[i] = card;
	}
	for (; i < PACK_SIZE*N; i++) {
		pack[i] = pack[i % PACK_SIZE];
	}
}

Card Pack::getCard() {
	return pack[topCard++];
}