#include <iostream>
#include <fstream>
#include <unordered_map>
#include <queue>
#include <bitset>
using namespace std;

unordered_map<char,int>freqss;
int bitz;
int bitzP;
struct Node {
    char data;
    int freq;
    Node* left;
    Node* right;
};

struct CompareNodes {
    bool operator()(Node* left, Node* right) const {
        return left->freq > right->freq;
    }
};

Node* createNode(char data, int freq, Node* left = nullptr, Node* right = nullptr) {
    Node* newNode = new Node{data, freq, left, right};
    return newNode;
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

Node* load(priority_queue<Node*, vector<Node*>, CompareNodes>& pq, unordered_map<char, string>& codes) {
    ifstream inputFile("compressedTree.txt");
    string fileContents((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());
    priority_queue<Node*, vector<Node*>, CompareNodes> tempPQ;  // Make a copy of pq for use to print the values
    inputFile.close();

        for (size_t i = 0; i < fileContents.size(); i += 2) {
        if (i + 1 < fileContents.size()) {
            char character = fileContents[i];
            int digit = fileContents[i + 1] - '0'; // Convert the digit character to an integer
            Node* newNode = createNode(character, digit);
            pq.push(newNode);
            tempPQ.push(newNode);
        }
    }

  priority_queue<Node*, vector<Node*>, CompareNodes> printPQ = tempPQ;  // Make a separate copy for printing

    cout << "Elements of the priority queue during construction:\n";
    while (!printPQ.empty()) {
        cout << "Data: " << printPQ.top()->data << ", Freq: " << printPQ.top()->freq << endl;
        freqss.insert(make_pair(printPQ.top()->data,printPQ.top()->freq)); //The character and the frequency are inserted in the map
        printPQ.pop();
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

string decompressTheText(){
ifstream decomFile("compressed.txt");
string fileConts((istreambuf_iterator<char>(decomFile)), istreambuf_iterator<char>());
string wApp;
cout<<"Compressed Text : "<<fileConts<<endl;
    for (char ch : fileConts) {
        int asciiValue = static_cast<unsigned char>(ch); // Ensure correct conversion for extended ASCII characters
        bitset<8> binaryValue(asciiValue);
        wApp += binaryValue.to_string();
        cout << ch << "\t" << asciiValue << "\t" << binaryValue << std::endl;
    }
    cout<<"The complete binary with padding: " <<wApp<<endl;
    bitzP = wApp.length();
    cout<<"The number of binary codes with padding: "<<bitzP<<endl;
    return wApp;
 }

string getOrigBit(){
string PaddedBits = decompressTheText();
int limit = bitz;
string newBits = PaddedBits.substr(0,limit);
return newBits;
}

string decodeHuffman(Node * root, const string& binaryString){
    Node* current = root;
    string decodedString;

    for (char bit : binaryString) {
        if (bit == '0') {
            current = current->left;
        } else if (bit == '1') {
            current = current->right;
        }

        if (current->left == nullptr && current->right == nullptr) {
            decodedString += current->data;
            current = root;
        }
    }

    return decodedString;
}

int main() {
    string compressedFileName = "compressed.txt";
    string treeFileName = "compressedTree.txt";
    string decompressedFileName = "decompressed.txt";

    // Load the Huffman tree data into a priority queue
    priority_queue<Node*, std::vector<Node*>, CompareNodes> pq;
    unordered_map<char, string> codes;
    Node* root = load(pq, codes);  // Read the serialized Huffman tree from the file
    generateCodes(root, "", codes);
// Find the frequency of the character in the original priority queue

    int sumResult = 0;

        for (const auto& pair : codes) { //To find the total number of bits without the padding
        char key = pair.first;
        int value1 = pair.second.length();

        // Check if the key exists in the second map
        if (freqss.find(key) != freqss.end()) {
            int value2 = freqss[key];
            int product = value1 * value2;
            sumResult += product;
        }
    }

    // Display the sum of the results
    std::cout << "Total bit results: " << sumResult << std::endl;
    bitz = sumResult;


    // Open the compressed file and the output file for decompression
    ifstream compressedFile(compressedFileName, ios::binary);
    ofstream decompressedFile(decompressedFileName);


    cout << "File decompressed successfully!" << endl;
   string binaryString =  getOrigBit();
    string decodedStr = decodeHuffman(root, binaryString);
    cout<<"Decoded string : "<<decodedStr<<endl;
    decompressedFile << decodedStr;
    compressedFile.close();
    decompressedFile.close();
    return 0;
}

