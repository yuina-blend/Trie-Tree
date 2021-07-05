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

void print_tree_2(trie_tree *root) {
    for (int i = 0; i < 26; i++) {
        if (root->node[i] != NULL) {
            printf("%c ", char(97 + i));
        }
    }
    printf("\n");
    for (int i = 0; i < 26; i++)
    {
        if (root->node[i] != NULL)
        {
            print_tree_2(root->node[i]);
        }
    }
}

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
}