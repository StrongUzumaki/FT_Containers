#pragma once
#include <memory>

template<class Value>
struct Node{
	typedef Node*			pointer;

	explicit Node(Value *srcval = 0) :	value(srcval),
										parent(0),
										left(0),
										right(0),
										is_black(false),
										is_nil(0){}
	
	Value	*value;
	Node*	parent;
	Node*	left;
	Node*	right;	
	bool	is_black;
	bool	is_nil;
	
	Node(pointer value, Node* node = NULL, Node* parent = NULL) :
	   value(value), left(node), right(node), parent(parent), is_black(false) {}	
};

template<class Value, class Compare = std::less<Value>, class Alloc = std::allocator<Value> >
class RBTree{
	private:
template<typename T>
	class TreeIter {
	public:
		typedef ptrdiff_t difference_type;
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef T								value_type;
		typedef T&								reference;
		typedef T*								pointer;

		template <class _Cont, class _Comp, class _Alloc> friend class  RBTree;

		typedef Node<T>* node_pointer;

	private:
		node_pointer _node;

		TreeIter(void *node): _node(static_cast<node_pointer>(node)) {}

		node_pointer tree_min(node_pointer n) {
			while (n->left != NULL && !n->left->is_nil)
				n = n->left;
			return n;
		}

		node_pointer tree_max(node_pointer n) {
			while (!n->right->is_nil)
				n = n->right;
			return n;
		}

		node_pointer node() {
			return _node;
		}

	public:
		TreeIter() {}

		TreeIter(const TreeIter<value_type> & other) {
			this->_node = other._node;
		}

		TreeIter& operator=(const TreeIter<value_type>& other) {
			this->_node = other._node;
			return *this;
		}

		reference operator*() const {
			return *(_node->content);
		}

		pointer operator->() const {
			return _node->content;
		}

		TreeIter& operator++() {
			if (!_node->right->is_nil) {
				_node = tree_min(_node->right);
			}
			else {
				node_pointer y = _node->father;
				while (y != NULL && _node == y->right) {
					_node = y;
					y = y->father;
				}
				_node = y;
			}
			return *this;
		}

		TreeIter operator++(int) {
			TreeIter<value_type> temp = *this;
			if (!_node->right->is_nil) {
				_node = tree_min(_node->right);
			}
			else {
				node_pointer y = _node->father;
				while (y != NULL && _node == y->right) {
					_node = y;
					y = y->father;
				}
				_node = y;
			}
			return temp;
		}

		TreeIter& operator--() {
			if (!_node->left->is_nil) {
				_node = tree_max(_node->left);
			}
			else {
				node_pointer y = _node->father;
				while (y != NULL && _node == y->left) {
					_node = y;
					y = y->father;
				}
				_node = y;
			}
			return *this;
		}

		TreeIter operator--(int) {
			TreeIter<value_type> temp = *this;
			if (!_node->left->is_nil) {
				_node = tree_max(_node->left);
			}
			else {
				node_pointer y = _node->father;
				while (y != NULL && _node == y->left) {
					_node = y;
					y = y->father;
				}
				_node = y;
			}
			return temp;
		}

		bool operator==(const TreeIter<value_type> &other) const {
			return this->_node == other._node;
		}

		bool operator!=(const TreeIter<value_type> &other) const {
			return this->_node != other._node;
		}
	};


	public:
		typedef Value value_type;
		typedef Compare key_compare;
		typedef Alloc	allocator_type;
		typedef typename Alloc::template
			                rebind<Node<Value> >::other            node_allocator;
		//typedef Node_Alloc node_allocator_type;
		typedef	typename node_allocator::pointer node_pointer;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef std::ptrdiff_t	difference_type;
		typedef std::size_t	size_type;
		//typedef iterator;
		//typedef const_iterator;
		//typedef	reverse_iterator;
	   	//typedef const_reverse_iterator;
		//typedef difference_type;	
	private:
		allocator_type				_val_alloc;
		node_allocator				_node_alloc;
		key_compare 				_compare;
		node_pointer				_nil;
		node_pointer				_header;
		node_pointer				_root;
		size_type					_size;
		
		//HELPER FUNCTIONS
		node_pointer	tree_min(node_pointer n){
			while (n->left != _nil)
				n = n->left;
			return n;
		}
		
		node_pointer	tree_max(node_pointer n){
			while (n->right != _nil)
				n = n->right;
			return n;
		}
		
