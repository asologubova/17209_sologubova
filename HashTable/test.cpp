#include "pch.h"
#include "../HashTable/hashTable.cpp"

#include <ctime>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

void generateRandomString(std::string & s, size_t length) {
	char buff[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
	'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
	char c = rand() % 26;
	for (size_t i = 0; i < length; i++) {
		s.push_back(buff[(c + i) % 26]);
	}
}

void generateRandomTable(HashTable & t, std::vector<std::string> & names, bool flag) {
	size_t a, w;
	Value v;

	if (flag) {
		std::ifstream in("names.txt");
		//std::ofstream out("bugs.txt");
		for (size_t i = 0; i < names.size(); i++) {
			std::getline(in, names[i]);
			a = i;
			w = i + 1;
			v = { a, w };
			/*bool b = */t.insert(names.at(i), v);
			//if (b) out << "writed" << std::endl;
		}
	}
	else {
		std::ofstream out("names.txt");
		for (size_t i = 0; i < names.size(); i++) {
			generateRandomString(names.at(i), 3 + i);
			out << names.at(i) << std::endl;
			a = i;
			w = i + 1;
			v = { a, w };
			t.insert(names.at(i), v);
		}
	}
}


TEST(SimpleTest, SomeTest) {
	HashTable a;
	EXPECT_EQ(a.size(), 0);
	EXPECT_TRUE(a.empty());
	EXPECT_THROW(a.at("Kot-Obormot"), std::out_of_range);
	Value v1 = { 20, 70 };
	EXPECT_TRUE(a.insert("Kot-Obormot", v1));
	EXPECT_EQ(a.size(), 1);
	EXPECT_EQ(a.at("Kot-Obormot"), v1);
	Value v2 = { 10, 30 };
	EXPECT_FALSE(a.insert("Kot-Obormot", v2));

	HashTable b = a;
	EXPECT_EQ(b.size(), 1);
	EXPECT_EQ(a, b);
	EXPECT_EQ(b.at("Kot-Obormot"), v1);
	EXPECT_EQ(b["Kot-Obormot"], v1);
	EXPECT_TRUE(b.contains("Kot-Obormot"));
	EXPECT_FALSE(b.contains("Pes-Borbos"));
	EXPECT_TRUE(b.erase("Kot-Obormot"));
	EXPECT_FALSE(b.erase("Kot-Obormot"));
	EXPECT_EQ(b.size(), 0);
	EXPECT_TRUE(b.empty());
	a.clear();
	EXPECT_EQ(a, b);

	Value ded = { 100, 80 };
	a.insert("Ded Moroz", ded);
	Value girl = { 15, 40 };
	b.insert("Snegurochka", girl);
	a.swap(b);
	EXPECT_EQ(a.at("Snegurochka"), girl);
	EXPECT_EQ(b.at("Ded Moroz"), ded);

	HashTable c(b);
	EXPECT_EQ(b, c);
}


TEST(SimpleTest, Contains) {
	srand(static_cast<size_t>(time(0)));
	size_t N = 50;
	HashTable ht;
	std::vector<std::string> names(N);

	generateRandomTable(ht, names, 0);
	EXPECT_TRUE(ht.contains(names.at(10)));

	Value v = { 10,10 };
	EXPECT_FALSE(ht.insert(names.at(10), v));

	ht.clear();
	HashTable t;
	EXPECT_TRUE(t.empty());
	EXPECT_TRUE(ht.empty());
	EXPECT_EQ(ht, t);
}


TEST(SimpleTest, Copy) {
	srand(static_cast<size_t>(time(0)));
	size_t N = 10;
	HashTable ht1;
	std::vector<std::string> names(N);
	generateRandomTable(ht1, names, 0);
	HashTable ht2(ht1);
	HashTable ht3 = ht1;
	EXPECT_TRUE(ht1 == ht2);
	EXPECT_TRUE(ht1 == ht3);

	std::string str;
	generateRandomString(str, 3);
	while (ht2.contains(str))
		generateRandomString(str, 3);
	Value v(12, 15);
	ht2.insert(str, v);
	EXPECT_TRUE(ht1 != ht2);

	ht2 = ht1;
	EXPECT_TRUE(ht1 == ht2);

	ht2.erase(names[5]);
	EXPECT_TRUE(ht1 != ht2);

	ht2.insert(names[5], { 15,15 });
	EXPECT_TRUE(ht1 == ht2);

	ht2.erase(names[5]);
	ht2.insert("Vasya", { 15,15 });
	EXPECT_TRUE(ht1 != ht2);
}


TEST(SimpleTest, Swap) {
	srand(static_cast<size_t>(time(0)));
	HashTable ht1;
	std::vector<std::string> names1(30);
	generateRandomTable(ht1, names1, 0);
	HashTable ht2(ht1);
	EXPECT_EQ(ht1.size(), 30);
	EXPECT_EQ(ht2.size(), 30);

	HashTable ht3;
	std::vector<std::string> names2(20);
	generateRandomTable(ht3, names2, 0);
	HashTable ht4(ht3);
	EXPECT_EQ(ht3.size(), 20);
	EXPECT_EQ(ht4.size(), 20);

	ht1.swap(ht3);

	EXPECT_EQ(ht3, ht2);
	EXPECT_EQ(ht1, ht4);
}

TEST(SimpleTest, Erase) {
	srand(static_cast<size_t>(time(0)));
	size_t N = 5;
	HashTable ht1;
	std::vector<std::string> names1(N);
	std::vector<std::string> names2(N);
	std::vector<std::string> names3(N);
	std::string str2, str3;

	std::ofstream out("bugs.txt");

	generateRandomTable(ht1, names1, 0);

	for (size_t i = 0; i < N; i++) {
		str2 = names1[i];
		std::swap(str2[0], str2[1]);
		names2[i] = str2;

		/*bool b = */ht1.insert(names2[i], { i + 1, i + 2 });
		//if (b) out << "writed" << std::endl;
	}

	for (size_t j = 0; j < N; j++) {
		str3 = names1[j];
		std::swap(str3[1], str3[2]);
		names3[j] = str3;
		/*bool b = */ht1.insert(names3[j], { j + 2, j + 3 });
		//if (b) out << "writed" << std::endl;
	}

	HashTable ht2(ht1);
	HashTable ht3(ht1);

	for (size_t k = 0; k < N; k++) {
		EXPECT_TRUE(ht1.contains(names1[k]));
		EXPECT_TRUE(ht2.contains(names1[k]));
		EXPECT_TRUE(ht3.contains(names1[k]));
		ht1.erase(names3[k]);
	}

	for (size_t k = 0; k < N; k++) {
		EXPECT_TRUE(ht1.contains(names1[k]));
		EXPECT_TRUE(ht2.contains(names1[k]));
		EXPECT_TRUE(ht3.contains(names1[k]));
		ht2.erase(names2[k]);
	}

	for (size_t k = 0; k < N; k++) {
		EXPECT_TRUE(ht1.contains(names1[k]));
		EXPECT_TRUE(ht2.contains(names1[k]));
		EXPECT_TRUE(ht3.contains(names1[k]));
		ht3.erase(names1[k]);
	}

	EXPECT_EQ(ht1.size(), N * 2);
	EXPECT_EQ(ht2.size(), N * 2);
	EXPECT_EQ(ht3.size(), N * 2);
}

TEST(SimpleTest, At) {
	srand(static_cast<size_t>(time(0)));
	size_t N = 15;
	HashTable ht;
	std::vector<std::string> names1(N);
	std::vector<std::string> names2(N);
	std::vector<std::string> names3(N);
	std::string str, str2, str3;

	std::ofstream out("bugs.txt");

	generateRandomTable(ht, names1, 0);

	for (size_t i = 0; i < N; i++) {
		str2 = names1[i];
		std::swap(str2[0], str2[1]);
		names2[i] = str2;

		/*bool b = */ht.insert(names2[i], { i + 1, i + 2 });
		//if (b) out << "writed" << std::endl;
	}

	for (size_t j = 0; j < N; j++) {
		str3 = names1[j];
		std::swap(str3[1], str3[2]);
		names3[j] = str3;
		/*bool b = */ht.insert(names3[j], { j + 2, j + 3 });
		//if (b) out << "writed" << std::endl;
	}

	Value v, v1, v2;

	for (size_t k = 0; k < N; k++) {
		v = { k, k + 1 };
		v1 = ht.at(names1[k]);
		v2 = ht[names1[k]];
		EXPECT_EQ(v, v1);
		EXPECT_EQ(v, v2);

		v = { k + 1, k + 2 };
		v1 = ht.at(names2[k]);
		v2 = ht[names2[k]];
		EXPECT_EQ(v, v1);
		EXPECT_EQ(v, v2);

		v = { k + 2, k + 3 };
		v1 = ht.at(names3[k]);
		v2 = ht[names3[k]];
		EXPECT_EQ(v, v1);
		EXPECT_EQ(v, v2);
	}

	v = { 0, 0 };
	str = names2[N - 1];
	std::swap(str[3], str[4]);
	v2 = ht[str];
	EXPECT_EQ(v, v2);

	size_t size = 10;
	while (size < ht.size()) size *= 2;
	EXPECT_EQ(ht.size(), N * 3 + 1);
	size_t i = 0;
	while (ht.size() <= size) {
		generateRandomString(str, 3 + i);
		i++;
		v2 = ht[str];
		EXPECT_EQ(v, v2);
	}
}

int main(int argc, char *argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}







