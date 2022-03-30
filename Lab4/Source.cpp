#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <iostream>
#include <synchapi.h>

int* make_array(int n) {
	int* arr = (int*)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) {
		arr[i] = 1;
	}
	return arr;
}

typedef struct data{
	int* arr;
	int start_range;
	int end_range;
	int thread_id;
}data_t;

data_t* make_data(int* arr, int start_range, int end_range, int thread_id) {
	data_t* d = (data_t*)malloc(sizeof(data_t));
	d->arr = arr;
	d->start_range = start_range;
	d->end_range = end_range;
	d->thread_id = thread_id;
	return d;
}

HANDLE threads[3];

DWORD WINAPI thread_function(void* arguments) {
	data_t* data = (data_t*)arguments;
	for (int i = data->start_range; i <= data->end_range; i++) {
		data->arr[i] = data->arr[i] * data->thread_id;
	}
	printf("Thread finished ID: %d\n", data->thread_id);
	return 0;
}

void print_arr(int* arr, int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

int main() {

	DWORD id;
	int n;
	printf("Type size of array: ");
	scanf("%d", &n);
	int* arr = make_array(n);
	int interval_len = n / 3; 
	printf("Array before: ");
	print_arr(arr, n);

	for (int i = 0; i < 3; i++) {
		data_t* data;
		int thread_id = i + 1;
		if (i == 0) {
			int start_range = 0; 
			int end_range = (interval_len) - 1;

			data = make_data(arr, start_range, end_range, thread_id);
		}
		else if (i == 1) { 
			int start_range = interval_len; 
			int end_range = (interval_len * 2) - 1; 

			data = make_data(arr, start_range, end_range, thread_id);
		}
		else {
			int start_range = (interval_len * 2); 
			int end_range = (interval_len * 3) - 1 + (n % 3) ; 

			data = make_data(arr, start_range, end_range, thread_id);
		}

		threads[i] = CreateThread(
			NULL,
			0,
			thread_function,
			(void*) data,
			0,
			&id
		);
		if (threads[i] != INVALID_HANDLE_VALUE) {
			printf("New thread created ID: %d\n", thread_id);
		}
	}
	
	WaitForMultipleObjects(3, threads, true, 10000);

	printf("Array after: ");
	print_arr(arr, n);
	return 0;
}