		void 	_rotate_right(node_pointer	node){
			node_pointer y;

			y = node->left;
			if (y->right != _nil)
				y->right->parent = node;
			if (node == _root)
				_root = y;
			else if (node == node->parent->right)
				node->parent->right = y;
			else
				node->parent->left = y;
		}
		void 	_rotate_left(node_pointer	node){
			node_pointer y;

			y = node->right;
			if (y->left != _nil)
				y->left->parent = node;
			if (node == _root)
				_root = y;
			else if (node == node->parent->left)
				node->parent->left = y;
			else
				node->parent->right = y;
		}
		node_pointer	_insert(node_pointer new_node){
			if (_root == _header)
				_root = new_node;
			else
				_insert_to_node(_root, new_node);
		   return new_node;	
		}

		node_pointer	_insert_to_node(node_pointer root, node_pointer new_node){
			if (_compare(*new_node->value, *root->value)){
				if (!is_nil(root->left))
					return (_insert_to_node(root->left, new_node));
				root->left = new_node;
			}
			else{
				if (!is_nil(root->right))
					return (_insert_to_node(root->right, new_node));
				_root->right = new_node;
			}
			new_node->parent = root;
			return (new_node);
		}

		void _insert_fixup(node_pointer node){
			if (node != _root && node->parent != _root){
				while (node != _root && !node->parent->is_black){
					if (node->parent == node->parent->parent->left){
						node_pointer uncle = node->parent->parent->right;
						if (!uncle->is_black){
							node->parent->is_black = true;
							uncle->is_black = true;
							node->parent->parent->is_black = false;
							node = node->parent->parent;
						}
						else {
							if (node == node->parent->right){
								node = node->parent;
								_rotate_left(node);
							}
							node->parent->is_black = true;
							node->parent->parent->is_black = false;
							_rotate_right(node->parent->parent);
						}
					}
					else{
						node_pointer uncle = node->parent->parent->left;
						if (!uncle->is_black){
							node->parent->is_black = true;
							uncle->is_black = true;
							node->parent->parent->is_black = false;
							node = node->parent->parent;
						}
						else{
							if (node == node->parent->left){
								node = node->parent;
								_rotate_right(node);
							}
							node->parent->is_black = true;
							node->parent->parent->is_black = false;
							_rotate_left(node->parent->parent);
						}
					}
				}
			}
			_root->is_black = true;
		}

		bool is_nil(node_pointer node) const {
			return node == _nil || node == _header;
		}

		void clear_node(node_pointer node){
			if (node && !is_nil(node)) {
				clear_node(node->right);
				clear_node(node->left);
			}
				_val_alloc.destroy(node->value);
				_val_alloc.deallocate(node->value, 1);
				_node_alloc.deallocate(node, 1);
		}
	
		void	init_nil_head(){
			_nil = _node_alloc.allocate(1);
			_node_alloc.construct(_nil, Node<Value>());
			_nil->is_black = true;
			_nil->is_nil = true;
			_header = _node_alloc.allocate(1);
			_node_alloc.construct(_header, Node<Value>());
			_header->value = _val_alloc.allocate(1);
			_val_alloc.construct(_header->value, Value());
			_header->is_black = true;
		}
		void transplant(node_pointer where, node_pointer what) {
			if (where == _root)
				_root = what;
			else if (where == where->parent->left)
				where->parent->left = what;
			else
				where->parent->right = what;
			what->parent = where->parent;
		}
		
		void 	free_node(node_pointer node){
			_val_alloc.destroy(node->value);
			_val_alloc.deallocate(node->value, 1);
			_node_alloc.deallocate(node, 1);
		}

		//void _visualize(int tabs , node_pointer root, bool new_str){
		//	if (root == _nil)
		//		return;
		//	std::string color = root->is_black == true ? "\x1b[m" : "\x1b[31;1m" ;
		//	for(int i = 0; i < tabs; i++)
		//		std::cout << '\t';
		//	std::cout << color << *root->value << "\x1b[31;1m" << std::endl;
		//	_visualize(tabs-1, root->left, false);
		//	_visualize(2, root->right, true);
		//	
		//
		//}	

		//PUBLIC FUNCTIONS
	public:
		node_pointer	search(const value_type &value, node_pointer node) const
		{
			if(!node || is_nil(node))
				return NULL;
			if (_compare(value, *node->value))
				return search(value, node->left);
			if (_compare(*node->value, value))
				return search(value, node->right);
			return node;
		}
		
