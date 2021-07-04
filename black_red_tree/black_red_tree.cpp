#include "black_red_tree.h"

template <class K, class V>
Node<K, V>* rotate_left(Node<K, V>* parent){
    Node<K, V>* temp = parent->right;
    parent -> right = temp -> left;
    temp-> left = parent; 
    return temp;
}

template <class K, class V>
Node<K, V>* rotate_right(Node<K, V>* node){
    Node<K, V>* temp = parent->left;
    parent -> left = temp -> right;
    temp-> right = parent; 
    return temp;
}