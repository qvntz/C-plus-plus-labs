#include<iostream>
#include <iomanip>

using namespace std;


template<typename t1, typename t2>
class AVLTree {
    struct Node {
        t1 key;
        t2 value;

        Node* parent;
        Node* left;
        Node* right;

        int height;
    };

    Node* root;
    int size_;

    //очистить дерево/передать корень дерева
    void makeEmpty(Node* node) {
        if (node == NULL) return;
        makeEmpty(node->left);
        makeEmpty(node->right);
        size_ = 0;
        delete node;
    }

    //создание узла с заданным ключом и значением, возвращает указатель на новый узел
    Node* newNode(t1 key, t2 value) {
        Node* temp = new Node;
        temp->key = key;
        temp->value = value;
        temp->left = temp->right = NULL;
        temp->parent = NULL;
        return temp;
    }

    //ищет узел с заданным ключом и возвращает его
    Node* findKey(Node* node, t1 key) {
        if (node == nullptr) return nullptr;
        else if (node->key == key) return node;
        else if (key > node->key) return findKey(node->right, key);
        return findKey(node->left, key);
    }

    //ищет узел с заданным значением и возвращает его
    Node* findValue(Node* node, t2 value) {
        if (node == nullptr) return nullptr;
        else if (node->value == value) return node;
        else if (value > node->value) return findValue(node->right, value);
        return findValue(node->left, value);
    }


    //вставка и балансировка дерева (данные для вставки, узел корневого дерева)
    Node* insert(t1 key, t2 value, Node* node) {
        if (node == NULL) {
            node = newNode(key, value);
            node->key = key;
            node->value = value;
            node->height = 0;
            node->left = node->right = NULL;
        }
        else if (key < node->key) {
            Node* leftChild = insert(key, value, node->left);
            node->left = leftChild;
            leftChild->parent = node;
            if (height(node->left) - height(node->right) == 2) {
                if (key < node->left->key)
                    node = singleRightRotate(node);
                else
                    node = doubleRightRotate(node);
            }
        }
        else if (key > node->key) {
            Node* rightChild = insert(key, value, node->right);
            node->right = rightChild;
            rightChild->parent = node;
            if (height(node->right) - height(node->left) == 2) {
                if (key > node->right->key)
                    node = singleLeftRotate(node);
                else
                    node = doubleLeftRotate(node);
            }
        }

        node->height = max(height(node->left), height(node->right)) + 1;
        return node;
    }

    //однократное вращение поддерева вправо
    Node* singleRightRotate(Node*& node) {
        Node* tmp = node->left;
        node->left = tmp->right;
        if (tmp->right != nullptr) tmp->right->parent = node;
        tmp->parent = node->parent;
        tmp->right = node;
        node->parent = tmp;

        node->height = max(height(node->left), height(node->right)) + 1;
        tmp->height = max(height(tmp->left), node->height) + 1;
        return tmp;
    }

    //тоже самое влево
    Node* singleLeftRotate(Node*& node) {
        Node* tmp = node->right;
        node->right = tmp->left;
        if (tmp->left != nullptr)
            tmp->left->parent = node;
        tmp->parent = node->parent;
        tmp->left = node;
        node->parent = tmp;


        node->height = max(height(node->left), height(node->right)) + 1;
        tmp->height = max(height(node->right), node->height) + 1;
        return tmp;
    }

    //два раза влево
    Node* doubleLeftRotate(Node*& node) {
        node->right = singleRightRotate(node->right);
        return singleLeftRotate(node);
    }

    //два раза вправо
    Node* doubleRightRotate(Node*& node) {
        node->left = singleLeftRotate(node->left);
        return singleRightRotate(node);
    }

    //поиск минимального значения поддерева
    Node* findMin(Node* node) {
        if (node == NULL) return NULL;
        else if (node->left == NULL) return node;
        else return findMin(node->left);
    }

    //а тут максимального
    Node* findMax(Node* node) {
        if (node == NULL) return NULL;
        else if (node->right == NULL) return node;
        else return findMax(node->right);
    }

