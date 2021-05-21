/******************************************************************************
                                 Data Structures
                            Recursibe Binary Search Tree
                                    Nir Tali
                                    27.12.18
 *****************************************************************************/


#include <stdio.h>  /* printf */

#include "utils.h"
#include "wet1/avl.h"  /* Recursive Binary Search Tree */

using namespace DS;
template <class T> void print(const T& x) { std::cout << x << std::endl; }
/*****************************************************************************/
					/* Function Declaration */
int AVLCompareFunc(const void *left, const void *right);
int AVLActionFunc(void *data, void *param);
int AVLActionFuncFailure(void *data, void *param);
void CreateDestroyTest(void);
void InsertRightRotationsTest(void);
void InsertLeftRotationsTest(void);
void InsertCombinedRotationsTest(void);
void SecondaryFuncsTest(void);
void FindForEachTest(void);
void RemoveTest(void);
void RemoveUltimateTest(void);
void RemoveUltimateTest2(void);
void RemoveUltimateTest3(void);
void inorderTest();
void nextDataTest();
/*****************************************************************************/
/*
	[x]	Create
	[x]	Destroy
	[x]	Size - when empty, when not empty
	[x]	IsEmpty - when empty, when not empty
	[x]	Insert - regular right place, rotate left , rotate right
	[x]	Height - when empty, insert, after balance, after remove root
	[x]	Remove - empty, leaf, has two sons ,has one son, ultimate with balance
	[x]	ForEach - when empty, when done without doing anything, when done with job
	[x]	Find - when empty, find regular, find node that doesn't exist
*/
/*****************************************************************************/

