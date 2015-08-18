class BookNode {
  public:
    string title;
    BookNode *next;
	
  	BookNode(string cat) {
	    title = cat;
	    next = NULL;
    }

  	void setNext(BookNode *nn) {
  		next = nn;
  	}

  	BookNode* getNext() {
  		return next;
  	}
    
  	string getTitle() {
      return title;
  	}
};
