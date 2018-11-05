#include <iostream>

#include <queue>

using namespace std;


typedef struct ThreadTreeNode{
	int data;

	ThreadTreeNode *l_child, *r_child;
	int l_tag, r_tag;
	ThreadTreeNode *parent;
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



void PreThread(ThreadTree &p, ThreadTree &prev)
{
	if (p) {


		if (p->l_child == NULL) {
			p->l_child = prev;
			p->l_tag = 1;
		}
		if (prev != NULL && prev->r_child == NULL) {
			prev->r_child = p;
			prev->r_tag = 1;
		}
		prev = p;
		if (p->l_tag == 0) PreThread(p->l_child,prev);
		if (p->r_tag == 0) PreThread(p->r_child,prev);
	}
}


void PreThreadCreate(ThreadTree &p)
{
	ThreadTree prev = NULL;

	if (p) {
		PreThread(p, prev);
		prev->r_child = NULL;
		prev->r_tag = 1;
	}
}




void ThreadPreOrder(ThreadTree p)
{
	
	while (p) {
		
		visit(p);

		if (p->l_tag == 0)
			p = p->l_child;
		else
			p = p->r_child;
	}
}

void PreOrder(ThreadTree p) 
{
	if (p) {
		visit(p);
		PreOrder(p->l_child);
		PreOrder(p->r_child);
	}
}





void PostThread(ThreadTree &p, ThreadTree &prev, ThreadTree parent)
{
	if (p) {
		p->parent = parent;
		PostThread(p->l_child,prev, p);
		PostThread(p->r_child,prev, p);
		if (p->l_child == NULL) {
			p->l_child = prev;
			p->l_tag = 1;
		}
		if (prev != NULL && prev->r_child == NULL) {
			prev->r_child = p;
			prev->r_tag = 1;
		}
		prev = p;
	}
}


void PostThreadCreate(ThreadTree &p)
{
	ThreadTree prev = NULL;
	if (p) {
		PostThread(p, prev, NULL);
	}
}






//后序遍历
void ThreadPostOrder(ThreadTree p, ThreadTree prev)
{
	
	while (1) {
		if (!p)
			return;

		if (p->l_child != prev && p->r_child != prev) {
				while (p->l_tag != 1) p = p->l_child;
		}
		visit(p);
		
		if (p->r_child != prev) {
			prev = p;
			p = p->r_child;
		}
		else {
			prev = p;
			if (p->parent == NULL)
				return;
			if (p == p->parent->l_child) {
				p = p->parent->r_child;
			}else
			p = p->parent;
		}
	}	
}











void PostOrder(ThreadTree p)
{
	if (p) {
		PostOrder(p->l_child);
		PostOrder(p->r_child);
		visit(p);
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
ThreadTree root2 = NULL;
ThreadTree root3 = NULL;



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

	

		

	cout << "==============================" << endl;





	cout << "创建树" << endl;
	CreateTree(root2, 25);

	cout << "层次遍历 ";
	levelOrder(root2);
	cout << endl;

	cout << "先序遍历" << endl;
	PreOrder(root2);
	cout << endl;





	cout << "创建二叉线索树 - 中序" << endl;
	PreThreadCreate(root2);

	cout << "线索中序遍历" << endl;
	ThreadPreOrder(root2);
	cout << endl;








	cout << "==============================" << endl;





	cout << "创建树" << endl;
	CreateTree(root3, 25);

	cout << "层次遍历 ";
	levelOrder(root3);
	cout << endl;

	cout << "先序遍历" << endl;
	PostOrder(root3);
	cout << endl;





	cout << "创建二叉线索树 - 后序" << endl;
	PostThreadCreate(root3);

	cout << "线索后序遍历" << endl;
	ThreadPostOrder(root3,NULL);
	cout << endl;


















	system("pause");

}