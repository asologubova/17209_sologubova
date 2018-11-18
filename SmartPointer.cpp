//������ ������� - ��� �������������
//��� ����������� ������ ��������� ������ (� �����������), �����������, ��������, � ������������
//���������� ���������

//��������!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#include <cstdio>
#include <fstream>

struct A {
	
};

struct SmartPtrData {
	size_t counter = 0u;
	A * ptr = nullptr;
};

//����� ���������
//�� �������: template <class T>
class SmartPointer {
public:
	SmartPointer() {} //����������� �� ���������
	~SmartPointer() { //����������
		if (nullptr != spdata) {
			if (1 == spdata->counter) {
				delete spdata->ptr;
				delete spdata;
				return;
			}
			--spdata->counter;
		}
	}
	SmartPointer(A * a = nullptr) { //����������� ����������� ������
		spdata = new SmartPtrData;
		spdata->ptr = a;
		spdata->counter++;
	}
<<<<<<< HEAD
	SmartPointer(const SmartPointer & other) { //���������� ����������� 
		//��������� � other.spdata
		//����������� �� ����� ����
		//��������� ������� ������
		if (!other.spdata) return; //??
		other.spdata = spdata;
		other.spdata->counter++;
	}
	SmartPointer & operator=(const SmartPointer & other) { //�������� ������������ 
		if (!other.spdata) return nullptr; //??
		other.spdata = spdata;
		other.spdata->counter++;
=======
	SmartPointer(const SmartPointer & other) { //���������� �����������
		//��������� � other.spdata
		//����������� �� ����� ����
		//��������� ������� ������
		if (!other.spdata) return;
		//...
		other.spdata->counter++;

	}
	SmartPointer & operator=(const SmartPointer & other) { //�������� ������������

>>>>>>> 9189338f2697f932b43c2d66738dfc2f30afe545

		return *this;
	}
	//�� �������: ���������� ��������� �����������

	A * get(); //�������� ���������
	void reset(A * other); //���������� ������ ������, ��������� �����

	//operator*, operator->

private:
	SmartPtrData * spdata = nullptr;
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
	//������� 1: ����������� ����������� (std::auto_ptr)
	//������� 2: ���������� ���-������ ������ ������ ��� ������ ������
	//������� 3: ������� ������ ����� �� ����� (std::shared_ptr) + ������
	//������� x: ������� ������
	//������� 4: base::linker_ptr (chromium)
	//������� 5: ������� ������ ������� ����� � ������� (boost::intrusive_ptr, refcounte......)
	//������� 6: ��������� ����������� (boost::scoped_ptr)
	// + ������� 7: ��������� �����������, �� ��������� ����������� (std::unique_ptr)
	//std::move(sp)

	//std::ifstream f("input.txt", "r"); 

	g();
	return 0;
	//int *i = new int;
	//g();
	//delete i; // � ������� �������� �.�. � g() ��������� ���������� � �� delete �� ������
}