		void /*pohui*/ insert(value_type *value){
			node_pointer find_val = search(*value, _root);
			if (find_val)
				return;
			node_pointer new_node = _node_alloc.allocate(1);
			_node_alloc.construct(new_node, Node<value_type>(value));
			_val_alloc.construct(new_node->value, *value);
			new_node->left = _nil;
			new_node->right = _nil;
			_insert(new_node);
			//ft::pair<iterator, bool> res(iterator(new_node), true);
			_insert_fixup(new_node);
			_size++;
			new_node = tree_max(_root);
			new_node->right = _header;
			_header->parent = new_node;
			//return res;
		} 

		void erase(value_type *pos){
			node_pointer y = Node(pos), x, for_free = y;
			bool y_original_is_black = y->is_black;
			if (is_nil(y->left)){
				x = y->right;
				transplant(y, y->right);
			}
			else if (is_nil(y->right)){
				x = y->left;
				transplant(y, y->left);
			}
			else {
				node_pointer z = y;
				y = tree_min(z->right);
				y_original_is_black = y->is_black;
				x = y->right;
				if (y->parent != z){
					transplant(y, y->right);
					y->right = z->right;
					z->right->parent = y;
				}
				transplant(z, y);
				y->left = z->left;
				y->left->parent = y;
				y->is_black = z->is_black;
			}
			free_node(for_free);
			if (y_original_is_black)
				erase_fixup(x);
			_size--;
			_nil->parent = NULL;
			if (_size == 0)
				_root = _header;
			else{
				if (_size != 1)
					x = tree_max(_root);
				else
					x = _root;
				x->right = _header;
				_header->parent = x;
			}
		}

		void erase_fixup(node_pointer x){
			node_pointer brother;
			while (x != _root && x->is_black){
				if (x == x->parent->left){
					brother = x->parent->right;
					//case 1
					if (!brother->is_black){
						brother->is_black = true;
						x->parent->is_black = false;
						_rotate_left(x->parent);
						brother = x->parent->right;
					}
					//case 2
					if (brother->left->is_black && brother->right->is_black){
						brother->is_black = false;
						x = x->parent;
					}
					else{
					//case 3
						if (brother->right->is_black){
							brother->left->is_black = true;
							brother->is_black = false;
							_rotate_right(brother);
							brother = x->parent->right;
						}
					//case 4
						brother->is_black = x->parent->is_black;
						x->parent->is_black = true;
						brother->right->is_black = true;
						_rotate_left(x->parent);
						x = _root;
					}
				}
				else{
					brother = x->parent->left;
					//case 1
					if (!brother->is_black){
						brother->is_black = true;
						x->parent->is_black = false;
						_rotate_right(x->parent);
						brother = x->parent->left;
					}
					//case 2
					if (brother->right->is_black && brother->left->is_black){
						brother->is_black = false;
						x = x->parent;
					}
					else{
					//case 3
						if (brother->left->is_black){
							brother->right->is_black = true;
							brother->is_black = false;
							_rotate_left(brother);
							brother = x->parent->left;
						}
					//case 4
						brother->is_black = x->parent->is_black;
						x->parent->is_black = true;
						brother->left->is_black = true;
						_rotate_right(x->parent);
						x = _root;
					}
				}
			}
		}
		//CONSTRUCTORS
		RBTree(const Compare &comp, const allocator_type& a = allocator_type()):
				_root(0), _val_alloc(a), _node_alloc(node_allocator()), _compare(comp), _size(0){
			init_nil_head();
			_root = _header;
		}

		RBTree() : _root(0), _val_alloc(allocator_type()), _node_alloc(node_allocator()), _compare(key_compare()), _size(0){
			init_nil_head();
			_root = _header;
		}

		RBTree(const RBTree& src){
			*this = src;
		}
	
		RBTree& operator=(const RBTree & src){
			this->_node_alloc = src._node_alloc;
			this->_val_alloc = src._val_alloc;
			this->_cmp = src._cmp;
			clear_node(_root);
			if (this->_nil == NULL)
			init_nil_head();
			if (src._size == 0)
			this->_root = this->_header;
			else {
				this->_root = copy_node(src._root);
				copy_child(this->_root, src._root);
			}
			this->_size = src._size;
			return *this;
		}

		~RBTree(){
			//clear_node(_root);
			_val_alloc.destroy(_header->value);
			_val_alloc.deallocate(_header->value, 1);
			_node_alloc.deallocate(_nil, 1);
			_node_alloc.deallocate(_header, 1);
		}

};


