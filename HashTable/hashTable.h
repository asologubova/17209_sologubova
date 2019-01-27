#include <cstdio>
#include <cstdlib>
#include <string>
#include <string.h>
#include <iostream>

// В этой задаче для простоты не требуется делать контейнер шаблонным,
// но это вполне допускается по желанию студента. Для нешаблонного решения, 
// введем типы ключей и значений: ключом будет выступать строка (например, имя
// студента, значением - произвольная структура (например, численные
// характеристики студента.

typedef std::string Key;

struct Value {
	size_t age = 0;
	size_t weight = 0;
	Value(size_t a, size_t w) : age(a), weight(w) {}
	Value() : Value(0, 0) {}
	Value& operator=(const Value & v) {
		age = v.age;
		weight = v.weight;
		return *this;
	}
};

bool operator==(const Value &v1, const Value &v2);

class HashTable {
public:
	HashTable();
	~HashTable();

	HashTable(const HashTable& b);

	// Обменивает значения двух хэш-таблиц.
	// Подумайте, зачем нужен этот метод, при наличии стандартной функции
	// std::swap.
	void swap(HashTable& b);

	HashTable& operator=(const HashTable& b);

	// Очищает контейнер.
	void clear();
	// Удаляет элемент по заданному ключу.
	bool erase(const Key& k);
	// Вставка в контейнер. Возвращаемое значение - успешность вставки.
	bool insert(const Key& k, const Value& v);

	// Проверка наличия значения по заданному ключу.
	bool contains(const Key& k) const;

	// Возвращает значение по ключу. Небезопасный метод.
	// В случае отсутствия ключа в контейнере, следует вставить в контейнер
	// значение, созданное конструктором по умолчанию и вернуть ссылку на него. 
	Value& operator[](const Key& k);

	// Возвращает значение по ключу. Бросает исключение при неудаче.
	Value& at(const Key& k);
	const Value& at(const Key& k) const;

	size_t size() const;
	bool empty() const;

	friend bool operator==(const HashTable & a, const HashTable & b);
	friend bool operator!=(const HashTable & a, const HashTable & b);

private:
	struct Student {
		Value parameters = Value();
		Key name;
		const Student & operator=(const Student & other) {
			if (this != &other) {
				parameters = other.parameters;
				name = other.name;
			}
			return *this;
		}
	};

	struct TableCell {
		Student data;
		bool flag;
		TableCell *next;

		TableCell() {
			data = Student();
			flag = false;
			next = nullptr;
		}
		TableCell(const TableCell & other) : data(other.data), flag(other.flag), next(other.next) {}
		const TableCell & operator=(const TableCell & other) {
			if (this != &other) {
				data = other.data;
				flag = other.flag;
				next = other.next;
			}
			return *this;
		}
	};

	static constexpr size_t kDefaultLen = 20;
	size_t len = kDefaultLen;
	size_t insertCounter = 0;
	size_t maxInserts = 0;
	TableCell *table = nullptr;

	void resizeTable();
};