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


BinaryTree root2 = NULL;




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



bool Insert(BinaryTree &root, int data)
{
	if (!root) {
		root = new BinaryTreeNode;
		root->data = data;
		root->left = NULL;
		root->right = NULL;
		return true;
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
			return false;
		}
	}
}

void CreateBST(BinaryTree &root,int size)
{
	for (int i = 0; i < size; ) {
		if (Insert(root, rand() % 100)) {
			++i;
		}
	}
}


void inOrder(BinaryTree root)
{
	if (root) {
		inOrder(root->left);
		visit(root);
		inOrder(root->right);
	}
}



int findmin(BinaryTree root)
{
	if (root == NULL)
		return 0;
	while (root->left != NULL) root = root->left;

	return root->data;
}

bool Delete(BinaryTree &root, int data)
{
	if (root == NULL) {
		cout << "Ԫ�ز����ڣ�ɾ��ʧ�ܣ�" << endl;
		return false;
	}

	if (data < root->data) {
		return Delete(root->left,data);
	}
	else if (data > root->data) {
		return Delete(root->right, data);
	}
	else {
		//�ҵ��˽ڵ�
		if (root->right == NULL && root->left == NULL) {
			delete(root);
			root = NULL;
		}
		else if (root->right != NULL ) {
			root->data = findmin(root->right);
			Delete(root->right, root->data);
		}
		else if (root->left != NULL && root->right == NULL){
			BinaryTree pChild = root->left;
			delete(root);
			root = pChild;
		}
	}
}





int inOrderFindHasLeftHasNonRigth(BinaryTree root)
{
	if (root) {
		inOrder(root->left);
		//visit(root);
		if (root->left && root->right == NULL) {
			return root->data;
		}
		inOrder(root->right);
	}

	return -1;
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

	//����BST
	cout << "����BST ���ò��뷽��" << endl;
	CreateBST(root2,25);

	cout << "��α���" << endl;
	levelOrder(root2);


	cout << "������� BST �õ� ��������" << endl;


	
	inOrder(root2);


	cout << "ɾ��BST�еļ��������" << endl;


	cout << "ɾ�������:=" << root2->data << endl;

	Delete(root2, root2->data);

	cout << "���������� �������" << endl;

	inOrder(root2);

	cout << endl;

	cout << "ɾ����С:=" << findmin(root2) << endl;

	Delete(root2, findmin(root2));

	cout << "���������� �������" << endl;

	inOrder(root2);


	int data;


	do 
	{
		data = inOrderFindHasLeftHasNonRigth(root2);
	} while (data == -1);
	

	cout << "���������� û�к��ӵĽڵ�ֵΪ ��" << data << endl;

	cout << "ɾ���õ�ֵ��" << data << endl;

	Delete(root2, data);

	cout << "���������� �������" << endl;

	inOrder(root2);





	system("pause");
}