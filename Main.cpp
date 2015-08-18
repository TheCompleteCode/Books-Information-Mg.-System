#include <iostream>
#include <fstream>
using namespace std;
ofstream fileWrite;
#include "Globel.h"


int main() {
	BooksList* total = new BooksList();
	char again='n';
	do {
    system("cls");
    char ch;
  	cout<<"\t\t\tWelcome To MY-BOOKSTORE\n\n";
  	cout<<"Select Option.\n";
  	cout<<"\t 1. Add New Category\n";
  	cout<<"\t 2. Add New Book\n";
  	cout<<"\t 3. Delete a Category\n";
  	cout<<"\t 4. Delete a Book\n";
  	cout<<"\t 5. Search a Category\n";
  	cout<<"\t 6. Search a Book\n";
  	cout<<"\t 7. Print All\n";
  	cout<<"Input : ";
  	cin>>ch;
  	switch(ch) {
      case '1':
          total->InsertNewCategory();
          break;
      case '2':
          total->InsertNewBook();
          break;
      case '3':
          total->DeleteCategory();
          break;
      case '4':
          total->DeleteBook();
          break;
      case '5':
          total->SearchCategory();
          break;
      case '6':
          total->SearchBook();
          break;
      case '7':
          total->PrintAll();
          break;
      default:
          cout<<"Invalid Option.\n";
          break;
    }
    cout<<"\n\t\t Do you want to run again(y/n) : "; cin>>again;
  }while(again!='n');
	system("pause");
}
