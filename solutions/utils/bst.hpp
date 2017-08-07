#include <stdlib.h>
#pragma once

template <class T> class Node{
private:
    Node<T>* _left_child;
    Node<T>* _right_child;
    T& _elem;
public:
    Node<T>(T& elem);
    ~Node<T>();
    Node<T>* getLeftChild();
    Node<T>* getRightChild();
    T& getElem();
    bool insert(T& elem);
};

template <class T> class BST{
private:
    Node<T>* _head_node;
    unsigned long _size;
public:
    BST<T>();
    ~BST<T>();
    Node<T>* getHead();
    bool insert(T& elem);
    unsigned long size();
};

template <class T>
Node<T>::Node(T& elem) : _left_child(NULL), _right_child(NULL), _elem(elem) {}

template <class T>
Node<T>::~Node<T>(){
    if(_left_child) delete _left_child;
    if(_right_child) delete _right_child;
}

template <class T>
Node<T>* Node<T>::getLeftChild(){
    return _left_child;
}

template <class T>
Node<T>* Node<T>::getRightChild(){
    return _right_child;
}

template <class T>
T& Node<T>::getElem(){
    return _elem;
}

template <class T>
bool Node<T>::insert(T &elem){
    if(elem < _elem){
        if(_left_child == NULL){
            _left_child = new Node<T>(elem);
            return true;
        }else{
            return _left_child->insert(elem);
        }
    }else if(_elem < elem){
        if(_right_child == NULL){
            _right_child = new Node<T>(elem);
            return true;
        }else{
            return _right_child->insert(elem);
        }
    }else{
        return false;
    }
}

template <class T>
BST<T>::BST(): _head_node(NULL), _size(0){}

template <class T>
BST<T>::~BST<T>(){
    if(_head_node) delete _head_node;
}

template <class T>
Node<T>* BST<T>::getHead(){
    return _head_node;
}

template <class T>
bool BST<T>::insert(T &elem){
    if(_head_node == NULL){
        _head_node = new Node<T>(elem);
        _size++;
        return true;
    }else{
        if(_head_node->insert(elem)){
            _size++;
            return true;
        }else{
            return false;
        }
    }
}

template <class T>
unsigned long BST<T>::size(){
    return _size;
}
