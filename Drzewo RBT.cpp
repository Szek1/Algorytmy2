// ALGO2 IS1 212A LAB04
// Michał Sprysak
// sm49406@zut.edu.pl

#include <iostream>
#include <string>
#include <random>
using namespace std;

template<typename T>
class NodeRBT {
public:
    T dane;
    NodeRBT<T>* parent = nullptr;
    NodeRBT<T>* leftChild = NULL;
    NodeRBT<T>* rightChild = NULL;
    string clr = "Czerwony";
    int id;
    NodeRBT() {}
    NodeRBT(T dane, int id)
    {
        this->dane = dane;
        this->id = id;
        this->clr = clr;
    }
};

template<typename T>
class TreeRBT {
public:
    NodeRBT<T>* root = NULL;
    int r = 0;

    NodeRBT<T>* search(T dane) {
        NodeRBT<T>* pom = root;
        do
        {
            if (dane > pom->dane)
            {
                if (pom->rightChild == NULL)
                    return NULL;
                else
                    pom = pom->rightChild;

            }
            else if (dane < pom->dane) {
                if (pom->leftChild == NULL)
                    return NULL;
                else
                    pom = pom->leftChild;
            }
        } while (dane != pom->dane);
        return pom;
    }
    void preOrder(NodeRBT<T>* pom)
    {
        if (pom == NULL)
            return;

        cout << to_string(pom->dane) + " ";
        preOrder(pom->leftChild);
        preOrder(pom->rightChild);
    }
    void inOrder(NodeRBT<T>* pom)
    {
        if (pom == NULL)
            return;
        inOrder(pom->leftChild);
        cout << to_string(pom->dane) + " ";
        inOrder(pom->rightChild);
    }

