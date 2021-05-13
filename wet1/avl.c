/******************************************************************************
                                 Data Structures
                            Recursibe Binary Search Tree
                                    Nir Tali
                                    27.12.18
 *****************************************************************************/

#include <stdlib.h> /* malloc */
#include <stdio.h>  /* printf */
#include <assert.h> /* assert */

#include "utils.h"
#include "avl.h"  /* Recursive Binary Search Tree */

/******************************************************************************/
/*						    Typedefs										  */
typedef int(*cmp_func_t)(const void *left, const void *right);
typedef int(*action_func_t)(void *data, void *param);

/******************************************************************************/
/*							Structures  									  */
typedef struct avl_node
{	
	size_t height;
	struct avl_node *left;
	struct avl_node *right;
	void *data;

}node_t;
 
struct avl
{
	node_t *root;
	int (*cmp_func)(const void *left, const void *right);		
};

/******************************************************************************/
static void AVLFreeTreeRec(node_t *node);
static void AVLFreeNode(node_t *node);
static size_t CountRec(node_t *node);
static node_t *InsertRec(node_t *node, void *data, cmp_func_t func);
static node_t *CreateNode(node_t *place, void *data, int which_son);
static int NodeHeight(node_t *node);
static node_t *AVLBalance(node_t *node);
static int BalanceFactor(node_t *node);
static node_t *RRotate(node_t *node);
static node_t *LRotate(node_t *node);
static node_t *RemoveRec(node_t *node, void *data, cmp_func_t func);
static void DestroyNode(node_t *node);
static node_t *RightMostNode(node_t *node);
static int ForEachRec(node_t *node, action_func_t func, void *param);
static void *FindRec(cmp_func_t func, node_t *node, void *data);

/******************************************************************************/
avl_t *AVLCreate(cmp_func_t func)
{
	avl_t *tree = NULL;

	assert (func);

	tree = malloc(sizeof(avl_t));
	
	if (tree)
	{
		tree->root = NULL;
		tree->cmp_func = func;
	}

	return (tree);
}

/******************************************************************************/
void AVLDestroy(avl_t *avl)
{
	assert(avl);

	AVLFreeTreeRec(avl->root);
	avl->root = NULL;
	avl->cmp_func = NULL;

	free(avl);
	avl = NULL;
}

static void AVLFreeTreeRec(node_t *node)
{
	if (node)
	{
		AVLFreeTreeRec(node->left);
		AVLFreeTreeRec(node->right);

		AVLFreeNode(node);
	}
}

static void AVLFreeNode(node_t *node)
{
		node->left = NULL;
		node->right = NULL;
		node->data = NULL;
		free(node);
		node = NULL;
}

/******************************************************************************/
size_t AVLSize(const avl_t *avl)
{
	assert(avl);

	return (CountRec(avl->root));
}

static size_t CountRec(node_t *node)
{
	if (node == NULL)
	{
		return (0);	
	}

	return (1 + CountRec(node->left) + CountRec(node->right));
}

/******************************************************************************/
int AVLIsEmpty(const avl_t *avl)
{
	assert(avl);

	return (NULL == avl->root);	
}

/******************************************************************************/

int AVLInsert(avl_t *avl, void *data)
{
	node_t *retval = NULL;
	
	assert(avl);
	assert(data);

	if (AVLIsEmpty(avl))
	{
		avl->root = CreateNode(NULL, data, 0);
		if (!avl->root)
		{
			return (-1);
		}

		return (0);
	}

	retval = InsertRec(avl->root, data, avl->cmp_func);
	if (NULL != retval)
	{
		avl->root = retval;
	}

	return (retval == NULL);
}

static node_t *InsertRec(node_t *node, void *data, cmp_func_t func)
{
	node_t *rec_retval = NULL;
	int cmp_retval = func(data, node->data);

	/* insert to the right place */
	if ((cmp_retval > 0 && node->right == NULL) || 
		(cmp_retval < 0 && node->left == NULL))
	{
		if (NULL == (rec_retval = CreateNode(node, data, cmp_retval)))
		{
			return (NULL);
		}
	}
	/* moving to the correct son */
	else if (cmp_retval > 0)
	{
		rec_retval = InsertRec(node->right, data , func);
	}
	else if (cmp_retval < 0)
	{
		rec_retval = InsertRec(node->left, data , func);
	}
	/*	Duplicate nodes are not allowed */
	else
	{
		return (NULL);
	}
	
	/* if insert fails */
	if (NULL == rec_retval)
	{
		return (NULL);
	}

	/* attach the recursive node to the first call node */
	if (0 > func(rec_retval->data, node->data))
	{
		node->left = rec_retval;
	}
	else
	{
		node->right = rec_retval;
	}

	/* height update */
	node->height = 1 + MAX(NodeHeight(node->left), NodeHeight(node->right));

	/* balancing */
	node = AVLBalance(node);

	return (node);
}

static node_t *AVLBalance(node_t *node)
{
	int balance_fac = BalanceFactor(node);
	
	if (balance_fac > 1)
	{
		if (BalanceFactor(node->right) < 0)
		{
			node->right = RRotate(node->right);
		}
		
		return (LRotate(node));
	}

	else if (balance_fac < -1)
	{
		if (BalanceFactor(node->left) > 0)
		{
			node->left = LRotate(node->left);
		}
		
		return (RRotate(node));
	}

	return (node);
}

static int NodeHeight(node_t *node)
{
	if (node)
	{
		return (node->height);
	}

	return (0);
}

static node_t *RRotate(node_t *node)
{
	node_t *new_head = node->left;

	node->left = new_head->right;
	new_head->right = node;

	node->height = 1 + MAX(NodeHeight(node->left), NodeHeight(node->right));
	new_head->height = 1 + MAX(NodeHeight(new_head->left), NodeHeight(new_head->right));

	return (new_head);
}

