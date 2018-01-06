#include <algorithm>
#include <iostream>
#include <vector>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using namespace std;

class Node;

class Node {
public:
    int key;
    Node *parent;
    vector<Node *> children;
    
    Node() {
        this->parent = NULL;
    }
    
    void setParent(Node *theParent) {
        parent = theParent;
        parent->children.push_back(this);
    }
    
    //added method returning num of children
    long getSizeChildren() {
        return children.size();
    }
    
    //add method returning key of child nodes
    int getChildKey(int j) {
        return children[j]->key;
    }
    
};

//added recursive function that descends tree to find height
int height(vector<Node> &nodes, int index) {
    
    
    long child_size = 0;
    child_size = nodes[index].getSizeChildren();
    
    //if no children, return 0
    if(child_size == 0) {
        return 0;
    }
    
    //check max. height of all child branches and increment by one
    else {
        int maxHeight = 0;
        for(int i = 0; i<child_size; i++) {
            //for each child node, retrieve the key
            //and use to make a recursive function call
            int check_index = nodes[index].getChildKey(i);
            int branch_height = height(nodes, check_index);
            maxHeight = max(maxHeight, branch_height);
        }
        return (1 + maxHeight);
    }
}


int main_with_large_stack_space() {
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;
    
    vector<Node> nodes;
    nodes.resize(n);
    for (int child_index = 0; child_index < n; child_index++) {
        int parent_index;
        cin >> parent_index;
        if (parent_index >= 0)
            nodes[child_index].setParent(&nodes[parent_index]);
        nodes[child_index].key = child_index;
    }
    
    
    
    
    //////////////////////////////////////////////////////////////
    // Replace this code with a faster implementation
    /*int maxHeight = 0;
    for (int leaf_index = 0; leaf_index < n; leaf_index++) {
        int height = 0;
        for (Node *v = &nodes[leaf_index]; v != NULL; v = v->parent)
            height++;
        maxHeight = std::max(maxHeight, height);
    }
    
    std::cout << maxHeight << std::endl;*/
    
    
    
    
    //finding root node, else statement to set to zero?
    int root_index = 0;
    for(int i= 0; i < nodes.size();i++) {
        if((nodes[i]).parent == NULL) {
            root_index = i;
        }
    }
    
    cout << 1 + height(nodes, root_index);
    ///////////////////////////////////////////////////////////////
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
                cerr << "setrlimit returned result = " << result << std::endl;
            }
        }
    }
    
#endif
    return main_with_large_stack_space();
}
