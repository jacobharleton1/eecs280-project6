#include "BinarySearchTree.hpp"
#include "unit_test_framework.hpp"
#include <sstream>
#include <vector>

using namespace std;

TEST(test_empty_default_constructed) {
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.empty());
    ASSERT_EQUAL(tree.height(), 0u);
    ASSERT_EQUAL(tree.size(), 0u);
}

TEST(test_insert) {
    BinarySearchTree<int> tree;
    tree.insert(3);
    ASSERT_FALSE(tree.empty());
    ASSERT_EQUAL(tree.height(), 1u);
    ASSERT_EQUAL(tree.size(), 1u);
}

TEST(test_height_balanced){
    BinarySearchTree<int> balanced_tree;
    balanced_tree.insert(5);
    balanced_tree.insert(3);
    balanced_tree.insert(7);
    ASSERT_EQUAL(balanced_tree.height(), 2u);
}

TEST(test_height_skewed){
    BinarySearchTree<int> balanced_tree;
    balanced_tree.insert(3);
    balanced_tree.insert(5);
    balanced_tree.insert(7);
    ASSERT_EQUAL(balanced_tree.height(), 3u);
}

TEST(test_find_found){
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);

    auto it = tree.find(3);
    ASSERT_NOT_EQUAL(it, tree.end());
    ASSERT_EQUAL(*it, 3);
}

TEST(test_find_not_found){
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);

    ASSERT_EQUAL(tree.find(99), tree.end());
}

TEST(test_find_empty_tree){
    BinarySearchTree<int> tree;

    ASSERT_EQUAL(tree.find(99), tree.end());
}

TEST(test_sorting_invariant_success){
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(1);
    tree.insert(4);
    ASSERT_TRUE(tree.check_sorting_invariant());
}

TEST(test_sorting_invariant_fail){
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(3);

    *tree.begin() = 7;

    ASSERT_FALSE(tree.check_sorting_invariant());
}

TEST(test_in_order_traversal_is_sorterd){
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(1);
    tree.insert(4);

    ostringstream oss;
    tree.traverse_inorder(oss);


    ASSERT_EQUAL(oss.str(), "1 3 4 5 7 ");
}

TEST(test_preorder_root_first){
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);

    ostringstream oss;
    
    tree.traverse_preorder(oss);

    ASSERT_EQUAL(oss.str(), "5 3 7 ");
}

TEST(test_min_max_normal){
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    
    ASSERT_EQUAL(*tree.min_element(), 3);
    ASSERT_EQUAL(*tree.max_element(), 7);
}

TEST(test_min_max_empty){
    BinarySearchTree<int> tree;
    
    ASSERT_EQUAL(tree.min_element(), tree.end());
    ASSERT_EQUAL(tree.max_element(), tree.end());
}

TEST(test_iterator){
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);

    vector<int> result;

    for (int x : tree){
        result.push_back(x);
    }    

    vector<int> expected_output = {3,5,7};
    ASSERT_EQUAL(result, expected_output);
}

TEST(min_greater_than){
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(1);

    ASSERT_EQUAL(*tree.min_greater_than(3), 5);
    ASSERT_EQUAL(*tree.min_greater_than(0), 1); 
    ASSERT_EQUAL(tree.min_greater_than(7), tree.end());
}

TEST(test_copy){
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);

    BinarySearchTree<int> copy(tree);

    copy.insert(9);
    ASSERT_EQUAL(tree.size(), 3u);
    ASSERT_EQUAL(copy.size(), 4u);
    ASSERT_TRUE(copy.check_sorting_invariant());
}

TEST_MAIN()
