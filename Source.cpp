#include<iostream>
#include<stdlib.h>

struct node {
	void* val;
	struct node* next;
};

struct stack_list {
	bool (*compare)(void*, void*);
	struct node* head;
};

typedef struct book {
	int ISBN;
	char* title;
	char* author;
}book_t;

struct stack_list* init_sl(bool (*f)(void*, void*)){
	struct stack_list* sl = (struct stack_list*)malloc(sizeof(struct stack_list));
	sl->head = (struct node*)malloc(sizeof(struct node));
	sl->compare = f;
	sl->head->val = NULL;
	sl->head->next = NULL;
	return sl;
}

int sl_len(struct stack_list* sl) {
	int len = 0;
	struct node* tmp = sl->head;
	while (tmp != NULL) {
		len++;
		tmp = tmp->next;
	}
	return len;
}

void sort(struct stack_list* sl) {
	for (int i = 0; i < sl_len(sl); i++) {
		struct node* tmp = sl->head;
		while (tmp->next != NULL) {
			if (sl->compare(tmp->val, tmp->next->val)) {
				void* tmp_val = tmp->val;
				tmp->val = tmp->next->val;
				tmp->next->val = tmp_val;
			}
			tmp = tmp->next;
		}
	}
}

void push(struct stack_list* sl, void* val) {
	if (sl->head->val == NULL) {
		sl->head->val = val;
		return;
	}
	struct node* n = sl->head;
	sl->head = (struct node*)malloc(sizeof(struct node));
	sl->head->val = val;
	sl->head->next = n;
	sort(sl);
}

void* pop(struct stack_list* sl) {
	if (sl->head != NULL) {
		void* val = sl->head->val;
		struct node* tmp = sl->head;
		sl->head = sl->head->next;
		free(tmp);
		return val;
	}
	else
		return NULL;
}

book_t* create_book(int ISBN, char* title, char* author) {
	book_t* book = (book_t*)malloc(sizeof(book_t));
	book->ISBN = ISBN;
	book->title = title;
	book->author = author;
	return book;
}

bool compare_int(void* x, void* y) {
	if ((int*)x > (int*)y) { return 1; }
	else { return 0; }
};

int char_arr_len(char* arr) {
	return sizeof(arr) / sizeof(char);
}

bool compare_book(void* b1, void* b2) {
	book_t* tmp_b1 = (book_t*)b1;
	book_t* tmp_b2 = (book_t*)b2;
	if (char_arr_len(tmp_b1->title) > char_arr_len(tmp_b2->title)) {
		return 1;
	}
	else { return 0; }
}

void sl_print_int(struct stack_list* sl) {
	struct node* tmp = sl->head;
	for (int i = 0; i < sl_len(sl); i++) {
		printf("%d ", tmp->val);
		tmp = tmp->next;
	}
	printf("\n");
}

void sl_print_book(struct stack_list* sl) {
	struct node* tmp = sl->head;
	for (int i = 0; i < sl_len(sl); i++) {
		book_t* tmp_b = (book_t*)tmp->val;
		printf("%s ", tmp_b->title);
		tmp = tmp->next;
	}
	printf("\n");
}

int main() {

	struct stack_list* sl_book = init_sl(compare_book);
	int ISBN_1 = 1111;
	char title_1[15] = "TitleTitle";
	char author_1[11] = "Author";
	book_t* b1 = create_book(ISBN_1, title_1, author_1);

	int ISBN_2 = 2222;
	char title_2[11] = "Titleeee";
	char author_2[11] = "Author";
	book_t* b2 = create_book(ISBN_2, title_2, author_2);

	int ISBN_3 = 3333;
	char title_3[10] = "Title";
	char author_3[11] = "Author";
	book_t* b3 = create_book(ISBN_3, title_3, author_3);

	push(sl_book, b1);
	push(sl_book, b2);
	push(sl_book, b3);
	sl_print_book(sl_book);
	void* tmp_book = pop(sl_book);
	sl_print_book(sl_book);

	struct stack_list* sl_int = init_sl(compare_int);
	push(sl_int, (int*)4);
	push(sl_int, (int*)6);
	push(sl_int, (int*)1);
	push(sl_int, (int*)3);
	sl_print_int(sl_int);
	void* tmp_int = pop(sl_int);
	sl_print_int(sl_int);
	
	return 0;
}

