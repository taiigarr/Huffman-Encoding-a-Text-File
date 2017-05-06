/* Note to instructor: please use the math option when compiling
 ie. cc -o hstats hstats.c -lm
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define NUM_CHARS 256

typedef struct _treenode Node;
struct _treenode {
    int freq;			/* frequency; is the priority for heap */
    unsigned char ch;		/* character, if any */
    struct _treenode *left;		/* left child of Huffman tree (not heap!) */
    struct _treenode *right;			/* right child of Huffman tree */
} ;


/* this is a priority queue implemented as a binary heap */
typedef struct _pq {
    int heap_size;
    Node *A[NUM_CHARS];
} PQ;

/* create an empty queue */

void create_pq(PQ * p)
{
    p->heap_size = 0;
}

/* this heap node's parent */

int parent(int i)
{
    return (i - 1) / 2;
}

/* this heap node's left kid */

int left(int i)
{
    return i * 2 + 1;
}

/* this heap node's right kid */

int right(int i)
{
    return i * 2 + 2;
}

/* makes the subheap with root i into a heap , assuming left(i) and
* right(i) are heaps
*/
void heapify(PQ * p, int i)
{
    int l, r, smallest;
    Node *t;

    l = left(i);
    r = right(i);

/* find the smallest of parent, left, and right */

    if (l < p->heap_size && p->A[l]->freq < p->A[i]->freq)
	smallest = l;
    else
	smallest = i;
    if (r < p->heap_size && p->A[r]->freq < p->A[smallest]->freq)
	smallest = r;

/* swap the parent with the smallest, if needed. */

    if (smallest != i) {
	t = p->A[i];
	p->A[i] = p->A[smallest];
	p->A[smallest] = t;
	heapify(p, smallest);
    }
}


/* remove the element at head of the queue (i.e., with minimum frequency)
 * */
Node *extract_min_pq(PQ * p)
{
    Node *r;

    if (p->heap_size == 0) {
	printf("heap underflow!n");
	exit(1);
    }

/* get return value out of the root */

    r = p->A[0];

/* take the last and stick it in the root (just like heapsort) */

    p->A[0] = p->A[p->heap_size - 1];

/* one less thing in queue */

    p->heap_size--;

/* left and right are a heap, make the root a heap */

    heapify(p, 0);
    return r;
}


/* insert an element into the priority queue. r->freq is the priority */
void insert_pq(PQ * p, Node * r)
{
    int i;

    p->heap_size++;
    i = p->heap_size - 1;

/* we would like to place r at the end of the array,
* but this might violate the heap property. we'll start
* at the end and work our way up
*/
    while ((i > 0) && (p->A[parent(i)]->freq > r->freq)) {
		p->A[i] = p->A[parent(i)];
		i = parent(i);
    }
    p->A[i] = r;
}
//yea
/* there are 256 possible characters */

int i = 0;

void copyArray(Node *ar1, Node *ar2)
{
	int i;
	for(i=0; i<NUM_CHARS; i++)
		ar2[i] = ar1[i];
}

// check if it's the end of sequence, yea lol.
Node *is_seq(Node * r, int code)
{
	if ((r->left == NULL) && (r->right == NULL)) {

		if (code == 0)
			is_seq(r->left, code);

	/* go right with bit 1 */

		else
			is_seq(r->right, code);
	}
	// return tree ptr at this point, we can then check if there's a char
	return r;
}

/* traverse the Huffman tree, building up the codes in codes[] */

void traverse(Node * r,	/* root of this (sub)tree */
	      int level,	/* current level in Huffman tree */
	      char code_so_far[],	/* code string up to this point in tree */
	      char *codes[])
{				/* array of codes */

/* if we're at a leaf node, */

    if ((r->left == NULL) && (r->right == NULL)) {

	/* put in a null terminator */

		code_so_far[level] = 0;

	/* make a copy of the code and put it in the array */

		codes[r->ch] = strdup(code_so_far);
    } else {

	/* not at a leaf node. go left with bit 0 */

		code_so_far[level] = '0';
		traverse(r->left, level + 1, code_so_far, codes);

	/* go right with bit 1 */

		code_so_far[level] = '1';
		traverse(r->right, level + 1, code_so_far, codes);
    }
}


/* make the huffman tree from frequencies in freq[] (Huffman's Algorithm)
 * */

