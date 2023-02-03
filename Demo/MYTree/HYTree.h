

#include "stdio.h"
#include <cmath>
#include <queue>
#include <utility>


class HYTree {
public:
    
    int value;
    
    HYTree* left;
    HYTree* right;
    
    HYTree(int _value):value(_value) {}
    ~HYTree() {}
    
    
    static HYTree* randomFullTree(int count, unsigned int range) {
        if (count <= 0) return nullptr;
        
        HYTree* root = new HYTree(rand() % range);
        
        int layer = floor(log2(count));
        int fullyLayerCount = (1 << layer) - 2;
        int targetMidCount = 1 << (layer - 1);
        
        int resetCount = count - 1 - fullyLayerCount;
        
        
        int leftCount = fullyLayerCount >> 1;
        int rightCount = fullyLayerCount >> 1;
        
        leftCount += fmin(resetCount, targetMidCount);
        rightCount += fmax(0, resetCount - targetMidCount);
        
        root->left = randomFullTree(leftCount, range);
        root->right = randomFullTree(rightCount, range);
        
        return root;
    }
    
    
    int maxDepth() {
        int leftDepth = 0;
        int rightDepth = 0;
        if (left) leftDepth = left->maxDepth();
        if (right) rightDepth = right->maxDepth();
        return std::max(leftDepth, rightDepth) + 1;
    }
    
    void printRealTree() {
        
        int maxLayer = maxDepth();
        int preLayerCount = 1 << (maxLayer - 2);
        int maxWidth = 4 * preLayerCount - 1;
        
        
        std::queue<std::pair<HYTree*, std::pair<int, int>>> q; // {value, {layer, idx}}
        int currentLayer = 1;
        
        q.push(std::make_pair(this, std::make_pair(1, 1)));
        
        while (!q.empty()) {
            std::pair<HYTree*, std::pair<int, int>> topPair = q.front();
            HYTree* topNode = topPair.first;
            std::pair<int, int> pos = topPair.second;
            
            
            if (topNode->left) {
                q.push(std::make_pair(topNode->left, std::make_pair(pos.first + 1, pos.second * 2)));
            }
            
            if (topNode->right) {
                q.push(std::make_pair(topNode->right, std::make_pair(pos.first + 1, pos.second * 2 + 1)));
            }
            
            q.pop();
        }
    }
};
