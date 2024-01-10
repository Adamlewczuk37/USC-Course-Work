#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item);
    virtual void remove(const Key& key);
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    void treeFix(AVLNode<Key,Value>* n);
    void treeHelper(AVLNode<Key,Value>* n);
		void insertHelper(AVLNode<Key,Value>* n);
		void removeHelper(AVLNode<Key,Value>* n, int diff);
    void rotateLeft(AVLNode<Key,Value>* n);
    void rotateRight(AVLNode<Key,Value>* n);
};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    Node<Key, Value>* temp = BinarySearchTree<Key, Value>::internalFind(new_item.first);
    AVLNode<Key, Value>* equ = static_cast<AVLNode<Key, Value>*>(temp);
    AVLNode<Key,Value>* newNode = NULL;
    AVLNode<Key,Value>* parent = NULL;

    if ((reinterpret_cast<AVLNode<Key,Value>*&>(this->root_)) == NULL){
				this->root_ = new AVLNode<Key,Value>(new_item.first, new_item.second, NULL);
    }
    else if (equ == NULL){
        parent = reinterpret_cast<AVLNode<Key,Value>*&>(this->root_);
        while ((parent->getKey() != new_item.first) && (parent != NULL)){
            if (parent->getKey() < new_item.first){
                if (parent->getRight() == NULL){
                    break;
                }
                parent = parent->getRight();
            } else {
                if (parent->getLeft() == NULL){
                    break;
                }
                parent = parent->getLeft();
            }
        }
        newNode = new AVLNode<Key,Value>(new_item.first, new_item.second, parent);
        newNode->setBalance(0);
        if (new_item.first < parent->getKey()){
            parent->setLeft(newNode);
        } else {
            parent->setRight(newNode);
        }

				if (parent != NULL){
						if (parent->getBalance() == 0){
							if (newNode == parent->getLeft()){
								parent->updateBalance(-1);
							}	else {
								parent->updateBalance(1);
							}
							insertHelper(newNode);
						}
						else {
							parent->setBalance(0);
						}
					}
    } else {
        equ->setValue(new_item.second);
    }
}


template<class Key, class Value>
void AVLTree<Key, Value>::insertHelper(AVLNode<Key,Value>* n){
	AVLNode<Key,Value>* parent = n->getParent();
	AVLNode<Key,Value>* grand = parent->getParent();
	int bal = 0;
	if (grand != NULL){
		if (parent == grand->getLeft()){
			grand->updateBalance(-1);
		}	else {
			grand->updateBalance(1);
		}
		bal = grand->getBalance();
	}
	int parBal = parent->getBalance();
	if (bal > 1){
			parBal = parent->getBalance();
			if (parBal > 0){
					rotateLeft(grand);
					grand->setBalance(0);
					parent->setBalance(0);
			} else {
					rotateRight(parent);
					rotateLeft(grand);
					if (n->getBalance() == -1){
							n->setBalance(0);
							grand->setBalance(0);
							parent->setBalance(1);
					} else if (n->getBalance() == 0){
							n->setBalance(0);
							grand->setBalance(0);
							parent->setBalance(0);
					} else {
							n->setBalance(0);
							grand->setBalance(-1);
							parent->setBalance(0);
					}
			}
	} else if (bal < -1){
			if (parBal < 0){
					rotateRight(grand);
					grand->setBalance(0);
					parent->setBalance(0);
			} else {
					rotateLeft(parent);
					rotateRight(grand);
					if (n->getBalance() == -1){
							n->setBalance(0);
							grand->setBalance(1);
							parent->setBalance(0);
					} else if (n->getBalance() == 0){
							n->setBalance(0);
							grand->setBalance(0);
							parent->setBalance(0);
					} else {
							n->setBalance(0);
							grand->setBalance(0);
							parent->setBalance(-1);
					}
			}
	} else if (bal == 0){
		return;
	} else if ((bal == 1) || (bal == -1)){
		insertHelper(parent);
	}
}


/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
		AVLNode<Key, Value>* AVLRoot = dynamic_cast<AVLNode<Key, Value>*>(this->root_);
    
    if (AVLRoot == NULL){
			return;
		}
    Node<Key, Value>* temp = BinarySearchTree<Key, Value>::internalFind(key);
    AVLNode<Key, Value>* equ = dynamic_cast<AVLNode<Key, Value>*>(temp);

    if (equ == NULL){
        return;
    }

    AVLNode<Key, Value>* parent = equ->getParent();
    temp = BinarySearchTree<Key, Value>::predecessor(equ);
    AVLNode<Key, Value>* pred = dynamic_cast<AVLNode<Key, Value>*>(temp);
    AVLNode<Key, Value>* lef = equ->getLeft();
    AVLNode<Key, Value>* rig = equ->getRight();
    AVLNode<Key, Value>* tempi = NULL;
		if (pred != NULL){
			tempi = pred->getLeft();
		}
		bool cond = false;

    if (pred != NULL){
        temp = pred->getLeft();
    }

		if ((equ->getLeft() != NULL) && (equ->getRight() != NULL)){
			if (parent == NULL){
				AVLRoot = pred;
			}
			nodeSwap(pred, equ);
			if (parent == NULL){
				this->root_ = AVLRoot;
			}
			cond = true;
			parent = equ->getParent();
		}

		int diff = 0;
		if (parent != NULL){
			if (equ == parent->getLeft()){
				diff = 1;
			} else {
				diff = -1;
			}
			removeHelper(parent, diff);
		}

    if ((equ->getLeft() == NULL) && (equ->getRight() == NULL) && (!cond)){
				if (parent != NULL){
            if (equ == parent->getLeft()){
                parent->setLeft(NULL);
            } else {
                parent->setRight(NULL);
            }
        } else {
            AVLRoot = NULL;
        }
    }  else if (cond){
				if (pred->getParent() == NULL){
					AVLRoot = pred;
				}
				if (equ == parent->getLeft()){
						if (tempi != NULL){
								pred->setLeft(tempi);
								tempi->setParent(pred);
						} else {
								parent->setLeft(NULL);
						}
				} else {
						if (tempi != NULL){
								parent->setRight(tempi);
								tempi->setParent(parent);
						} else {
								parent->setRight(NULL);
						}
				}
    } else {
        if (equ->getLeft() != NULL){
            lef->setParent(parent);
            if (parent != NULL){
                if (equ == parent->getLeft()){
                    parent->setLeft(lef);
                } else {
                    parent->setRight(lef);
                }
            } else {
                AVLRoot = lef;
            }
        } else {
            rig->setParent(parent);
            if (parent != NULL){
                if (equ == parent->getLeft()){
                    parent->setLeft(rig);
                } else {
                    parent->setRight(rig);
                }
            } else {
                AVLRoot = rig;
            }
        }
    }
		delete equ;

		if (AVLRoot != NULL){
				while (AVLRoot->getParent() != NULL){
					AVLRoot = AVLRoot->getParent();
				}
				this->root_ = AVLRoot;
		} else {
				this->root_ = NULL;
		}
}


