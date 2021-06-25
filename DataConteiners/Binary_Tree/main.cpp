#pragma warning(disable:4326)

#include <iostream>
using namespace std;

using std::cout;
using std::cin;
using std::endl;

#define tab "\t"
//#define DEBUG
//	UTF-8-BOM
//	Windows (CL-RF)

//#define BASE_CHECK

class Tree
{
protected:
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr) :Data(Data), pLeft(pLeft), pRight(pRight)
		{
#ifdef DEBUG
			cout << "EConstructor:" << tab << this << endl;
#endif // DEBUG
		}

		~Element()
		{
#ifdef DEBUG
			cout << "EDestructor:" << tab << this << endl;
#endif // DEBUG
		}

		bool is_leaf()const
		{
			return pLeft == pRight;
		}

		friend class Tree;
		friend class UniqueTree;
	} *Root;

public:
	Element* getRoot() const
	{
		return Root;
	}
	Tree() :Root(nullptr)
	{
#ifdef DEBUG
		cout << "TConstructor:" << tab << this << endl;
#endif // DEBUG
	}

	Tree(const initializer_list<int>& il) :Tree()
	{
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			insert(*it, Root);
		}
	}


	Tree(const Tree& other)
	{
#ifdef DEBUG
		cout << "CopyTConstructor:" << tab << this << endl;
#endif // DEBUG
		copy(other.Root);
	}

	~Tree()
	{
		clear();
#ifdef DEBUG
		cout << "TDestructor:" << tab << this << endl;
#endif // DEBUG
	}

	//	Operators:
	Tree& operator=(const Tree& other)
	{
		if (this == &other)return *this;
		clear(Root);
		copy(other.Root);
#ifdef DEBUG
		cout << "CopyAsignmentTConstructor:" << tab << this << endl;
#endif // DEBUG
	}


	int minValue() const
	{
		return minValue(Root);
	}

	int maxValue() const
	{
		return maxValue(Root);
	}

	int count() const
	{
		return count(Root);
	}

	int sum() const
	{
		return sum(Root);
	}

	double avg() const
	{
		return avg(Root);
	}

	void insert(int Data)
	{
		insert(Data, Root);
	}

	void erase(int Data)
	{
		erase(Data, this->Root);
	}

	void clear()
	{
		clear(this->Root);
		this->Root = nullptr;
	}

	void print() const
	{
		print(Root);
		cout << endl;
	}

private:
	int minValue(Element* Root) const
	{
		/*if (Root->pLeft == nullptr)
		{
			return Root->Data;
		}
		else
		{
			return minValue(Root->pLeft);
		}*/
		return Root->pLeft ? minValue(Root->pLeft) : Root->Data;
	}

	int maxValue(Element* Root) const
	{
		return Root->pRight ? maxValue(Root->pRight) : Root->Data;
	}

	int count(Element* Root) const
	{

		/*if (!Root) return 0;

		return count(Root->pLeft) + count(Root->pRight) + 1;*/

		return Root ? count(Root->pLeft) + count(Root->pRight) + 1 : 0;

	}

	int sum(Element* Root) const
	{
		return Root ? sum(Root->pLeft) + sum(Root->pRight) + Root->Data : 0;
	}

	double avg(Element* Root) const
	{
		return (double)sum(Root) / count(Root);
	}

	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)
		{
			this->Root = new Element(Data);
		}

		if (Root == nullptr) return;

		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)
			{
				Root->pLeft = new Element(Data);
			}
			else
			{
				insert(Data, Root->pLeft);
			}
		}
		else
		{
			/*if (Root->pRight == nullptr)
			{
				Root->pRight = new Element(Data);
			}
			else
			{
				insert(Data, Root->pRight);
			}*/

			if (Root->pRight) insert(Data, Root->pRight);
			else Root->pRight = new Element(Data);

		}
	}

	void clear(Element* Root)
	{
		if (Root == nullptr) return;
		clear(Root->pLeft);
		clear(Root->pRight);
		delete Root;
	}

	void erase(int Data, Element*& Root)
	{
		if (Root == nullptr) return;
		erase(Data, Root->pLeft);
		erase(Data, Root->pRight);

		if (Data == Root->Data)
		{
			if (Root->is_leaf())
			{
				delete Root;
				Root = nullptr;
			}
			else
			{
				if (count(Root->pLeft) > count(Root->pRight))
				{
					Root->Data = maxValue(Root->pLeft);
					erase(maxValue(Root->pLeft), Root->pLeft);
				}
				else
				{
					Root->Data = minValue(Root->pRight);
					erase(minValue(Root->pRight), Root->pRight);
				}
			}
		}
	}

	void print(Element* Root) const
	{
		if (Root == nullptr) return;

		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
	}

	void copy(Element* Root)
	{
		if (Root == nullptr) return;
		insert(Root->Data, this->Root);
		copy(Root->pLeft);
		copy(Root->pRight);
	}
};

