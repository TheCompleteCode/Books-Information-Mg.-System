class CategoryNode {
  public:  
    string category;
    CategoryNode *next;
    BookNode *books; // all books of that particular category

    CategoryNode(string cat) {
      category = cat;
      next = NULL;
      books = NULL;
    }

    void setNext(CategoryNode *nn) {
    	next = nn;
    }

    void setBooks(BookNode *bb) {
    	books = bb;
    }

    CategoryNode* getNext() {
    	return next;
    }

    BookNode* getBooks() {
    	return books;
    }

    string getCategory() {
      return category;
    }
};
