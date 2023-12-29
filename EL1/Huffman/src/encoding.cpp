/*This file contains functions used to compress/decompress
 * files based on huffman coding.
 */

#include "encoding.h"
#include <queue>
#include <strlib.h>

struct LessThan{
    bool operator()(HuffmanNode* n1, HuffmanNode* n2){
        return *n1 < *n2;
    }
};

/*Checks how many times a given character occurs in a given file.
 * Retuns a map containing this info
 */
map<int, int> buildFrequencyTable(istream& input) {
    map<int, int> freqTable;
    int letter;
    while(!input.eof()){
        letter = input.get();
        if(letter == -1){
            letter = PSEUDO_EOF;
        }
        if(freqTable.find(letter) == freqTable.end()){
            freqTable[letter] = 1;
        }
        else{
            freqTable[letter] += 1;
        }
    }
    return freqTable;
}

//Creates a binary huffman coded tree given a frequency table
HuffmanNode* buildEncodingTree(const map<int, int> &freqTable) {
    HuffmanNode* node;
    HuffmanNode* n1;
    HuffmanNode* n2;
    int sum; 
    auto queue = priority_queue<HuffmanNode*, vector<HuffmanNode*>, LessThan>();
    for(auto it = freqTable.begin(); it != freqTable.end(); it++){
        node = new HuffmanNode(it->first, it->second);
        queue.push(node);
    }
    while(queue.size() > 1){
        n1 = queue.top();
        queue.pop();
        n2 = queue.top();
        queue.pop();
        sum = n1->count + n2->count;
        queue.push(new HuffmanNode(NOT_A_CHAR, sum, n1, n2));
    }
    node = queue.top();
    return node;
}

//Traverses the huffman tree
void traverse(HuffmanNode* node, string code, map<int,string>& map){
    if(node == nullptr){
        return;
    }
    if(node->character != NOT_A_CHAR){
        map[node->character] = code;
    }
    traverse(node->zero, code + "0", map);
    traverse(node->one, code + "1", map);
}

/*Returns a map. The key represents a character and the key contains the binary
 * representation of that charcter, given the structure of the huffman tree
 */
map<int, string> buildEncodingMap(HuffmanNode* encodingTree){
    map<int, string> encodingMap;
    traverse(encodingTree, "", encodingMap);
    return encodingMap;
}

/*Used to turn a given character into its "binary" represebtation
 * in the huffman tree
 */
void encodeData(istream& input, const map<int, string> &encodingMap, obitstream& output) {
    int letter;
    while(!input.eof()){
        letter = input.get();
        if(letter != -1){
            for(char c : encodingMap.at(letter)){
                if(c == '1'){
                    output.writeBit(1);
                }
                else{
                    output.writeBit(0);
                }
            }
        }
        else{
            for(char c : encodingMap.at(PSEUDO_EOF)){
                if(c == '1'){
                    output.writeBit(1);
                }
                else{
                    output.writeBit(0);
                }
            }
        }
    }
}

//Does the opposite of endodeData, it turns a "binary" number back to a character
void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    int code;
    bool done = false;
    HuffmanNode* temp = encodingTree;

    while(!done){
        code = input.readBit();
        if(input.fail()){
            break;
        }
        if(code == 0 && temp->zero != nullptr){
            temp = temp->zero;
        }
        else if(code == 1 && temp->one != nullptr){
            temp = temp->one;
        }
        else{
            output.put(temp->character);
            temp = encodingTree;
            if(code == 0){
                temp = temp->zero;
            }
            else{
                temp = temp->one;
            }
        }
    }
}

//Compresses a given file using a huffman tree
void compress(istream& input, obitstream& output) {
    string out = "{";
    map<int, int> map1 = buildFrequencyTable(input);
    for(auto it = map1.begin(); it != map1.end(); it++){
        if(it->first != 10){
        out += integerToString(it->first);
        }
        else{
            out += '\n';
        }
        out += ":";
        out += integerToString(it->second);
        out += ", ";
    }
    out.pop_back();
    out.pop_back();
    out += "}";
    for(int i = 0; i < out.size(); i++){
        output.put(out[i]);
    }
    input.clear();
    input.seekg(0);
    HuffmanNode* node = buildEncodingTree(map1);
    map<int, string> map2 = buildEncodingMap(node);
    encodeData(input, map2, output);
    freeTree(node);
}

//Does the opposite of compress, it decompresses a file based on the huffman structure
void decompress(ibitstream& input, ostream& output) {
    map<int, int> map1;
    string decode = "";
    string tempChar;
    string tempFreq;
    HuffmanNode* node;
    char current = input.get();
    while(current != '}'){

        decode += current;
        current = input.get();
    }
    decode = decode.substr(1, decode.size());

    while(decode.size() > 3){
        tempChar = "";
        tempFreq = "";
        while(decode.front() != ':'){
            tempChar += decode[0];
            decode = decode.substr(1, decode.size());
        }
        decode = decode.substr(1, decode.size());
        while(decode.front() != ','){
            tempFreq += decode[0];
            decode = decode.substr(1, decode.size());
        }
        decode = decode.substr(2, decode.size());
        map1[stringToInteger(tempChar)] = stringToInteger(tempFreq);
    }
    map1[PSEUDO_EOF] = 1;
    node = buildEncodingTree(map1);
    decodeData(input, node, output);
    freeTree(node);

}

//Frees all memory used by a huffman tree
void freeTree(HuffmanNode* node) {
    if(node == nullptr){
        return;
    }
    else {
        freeTree(node->one);
        freeTree(node->zero);
        delete node;
    }
}
