#include <iostream>

#include <queue>

using namespace std;






typedef struct BinaryTreeNode{
	int data;
	struct BinaryTreeNode *left, *right;
}BinaryTreeNode, *BinaryTree;










//��α���������  ע�� ��������� ���������� ֻ��Ϊ�˲���  ֮���ö����������Ĳ��������� ����������

void CreateTree(BinaryTree &root, int size)
{

	if (root != NULL) {
		cout << "���Ѵ��ڣ�" << endl;
	}
	else {
		
		queue<BinaryTree> Q;

		root = new BinaryTreeNode;
		root->data = 1;
		root->left = NULL;
		root->right = NULL;

		Q.push(root);
		
		int counter = 1;

		if (size <= 1)
			return;

		while (!Q.empty()){
		
			BinaryTree p = Q.front();
			Q.pop();

			p->left = new BinaryTreeNode;
			p->left->data = ++counter;
			p->left->left = NULL;
			p->left->right = NULL;

			if (counter >= size)
				return;

			p->right = new BinaryTreeNode;
			p->right->data = ++counter;
			p->right->left = NULL;
			p->right->right = NULL;

			if (counter >= size)
				return;

			Q.push(p->left);
			Q.push(p->right);
		}

	}
	
}


void visit(BinaryTree root)
{
	cout << root->data << " " ;
}






//��α���
void levelOrder(BinaryTree root)
{

	if (root == NULL)
		return;
	queue<BinaryTree> Q;
	Q.push(root);

	while (!Q.empty()) {
		BinaryTree p = Q.front();
		Q.pop();
		visit(p);
		if (p->left) Q.push(p->left);
		if (p->right) Q.push(p->right);
	}
}



BinaryTree root = NULL;




BinaryTree Search(BinaryTree root,int data)
{
	if (!root) {
		return NULL;
	}

	if (data < root->data) {
		return Search(root->left, data);
	}
	else if (data > root->data) {
		return Search(root->right, data);
	}
	else {
		return root;
	}
}



void Insert(BinaryTree &root, int data)
{
	if (!root) {
		root = new BinaryTreeNode;
		root->data = data;
		root->left = NULL;
		root->right = NULL;
	}
	else {
		if (data < root->data) {
			Insert(root->left, data);
		}
		else if (data > root->data) {
			Insert(root->right, data);
		}
		else {
			cout << "�������ظ���Ԫ�أ�" << endl;
		}
	}

}

int main() 
{


	cout << "��α���������  ע�� ��������� ���������� ֻ��Ϊ�˲���  ֮���ö����������Ĳ��������� ����������" << endl;
	CreateTree(root,25);



	cout << "��α���" << endl;
	levelOrder(root);


	BinaryTree p = Search(root,15);

	cout << "����15���= " << p->data;
	


	p = Search(root, 26);

	if (p) {
		cout << "����26���= " << p->data;
	}else{
		cout << "����26���= δ�ҵ���" << endl;
	}
	


	Insert(root, 26);

	Insert(root, 26);

	
	levelOrder(root);




	system("pause");
}