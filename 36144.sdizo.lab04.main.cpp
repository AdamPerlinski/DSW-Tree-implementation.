//SDIZO IS1 213B LAB04
//Adam Perliñski
//foxtheowner@gmail.com
// ConsoleApplication1.cpp : Defines the entry point for the console application.
//klucz lewego potomka < klucz przodka < klucz prawego potomka
//


#include "stdafx.h"
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <time.h>
#include <ctime>
#include <math.h>
#include <algorithm>
#include <cstdlib>
#pragma warning(disable:4996)
using namespace std;
struct BST {
	int klucz;
	char tab[100];
	BST* left;
	BST* right;
};
void inicjacja(BST*& a) {
	int i = 0;
	a = new BST;
	a->klucz = NULL;
	a->right = NULL;
	a->left = NULL;
	for (i; i < 100; i++) {
		a->tab[i] = NULL;
	}
}
void wstawianie(BST*& a, int klucz) {
	BST* etemp = a;
	BST* temp = a;

	if (a->left == NULL && a->right == NULL && a->klucz == NULL) {
		a->right = NULL;
		a->left = NULL;
		a->klucz = klucz;
		int i = 0;
		for (i; i < 100; i++) {
			a->tab[i] = (65 + rand() % (25 - 1 + 1));
		}
		return;
	}
	else {
		BST* nowy = new BST;
		while (temp != NULL) {
			if (klucz == temp->klucz) { cout << "\nError, wartosc sie powtarza" << endl; return; }
			if (klucz < temp->klucz) {
				etemp = temp;
				temp = temp->left;
			}
			else
			{
				etemp = temp;
				temp = temp->right;
			}
		}
		nowy->right = NULL;
		nowy->left = NULL;
		nowy->klucz = klucz;
		int i = 0;
		for (i; i < 100; i++) {
			nowy->tab[i] = (65 + rand() % (25 - 1 + 1));
			if (klucz < etemp->klucz) {
				etemp->left = nowy;
			}
			else {
				etemp->right = nowy;
			}
		}


	}

}
void xnowych(BST*& a, int ile) {
	int klucz, i;
	i = 0;
	for (i; i < ile; i++) {
		klucz = rand() % (19001 - 11) + 11;
		wstawianie(a, klucz);
	}
}
void wyszukiwanie(BST*a, int klucz) {
	BST* etemp = a;
	BST* temp = a;
	while (temp != NULL) {
		if (klucz == temp->klucz) { cout << "Znaleziono klucz o wartosci :  " << temp->klucz << endl; return; }
		if (klucz < temp->klucz) {
			etemp = temp;
			temp = temp->left;
		}
		else
		{
			etemp = temp;
			temp = temp->right;
		}
	}
	cout << "Nie znaleziono klucza" << endl;
}


void usuwanie(BST*& a, int klucz) {
	BST* etemp = a;
	BST* temp = a;
	while (temp != NULL) {
		if (klucz == temp->klucz) {
			if (temp->right == NULL && temp->left == NULL) {
				if (temp == a) {
					cout << "Usuwamy ca³e drzewo!" << endl;
					delete temp;
					return;
				}

				if (etemp->right == temp) {
					etemp->right = NULL;

				}
				else {
					etemp->left = NULL;
				}
				delete temp;
				return;
			}
			if (temp == a && (temp->right != NULL || temp->left != NULL)) {
				if (temp->right != NULL && temp->left != NULL) {
					BST* preparent = temp;
					BST* child = temp->left;
					while (child->right != NULL) {
						preparent = child;
						child = child->right;
					}
					child->right = temp->right;
					preparent->right = child->left;
					child->left = temp->left;
					a = child;
					delete temp;
					return;
				}
				if (temp->right != NULL) {
					a = temp->right;
					delete temp;
					return;
				}
				else
				{
					a = temp->left;
					delete temp;
					return;
				}
			}
			if (temp->right == NULL) {
				if (etemp->right == temp) {
					etemp->right = temp->left;

				}
				else {
					etemp->left = temp->left;
				}
				delete temp;
				return;
			}
			if (temp->left == NULL) {
				if (etemp->right == temp) {
					etemp->right = temp->right;

				}
				else {
					etemp->left = temp->right;
				}
				delete temp;
				return;
			}
			if (temp->left != NULL && temp->right != NULL) {

				BST* preparent = temp;
				BST* child = temp->left;
				while (child->right != NULL) {
					preparent = child;
					child = child->right;
				}
				if (child == temp->left) {
					if (etemp->right == temp) {
						child->right = temp->right;
						etemp->right = child;
					}
					else {
						child->right = temp->right;
						etemp->left = child;
					}
					delete temp;
					return;
				}

				BST* grandchild = child->left;
				if (preparent->right == child) {
					preparent->right = grandchild;
				}
				else {
					preparent->left = grandchild;
					child->left = temp->left;
				}

				if (etemp->right == temp) {
					etemp->right = child;
				}
				else {
					etemp->left = child;
				}
				delete temp;
				return;

			}

		}
		if (klucz < temp->klucz) {
			etemp = temp;
			temp = temp->left;
		}
		else
		{
			etemp = temp;
			temp = temp->right;
		}
	}
	cout << "Nie znaleziono klucza" << endl;
}
void usunall(BST* a) //get root
{
	if (a == NULL)
		return;
	if (a->left != NULL)
		usunall(a->left);
	if (a->right != NULL)
		usunall(a->right);

	delete a;

	return;
}
int global_counter = 0;
void preorder(BST* a, BST* b) {
	if (a == NULL) {
		return;
	}
	if (a != NULL) {
		global_counter++;
		cout << "\nWartosc klucza :   " << a->klucz << endl;
		/*/int j = 0;
		for (j; j < 100; j++) {
		cout << a->tab[j];
		}/*/

		preorder(a->left, b);
		preorder(a->right, b);
		if (a == b) {
			cout << "\nOdwiedzono " << global_counter << " wezlow" << endl;
			global_counter = 0;
		}
	}

}
void inorder(BST* a, BST* b) {
	if (a == NULL) {
		return;
	}
	if (a != NULL) {
		global_counter++;
		inorder(a->left, b);
		cout << "\nWartosc klucza :   " << a->klucz << endl;
		/*/int j = 0;

		for (j; j < 100; j++) {
		cout << a->tab[j];
		}/*/
		inorder(a->right, b);


		if (a == b) {
			cout << "\nOdwiedzono " << global_counter << " wezlow" << endl;
			global_counter = 0;
		}
	}

}

