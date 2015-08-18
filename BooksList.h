class BooksList {
    CategoryNode *head;    
  public:
    BooksList() {
      head = NULL;           
    }

    bool isEmpty() {
      return (head==NULL);     
    }

    bool Search(string query, int val, string save) { // search a book / category..
         bool retFound = false;
         if(save == "yes")
             fileWrite.open("Books_Info.txt",ios::app);
         if(!isEmpty()){
             CategoryNode *curr=head,*ret=NULL;
             bool found=false;
             
             while(curr!=NULL && !found){
                   if(curr->category == query && val==2) { // search in category
                        if(save == "yes") 
                             fileWrite<<"\n\t\t\tCategory : "<<curr->category;
                        cout<<"\n\t\t\tCategory : "<<curr->category;
                        found=true;
                        BookNode* sBooks = curr->books; 
                        while(sBooks != NULL && !found) {
                             if(save == "yes")
                                fileWrite<<"\n\t\t\tBook Title : "<<sBooks->title;
                             cout<<"\n\t\t\tBook Title : "<<sBooks->title;
                             sBooks = sBooks->next;
                        }
                   }
                   else if(val==1) { // search in books..
                        BookNode* sBooks = curr->books;
                        bool bookF = false; 
                        while(sBooks != NULL && !bookF) {
                              if(sBooks->title == query) {
                                   bookF = true;
                                   if(save == "yes")
                                       fileWrite<<"\n\t\t\tBook Title : "<<sBooks->title;
                                   cout<<"\n\t\t\tBook Title : "<<sBooks->title;
                              }
                              else {
                                   sBooks = sBooks->next;
                              }
                        }
                        if(bookF) {
                             if(save == "yes")
                                  fileWrite<<"\n\t\t\tCategory : "<<curr->category;
                             cout<<"\n\t\t\tCategory : "<<curr->category;
                             found = retFound = true;
                        }       
                   }
                   curr=curr->next;        
             }  
             retFound = found;        
         }
         if(save == "yes") fileWrite.close();
         return retFound;
    }

    bool DeleteBookByTitle(string bookName) {
        bool retResult = false;
        if(!isEmpty()){
             CategoryNode *curr=head,*ret=NULL;
             bool deleted=false;
             while(curr!=NULL && !deleted) {
                        bool found = false;
                        BookNode* currBook = curr->books; 
                        BookNode* prevBook = NULL;
                        while(currBook != NULL && !found) {
                              if(currBook->title == bookName) {
                                   found = true;
                              }
                              else {
                                   prevBook = currBook;
                                   currBook = currBook->next;
                              }
                        }
                        if(found) {
                             BookNode* node = currBook;
                             if(prevBook == NULL) {
                                  curr->books = currBook->next;
                             }
                             else {
                                  prevBook->next = currBook->next;
                             }
                             delete (node);
                             deleted = true;
                        }
                        else // move to next category
                             curr=curr->next;          
             }  
             retResult = deleted;        
         }
         return retResult;
    }

    bool InsertCategory(string cat) {
       bool retInserted = false;
       CategoryNode *newnode = new CategoryNode(cat);
       if(isEmpty()) {
           head = newnode;   
           retInserted = true;           
       }
       else {
           newnode->next = head;
           head = newnode;
           retInserted = true; 
       }
       return retInserted;
    }

    bool InsertBook(string bok, int catID) {
       bool retInserted = false; 
       BookNode *newBook = new BookNode(bok);
       if(!isEmpty()) { // categories available
           int i=1;
           CategoryNode *curr = head,*prev = NULL;
           bool CanInsert=false;
           i = 1;
           while(i<= catID && curr!=NULL && !CanInsert) {
             if(i == catID) {
               	if(curr->books == NULL) {
                      CanInsert = true;
                }
                else{
                   BookNode *sBooks = curr->books;
                   bool foundBook = false;
                   while(sBooks!=NULL && !foundBook) {
                         if(sBooks->title == bok) { // book found
                             foundBook = true;          
                         }
                         else {
                             sBooks = sBooks->next;     
                         }            
                   } 
                   if(!foundBook) {
                      CanInsert = true; 
                   }
                }
             }
             else{
                  curr = curr->next;
                  i++;
             }
           }
           if( CanInsert && curr != NULL ) {
              if(curr->books == NULL){
                   curr->books = newBook;
                   retInserted = true;
              }
              else {
                   newBook->next = curr->books;
                   curr->books = newBook;
                   retInserted = true;
              }
           }
       }
       return retInserted;
    }

    bool DeleteCategoryByID(int catID) {
        bool retDeleted = false;
        if(!isEmpty()){
             CategoryNode* curr = head;
             CategoryNode* prev = NULL;
             int i=1;
             bool canDelete = false;
             while(curr!=NULL && i<=catID && !canDelete) {
                   if(i == catID){
                        canDelete = true;
                   }
                   else{
                        prev = curr;
                        curr = curr->next;
                        i++;
                   }
             }
             if(canDelete) {
                  if(prev == NULL) { // delete First
                        CategoryNode *node = curr;
                        head = curr->next;
                        delete (node);
                        retDeleted = true;
                  }
                  else {
                       CategoryNode *node = curr;
                       prev->next = curr->next;
                       delete (node);
                       retDeleted = true;
                  }
             }
        }
        return retDeleted;
    }

    void InsertNewCategory() {
        string categ;
        cout<<"Category Name : "; 
        fflush(stdin);
        getline(cin,categ);
        convertToLower(categ);
        if(InsertCategory(categ)) {
           cout<<"Inserted..\n";
        }
        else {
           cout<<"Already Exist.! \n";     
        }
    }

    void InsertNewBook() {
        if(!isEmpty()){
            string bookTitle = "";
            int categ = -1, i = 1;
            CategoryNode *ptr = head;
            cout<<"Book Title : "; 
            fflush(stdin);
            getline(cin,bookTitle);
            convertToLower(bookTitle);
            cout<<"\n\t\tAvailable Books Categories\n";
            while(ptr!=NULL) {
               	cout<<i<<".\t"<<ptr->category<<endl;
               	ptr = ptr->next;
               	i++;
            }
            cout<<"Choose Category :"; cin>>categ;

            if( InsertBook(bookTitle,categ) ) {
               cout<<"Inserted..\n";
            }
            else {
               cout<<"Book Already Exist.! \n";     
            }
        }
        else {
             cout<<"No Categories Available!\n";
        }
    }

    void DeleteCategory() {
        if(!isEmpty()) {
            int categ = -1, i = 1;
            CategoryNode *ptr = head;
            cout<<"\n\t\tAvailable Books Categories\n";
            while(ptr!=NULL) {
               	cout<<i<<".\t"<<ptr->category<<endl;
               	ptr = ptr->next;
               	i++;
            }
            cout<<"Choose Category to delete :"; cin>>categ;
            if( DeleteCategoryByID(categ) ) {
               cout<<"Deleted..\n";
            }
            else {
               cout<<"Category not exist.! \n";     
            }
        }
        else {
             cout<<"No Categories Available!\n";
        }
    }

    void DeleteBook() {
        if(!isEmpty()) {
            string bookTitle = "";
            cout<<"BookTitle to delete :"; 
            fflush(stdin);
            getline(cin,bookTitle);
            convertToLower(bookTitle);
            if( DeleteBookByTitle(bookTitle) ) {
               cout<<"Deleted..\n";
            }
            else {
               cout<<"No Category exist.! \n";     
            }
        }
        else {
             cout<<"No Categories Available!\n";
        }
    }

    void SearchBook() {
        if(!isEmpty()) {
             string bookTitle = "", saveResult="no";
             cout<<"BookTitle to search :"; 
             fflush(stdin);
             getline(cin,bookTitle);
             cout<<"Do you want to save results too(yes/no): ";
             cin>>saveResult;
             convertToLower(bookTitle);
             convertToLower(saveResult);
             if(!Search(bookTitle,1,saveResult))
                 cout<<"Book Not Found!\n";
        }
        else {
            cout<<"No Categories Available!\n";
        }  
    }

    void SearchCategory() {
        if(!isEmpty()) {
             string Categ = "", saveResult="no";
             cout<<"Category to search :"; 
             fflush(stdin);
             getline(cin,Categ);
             cout<<"Do you want to save results too(yes/no): ";
             cin>>saveResult;
             convertToLower(saveResult);
             convertToLower(Categ);
             if(!Search(Categ,2,saveResult))
                 cout<<"Category Not Found!\n";
        }
        else {
            cout<<"No Categories Available!\n";
        }  
    }

    void PrintAll() {
        if(!isEmpty()) {
             CategoryNode* currCateg = head;
             int i=1,j=1;
             while(currCateg!=NULL) {
                   cout<<"\tCategory "<<i<<": "<<currCateg->category<<"\n";
                   BookNode *currBook = currCateg->books;
                   j=1;
                   while(currBook!=NULL) {
                         cout<<"\t\tBook Title"<<j<<" : "<<currBook->title<<"\n";
                         currBook = currBook->next;
                         j++;
                   }
                   currCateg = currCateg->next;
                   i++;
             }
        }
        else {
            cout<<"No Categories Available!\n";
        }     
    }
};
