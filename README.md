The Efficient String Library
-
As soon as I started learning about bitfields and bitwise operations, I discovered my interest in binary and in bit manipulation. Many thoughts came to me in terms of how to use this knowledge to produce more memory efficient code in C++. 

My first idea was to try and figure out a way to create a more efficient string class, that uses the exact amount of bits needed to store each ASCII character, rather than having 8 bits to store a character with an ASCII value that can fit in 7 bits. 

I did some research on the ability to dynamically change the value of an allocated bitfield during runtime, however, bitfields are allocated during compile-time only, so that wasn't possible.

Afterwards, still trying to pursue my idea of a more efficient string class, I did some more research on the ASCII table, and I realized that, only 7 bits are necessary to represent 128 different characters. The 8th bit was not used for encoding characters in the standard ASCII character set. 

However, the 8th bit has its uses. The 8th bit of the "char" data type helps represent up to 256 different characters. One well-known example of an extended character set is the ISO/IEC 8859 series. Later on, the use of the 8th bit was even more needed. Unicode, while the 8th bit was initially unused in the original 7-bit ASCII character set, it has since found usage in extended character sets and modern Unicode character encodings to represent a broader range of characters from different languages and applications.

However, even if the 8th bit wasn't there, the 7 bit representation of the "char" data type is still useful in many scenarios, particularly for representing English text and basic symbols.

The 7-bit ASCII character set covers 128 different characters, which include:

        - Uppercase English letters (A-Z)
        - Lowercase English letters (a-z)
        - Decimal digits (0-9)
        - Basic punctuation marks and symbols
        - Control characters (e.g., newline, tab, and carriage return)
In the absence of Unicode, 7-bit ASCII characters would suffice for many applications that use only the English language and simple symbols, however it would be insufficient for representing the diverse characters and symbols used in other languages or more complex applications.

The Efficient String Library was created for using only English text and basic symbols. However its limitations would become evident when working with non-English languages and more diverse character sets.

What Is The Efficient String Library?
-
The Efficient String Library is a string library replica, that uses 7-bits for characters in the ASCII table, opposed to the 8 bits in the String Library.

Benefits of using the Efficient String Library:

        - Memory Efficiency: By using only 7 bits per character, you can save a whopping 12.5% memory compared to using 8 bits.
        - Simplified Encoding and Decoding
        - Faster transmission
        - Compatibility with legacy systems

However, these benefits come with the trade-off of a limited character set. Using only 7 bits restricts the user to the original ASCII character set, which may not be suitable for applications requiring non-English characters or more divere symbols. In many modern applications, the advantages of using more advanced character encoding schemes like Unicode, outweigh the benefits of using 7 bits per character. But the Efficient String Library still has its uses regardless.

Memory Efficiency Example
- 
Below is a fragment of code demonstrating the memory efficiency of the Efficient String Library.
```cpp
        int main()
        {
            std::string string_ver{};
            std::ef_string ef_string_ver{};
            for (int i = 0; i < 50000; ++i)
            {
                string_ver += "Hello World";
                ef_string_ver += "Hello World";
            }
            std::cout << "String object size: [" 
                << (string_ver.size() * sizeof(char))
                << "]\n";
            std::cout << "Efficient String object size: ["
                << (ef_string_ver.size() * ef_string_ver.characterSize())
                << "]\n";
        }
```       
Output:

        String object size: [550000]
        Efficient String object size: [481250]

As expected, 12.5% memory efficiency.

How To Use The Efficient String Library?
- 
Simply download the source and the header file, and add them to your project.

        #include "ef_string.h"

How Similar Is It To std::string?
- 
The Efficient String Library is used exactly like the String Library, it has the same member functions, uses and approaches. Very thorough documentation is provided for each function, in order to deliver a simple experience to the user. Below is the full list of member functions implemented in the Efficient String Library.

