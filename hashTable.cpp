#include "hashTable.h"
/*
private:
int m_numOfObjects;
int m_tableSize;
int (*m_hashFunc)(int);
AVLTree<int, std::shared_ptr<Customer> >* m_hashTableWithTrees;

void enlargeTable();

public:
hashTable();
~hashTable();
void insert(int key, std::shared_ptr<Customer>);
std::shared_ptr<Customer> find(int key);
*/

hashTable::hashTable():
m_numOfObjects(0),
m_tableSize(MIN_SIZE),
m_hashFunc(HashFunc(MIN_SIZE)),
m_hashTableWithTrees(new AVLTree<int,std::shared_ptr<Customer>>[MIN_SIZE])
{}

hashTable::~hashTable()
{
    delete[] m_hashTableWithTrees;
}

void hashTable::insert(int key, std::shared_ptr<Customer> customer)
{
    int placeInTable = m_hashFunc(key);
    m_hashTableWithTrees[placeInTable].insert(key, customer);
    m_numOfObjects++;
    if(m_numOfObjects == m_tableSize)
        enlargeTable();
}

std::shared_ptr<Customer> hashTable::find(int key) const
{
    int placeInTable = m_hashFunc(key);
    return m_hashTableWithTrees[placeInTable].find(key);
}

void hashTable::enlargeTable()
{
    AVLTree<int, std::shared_ptr<Customer>>* newHashTableWithTrees = new AVLTree<int, std::shared_ptr<Customer>>[m_tableSize*INCREMENT_FACTOR];
    HashFunc newHashFunc = HashFunc(m_tableSize*2);
    for(int i=0; i<m_tableSize; i++)
    {
        for(auto it = m_hashTableWithTrees[i].begin(); it!=m_hashTableWithTrees[i].end(); ++it )
        {
            int placeInNewTable = newHashFunc(it->get()->getId());
            newHashTableWithTrees[placeInNewTable].insert(it->get()->getId(),*it);
        }
    }
    delete[] m_hashTableWithTrees;
    m_hashTableWithTrees = newHashTableWithTrees;
    m_tableSize = m_tableSize*INCREMENT_FACTOR;
    m_hashFunc=newHashFunc;
}