void postorder(BST* a, BST* b) {
	if (a == NULL) {
		return;
	}
	if (a != NULL) {
		global_counter++;
		postorder(a->left, b);
		postorder(a->right, b);
		cout << "\nWartosc klucza :   " << a->klucz << endl;
		/*/int j = 0;

		for (j; j < 100; j++) {
		cout << a->tab[j];
		} /*/

		if (a == b) {
			cout << "\nOdwiedzono " << global_counter << " wezlow" << endl;
			/*/global_counter = 0;*/
		}
	}

}

void rotate_r(BST*& root, BST* grandfather, BST* parent, BST* child) {
	if (grandfather != NULL) {
		if (grandfather->right = parent) {
			grandfather->right = child;
		}
		else{
			grandfather->left = child;
		}
}
	else {
		root = child;
	}
		BST* tmp = child->right;
		child->right = parent;
		parent->left = tmp;
		return;
}
void rotate_l(BST*& root, BST* grandfather, BST* parent, BST* child) {
	BST* tmp;
	if (grandfather != NULL) {
		if (grandfather->right = parent) {
			grandfather->right = child;
		}
		else {
			grandfather->left = child;
		}
	}
	else {
		root = child;
	}
	tmp = child ->left;
	child->left = parent;
	parent->right = tmp;
	return;
	
}
void make_list(BST*& root) {
	BST* grandfather = NULL;
	BST* tmp = root;
	BST* tmp2 = NULL;
	while (tmp != NULL) {
		if (tmp->left != NULL) {
			tmp2 = tmp->left;
			rotate_r(root, grandfather, tmp, tmp->left);
			tmp = tmp2;
		}
		else
		{
			grandfather = tmp;
			tmp = tmp->right;
		}
	}
}
int getheight(BST* root)
{
	if (root == NULL)
		return 0;
	else
		return 1 + max(getheight(root->left), getheight(root->right));
}
void showheight(BST* root) {
	int x = getheight(root);
	cout << "\nHello, wysokosc drzewa wynosi: " << x << endl;
}

void make_perfect_tree(BST*& root) {
	BST* grandfather = NULL;
	BST* tmp = root;
	BST* tmp2 = NULL;	
	int m = 1;
	int x = getheight(root);
	while (m <= x) {
		m = 2 * m + 1;
		
	}
	m = m / 2;
		for (int i = 0; i < (x - m); i++) {
			tmp2 = tmp->right;
			if (tmp2 != NULL) {
				rotate_l(root, grandfather, tmp, tmp->right);
				grandfather = tmp2;
				tmp = tmp2->right;
			}
		}
		while (m > 1) {
			m = m / 2; grandfather = NULL; tmp = root;
			for (int i = 0; i < m; i++) {
				tmp2 = tmp->right;
				rotate_l(root, grandfather, tmp, tmp->right);
				grandfather = tmp2;
				tmp = tmp2->right;
			}
		}
}
void DSW(BST*& root) {
	make_list(root);
	make_perfect_tree(root);
}
void rotacja(BST*& a, int klucz) {
	BST* eetemp = NULL;
	BST* etemp = NULL;
	BST* temp = a;
	if (klucz == temp->klucz) {
		cout << "Nie mo¿na dokonaæ rotacji, klucz jest rootem " << endl; return;
		while (temp != NULL) {
			if (klucz == temp->klucz) {
				cout << "Znaleziono klucz o wartosci :  , 1 - w prawo, reszta - w lewo" << temp->klucz << endl;
				int option;
				cin >> option;
				if (option == 1) {
					rotate_r(a, eetemp, etemp, temp);
				}
				else
					rotate_l(a, eetemp, etemp, temp);
				return;
			}
			if (klucz < temp->klucz) {
				etemp = temp;
				temp = temp->left;
			}
			else
			{
				eetemp = temp;
				etemp = temp;
				temp = temp->right;
			}
		}
		cout << "Nie znaleziono klucza" << endl;
	}
}
int main()
{
	int X, Y;
	FILE* fp = fopen("inlab04.txt", "r");
	if (fp == NULL)
		return -1;
	fscanf(fp, "%d %d", &X, &Y);
	fclose(fp); 
	clock_t begin, end;
	double time_spent;
	begin = clock();
	BST* root;
	srand(time(NULL));
	inicjacja(root);
	xnowych(root, X);
	showheight(root);
	DSW(root);
	showheight(root);
	usunall(root);
	inicjacja(root);
	xnowych(root, Y);
	showheight(root);
	DSW(root);
	showheight(root);

	/* here, do your time-consuming job */
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	cout << "\nCzas wykonania programu: " << time_spent << endl;
	getchar();

	return 0;
}