class UniqueTree : public Tree
{
private:
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)
		{
			this->Root = new Element(Data);
		}

		if (Root == nullptr) return;

		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)
			{
				Root->pLeft = new Element(Data);
			}
			else
			{
				insert(Data, Root->pLeft);
			}
		}
		if (Data > Root->Data)
		{
			/*if (Root->pRight == nullptr)
			{
				Root->pRight = new Element(Data);
			}
			else
			{
				insert(Data, Root->pRight);
			}*/

			if (Root->pRight) insert(Data, Root->pRight);
			else Root->pRight = new Element(Data);

		}
	}
public:
	void insert(int Data)
	{
		insert(Data, this->Root);
	}
};

void main()
{
	setlocale(LC_ALL, "Russian");

#ifdef BASE_CHECK
	int n;
	cout << "Введите размер дерева:"; cin >> n;

	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	UniqueTree u_tree;
	for (int i = 0; i < n; i++)
	{
		u_tree.insert(rand() % 100);
	}

	//	tree.insert(-2, tree.getRoot());
	tree.print();

	cout << "Минимальное значение в дереве: " << tree.minValue() << endl;
	cout << "Максимальное значение в дереве: " << tree.maxValue() << endl;
	cout << "Количество элементов в дереве: " << tree.count() << endl;
	cout << endl;
	cout << "sum: " << tree.sum() << endl;
	cout << "avg: " << tree.avg() << endl;

	int value;
	cout << "Введите значение удаляемого значения: "; cin >> value;
	tree.erase(value);
	tree.print();

	cout << endl;
	cout << "\n:: Вызов без передачи корня ::\n";
	tree.print();
	cout << "Минимальное значение в дереве: " << tree.minValue() << endl;
	cout << "Максимальное значение в дереве: " << tree.maxValue() << endl;
	cout << "Количество элементов в дереве: " << tree.count() << endl;
	cout << endl;
	cout << "sum: " << tree.sum() << endl;
	cout << "avg: " << tree.avg() << endl;

	cout << "\n:: Уникальне дерево ::\n";

	//	u_tree.insert(-2, u_tree.getRoot());
	u_tree.print();
	cout << endl;

	cout << "Минимальное значение в дереве: " << u_tree.minValue() << endl;
	cout << "Максимальное значение в дереве: " << u_tree.maxValue() << endl;
	cout << "Количество элементов в дереве: " << u_tree.count() << endl;
	cout << endl;
	cout << "sum: " << u_tree.sum() << endl;
	cout << "avg: " << u_tree.avg() << endl;

	//Tree tree2 = tree;
	Tree tree2;
	tree2 = tree;

	tree2.print();
#endif // BASE_CHECK

	Tree tree = { 50, 25, 80, 16, 32, 64, 85, 12, 22 ,31 ,58 ,77 ,84 ,91 };
	tree.print();
	int value;
	cout << "Введите значение удаляемого значения: "; cin >> value;
	tree.erase(value);
	tree.print();

}