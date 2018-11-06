#include <iostream>
#include <algorithm>




using namespace std;



typedef struct ASTNode{
	int data;
	struct ASTNode *left, *right;
	int height;//�߶�
}ASTNode,*AST;



int Height(AST root)
{
	if (root) return root->height;
	else return -1;
}


void SingleRotateRight(AST &root)
{
	AST p = root;

	root = root->left;
	p->left = root->right;
	root->right = p;
	p->height = max(Height(p->left), Height(p->right)) + 1;
	root->height = max(Height(root->left), Height(root->right)) + 1;
}

void SingleRotateLeft(AST &root)
{
	AST p = root;

	root = root->right;
	p->right = root->left;
	root->left = p;

	p->height = max(Height(p->left), Height(p->right)) + 1;
	root->height = max(Height(root->left), Height(root->right)) + 1;
}


void DoubleRotateLeftRight(AST &root)
{
	SingleRotateLeft(root->left);
	SingleRotateRight(root);
}

void DoubleRotateRightLeft(AST &root)
{
	SingleRotateRight(root->right);
	SingleRotateLeft(root);
}

bool Insert(AST &root, int data)
{
	if (root == NULL) {
		root = new ASTNode;
		root->data = data;
		root->left = NULL;
		root->right = NULL;
		root->height = max(Height(root->left), Height(root->right)) + 1;
		return true;
	}
	else {
		
		if (data < root->data) {
			bool res = Insert(root->left, data);
			root->height = max(Height(root->left),Height(root->right)) + 1;//�������ĸ߶�
			if (abs(Height(root->left) - Height(root->right)) >= 2) {
				//ʧȥƽ�� ��X
				if (Height(root->left->left) > Height(root->left->right)) {
					//����
					SingleRotateRight(root);
				}
				else {
					DoubleRotateLeftRight(root);
				}
			}
			return res;
		}
		else if (data > root->data) {
			bool res = Insert(root->right, data);
			root->height = max(Height(root->left), Height(root->right)) + 1;//�������ĸ߶�
			if (abs(Height(root->left) - Height(root->right)) >= 2) {
				//ʧȥƽ�� ��X
				if (Height(root->right->left) < Height(root->right->right)) {
					SingleRotateLeft(root);
				}
				else {
					DoubleRotateRightLeft(root);
				}
			}
			return res;
		}
		else {
			cout << "�����ֵ�Ѿ����ڣ�" << endl;
			return false;//�����ֵ�Ѿ����ڣ�
		}
	}
}



void CreateAST(AST &root, int size)
{
	for (int i = 0; i < size;) {
		int value = rand() % 100;
		cout << value << " ";
		if (Insert(root, value)) {
			
			++i;
		}
	}
}


void visit(AST root) 
{
	cout << root->data << " ";
}

void inOrder(AST root)
{
	if (root) {
		inOrder(root->left);
		visit(root);
		inOrder(root->right);
	}
}


AST find(AST root, int value)
{
	if (root == NULL) {
		cout << "û�ҵ�" << endl;
		return NULL;
	}
	if (value < root->data) {
		return find(root->left, value);
	}
	else if (value > root->data) {
		return find(root->right, value);
	}
	else {
		return root;
	}
}


int findmin(AST root) 
{
	while (root->left) {
		root = root->left;
	}
	return root->data;
}


bool Delete(AST &root, int value)
{
	if (root == NULL) {
		cout << "û�ҵ����޷�ɾ��" << endl;
		return false;
	}
	if (value < root->data) {
		bool res = Delete(root->left, value);
		if (abs(Height(root->left) - Height(root->right)) >= 2) {
			//����ƽ��
			if (Height(root->right->left) < Height(root->right->right)) {
				SingleRotateLeft(root);
			}
			else {
				DoubleRotateRightLeft(root);
			}
		}
		root->height = max(root->left->height, root->right->height) + 1;
		return res;
	}
	else if (value > root->data) {
		bool res = Delete(root->right, value);
		if (abs(Height(root->left) - Height(root->right)) >= 2) {
			//����ƽ��
			if (Height(root->left->left) > Height(root->left->right)) {
				SingleRotateRight(root);
			}
			else {
				DoubleRotateLeftRight(root);
			}
		}
		root->height = max(root->left->height, root->right->height) + 1;
		return res;
	}
	else {
		//ƥ�䵽������
		if (root->left == NULL && root->right == NULL) {
			delete(root);
			root = NULL;
			return true;
		}
		else if (root->left != NULL && root->right != NULL) {
			bool res;
			int value = findmin(root->right);
			root->data = value;
			Delete(root->right, value);
			root->height = max(root->left->height, root->right->height) + 1;
			return true;
		}
		else if (root->left){
			AST p = root->left;
			delete(root);
			root = p;
			return true;
		}
		else {
			AST p = root->right;
			delete(root);
			root = p;
			return true;
		}
	}
}


AST root = NULL;

int main()
{

	

	cout << "���ò���ķ����� ����ƽ������������" << endl;

	CreateAST(root, 25);




	cout << "������� ƽ������������ ��������Ƿ�����" << endl;

	inOrder(root);

	cout << endl;


	find(root, 0);



	inOrder(root);
	Delete(root,0);
	cout << "������� " << endl;
	inOrder(root);



	Delete(root, 4);
	cout << "������� " << endl;


	inOrder(root);

	system("pause");
}
