#pragma once
#include <memory>
#include <string>
#include "Node.h"

/**
 * @brief Balanced binary tree implementation with basic operations.
 */
class BinaryTree
{
private:
    std::unique_ptr<Node> root{nullptr};

public:
    BinaryTree() = default;
    ~BinaryTree() = default;

    void InsertNode(int key);
    void DeleteNode(int key);

    /**
     * @brief Method used to get the first common ancestor between two keys.
     * This operation involves the data retrieval of each requested node.
     * 
     * @param firstValue First value to be found.
     * @param secondValue Second value to be found.
     * @return int The first common ancestor between the two nodes
     */
    int FindCommonAncestor(int firstValue, int secondValue);    

    std::string Traverse();
private:
    /**
     * @brief Data modification operations include the adition & deletion of a node
     * 
     * @param stepNode Node which will be iterated to add/delete the requested value
     * @param key value to be added/deleted
     * @return std::unique_ptr<Node> root node
     */
    void InsertNode(std::unique_ptr<Node> &stepNode, int key);
    void DeleteNode(std::unique_ptr<Node> &stepNode, int key);

    /**
     * @brief calculates the height of a given subtree
     * 
     * @param stepNode root node (start point)
     * @return int calculated height
     */
    int CalculateHeight(const std::unique_ptr<Node> &stepNode);

    /**
     * @brief auxiliar method to validate the inputs of the common ancestor finding operation;     
     */
    void CheckInputs(int firstValue, int secondValue);

    /**
     * @brief Auxiliar method to calculate LCA given a subtree
     */
    int FindCommonAncestor(const std::unique_ptr<Node> &stepNode, int firstValue, int secondValue);

    /**
     * @brief Data retrieval operations which intends to find the minimun/maximun 
     * or a specific value given a root node
     * 
     * @param stepNode root node (start point of the usage of find)
     * @return int requested value
     */
    int FindMin(const std::unique_ptr<Node> &stepNode);
    int FindMax(const std::unique_ptr<Node> &stepNode);
    bool Search(int key);

    /**
     * @brief performs a rebalance of the whole tree this method only
     * should be called in certains cases as the insertion or deletion
     * of nodes, operations with data retrieval responsabilities shouldn't
     * call it.
     */
    void Rebalance(std::unique_ptr<Node> &stepNode);

    /**
     * @brief Balance operations auxiliars, used to perform movements in the
     * tree childs, both from left side subtrees or right side subtrees.
     * 
     * @param stepNode root of the subtree to be rotated
     */
    void RotateLeftChild(std::unique_ptr<Node> &stepNode);
    void RotateTwiceLeftChild(std::unique_ptr<Node> &stepNode);
    void RotateRightChild(std::unique_ptr<Node> &stepNode);
    void RotateTwiceRightChild(std::unique_ptr<Node> &stepNode);

    /**
     * @brief method used to print the tree contents
     * 
     * @param stepNode Node to be iterated
     * @return std::string representation of the tree in form left - root - right
     */
    std::string Traverse(const std::unique_ptr<Node> &stepNode);
};