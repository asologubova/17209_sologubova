#include "pch.h"
#include "../header.h"

#include <ctime>

void generateRandomString(char *s, size_t length) {
	srand(time(0));
	for (size_t i = 0; i < length; i++) {
		s[i] = (char)(rand() % 256);
	}
	return;
}

void generateRandomTable(HashTable &t, char **names, size_t N) {
	size_t length = rand();
	for (size_t i = 0; i < N; i++) {
		char* s = new char[length];
		generateRandomString(s, length + i);
		names[i] = s;
		size_t a = rand();
		size_t w = rand();
		Value v(a, w);
		t.insert(s, v);
	}
	return;
}

TEST(SimpleTest, FunctionsTest) {
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

TEST(SimpleTest, SomeTest) {
	srand(time(0));
	size_t N = rand();
	HashTable ht;
	char **names = new char *[N];
	generateRandomTable(ht, names, N);
	EXPECT_TRUE(ht.contains(names[rand() % N]));

}

int main(int argc, char *argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}