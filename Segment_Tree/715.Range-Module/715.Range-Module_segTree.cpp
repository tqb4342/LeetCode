class RangeModule {
    class SegTree
    {
        public:
        int begin,end, status;
        SegTree* left;
        SegTree* right;
        SegTree(int a, int b, int s)
        {
            begin = a;
            end = b;
            status = s;
            left = NULL;
            right = NULL;
        }
        
        void remove(SegTree* &node)
        {
            if (!node) return;
            remove(node->left);
            remove(node->right);
            delete node;
            node = NULL;
        }
        
        
        int setStatus(int a, int b, int s)
        {
            if (begin>=b || end<=a)            // 1. [a,b]与这个区间不相交，返回原先的状态
                return status;                        
            if (a<=begin && end<=b)            // 2. [a,b]包括了整个区间，将该区间抹平
            {
                remove(left);
                remove(right);
                return status = s;
            }         
            if (!left)                         // 3. [a,b]与该区间相交，需考虑其子树
            {
                int mid = (end-begin)/2+begin;
                left = new SegTree(begin,mid,status);
                right = new SegTree(mid,end,status);
            }            
            int leftStatus = left->setStatus(a,b,s);
            int rightStatus = right->setStatus(a,b,s);
            return status = leftStatus && rightStatus;
        }
                
        int getStatus(int a, int b)
        {
            if (begin>=b || end<=a)            // 1. [a,b]与这个区间不相交，返回一个不影响结果的状态
                return true;            
            if (a<=begin && end<=b)            // 2. [a,b]包括了整个区间，返回该区间的状态
                return status;                        
            if (!left)                         // 3. [a,b]与该区间相交，但又没有子树，返回整个区间状态
                return status;
            int mid = (end-begin)/2+begin;      // 4. [a,b]与该区间相交，需要考虑其子树
            int leftStatus = left->getStatus(a,b);
            int rightStatus = right->getStatus(a,b);
            return leftStatus && rightStatus;            
        }
            
    };
    
    
public:
    
    SegTree root = SegTree(0,INT_MAX,false);
    
    RangeModule() 
    {
        
    }
    
    void addRange(int left, int right) 
    {
        root.setStatus(left,right,true);
    }
    
    bool queryRange(int left, int right) 
    {
        return root.getStatus(left,right);
    }
    
    void removeRange(int left, int right) 
    {
        root.setStatus(left,right,false);
    }
};

/**
 * Your RangeModule object will be instantiated and called as such:
 * RangeModule obj = new RangeModule();
 * obj.addRange(left,right);
 * bool param_2 = obj.queryRange(left,right);
 * obj.removeRange(left,right);
 */
