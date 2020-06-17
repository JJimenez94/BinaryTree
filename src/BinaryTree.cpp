#include <algorithm>
#include <sstream>
#include <stdexcept>
#include "BinaryTree.h"

constexpr int MINIMUN_HEIGHT{1};

using namespace std;

void BinaryTree::InsertNode(int key)
{
    InsertNode(root, key);
}

void BinaryTree::DeleteNode(int key)
{
    DeleteNode(root, key);
}

/**
 * @remark duplicate values will be ignored
 */
void BinaryTree::InsertNode(unique_ptr<Node> &stepNode, int key)
{
    if (stepNode == nullptr)
        stepNode = make_unique<Node>(key);
    else if (key < stepNode->data)
        InsertNode(stepNode->left, key);
    else if (key > stepNode->data)
        InsertNode(stepNode->right, key);

    Rebalance(stepNode);
}

void BinaryTree::DeleteNode(unique_ptr<Node> &stepNode, int key)
{
    if (root == nullptr || stepNode == nullptr)
        return; // empty tree or non existent node should do nothing

    if (key < stepNode->data)
        DeleteNode(stepNode->left, key);
    else if (key > stepNode->data)
        DeleteNode(stepNode->right, key);
    else if (stepNode->left != nullptr && stepNode->right != nullptr) // value found, with two childs.
    {
        stepNode->data = FindMin(stepNode->right);
        DeleteNode(stepNode->right, stepNode->data);
    }
    else // value, with one child
    {
        unique_ptr<Node> tempNode{move(stepNode)};
        stepNode = (tempNode->left != nullptr) ? move(tempNode->left) : move(tempNode->right);
    }

    // Rebalance(root);
}

int BinaryTree::FindCommonAncestor(int firstValue, int secondValue)
{
    CheckInputs(firstValue, secondValue);
    return FindCommonAncestor(root, firstValue, secondValue);
}

string BinaryTree::Traverse()
{
    return Traverse(root);
}

string BinaryTree::Traverse(const unique_ptr<Node> &stepNode)
{
    if (stepNode == nullptr)
        return "";

    stringstream output;
    output << Traverse(stepNode->left);
    output << stepNode->data << " ";
    output << Traverse(stepNode->right);
    return output.str();
}

int BinaryTree::CalculateHeight(const unique_ptr<Node> &stepNode)
{
    if (stepNode != nullptr)
    {
        int LeftHeight = CalculateHeight(stepNode->left);
        int RightHeight = CalculateHeight(stepNode->right);

        return 1 + max(LeftHeight, RightHeight);
    }

    return 0;
}

void BinaryTree::CheckInputs(int firstValue, int secondValue)
{
    if (root == nullptr)
        throw logic_error("Empty tree");

    if (!Search(firstValue) || !Search(secondValue))
        throw invalid_argument("Check your inputs, some values doesn't exists");
}

int BinaryTree::FindCommonAncestor(const unique_ptr<Node> &stepNode, int firstValue, int secondValue)
{
    if (stepNode == nullptr)
        throw logic_error("Invalid iteration");

    if (stepNode->data > firstValue && stepNode->data > secondValue)
        return FindCommonAncestor(stepNode->left, firstValue, secondValue);
    else if (stepNode->data < firstValue && stepNode->data < secondValue)
        return FindCommonAncestor(stepNode->right, firstValue, secondValue);

    return stepNode->data;
}

int BinaryTree::FindMin(const unique_ptr<Node> &stepNode)
{
    auto temp = stepNode.get();

    if (temp != nullptr)
        while (temp->left != nullptr)
            temp = temp->left.get();

    return temp->data;
}

int BinaryTree::FindMax(const unique_ptr<Node> &stepNode)
{
    auto temp = stepNode.get();

    if (temp != nullptr)
        while (temp->right != nullptr)
            temp = temp->right.get();

    return temp->data;
}

bool BinaryTree::Search(int key)
{
    auto temp = root.get();

    while (temp != nullptr)
        if (key < temp->data)
            temp = temp->left.get();
        else if (key > temp->data)
            temp = temp->right.get();
        else
            return true;

    return false;
}

void BinaryTree::Rebalance(unique_ptr<Node> &stepNode)
{
    if (stepNode == nullptr)
        return;

    auto leftHeight = CalculateHeight(stepNode->left);
    auto rightHeight = CalculateHeight(stepNode->right);

    if ((leftHeight - rightHeight) > MINIMUN_HEIGHT)
    {
        if (CalculateHeight(stepNode->left->left) >= CalculateHeight(root->left->right))
            RotateLeftChild(stepNode);
        else
            RotateTwiceLeftChild(stepNode);
    }
    else if ((rightHeight - leftHeight) > MINIMUN_HEIGHT)
    {
        if (CalculateHeight(stepNode->right->right) >= CalculateHeight(root->right->left))
            RotateRightChild(stepNode);
        else
            RotateTwiceRightChild(stepNode);
    }
}

void BinaryTree::RotateLeftChild(unique_ptr<Node> &stepNode)
{
    auto auxNode = move(stepNode->left);
    stepNode->left = move(auxNode->right);
    auxNode->right = move(stepNode);
    stepNode = move(auxNode);
}

void BinaryTree::RotateTwiceLeftChild(unique_ptr<Node> &stepNode)
{
    RotateRightChild(stepNode->left);
    RotateLeftChild(stepNode);
}

void BinaryTree::RotateRightChild(unique_ptr<Node> &stepNode)
{
    auto auxNode = move(stepNode->right);
    stepNode->right = move(auxNode->left);
    auxNode->left = move(stepNode);
    stepNode = move(auxNode);
}

void BinaryTree::RotateTwiceRightChild(unique_ptr<Node> &stepNode)
{
    RotateLeftChild(stepNode->right);
    RotateRightChild(stepNode);
}