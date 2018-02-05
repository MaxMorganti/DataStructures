#include <iostream>
#include <vector>
#include <algorithm>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using std::vector;
using std::ios_base;
using std::cin;
using std::cout;

class TreeOrders {

 public:	
	
  int n;
  vector <int> key;
  vector <int> left;
  vector <int> right;
  
  vector <int> results_inOrder;
  vector <int> results_preOrder;
  vector <int> results_postOrder;

  void read() {
    cin >> n;
    key.resize(n);
    left.resize(n);
    right.resize(n);
    for (int i = 0; i < n; i++) {
      cin >> key[i] >> left[i] >> right[i];
    }
  }

  void in_order(int index) {
  	
  	if(left[index]!=-1) {
  		in_order(left[index]);
  	}
  	
  	results_inOrder.push_back(key[index]);
  	
  	if(right[index]!=-1) {
  		in_order(right[index]);
  	}
  }

  void pre_order(int index) {
  	
  	results_preOrder.push_back(key[index]);
  	
  	if(left[index]!=-1) {
  		pre_order(left[index]);
  	}
  	
  	if(right[index]!=-1) {
  		pre_order(right[index]);
  	}
  }

  void post_order(int index) {
  	
  	if(left[index]!=-1) {
  		post_order(left[index]);
  	}
  	
  	if(right[index]!=-1) {
  		post_order(right[index]);
  	}
  	
  	results_postOrder.push_back(key[index]);
  	
  }

  
};

void print(vector <int> a) {
  for (size_t i = 0; i < a.size(); i++) {
    if (i > 0) {
      cout << ' ';
    }
    cout << a[i];
  }
  cout << '\n';
}

int main_with_large_stack_space() {
  ios_base::sync_with_stdio(0);
  TreeOrders t;
  t.read();
  
  t.in_order(0);
  t.pre_order(0);
  t.post_order(0);
  
  print(t.results_inOrder);
  print(t.results_preOrder);
  print(t.results_postOrder);
  
  return 0;
}

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
      if (rl.rlim_cur < kStackSize)
      {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0)
          {
              std::cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }
#endif

  return main_with_large_stack_space();
}

