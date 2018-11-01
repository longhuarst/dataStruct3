#include <iostream>

#include <queue>

#include <stack>


using namespace std;



typedef struct BinaryTreeNode{
	int data;
	struct BinaryTreeNode *left, *right;
}BinaryTreeNode, *BinaryTree;



void visit(BinaryTree p)
{
	cout << p->data << " ";
}


void preOrder(BinaryTree p)
{
	if (p) {
		visit(p);
		preOrder(p->left);
		preOrder(p->right);
	}
	
}



void inOrder(BinaryTree p)
{
	if (p) {
		inOrder(p->left);
		visit(p);
		inOrder(p->right);
	}
}



void postOrder(BinaryTree p)
{
	if (p) {
		postOrder(p->left);
		postOrder(p->right);
		visit(p);
	}
}

void levelOrder(BinaryTree p)
{
	queue<BinaryTree> Q;

	if (!p) return;

	Q.push(p);

	while (!Q.empty()) {
		BinaryTree pTemp = Q.front();
		visit(pTemp);
		Q.pop();
		if (pTemp->left != NULL) Q.push(pTemp->left);
		if (pTemp->right != NULL) Q.push(pTemp->right);
	}

}




//先序遍历[非递归]
void preOrderNonRecursive(BinaryTree p)
{
	stack<BinaryTree> stk;

	while (p || !stk.empty())
	{
		if (p) {
			visit(p);
			stk.push(p);
			p = p->left;
		}
		else {
			p = stk.top();
			stk.pop();
			p = p->right;
		}
	}
}








//中序遍历[非递归]
void inOrderNonRecursive(BinaryTree p)
{
	stack<BinaryTree> stk;

	while (p || !stk.empty())
	{
		if (p) {
			
			stk.push(p);
			p = p->left;
		}
		else {
			p = stk.top();
			visit(p);
			stk.pop();
			p = p->right;
		}
	}
}







//后序遍历[非递归]

void postOrderNonRecursive(BinaryTree p)
{

	stack<BinaryTree> stk;

	if (!p) return;

	stk.push(p);

	BinaryTree pLast = NULL;

	while (!stk.empty()) {
		
		p = stk.top();
		
		if (((p->right == NULL) && (p->left == NULL)) || ((pLast != NULL)&&(p->left == pLast || p->right == pLast))){
			visit(p);
			stk.pop();
			pLast = p;
		}
		else {
			if (p->right) stk.push(p->right);
			if (p->left) stk.push(p->left);
		}
		
	}
}




































//创建树

void createTree(BinaryTree &p,int size)
{
	queue<BinaryTree> Q;
	
	if (!p && size > 0) {
		
		//创建第一个节点
		p = new BinaryTreeNode;//
		p->data = 1;
		p->left = NULL;
		p->right = NULL;

		Q.push(p);
		//创建第二个节点

		int counter = 1;

		if (size > 1) {
			while (!Q.empty()) {
				BinaryTree pTemp = Q.front();
				Q.pop();

				pTemp->left = new BinaryTreeNode;
				pTemp->left->data = ++counter;
				pTemp->left->left = NULL;
				pTemp->left->right = NULL;

				if (counter >= size)
					break;

				pTemp->right = new BinaryTreeNode;
				pTemp->right->data = ++counter;
				pTemp->right->left = NULL;
				pTemp->right->right = NULL;

				if (counter >= size)
					break;

				Q.push(pTemp->left);
				Q.push(pTemp->right);

			}
		
		}
	}
	else {
		cout << "树已存在，无法创建" << endl;
	}
}





BinaryTree root = NULL;




int main()
{


	cout << "先序遍历 - 递归" << endl;


	createTree(root,25);


	preOrder(root);
	cout << endl;
	preOrderNonRecursive(root);
	cout << endl;




	inOrder(root);
	cout << endl;
	inOrderNonRecursive(root);
	cout << endl;

	
	postOrder(root);
	cout << endl;
	postOrderNonRecursive(root);
	cout << endl;



	cout << "===================" << endl;



	cout << endl;
	levelOrder(root);



	system("pause");
	
}







