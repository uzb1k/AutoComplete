#include "Correction.h"

TrieNode::TrieNode() : isEndOfWord(false) {
	for (int i = 0; i < ALPHABET_SIZE; ++i) {
		childrens[i] = nullptr;
	}
}

Trie::Trie() {
	root = getNewNode();
}
void Trie::SetDictionary() {
	ifstream in("popular.txt");
	if (in.is_open()) {

		while (getline(in, line)) {
			dictionary.push_back(line);

		}
		for (int i = 0; i < dictionary.size(); ++i) {
			insert(dictionary[i]);
		}

	}
	in.close();
}

TrieNode* Trie::getNewNode(void)
{

	struct TrieNode* pNode = new TrieNode;

	pNode->isEndOfWord = false;

	for (int i = 0; i < ALPHABET_SIZE; i++)
		pNode->childrens[i] = nullptr;

	return pNode;
}

TrieNode* Trie::search(string& prefix) {
	TrieNode* node = root;

	for (int i = 0; i < prefix.length(); ++i) {
		int index = prefix[i] - 'a';

		if (!node->childrens[index]) {
			return nullptr;
		}

		node = node->childrens[index];
	}

	return node;
}

void Trie::insert(string key) {
	TrieNode* node = root;

	for (int i = 0; i < key.length(); ++i) {
		int index = key[i] - 'a';
		if (!node->childrens[index]) {
			node->childrens[index] = getNewNode();
		}

		node = node->childrens[index];
	}

	node->isEndOfWord = true;
}

string Trie::indexToString(int index) {

	return string(1, 'a' + index);
}

void Trie::collectWords(TrieNode* node, string& prefix, vector<std::string>& result) {
	if (node->isEndOfWord) {
		result.push_back(prefix);
	}

	for (int i = 0; i < ALPHABET_SIZE; ++i) {
		if (node->childrens[i]) {
			string newPrefix = prefix + char('a' + i);
			collectWords(node->childrens[i], newPrefix, result);
		}
	}
}

void Trie::autoComplete(string& prefix) {
	vector <string> result;

	TrieNode* node = search(prefix);

	if (node) {
		collectWords(node, prefix, result);
		cout << "Maybe you meant: " << endl;
	}

	else {
		cout << "No results";
	}
	
	for (int i = 0; i < result.size(); ++i) {
		cout << result[i] << endl;
	}
}

bool Trie::checkTrieIntegrity(TrieNode* node) {
	// Базовый случай: если текущий узел пуст, возвращаем true
	if (node == nullptr) {
		return true;
	}

	// Проверяем каждый дочерний указатель
	for (int i = 0; i < ALPHABET_SIZE; ++i) {
		if (node->childrens[i] != nullptr) {
			// Рекурсивно проверяем дочерний узел
			if (!checkTrieIntegrity(node->childrens[i])) {
				return false;
			}
		}
	}

	// Если прошли все проверки, возвращаем true
	return true;
}