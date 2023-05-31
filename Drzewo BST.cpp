// ALGO2 IS1 212A LAB03
// Michał Sprysak
// sm49406@zut.edu.pl

#include <iostream>
#include <string>

using namespace std;

template<typename T>
class NodeBST
{
public:
    T dane;
    NodeBST<T>* leftChild;
    NodeBST<T>* parent;
    NodeBST<T>* rightChild;
    int id;
    NodeBST(T dane, int id)
    {
        this->id = id;
        this->dane = dane;

    }
};

template<typename T>
class TreeBST
{
public:
    NodeBST<T>* root = NULL;
    int r;
    TreeBST()
    {
        this->r = 0;
    }



    void delTree(NodeBST<T>* pom)
    {
        if (pom->rightChild != NULL)
            delTree(pom->rightChild);
        if (pom->leftChild != NULL)
            delTree(pom->leftChild);
        r--;
        delete pom;
        if (r == 0)
        {
            root = NULL;
            cout << "\nPomyslnie usunieto\n";
        }
    }



    string str(NodeBST<T>* pom = nullptr)
    {
        string s;
        if (pom == nullptr) {
            pom = root;
        }
        if (root == nullptr)
        {
            s = "\nDrzewo jest puste\n";
            return s;
        }
        if (pom->leftChild != nullptr) { //inorder
            s += str(pom->leftChild);
        }
        s += "(" + to_string(pom->id) + ": [p: ";
        if (pom->parent != nullptr) {
            s += to_string(pom->parent->id) + ", l: ";
        }
        else if (pom->parent == nullptr) {
            s += "NULL, l: ";
        }
        if (pom->leftChild != nullptr) {
            s += to_string(pom->leftChild->id) + ", r: ";
        }
        else if (pom->leftChild == nullptr) {
            s += "NULL , r: ";
        }
        if (pom->rightChild != nullptr) {
            s += to_string(pom->rightChild->id) + "], data: ";
        }
        else if (pom->rightChild == nullptr) {
            s += "NULL], data: ";
        }
        s += to_string(pom->dane) + "),\n";
        if (pom->rightChild != nullptr)
            s += str(pom->rightChild);
        return s;

    }
    int BSTHeight(NodeBST<T>* pom) {
        int lH = 0;
        int rH = 0;
        if (pom == NULL)
            return 0;
        else {
            lH = BSTHeight(pom->leftChild);
            rH = BSTHeight(pom->rightChild);
            if (lH >= rH)
                return lH + 1;
            else
            {
                return rH + 1;
            }
        }
    }

    void inOrder(NodeBST<T>* pom);
    void addElement(T dane);
    NodeBST<T>* search(T dane);
    NodeBST<T>* delNode(T dane);
    void preOrder(NodeBST<T>* pom);
};


template<typename T>
void TreeBST<T>::preOrder(NodeBST<T>* pom)
{
    if (pom == NULL)
        return;

    cout << to_string(pom->dane) + " ";
    preOrder(pom->leftChild);
    preOrder(pom->rightChild);
}
template<typename T>
void TreeBST<T>::inOrder(NodeBST<T>* pom)
{
    if (pom == NULL)
        return;
    inOrder(pom->leftChild);
    cout << to_string(pom->dane) + " ";
    inOrder(pom->rightChild);
}
template<typename T>
NodeBST<T>* TreeBST<T>::search(T dane)
{
    if (root == NULL)
    {
        return NULL;
    }
    else
    {
        NodeBST<T>* pom = root;
        do
        {
            if (dane > pom->dane)
            {
                if (pom->rightChild == NULL)
                {
                    return NULL;
                }
                else
                {
                    pom = pom->rightChild;
                }
            }
            else if (dane <= pom->dane)
            {
                if (pom->leftChild == NULL)
                {
                    return NULL;
                }
                else
                {
                    pom = pom->leftChild;
                }
            }
        } while (dane != pom->dane);
        return pom;
    }
}
template<typename T>
void TreeBST<T>::addElement(T dane)
{
    if (root == NULL)
    {
        root = new NodeBST<T>(dane, r);
        r++;
    }
    else
    {
        NodeBST<T>* pom = root;
        do
        {
            if (dane > pom->dane)
            {
                if (pom->rightChild == NULL)
                {
                    pom->rightChild = new NodeBST<T>(dane, r);
                    pom->rightChild->parent = pom;
                    r++;
                    return;
                }
                else
                {
                    pom = pom->rightChild;
                }
            }
            else if (dane <= pom->dane)
            {
                if (pom->leftChild == NULL)
                {
                    pom->leftChild = new NodeBST<T>(dane, r);
                    pom->leftChild->parent = pom;
                    r++;
                    return;
                }
                else
                {
                    pom = pom->leftChild;
                }
            }
        } while (true);
    }
}
template<typename T>
NodeBST<T>* TreeBST<T>::delNode(T dane)
{
    NodeBST<T>* pom = search(dane);
    if (pom != NULL)
    {
        if (pom->leftChild == NULL && pom->rightChild == NULL)
        {
            if (pom->parent->leftChild == pom)
            {
                pom->parent->leftChild = NULL;
                delete pom;
            }
            else if (pom->parent->rightChild == pom)
            {
                pom->parent->rightChild = NULL;
                delete pom;
            }
        }
        else if (pom->leftChild != NULL && pom->rightChild == NULL)
        {
            if (pom->parent->leftChild == pom)
            {
                pom->parent->leftChild = pom->leftChild;
                pom->leftChild->parent = pom->parent;
                delete pom;
            }
            else if (pom->parent->rightChild == pom)
            {
                pom->parent->rightChild = pom->leftChild;
                pom->leftChild->parent = pom->parent;
                delete pom;
            }
        }
        else if (pom->leftChild == NULL && pom->rightChild != NULL)
        {
            if (pom->parent->rightChild == pom)
            {
                pom->parent->rightChild = pom->rightChild;
                pom->rightChild->parent = pom->parent;
                delete pom;
            }
            else if (pom->parent->leftChild == pom)
            {
                pom->parent->leftChild = pom->rightChild;
                pom->rightChild->parent = pom->parent;
                delete pom;
            }
        }
        else if (pom->leftChild != NULL && pom->rightChild != NULL)
        {
            NodeBST<T>* pom2 = pom;
            pom2 = pom2->leftChild;
            do
            {
                if (pom2->rightChild != NULL)
                    pom2 = pom2->rightChild;
            } while (pom2->rightChild != NULL);
            pom->dane = pom2->dane;
            if (pom2->leftChild == NULL)
            {
                pom2->parent->rightChild = NULL;
                delete pom2;
            }
            else
            {
                pom2->leftChild->parent = pom2->parent;
                pom2->parent->rightChild = pom2->leftChild;
                delete pom2;
            }
        }
        r--;
    }
}

int main()
{
    TreeBST<int>* o1 = new TreeBST<int>;

    o1->addElement(9);
    o1->addElement(5);
    o1->addElement(21);
    o1->addElement(3123);
    o1->addElement(684);
    o1->addElement(232);
    //cout<< o1->search(31);
    //o1->delTree(o1->root);
    cout << "Drzewo BST:\n";
    cout << "Rozmiar: " << o1->r << endl;
    cout << "Wysokosc: " << o1->BSTHeight(o1->root) << endl;
    cout << o1->str();

    cout << "\nIn order:\n";
    o1->inOrder(o1->root);
    cout << "\nPre Order:\n";
    o1->preOrder(o1->root);
    o1->delTree(o1->root);

    return 0;
}
