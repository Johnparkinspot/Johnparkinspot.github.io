#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


using std::string;
using std::cout;
using std::cin;
using std::endl;

template <typename T>
void print(std::vector<T> v)
{
    for(int i = 0; i < v.size(); ++i)
    {
        cout << v[i] << " ";
    }
    cout << endl;
}

// checks if the two vectors are equal
template<typename T>
bool two_vectors_equal(const std::vector<T> v1, const std::vector<T> v2)
{
    int num_correct = 0;
    if(v1.size() != v2.size())
    {
        return false;
    }
    for(int i = 0; i < v1.size(); ++i)
    {
        if(v1[i] == v2[i])
        {
            ++num_correct;
        }
    }
    if(num_correct == v1.size())
    {
        return true;
    }
    else return false;
}

void bubble_sort(std::vector<char> & c)
{
    if(c.size() == 1 || c.size() == 0)
    {
        return;
    }
    int result;
    char temp1[1];
    char temp2[2];
    for(int i = 0; i < c.size(); ++i)
    {
        for(int j = i+1; j < c.size(); ++j) // important that it is i + 1
        {
            temp1[0] = c[i];
            temp2[0] = c[j];
            result = strcmp(temp1,temp2);
            if(result > 0 || result == 0)
            {
                std::swap(c[i],c[j]);
                //cout << i << ", " << j;
                //print(c);
            }
        }
    }
}

//1.1 works
bool check_if_all_unique_characters(const string s)
{
    std::vector<char> c;
    for(int i =0 ; i < s.length(); ++i)
    {
        for(int j = 0; j < c.size(); ++j)
        {
            if(c[j] == s[i])
            {
                return false;
            }
        }
        c.push_back(s[i]);
    }
    return true;
}


//1.2 works
void reverse_null_terminated_string(string & s)
{
    string temp = s;
    int j = 0;
    for(int i = temp.length() - 1; i >= 0; --i)
    {
        s[j] = temp[i];
        ++j;
    }
}

//1.3 works
// given 2 strings write a method to decide if one is a permutation of the other
bool two_strings_permute_of_each_other(const string s1, const string s2)
{
    std::vector<char> c1, c2;
    if(s1.length() != s2.length())
    {
        return false;
    }
    for(int i = 0; i < s1.length(); ++i)
    {
        c1.push_back(s1[i]);
        c2.push_back(s2[i]);
    }
    bubble_sort(c1);
    bubble_sort(c2);
    if(two_vectors_equal(c1,c2))
    {
        return true;
    }
    else
        return false;

}

//1.4 works
//replace all spaces in string with %20
void replace_space_with_percent_twenty(string & s)
{
    std::vector<std::vector<char> > v;
    bool hit_char = false;
    int word_index = 0;
    bool not_a_space;
    int index = -1;
    std::vector<char> temp;

    for(int i = 0; i < s.length(); ++i)
    {
        if(isspace(char(s[i])) == 0)
        {  // hit chars
            temp.push_back(char(s[i]));
            if(temp.size() == 1) // if only has first letter of word
            {
                v.push_back(std::vector<char>());
                ++index;
            }
            v[index].push_back(char(s[i])); // tokenized the words
        }
        else
        {
            temp = std::vector<char>(); //
        }
    }

    string replace = "%20";
    string final;
    if(isspace(char(s[0])))
    {
        final += replace;
    }
    int k = 0;
    for(int i = 0; i < v.size(); ++i)
    {
        for(int j = 0; j < v[i].size(); ++j)
        {
            final += v[i][j];
        }
        if(isspace(char(s[s.size()-1]))) // check if have to append %20 at the end
        {
            final += replace;
        }
        else
        {
            if(k < v.size()-1)
            {
                final += replace;
                ++k;
            }
        }

    }

    s = final;

}
//1001001
//1101101 hit char
//aa bb c

int main()
{
    string s = "hello world";

    replace_space_with_percent_twenty(s);
    cout << s << endl;
    return 0;
}
