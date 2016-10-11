//
//  SkipList.cpp
//

#include "SkipList.h"
#include "Flags.h"

/* **************************************************************** */

#if CONSTRUCTOR || ALL
// TODO: constructor
template <class T>
SkipList<T>::SkipList()
{
    head = new Node<T>(T(),maxHeight);
    height = 1;
}
#endif

/* **************************************************************** */

#if DESTRUCTOR || ALL
// TODO: destructor
template <class T>
SkipList<T>::~SkipList()
{
    makeEmpty();
    head=NULL;
    delete head;
}
#endif

/* **************************************************************** */

#if FIND || ALL
// TODO: find() method
template <class T>
bool SkipList<T>::find(const T &x) const {
    bool ans = false;
    Node<T> *curr = head;
    if (!isEmpty())
    {
        for (int i = height-1; i >= 0; i--)
        {
            while (curr->next[i] != NULL && curr->next[i]->data < x )
            {
                curr = curr->next[i];
            }
        }
        curr = curr->next[0];
        if(curr != NULL && curr->data == x)
        {
            ans= true;
        }
    }
    curr = NULL;
    delete curr;
    return ans;
}
#endif

/* **************************************************************** */

#if INSERT || ALL
// TODO: insert() method
template <class T>
void SkipList<T>::insert(const T &searchKey)
{
    Node<T> *update[maxHeight];
    Node<T> *x=head;
    if(this->find(searchKey)==0)
    {
        for (int i = height-1; i >= 0; i--)
        {
            while (x->next[i] != NULL && x->next[i]->data < searchKey)
            {
                x = x->next[i];
            }
            update[i] = x;
        }
        if(x->data == searchKey)
        {
            x->data=searchKey;
        }
        else
        {
            int lvl = randomLevel();
            if(lvl > height-1)
            {
                for(int i=height; i < lvl; i++)
                {
                    update[i]=head;
                }
                height=lvl;

            }
            x=new Node<T>(searchKey,lvl);
            for(int i=0;i<lvl;i++)
            {
                x->next[i]=update[i]->next[i];
                update[i]->next[i]=x;
            }
        }
    }
    x=NULL;
    delete x;
}
#endif

/* **************************************************************** */

#if REMOVE || ALL
// TODO: remove() method
template <class T>
void SkipList<T>::remove(const T &searchKey)
{
    if(this->isEmpty() == false && this->find(searchKey)==1)
    {
        Node<T> *update[maxHeight];
        Node<T> *x=head;
        for (int i = height-1; i >= 0; i--)
        {
            while (x->next[i] != NULL && x->next[i]->data < searchKey)
            {
                x = x->next[i];
            }
            update[i] = x;
        }
        x = x->next[0];
        if (x->data == searchKey)
        {
            for (int i = 0; i <= height-1; i++)
            {
                if (update[i]->next[i] != x)
                {
                    break;
                }
                update[i]->next[i] = x->next[i];
            }
            x = NULL;
            delete x;
            while (height-1 > 0 && head->next[height-1] == NULL)
            {
                height = height - 1;
            }
        }
        x=NULL;
        delete x;
    }
}
#endif

/* **************************************************************** */

#if ISEMPTY || ALL
// TODO: isEmpty() method
template <class T>
bool SkipList<T>::isEmpty() const
{
    bool ans = false;
    if(head->next[0] == NULL)
    {
        ans=true;
    }
    return ans;
}
#endif

/* **************************************************************** */

#if MAKEEMPTY || ALL
// TODO: makeEmpty() method
template <class T>
void SkipList<T>::makeEmpty()
{
    if(!isEmpty())
    {
        Node<T> *n = head->next[0];
        head->next[0]=NULL;
        Node<T> *del = NULL;
        while(n->next[0]!= NULL)
        {
            del=n;
            n=n->next[0];
            delete del;
        }
        delete n;
        del=NULL;
        delete del;
    }
    height=1;
}
#endif

/* **************************************************************** */

#if RANDOMLEVEL || ALL
// TODO: randomLevel() method
template <class T>
int SkipList<T>::randomLevel()
{
    int rand=1;
    while(getRandomNumber() < .5 && rand < height+1 && rand < maxHeight)
    {
        rand = rand + 1;
    }
    return rand;
}
#endif

/* **************************************************************** */



/* **************************************************************** */
// Do NOT modify anything below this line
/* **************************************************************** */

#ifndef BUILD_LIB
// random number generator
template <class T>
double SkipList<T>::getRandomNumber()
{
    static int i = 0;
    static double a[10] = {0.32945,0.15923,0.12982,0.16250,0.36537,0.64072,0.27597,0.83957,0.75531,0.22502};
    
    return a[(i++)%10];
}


// printList() method
template <class T>
void SkipList<T>::printList()
{
    Node<T> *n = head;
    
    if (isEmpty())
    {
        std::cout << "Empty List" << std::endl;
    } else {
        while(n->next[0] != NULL)
        {
            n = n->next[0];
            // Print node data
            std::cout << "Node " << n->data << " height " << n->height << ": ";
            
            // Print levels
            for (int i=(n->height - 1); i >= 0; i--) {
                std::cout << "Level " << i << " -> ";
                if (n->next[i] != NULL) {
                    std::cout << n->next[i]->data;
                } else {
                    std::cout << "NULL";
                }
                std::cout << ",";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}
#endif

template class SkipList<int>;


