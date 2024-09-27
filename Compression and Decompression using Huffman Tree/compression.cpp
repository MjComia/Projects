#include <iostream>
#include <fstream>
#include <unordered_map>
#include <queue>
using namespace std;

struct Node {
    char data;
    int freq;
    Node* left;
    Node* right;
};

Node* createNode(char data, int freq, Node* left = nullptr, Node* right = nullptr) {
    Node* newNode = new Node{data, freq, left, right};
    return newNode;
}

struct CompareNodes {
    bool operator()(Node* left, Node* right) const {
        return left->freq > right->freq;
    }
};

Node* buildHuffmanTree(const string& text) {
    unordered_map<char, int> freq;
    for (char ch : text) {
        freq[ch]++;
    }

    priority_queue<Node*, vector<Node*>, CompareNodes> pq;
    for (auto& pair : freq) {
        pq.push(createNode(pair.first, pair.second));
    }

    while (pq.size() > 1) {
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();
        int sumFreq = left->freq + right->freq;
        pq.push(createNode('\0', sumFreq, left, right));
    }

    return pq.top();
}

void generateCodes(Node* root, string code, unordered_map<char, string>& codes) {
    if (root == nullptr) {
        return;
    }

    if (root->data != '\0') {
        codes[root->data] = code;
    }

    generateCodes(root->left, code + "0", codes);
    generateCodes(root->right, code + "1", codes);
}

Node* serializeTwo(const string& text, ofstream& treeFile) {
    unordered_map<char, int> freq;


    for (char ch : text) {
        freq[ch]++;
    }

    priority_queue<Node*, vector<Node*>, CompareNodes> pq;

    for (auto& pair : freq) {
        pq.push(createNode(pair.first, pair.second));
        treeFile << pair.first<< pair.second;
    }

    return pq.top();
}
void compressText(Node* root, const string& text, ofstream& outputFile) {
    unordered_map<char, string> codes;
    generateCodes(root, "", codes);
    string compressedText;
    for (char ch : text) {
        compressedText += codes[ch];
        cout << ch << ": " << codes[ch] << endl;
    }
    cout << "Compressed Binary Representation without padding:" << compressedText.length() << endl;

    size_t padding = 8 - compressedText.size() % 8;
    compressedText += string(padding, '1');
    cout << "Compressed Binary Representation:" << compressedText << endl;
    for (size_t i = 0; i < compressedText.size(); i += 8) {
        string byte = compressedText.substr(i, 8);

        int decimalValue = stoi(byte, nullptr, 2);

        char asciiChar = static_cast<char>(decimalValue);

        outputFile << asciiChar;
    }
}

void displayResult(const string& compressedFileName, const string& treeFileName) {
    cout << "Compressed File Content:" << endl;
    ifstream compressedFile(compressedFileName, ios::binary);
    cout << noskipws;
    char ch;
    while (compressedFile >> ch) {
        cout << ch;
    }
    cout << endl;
    compressedFile.close();
    cout << "\nHuffman Tree (Serialized):" << endl;
    ifstream treeFile(treeFileName);
    while (treeFile >> ch) {
        cout << ch;
    }
    cout << endl;
    treeFile.close();
}

int main() {
    string inputFileName = "input.txt";
    string compressedFileName = "compressed.txt";
    string treeFileName = "compressedTree.txt";

    ifstream inputFile(inputFileName);
    string text((istreambuf_iterator<char>(inputFile)), (istreambuf_iterator<char>()));
    inputFile.close();


    ofstream treeFile(treeFileName);
    serializeTwo(text,treeFile);
    treeFile.close();

    Node* root = buildHuffmanTree(text);

    unordered_map<char, string> codes;
    generateCodes(root, "", codes);

    ofstream compressedFile(compressedFileName, ios::binary);
    compressText(root, text, compressedFile);
    compressedFile.close();

    cout << "File compressed successfully!" << endl;

    displayResult(compressedFileName, treeFileName);

    return 0;
}