    //удаляет узел с заданными данными из поддерева
    Node* remove(t1 key, t2 value, Node* node) {
        Node* temp;

        if (node == NULL) return NULL;
        else if (key < node->key) node->left = remove(key, value, node->left);
        else if (key > node->key) node->right = remove(key, value, node->right);

        else if (node->left && node->right) {
            temp = findMin(node->right);
            node->key = temp->key;
            node->value = temp->value;
            node->right = remove(node->key, node->value, node->right);
        }
        else {
            temp = node;
            if (node->left == NULL) node = node->right;
            else if (node->right == NULL) node = node->left;
            delete temp;
        }
        if (node == NULL) return node;

        node->height = max(height(node->left), height(node->right)) + 1;

        if (height(node->left) - height(node->right) == 2) {
            if (height(node->left->left) - height(node->left->right) == 1) return singleLeftRotate(node);
            else return doubleLeftRotate(node);
        }
        else if (height(node->right) - height(node->left) == 2) {
            if (height(node->right->right) - height(node->right->left) == 1) return singleRightRotate(node);
            else return doubleRightRotate(node);
        }
        return node;
    }

    //возвращает высоту заданного поддерева / -1 если корень равен нулевому указателю
    int height(Node* node) {
        return node == NULL ? -1 : node->height;
    }

    //возврат баланса данного узла ( разница между высотой правого и левого поддерева )
    int getBalance(Node* node) {
        return node == NULL ? 0 : height(node->left) - height(node->right);
    }

    //тут принт как в питоне только на с++ ( спейс - отступ )
    void print(Node* node, int space) {
        int COUNT = 10;
        if (node == NULL) return;
        space += COUNT;
        print(node->right, space);

        cout << "\n";
        for (int i = COUNT; i < space; i++) cout << " ";
        cout << node->key << "  " << node->value << endl;
        print(node->left, space);
    }

    void change_size(const int& digit) {
        size_ += digit;
    }

public:
    template<typename K, typename I>
    class Iterator {
        Node* it;
    public:
        //тут конструктор по умолчанию, как в с++
        Iterator() { it = nullptr; }

        //конструктор с указателем на узел
        Iterator(Node* element) {
            it = element;
        }

        //деструктор
        ~Iterator() {}

        //конструктор копирования
        Iterator(const Iterator& cc) { it = cc.it; }


        //оператор равно
        Iterator operator=(const Iterator& iterator) {
            if (this == &iterator) return *this;
            it = iterator.it;
            return *this;
        }

        //оператор плюс (переместить итератор вперед на длину позиции)
        Iterator operator+(int length) {
            if (length > 0) for (int i = 0; it && it->next && i < length; i++) it = it->next;
            return *this;
        }

        //тоже самое только минус
        Iterator operator-(int length) {
            if (length > 0) for (int i = 0; it && it->next && i < length; i++) it = it->prev;
            return *this;
        }


        //оператор плюс плюс
        Iterator& operator++() {
            Node* p;

            if (it == nullptr) {
                if (it == nullptr) return nullptr;
                while (it->left != nullptr) {
                    it = it->left;
                }
            }
            else if (it->right != nullptr) {
                it = it->right;

                while (it->left != nullptr) {
                    it = it->left;
                }
            }
            else {
                p = it->parent;
                while (p != nullptr && it == p->right) {
                    it = p;
                    p = p->parent;
                }
                it = p;
            }
            return *this;
        }

        //какой-то из них постфиксный, а какой-то префиксный ( не помню )
        const Iterator<K, I> operator++(int) {
            if (!it) return *this;
            else {
                Node* p;
                auto* temporary = new Iterator(it);
                if (it == nullptr) {
                    while (it->left != nullptr) {
                        it = it->left;
                    }
                }
                else if (it->right != nullptr) {
                    it = it->right;

                    while (it->left != nullptr) {
                        it = it->left;
                    }
                }
                else {
                    p = it->parent;
                    while (p != nullptr && it == p->right) {
                        it = p;
                        p = p->parent;
                    }
                    it = p;
                }
                return *temporary;
            }
        }

        //это как плюс плюс только минус минус
        Iterator& operator--() {
            Node* p;

            if (it == nullptr) {
                if (it == nullptr) return nullptr;
                while (it->right != nullptr) {
                    it = it->right;
                }
            }
            else if (it->left != nullptr) {
                it = it->left;

                while (it->right != nullptr) {
                    it = it->right;
                }
            }
            else {
                p = it->parent;
                while (p != nullptr && it == p->left) {
                    it = p;
                    p = p->parent;
                }
                it = p;
            }
            return *this;
        }

        //это как минус минус только с другой стороны
        const Iterator<K, I> operator--(int) {
            if (!it) return *this;
            else {
                Node* p;
                auto* temporary = new Iterator(it);
                if (it == nullptr) {
                    while (it->right != nullptr) {
                        it = it->right;
                    }
                }
                else if (it->left != nullptr) {
                    it = it->left;

                    while (it->right != nullptr) {
                        it = it->right;
                    }
                }
                else {
                    p = it->parent;
                    while (p != nullptr && it == p->left) {
                        it = p;
                        p = p->parent;
                    }
                    it = p;
                }
                return *temporary;
            }
        }

