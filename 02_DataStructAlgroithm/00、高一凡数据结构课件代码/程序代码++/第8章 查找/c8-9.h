// c8-9.h Trie�����Ĵ洢�ṹ���������250ҳ
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

