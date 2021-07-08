#include <stdio.h>
#include <stdlib.h>
#include <iostream>

typedef struct trie_tree {
    struct trie_tree *node[26];
    bool eof;
} trie_node;

trie_node *malloc_node() {
    trie_node *new_node;
    new_node = (trie_node *)malloc(sizeof(trie_node));

    for (int i = 0; i < 26; i++) {
        // printf("bb");
        new_node->node[i] = NULL;
        new_node->eof = false;
    }

    return new_node;
}

trie_node *add_node(trie_node *root, char *word, int word_size) {
    trie_node *tmp;
    if (root == NULL) {
        root = malloc_node();
        if (root == NULL) {
            printf("malloc erroe\n");
            return NULL;
        }
        return root;
    }
    tmp = root;
    for (int i = 0; i < word_size; i++) {
        if (tmp->node[int(word[i]) - 97] == NULL) {
            // printf("aa");
            tmp->node[int(word[i]) - 97] = malloc_node();
        }
        tmp = tmp->node[int(word[i]) - 97];
    }
    tmp->eof = true;
    return root;
}

bool search_word(trie_node *root, char *word, int word_size) {
    trie_node *tmp = root;
    for (int i = 0; i < word_size; i++) {
        if (tmp->node[int(word[i]) - 97] == NULL) {
            // printf("not found\n");
            return false;
        }
        else {
            tmp = tmp->node[int(word[i]) - 97];
        }
    }
    if (tmp->eof) {
        // printf("find %s\n", word);
        return true;
    }
    else {
        // printf("not found\n");
        return false;
    }
}

void print_tree(trie_node *root, std::string s, int depth) {
    for (int i = 0; i < 26; i++) {
        if (root->node[i] != NULL) {
            if (root->node[i]->eof) {
            std::cout << s;
            }
            s.push_back(char(97 + i));
            if (root->node[i]->eof)
            {
            printf("%c\n", char(97 + i));
            }
            // printf("%s", s);
            print_tree(root->node[i], s, depth++);
            s.pop_back();
        }
    }
    return;
}

trie_node *delete_word(trie_node *root, char *word, int word_size, int depth) {
    if (depth == 0 && !search_word(root, word, word_size)) {
        printf("not found %s\n", word);
        return NULL;
    }
    // trie_node *tmp = root;
    if (word_size != depth) {
        root->node[int(word[depth]) - 97] = delete_word(root->node[int(word[depth]) - 97], word, word_size, depth + 1);
    }
    for (int i = 0; i < 26; i++) {
        if (root->node[int(word[i]) -97] != NULL) {
            root->eof = false;
            return root;
        }
    }
    return NULL;
}

// void print_tree_2(trie_tree *root) {
//     for (int i = 0; i < 26; i++) {
//         if (root->node[i] != NULL) {
//             printf("%c ", char(97 + i));
//         }
//     }
//     printf("\n");
//     for (int i = 0; i < 26; i++)
//     {
//         if (root->node[i] != NULL)
//         {
//             print_tree_2(root->node[i]);
//         }
//     }
// }

int main() {
    // char *word = "a";
    // printf("%d", int(word[0]));
    //car, card, try, tried, catを挿入する
    trie_node *root = malloc_node();
    root = add_node(root, "car", 3);
    root = add_node(root, "card", 4);
    root = add_node(root, "try", 3);
    root = add_node(root, "tried", 5);
    root = add_node(root, "cat", 3);
    // root = add_node(root, "a");
    // printf("%p", root->node);
    print_tree(root, "", 0);
    // print_tree_2(root);
    //card, carp, trieを検索する
    search_word(root, "card", 4);
    search_word(root, "carp", 4);
    search_word(root, "trie", 4);
    // search_word(root, "cat", 3);
    delete_word(root, "car", 3, 0);
    delete_word(root, "try", 3, 0);
    print_tree(root, "", 0);
    delete_word(root, "dog", 3, 0);
}