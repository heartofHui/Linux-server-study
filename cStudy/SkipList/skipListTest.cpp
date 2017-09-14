#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <stdlib.h>
#include <limits.h>
#include "../Includes/times.h"
using namespace std;

#define MAXLEVEL 4 //最多2 power n=16个数
/*skip list node,they are keys and pointers*/

class SKNode
{
public:
	int64_t member;
	int64_t score;
	SKNode* forward[MAXLEVEL];

	SKNode()
	{
		member = 0;
		score = 0;
		for (int i = 0; i < MAXLEVEL; i++)
		{
			forward[i] = NULL;
		}
	}
};
//skip list, it has a header, this header have maxlevel pointers
class SkipList
{
public:
	SKNode *hdr; /* list Header */
	int listLevel; /* current level of list */
	int insert(int64_t mem,int64_t score);
	SKNode* search(int key);
	bool deleteNode(int key);
	void printList();
	int getInsertLevel();
	SkipList()
	{
		cout<<"SkipList()"<<endl;
		hdr = new SKNode;
		listLevel = 1;
		hdr->score = -INT_MAX;
		SKNode* end = new SKNode;
		SKNode* first = new SKNode;
		first->score = -INT_MAX;
		end->score = INT_MAX;
		for (int i = 0; i < MAXLEVEL; i++)
		{
			hdr->forward[i] = first;
			hdr->forward[i]->forward[i] = end;
		}
		printList();
	}
	~SkipList()
	{
		cout<<"~SkipList()"<<endl;
		delete hdr;
	}
};

class CH_Zset
{
	SkipList skpl;
	std::map<int64_t,int64_t> MemScoreMap;
public:
	/*
	 * args
	 * 		mem:data
	 * 		score:sort by score
	 * return:
	 * 		0:success other:fail
	 * 		*/
	int zsetadd(const int64_t& mem, const int64_t& score);
	int zscore(const int64_t& mem,int64_t& score);
	int zrange(const int64_t& start, const int64_t& end, );
	int zrem(const int64_t& mem);
};

int CH_Zset::zsetadd(const int64_t& mem, const int64_t& score)
{
	skpl.insert(mem,score);
	MemScoreMap[mem] = score;
	return 0;
}

int CH_Zset::zscore(const int64_t& mem,int64_t& score)
{
	score = 0;
	if(MemScoreMap.find(mem)!=MemScoreMap.end())
	{
		score = MemScoreMap[mem];
		return 0;
	}
	else
	{
		return 1;
	}
}

int CH_Zset::zrange(const )

int SkipList::getInsertLevel()
{
	static int i = 1;
	i++;
	int32_t sed = getTimeUsec() % 10000 + i;
	cout << "sed" << sed << endl;
	srand(sed);
	int upcount = 0;
	for (int i = 0; i < MAXLEVEL; i++)
	{
		int num = rand() % 10;
		if (num < 3)
		{
			upcount++;
		}
	}
	return upcount > 1 ? upcount : 1;
}

SKNode* SkipList::search(int score)
{
	SKNode* current = new SKNode;
	current = hdr;
	int i = listLevel - 1;
	for (; i >= 0; i--)
	{
		while (current->forward[i]->score != INT_MAX
				&& score > current->forward[i]->score) //key大于下一个数据的值。转到本层下一个元素
		{
			cout<<" find, from key="<< current->forward[i]->score<<" this floor to next "<<endl;
			current = current->forward[i];
		}
		if(i != 0)
		{
			cout<<" find, from "<< current->score <<" to next floor "<<endl;
		}
		//否则i--，转到下一层
	}
	current = current->forward[0];
	if (current != NULL && current->score == score)
	{
		cout << "find" << score << endl;
		return current;
	}
	return NULL;
}

int SkipList::insert(int64_t mem,int64_t score)
{
	int level = getInsertLevel();
	SKNode* node = new SKNode;
	node->member = mem;
	node->score = score;

	SKNode *s[MAXLEVEL];
	SKNode* current = new SKNode;
	SKNode* last = new SKNode;
	for (int i = 0; i < MAXLEVEL; i++)
	{
		s[i] = hdr->forward[i]; //initiation
	}
	current = last = hdr;
	int i = listLevel - 1;
	for (; i >= 0; i--)
	{
		while (current->forward[i]->score != INT_MAX
				&& score > current->forward[i]->score) //key大于下一个数据的值。转到本层下一个元素
		{
			current = current->forward[i];
		}
		s[i] = current; //保存每一层位置上的最后指针的前驱
	}
	last = current->forward[0];
	if (last != NULL && last->score == score)
	{
//		cout << "inset key:" << key << "already existed" << endl;
//		return 0;
		level = 1;
	}
	if (level > listLevel) //更新层数
	{
		listLevel = level;
	}
	for (int k = 0; k < level; k++)
	{
		node->forward[k] = s[k]->forward[k];
		s[k]->forward[k] = node;
	}
	return 1;
}

/*
 * key: des delete key
 * return:false:fail , true:success*/
bool SkipList::deleteNode(int score)
{
	SKNode * node;
	node = search(score);
	if(node)
	{
		int i = listLevel-1;
		SKNode *p,*q;
		while(i>=0)
		{
			p=q=hdr;
			while(p!=node && p!=NULL)
			{
				q=p;
				p=p->forward[i];
			}
			if(p)
			{
				q->forward[i] = p->forward[i];
				if (i==listLevel-1 && q->score == -INT_MAX && p->forward[i]->score == INT_MAX)//如果当前层无元素，把层数减1
				{
					--listLevel;
				}
			}
			--i;
		}
		delete node;
		return true;
	}
	else
	{
		cout<<"key "<< score<<" not exists!"<<endl;
		return false;
	}
}

void SkipList::printList()
{
	SKNode* current = hdr;
	for (int i = listLevel - 1; i >= 0; i--)
	{
		current = hdr->forward[i];
		cout << "level " << i << "................................" << endl;
		while (current->forward[i] != NULL) //
		{
			cout << " " <<current->member<<":"<< current->score;
			current = current->forward[i];
		}
		cout << " " <<current->member<<":"<< current->score << endl;
	}
}

int main()
{
	SkipList sk;
	const int n = 7;
	int num[n] =
	{ 30, 15, 45, 37, 11, 53, 17 };
	cout << "test insert............." << endl;

	for (int i = 0; i < n; i++)
	{
		sk.insert(num[i], num[i]);
	}
	sk.printList();

	int32_t mem=0,score=0;
	while(mem!=0)
	{
		cout<<"input mem&score:";
		cin>>mem>>score;
		sk.insert(mem, score);
		sk.printList();
	}

	cout << "test search............" << endl;
	sk.search(17);

	cout << "test delete................." << endl;
	int32_t deleteKey = 0;
	cin >> deleteKey;
	sk.deleteNode(deleteKey);
	sk.printList();

	return 0;
}
