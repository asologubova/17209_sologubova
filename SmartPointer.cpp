//захват ресурса - это инициализация
//при уничтожении объект отпускает ресурс (в деструкторе), захватывает, например, в конструкторе
//управление ресурсами

#include <cstdio>
#include <fstream>

//умный указатель
template <class A> 
class SmartPointer {
public:
	SmartPointer() {} //конструктор по умолчанию
	~SmartPointer() { //деструктор
		if (nullptr != spdata) {
			if (1 == spdata->counter) {
				delete spdata->ptr;
				delete spdata;
				return;
			}
			--spdata->counter;
		}
	}
	SmartPointer(A * a = nullptr) { //конструктор захватывает ресурс
		spdata = new SmartPtrData;
		spdata->ptr = a;
		spdata->counter++;
	}
	SmartPointer(const SmartPointer & other) { //консруктор копирования 
		//заглянуть в other.spdata
		//скопировать ее адрес себе
		//увеличить счетчик ссылок
		if (!other.spdata) return; //??
		spdata = other.spdata;
		spdata->counter++;
	}
	SmartPointer & operator=(const SmartPointer & other) { //операция присваивания 
		if (!other.spdata) return nullptr;
		
		if (this != &other) {
			if (nullptr != spdata) {
				--spdata->counter;
				if (1 == spdata->counter)
					delete spdata->ptr;
			}
			spdata = other.spdata;
			spdata->counter++;
		}
		return *this;
	}
	//по желанию: поддердать семантику перемещения

	A * get() { //получить указатель
		return spdata->ptr;
	}
	void reset(A * other) { //освободить старый ресурс, захватить новый
		if (1 == spdata->counter) {
			delete spdata->ptr;
		}
		if (!other) return;
		spdata->ptr = other;
		spdata->counter++;
	}

	SmartPtrData & operator* {
		return *spdata;
	}
	SmartPtrData * operator-> {
		return spdata;
	}

private:
	SmartPtrData * spdata = nullptr;

	struct SmartPtrData {
		size_t counter = 0u;
		A * ptr = nullptr;
	};
};

void f() {
	throw 1;
}

void g() {
	f();
}

int main() {
	SmartPointer sp(new int);
	SmartPointer sp2 = sp;
	//вариант 1: рузрушающее копирование (std::auto_ptr)
	//вариант 2: глобальная хеш-аблица хранит флажки про каждый ресурс
	//вариант 3: хранить флажок прямо на месте (std::shared_ptr) + нюансы
	//вариант x: счетчик ссылок
	//вариант 4: base::linker_ptr (chromium)
	//варинат 5: счетчик ссылок хранить прямо в объекте (boost::intrusive_ptr, refcounte......)
	//варинат 6: запретить копирование (boost::scoped_ptr)
	// + варинат 7: запретить копирование, но разрешить перемещение (std::unique_ptr)
	//std::move(sp)

	//std::ifstream f("input.txt", "r"); 

	g();
	return 0;
	//int *i = new int;
	//g();
	//delete i; // с памятью проблемс т.к. в g() бросается исключение и до delete не дойдем
}


//struct A {
//	
//};
//
//struct SmartPtrData {
//	size_t counter = 0u;
//	A * ptr = nullptr;
//};