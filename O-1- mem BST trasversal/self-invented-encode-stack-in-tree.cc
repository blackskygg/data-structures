/**
 * Definition of TreeNode:
 * class TreeNode {
 * public:
 *     int val;
 *     TreeNode *left, *right;
 *     TreeNode(int val) {
 *         this->val = val;
 *         this->left = this->right = NULL;
 *     }
 * }
 * Example of iterate a tree:
 * BSTIterator iterator = BSTIterator(root);
 * while (iterator.hasNext()) {
 *    TreeNode * node = iterator.next();
 *    do something for node
 */

// This algorithm is self invented by myself while tackling lintcode 86.
// It's time and space complexity is the same as Morris trasversal, but here I'm encoding the stack in the open path
// instead of contructing a threaded binary tree on the fly :)

class BSTIterator {
public:
    /*
    * @param root: The root of binary tree.
    */BSTIterator(TreeNode * root)  {
        static TreeNode kMaxNode(numeric_limits<int>::max());
        
        top_ = &kMaxNode;
        if (root != nullptr) {
            father_ = top_;
            curr_ = root;
            state_ = kToLeft;
            GotoNext();
        } else {
            curr_ = top_;
        }
    }

    /*
     * @return: True if there has next node, or false
     */
    bool hasNext() {
        return curr_ != top_;
    }

    /*
     * @return: return next node
     */
    TreeNode * next() {
        TreeNode* result = curr_;
        state_ = kToRight;
        GotoNext();
        return result;
    }
private:
    // Updates curr to next node. Points curr to nullptr if no next node.
    // Encoding status in the pointers, we define that:
    // 1. father > curr, going left: curr->left = father ==> left > curr && right > curr
    // 2. father > curr, going right: curr->right = father ==> left < curr && right > curr
    // 3. father < curr, going left: curr->right = father, curr->left = curr->right or top ==> left > curr && righ < curr
    // 4. father < curr, going right: curr->right = father ==> left < curr && right < curr
    void GotoNext() {
        auto right_good = [&] {
            return father_->right == nullptr || father_->right->val > father_->val;
        };
        auto left_good = [&] {
            return father_->left == nullptr || father_->left->val < father_->val;
        };
        
        for (;state_ != kToPrint;) {
            switch (state_) {
            case kToLeft:
                if (curr_->left) {
                    auto temp = curr_->left;
                    if (father_->val > curr_->val || father_ == top_) {
                        // situation 1
                        curr_->left = father_;
                    } else {
                        // situation 3
                        curr_->left = (curr_->right ? curr_->right : top_);
                        curr_->right = father_;
                    }
                    father_ = curr_;
                    curr_ = temp;
                    state_ = kToLeft;
                } else {
                    state_ = kToPrint;
                }
                break;
            case kToRight:
                if (curr_->right) {
                    // situation 2 and 4
                    auto temp = curr_->right;
                    curr_->right = father_;
                    father_ = curr_;
                    curr_ = temp;
                    state_ = kToLeft;
                } else {
                    state_ = kToBack;
                }
                break;
            case kToBack:
                if (father_ == top_) {
                    // returning to top;
                    curr_ = top_;
                    state_ = kToPrint;
                } else { 
                    if (right_good()) {
                        if (!left_good()) {
                            // sit 1 from left
                            auto temp = father_->left;
                            father_->left = curr_;
                            curr_ = father_;
                            father_ = temp;
                            state_ = kToPrint;
                        } else {
                            // sit 2 from right
                            auto temp = father_->right;
                            father_->right = curr_;
                            curr_ = father_;
                            father_ = temp;
                            state_ = kToBack;
                        }
                    } else {
                        if (!left_good()) {
                            // sit 3 from left
                            auto temp = father_->right;
                            father_->right = (father_->left == top_ ? nullptr : father_->left);
                            father_->left = curr_;
                            curr_ = father_;
                            father_ = temp;
                            state_ = kToPrint;
                        } else {
                            // sit 4 from right
                            auto temp = father_->right;
                            father_->right = curr_;
                            curr_ = father_;
                            father_ = temp;
                            state_ = kToBack;
                        }
                    }
                }
                break;
            default:
                break;
            }
        }
    }

private:
    enum State {
      kToLeft,
      kToPrint,
      kToRight,
      kToBack,
    };

    State state_;
    TreeNode* top_;
    TreeNode* curr_;
    TreeNode* father_;
};
