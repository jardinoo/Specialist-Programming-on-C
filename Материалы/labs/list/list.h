struct tagItem {
	void* p;
	struct tagItem* prev;
	struct tagItem* next;
};
typedef struct tagItem Item;

int getCount();
void delItem();
void printList();
int findItem(void* s);
void addItem(void* s);