        //это как равно, только сравнение ( сравнивает что это один объект )
        bool operator==(Iterator iterator) const { return it == iterator.it; }

        //это как сравнение, только на неравенство
        bool operator!=(Iterator iterator) const { return it != iterator.it; }

        //разыменование оператора
        Node& operator*() const { return *it; }

        //доступ к указателю итератора
        Node* operator->() const { return it; }

        //геттер кей
        t1 getKey() { return it->key; }

        //геттер валуе
        t2 getValue() { return it->value; }

        //оператор вывода
        friend ostream& operator<<(ostream& output, const Iterator& iter) {
            output << *iter;
            return output;
        }

    };

    typedef Iterator<t1, t2> TreeIterator;
    typedef Iterator<const t1, const t2> ConstTreeIterator;

    //итератор на начало
    TreeIterator begin() {
        Node* curr = root;
        if (curr != NULL)
            while (curr->left != NULL)
                curr = curr->left;

        return TreeIterator(curr);
    }

    //конец
    TreeIterator end() {
        return TreeIterator(nullptr);
    }

    //константый итератор на первый элемент
    ConstTreeIterator constBegin() const { return ConstRingIterator(root); }

    //константный итератор на последний элемент
    ConstTreeIterator constEnd() const { return ConstRingIterator(root); }

    //конструктор
    AVLTree() {
        size_ = 0;
        root = NULL;
    }

    //конструктор копирования
    AVLTree(AVLTree& tree) {
        root = NULL;
        for (TreeIterator it = tree.begin(); it != tree.end(); it++) {
            insert(it->key, it->value);
        }
        change_size(tree.size());
    }

    ~AVLTree() {
        makeEmpty(root);
    }

    //вставка в это дерево (key, value)
    void insert(t1 x, t2 y=1) {
        if (searchKey(x) == nullptr) {
            root = insert(x, y, root);
        }
        else {
            searchKey(x)->value += y;
        }

        change_size(y);
    }

    //удаление узла по ключу
    void remove(t1 x) {
        t2 y = searchKey(x)->value;
        change_size(-y);
        root = remove(x, y, root);
    }

    int size() const {
        return size_;
    }

    //ищет узел с заданным ключом
    Node* searchKey(t1 key) {
        return findKey(root, key);
    }

    //ищет узел с заданным значением
    Node* searchValue(t2 value) {
        return findValue(root, value);
    }

    //печатает дерево
    void print() {
        if (root == nullptr) cout << "Empty tree" << endl;
        print(root, 1);
    }

    //оператор скобочек
    t2 operator[](t1 key) {
        if (searchKey(key) == nullptr) {
            throw std::invalid_argument("Tree does not have such key");
        }
        t2 val = searchKey(key)->value;
        return val;
    }

    //оператор круглых скобочек
    t1 operator()(t2 value) {
        if (searchValue(value) == nullptr) {
            throw std::invalid_argument("Tree does not have such key");
        }
        t1 key = searchValue(value)->key;
        return key;
    }

    //равно равно
    friend bool operator==(AVLTree& tree1, AVLTree& tree2) {
        if (tree2.root == nullptr && tree1.root == nullptr) return true;
        TreeIterator it = tree2.begin();
        for (TreeIterator itTree = tree1.begin(); itTree != tree1.end(); itTree++) {
            if (it == nullptr && itTree == nullptr) return true;
            if (it == nullptr || itTree == nullptr) return false;
            if (it->key != itTree->key && it->value != itTree->value) return false;
            it++;
        }
        return true;
    }


    //оператор равно
    AVLTree& operator=(const AVLTree& tree) {
        auto* newTree = new AVLTree(tree);
        return *newTree;
    }

    AVLTree& operator-=(const int& digit) {
        if (searchKey(digit) == nullptr) {
            return *this;
        }
        else if (searchKey(digit)->value <= 1) {
            remove(digit);
            
        }
        else {
            searchKey(digit)->value--;
            change_size(-1);
        }
        
        return *this;
    }

    AVLTree& operator+=(const int& digit) {
        if (searchKey(digit) == nullptr) {
            insert(digit, 1);
        }
        else {
            searchKey(digit)->value++;
            change_size(1);
        }

        return *this;
    }

};