#include <iostream>
#include <stack>
#include <string>

using namespace std;

struct Node {
    string data;
    Node* left;
    Node* right;
};

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

Node* constructExpressionTree(const string& expression) {
    stack<Node*> st;
    for (char c : expression) {
        Node* newNode = new Node;
        newNode->data = c;
        newNode->left = newNode->right = nullptr;

        if (isOperator(c)) {
            newNode->right = st.top();
            st.pop();
            newNode->left = st.top();
            st.pop();
        }
        st.push(newNode);
    }
    return st.top();
}

void printRootValue(Node* root) {
    cout << "Root Value: " << root->data << endl;
}

int main() {
    string expression = "((3+4)*5)";
    Node* root = constructExpressionTree(expression);
    printRootValue(root);

    return 0;
}