// C++ program for implementing B+ Tree
#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;
// int MAX = 3;
int dn = 0;
int ln = 0;
int d,t;

// BP node
class Node {
    public:
	bool IS_LEAF;
	int *key, size;
    int max_size;
	Node** ptr;
	friend class BPTree;


	Node(bool ,int);
};

// BP tree
class BPTree {
    public:
	Node* root;
	void insertInternal(int,
						Node*,
						Node*);
	Node* findParent(Node*, Node*);


	BPTree();
	void search(int);
	void insert(int);
	void display(Node*);
	Node* getRoot();
    void display();
};

// Constructor of Node
Node::Node(bool islf , int sz)
{
    IS_LEAF = islf;
    max_size = sz;
	key = new int[sz];
	ptr = new Node*[sz];
}

// Initialise the BPTree Node
BPTree::BPTree()
{
	root = NULL;
}

// Function to find any element
// in B+ Tree
void BPTree::search(int x)
{

	// If tree is empty
	if (root == NULL) {
		cout << "Tree is empty\n";
	}

	// Traverse to find the value
	else {

		Node* cursor = root;

		// Till we reach leaf node
		while (cursor->IS_LEAF == false) {

			for (int i = 0;
				i < cursor->size; i++) {

				// If the element to be
				// found is not present
				if (x < cursor->key[i]) {
					cursor = cursor->ptr[i];
					break;
				}

				// If reaches end of the
				// cursor node
				if (i == cursor->size - 1) {
					cursor = cursor->ptr[i + 1];
					break;
				}
			}
		}

		// Traverse the cursor and find
		// the node with value x
		for (int i = 0;
			i < cursor->size; i++) {

			// If found then return
			if (cursor->key[i] == x) {
				cout << "Found\n";
				return;
			}
		}

		// Else element is not present
		cout << "Not found\n";
	}
}

void BPTree::display(){
    cout << dn << " " << ln << " ";
    for(int i = 0 ; i < root->size ; i++){
        cout << root->key[i] << " " ;
    }
    cout << endl;
}

// Function to implement the Insert
// Operation in B+ Tree
void BPTree::insert(int x)
{

	// If root is null then return
	// newly created node
	if (root == NULL) {
		root = new Node(true,2*d);
        ln++;
		root->key[0] = x;
		root->IS_LEAF = true;
		root->size = 1;
	}

	// Traverse the B+ Tree
	else {
		Node* cursor = root;
		Node* parent;

		// Till cursor reaches the
		// leaf node
		while (cursor->IS_LEAF
			== false) {

			parent = cursor;

			for (int i = 0;
				i < cursor->size;
				i++) {

				// If found the position
				// where we have to insert
				// node
				if (x < cursor->key[i]) {
					cursor
						= cursor->ptr[i];
					break;
				}

				// If reaches the end
				if (i == cursor->size - 1) {
					cursor
						= cursor->ptr[i + 1];
					break;
				}
			}
		}
// MAX
		if (cursor->size < (2*d)) {
			int i = 0;
			while (x > cursor->key[i]
				&& i < cursor->size) {
				i++;
			}

			for (int j = cursor->size;
				j > i; j--) {
				cursor->key[j]
					= cursor->key[j - 1];
			}

			cursor->key[i] = x;
			cursor->size++;

			cursor->ptr[cursor->size]
				= cursor->ptr[cursor->size - 1];
			cursor->ptr[cursor->size - 1] = NULL;
		}

		else {

			// Create a newLeaf node
			Node* newLeaf = new Node(true,2*d);
    ln++;
			int virtualNode[2*d + 1];
            //MAX

			// Update cursor to virtual
			// node created
			for (int i = 0; i < 2*d; i++) {
				virtualNode[i]
					= cursor->key[i];
			}
			int i = 0, j;

			// Traverse to find where the new
			// node is to be inserted
			while (x > virtualNode[i]
				&& i < 2*d) {
				i++;
			}

			// Update the current virtual
			// Node to its previous
			for (int j = 2*d + 1;
				j > i; j--) {
				virtualNode[j]
					= virtualNode[j - 1];
			}

			virtualNode[i] = x;
			newLeaf->IS_LEAF = true;
	cursor->size = (2*d + 1) / 2;
			newLeaf->size
				= 2*d + 1 - (2*d + 1) / 2;

			cursor->ptr[cursor->size]
				= newLeaf;

			newLeaf->ptr[newLeaf->size]
				= cursor->ptr[2*d];

			cursor->ptr[2*d] = NULL;
            // MAX

			// Update the current virtual
			// Node's key to its previous
			for (i = 0;
				i < cursor->size; i++) {
				cursor->key[i]
					= virtualNode[i];
			}

			// Update the newLeaf key to
			// virtual Node
			for (i = 0, j = cursor->size;
				i < newLeaf->size;
				i++, j++) {
				newLeaf->key[i]
					= virtualNode[j];
			}

			// If cursor is the root node
			if (cursor == root) {

				// Create a new Node
				Node* newRoot = new Node(false,(2*t + 1));
                dn++;
				// Update rest field of
				// B+ Tree Node
				newRoot->key[0] = newLeaf->key[0];
				newRoot->ptr[0] = cursor;
				newRoot->ptr[1] = newLeaf;
				newRoot->IS_LEAF = false;
				newRoot->size = 1;
				root = newRoot;
			}
			else {

				// Recursive Call for
				// insert in internal
				insertInternal(newLeaf->key[0],
							parent,
							newLeaf);
			}
		}
	}
}