static node_t *LRotate(node_t *node)
{
	node_t *new_head = node->right;
	
	node->right = new_head->left;
	new_head->left = node;

	node->height = 1 + MAX(NodeHeight(node->left), NodeHeight(node->right));
	new_head->height = 1 + 
				MAX(NodeHeight(new_head->left), NodeHeight(new_head->right));

	return (new_head);
}

/* return <0 to balance left/=0 if is balanced/>0 to balance right */
static int BalanceFactor(node_t *node)
{
	return (NodeHeight(node->right) - NodeHeight(node->left));
}

/*  place is the node who gets a new son
	which_son<0 = node->left / which_son==0 = node / which_son>0 = node->right*/
static node_t *CreateNode(node_t *place, void *data, int which_son)
{
	node_t *node = malloc(sizeof(node_t));
	if (!node)
	{
		return (NULL);
	}

	node->data = data;
	node->height = 1;
	node->right = NULL;
	node->left = NULL;

	if (which_son > 0)
	{
		place->right = node;
	}
	else if (which_son < 0)
	{
		place->left = node;
	}

	return (node);
}

/******************************************************************************/
size_t AVLHeight(avl_t *avl)
{
	assert(avl);

	if (avl->root)
	{
		return (avl->root->height);	
	}

	return (0);
}

/******************************************************************************/

void AVLRemove(avl_t *avl, void *data)
{
	assert(avl);
	assert(data);
	
	avl->root = RemoveRec(avl->root, data, avl->cmp_func);
}

static node_t *RemoveRec(node_t *node, void *data, cmp_func_t func)
{
	node_t *replacer = NULL;
	int cmp_retval = 0;

	if (NULL == node)
	{
		return (NULL);
	}

	cmp_retval = func(data, node->data);
	/* moving to the correct son */
	if (cmp_retval > 0)
	{
		node->right = RemoveRec(node->right, data , func);
	}
	else if (cmp_retval < 0)
	{
		node->left = RemoveRec(node->left, data , func);
	}
	/* Find the node to be removed */
	else
	{
		/* one son or no sons */	
		if (!node->left || !node->right)
		{
			replacer = (node->left) ? (node->left) : (node->right);
		
			if (replacer)
			{
				node->data = replacer->data;
				if (replacer == node->left)
				{
					node->left = NULL; 
				}
				else
				{
					node->right = NULL;
				}

				DestroyNode(replacer);
				replacer = NULL;
			}
			else
			{
				DestroyNode(node);
				node = NULL;
			}
		}
		/* two sons */
		else
		{
			replacer = RightMostNode(node->left);

			node->data = replacer->data;
			node->left = RemoveRec(node->left, node->data, func);
		}
	}

	if (NULL == node)
	{
		return (NULL);
	} 
    

    /* Height Update */
	node->height = 1 + MAX(NodeHeight(node->left), NodeHeight(node->right));


	/* balancing */
	node = AVLBalance(node);

    return (node);
}

static void DestroyNode(node_t *node)
{
	node->right = NULL;
	node->left = NULL;
	node->data = NULL;

	free(node);
	node = NULL;
}

static node_t *RightMostNode(node_t *node)
{
	node_t* retval = node;

	if (node->right)
	{
		retval = RightMostNode(node->right);
	}

	return (retval);
}
/******************************************************************************/
int AVLForEach(avl_t *avl, action_func_t func, void *param)
{
	assert(avl);
	assert(func);

	return (ForEachRec(avl->root, func, param));
}

static int ForEachRec(node_t *node, action_func_t func, void *param)
{
	int retval_rec = 0;

	if (node)
	{	
		retval_rec = ForEachRec(node->left, func, param);
		
		if (0 != func(node->data,param) || retval_rec != 0)
		{
			return (-1);
		}
	
		retval_rec = ForEachRec(node->right, func, param);
	}

	return (retval_rec);
}

/******************************************************************************/
void *AVLFind(const avl_t *avl, void *data)
{
	assert(avl);

	return ( FindRec(avl->cmp_func, avl->root, data));
}

static void *FindRec(cmp_func_t func, node_t *node, void *data)
{
	int cmp_retval = 0;
	void *data_retval = NULL;

	if (NULL == node)
	{
		return (NULL);
	}

	cmp_retval = func(data, node->data);

	if (cmp_retval > 0)
	{
		data_retval = FindRec(func,node->right,data);
	}

	else if (cmp_retval < 0)
	{
		data_retval = FindRec(func,node->left,data);		
	}
	else
	{
		data_retval = node->data;
	}

	return (data_retval);
}
/******************************************************************************/

#ifndef NDEBUG
/* ========================================================================= */
/*                                                                 PrintTree */
static void AVLPrintNode(const node_t *node, size_t depth)
{
    size_t i = 0;
    for (i = 0; i < depth; ++i)
    {
        printf("│  ");
    }
    if (NULL != node)
    {
        printf("├╴ %p -> %d\n", (void*) node, *(int*)node->data);
        AVLPrintNode(node->left, depth + 1);
        AVLPrintNode(node->right, depth + 1);
    } else {
        printf("├╴ X\n");
    }
}

void AVLPrint(const avl_t *avl)
{
    assert(NULL != avl);

    if (NULL != avl->root)
    {
    	printf("\nStart Print:\n");
        printf("%p -> %d\n", (void*)avl->root,
                *(int*)avl->root->data);
        AVLPrintNode(avl->root->left, 0);
        AVLPrintNode(avl->root->right, 0);
    }
}
#endif /* NDEBUG */
