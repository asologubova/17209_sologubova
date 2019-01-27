#pragma once

#include <map>
#include <string>

#include "strategy.h"

//class Strategy;

template<class Id, class CreatedType>
class Factory {
public:
	CreatedType * createStrategyByID(const Id & id) {
		auto it = creators.find(id);
		if (creators.end() == it) {
			return nullptr;
		}
		//CreateType * (*creator)() = it->second;
		//CreateType * u = it->second();
		//return u;
		return (*it->second)();
	}

	bool registerStrategy(const Id & id, const CreatedType * (*creator)()) {
		CreatedType * s = createStrategyByID(id);
		if (s == nullptr) {
			creators[id] = creator;
			return true;
		}
		delete s;
		return false;
	}

	static Factory * getInstance() {
		static Factory f;
		return &f;
	}
private:
	Factory() = default;
	Factory(const Factory &) = delete;
	Factory & operator=(const Factory &) = delete;
	std::map <Id, CreatedType * (*)()> creators;
};