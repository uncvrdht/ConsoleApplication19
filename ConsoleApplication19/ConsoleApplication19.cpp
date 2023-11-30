#include <iostream>
#include <ctime>

using namespace std;

class SinglyLinkedList
{
public:
    struct Node
    {
        int data = 0;
        Node* next = nullptr;
    };

private:
    Node* head = nullptr;
    Node* tail = nullptr;
    int count = 0;

public:
    void AddToHead(int data)
    {
        Node* newElem = new Node();
        newElem->data = data;
        newElem->next = head;
        if (head == nullptr)
        {
            tail = newElem;
        }
        head = newElem;
        count++;
    }

    void AddToTail(int data)
    {
        Node* newElem = new Node();
        newElem->data = data;
        if (tail == nullptr)
        {
            head = newElem;
        }
        else
        {
            tail->next = newElem;
        }
        tail = newElem;
        count++;
    }

    void InsertInto(int data, int position)
    {
        if (position >= count)
        {
            AddToTail(data);
            return;
        }
        else if (position <= 0)
        {
            AddToHead(data);
            return;
        }

        Node* newElem = new Node();
        newElem->data = data;
        int i = 1;
        Node* beforeNew = head;
        while (i++ != position)
        {
            beforeNew = beforeNew->next;
        }
        newElem->next = beforeNew->next;
        beforeNew->next = newElem;

        count++;
    }

    void DeleteFromHead()
    {
        if (count == 0)
        {
            return;
        }
        Node* temp = head;
        head = head->next;
        delete temp;
        count--;
        if (head == nullptr)
        {
            tail = nullptr;
        }
    }

    void DeleteFromTail()
    {
        if (count == 0) {
            return;
        }
        DeleteByIndex(count - 1);
    }

    void DeleteByIndex(int position)
    {
        if (position <= 0)
        {
            DeleteFromHead();
            return;
        }

        if (position >= count)
        {
            position = count - 1;
        }

        int i = 1;
        Node* beforeDel = head;
        while (i++ != position)
        {
            beforeDel = beforeDel->next;
        }
        Node* sacrifice = beforeDel->next;
        beforeDel->next = sacrifice->next;
        delete sacrifice;
        count--;
        if (beforeDel->next == nullptr)
        {
            tail = beforeDel;
        }
    }

    void Clear()
    {
        while (head != nullptr)
        {
            DeleteFromHead();
        }
    }

