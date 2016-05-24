#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;
char alphabet[] = {'a','b','c','d','e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

// takes in a vector filled with chars [a, b, c] and prints abc
void print_word(const vector<char> v)
{
	for (int i = 0; i < v.size(); ++i)
	{
		cout << v[i]; 
	}
	cout << endl; 
}

//gets char binary array from dec number and specified bitlength
vector<char> dec_to_bin(int bitlength, int decimal)
{
	int remainder = 0;
	vector<char> binary;

	for (int i = 0; i < bitlength; ++i)
	{
		remainder = decimal % 2;
		if (remainder == 1)
			binary.insert(binary.begin(),'1');
		else
			binary.insert(binary.begin(),'0'); 

		if (decimal == 1)
		{
			if (i < bitlength - 1)
			{
				for (int j = i; j < bitlength - 1; ++j)
				{
					binary.insert(binary.begin(), '0'); 
				}
			}
			break; 
		}


		decimal = floor(decimal / 2); 
	}
	return binary; 
}

//input: binary array (max size is 5) 
int bin_to_dec(vector<int> bin)
{
	int decimal; 
	int power,index;
	index = power = decimal = 0; 
	for (int i = bin.size() - 1; i >= 0; --i)
	{
		if (bin[i] == 1)
		{
			power = pow(2, index);
			decimal += power;
		}
		++index; 
	}
	return decimal; 
}

//input: 5 bit binary array
//output: returns a character corresponding to it 
char bin_to_letter(vector<char> bin)
{
	vector<int> b; 
	for (int i = 0; i < 5; ++i)
	{
		if (bin[i] == '1')
			b.push_back(1);
		else
			b.push_back(0); 
	}
	// converted array to int by here 
	int key; 
	key = bin_to_dec(b); 
	if (key < 26)
		return alphabet[key];
	else
		return '*'; 
}


//inptu: two numbers 0-25 that represent integers
int xor_twoletters(int l1, int l2)
{
	vector<char> bin_l1 = dec_to_bin(5, l1);
	vector<char> bin_l2 = dec_to_bin(5, l2); 
	vector<int> output; 
	int one, two; 
	one = two = 0; 
	for (int i = 0; i < 5; ++i)
	{
		if (bin_l1[i] == '1')
			one = 1;
		else
			one = 0;
		if (bin_l2[i] == '1')
			two = 1;
		else
			two = 0;

		output.push_back(one ^ two); 
	}
	int result = bin_to_dec(output); 
	return result; 
}  

//input: 2d tokenized binary array and key array (integer) 
//output: get back tokenized array
vector<vector<char>> decrypt(vector<vector<char>>ct_bin, vector<int>key)
{
	int temp1 = 0;
	int temp2 = 0;

	vector<vector<int>> ct_bin_int; 
	vector<vector<char>> result; 
	vector<char> temp; 

	for (int i = 0; i < ct_bin.size(); ++i)
	{
		ct_bin_int.push_back(vector<int>()); 
		result.push_back(vector<char>()); 
		for (int j = 0; j < 5; ++j)
		{
			if (ct_bin[i][j] == '1')
				ct_bin_int[i].push_back(1);
			else
				ct_bin_int[i].push_back(0); 
		}
	}
	//converted char ct_bin to int ct_bin
	for (int i = 0; i < ct_bin.size(); ++i)
	{
		temp1 = bin_to_dec(ct_bin_int[i]);
		temp2 = key[i % key.size()];
		int xored = xor_twoletters(temp1, temp2); 
		temp = dec_to_bin(5, xored); 
		for (int j = 0; j < 5; ++j)
		{
			result[i].push_back(temp[j]);
		}
	}
	return result; 
}

//prints 2d bin array to a letter array 
void print_2darray(vector<vector<char>> in)
{
	vector<char> ct_letters;
	for (int i = 0; i < in.size(); ++i)
	{
		ct_letters.push_back(bin_to_letter(in[i]));
	}

	// got the ct in letters here (char array) 
	print_word(ct_letters);
}

int get_letter_key(char letter)
{
	int key = 0; 
	for (int i = 0; i < 26; ++i)
	{
		if (letter == alphabet[i])
		{
			key = i; 
		}
	}
	return key; 
}

//input: word ['a','b','e'] gives back [0,1,4]  
vector<int> word_to_key(vector<char> word)
{
	vector<int> result;
	for (int i = 0; i < word.size(); ++i)
	{
		result.push_back(get_letter_key(word[i]));
	}
	return result; 
}

int main()
{
	string ct;
	string dictionary; 
	vector<vector<vector<char>>> alpha_dict; 
	vector<vector<char>> ct_bin; 

	for (int i = 0; i < 26; ++i)
	{
		alpha_dict.push_back(vector<vector<char>>());
	}
	/*
	alpha_dict[0].push_back(vector<char>());
	alpha_dict[0][0].push_back('a');
	cout << alpha_dict[0][0][0] << endl; 
	*/ 
	int ct_index = 0; 
	ifstream myfile("CT9.txt");
	if (myfile.is_open())
	{
		while (getline(myfile,ct))
		{
			for (int i = 0; i < ct.length(); ++i)
			{
				if ((i % 5) == 0)
				{
					ct_bin.push_back(vector<char>());
					ct_bin[ct_index].push_back(ct[i]);
					
				}
				else
				{
					ct_bin[ct_index].push_back(ct[i]); 
					if ((i % 5) == 4)
						++ct_index; 
				}
			}
		}
		myfile.close();
	}
	else cout << "Unable to open file" << endl; 

	ifstream mydict("dictionary.txt");
	if (mydict.is_open())
	{
		while (getline(mydict, dictionary))
		{
			// push_back in alphabetical vector if 1st is a, than [0].push_back(vector<char>)
			int letter_id = 0; 
			for (int i = 0; i < 26; ++i)
			{
				if (char(tolower(dictionary[0])) == alphabet[i])
				{
					alpha_dict[i].push_back(vector<char>()); 
					letter_id = i; // set the letter id. 
				}
			}
			// fill the [0][0] vector with the word
			for (int i = 0; i < dictionary.length(); ++i)
			{
				alpha_dict[letter_id][alpha_dict[letter_id].size()-1].push_back(char(tolower(dictionary[i])));
			}
			//cout << char(tolower(dictionary[0])) << endl; converts to lowercase
		}
		mydict.close();
	}
	else cout << "Unable to open file" << endl; 


	// dictionary alphabetized 3d array filled by here...
	//print_word(alpha_dict[0][0]); print first word.. 
	//print_word(alpha_dict[alpha_dict.size() - 1][alpha_dict[alpha_dict.size() - 1].size()-1]); 
	// prints last word ..


	string wbf_string;
	vector<vector<char>> wbf_v;
	int wbf_i = 0;
	ifstream wbf("words-by-frequency.txt"); // words by frequency
	if (wbf.is_open())
	{
		while (getline(wbf, wbf_string))
		{
			wbf_v.push_back(vector<char>());
			for (int i = 0; i < wbf_string.length(); ++i)
			{
				wbf_v[wbf_i].push_back(wbf_string[i]);
			}
			++wbf_i;
		}
		wbf.close();
	}
	else cout << "Unable to open file" << endl;


	// ct_bin = tokenized bit string  
	vector<int> key;
	//vector<vector<char>> decrypted_2darray;
	//decrypted_2darray = decrypt(ct_bin, key); 
	//print_2darray(decrypted_2darray); 



	// dictionary attack begins here key1 = the key2 = or ... etc... 
	vector<vector<char>> decrypted_2darray;
	for (int i = 0; i < wbf_v.size(); ++i)
	{
		key = word_to_key(wbf_v[i]); 
		decrypted_2darray = decrypt(ct_bin, key);
		vector<char> ct_letters;
		for (int j = 0; j < decrypted_2darray.size(); ++j)
		{
			ct_letters.push_back(bin_to_letter(decrypted_2darray[j]));
		}
		// ct xor key char array gotten by here 
		//cout << i << ": ";
		//print_word(ct_letters);

		int index = 0;
		int chars_right = 0;
		int letter_key = 0; 
		int words_right = 0; 
		bool got_a_word = false; 
		bool got_an_asterisk = false; 

		int char_right_first_word = 0; 
		bool word_at_beginning = false; 

		/*
		// scan first word 
		int f_letter_key = get_letter_key(ct_letters[0]);
		for (int d = 0; d < alpha_dict[f_letter_key].size(); ++d)
		{
			char_right_first_word = 0;
			for (int f = 0; f < alpha_dict[f_letter_key][d].size(); ++f)
			{
				
					if (ct_letters[f] == alpha_dict[f_letter_key][d][f])
					{
						++char_right_first_word;
					}
					if (char_right_first_word == alpha_dict[f_letter_key][d].size())
					{
						word_at_beginning = true;
						break;
					}

			}
		}
		
		if (word_at_beginning) // removed words right > 1 temorary .. 
		{
			for (int q = 0; q < key.size(); ++q)
			{
				cout << key[q] << ", ";
			}
			cout << endl;
			cout << i << " :";
			print_word(ct_letters);
			//system("pause"); // press any letter to continue
			
		}
		*/
		while (index < ct_letters.size())
		{
			if (ct_letters[index] == '*' && (index + 1) < ct_letters.size())
			{
				++index;
			}

			if (ct_letters[index] != '*')
			{
				chars_right = 0;
				letter_key = get_letter_key(ct_letters[index]);
				// fix this part 
				for (int d = 0; d < alpha_dict[letter_key].size(); ++d)
				{
					chars_right = 0;
					got_a_word = false;
					for (int f = 0; f < alpha_dict[letter_key][d].size(); ++f)
					{
						if ((index + f) < ct_letters.size())
						{
							if (ct_letters[index + f] == '*')
							{
								break;
							}
							if (ct_letters[index + f] == alpha_dict[letter_key][d][f])
							{
								++chars_right;
							}
							if (chars_right == alpha_dict[letter_key][d].size())
							{
								index += chars_right;
								++words_right;
								got_a_word = true;
							}
						}
					}
				} // end 1st for
				  // end fix this part 
			}
			for (int b = 0; b < key.size(); ++b)
			{
				if (ct_letters[b] == '*')
					got_an_asterisk = true;
			}

			// scan first word 
			int f_letter_key = get_letter_key(ct_letters[0]);
			for (int d = 0; d < alpha_dict[f_letter_key].size(); ++d)
			{
				char_right_first_word = 0;
				for (int f = 0; f < alpha_dict[f_letter_key][d].size(); ++f)
				{
					if (ct_letters[f] == alpha_dict[f_letter_key][d][f])
					{
						++char_right_first_word;
					}
					if (char_right_first_word == alpha_dict[f_letter_key][d].size())
					{
						word_at_beginning = true;
					}
				}
			}

			if (words_right > 1 && word_at_beginning)
			{
				for (int q = 0; q < key.size(); ++q)
				{
					cout << key[q] << ", ";
				}
				cout << endl;
				cout << i << " :";
				print_word(ct_letters);
				//system("pause"); // press any letter to continue
				break;
			}

			if (!got_a_word)
			{
				++index;
			}
		} // end while


	} 




	/*
	
	// brute forcing begins here 
	for (int i = 0; i < 26; ++i)
	{
		for (int j = 0; j < 26; ++j)
		{
			for (int k = 0; k < 26; ++k)
			{
				for (int p = 0; p < 26; ++p)
				{
					vector<vector<char>> decrypted_2darray;
					key[0] = i;
					key[1] = j;
					key[2] = k;
					key[3] = p; 
					decrypted_2darray = decrypt(ct_bin, key); 

					
					vector<char> ct_letters;
					for (int i = 0; i < decrypted_2darray.size(); ++i)
					{
						ct_letters.push_back(bin_to_letter(decrypted_2darray[i]));
					}

					print_word(ct_letters); 
					/*
					//dictionary search here (makes use of alphabetized) 
					int index = 0;
					int chars_right = 0;
					int letter_key = 0; 
					int words_right = 0; 
					// this while loop is messed up .. 
					while (index < ct_bin.size())
					{
						if (ct_letters[index] != '*')
						{
							 
							letter_key = get_letter_key(ct_letters[index]);
							for (int d = 0; d < alpha_dict[letter_key].size(); ++d)
							{ // iterate thru words starting with LETTER_KEY 
							chars_right = 0;
								for (int f = 0; f < alpha_dict[letter_key][d].size(); ++f)
								{
									if (ct_letters[index + f] == alpha_dict[letter_key][d][f])
									{
										++chars_right;
									}
									if (chars_right == alpha_dict[letter_key][d].size() || chars_right == key.size())
									{
										index += chars_right; 
										++words_right;
										break; 
									}
								}
								break; 
							}
							if (words_right >= 1)
							{
							
								print_word(ct_letters); 
								system("pause"); // press any key to continue... 
								break; 
							}

						}
						else
							break; // skip if first decry letter is * 
					} 

				}
			}
		}
	}

	*/








	system("pause");
	return 0; 
}
