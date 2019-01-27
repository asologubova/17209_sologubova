#include "hashTable.h"
#include<functional>

#include <fstream>

bool operator==(const Value &v1, const Value &v2) {
	return ((v1.age == v2.age) && (v1.weight == v2.weight));
}

//size_t hashFunction(const Key& k) {
//	size_t i = 0, sum = 0;
//	std::hash<std::string> f;
//	return f(k);
//}

size_t hashFunction(const Key& k) {
	size_t i = 0, sum = 0;
	for (; i < k.length(); i++) {
		sum += k[i];
	}
	return sum;
}

HashTable::HashTable() {
	len = 20;
	maxInserts = 10;
	insertCounter = 0;
	table = new TableCell[len];
}

HashTable::~HashTable() {
	for (size_t i = 0; i < len; i++) {
		if (table[i].flag) {
			while (table[i].next) {
				TableCell *tmp = table[i].next->next;
				delete(table[i].next);
				table[i].next = tmp;
			}
		}
	}
	delete[](table);
}

HashTable::HashTable(const HashTable& b) {
	len = b.len;
	insertCounter = b.insertCounter;
	maxInserts = b.maxInserts;
	table = new TableCell[len];
	for (int i = 0; i < len; i++) {
		if (b.table[i].flag) {
			table[i] = b.table[i];
			TableCell *tmp_a = table + i;
			TableCell *tmp_b = b.table[i].next;;
			while (tmp_b) {
				TableCell *tc = new TableCell;
				*tc = *tmp_b;
				tmp_a->next = tc;
				tmp_a = tmp_a->next;
				tmp_b = tmp_b->next;
			}
		}
	}
}

void HashTable::swap(HashTable& b) { // Обменивает значения двух хэш-таблиц
	std::swap(len, b.len);
	std::swap(insertCounter, b.insertCounter);
	std::swap(maxInserts, b.maxInserts);
	std::swap(table, b.table);
}

HashTable& HashTable::operator=(const HashTable& b) {
	if (*this == b) return *this;

	clear();
	delete[] table;
	table = new TableCell[b.len];
	len = b.len;
	maxInserts = b.maxInserts;
	insertCounter = 0;

	for (size_t i = 0; i < b.len; i++) {
		if (b.table[i].flag) {
			TableCell *tmp = &b.table[i];
			while (tmp) {
				insert(tmp->data.name, tmp->data.parameters);
				tmp = tmp->next;
			}
		}
	}

	return *this;
}

void HashTable::clear() { //очистка контейнера
	for (size_t i = 0; i < len; i++) {
		if (table[i].flag) {
			while (table[i].next) {
				TableCell *tmp = table[i].next;
				table[i].next = table[i].next->next;
				delete(tmp);
			}
			table[i] = TableCell();
		}
	}
	insertCounter = 0;
}

bool HashTable::erase(const Key& k) { // Удаление. взвращаем успешность удаления
	size_t hash = hashFunction(k) % len;
	if (table[hash].flag) {
		if (table[hash].data.name == k) {
			if (table[hash].next) {
				TableCell *tmp = table[hash].next;
				table[hash] = *(table[hash].next);
				delete tmp;
			}
			else {
				table[hash] = TableCell();
				table[hash].flag = false;
			}
			insertCounter--;
			return true;
		}
		TableCell *tmpPrev = &table[hash];
		TableCell *tmpCurrent = table[hash].next;

		while (tmpCurrent) {
			if (tmpCurrent->data.name == k) {
				tmpPrev->next = tmpCurrent->next;
				delete tmpCurrent;
				insertCounter--;
				return true;
			}
			tmpPrev = tmpCurrent;
			tmpCurrent = tmpCurrent->next;
		}
	}
	std::cout << "point" << std::endl;
	return false;
}

bool HashTable::insert(const Key& k, const Value& v) { // Вставка. Возвращаем успешность вставки
	TableCell element = TableCell();
	size_t hash = hashFunction(k) % len;
	element.data.name = k;
	element.data.parameters = v;
	element.flag = true;

	TableCell *tmp = table + hash;
	TableCell *t = nullptr;
	if (tmp->flag) {
		while (tmp != nullptr) {
			if (tmp->data.name == k) {
				return false;
			}
			t = tmp;
			tmp = tmp->next;
		}
		TableCell *tm = new TableCell(element);
		t->next = tm;
	}
	else
		*tmp = element;

	insertCounter++;

	if (insertCounter > maxInserts)
		resizeTable();

	return true;
}

bool HashTable::contains(const Key & k) const { // Проверка наличия значения в таблице
	size_t hash = hashFunction(k) % len;
	TableCell *tmp = table + hash;
	if (tmp->flag) {
		while (tmp != nullptr) {
			if (tmp->data.name == k)
				return true;
			tmp = tmp->next;
		}
	}
	return false;
}

Value& HashTable::operator[](const Key& k) { // Возвращает значение по ключу. Небезопасный метод
	if ((insertCounter + 1) > maxInserts)
		resizeTable();

	size_t hash = hashFunction(k) % len;
	TableCell *tmp = &table[hash];

	if (table[hash].flag) {
		while (tmp) {
			if (tmp->data.name == k) {
				return tmp->data.parameters;
			}
			tmp = tmp->next;
		}
	}
	tmp = new TableCell();
	tmp->flag = true;
	tmp->next = nullptr;
	tmp->data.name = k;
	insertCounter++;
	return tmp->data.parameters;
}

Value& HashTable::at(const Key& k) { // Возвращает значение по ключу. Бросает исключение при неудаче
	size_t hash = hashFunction(k) % len;
	if (table[hash].flag) {
		TableCell *tmp = &table[hash];
		while (tmp) {
			if (tmp->data.name == k) {
				return tmp->data.parameters;
			}
			tmp = tmp->next;
		}
	}
	throw std::out_of_range(k); //"Key not found!"
}

const Value& HashTable::at(const Key& k) const { // Возвращает значение по ключу. Бросает исключение при неудаче ???????????????? в чем отличие должно быть?
	size_t hash = hashFunction(k) % len;
	if (table[hash].flag) {
		TableCell *tmp = &table[hash];
		while (tmp) {
			if (tmp->data.name == k) {
				return tmp->data.parameters;
			}
			tmp = tmp->next;
		}
	}
	throw std::out_of_range("Key not found!");
}

size_t HashTable::size() const {
	return insertCounter;
}

bool HashTable::empty() const {
	return (insertCounter == 0);
}

bool operator==(const HashTable & a, const HashTable & b) {
	bool in = false;
	if (a.insertCounter != b.insertCounter) return false;

	for (int i = 0; i < a.len; i++) {

		if (a.table[i].flag) {
			HashTable::TableCell *tmp = &a.table[i];

			while (tmp) {
				if (!b.contains(tmp->data.name)) return false;
				tmp = tmp->next;
			}
		}
	}

	return true;
}

bool operator!=(const HashTable & a, const HashTable & b) {
	return !(a == b);
}

void HashTable::resizeTable() { //Учеличение размра таблицы
	HashTable b;
	b.len = len * 2;
	b.maxInserts = maxInserts * 2;
	b.table = new TableCell[b.len];

	for (int i = 0; i < len; i++) {
		if (table[i].flag) {
			TableCell *tmp = &table[i];
			while (tmp) {
				b.insert(tmp->data.name, tmp->data.parameters);
				tmp = tmp->next;
			}
		}
	}
	swap(b);
}