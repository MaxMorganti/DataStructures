#include <iostream>
#include <vector>
#include <algorithm>

/*
using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;
*/

using namespace std;

//two simple functions to return vector index of child nodes
//based on input index
int LeftChildIndex(int i) {
	return (i*2)+1;
}
int RightChildIndex(int i) {
	return (i*2)+2;
}

class HeapBuilder {
 private:
  vector<int> data_;
  vector< pair<int, int> > swaps_;

  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void ReadData() {
    int n;
    cin >> n;
    data_.resize(n);
    for(int i = 0; i < n; ++i)
      cin >> data_[i];
  }
  
  // Compares a node to its children and swaps it with
  // with the smallest child if it is greater than either (for a min-heap)
  void SiftDown(int i) {
	int minIndex = i;
	int leftChild = LeftChildIndex(i);
	if(leftChild < data_.size()&&data_[leftChild]<data_[minIndex]) {
		minIndex = leftChild;
	}
	int rightChild = RightChildIndex(i);
	if(rightChild < data_.size()&&data_[rightChild]<data_[minIndex]) {
		minIndex = rightChild;
	}
	if(i!=minIndex) {
		swap(data_[i], data_[minIndex]);
		//record swaps in a vector
		swaps_.push_back(make_pair(i, minIndex));
		SiftDown(minIndex);
		}
  }
  
  void GenerateSwapsNaive() {
    swaps_.clear();
    // The following naive implementation just sorts 
    // the given sequence using selection sort algorithm
    // and saves the resulting sequence of swaps.
    // This turns the given array into a heap, 
    // but in the worst case gives a quadratic number of swaps.
    //
    // TODO: replace by a more efficient implementation
    for (int i = 0; i < data_.size(); ++i)
      for (int j = i + 1; j < data_.size(); ++j) {
        if (data_[i] > data_[j]) {
          swap(data_[i], data_[j]);
          swaps_.push_back(make_pair(i, j));
        }
      }    
  }
  
  void GenerateSwaps() {
    swaps_.clear();
    // Build heap by "sifting down" non-leaf nodes
    int size = data_.size();
    for(int i = ((size/2)-1); i >= 0; i--) {
    	SiftDown(i);
    }  
  }
  
 public:
  void Solve() {
    ReadData();
    GenerateSwaps();
    WriteResponse();
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