Member Functions
- 
```cpp
        // Maximum value size_t can store
        static constexpr size_t npos = static_cast<size_t>(-1);

        // Copy Constructor
        ef_string(const ef_string& other);

        // Returns a reverse iterator pointing to the last character of the ef_string.
        // The iterator can be used to modify the contents of the ef_string in reverse order.
        reverse_iterator rbegin();

        // Returns a reverse iterator pointing to the position before the first character of the ef_string.
        // The iterator can be used to modify the contents of the ef_string in reverse order.
        reverse_iterator rend();

        // Returns a constant reverse iterator pointing to the last character of the ef_string.
        // The iterator cannot be used to modify the contents of the ef_string in reverse order.
        const_reverse_iterator rbegin() const;

        // Returns a constant reverse iterator pointing to the position before the first character of the ef_string.
        // The iterator cannot be used to modify the contents of the ef_string in reverse order.
        const_reverse_iterator rend() const;

        // Returns a constant reverse iterator (creverse_iterator) pointing to the last character of the ef_string.
        // The iterator cannot be used to modify the contents of the ef_string in reverse order.
        const_reverse_iterator crbegin() const;

        // Returns a constant reverse iterator (creverse_iterator) pointing to the position before the first character of the ef_string.
        // The iterator cannot be used to modify the contents of the ef_string in reverse order.
        const_reverse_iterator crend() const;

        // Returns the size of one character in the ef_string in bytes
        float characterSize() const;

        // Move Constructor
        ef_string(ef_string&& other) noexcept;

        // Returns true if the ef_string is empty
        bool empty() const;

        // Copy Assignment Operator
        ef_string& operator=(const ef_string& other);

        // Copy Assignment Operator
        ef_string& operator=(char other);

        // Copy Assignment Operator
        ef_string& operator=(const std::string& temp);

        // Move Assignment Operator
        ef_string& operator=(ef_string&& other) noexcept;

        // Returns concatenation of ef_strings
        ef_string& operator+=(const ef_string& other);

        // Returns concatenation of ef_strings
        ef_string& operator+=(const std::string& other);

        // Returns concatenation of ef_strings
        ef_string& operator+=(const char* other);

        friend ef_string operator+(const ef_string& lhs, const ef_string& rhs);

        // Default Constructor, sets ef_string to empty
        ef_string() = default;

        // Initializes ef_string to arg
        ef_string(const char* temp);

        // Initializes ef_string to argm
        ef_string(std::string temp);

        // Initializes ef_string to "n" count of source
        ef_string(const char* source, size_t n);

        // Initializes ef_string to "count" number of "c"
        ef_string(size_t count, char c);

        // Returns character at idx
        char operator[](int idx) const;

        // Returns character at idx
        StringBit& operator[](int idx);

        // Returns reference to character at idx
        StringBit& at(int idx);

        // Clears ef_string
        void clear();

        // Returns if ef_strings are equal
        bool operator==(const ef_string& other) const;

        // Returns if ef_string and string are equal
        bool operator==(const std::string& other) const;


        // Returns if ef_string and other are equal
        bool operator==(const char* other) const;

        // Returns if ef_strings are not equal
        bool operator!=(const ef_string& other) const;

        // Returns if ef_string and string are not equal
        bool operator!=(const std::string& other) const;

        // Returns if ef_string and other are not equal
        bool operator!=(const char* other) const;

        // Inserts the content of ef_string in ostream
        friend std::ostream& operator<<(std::ostream& os, const ef_string& temp);

        // Extracts user input from istream into ef_string
        friend std::istream& operator>>(std::istream& in, ef_string& temp);

        // Inserts the content of ef_string in ostream
        friend std::ofstream& operator<<(std::ofstream& os, const ef_string& temp);

        // Extracts user input from istream into ef_string
        friend std::ifstream& operator>>(std::ifstream& in, ef_string& temp);

        // Returns a const char* representation of ef_string
        const char* c_str() const;

        // Returns true if lhs lexicographically greater than rhs
        friend bool operator > (const ef_string& lhs, const ef_string& rhs);

        // Returns true if lhs lexicographically smaller than rhs
        friend bool operator < (const ef_string& lhs, const ef_string& rhs);

        // Returns true if lhs lexicographically smaller or equal to rhs
        friend bool operator <= (const ef_string& lhs, const ef_string& rhs);

        // Returns true if lhs lexicographically greater or equal to rhs
        friend bool operator >= (const ef_string& lhs, const ef_string& rhs);

        // Returns size of ef_string
        size_t size() const;

        // Returns the total amount of bytes allocated for ef_string object
        size_t capacity() const;

        // Returns const char * representation of ef_string
        operator const char* ();

        // Sets a new capactiy for the ef_string
        void reserve(size_t new_capacity);

        // Reduce capactiy to fit the current size of the ef_string
        void shrink_to_fit();

        // Changes the size of the string
        void resize(size_t new_size);

        // Appends a character to the string
        void push_back(char c);

        // Appends a character to the end of the string
        void append(ef_string& to_append);

        // Appends a character to the end of the string
        void append(std::string& to_append);

        // Appends a character to the end of the string
        void append(const char* to_append);

        // Removes the last character from the string
        void pop_back();

        // Removes the first character from the string
        void pop_front();

        // Returns a substring of the ef_string
        ef_string substr(size_t pos = 0, size_t count = std::string::npos) const;

        // Returns the position of the first occurrence of str if found in ef_string
        // pos is starting position to look from
        size_t find(const ef_string& str, size_t pos = 0) const;

        // Returns the position of the first occurrence of ch if found in ef_string
        // pos is starting position to look from
        size_t find(char ch, size_t pos = 0) const;

        // Trims trailing whitespace from beginning and end ef_string
        void trimTrailingWhitespace();

        // Returns std::string represenation of ef_string
        operator std::string();

        // Returns the index of the first character in the ef_string that is not equal to "c".
        // If no such character is found, returns std::ef_string::npos.
        size_t find_first_not_of(char c) const;

        // Returns the index of the last character in the ef_string that is not equal to "c".
        // If no such character is found, returns std::ef_string::npos.
        size_t find_last_not_of(char c) const;

        // Returns the index of the first occurrence of the character "c" in the ef_string.
        // If "c" is not found, returns std::ef_string::npos.
        size_t find_first_of(char c) const;

        // Returns the index of the last occurrence of the character "c" in the ef_string.
        // If "c" is not found, returns std::ef_string::npos.
        size_t find_last_of(char c) const;

        // Returns reference to last character in ef_string
        StringBit& back();

        // Returns reference to first character in ef_string
        StringBit& front();

        // Erases "count" number of characters starting from pos
        // Throw std::out_of_range("Subscript Out Of Rang") if pos is bigger or equal to size of ef_string
        ef_string& erase(size_t pos, size_t count);

        // Returns an iterator pointing to the beginning of the ef_string.
        // The iterator can be used to modify the contents of the ef_string.
        iterator begin();

        // Returns an iterator pointing to the end (one past the last element) of the ef_string.
        // The iterator can be used to modify the contents of the ef_string.
        iterator end();

        // Returns a constant iterator pointing to the beginning of the ef_string.
        // The iterator cannot be used to modify the contents of the ef_string.
        const_iterator begin() const;

        // Returns a constant iterator pointing to the end (one past the last element) of the ef_string.
        // The iterator cannot be used to modify the contents of the ef_string.
        const_iterator end() const;

        // Returns a constant iterator (citerator) pointing to the beginning of the ef_string.
        // The iterator cannot be used to modify the contents of the ef_string.
        const_iterator cbegin() const;

        // Returns a constant iterator (citerator) pointing to the end (one past the last element) of the ef_string.
        // The iterator cannot be used to modify the contents of the ef_string.
        const_iterator cend() const;

        // Returns the length of the ef_string
        size_t length() const;

        // Returns the max size of the ef_string
        size_t max_size() const;

        // Swaps contents of other with current ef_string
        void swap(ef_string& other);

        // Returns ef_string representation in string
        string inString() const;

        // Assigns the C-style string "other" as new content to the ef_string
        void assign(const char* other);

        // Assigns the string "other" as new content to the ef_string
        void assign(std::string other);

        // Inserts the contents of "str" into the current ef_string at the specified "pos".
        // If "pos" is greater than the size of ef_string, throws std::out_of_range("Pos is out of range").
        ef_string& insert(size_t pos, const ef_string& str);

        // Inserts a substring of "str" specified by "subpos" and "sublen" into the current ef_string at the specified "pos".
        // If "pos" is greater than the size of ef_string, throws std::out_of_range("Pos is out of range").
        ef_string& insert(size_t pos, const ef_string& str, size_t subpos, size_t sublen);

        // Inserts the C-style string "s" into the current ef_string at the specified "pos".
        // If "pos" is greater than the size of ef_string, throws std::out_of_range("Pos is out of range").
        ef_string& insert(size_t pos, const char* s);

        // Inserts the first "n" characters of the C-style string "s" into the current ef_string at the specified "pos".
        // If "pos" is greater than the size of ef_string, throws std::out_of_range("Pos is out of range").
        ef_string& insert(size_t pos, const char* s, size_t n);

        // Inserts "n" occurrences of the character "c" into the current ef_string at the specified "pos".
        // If "pos" is greater than the size of ef_string, throws std::out_of_range("Pos is out of range").
        ef_string& insert(size_t pos, size_t n, char c);

        // Returns pointer to the underlying character array of the ef_string
        char* data();

        // Returns the capacity of the ef_string
        size_t reserve() const;

        // Replaces characters in ef_string starting at "pos" for "len" with characters from the beginning of "str".
        // If "pos" is greater than or equal to the size of ef_string, throws std::out_of_range("Pos is out of range").
        ef_string& replace(size_t pos, size_t len, const ef_string& str);

        // Replaces characters in ef_string starting at "pos" for "len" with a substring of "str" denoted by "subpos" and "sublen".
        // If "pos" is greater than or equal to the size of ef_string, throws std::out_of_range("Pos is out of range").
        ef_string& replace(size_t pos, size_t len, const ef_string& str, size_t subpos, size_t sublen);

        // Replaces characters in ef_string starting at "pos" for "len" with characters from the C-style string "s".
        // If "pos" is greater than or equal to the size of ef_string, throws std::out_of_range("Pos is out of range").
        ef_string& replace(size_t pos, size_t len, const char* s);

        // Replaces characters in ef_string starting at "pos" for "len" with "n" characters from the beginning of the C-style string "s".
        // If "pos" is greater than or equal to the size of ef_string, throws std::out_of_range("Pos is out of range").
        ef_string& replace(size_t pos, size_t len, const char* s, size_t n);

        // Replaces characters in ef_string starting at "pos" for "len" with "n" occurrences of the character "c".
        // If "pos" is greater than or equal to the size of ef_string, throws std::out_of_range("Pos is out of range").
        ef_string& replace(size_t pos, size_t len, size_t n, char c);

        // Returns the index of the beginning of the last occurrence of "str" in the ef_string.
        // If "pos" is specified, the search begins from the given index and moves backward in the ef_string.
        // If no occurrence is found, returns std::ef_string::npos.
        size_t rfind(const ef_string& str, size_t pos = npos) const;

        // Returns the index of the beginning of the last occurrence of the C-style string "s" in the ef_string.
        // If "pos" is specified, the search begins from the given index and moves backward in the ef_string.
        // If no occurrence is found, returns std::ef_string::npos.
        size_t rfind(const char* s, size_t pos = npos) const;

        // Returns the index of the occurrence of the C-style string "s" with a size of "n" in the first "pos" characters of ef_string.
        // Searches backward in the ef_string.
        // If no occurrence is found within the specified range, returns std::ef_string::npos.
        size_t rfind(const char* s, size_t pos, size_t n) const;

        // Returns the index of the last occurrence of the character "c" in the ef_string.
        // If "pos" is specified, the search begins from the given index and moves backward in the ef_string.
        // If no occurrence is found, returns std::ef_string::npos.
        size_t rfind(char c, size_t pos = npos) const;

        // Copies a substring from the ef_string starting at the "pos" index with a maximum length of "len" into the "destination" C-style string.
        // If "pos" is not specified, the copy starts from the beginning of the ef_string.
        // Returns the number of characters copied, not including the null-terminator.
        size_t copy(char* destination, size_t len, size_t pos = 0) const;

        // Compares current ef_string with str, returns True if they are the same
        bool compare(ef_string& str) const;

        // Compares current ef_string with str, returns True if they are the same
        bool compare(std::string& str) const;

        // Compares current ef_string with str, returns True if they are the same
        bool compare(const char* str) const;

        // Finds and returns the index of the first occurrence of a character not present in the given C-style string "s".
        // If "pos" is specified, the search begins from the given index in the ef_string.
        // If no character is found, returns std::ef_string::npos.
        size_t find_first_not_of(const char* s, size_t pos = 0) const;

        // Finds and returns the index of the first occurrence of a character not present in the given C-style string "s"
        // within the range [pos, pos + n).
        // If no character is found within the specified range, returns std::ef_string::npos.
        size_t find_first_not_of(const char* s, size_t pos, size_t n) const;

        // Finds and returns the index of the first occurrence of a character not present in the given std::string "str".
        // If "pos" is specified, the search begins from the given index in the ef_string.
        // If no character is found, returns std::ef_string::npos.
        size_t find_first_not_of(const std::string& str, size_t pos = 0) const;

        // Finds and returns the index of the first occurrence of a character not present in the given std::string "str"
        // within the range [pos, pos + n).
        // If no character is found within the specified range, returns std::ef_string::npos.
        size_t find_first_not_of(const std::string& str, size_t pos, size_t n) const;

        // Finds and returns the index of the first occurrence of a character not present in the given ef_string "str".
        // If "pos" is specified, the search begins from the given index in the ef_string.
        // If no character is found, returns std::ef_string::npos.
        size_t find_first_not_of(const std::ef_string& str, size_t pos = 0) const;

        // Finds and returns the index of the first occurrence of a character not present in the given ef_string "str"
        // within the range [pos, pos + n).
        // If no character is found within the specified range, returns std::ef_string::npos.
        size_t find_first_not_of(const std::ef_string& str, size_t pos, size_t n) const;

        // Finds and returns the index of the last occurrence of a character not present in the given C-style string "s".
        // If "pos" is specified, the search begins from the given index and moves backward in the ef_string.
        // If no character is found, returns std::ef_string::npos.
        size_t find_last_not_of(const char* s, size_t pos = npos) const;

        // Finds and returns the index of the last occurrence of a character not present in the given C-style string "s"
        // within the range [pos - n + 1, pos].
        // If no character is found within the specified range, returns std::ef_string::npos.
        size_t find_last_not_of(const char* s, size_t pos, size_t n) const;

        // Finds and returns the index of the last occurrence of a character not present in the given std::string "str".
        // If "pos" is specified, the search begins from the given index and moves backward in the ef_string.
        // If no character is found, returns std::ef_string::npos.
        size_t find_last_not_of(const std::string& str, size_t pos = npos) const;

        // Finds and returns the index of the last occurrence of a character not present in the given std::string "str"
        // within the range [pos - n + 1, pos].
        // If no character is found within the specified range, returns std::ef_string::npos.
        size_t find_last_not_of(const std::string& str, size_t pos, size_t n) const;

        // Finds and returns the index of the last occurrence of a character not present in the given ef_string "str".
        // If "pos" is specified, the search begins from the given index and moves backward in the ef_string.
        // If no character is found, returns std::ef_string::npos.
        size_t find_last_not_of(const std::ef_string& str, size_t pos = npos) const;

        // Finds and returns the index of the last occurrence of a character not present in the given ef_string "str"
        // within the range [pos - n + 1, pos].
        // If no character is found within the specified range, returns std::ef_string::npos.
        size_t find_last_not_of(const std::ef_string& str, size_t pos, size_t n) const;

        // Finds and returns the index of the first occurrence of a character present in the given C-style string "s".
        // If "pos" is specified, the search begins from the given index in the ef_string.
        // If no character is found, returns std::ef_string::npos.
        size_t find_first_of(const char* s, size_t pos = 0) const;

        // Finds and returns the index of the first occurrence of a character present in the given C-style string "s"
        // within the range [pos, pos + n).
        // If no character is found within the specified range, returns std::ef_string::npos.
        size_t find_first_of(const char* s, size_t pos, size_t n) const;

        // Finds and returns the index of the first occurrence of a character present in the given std::string "str".
        // If "pos" is specified, the search begins from the given index in the ef_string.
        // If no character is found, returns std::ef_string::npos.
        size_t find_first_of(const std::string& str, size_t pos = 0) const;

        // Finds and returns the index of the first occurrence of a character present in the given std::string "str"
        // within the range [pos, pos + n).
        // If no character is found within the specified range, returns std::ef_string::npos.
        size_t find_first_of(const std::string& str, size_t pos, size_t n) const;

        // Finds and returns the index of the first occurrence of a character present in the given ef_string "str".
        // If "pos" is specified, the search begins from the given index in the ef_string.
        // If no character is found, returns std::ef_string::npos.
        size_t find_first_of(const std::ef_string& str, size_t pos = 0) const;

        // Finds and returns the index of the first occurrence of a character present in the given ef_string "str"
        // within the range [pos, pos + n).
        // If no character is found within the specified range, returns std::ef_string::npos.
        size_t find_first_of(const std::ef_string& str, size_t pos, size_t n) const;

        // Finds and returns the index of the last occurrence of a character present in the given C-style string "s".
        // If "pos" is specified, the search begins from the given index and moves backward in the ef_string.
        // If no character is found, returns std::ef_string::npos.
        size_t find_last_of(const char* s, size_t pos = npos) const;

        // Finds and returns the index of the last occurrence of a character present in the given C-style string "s"
        // within the range [pos - n + 1, pos].
        // If no character is found within the specified range, returns std::ef_string::npos.
        size_t find_last_of(const char* s, size_t pos, size_t n) const;

        // Finds and returns the index of the last occurrence of a character present in the given std::string "str".
        // If "pos" is specified, the search begins from the given index and moves backward in the ef_string.
        // If no character is found, returns std::ef_string::npos.
        size_t find_last_of(const std::string& str, size_t pos = npos) const;

        // Finds and returns the index of the last occurrence of a character present in the given std::string "str"
        // within the range [pos - n + 1, pos].
        // If no character is found within the specified range, returns std::ef_string::npos.
        size_t find_last_of(const std::string& str, size_t pos, size_t n) const;

        // Finds and returns the index of the last occurrence of a character present in the given ef_string "str".
        // If "pos" is specified, the search begins from the given index and moves backward in the ef_string.
        // If no character is found, returns std::ef_string::npos.
        size_t find_last_of(const std::ef_string& str, size_t pos = npos) const;

        // Finds and returns the index of the last occurrence of a character present in the given ef_string "str"
        // within the range [pos - n + 1, pos].
        // If no character is found within the specified range, returns std::ef_string::npos.
        size_t find_last_of(const std::ef_string& str, size_t pos, size_t n) const;
        
        // Returns a copy of the ef_string with all alpha characters in upper case
        ef_string toUpper() const;

        // Returns a copy of the ef_string with all alpha characters in lower case
        ef_string toLower() const;
```        
Global Functions
- 
```cpp
        // Extracts from istream until delimiter is met
        inline std::istream& getline(std::istream& is, ef_string& str, char delim = '\n');

        // Swaps contents of lhs and rhs ef_strings
        inline void swap(ef_string& lhs, ef_string& rhs);

        // Compares lhs and rhs lexicographically
        inline bool compare(ef_string& lhs, ef_string& rhs);

        // Compares lhs and rhs lexicographically
        inline bool compare(ef_string& lhs, std::string& rhs);

        // Compares lhs and rhs lexicographically
        inline bool compare(ef_string& lhs, const char* rhs);

        // Returns ef_string representation of numberic value
        inline ef_string to_efstring(size_t value);

        // Returns integer representation of ef_string
        // Stops at occurrence if first none-integer
        inline int ef_stoi(ef_string to_convert);

        // Returns long representation of ef_string
        inline long ef_stol(ef_string to_convert);

        // Returns long long representation of ef_string
        inline long long ef_stoll(ef_string to_convert);

        // Returns unsigned long representation of ef_string
        inline unsigned long ef_stoul(ef_string to_convert);

        // Returns unsigned long long representation of ef_string
        inline unsigned long long ef_stoull(ef_string to_convert);

        // Returns float representation of ef_string
        inline float ef_stof(ef_string to_convert);

        // Returns double representation of ef_string
        inline double ef_stod(ef_string to_convert);
```    

Final Words
-
I hope that this library can be of use to you! Have fun!

