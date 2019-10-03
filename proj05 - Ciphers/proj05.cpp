#include<iostream>
using std::cout; using std::cin; using std::endl;
#include<string>
using std::string; 
/*

Chris Nastoski
10/14/2017
Section 012
Project 05

Beaufort Cipher: http://practicalcryptography.com/ciphers/classical-era/beaufort/
Vigenère Cipher: http://practicalcryptography.com/ciphers/classical-era/vigenere-gronsfeld-and-autokey/

A program that takes in a plaintext input and makes operations with characters with the key provided to create a ciphered string
based on the two ciphers provided above. 

*/
const string alphabet = "abcdefghijklmnopqrstuvwxyz";

//inputs: int amt - takes in the amount of times to rotate the string left.
//		  string line - takes in the string to be rotated.
//Function recreates the string provided with the first letter being moved to the last position.
//returns: string line - the rotated string.
string rotate_left(int amt, string line) {
	if (amt >= 0) {//error checking for negative integers
		int i = 0;
		long end = line.size();//sets the last index to use
		amt = amt % line.size();//make the code more efficient if the amt>string.length()

		while (i < amt) {//keeps repeating the left rotation until it reaches the amt requested
			line = line.substr(1, end) + line.substr(0, 1);
			i++;
		}
		return line;//returns rotated string
	}
	else
		return line;
}

//inputs: char plain - takes in a plaintext letter to create a left rotated alphabet
//		  char key - a letter to use as the index of the rotated alphabet	
//Function creates the amt to rotate the alphabet and uses they key as the index of the 
//new alphabet to find a Vigenère ciphered letter
//returns: char rot[index] - the ciphered letter
char vigenere_letter(char plain, char key) {
	if (((isalpha(plain)) && (islower(plain))) && (isalpha(key) && islower(key))) {
		long amt = plain - 'a', index = key - 'a'; //creates the rotation amt and the index 
		string rot = rotate_left(amt, alphabet);//calls rotate function to create new alphabet


		return rot[index];
	}

	else//error checking for both the key and plain to be lowercase and alphabetic
		return plain;
}


//This function is very similar to the Vigenère_letter fn, except that it uses the 
//index of the key in the rotated alphabed as the index of the alphabet.
char beaufort_letter(char plain, char key) {
	if (((isalpha(plain)) && (islower(plain))) && (isalpha(key) && islower(key))) {
		long amt = plain - 'a';
		string rot = rotate_left(amt, alphabet);
		char index = rot.find(key);//finds index of the key in rotated alphabet


		return alphabet[index];//uses that index to return the Beaufort letter
	}

	else
		return plain;
}


//Inputs: string plain - the string to be ciphered
//		  string key - the key to cipher each letter. is repeated if it is shorter than the plain
//Function calls the beaufort_letter fn for each char in plain and key to create a ciphered string.
//Returns: string cipher - the ciphered string
string encode_beaufort(string plain, string key) {
	string cipher = "",plaintext = "";//initilize two emty strings
	int i = 0;

	for (char c : plain) {//iterates through each char in plain and create a string with only lowercase alphabetic letters
		if (isalpha(c) && islower(c))
			plaintext += c;
	}
	if (plaintext.length() > key.length()) {
		while ((plaintext.length() / key.length()) > 1)
			key += key;//keeps repeating key until it cannot add another whole key string

		if (plaintext.length() % key.length()) {
			key += key.substr(0, plaintext.length() % key.length());
			//adds the remaining letters until the key size is the same as the plaintext
		}	
	}
	if (plaintext.length() < key.length())//cuts off the key if it is too large
		key = key.substr(0, plaintext.length());

	for (char c : plaintext) {//ciphers each char by char
		cipher += beaufort_letter(plaintext[i], key[i]);
		i++;
	}
	
	return cipher;
}

//Same as encode_beaufort fn, except it uses Vigenère cipher
string encode_vigenere(string plain, string key) {
	string cipher = "", plaintext = "";
	int i = 0;

	for (char c : plain) {
		if (isalpha(c) && islower(c))
			plaintext += c;
	}
	if (plaintext.length() > key.length()) {
		while ((plaintext.length() / key.length()) > 1)
			key += key;
		if (plaintext.length() % key.length()) {
			key += key.substr(0, plaintext.length() % key.length());
		}

	}
	if (plaintext.length() < key.length())
		key = key.substr(0, plaintext.length());

	for (char c : plaintext) {
		cipher += vigenere_letter(plaintext[i], key[i]);
		i++;
	}

	return cipher;



}

int main() {
	int case_number;
	cin >> case_number;

	switch (case_number) {

	case 1: {
		int rotations;
		cin >> rotations;
		string s;
		cin >> s;
		cout << rotate_left(rotations, s) << endl;
		break;
	}

	case 2: {
		char plain_letter;
		char key_letter;
		cin >> plain_letter >> key_letter;
		cout << beaufort_letter(plain_letter, key_letter) << endl;
		break;
	}

	case 3: {
		char plain_letter;
		char key_letter;
		cin >> plain_letter >> key_letter;
		cout << vigenere_letter(plain_letter, key_letter) << endl;
		break;
	}

	case 4: {
		string plain_text;
		string key;
		cin.ignore(100, '\n');
		getline(cin, plain_text);
		getline(cin, key);
		cout << encode_beaufort(plain_text, key) << endl;
		break;
	}

	case 5: {
		string plain_text;
		string key;
		cin.ignore(100, '\n');
		getline(cin, plain_text);
		getline(cin, key);
		cout << encode_vigenere(plain_text, key) << endl;
		break;
	}

	} // of switch
} // of main
