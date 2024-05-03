#ifndef _RB_TREE_H_
#define _RB_TREE_H_
#include<bits/stdc++.h>
enum COLOR{
    RED,BLACK
};

template <class K,class V>
struct _treeNode
{
    std::pair<K,V> _val;
    COLOR _color;
    _treeNode<K,V> *_leftChild;
    _treeNode<K,V> *_rightChild;
    _treeNode<K,V> *_parent;
    _treeNode(const std::pair<K,V> &val = std::pair<K,V>(), const COLOR &color = RED,
        _treeNode<K,V> *leftChild = nullptr, _treeNode<K,V> *rightChild = nullptr, 
        _treeNode<K,V> *parent = nullptr)
    : _val(val), _color(color), _leftChild(leftChild), _rightChild(rightChild), _parent(parent){}
};

template <class K, class V>
class Iterator{
public:
    Iterator(){iterator = nullptr;}
    Iterator(const Iterator& it){*this = it;}
    Iterator(_treeNode<K,V>* it){iterator = it;}
    ~Iterator(){iterator = nullptr;}
    std::pair<K,V> operator *() const{ //取结点pair的值,修改这个不会修改树结点的值
        if(iterator==nullptr) return std::pair<K,V>();
        return iterator->_val;
    }
    std::pair<K,V>* operator ->() const{ //返回指向结点的pair的指针,可以修改,修改K会破坏树结构
        if(iterator==nullptr) return nullptr;
        return &iterator->_val;
    }
    Iterator<K,V> operator ++(){ //前++
        *this = findNextNode();
        return *this;
    }
    Iterator<K,V> operator ++(int){ //后++
        Iterator temp = *this;
        *this = findNextNode();
        return temp;
    }
    Iterator<K,V> operator --(){ //前--
        *this = findPreNode();
        return *this;
    }
    Iterator<K,V> operator --(int){ //后--
        Iterator temp = *this;
        *this = findPreNode();
        return temp;
    }
    bool operator ==(const Iterator<K,V>& t)const {        //迭代器判等
        return this->iterator == t.iterator;
    }
    bool operator !=(const Iterator<K,V>& t)const {        //迭代器判不等
        return !(*this == t);  //利用判等
    }
    Iterator<K,V> findNextNode() const{
        if(iterator==nullptr) return *this;
        _treeNode<K,V>* cur = iterator;
        //右子树最小值
        if(cur->_rightChild){ //有右子树
            cur = cur->_rightChild;
            while(cur->_leftChild){
                cur = cur->_leftChild;
            }
            return Iterator<K,V>(cur);
        }else{ //没有右子树
            //一直向上寻找
            while(cur->_parent && cur->_parent->_rightChild == cur){
                cur = cur->_parent;
            }
            if(cur->_parent && cur->_parent->_leftChild==cur){
                cur = cur->_parent;
                return Iterator<K,V>(cur);
            }
        }
        return Iterator<K,V>(nullptr);
    }
    Iterator<K,V> findPreNode() const{
        if(iterator==nullptr) return *this;
        _treeNode<K,V>* cur = iterator;
        //左子树最大值
        if(cur->_leftChild){ //有左子树
            cur = cur->_leftChild;
            while(cur->_rightChild){
                cur = cur->_rightChild;
            }
            return Iterator<K,V>(cur);
        }else{ //没有左子树
            //一直向上寻找
            while(cur->_parent && cur->_parent->_leftChild == cur){
                cur = cur->_parent;
            }
            if(cur->_parent && cur->_parent->_rightChild==cur){
                cur = cur->_parent;
                return Iterator<K,V>(cur);
            }
        }
        return Iterator<K,V>(nullptr);
    }
private:
    _treeNode<K,V>* iterator;
};

template <class K,class V>
class _rbTree{
public:
    _rbTree(){_root = nullptr;_size=0;}
    ~_rbTree();
    void delSubTree(_treeNode<K,V>*);
    _treeNode<K,V>* find(const K&) const;
    bool isLeftChild(_treeNode<K,V>*) const;
    bool isRightChild(_treeNode<K,V>*) const;
    void leftRotate(_treeNode<K,V>*);
    void rightRotate(_treeNode<K,V>*);
    void insert(const std::pair<K,V>&);
    void insert(const K& fir, const V& sec){
        insert(make_pair(fir,sec));
    }
    void erase(const K&);
    std::pair<K,V> pop_root(){
        std::pair<K,V> p= _root->_val;
        erase(p.first);
        return p;
    }
    size_t size() const{return _size;}
    void debug() const;
    Iterator<K,V> begin() const{ //找最小值
        _treeNode<K,V>* cur = _root;
        while(cur && cur->_leftChild){
            cur = cur->_leftChild;
        }
        return Iterator<K,V>(cur);
    }
    Iterator<K,V> end() const{return Iterator<K,V>();}
private:
    _treeNode<K,V> *_root;
    size_t _size;
};

