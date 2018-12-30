#include "header.h"

bool operator==(const Value &v1, const Value &v2) {
	return ((v1.age == v2.age) && (v1.weight == v2.weight));
}

size_t hashFunction(const Key& k) {
	size_t i = 0, sum = 0;
	for (; i < k.length(); i++) {
		sum += (size_t)((k[i] % 3) * pow(3, i));
	}
	return sum;
}

HashTable::HashTable() {
	len = 10;
	maxInserts = 10;
	insertCounter = 0;
	table = new TableCell[len];
	for (int i = 0; i < len; i++)
		table[i] = TableCell();
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
	//insertCounter = 0;
	//maxInserts = 0;
	delete[](table);
}

HashTable::HashTable(const HashTable& b) {
	len = b.len;
	insertCounter = b.insertCounter;
	maxInserts = b.maxInserts;
	table = new TableCell[len];
	for (int i = 0; i < len; i++) {
		table[i] = TableCell();
		if (b.table[i].flag) {
			table[i] = b.table[i];
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
	HashTable c;
	c.len = b.len;
	c.maxInserts = b.maxInserts;
	c.insertCounter = b.insertCounter;

	c.table = new TableCell[c.len];
	for (size_t i = 0; i < c.len; i++) {
		if (b.table[i].flag) {
			c.table[i] =  b.table[i]; 
			TableCell *tmp_b = b.table[i].next;
			TableCell *tmp_c = &c.table[i];
			while (tmp_b) {
				TableCell *tmp = new TableCell;
				*tmp = *tmp_b;
				tmp_c->next = tmp;
				tmp_b = tmp_b->next;
				tmp_c = tmp_c->next;
			}
		}
	}
	swap(c);
	//c.~HashTable();
	return *this;
}

void HashTable::clear() { //очистка контейнера
	for (size_t i = 0; i < len; i++) {
		if (table[i].flag) {
			while (table[i].next) {
				TableCell *tmp = table[i].next->next;
				delete(table[i].next);
				table[i].next = tmp;
			}
			table[i] = TableCell();
		}
	}
	insertCounter = 0;
	maxInserts = 10;
}

bool HashTable::erase(const Key& k) { // Удаление. взвращаем успешность удаления
	size_t hash = hashFunction(k) % len;
	if (table[hash].flag) {
		if (/*(&tmp->data.name) && */(table[hash].data.name == k)) {
			if (table[hash].next) {
				table[hash] = *table[hash].next;
				delete table[hash].next;
			}
			else table[hash] = TableCell();
			insertCounter--;
			return true;
		}
		TableCell *tmpPrev = &table[hash];
		TableCell *tmpCurrent = table[hash].next;

		while (tmpCurrent) {
			if (/*(&tmp->data.name) && */(tmpCurrent->data.name == k)) {
				tmpPrev->next = tmpCurrent->next;
				delete tmpCurrent;
				return true;
			}
			tmpPrev = tmpCurrent;
			tmpCurrent = tmpCurrent->next;
		}
	}
	
	return false;
}

bool HashTable::insert(const Key& k, const Value& v) { // Вставка. Возвращаем успешность вставки
	if (k == "") return false;
	TableCell *newEl = new TableCell();
	size_t hash = hashFunction(k) % len;
	newEl->data.name = k;
	newEl->data.parameters = v;

	if (table[hash].flag) {
		TableCell *tmp = &table[hash]; // проверка наличия ключа
		while (tmp) {
			if (tmp->data.name == k)
				return false;
			tmp = tmp->next;
		}
		newEl->next = &table[hash];
		table[hash] = *newEl;
	}
	else {
		table[hash] = *newEl;
		table[hash].flag = true;
	}
	insertCounter++;
	if (insertCounter > maxInserts) resizeTable();
	return true;
}

bool HashTable::contains(const Key& k) const { // Проверка наличия значения в таблице
	size_t hash = hashFunction(k) % len;
	for (size_t i = 0; i < len; i++) {
		if (table[i].flag) {
			TableCell *tmp = &table[i];
			while (tmp) {
				if ((&tmp->data.name) && (tmp->data.name == k))
					return true;
				tmp = tmp->next;
			}
		}
	}
	return false;
}

Value& HashTable::operator[](const Key& k) { // Возвращает значение по ключу. Небезопасный метод
	size_t hash = hashFunction(k) % len;
	TableCell *tmp;
	if (insertCounter + 1 > maxInserts)
		resizeTable();
	if (table[hash].flag) {
		tmp = &table[hash];
		while (tmp) {
			if (tmp->data.name == k) {
				return table[hash].data.parameters;
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
			if (table[hash].data.name == k) {
				return table[hash].data.parameters;
			}
			tmp = tmp->next;
		}
	}
	throw std::out_of_range("Key not found!");
}

const Value& HashTable::at(const Key& k) const { // Возвращает значение по ключу. Бросает исключение при неудаче ???????????????? в чем отличие должно быть?
	size_t hash = hashFunction(k) % len;
	if (table[hash].flag) {
		TableCell *tmp = &table[hash];
		while (tmp) {
			if (table[hash].data.name == k) {
				return table[hash].data.parameters;
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
	bool l = false, in = false, m = false;
	if (a.len == b.len) l = true;
	if (a.insertCounter == b.insertCounter) in = true;
	if (a.maxInserts == b.maxInserts) m = true;

	if (!(l && in && m)) return false;
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
	b.len *= 2;
	b.maxInserts *= 2;
	b.table = new TableCell[b.len];
	for (int i = 0; i < b.len; i++)
		table[i] = TableCell();

	for (int i = 0; i < len; i++) {
		if (table[i].flag) {
			TableCell *tmp = &table[i];
			while (tmp) {
				b.insert(table[i].data.name, table[i].data.parameters);
				tmp = tmp->next;
			}
		}
	}
	swap(b);
	//b.~HashTable();
}




//ht["nnn"] = Value{ 1, 2 };
//конструктор по размеру



//h(c[0],...,c[N-1])=сумма((c[i]%3)*(3^i))   - хеш для строки
//#define MAX_LEN_KEY 100

/*
void fill(int *pow3, int *ascii_mod3){
int i = 0, pow = 1;
for (; i < MAX_LEN_KEY; i++){
pow3[i] = pow;
pow *= 3;
}
for (i = 0; i <= 255; i++)
ascii_mod3[i] = i % 3;
return;
}

unsigned int hash_function1(const Key& k, int *pow3, int *ascii_mod3){
int i;
unsigned int sum = 0;

for (i = 0; i < strlen(k); i++)
sum += (ascii_mod3[k[i]] * pow3[i]);

return sum;
}*/