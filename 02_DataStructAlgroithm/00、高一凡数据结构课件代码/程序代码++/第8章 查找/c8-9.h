// c8-9.h Trie键树的存储结构。在严书第250页
typedef struct TrieNode 
{ NodeKind kind;
  union
  { struct
    { KeyType K;
      Record *infoptr;
    }lf; 
    struct
    { TrieNode *ptr[LENGTH]; 
      int num; 
    }bh; 
  };
}TrieNode, *TrieTree;

