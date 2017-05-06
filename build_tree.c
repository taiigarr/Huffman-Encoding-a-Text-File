
	 // pick the first two, build huffman tree yo! ok yaa
	 // store the sum, after storing the first two
//	 int i;
	//
	
		
	Node huff_tree[c*2];
	// this shouldn't be in a loop ye yea
	int initial_sum = huff_tree[1].freq;
	// oh separate char with highest frequency
	first_node = huff_tree[2]; // i checked b4 lol:p
	int sum = 0;
	 for (i=2, j=c*2-1; i <= c-1; i++,j--)	
	 {	
		// take the sum of all the frequencies.
		if (n_copy[i].freq > 0)
		{
			sum += huff_tree[i].freq;
		}
	 }
	 
	 huff_tree[1].freq = sum;
	 huff_tree[2] = n_copy[1]; //k
	 sum -= huff_tree[2].freq;
	 huff_tree[3].freq = sum; // we need this in a loop? ok k
	 //kk
	 // remove highest freq node from n_copy
	 // we could assign a char as a flag maybe
	 //cuz the char would be null anyway, kul
	 // assign -1 to n_copy highest freq node
	 n_copy[1].ch = '-1';// a-1? i'm not appending, exacto
	 int j, k;
	 int half_1_sum = 0, half_2_sum = 0;
	 for (i=4; i<=c-1; i++) // that makes sense)
	 {
	 	//split into two 
	 	// you know, i think it would be easier if we start from the 
	 	// end of the tree.. maybe.. oh, idk yea nvm:p
	 	// save the var for the first and second halves
	 	//bb, we can do.. store the sums into the tree
	 	// we need another for
	 	// hold on i thought we're starting at 4, oohh kk
	 	for(j=0, k=c-1; j<=(c-1)/2, k>(c-1)/2; j++, k--)
	 	{
		 	half_1_sum = n_copy[j].freq;
		 	half_2_sum = n_copy[k].freq; //? lol no i didnt  lol:P :d
		 }
		 
		 huff_tree[i].freq = half_1_sum; //jaja
		 huff_tree[i+1].freq = half_2_sum;
		 // add the char nodes
	 }
	 
	 for (i=0; i<c; i++) //k
	 	printf("%d ", huff_tree[i].freq);
	 /*
	 // take the first two smallest
		if (n_copy[i].freq > 0)
		{
			huff_tree[j] = n_copy[i];
			huff_tree[j-1] = n_copy[i+1];
			sum = n_copy[i].freq + n_copy[i+1].freq;
			// so now, "remove" those previous ones
			n_copy[i].freq = 0;
			n_copy[i+1].freq = sum;
			n_copy[i+1].ch = '\0'; //   // empty the char yo
			huff_tree[j-2].freq = sum; //lol
			j --;
		}
		*/
