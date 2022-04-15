#include <iostream>
#include <vector>
#include <string>
#include <queue>

template<typename T>
struct BinaryTree {
	T val;
	bool has_val = false;
	BinaryTree* l = nullptr; 
	BinaryTree* r = nullptr;

	BinaryTree() {}
	BinaryTree(T val_in) {val = val_in; has_val = true;}
	BinaryTree(T val_in, BinaryTree* l_in, BinaryTree* r_in) {val = val_in; l = l_in; r = r_in; has_val = true;}
	
	~BinaryTree() {
		if (l != nullptr) {delete l;}
		if (r != nullptr) {delete r;}
	}

	void insert(T i_val) {
		if (!has_val) {has_val = true; val = i_val;}
		else if (i_val >= val) {
			if (r == nullptr) {r = new BinaryTree<T>(i_val);}
			else {r->insert(i_val);}
		}
		else {
			if (l == nullptr) {l = new BinaryTree<T>(i_val);}
			else {l->insert(i_val);}
		}
	}
	std::vector<T> findRange(T min, T max) {
		std::vector<T> out;
		BinaryTree* node = this;
		while (node->val > max || node->val < min) {
			if (node->val > max) {
				if (node->l == nullptr) {return out;}
				node = node->l;
			}
			else if (node->val < min) {
				if (node->r == nullptr) {return out;}
				node = node->r;
			}
		}
		std::queue<BinaryTree*> nodes;
		nodes.push(node);
		while (nodes.size()) {
			node = nodes.front();
			nodes.pop();
			out.push_back(node->val);
			if (node->l != nullptr) { if (node->l->has_val && node->l->val <= max && node->l->val >= min) {nodes.push(node->l);}}
			if (node->r != nullptr) { if (node->r->has_val && node->r->val <= max && node->r->val >= min) {nodes.push(node->r);}}
		}
		return out;
	}
	BinaryTree* find(T key) {
		if (!has_val) {return nullptr;}
		BinaryTree* node = this;
		while (node->val != key) {
			if (node->val < key) {
				if (node->r != nullptr) {
				if (node->r->has_val) {node = node->r;}
				else {return nullptr;}
			} else {return nullptr;}}
			else if (node->val > key) {
				if (node->l != nullptr) {
				if (node->l->has_val) {node = node->l;}
				else {return nullptr;}
			} else {return nullptr;}}
		}
		return node;
	}
};

template<typename T>
void printTree(BinaryTree<T>* tree) {
	std::vector<BinaryTree<T>*>* next_layer = new std::vector<BinaryTree<T>*>;
	std::vector<BinaryTree<T>*>* this_layer = new std::vector<BinaryTree<T>*>;
	this_layer->push_back(tree);
	bool running = true;
	while (running) {
		running = false;
		for (BinaryTree<T>* node : *this_layer) {
			if (node == nullptr) {
				std::cout<<"MT ";
				next_layer->push_back(nullptr);
				next_layer->push_back(nullptr);
				continue;
			}
			if (!(node->has_val)) {std::cout<<"MT ";}
			else {std::cout<< node->val << ' ';}
			if (node->l != nullptr || node->r != nullptr) {running = true;}
			next_layer->push_back(node->l);
			next_layer->push_back(node->r);
		}
		std::cout<<std::endl;
		this_layer = next_layer;
		next_layer = new std::vector<BinaryTree<T>*>;
	}
}
