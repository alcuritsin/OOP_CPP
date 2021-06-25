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

		~Tree()
		{
#ifdef DEBUG
			cout << "TDestructor:" << tab << this << endl;
#endif // DEBUG
		}

		/*Element* maximum(Element* Root)
		{
			if (Root == nullptr) return maximum(Root->pRight);

		}*/

		int minValue(Element* Root)
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

		int minValue()
		{
			return minValue(Root);
		}

		int maxValue(Element* Root)
		{
			return Root->pRight ? maxValue(Root->pRight) : Root->Data;
		}

		int maxValue()
		{
			return maxValue(Root);
		}

		int count(Element* Root)
		{	
			
			/*if (!Root) return 0;

			return count(Root->pLeft) + count(Root->pRight) + 1;*/
			
			return Root ? count(Root->pLeft) + count(Root->pRight) + 1 : 0;
		
		}

		int count()
		{
			return count(Root);
		}

		int sum(Element* Root)
		{
			return Root ? sum(Root->pLeft) + sum(Root->pRight) + Root->Data: 0 ;
		}

		int sum()
		{
			return sum(Root);
		}


		double avg(Element* Root)
		{
			return (double)sum(Root) / count(Root);
		}

		double avg()
		{
			return avg(Root);
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
				if (Root->pLeft == nullptr )
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

		void insert(int Data)
		{
			insert(Data, Root);
		}

		void print(Element* Root)
		{
			if (Root == nullptr) return;

			print(Root->pLeft);
			cout << Root->Data << tab;
			print(Root->pRight);
		}

		void print()
		{
			print(Root);
		}

};

class UniqueTree : public Tree
{
public:
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
};

void main()
{
	setlocale(LC_ALL, "Russian");
	
	int n;
	cout << "Введите размер дерева:"; cin >> n;

	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand()%100,tree.getRoot());
	}
	UniqueTree u_tree;
	for (int i = 0; i < n; i++)
	{
		u_tree.insert(rand()%100, u_tree.getRoot());
	}

//	tree.insert(-2, tree.getRoot());
	tree.print(tree.getRoot());
	cout << endl;

	cout << "Минимальное значение в дереве: " << tree.minValue(tree.getRoot ()) << endl;
	cout << "Максимальное значение в дереве: " << tree.maxValue(tree.getRoot ()) << endl;
	cout << "Количество элементов в дереве: " << tree.count(tree.getRoot()) << endl;
	cout << endl;
	cout << "sum: " << tree.sum(tree.getRoot()) << endl;
	cout << "avg: " << tree.avg(tree.getRoot()) << endl;
	
	cout << endl;
	cout << "\n:: Вызов без передачи корня ::\n";
	tree.print();
	cout << endl;
	cout << "Минимальное значение в дереве: " << tree.minValue() << endl;
	cout << "Максимальное значение в дереве: " << tree.maxValue() << endl;
	cout << "Количество элементов в дереве: " << tree.count() << endl;
	cout << endl;
	cout << "sum: " << tree.sum() << endl;
	cout << "avg: " << tree.avg() << endl;

	cout << "\n:: Уникальне дерево ::\n";

//	u_tree.insert(-2, u_tree.getRoot());
	u_tree.print(u_tree.getRoot());
	cout << endl;

	cout << "Минимальное значение в дереве: " << u_tree.minValue(u_tree.getRoot ()) << endl;
	cout << "Максимальное значение в дереве: " << u_tree.maxValue(u_tree.getRoot ()) << endl;
	cout << "Количество элементов в дереве: " << u_tree.count(u_tree.getRoot()) << endl;


}