    void Print() const
    {
        if (count == 0)
        {
            cout << "Empty list!\n";
            return;
        }
        Node* current = head;
        while (current != nullptr)
        {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    int GetCount() const
    {
        return count;
    }

    int IndexOf(int data) const
    {
        if (count == 0)
        {
            return -1;
        }
        Node* temp = head;
        int i = 0;
        while (i < count)
        {
            if (data == temp->data)
            {
                return i;
            }
            i++;
            temp = temp->next;
        }

        return -1;
    }

    // Новые методы

    bool IsEmpty() const
    {
        return count == 0;
    }

    int LastIndexOf(int value) const
    {
        if (count == 0)
            return -1;

        int lastIndex = -1;
        Node* current = head;
        int currentIndex = 0;

        while (current != nullptr)
        {
            if (current->data == value)
                lastIndex = currentIndex;

            current = current->next;
            currentIndex++;
        }

        return lastIndex;
    }

    void Reverse()
    {
        Node* prev = nullptr;
        Node* current = head;
        Node* next = nullptr;

        while (current != nullptr)
        {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }

        head = prev;
    }

    void SortAsc()
    {
        if (count <= 1)
            return;

        Node* current = head;
        Node* index = nullptr;
        int temp;

        while (current != nullptr)
        {
            index = current->next;

            while (index != nullptr)
            {
                if (current->data > index->data)
                {
                    temp = current->data;
                    current->data = index->data;
                    index->data = temp;
                }

                index = index->next;
            }

            current = current->next;
        }
    }

    void Shuffle()
    {
        if (count <= 1)
            return;

        srand(time(0));

        for (int i = count - 1; i > 0; --i)
        {
            int j = rand() % (i + 1);
            SwapNodes(i, j);
        }
    }

    int* ToArray() const
    {
        if (count == 0)
            return nullptr;

        int* array = new int[count];
        Node* current = head;
        int index = 0;

        while (current != nullptr)
        {
            array[index++] = current->data;
            current = current->next;
        }

        return array;
    }

    int& operator[](unsigned int index)
    {
        if (index < count)
        {
            Node* current = head;
            for (unsigned int i = 0; i < index; ++i)
                current = current->next;

            return current->data;
        }
        else
        {
            cerr << "Error: Index out of bounds.\n";
            static int placeholder;
            return placeholder;
        }
    }

    friend ostream& operator<<(ostream& os, const SinglyLinkedList& list)
    {
        Node* current = list.head;
        while (current != nullptr)
        {
            os << current->data << " ";
            current = current->next;
        }
        return os;
    }

private:
    void SwapNodes(int i, int j)
    {
        if (i == j)
            return;

        int minIndex = min(i, j);
        int maxIndex = max(i, j);

        Node* minNode = GetNodeAtIndex(minIndex);
        Node* maxNode = GetNodeAtIndex(maxIndex);

        int temp = minNode->data;
        minNode->data = maxNode->data;
        maxNode->data = temp;
    }

    Node* GetNodeAtIndex(int index) const
    {
        if (index >= count)
            return nullptr;

        Node* current = head;
        for (int i = 0; i < index; ++i)
            current = current->next;

        return current;
    }
};
int main()
{
    setlocale(LC_ALL, "russian");

    SinglyLinkedList sll;

    // вставка в конец списка
    sll.AddToTail(10);
    sll.AddToTail(20);
    sll.AddToTail(30);
    sll.AddToTail(40);
    cout << "Список после вставки в конец:\n";
    sll.Print();

    // вставка в начало списка
    sll.AddToHead(50);
    sll.AddToHead(60);
    sll.AddToHead(70);
    sll.AddToHead(80);
    cout << "Список после вставки в начало:\n";
    sll.Print();

    // количество элементов, поиск элементов
    cout << "Количество элементов в списке: " << sll.GetCount() << "\n";
    cout << "Индекс элемента 70: " << sll.IndexOf(70) << ", индекс элемента 90: " << sll.IndexOf(90) << "\n";

    // вставка по позиции
    sll.InsertInto(-1, -1);
    cout << "Список после вставки -1 по индексу -1:\n";
    sll.Print();
    sll.InsertInto(2, 2);
    cout << "Список после вставки 2 по индексу 2:\n";
    sll.Print();
    sll.InsertInto(22, 22);
    cout << "Список после вставки 22 по индексу 22:\n";
    sll.Print();

    // удаление с начала списка
    sll.DeleteFromHead();
    sll.DeleteFromHead();
    sll.DeleteFromHead();
    cout << "Список после удаления из начала:\n";
    sll.Print();

    // удаление с конца списка
    sll.DeleteFromTail();
    sll.DeleteFromTail();
    sll.DeleteFromTail();
    cout << "Список после удаления с конца:\n";
    sll.Print();

    // удаление по указанному индексу
    sll.DeleteByIndex(0);
    sll.DeleteByIndex(1);
    sll.DeleteByIndex(2);
    cout << "Список после удаления по индексу:\n";
    sll.Print();

    // очистка списка
    sll.Clear();
    cout << "Список после очистки:\n";
    sll.Print();

    // тестирование новых методов
    cout << "Тестирование новых методов:\n";

    // IsEmpty
    if (sll.IsEmpty())
        cout << "Список пуст.\n";
    else
        cout << "Список не пуст.\n";

    // LastIndexOf
    sll.AddToTail(10);
    sll.AddToTail(20);
    sll.AddToTail(30);
    sll.AddToTail(20);
    sll.AddToTail(40);
    cout << "Список для LastIndexOf:\n";
    sll.Print();
    int lastIndex = sll.LastIndexOf(20);
    cout << "Последний индекс элемента 20: " << lastIndex << "\n";

    // Reverse
    sll.Reverse();
    cout << "Список после Reverse:\n";
    sll.Print();

    // SortAsc
    sll.SortAsc();
    cout << "Список после SortAsc:\n";
    sll.Print();

    // Shuffle
    sll.Shuffle();
    cout << "Список после Shuffle:\n";
    sll.Print();

    // ToArray
    int* array = sll.ToArray();
    cout << "Массив, полученный из списка:\n";
    for (int i = 0; i < sll.GetCount(); i++)
    {
        cout << array[i] << " ";
    }
    cout << "\n";

    // Перегрузка операции []
    cout << "Элементы списка через операцию []:\n";
    for (int i = 0; i < sll.GetCount(); i++)
    {
        cout << sll[i] << " ";
    }
    cout << "\n";

    // Перегрузка операции <<
    cout << "Вывод списка через перегруженную операцию <<:\n";
    cout << sll;

    // Освобождение памяти
    delete[] array;

    return 0;
}