static int array[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

int main(void)
{
	SecondaryFuncsTest();

	FindForEachTest();

	InsertRightRotationsTest();

	InsertLeftRotationsTest();

	InsertCombinedRotationsTest();

	RemoveTest();

	RemoveUltimateTest();

	RemoveUltimateTest2();

	RemoveUltimateTest3();

	inorderTest();
	
	nextDataTest();

	return 0;
}

void InsertRightRotationsTest(void)
{
	AVL<int> tree;

	tree.insert(&array[5]);
	tree.insert(&array[4]);
	tree.insert(&array[3]);
	tree.insert(&array[2]);
	tree.insert(&array[1]);
	tree.insert(&array[0]);

	print("\n\t\t\tRight Insert: ");
	tree.print();
}

void InsertLeftRotationsTest(void)
{
	AVL<int> tree;

	tree.insert(&array[0]);
	tree.insert(&array[1]);
	tree.insert(&array[2]);
	tree.insert(&array[3]);
	tree.insert(&array[4]);
	tree.insert(&array[5]);
	tree.insert(&array[6]);
	tree.insert(&array[7]);
	tree.insert(&array[8]);
	tree.insert(&array[9]);

	print("\n\t\t\tLeft Insert: ");
	tree.print();
}

void InsertCombinedRotationsTest(void)
{
	AVL<int> tree;

	tree.insert(&array[0]);
	tree.insert(&array[2]);
	tree.insert(&array[1]);
	tree.insert(&array[5]);
	tree.insert(&array[4]);
	tree.insert(&array[3]);
	
	print("\n\t\t\tCombined Insert: ");
	
	tree.print();
}


void SecondaryFuncsTest(void)
{
	AVL<int> tree;

	TEST_INT(1, tree.isEmpty(), true, "IsEmpty when empty")
	TEST_INT(2, tree.size(), 0, "Size when empty")
	TEST_INT(3, tree.height(), 0, "Height when empty")

	tree.insert(&array[5]);
	tree.insert(&array[4]);
	tree.insert(&array[3]);
	tree.insert(&array[2]);
	tree.insert(&array[1]);
	tree.insert(&array[0]);
	tree.print();
	
	TEST_INT(4, tree.size(), 6, "Size when not empty")
	TEST_INT(5, tree.isEmpty(), false, "IsEmpty when not empty")
	TEST_INT(6, tree.height(), 3, "Height when not empty")
}

void FindForEachTest(void)
{
	AVL<int> tree;

	tree.insert(&array[5]);
	tree.insert(&array[4]);
	tree.insert(&array[3]);

	try
	{
		tree.insert(&array[4]);
	}	catch(const AVLDuplicate&)	{
		print("AVLDuplicate");
	}
}

void RemoveTest(void)
{
	AVL<int> tree;

	tree.insert(&array[5]);
	tree.insert(&array[4]);
	tree.insert(&array[3]);
	tree.insert(&array[2]);
	tree.insert(&array[1]);
	tree.insert(&array[0]);

	print("\n\n\t\t\tRemove Test1: - Before ");
	tree.print();

	tree.remove(&array[2]);
	tree.print();
	tree.remove(&array[0]);
	tree.print();

	printf("\n\n\t\t\tRemove Test1: - After ");
	tree.print();
}

void RemoveUltimateTest(void)
{
	AVL<int> tree;

	tree.insert(&array[7]);
	tree.insert(&array[0]);
	tree.insert(&array[5]);
	tree.insert(&array[9]);
	tree.insert(&array[8]);
	tree.insert(&array[2]);
	tree.insert(&array[3]);
	tree.insert(&array[4]);
	tree.insert(&array[6]);
	tree.insert(&array[1]);

	printf("\n\n\t\t\tRemove: Integrated - Before ");
	tree.print();

	tree.remove(&array[6]);
	tree.remove(&array[5]);
	tree.remove(&array[8]);
	tree.remove(&array[7]);

	printf("\n\n\t\t\tRemove: Integrated - After ");
	tree.print();
}

void RemoveUltimateTest2(void)
{
	AVL<int> tree;

	tree.insert(&array[8]);
	tree.insert(&array[3]);
	tree.insert(&array[7]);
	tree.insert(&array[6]);
	tree.insert(&array[9]);
	tree.insert(&array[4]);
	tree.insert(&array[5]);

	printf("\n\n\t\t\tRemove: have 2 sons and replaced have left son - Before ");
	tree.print();

	tree.remove(&array[7]);

	printf("\n\n\t\t\tRemove: have 2 sons and replaced have left son - After ");
	tree.print();
}

void RemoveUltimateTest3(void)
{
	AVL<int> tree;

	tree.insert(&array[0]);
	tree.insert(&array[1]);
	tree.insert(&array[2]);
	tree.insert(&array[3]);
	tree.insert(&array[4]);
	tree.insert(&array[5]);
	tree.insert(&array[6]);
	tree.insert(&array[7]);
	tree.insert(&array[8]);
	tree.insert(&array[9]);
	tree.print();
	tree.insert(&array[10]);
	tree.insert(&array[11]);
	tree.insert(&array[12]);
	tree.insert(&array[13]);

	tree.print();

	tree.remove(&array[0]);
	tree.remove(&array[1]);
	tree.remove(&array[2]);
	tree.remove(&array[3]);
	tree.remove(&array[4]);
	tree.remove(&array[5]);
	try
	{
		tree.remove(&array[14]);
	}	catch(const AVLNotFound&)	{
		print("AVLNotFound");
	}
	tree.print();
	tree.remove(&array[6]);
	tree.remove(&array[7]);
	tree.remove(&array[8]);
	tree.remove(&array[9]);
	tree.remove(&array[10]);
	tree.remove(&array[11]);
	tree.remove(&array[12]);
	tree.remove(&array[13]);
	
	printf("\n\n\t\t\tRemove ALL\n ");
	TEST_INT(9, tree.isEmpty(), true, "IsEmpty when not empty")
}

void inorderTest()
{
	AVL<int> tree;

	tree.insert(&array[7]);
	tree.insert(&array[0]);
	tree.insert(&array[5]);
	tree.insert(&array[9]);
	tree.insert(&array[8]);
	tree.insert(&array[2]);
	tree.insert(&array[3]);
	tree.insert(&array[4]);
	tree.insert(&array[6]);
	tree.insert(&array[1]);

	tree.print();

	int arr[10];
	tree.inorder(10, arr);
	TEST_ARRAY(arr,array, 10)
}

void nextDataTest()
{
	AVL<int> tree;

	tree.insert(&array[7]);
	tree.insert(&array[0]);
	tree.insert(&array[5]);
	tree.insert(&array[9]);
	tree.insert(&array[8]);
	tree.insert(&array[2]);
	tree.insert(&array[3]);
	tree.insert(&array[4]);
	tree.insert(&array[6]);
	tree.insert(&array[1]);

	for (int i = 0; i < 9; i++)
	{
		TEST_IS_TRUE(*(tree.findNext(&array[i])) == (i+1))
	}

	try	{
		tree.findNext(&array[10]);
	}	catch(const AVLNotFound&)	{
		print("AVLNotFound");
	}

	try	{
		tree.findNext(&array[9]);
	}	catch(const AVLNextNotFound&)	{
		print("AVLNextNotFound");
	}
	
	
}