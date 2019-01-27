#include <cstdio>
#include <cstdlib>
#include <string>
#include <string.h>
#include <iostream>

// � ���� ������ ��� �������� �� ��������� ������ ��������� ���������,
// �� ��� ������ ����������� �� ������� ��������. ��� ������������ �������, 
// ������ ���� ������ � ��������: ������ ����� ��������� ������ (��������, ���
// ��������, ��������� - ������������ ��������� (��������, ���������
// �������������� ��������.

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

	// ���������� �������� ���� ���-������.
	// ���������, ����� ����� ���� �����, ��� ������� ����������� �������
	// std::swap.
	void swap(HashTable& b);

	HashTable& operator=(const HashTable& b);

	// ������� ���������.
	void clear();
	// ������� ������� �� ��������� �����.
	bool erase(const Key& k);
	// ������� � ���������. ������������ �������� - ���������� �������.
	bool insert(const Key& k, const Value& v);

	// �������� ������� �������� �� ��������� �����.
	bool contains(const Key& k) const;

	// ���������� �������� �� �����. ������������ �����.
	// � ������ ���������� ����� � ����������, ������� �������� � ���������
	// ��������, ��������� ������������� �� ��������� � ������� ������ �� ����. 
	Value& operator[](const Key& k);

	// ���������� �������� �� �����. ������� ���������� ��� �������.
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