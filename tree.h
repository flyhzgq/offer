#ifndef _TREE_H_
#define _TREE_H_

struct tree
{
	int value;
	struct tree *left;
	struct tree *right;
};

#ifdef TREE_COMPARE_TEST
#define TEST_MAX 128
extern int tree_test[TEST_MAX];
extern int tree_test_r[TEST_MAX];
extern int tree_index;
extern int tree_index_r;
#endif

struct tree * tree_init(int *v, int size);
struct tree * tree_insert(struct tree *t, int value);
void tree_deinit(struct tree * t);

void tree_pretraveres_resursion(struct tree *t);
void tree_intraveres_resursion(struct tree *t);
void tree_posttraveres_resursion(struct tree *t);
void tree_pretraveres_loop(struct tree *t);
void tree_intraveres_loop(struct tree *t);
void tree_posttraveres_loop(struct tree *t);
void tree_leveltraveres(struct tree *t);

#endif