Node *build_huffman(unsigned int freqs[])
{
    int i, n;
    Node *x, *y, *z;
    PQ p;

/* make an empty queue */

    create_pq(&p);

/* for each character, make a heap/tree node with its value
* and frequency 
*/
    for (i = 0; i < NUM_CHARS; i++) {
		x = malloc(sizeof(Node));

	/* its a leaf of the Huffman tree */

		x->left = NULL;
		x->right = NULL;
		x->freq = freqs[i];
		x->ch = (char) i;
		//if (x->freq)
			//printf("%c %d \n", x->ch, x->ch);

	/* put this node into the heap */
// YOU FEIM
		insert_pq(&p, x);
    }

/* at this point, the heap is a "forest" of singleton trees */

    n = p.heap_size - 1;	/* heap_size isn't loop invariant! */

/* if we insert two things and remove one each time,
* at the end of heap_size-1 iterations, there will be
* one tree left in the heap
*/
    for (i = 0; i < n; i++) {

/* make a new node z from the two least frequent
* nodes x and y
*/
	z = malloc(sizeof(Node));
	x = extract_min_pq(&p);	
	y = extract_min_pq(&p);
	z->left = x;
	z->right = y;

/* z's frequency is the sum of x and y */

	z->freq = x->freq + y->freq;

/* put this back in the queue */

	insert_pq(&p, z);
    }

/* return the only thing left in the queue, the whole Huffman tree */

    return extract_min_pq(&p);
}

// milo's fn converting decimal to binario
int dectobin(int num)
{
	int bin = 0;
	int exp;
	while(num > 0)
	{
		exp = log2(num);
		num = num % (int) pow(2, exp);
		bin += pow(10, exp);
	}
	return bin;
}

// MAIN
int main(int argc, char *argv[])
{
    FILE *f, *g;
    Node *r, **root;		/* root of Huffman tree */
    unsigned int n, n2, saving,
    	freqs[NUM_CHARS];		/* number of bytes in file */
    Node
     nodes[NUM_CHARS],
     n_copy[NUM_CHARS];		/* frequency of each char */
    char *codes[NUM_CHARS],	/* array of codes, 1 per char */
     code[NUM_CHARS],		/* a place to hold one code */
     fname[100];		/* what to call output file */
     char huff_str[NUM_CHARS] = "";

/* hassle user */
    if (argc != 2) {
		fprintf(stderr, "Usage: %s < filename>\n", argv[0]);
		exit(1);
    }

/* open command line argument file */

    f = fopen(argv[1], "r");
    if (!f) {
		perror(argv[1]);
		exit(1);
    }
    g = fopen("Haha.new", "w");
    if (!g) {
		perror(fname);
		exit(1);
    }
    
    // make the binary file legible, put in inside freqs
	fread(freqs, NUM_CHARS, sizeof(int), f);
	// read the number of characters in file
	fread(&n, 1, sizeof(int), f);
	
	/* make the huffman tree */
	 r = build_huffman(freqs);
	 // keep the root
	 root = &r;
	 
	int i;
	int c = 0; 
	// store every frequency inside our node
	for (i=0; i < NUM_CHARS; i++)
	{
		if (freqs[i] > 0)
		{
			nodes[c].freq = freqs[i];
			nodes[c].ch = i;
			c++;	// LOL
		}
	}
		
	// go char by char and print
	printf("FREQUENCIES:\n");
	for (i = 0; i < NUM_CHARS; i++)
	{
		if (freqs[i] > 0)
		{
			if (i > 31)
				printf("%c %d %d\n", i, i, freqs[i]);
			else
			// weird chars
				printf("? %d %d\n", i, freqs[i]);
		}
	}
	
	 /* traverse the tree, filling codes[] with the codes */

    traverse(r, 0, code, codes);	//n_copy
    
	printf("\nCODES:\n");
		for (i = 0; i < NUM_CHARS; i++)
	{
		if (freqs[i] > 0)
		{
			if (i > 31)
				printf("%c %d %s\n", i, i, codes[i]);
			else
			// weird chars
				printf("? %d %s\n", i, codes[i]);
		}
	}
	// shifts all the chars to the right
	void shift_right(char *str, int pos)
	{
		int c;
		for (c = strlen(str)-1; c >= pos-1; c--)
	      str[c+1] = str[c];	
	}
	// Read the codes (decimal form of binary codes)
	// * need math.h and stdlib.h
	printf("\nENCODED BIT STRING:\n");
	int hc;
	int k, j, start = 0;
	int seq_done = 1;
	char str[NUM_CHARS*NUM_CHARS];
	n2 = 0;
	for (i=0; (hc=fgetc(f))!=EOF; i++)
	{
		n2++;	// count number of character

		/* hc is the actual decimal code. 
		Use it to determine when to insert a zero. 
		 Use a counter to go from 0 to 8
		 Check when i==0, and if the seq is done
		 */
		int seq = dectobin(hc);
		sprintf(str, "%d", seq);
		if (i==0)
		{
			shift_right(str, 0);
			str[0] = '0';
		}
		seq_done = 0;	// false
		
		// Check against the codes
		for (k=start; k<NUM_CHARS; k++)
		{
			// Display bit string
			printf("%c", str[k]);
			// Insert a zero on a complete sequence per every "byte" of code 
			is_seq(r, str[k]);
			if (r->ch != '\0' && k%8 == 0) 
			{
				shift_right(str, k);
				str[0] = '0';
				start = k;
				break;
			}
	
		}	
	}	
	printf("\n");
	
	// Computer space saving
	if (n2 < n)
		saving = 0;
	else
		saving = 1 - n2/n;	
	printf("SPACE SAVING:\t%d\n", saving);
}   
