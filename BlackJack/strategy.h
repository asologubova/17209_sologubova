#include <cstdio>
#include "hand.h"

class Strategy {
public:
	virtual ~Strategy() {};
	virtual bool makeDecision(const Hand & hand) = 0;
};