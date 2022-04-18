/*
* 1. Реализовать шаблон класса Pair1, который позволяет пользователю передавать данные одного типа парами.
Следующий код:

int main()
{
Pair1<int> p1(6, 9);
cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

const Pair1<double> p2(3.4, 7.8);
cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';

return 0;
}

… должен производить результат:
Pair: 6 9
Pair: 3.4 7.8

2. Реализовать класс Pair, который позволяет использовать разные типы данных в передаваемых парах.
Следующий код:

int main()
{
Pair<int, double> p1(6, 7.8);
cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

const Pair<double, int> p2(3.4, 5);
cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';

return 0;
}

… должен производить следующий результат:
Pair: 6 7.8
Pair: 3.4 5

Подсказка: чтобы определить шаблон с использованием двух разных типов, просто разделите параметры типа шаблона запятой.

3. Написать шаблон класса StringValuePair, в котором первое значение всегда типа string, а второе — любого типа. 
Этот шаблон класса должен наследовать частично специализированный класс Pair, в котором первый параметр — string, а второй — любого типа данных.
Следующий код:

int main()
{
StringValuePair<int> svp("Amazing", 7);
std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';
return 0;
}

… должен производить следующий результат:
Pair: Amazing 7

Подсказка: при вызове конструктора класса **Pair* из конструктора класса StringValuePair не забудьте указать, что параметры относятся к классу Pair. *

4. Согласно иерархии классов, которая представлена в методичке к уроку 3, от класса Hand наследует класс GenericPlayer, 
который обобщенно представляет игрока, ведь у нас будет два типа игроков - человек и компьютер. Создать класс GenericPlayer, 
в который добавить поле name - имя игрока. Также добавить 3 метода:
• IsHitting() - чисто виртуальная функция, возвращает информацию, нужна ли игроку еще одна карта.
• IsBoosted() - возвращает bool значение, есть ли у игрока перебор
• Bust() - выводит на экран имя игрока и объявляет, что у него перебор.
*/

#include <iostream>
#include <vector>
//Task#1

template <typename T>
class Pair1
{
public:
	Pair1(T a, T b): one(a), two(b) {}
	~Pair1(){}
	T first() const { return one; }
	T second() const { return two; }

protected:
	T one;
	T two;
};

//Task#2
template <typename One, typename Two>
class Pair
{
public:
	Pair(One aa, Two bb) : a(aa), b(bb) {}
	~Pair() {}
	virtual One first() const { return a; }
	Two second() const { return b; }

protected:
	One a;
	Two b;
};


//Task#3
template <typename StringValue>
class StringValuePair : public Pair<std::string, StringValue>
{
public:
	StringValuePair(std::string aa, StringValue bb) : Pair<std::string, StringValue>(aa,bb), a(aa) {}
	~StringValuePair() {}
	std::string first() const {
		std::cout << a;
		return "";
	}
	

protected:
	std::string a;
};
//Task#4
enum rank {
	ACE = 1,
	TWO = 2,
	THREE = 3,
	FOUR = 4,
	FIVE = 5,
	SIX = 6,
	SEVEN = 7,
	EIGHT = 8,
	NINE = 9,
	TEN = 10,
	JACK = 10,
	QUEEN = 10,
	KING = 10
};
enum suit
{
	CLUBS,
	DIAMONDS,
	HEARTS,
	SPADES
};
class Card
{
public:

	Card(rank Rank, suit Suit) : Rank(Rank), Suit(Suit) {
		isFaceUp = true;
	}
	~Card() {}
	int GetValue() const {
		return Rank;
	}
	void Flip() {
		isFaceUp = !(isFaceUp);
	}

protected:
	rank Rank;
	suit Suit;
	bool isFaceUp;
};
class Hand
{
public:
	Hand();
	virtual ~Hand();
	void Add(Card* pCard)
	{
		myCards.push_back(pCard);
	}
	void Clear() {
		std::vector<Card*>::iterator i = myCards.begin();
		for (i = myCards.begin(); i != myCards.begin(); ++i)
		{
			delete* i;
			*i = 0;
		}
		myCards.clear();
	}
	int GetValue() const {
		if (myCards.empty())
		{
			return 0;
		}
		if (myCards[0]->GetValue() == 0)
		{
			return 0;
		}
		int total = 0;
		std::vector<Card*>::const_iterator i;
		for (i = myCards.begin(); i != myCards.end(); ++i)
		{
			total += (*i)->GetValue();
		}
		bool isAce = false;
		for (i = myCards.begin(); i != myCards.end(); ++i)
		{
			if ((*i)->GetValue() == rank::ACE)
			{
				isAce = true;
			}
		}
		if (isAce && total <= 11)
		{
			total += 10;
		}
		return total;
	}
protected:
	std::vector<Card*> myCards;
};

Hand::Hand()
{
	myCards.reserve(5);
}

Hand::~Hand()
{
	Clear();
}

class GenericPlayer : public Hand
{
public:
	GenericPlayer(const std::string& name = "");
	virtual ~GenericPlayer ();
	virtual bool IsHitting() const = 0;
	bool IsBusted() const {
		return (GetValue() > 21);
	}
	void Bust() const {
		std::cout << myName << "busts.\n";
	}
protected:
	std::string myName;
};
GenericPlayer::GenericPlayer(const std::string& name): myName(name) {}
GenericPlayer::~GenericPlayer() {}

int main()
{
	Pair1<int> p1(6, 9);
	std::cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

	const Pair1<double> p2(3.4, 7.8);
	std::cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';
	Pair<int, double> p3(6, 7.8);
	std::cout << "Pair: " << p3.first() << ' ' << p3.second() << '\n';

	const Pair<double, int> p4(3.4, 5);
	std::cout << "Pair: " << p4.first() << ' ' << p4.second() << '\n';

	StringValuePair<int> svp("Amazing", 7);
	std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';
	return 0;
}

