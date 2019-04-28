#include <Card.h>
#include <iostream>
#include <vector>
#include <ctime>
using json = nlohmann::json;
using namespace std;
class Deck
{
public:
	Deck(Deck &other)
	{
		for (int i = 0; i < other.size(); i++)
		{
			vector<Card> temp = other.getDeck();
			deckLinkList.push_back(temp[i]);
		}
	}

	int size()
	{
		return deckLinkList.size();
	}

	void pushCard(Card C)
	{
		deckLinkList.push_back(C);
	}
	void pushCard(json JSON) // push pop
	{
		Card C;

		pushCard(C);
	}

	vector<Card> searchCards(int id = -1)
	{
		vector<Card> *temp = new vector<Card>;
		if (id == -1)
		{
			for (int i = 0; i < deckLinkList.size(); i++)
			{
				if (deckLinkList[i].getCardType == id) // ??
				{
					temp->push_back(deckLinkList[i]);
				}
			}
		}
		else
		{
			for (int i = 0; i < deckLinkList.size(); i++)
			{
				if (deckLinkList[i].getId() == id)
				{
					temp->push_back(deckLinkList[i]);
				}
			}
		}
		return *temp;
	}
	//-1 search by type, others by id

	vector<Card> getDeck()
	{
		return this->deckLinkList;
	}
	//取得整副牌

	Card popDeck(int index = -1)
	{
		if (index == -1)
		{
			Card *pointer = new Card(deckLinkList[-1]);
			deckLinkList.pop_back();
			return *pointer;
		}
		else
		{
			deckLinkList.erase(deckLinkList.begin() + index);
		}
	}
	//-1 抽一張牌, others just pop by index

	vector<Card &> getIndexCards(int num, int mode = 0, int sieve = -1)
	{
		vector<int> *array = new vector<int>;
		if (mode) // mode => 1
		{
			for (int i = deckLinkList.size() - 1; i >= 0 && num; i++)
			{
				if (sieve == -1)
				{
					array->push_back(i);
					num--;
				}
				else if (sieve == deckLinkList[i].getCardType())
				{
					array->push_back(i);
					num--;
				}
			}
		}
		else // mode => 0
		{
			Init();
			for (int i = num; i > 0; i--)
			{
				int temp = rand() % deckLinkList.size();
				while (find(array->begin(), array->end(), temp) == array->end())
				{
					if (sieve == deckLinkList[i].getCardType() || sieve == -1)
						break;
					temp = rand() % deckLinkList.size();
				}

				array->push_back(temp);
			}
		}
		return *array;
	}

	//取得num張牌的index, mode=0 (random抽取) , mode=1 (從牌堆最前面), sieve=-1 所有牌,others 只有那種type的牌

	void deckShuffler()
	{
		Init();
		for (int i = 0; i < deckLinkList.size(); i++)
			swap(deckLinkList[i], deckLinkList[i + rand() % (deckLinkList.size() - i)]);
	}

private:
	void
	Init()
	{
		srand(time(NULL));
	}

	vector<Card> deckLinkList;
};