template <class K,class V>
_treeNode<K,V>* _rbTree<K,V>::find(const K &key) const
{
    _treeNode<K,V>* cur = _root;
    while(cur){
        if(cur->_val.first == key){
            return cur;
        }
        if(cur->_val.first < key) cur = cur->_rightChild;
        else cur = cur ->_leftChild;
    }
    return nullptr;
}

template <class K,class V>
bool _rbTree<K,V>::isLeftChild(_treeNode<K,V>* x) const //节点x是否是左孩子
{
    if(x->_parent==nullptr) return false;
    if(x->_parent->_leftChild==nullptr) return false;
    if(x->_parent->_leftChild->_val == x->_val) return true;
    return false;
}

template <class K,class V>
bool _rbTree<K,V>::isRightChild(_treeNode<K,V>* x) const //节点x是否是右孩子
{
    if(x->_parent==nullptr) return false;
    if(x->_parent->_rightChild==nullptr) return false;
    if(x->_parent->_rightChild->_val == x->_val) return true;
    return false;
}

template <class K,class V>
void _rbTree<K,V>::leftRotate(_treeNode<K,V>* x)//以x为支点左旋,最终x会上位
{
    if(x->_leftChild){
        x->_leftChild->_parent = x->_parent;
    }
    if(x->_parent->_parent){
        if(isLeftChild(x->_parent)){
            x->_parent->_parent->_leftChild = x;
        }else{
            x->_parent->_parent->_rightChild = x;
        }
    }
    x->_parent->_rightChild = x->_leftChild;
    x->_leftChild = x->_parent;
    x->_parent = x->_parent->_parent;
    x->_leftChild->_parent = x;
    if(x->_parent==nullptr){ //x上位之后变成了根节点
        _root = x;
    }
}

template <class K,class V>
void _rbTree<K,V>::rightRotate(_treeNode<K,V>* x)//以x为支点右旋,最终x会上位
{
    if(x->_rightChild){
        x->_rightChild->_parent = x->_parent;
    }
    if(x->_parent->_parent){
        if(isLeftChild(x->_parent)){
            x->_parent->_parent->_leftChild = x;
        }else{
            x->_parent->_parent->_rightChild = x;
        }
    }
    x->_parent->_leftChild = x->_rightChild;
    x->_rightChild = x->_parent;
    x->_parent = x->_parent->_parent;
    x->_rightChild->_parent = x;
    if(x->_parent==nullptr){ //x上位之后变成了根节点
        _root = x;
    }
}

template <class K,class V>
void _rbTree<K,V>::insert(const std::pair<K,V> &val)
{
    auto findNode = find(val.first);
    if(findNode != nullptr){ //对应键已存在,覆盖原值
        findNode->_val = val;
        return;
    }
    _size++;
    if(_root == nullptr){ //插入结点是根节点
        _root = new _treeNode<K,V>(val);
        _root->_color = BLACK;//根节点染黑
        return;
    }
    auto findUncleNode = [&](_treeNode<K,V>* x) -> _treeNode<K,V>*{ //找结点x的叔叔结点
        if(x->_parent==nullptr) return nullptr;
        if(x->_parent->_parent==nullptr) return nullptr;
        //现在祖父存在
        if(isLeftChild(x->_parent)){//x的父节点是祖父节点的左孩子
            return x->_parent->_parent->_rightChild;
        }else{//x的父节点是祖父节点的右孩子
            return x->_parent->_parent->_leftChild;
        }
    };
    auto modify = [&](_treeNode<K,V>* x){ //当前节点为红且父节点为红,需要调整
        while(x->_parent && x->_parent->_color==RED){
            auto findNode = findUncleNode(x);//找到叔节点
            if(findNode==nullptr || findNode->_color==BLACK){ //叔节点为空或者黑色
                if(isLeftChild(x) && ((findNode!=nullptr && isLeftChild(findNode)) || (findNode==nullptr && isRightChild(x->_parent)))){
                    //先右旋再左旋
                    rightRotate(x);
                    leftRotate(x);
                    x->_color = BLACK;
                    x->_leftChild->_color = RED;
                }else if(isLeftChild(x) && ((findNode!=nullptr && isRightChild(findNode)) || (findNode==nullptr && isLeftChild(x->_parent)))){
                    //一步右旋
                    rightRotate(x->_parent);
                    x->_parent->_color = BLACK;
                    x->_parent->_rightChild->_color = RED;
                }else if(isRightChild(x) && ((findNode!=nullptr && isLeftChild(findNode)) || (findNode==nullptr && isRightChild(x->_parent)))){
                    //一步左旋
                    leftRotate(x->_parent);
                    x->_parent->_color = BLACK;
                    x->_parent->_leftChild->_color = RED;
                }else if(isRightChild(x) && ((findNode!=nullptr && isRightChild(findNode)) || (findNode==nullptr && isLeftChild(x->_parent)))){
                    //先左旋再右旋
                    leftRotate(x);
                    rightRotate(x);
                    x->_color = BLACK;
                    x->_rightChild->_color = RED;
                }
                break;
            }else{ //叔节点为红色
                //将父节点与叔节点染黑
                findNode->_color = BLACK;
                x->_parent->_color = BLACK;
                //祖父节点染红
                x->_parent->_parent->_color = RED;
                //x成为祖父节点,继续调整
                x = x->_parent->_parent;
            }
        }
    };
    //找到插入位置并进行插入
    _treeNode<K,V>* cur=_root;
    while(1){
        if(val.first<cur->_val.first){
            if(cur->_leftChild){
                cur = cur->_leftChild;
            }else{
                //insert here
                cur->_leftChild = new _treeNode<K,V>(val);
                cur->_leftChild->_parent = cur;
                if(cur->_color==RED){//父节点为红,需要调整
                    modify(cur->_leftChild);
                }
                break;
            }
        }else{
            if(cur->_rightChild){
                cur = cur->_rightChild;
            }else{
                //insert here
                cur->_rightChild = new _treeNode<K,V>(val);
                cur->_rightChild->_parent = cur;
                if(cur->_color==RED){//父节点为红,需要调整
                    modify(cur->_rightChild);
                }
                break;
            }
        }
    }
    _root->_color = BLACK;//根节点的颜色维护
}

