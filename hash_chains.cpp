#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::cin;



struct Query {
    string type, s;
    size_t ind;
};

class QueryProcessor {
    int bucket_count;
    
    vector<string> elems;
    
    vector<vector<string> > elems2;
    
    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }

public:
    explicit QueryProcessor(int bucket_count): bucket_count(bucket_count) {}

    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void writeSearchResult(bool was_found) const {
        std::cout << (was_found ? "yes\n" : "no\n");
    }
    
    void processQueries() {
        int n;
        cin >> n;
        elems2.resize(bucket_count);
        for (int i = 0; i < n; ++i)
            processQuery3(readQuery());
    }

    void processQuery(const Query& query) {
        if (query.type == "check") {
            // use reverse order, because we append strings to the end
            for (int i = static_cast<int>(elems.size()) - 1; i >= 0; --i)
                if (hash_func(elems[i]) == query.ind)
                    std::cout << elems[i] << " ";
            std::cout << "\n";
        } else {
            vector<string>::iterator it = std::find(elems.begin(), elems.end(), query.s);
            if (query.type == "find")
                writeSearchResult(it != elems.end());
            else if (query.type == "add") {
                if (it == elems.end())
                    elems.push_back(query.s);
            } else if (query.type == "del") {
                if (it != elems.end())
                    elems.erase(it);
            }
        }
    }
    
    
    void processQuery3(const Query& query) {
    	
    	if(query.type == "check") {
    		size_t main_index = query.ind;
    		for (int i = static_cast<int>(elems2[main_index].size()) - 1; i >= 0; i--) {
    			std::cout << elems2[main_index][i] << " ";
    		}
    		std::cout<<"\n";
    	}
    	else {
    		size_t main_index = hash_func(query.s);
    		vector<string>::iterator it = std::find(elems2[main_index].begin(), elems2[main_index].end(), query.s);
    		
    		if(query.type == "add") {
    			if(it==elems2[main_index].end()) {
    			elems2[main_index].push_back(query.s);
    			}	
    		}
    		
    		else if(query.type == "find") {	
                writeSearchResult(it != elems2[main_index].end());
    		}	
    		
    		else if(query.type == "del") {
    			if (it != elems2[main_index].end()) {
    			elems2[main_index].erase(it);
    			}
    		}			
    	}
    }

    
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    
    proc.processQueries();
    
    return 0;
}
