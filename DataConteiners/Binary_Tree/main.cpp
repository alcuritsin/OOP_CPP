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

template<typename T> class Tree;
template<typename T> class UniqueTree;

template<typename T> class Tree
{
protected:
	class Element
	{
		T Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(T Data, Element* pLeft = nullptr, Element* pRight = nullptr) :Data(Data), pLeft(pLeft), pRight(pRight)
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

		friend class Tree<T>;
		friend class UniqueTree<T>;
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

	Tree(const initializer_list<T>& il) :Tree<T>()
	{
		for (T const* it = il.begin(); it != il.end(); it++)
		{
			insert(*it, Root);
		}
	}


	Tree(const Tree<T>& other)
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
	Tree<T>& operator=(const Tree<T>& other)
	{
		if (this == &other)return *this;
		clear(Root);
		copy(other.Root);
#ifdef DEBUG
		cout << "CopyAsignmentTConstructor:" << tab << this << endl;
#endif // DEBUG
	}

	T minValue() const
	{
		return minValue(Root);
	}

	T maxValue() const
	{
		return maxValue(Root);
	}

	T count() const
	{
		return count(Root);
	}

	T sum() const
	{
		return sum(Root);
	}

	double avg() const
	{
		return avg(Root);
	}

	void insert(T Data)
	{
		insert(Data, Root);
	}

	void erase(T Data)
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
	T minValue(Element* Root) const
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

	T maxValue(Element* Root) const
	{
		return Root->pRight ? maxValue(Root->pRight) : Root->Data;
	}

	T count(Element* Root) const
	{

		/*if (!Root) return 0;

		return count(Root->pLeft) + count(Root->pRight) + 1;*/

		return Root ? count(Root->pLeft) + count(Root->pRight) + 1 : 0;

	}

	T sum(Element* Root) const
	{
		return Root ? sum(Root->pLeft) + sum(Root->pRight) + Root->Data : 0;
	}

	double avg(Element* Root) const
	{
		return (double)sum(Root) / count(Root);
	}

	void insert(T Data, Element* Root)
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

	void erase(T Data, Element*& Root)
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

template<typename T> class UniqueTree : public Tree<T>
{
protected:
	void insert(T Data, Tree<T>::Element* Root)
	{
		if (this->Root == nullptr)
		{
			this->Root = new typename Tree<T>::Element(Data);
		}

		if (Root == nullptr) return;

		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)
			{
				Root->pLeft = new typename Tree<T>::Element(Data);
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
			else Root->pRight = new typename Tree<T>::Element(Data);

		}
	}
public:
	//UniqueTree(const initializer_list<T>& il) :Tree<T>(*il);

	void insert(T Data)
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

	tree2.print(); TemplatedTree
#endif // BASE_CHECK
	
	//UniqueTree<int> u_tree = { 50, 25, 80, 16, 32, 64, 85, 12, 22 ,31 ,58 ,77 ,84 ,91 };
		int n;
	
	cout << "Введите размер дерева:"; cin >> n;

	UniqueTree<double> u_tree;
	for (int i = 0; i < n; i++)
	{
		u_tree.insert((double)(rand() % 1000)/100);
	}

	u_tree.print();

	Tree<double> tree = { 50.5, 25.5, 80.5, 16.5, 32.5, 64.5, 85.5, 12.0, 22.0, 31.0, 58.0, 77.0, 84.0, 91.0 };
	tree.print();
	double value;
	cout << "Введите значение удаляемого значения: "; cin >> value;
	tree.erase(value);
	tree.print();

}