template <class K,class V>
void _rbTree<K,V>::erase(const K &key)
{
    auto findNode = find(key);
    if(findNode==nullptr) return;//对应键不存在,忽略本次删除操作
    _size--;
    _treeNode<K,V>* x = findNode;//x为待删除节点
    if(findNode->_leftChild){ //左子树存在的情况
        x = findNode->_leftChild;
        while(x->_rightChild){
            x = x->_rightChild;
        }
        findNode->_val = x->_val;
    }else if(findNode->_rightChild){//左子树不存在,但是右子树存在,那么右子树只有一个节点,且是RED
        findNode->_val = findNode->_rightChild->_val;//直接替换并删除这个RED节点
        delete findNode->_rightChild;
        findNode->_rightChild = nullptr;
        return;
    }
    //现在待删除节点为x,且x一定没有右子树
    if(x==_root){//x是根节点,这说明本来树中只有一个根节点,那么将树清空。
        delete _root;
        _root = nullptr;
        return;
    }
    //现在待删除节点x一定没有右子树,且有父节点
    if(x->_color==RED){//x是红色节点,那么x一定不可能有左子树了
        if(isLeftChild(x)){
            x->_parent->_leftChild = nullptr;
        }else{
            x->_parent->_rightChild = nullptr;
        }
        delete x;//删掉x
        return;
    }
    //现在待删除节点x是黑色节点(说明x一定有兄弟),且有父节点,可能有一个RED左儿子
    if(x->_leftChild){//x有一个RED左儿子
        x->_val = x->_leftChild->_val;
        delete x->_leftChild;
        x->_leftChild = nullptr;
        return;
    }
    auto haveRedSon = [&](_treeNode<K,V>* x){//x有两个红色儿子,返回3;x有红色左儿子,返回1;x有红色右儿子没有红色左儿子,返回2;否则返回0。
        if(x->_leftChild && x->_leftChild->_color==RED && x->_rightChild && x->_rightChild->_color==RED) return 3;
        if(x->_leftChild && x->_leftChild->_color==RED) return 1;
        if(x->_rightChild && x->_rightChild->_color==RED) return 2;
        return 0;
    };
    std::function<void (_treeNode<K,V>*)> modify = [&](_treeNode<K,V>* x){
        if(x->_parent==nullptr) return;
        //现在x有父节点,由于x是黑色,那么x一定存在兄弟子树
        if(isLeftChild(x)){
            if(x->_parent->_rightChild->_color==RED){//x的兄弟是红色
                leftRotate(x->_parent->_rightChild);
                x->_parent->_parent->_color = BLACK;
                x->_parent->_color = RED;
                modify(x);
            }else{//x的兄弟是黑色
                _treeNode<K,V>* bro = x->_parent->_rightChild;
                if(x->_parent->_color==RED){ //父节点为红色
                    int tag=haveRedSon(bro);
                    if(tag==0){ //兄弟节点没有红色儿子
                        bro->_color = RED;
                        bro->_parent->_color = BLACK; //结束啦
                    }else{
                        if(tag==1 || tag==3){ //兄弟节点有红色左儿子
                            rightRotate(bro->_leftChild);
                            leftRotate(bro->_parent);
                            bro->_parent->_leftChild->_color=BLACK;//结束啦
                        }else{
                            leftRotate(bro);//结束啦
                        }
                    }
                }else{ //父节点为黑
                    int tag=haveRedSon(bro);
                    if(tag==0){ //兄弟节点没有红色儿子
                        bro->_color = RED;
                        modify(bro->_parent);
                    }else{
                        if(tag==2){ //兄弟节点有红色右儿子没有红色左儿子
                            leftRotate(bro);
                            bro->_rightChild->_color = BLACK; //结束啦
                        }else{
                            rightRotate(bro->_leftChild);
                            leftRotate(bro->_parent);
                            bro->_parent->_color = BLACK; //结束啦
                        }
                    }
                }
            }
        }else{//对称情况,x是右孩子
            if(x->_parent->_leftChild->_color==RED){//x的兄弟是红色
                rightRotate(x->_parent->_leftChild);
                x->_parent->_parent->_color = BLACK;
                x->_parent->_color = RED;
                modify(x);
            }else{//x的兄弟是黑色
                _treeNode<K,V>* bro = x->_parent->_leftChild;
                if(x->_parent->_color==RED){ //父节点为红色
                    int tag=haveRedSon(bro);
                    if(tag==0){ //兄弟节点没有红色儿子
                        bro->_color = RED;
                        bro->_parent->_color = BLACK; //结束啦
                    }else{
                        if(tag==2 || tag==3){ //兄弟节点有红色右儿子
                            leftRotate(bro->_rightChild);
                            rightRotate(bro->_parent);
                            bro->_parent->_rightChild->_color = BLACK; //结束啦
                        }else{ //兄弟节点有红色左儿子,没有红色右儿子
                            rightRotate(bro);//结束啦
                        }
                        
                    }
                }else{ //父节点为黑
                    int tag=haveRedSon(bro);
                    if(tag==0){ //兄弟节点没有红色儿子
                        bro->_color = RED;
                        modify(bro->_parent);
                    }else{
                        if(tag==1){ //兄弟节点有红色左儿子
                            rightRotate(bro);
                            bro->_leftChild->_color = BLACK;//结束啦
                        }else{
                            leftRotate(bro->_rightChild);
                            rightRotate(bro->_parent);
                            bro->_parent->_color = BLACK; //结束啦
                        }
                    }
                }
            }
        }
    };
    //现在x是黑色叶子节点,且有兄弟节点,有父节点。
    _treeNode<K,V>* del = x;
    modify(x);//该函数要求传入的x节点为黑色,并希望兄弟子树调整为黑高-1,且父节点由R变B
    if(isLeftChild(del)) del->_parent->_leftChild = nullptr;
    if(isRightChild(del)) del->_parent->_rightChild = nullptr; 
    delete del;//把那个要删除的节点最后删掉
}

