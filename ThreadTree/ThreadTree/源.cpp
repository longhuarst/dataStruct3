#include <iostream>

#include <queue>

using namespace std;


typedef struct ThreadTreeNode{
	int data;

	ThreadTreeNode *l_child, *r_child;
	int l_tag, r_tag;
}ThreadTreeNode, *ThreadTree;



void visit(ThreadTree p)
{
	cout << p->data << " ";
}






void InThread(ThreadTree &p,ThreadTree &prev)
{
	if (p) {
		InThread(p->l_child, prev);

		if (p->l_child == NULL) {
			p->l_child = prev;
			p->l_tag = 1;
		}
		if (prev && prev->r_child == NULL) {
			prev->r_child = p;
			prev->r_tag = 1;
		}
		prev = p;
		InThread(p->r_child, prev);
	}

}


void InThreadCreate(ThreadTree &p) 
{
	ThreadTree prev = NULL;
	ThreadTree pt = p;
	if (pt) {
		InThread(pt,prev);
		prev->r_child = NULL;
		prev->r_tag = 1;
	}
}



ThreadTree First(ThreadTree p)
{
	if (p->l_tag) return p;
	if (p->l_child == NULL) return p;
	return First(p->l_child);

}



ThreadTree Next(ThreadTree p)
{
	if (p->r_tag) return p->r_child;

	return First(p->r_child);
}

void ThreadInOrder(ThreadTree p)
{
	for (ThreadTree pt = First(p); pt != NULL; pt = Next(pt)) {
		visit(pt);
	}
}



void InOrder(ThreadTree p)
{
	if (p) {
		InOrder(p->l_child);
		visit(p);
		InOrder(p->r_child);
	}
}



void CreateTree(ThreadTree &p,int size)
{

	queue<ThreadTree> Q;

	if (p) {
		cout << "树已存在！" << endl;
		return;
	}

	p = new ThreadTreeNode;

	p->data = 1;
	p->l_child = NULL;
	p->r_child = NULL;
	p->l_tag = 0;
	p->r_tag = 0;

	int counter = 1;

	if (size > 1) {

		Q.push(p);

		while (!Q.empty()) {

			ThreadTree pt = Q.front();
			Q.pop();

			pt->l_child = new ThreadTreeNode;
			pt->l_child->data = ++counter;
			pt->l_child->l_child = NULL;
			pt->l_child->r_child = NULL;
			pt->l_child->l_tag = 0;
			pt->l_child->r_tag = 0;

			if (counter > size) {
				break;
			}

			pt->r_child = new ThreadTreeNode;
			pt->r_child->data = ++counter;
			pt->r_child->l_child = NULL;
			pt->r_child->r_child = NULL;
			pt->r_child->l_tag = 0;
			pt->r_child->r_tag = 0;


			if (counter > size) {
				break;
			}

			Q.push(pt->l_child);
			Q.push(pt->r_child);

		}



		
	}





}


void levelOrder(ThreadTree p)
{
	queue<ThreadTree> Q;

	if (!p)
		return;

	Q.push(p);

	while (!Q.empty()) {
		ThreadTree pt = Q.front();
		Q.pop();

		visit(pt);

		if (pt->l_child) Q.push(pt->l_child);

		if (pt->r_child) Q.push(pt->r_child);
	}

}



ThreadTree root = NULL; 





int main()
{



	cout << "创建树" << endl;
	CreateTree(root,25);

	cout << "层次遍历 ";
	levelOrder(root);
	cout << endl;

	cout << "中序遍历" << endl;
	InOrder(root);
	cout << endl;





	cout << "创建二叉线索树 - 中序" << endl;
	InThreadCreate(root);
	
	cout << "线索中序遍历" << endl;
	ThreadInOrder(root);
	cout << endl;

	

		




	system("pause");

}