// Function to implement the Insert
// Internal Operation in B+ Tree
void BPTree::insertInternal(int x,
							Node* cursor,
							Node* child)
{

	// If we doesn't have overflow
	if (cursor->size < (2*t +1)) {
        // MAX
		int i = 0;

		// Traverse the child node
		// for current cursor node
		while (x > cursor->key[i]
			&& i < cursor->size) {
			i++;
		}

		// Traverse the cursor node
		// and update the current key
		// to its previous node key
		for (int j = cursor->size;
			j > i; j--) {

			cursor->key[j]
				= cursor->key[j - 1];
		}

		// Traverse the cursor node
		// and update the current ptr
		// to its previous node ptr
		for (int j = cursor->size + 1;
			j > i + 1; j--) {
			cursor->ptr[j]
				= cursor->ptr[j - 1];
		}

		cursor->key[i] = x;
		cursor->size++;
		cursor->ptr[i + 1] = child;
	}

	// For overflow, break the node
	else {

		// For new Interval
		Node* newInternal = new Node(false,(2*t + 1));
        dn++;
		int virtualKey[(2*t + 1) + 1];
		Node* virtualPtr[(2*t + 1) + 2];

		// Insert the current list key
		// of cursor node to virtualKey
		for (int i = 0; i < (2*t + 1); i++) {
			virtualKey[i] = cursor->key[i];
		}

		// Insert the current list ptr
		// of cursor node to virtualPtr
		for (int i = 0; i < (2*t + 1) + 1; i++) {
			virtualPtr[i] = cursor->ptr[i];
		}

		int i = 0, j;
        // MAX

		// Traverse to find where the new
		// node is to be inserted
		while (x > virtualKey[i]
			&& i < (2*t + 1)) {
			i++;
		}

		// Traverse the virtualKey node
		// and update the current key
		// to its previous node key
		for (int j = (2*t + 1) + 1;
			j > i; j--) {

			virtualKey[j]
				= virtualKey[j - 1];
		}

		virtualKey[i] = x;

		// Traverse the virtualKey node
		// and update the current ptr
		// to its previous node ptr
		for (int j = (2*t +1 ) + 2;
			j > i + 1; j--) {
			virtualPtr[j]
				= virtualPtr[j - 1];
		}

		virtualPtr[i + 1] = child;
		newInternal->IS_LEAF = false;

		cursor->size = t;
			// = ((2*t +1 ) + 1) / 2;

		newInternal->size = t+1;
			// = (2*t +1 ) - ((2*t +1 ) + 1) / 2;

		// Insert new node as an
		// internal node MAX

		for(int k=0;k<t;k++){
			cursor->key[i] = virtualKey[i];
		}

		for(int k=0;k<t+1;k++){
			cursor->ptr[i] = virtualPtr[i];
		}

		for (i = 0, j = cursor->size + 1;
			i < newInternal->size;
			i++, j++) {

			newInternal->key[i]
				= virtualKey[j];
		}

		for (i = 0, j = cursor->size + 1 + 1;
			i < newInternal->size + 1;
			i++, j++) {

			newInternal->ptr[i]
				= virtualPtr[j];
		}

		// If cursor is the root node
		if (cursor == root) {

			// Create a new root node
			Node* newRoot = new Node(false , 2*t + 1);
            dn++;
			// Update key value
			newRoot->key[0] = virtualKey[cursor->size];
				// = cursor->key[cursor->size];

			// Update rest field of
			// B+ Tree Node
			newRoot->ptr[0] = cursor;
			newRoot->ptr[1] = newInternal;
			newRoot->IS_LEAF = false;
			newRoot->size = 1;
			root = newRoot;
		}

		else {

			// Recursive Call to insert
			// the data
			insertInternal(virtualKey[cursor->size],
						findParent(root,
									cursor),
						newInternal);
		}
	}
}

// Function to find the parent node
Node* BPTree::findParent(Node* cursor,
						Node* child)
{
	Node* parent;

	// If cursor reaches the end of Tree
	if (cursor->IS_LEAF
		|| (cursor->ptr[0])->IS_LEAF) {
		return NULL;
	}

	// Traverse the current node with
	// all its child
	for (int i = 0;
		i < cursor->size + 1; i++) {

		// Update the parent for the
		// child Node
		if (cursor->ptr[i] == child) {
			parent = cursor;
			return parent;
		}

		// Else recursively traverse to
		// find child node
		else {
			parent
				= findParent(cursor->ptr[i],
							child);

			// If parent is found, then
			// return that parent node
			if (parent != NULL)
				return parent;
		}
	}

	// Return parent node
	return parent;
}

// Function to get the root Node
Node* BPTree::getRoot()
{
	return root;
}

// Driver Code
int main()
{
	BPTree node;

    
    cin >> d >> t;

    while(true){
        int opt;
        cin >> opt;
        if(opt == 1){
            int temp;
            cin >> temp;
            node.insert(temp);
        }
        else if (opt == 2)
        {
            node.display();
        }
        else
        {
            break;
        }
        
        
    }

	return 0;
}
