#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// add thread class
class Thread {
	public:

		int id;
		long long time;
};

// functions to return children of a binary tree
int LeftChildIndex(int i) {
	return (i*2)+1;
}
int RightChildIndex(int i) {
	return (i*2)+2;
}



class JobQueue {
 private:
  int numThreads;
  vector<Thread> threads_; //will hold a min-heap of threads
  vector<int> jobs_;
  
  //for output
  vector<int> assigned_threads;
  vector<long long> start_times;
	
  //for debugging
  vector<int> assigned_threads2;
  vector<long long> start_times2;

  //outputs the assigned threads and start times of all jobs
  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); i++) {
      cout << assigned_threads[i] << " " << start_times[i] << "\n";
    }
  }
  

  void ReadData() {
    int m;
    cin >> numThreads >> m;
    jobs_.resize(m);
    threads_.resize(numThreads);
    for(int i = 0; i < m; i++) {
    	cin >> jobs_[i];
    }
    // initializing thread vector
    for (int i = 0; i < numThreads; i++) {
    	threads_[i].id = i;
    	threads_[i].time = 0;
    } 
  }
  
  void AssignJobs() {
  	
  	//PLAN:
    // threads start in min-heap formation
    // for each job, take root node of min-heap
    // return the current index and time of that thread
    // add the job time to the thread's time
    // siftdown the heap based on time, index
    // repeat? this way always know which thread is next w/out checking all
    
    assigned_threads.resize(jobs_.size());
    start_times.resize(jobs_.size());
    
    for(int i=0; i<jobs_.size();i++) {
    	assigned_threads[i] = threads_[0].id;
    	start_times[i] = threads_[0].time;
    	
    	threads_[0].time += jobs_[i];
    	SiftDown(0);
    }
    
    // TODO: replace this code with a faster algorithm.
    /*vector<long long> next_free_time(numThreads, 0);
    for (int i = 0; i < jobs_.size(); ++i) {
      int duration = jobs_[i];
      int next_thread = 0;
      for (int j = 0; j < numThreads; ++j) {
        if (next_free_time[j] < next_free_time[next_thread])
          next_thread = j;
      }
      assigned_threads[i] = next_thread;
      start_times[i] = next_free_time[next_thread];
      next_free_time[next_thread] += duration;
    }*/
  }
				         
  void SiftDown(int i) {
  	
  	int minIndex = i;
	
	int parentId = threads_[minIndex].id;
	long long parentTime = threads_[minIndex].time;
	
	int minId = parentId;
	long long minTime = parentTime;
	
	//check left
	int leftChild = LeftChildIndex(i);
	long long leftTime = -1; //initialize it to some value??...not sure if this is good
	int leftId = -1;   //is it okay to initialize these id values to this? 
	if(leftChild < threads_.size()) {
		leftTime = threads_[leftChild].time;
		leftId = threads_[leftChild].id;
		if(leftTime<minTime && leftTime!=-1) { //add condition that it also isn't negative
			minIndex = leftChild;
			minTime = threads_[minIndex].time;
			minId = leftId;
		}
		else if(leftTime==minTime && leftId<minId) {
			minIndex = leftChild;
			minTime = threads_[minIndex].time;
			minId = leftId;
		}
	}

	//check right
	int rightChild = RightChildIndex(i);
	long long rightTime= -1;
	int rightId = -1; 
	if(rightChild < threads_.size()) {
		rightTime = threads_[rightChild].time;
		rightId = threads_[rightChild].id;
		if(rightTime<minTime && rightTime!=-1) {
			minIndex = rightChild;
		}
		else if(rightTime == minTime && rightId < minId) {
			minIndex = rightChild;
		}
	}
	
	if(i!=minIndex) {
		swap(threads_[i], threads_[minIndex]);
		SiftDown(minIndex);
	}
  }
  
  //for debugging
  void WriteResponseDB() const {
    for (int i = 0; i < jobs_.size(); i++) {
      cout << assigned_threads2[i] << " " << start_times2[i] << "\n";
    }
  }
  
  void ReadDataDB() {
  	//generate some random input data
  	int m = rand() % 100 + 1;
  	numThreads = rand() % 100 + 1;
  	jobs_.resize(m);
  	threads_.resize(numThreads);
  	for(int i = 0; i < m; i++) {
  		jobs_[i] = rand() % 100 + 1;
  	}
  	
  	// initializing thread vector
    for (int i = 0; i < numThreads; i++) {
    	threads_[i].id = i;
    	threads_[i].time = 0;
    } 
  }
  
  void AssignJobsDB() {
    
    assigned_threads.resize(jobs_.size());
    start_times.resize(jobs_.size());
    
    assigned_threads2.resize(jobs_.size());
    start_times2.resize(jobs_.size());
    
    //my soln.
    for(int i=0; i<jobs_.size();i++) {
    	//return information from root node of min-heap
    	assigned_threads[i] = threads_[0].id;
    	start_times[i] = threads_[0].time;
    	
    	//
    	threads_[0].time += jobs_[i];
    	SiftDown(0);
    }
    
    //slow soln.
    vector<long long> next_free_time(numThreads, 0);
    for (int i = 0; i < jobs_.size(); ++i) {
      int duration = jobs_[i];
      int next_thread = 0;
      for (int j = 0; j < numThreads; ++j) {
        if (next_free_time[j] < next_free_time[next_thread])
          next_thread = j;
      }
      assigned_threads2[i] = next_thread;
      start_times2[i] = next_free_time[next_thread];
      next_free_time[next_thread] += duration;
    }
  }
  
  bool CheckTestDB() {
 	for(int i = 0;i<jobs_.size();i++) {
 		if(assigned_threads[i]!=assigned_threads2[i]||start_times[i]!=start_times2[i]) {
 			return false;
 		}
 	}
  return true;			
  } 
		
  void OutputDB() {
  	
  	cout << "Threads: " << numThreads << endl;
  	cout << "Num. Jobs: " << jobs_.size() << endl;
  	cout << "Jobs Times: "; 
	for (int i = 0; i<jobs_.size();i++) {
		cout << jobs_[i] << " ";	
  	}
  	
  	cout << endl;
  	cout << "My Alg. Output: " << endl;
  	WriteResponse();
  	cout << endl;
  	cout << "Naive Alg. Output: " << endl;
  	WriteResponseDB();
  }

  
		       
 public:
  void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
  
  //runs a stress-test comparing results of naive and fast alg.
  void StressTest() {
  	bool test_status = true;
  	int test_count = 1;
  	while(test_status) {
  		cout << test_count << endl;
  		ReadDataDB();
  		AssignJobsDB();
  		test_status = CheckTestDB();
  		
  		if(!test_status) {
  			cout << "Test " << test_count << " Failed!" << endl;
  			OutputDB();
  		}
		test_count++;	
  	}
  }
  
};

int main() {
	
  ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  //job_queue.StressTest();
  return 0;
}