template<class Key, class Value>
void AVLTree<Key, Value>::removeHelper(AVLNode<Key,Value>* n, int diff){
	if (n == NULL){
		return;
	}
	AVLNode<Key,Value>* parent = n->getParent();
	AVLNode<Key,Value>* child = NULL;
	AVLNode<Key,Value>* grand = NULL;
	int nxdf = 0;
	int bal = n->getBalance();
	int chiBal = 0;
	int graBal = 0;
	if (parent != NULL){
		if (n == parent->getLeft()){
			nxdf = 1;
		}	else {
			nxdf = -1;
		}
	}
	
	if (bal + diff == -2){
			child = n->getLeft();
			chiBal = child->getBalance();
			if (chiBal < 0){
					rotateRight(n);
					n->setBalance(0);
					child->setBalance(0);
					removeHelper(parent, nxdf);
			} else if (chiBal == 0){
					rotateRight(n);
					n->setBalance(-1);
					child->setBalance(1);
				return;
			} else {
					grand = child->getRight();
					graBal = grand->getBalance();
					rotateLeft(child);
					rotateRight(n);
					if (graBal == 1){
							n->setBalance(0);
							grand->setBalance(0);
							child->setBalance(-1);
					} else if (graBal == 0){
							n->setBalance(0);
							grand->setBalance(0);
							child->setBalance(0);
					} else {
							n->setBalance(1);
							grand->setBalance(0);
							child->setBalance(0);
					}
					removeHelper(parent, nxdf);
			}
	} else if (bal + diff == 2){
			child = n->getRight();
			chiBal = child->getBalance();

			if (chiBal > 0){
					rotateLeft(n);
					n->setBalance(0);
					child->setBalance(0);
					removeHelper(parent, nxdf);
			} else if (chiBal == 0){
					rotateLeft(n);
					n->setBalance(1);
					child->setBalance(-1);
				return;
			} else {
					grand = child->getLeft();
					graBal = grand->getBalance();
					rotateRight(child);
					rotateLeft(n);
					if (graBal == -1){
							n->setBalance(0);
							grand->setBalance(0);
							child->setBalance(1);
					} else if (graBal == 0){
							n->setBalance(0);
							grand->setBalance(0);
							child->setBalance(0);
					} else {
							n->setBalance(-1);
							grand->setBalance(0);
							child->setBalance(0);
					}
					removeHelper(parent, nxdf);
			}
	} else if ((bal + diff == -1) || (bal + diff == 1)){
			bal += diff;
			n->setBalance(bal);
	} else if (bal + diff == 0){
			n->setBalance(0);
			removeHelper(parent, nxdf);
	}
}


template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key,Value>* n){
    AVLNode<Key,Value>* parent = n->getParent();
    AVLNode<Key,Value>* child = n->getRight();
    AVLNode<Key,Value>* s2 = NULL;
    if (child != NULL){
        s2 = child->getLeft();
    }

    if (parent == NULL){
        child->setParent(NULL);
        child->setLeft(n);
        n->setParent(child);
        n->setRight(s2);
        if (s2 != NULL){
            s2->setParent(n);
        }
        this->root_ = child;
        return;
    } else if (n == parent->getRight()){
        parent->setRight(child);
    } else {
        parent->setLeft(child);
    }
    child->setParent(parent);
    child->setLeft(n);
    n->setParent(child);
    n->setRight(s2);
    if (s2 != NULL){
        s2->setParent(n);
    }
    return;
}


template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key,Value>* n){
		AVLNode<Key,Value>* parent = n->getParent();
    AVLNode<Key,Value>* child = n->getLeft();
    AVLNode<Key,Value>* s3 = NULL;
		if (child != NULL){
			s3 = child->getRight();
		}
    if (parent == NULL){
        child->setParent(NULL);
        child->setRight(n);
        n->setParent(child);
        n->setLeft(s3);
        if (s3 != NULL){
            s3->setParent(n);
        }
        this->root_ = child;
        return;
    } else if (n == parent->getRight()){
        parent->setRight(child);
    } else {
        parent->setLeft(child);
    }
    child->setParent(parent);
    child->setRight(n);
    n->setParent(child);
    n->setLeft(s3);
    if (s3 != NULL){
        s3->setParent(n);
    }
    return;
}


template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif