// reverse_iterator example
#include "../ft_containers/vector/Vector.hpp"
#include "../ft_containers/iterator/iterator.hpp"
#include "../ft_containers/iterator/reverse_iterator.hpp"
#include <iostream>     // std::cout
#include <iterator>     // ft::reverse_iterator
#include <vector>       // ft::vector
#include <map>

void	test_constructor() {
	ft::vector<int> myvector;
	for (int i=0; i<10; i++) myvector.push_back(i);
	typedef ft::vector<int>::iterator iter_type;                                                         // ? 0 1 2 3 4 5 6 7 8 9 ?
	iter_type from (myvector.begin());                     //   ^                                                         //         ------>
	iter_type until (myvector.end());                      //                       ^                                                         //
	ft::reverse_iterator<iter_type> rev_until (from);     // ^                                                         //         <------
	ft::reverse_iterator<iter_type> rev_from (until);     //
	std::cout << "myvector:";
	while (rev_from != rev_until)
	std::cout << ' ' << *rev_from++;
	std::cout << '\n';
}

void	test_base() {
  ft::vector<int> myvector;
  for (int i=0; i<10; i++) myvector.push_back(i);

  typedef ft::vector<int>::iterator iter_type;

  ft::reverse_iterator<iter_type> rev_end (myvector.begin());
  ft::reverse_iterator<iter_type> rev_begin (myvector.end());

  std::cout << "myvector:";
  for (iter_type it = rev_end.base(); it != rev_begin.base(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';
}

void	test_operator_star(){
	ft::vector<int> myvector;
  for (int i=0; i<10; i++) myvector.push_back(i);

  typedef ft::vector<int>::iterator iter_type;
                                                         // ? 9 8 7 6 5 4 3 2 1 0 ?
  iter_type from (myvector.begin());                     //   ^
                                                         //         ------>
  iter_type until (myvector.end());                      //                       ^
                                                         //
  ft::reverse_iterator<iter_type> rev_until (from);     // ^
                                                         //         <------
  ft::reverse_iterator<iter_type> rev_from (until);     //                     ^

  std::cout << "myvector:";
  while (rev_from != rev_until)
    std::cout << ' ' << *rev_from++;
  std::cout << '\n';
}

void	test_operator_plus(){
	ft::vector<int> myvector;
  for (int i=0; i<10; i++) myvector.push_back(i);	// myvector: 0 1 2 3 4 5 6 7 8 9

  typedef ft::vector<int>::iterator iter_type;

  ft::reverse_iterator<iter_type> rev_it;

  rev_it = myvector.rbegin() +3;

  std::cout << "The fourth element from the end is: " << *rev_it << '\n';
}

void test_operator_plus_plus(){
ft::vector<int> myvector;
  for (int i=0; i<10; i++) myvector.push_back(i);

  typedef ft::vector<int>::iterator iter_type;
                                                         // ? 9 8 7 6 5 4 3 2 1 0 ?
  iter_type from (myvector.begin());                     //   ^
                                                         //         ------>
  iter_type until (myvector.end());                      //                       ^
                                                         //
  ft::reverse_iterator<iter_type> rev_until (from);     // ^
                                                         //         <------
  ft::reverse_iterator<iter_type> rev_from (until);     //                     ^

  std::cout << "myvector:";
  while (rev_from != rev_until) {
    std::cout << ' ' << *rev_from;
    ++rev_from;
  }
  std::cout << '\n';
}

void test_operator_plus_equals(){
ft::vector<int> myvector;
  for (int i=0; i<10; i++) myvector.push_back(i);	// myvector: 0 1 2 3 4 5 6 7 8 9

  typedef ft::vector<int>::iterator iter_type;

  ft::reverse_iterator<iter_type> rev_iterator = myvector.rbegin();

  rev_iterator += 2;

  std::cout << "The third element from the end is: " << *rev_iterator << '\n';
}

void test_operator_minus(){
ft::vector<int> myvector;
  for (int i=0; i<10; i++) myvector.push_back(i);	// myvector: 0 1 2 3 4 5 6 7 8 9

  typedef ft::vector<int>::iterator iter_type;

  ft::reverse_iterator<iter_type> rev_iterator;

  rev_iterator = myvector.rend() - 3;

  std::cout << "myvector.rend()-3 points to: " << *rev_iterator << '\n';
}

void	test_operator_minus_minus(){	
ft::vector<int> myvector;
  for (int i=0; i<10; i++) myvector.push_back(i);

  typedef ft::vector<int>::iterator iter_type;

  ft::reverse_iterator<iter_type> rev_begin (myvector.end());
  ft::reverse_iterator<iter_type> rev_end (myvector.begin());

  ft::reverse_iterator<iter_type> rev_iterator = rev_begin;
  while ( rev_iterator != rev_end )
    std::cout << *rev_iterator++ << ' ';
  std::cout << '\n';

  while ( rev_iterator != rev_begin )
    std::cout << *(--rev_iterator) << ' ';
  std::cout << '\n';
}

void	test_operator_minus_equals(){	
ft::vector<int> myvector;
  for (int i=0; i<10; i++) myvector.push_back(i);	// myvector: 0 1 2 3 4 5 6 7 8 9

  typedef ft::vector<int>::iterator iter_type;

  ft::reverse_iterator<iter_type> rev_iterator = myvector.rend();

  rev_iterator -= 4;

  std::cout << "rev_iterator now points to: " << *rev_iterator << '\n';
}


void test_operator_arrow(){	
	std::map<int,std::string> numbers;
  numbers.insert (std::make_pair(1,"one"));
  numbers.insert (std::make_pair(2,"two"));
  numbers.insert (std::make_pair(3,"three"));

  typedef std::map<int,std::string>::iterator map_iter;

  ft::reverse_iterator<map_iter> rev_end (numbers.begin());

  ft::reverse_iterator<map_iter> rev_iterator (numbers.end());

  for ( ; rev_iterator != rev_end ; ++rev_iterator )
    std::cout << rev_iterator->first << ' ' << rev_iterator->second << '\n';
}

void test_operator_brackets(){
ft::vector<int> myvector;
  for (int i=0; i<10; i++) myvector.push_back(i);  // myvector: 0 1 2 3 4 5 6 7 8 9

  typedef ft::vector<int>::iterator iter_type;

  ft::reverse_iterator<iter_type> rev_iterator = myvector.rbegin();

  std::cout << "The fourth element from the end is: " << rev_iterator[3] << '\n';
}

void test_relational(){
ft::vector<int> myvector;
  for (int i=0; i<10; i++) myvector.push_back(i);

  typedef ft::vector<int>::iterator iter_type;
                                                         // ? 9 8 7 6 5 4 3 2 1 0 ?
  iter_type from (myvector.begin());                     //   ^
                                                         //         ------>
  iter_type until (myvector.end());                      //                       ^
                                                         //
  ft::reverse_iterator<iter_type> rev_until (from);     // ^
                                                         //         <------
  ft::reverse_iterator<iter_type> rev_from (until);     //                     ^

  std::cout << "myvector:";
  while (rev_from != rev_until)
    std::cout << ' ' << *rev_from++;
  std::cout << '\n';
}

void test_operator_plus_nonmember(){
ft::vector<int> myvector;
  for (int i=0; i<10; i++) myvector.push_back(i);	// myvector: 0 1 2 3 4 5 6 7 8 9

  typedef ft::vector<int>::iterator iter_type;

  ft::reverse_iterator<iter_type> rev_it;

  rev_it = 3 + myvector.rbegin();

  std::cout << "The fourth element from the end is: " << *rev_it << '\n';
}	

void test_operator_minus_nonmember(){
ft::vector<int> myvector;
  for (int i=0; i<10; i++) myvector.push_back(i);

  ft::reverse_iterator<ft::vector<int>::iterator> from,until;

  from = myvector.rbegin();
  until = myvector.rend();

  std::cout << "myvector has " << (until-from) << " elements.\n";
}

int main()
{
	test_constructor();
	test_base();
	test_operator_star();
	test_operator_plus();
	test_operator_plus_plus();
	test_operator_plus_equals();
	test_operator_minus();
	test_operator_minus_minus();
	test_operator_minus_equals();
	test_operator_arrow();
	test_operator_brackets();
	test_relational();
	test_operator_plus_nonmember();
	test_operator_minus_nonmember();
	return (0);
}