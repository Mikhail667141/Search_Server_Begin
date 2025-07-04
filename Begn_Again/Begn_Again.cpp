﻿#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

string ReadLine() {
    string s;
    getline(cin, s);
    return s;
}

int ReadLineWithNumber() {
    int result = 0;
    cin >> result;
    ReadLine();
    return result;
}

vector<string> SplitIntoWords(const string& text) {
    vector<string> words;
    string word;
    for (const char c : text) {
        if (c == ' ') {
            if (!word.empty()) {
                words.push_back(word);
                word.clear();
            }
        }
        else {
            word += c;
        }
    }
    if (!word.empty()) {
        words.push_back(word);
    }

    return words;
}

set<string> ParseStopWords(const string& text) {
    set<string> stop_words;
    for (const string& word : SplitIntoWords(text)) {
        stop_words.insert(word);
    }
    return stop_words;
}

vector<string> SplitIntoWordsNoStop(const string& text, const set<string>& stop_words) {
    vector<string> words;
    for (const string& word : SplitIntoWords(text)) {
        if (stop_words.count(word) == 0) {
            words.push_back(word);
        }
    }
    return words;
}
///////////////////////////////
void AddDocument(vector<pair<int, vector<string>>>& documents, const set<string>& stop_words, int document_id, const string& document) {

    const vector<string> words = SplitIntoWordsNoStop(document, stop_words);
    documents.push_back({ document_id,words });
}

set<string> ParseQuery(const string& text, const set<string>& stop_words) {
    set<string> query_words;
    for (const string& word : SplitIntoWordsNoStop(text, stop_words)) {
        query_words.insert(word);
    }
    return query_words;
}
////////////////////////////
int MatchDocument(const pair<int, vector<string>>& content, const set<string>& query_words) {
    int relevanse = 0;
    for (const auto& word : content.second) {
        
        if (query_words.count(word)){

            ++relevanse;
            
        }
       }
    return relevanse;
}

////////////////////////////////
// Для каждого найденного документа возвращает его id
vector<pair<int, int>> FindDocuments(const vector<pair<int, vector<string>>>& documents,
    const set<string>& stop_words, const string& query) {

    const set<string> query_words = ParseQuery(query, stop_words);
    vector<pair<int,int>> matched_documents;
    
    for (const auto& document : documents) {
        int relevance = MatchDocument(document, query_words);
        if (relevance > 0) {
            matched_documents.push_back({ document.first, relevance });
        }
    }
    return matched_documents;
}

 
 
 


int main() {
    const string stop_words_joined = ReadLine();
    const set<string> stop_words = ParseStopWords(stop_words_joined);

    // Считываем документы
    vector<pair<int, vector<string>>> documents;
    const int document_count = ReadLineWithNumber();
    for (int document_id = 0; document_id < document_count; ++document_id) {
        AddDocument(documents, stop_words, document_id, ReadLine());
    }

    const string query = ReadLine();
    // Выводим результаты поиска по запросу query
    for (auto [document_id, relevance] : FindDocuments(documents, stop_words, query)) {
        cout << "{ document_id = "s << document_id << ", relevance = "s << relevance << " }"s
            << endl;
    }
}