template <class K,class V>
void _rbTree<K,V>::debug() const//输出树结构到文件
{
    std::ofstream out("tree.dot", std::ios::out);
    std::string result="digraph tree{\n";
    std::queue<_treeNode<K,V>*> q;
    q.push(_root);
    while(!q.empty()){
        auto x = q.front();
        q.pop();
        if(x==nullptr) continue;
        std::string a = "<"+std::to_string((x->_val).first)+", "+((x->_val).second)+">";
        result+=a;
        result+="  [label=\""+a+"\", color=\"";
        if(x->_color==BLACK) result+="black\"];\n";
        else result+="red\"];\n";
        std::string b;
        if(x->_leftChild){
            result+=a;
            result+="->";
            b = "<"+std::to_string((x->_leftChild->_val).first)+", "+((x->_leftChild->_val).second)+">";
            result+=b;
            result+=";\n";
        }
        if(x->_rightChild){
            result+=a;
            result+="->";
            b = "<"+std::to_string((x->_rightChild->_val).first)+", "+((x->_rightChild->_val).second)+">";
            result+=b;
            result+=";\n";
        }
        q.push(x->_leftChild);
        q.push(x->_rightChild);
    }
    result+="}";
    out << result;
    out.close();
}

template <class K,class V>
void _rbTree<K,V>::delSubTree(_treeNode<K,V>* cur) //删除以cur为根的子树
{
    if(cur==nullptr) return;
    delSubTree(cur->_leftChild);
    delSubTree(cur->_rightChild);
    delete cur;
}

template <class K,class V>
_rbTree<K,V>::~_rbTree()
{
    delSubTree(_root);
}

#endif