    void delTree(NodeRBT<T>* pom)
    {
        if (root == NULL)
        {
            return;
        }
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
    int RBTHeight(NodeRBT<T>* pom) {
        int lH = 0;
        int rH = 0;
        if (pom == NULL)
            return 0;
        else {
            lH = RBTHeight(pom->leftChild);
            rH = RBTHeight(pom->rightChild);
            if (lH >= rH)
                return lH + 1;
            else
            {
                return rH + 1;
            }
        }
    }
    void addElement(T dane) {
        NodeRBT<T>* newNode = NULL;
        if (root == NULL) {
            root = new NodeRBT<T>(dane, r);
            root->clr = "Czarny";
            newNode = root;
            r++;
        }
        else {
            NodeRBT<T>* pom = root;
            while (newNode == NULL) {
                if (dane >= pom->dane)
                {
                    if (pom->rightChild == NULL)
                    {
                        pom->rightChild = new NodeRBT<T>(dane, r);
                        pom->rightChild->parent = pom;
                        pom->rightChild->clr = "Czerwony";
                        newNode = pom->rightChild;
                        r++;
                    }
                    else
                        pom = pom->rightChild;
                }
                else if (dane <= pom->dane) {
                    if (pom->leftChild == NULL)
                    {
                        pom->leftChild = new NodeRBT<T>(dane, r);
                        pom->leftChild->parent = pom;
                        pom->leftChild->clr = "Czerwony";
                        newNode = pom->leftChild;
                        r++;
                    }
                    else
                        pom = pom->leftChild;
                }

            }
        }
        fix(newNode);
        root->clr = "Czarny";
    }


    void fix(NodeRBT<T>* newNode) {
        NodeRBT<T>* uncle;
        NodeRBT<T>* tmp;
        while ((newNode->dane != root->dane) && (newNode->parent->clr == "Czerwony"))
        {
            if (newNode->parent == newNode->parent->parent->leftChild)
            {
                uncle = newNode->parent->parent->rightChild;
                if (uncle != NULL)
                {
                    if (uncle->clr == "Czerwony")
                    {
                        recol(newNode->parent);
                        recol(uncle);
                        recol(newNode->parent->parent);
                        newNode = newNode->parent->parent;
                    }
                    else if (uncle->clr == "Czarny")
                    {
                        if (newNode->parent->rightChild == newNode)
                        {
                            tmp = newNode->parent;
                            leftRot(newNode->parent, newNode);
                            newNode = tmp;
                        }
                        recol(newNode->parent);
                        recol(newNode->parent->parent);
                        rightRot(newNode->parent->parent, newNode->parent);
                    }
                }
                else if (uncle == NULL)
                {
                    if (newNode->parent->rightChild == newNode)
                    {
                        tmp = newNode->parent;
                        leftRot(newNode->parent, newNode);
                        newNode = tmp;
                    }
                    recol(newNode->parent);
                    recol(newNode->parent->parent);
                    rightRot(newNode->parent->parent, newNode->parent);
                }
            }
            else if (newNode->parent == newNode->parent->parent->rightChild)
            {
                uncle = newNode->parent->parent->leftChild;
                if (uncle != NULL)
                {
                    if (uncle->clr == "Czerwony")
                    {
                        recol(newNode->parent);
                        recol(uncle);
                        recol(newNode->parent->parent);
                        newNode = newNode->parent->parent;
                    }
                    else if (uncle->clr == "Czarny")
                    {
                        if (newNode == newNode->parent->leftChild)
                        {
                            tmp = newNode->parent;
                            rightRot(newNode->parent, newNode);
                            newNode = tmp;
                        }
                        recol(newNode->parent);
                        recol(newNode->parent->parent);
                        leftRot(newNode->parent->parent, newNode->parent);
                    }
                }
                else if (uncle == NULL)
                {
                    if (newNode == newNode->parent->leftChild)
                    {
                        tmp = newNode->parent;
                        rightRot(newNode->parent, newNode);
                        newNode = tmp;
                    }
                    recol(newNode->parent);
                    recol(newNode->parent->parent);
                    leftRot(newNode->parent->parent, newNode->parent);
                }
            }
        }

    }


    void rightRot(NodeRBT<T>* parent, NodeRBT<T>* child) {
        if (parent == parent->parent->rightChild) {
            child->parent = parent->parent;
            parent->parent->rightChild = child;
        }
        if (parent == parent->parent->leftChild) {
            child->parent = parent->parent;
            parent->parent->leftChild = child;
        }
        if (child->rightChild != NULL) {
            child->rightChild->parent = parent;
            parent->leftChild = child->rightChild;
        }
        
        child->rightChild = parent;
        parent->parent = child;
        if (parent->rightChild == parent->parent)
        {
            parent->rightChild = NULL;
        }
        if (parent->leftChild == parent->parent)
        {
            parent->leftChild = NULL;
        }
    }
    void leftRot(NodeRBT<T>* parent, NodeRBT<T>* child) {
        if (parent->parent == NULL) {
            child->parent = NULL;
            root = child;
        }
        else if (parent == parent->parent->leftChild) {
            child->parent = parent->parent;
            parent->parent->leftChild = child;
        }
        else if (parent = parent->parent->rightChild)
        {
            child->parent = parent->parent;
            parent->parent->rightChild = child;
        }
        if (child->leftChild != NULL) {
            child->leftChild->parent = parent;
            parent->rightChild = child->leftChild;
        }
        child->leftChild = parent;
        parent->parent = child;
        if (parent->rightChild == parent->parent)
        {
            parent->rightChild = NULL;
        }
        if (parent->leftChild == parent->parent)
        {
            parent->leftChild = NULL;
        }
    }
    void recol(NodeRBT<T>* newclr) {
        if (newclr->clr == "Czerwony")
            newclr->clr = "Czarny";
        else
            newclr->clr = "Czerwony";
    }

    string str(NodeRBT<T>* pom = NULL) {
        string s;
        if (pom == NULL)
            pom = root;
        if (root == NULL)
            pom = root;
        if (root == NULL) {
            s = "\nDrzewo jest puste\n";
            return s;
        }

        s += "(" + to_string(pom->id) + ": [" + pom->clr + ", p: ";
        if (pom->parent != NULL) {
            s += to_string(pom->parent->id) + ", l: ";
        }
        else {
            s += "NUll, l: ";
        }
        if (pom->leftChild != NULL) {
            s += to_string(pom->leftChild->id) + ", r: ";
        }
        else
            s += "NULL, r: ";
        if (pom->rightChild != NULL) {
            s += to_string(pom->rightChild->id) + "] (";
        }
        else
            s += "NULL] (";
        s += to_string(pom->dane) + ")),\n";
        if (pom->leftChild != NULL) {
            s += str(pom->leftChild);
        }
        if (pom->rightChild != NULL)
            s += str(pom->rightChild);
        return s;
    }

};

int main()
{
    TreeRBT<int>* o1 = new TreeRBT<int>;
    o1->addElement(55);
    o1->addElement(69);
    o1->addElement(62);
    o1->addElement(57);
    o1->addElement(35);
    o1->addElement(83);
    o1->addElement(72);
    o1->addElement(74);
    //o1->delTree(o1->root);
    cout << "Drzewo RBT\n";
    cout << "Rozmiar: " << o1->r << endl;
    cout << "Wysokosc: " << o1->RBTHeight(o1->root) << endl;
    cout << o1->str();
    o1->delTree(o1->root);
    return 0;
}

