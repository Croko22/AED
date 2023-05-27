#include "DTree.h"
#include "Node.h"

// class DTree::Node
// {
// public:
//     Node(char ch = '\0') : c(ch){};
//     const char c = '\0';
//     std::array<std::unique_ptr<Node>, N> children;
//     // TODO: Esta es la clase hoja donde la data sera un template
//     bool isWord = false;
//     int data;
//     // Hoja<T> *hoja;
// };

DTree::Node *DTree::getNode(std::string word)
{
    auto current = root.get();
    for (auto &c : word)
    {
        const int index = c - 'a';

        auto child = current->children.at(index).get();
        if (child == nullptr)
            return nullptr;

        current = child;
    }
    return current;
}

DTree::DTree() : root(std::make_unique<Node>('\0')) {}

void DTree::insert(std::string word, int data)
{
    auto current = root.get();
    for (auto &c : word)
    {
        const int index = c - 'a';
        auto &child = current->children.at(index);

        if (child == nullptr)
        {
            child = std::make_unique<Node>(c);
        };

        current = child.get();
    }
    current->isWord = true;
    current->data = data;
}

void DTree::deleteWord(std::string word)
{
    Node *current = root.get();
    for (auto &c : word)
    {
        const int index = c - 'a';
        auto &child = current->children.at(index);

        if (child == nullptr)
            return;

        current = child.get();
    }

    current->isWord = false;
    current->data = 0;

    for (auto &child : current->children)
    {
        if (child != nullptr)
        {
            return;
        }
    }

    while (current != root.get() && !current->isWord && current->children.empty())
    {
        auto parent = root.get();
        for (auto &c : word)
        {
            const int index = c - 'a';
            auto child = parent->children.at(index).get();

            if (child == current)
            {
                delete child;
                break;
            }

            parent = child;
        }

        current = parent;
    }
}

int DTree::search(std::string word)
{
    auto node = getNode(word);
    if (node != nullptr && node->isWord)
        return node->data;
    else
        return -1;
}

bool DTree::startsWith(std::string prefix)
{
    return getNode(prefix) != nullptr;
}