#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <iostream>
#include <exception>
#include <crtdbg.h>
#include <cstring>
#include <utility>
#include <string>
#include <fstream>
#include <sstream>
#include "ef_string.h"



namespace std
{
    std::ostream& operator<<(std::ostream& os, const StringBit& temp)
    {

        os << static_cast<char>(temp.a);
        return os;
    }

    ef_string operator+(const ef_string& lhs, const ef_string& rhs)
    {
        ef_string result(lhs);

        for (size_t i = 0; i < rhs.m_size; ++i) {

            result.m_bits.push_back(rhs.m_bits[i]);

        }

        result.m_size += rhs.m_size;

        return result;
    }

    std::ostream& operator<<(std::ostream& os, const ef_string& temp)
    {

        auto size = temp.m_size;

        for (auto i = 0u; i < size; ++i)
        {
            os << static_cast<char>(temp.m_bits[i].a);
        }


        return os;
    }

    std::istream& operator>>(std::istream& in, ef_string& temp)
    {
        if (isspace(in.peek()))
        {
            in.get();
        }

        temp.clear();

        temp.m_bits.clear();
        temp.m_size = 0;

        while (!isspace(in.peek()))
        {
            temp.m_bits.push_back(StringBit(in.get()));
            ++temp.m_size;
        }

        return in;
    }

    std::ofstream& operator<<(std::ofstream& os, const ef_string& temp)
    {

        for (auto i = 0u; i < temp.m_size; ++i)
        {
            os << static_cast<char>(temp.m_bits[i].a);
        }


        return os;
    }

    std::ifstream& operator>>(std::ifstream& in, ef_string& temp)
    {
        if (isspace(in.peek()))
        {
            in.get();
        }

        temp.m_bits.clear();
        temp.m_size = 0;

        while (!isspace(in.peek()) && !in.eof())
        {
            temp.m_bits.push_back(StringBit(in.get()));
            ++temp.m_size;
        }

        return in;
    }

    bool operator>(const ef_string& lhs, const ef_string& rhs)
    {

        size_t min_size = std::min(lhs.m_size, rhs.m_size);

        for (auto i = 0u; i < min_size; ++i) {

            if (lhs[i] > rhs[i]) {
                return true;
            }
            else if (lhs[i] < rhs[i]) {
                return false;
            }
        }

        // If the strings are the same up to min_size, the longer string is considered greater.
        return lhs.m_size > rhs.m_size;
    }

    bool operator<(const ef_string& lhs, const ef_string& rhs)
    {
        size_t min_size = std::min(lhs.m_size, rhs.m_size);

        for (auto i = 0u; i < min_size; ++i) {
            if (lhs[i] < rhs[i]) {
                return true;
            }
            else if (lhs[i] > rhs[i]) {
                return false;
            }
        }

        return lhs.m_size < rhs.m_size;
    }

    bool operator<=(const ef_string& lhs, const ef_string& rhs)
    {
        return !(lhs > rhs);
    }

    bool operator>=(const ef_string& lhs, const ef_string& rhs)
    {
        return !(lhs < rhs);
    }

    void ef_string::fill(const char* temp)
    {
        if (temp != nullptr)
        {
            auto size = strlen(temp) + 1;


            for (auto i = 0u; i < size; ++i)
            {
                m_bits.push_back(StringBit(temp[i]));
            }
            m_size = size - 1;
            m_capacity = m_size;
        }
    }

    ef_string::ef_string(const ef_string& other)
    {
        *this = other;
    }



    float ef_string::characterSize() const
    {

        return 0.875f;

    }

    ef_string::ef_string(ef_string&& other) noexcept
    {
        *this = move(other);
    }

    bool ef_string::empty() const
    {
        return m_size == 0;
    }

    ef_string& ef_string::operator=(const ef_string& other)
    {
        if (this != &other)
        {

            m_bits = other.m_bits;
            m_size = other.m_size;
            m_capacity = other.m_capacity;
        }


        return *this;
    }

    ef_string& ef_string::operator=(const std::string& temp)
    {
        ef_string other(temp.c_str());

        m_bits = other.m_bits;
        m_size = other.m_size;
        m_capacity = other.m_capacity;



        return *this;
    }

    ef_string& ef_string::operator=(ef_string&& other) noexcept
    {
        if (this != &other)
        {

            m_bits = move(other.m_bits);
            m_size = other.m_size;
            m_capacity = other.m_capacity;
            other.m_size = 0;
            other.m_capacity = 0;
        }


        return *this;
    }

    ef_string& ef_string::operator+=(const ef_string& other)
    {

        for (auto i = 0; i < other.m_size; ++i)
        {
            m_bits.push_back(other.m_bits[i]);
        }

        m_size = m_bits.size();
        m_capacity = m_bits.capacity();

        return *this;
    }

    ef_string& ef_string::operator+=(const string& other)
    {
        auto size = other.length();
        for (auto i = 0; i < size; ++i)
        {
            m_bits.push_back(StringBit(other[i]));
        }

        m_size = m_bits.size();
        m_capacity = m_bits.capacity();

        return *this;
    }

    ef_string& ef_string::operator+=(const char* other)
    {
        auto size = strlen(other) + 1;
        for (auto i = 0; i < size; ++i)
        {
            m_bits.push_back(StringBit(other[i]));
        }

        m_size = m_bits.size();
        m_capacity = m_bits.capacity();

        return *this;
    }

    ef_string::ef_string(const char* temp)
    {
        fill(temp);
    }



    ef_string::ef_string(std::string temp)
    {
        fill(temp.c_str());
    }

    ef_string::ef_string(const char* source, size_t n)
    {
        for (size_t i = 0; i < n; ++i) {
            m_bits.push_back(static_cast<StringBit>(source[i]));
        }
        m_size = n;
    }

    ef_string::ef_string(size_t count, char c)
    {
        m_bits = vector<StringBit>(count, c);
        m_size = count;
    }

    char ef_string::operator[](int idx) const
    {
        if (idx < 0 || static_cast<unsigned int>(idx) >= (m_size - 1))
        {
            _RPTF0(_CRT_ASSERT, "Subscript Out Of Range");
            throw out_of_range("Subscript Out Of Range");
        }

        return static_cast<char>(m_bits[idx].a);
    }

    StringBit& ef_string::operator[](int idx)
    {
        if (idx < 0 || static_cast<unsigned int>(idx) >= (m_size - 1))
        {
            _RPTF0(_CRT_ASSERT, "Subscript Out Of Range");
            throw out_of_range("Subscript Out Of Range");
        }

        return m_bits[idx];
    }

    StringBit& ef_string::at(int idx)
    {
        if (idx < 0 || static_cast<unsigned int>(idx) >= (m_size - 1))
        {
            _RPTF0(_CRT_ASSERT, "Subscript Out Of Range");
            throw out_of_range("Subscript Out Of Range");
        }

        return m_bits[idx];
    }

    void ef_string::clear()
    {

        m_bits.clear();
        m_size = 0;
        m_capacity = 0;
    }

    bool ef_string::operator==(const ef_string& other) const
    {

        if (m_size == other.m_size)
        {
            bool check{ true };
            for (auto i = 0u; i < m_size; ++i)
            {
                if (m_bits[i] != other.m_bits[i])
                {
                    check = false;
                    break;
                }
            }
            return check;
        }

        return false;
    }

    bool ef_string::operator==(const std::string& other) const
    {
        return this->operator==(ef_string(other));
    }

    bool ef_string::operator==(const char* other) const
    {
        return this->operator==(ef_string(other));
    }

    bool ef_string::operator!=(const ef_string& other) const
    {
        return !(*this == other);
    }

    bool ef_string::operator!=(const std::string& other) const
    {
        return this->operator!=(ef_string(other.c_str()));
    }

    bool ef_string::operator!=(const char* other) const
    {
        return this->operator!=(ef_string(other));
    }

    const char* ef_string::c_str() const
    {
        std::ostringstream stream;
        for (const auto& bit : m_bits) {
            stream << static_cast<char>(bit.a & 0x7F); // extract the 7-bit field and cast to char
        }
        std::string str = stream.str();
        std::unique_ptr<char[]> cstr(new char[str.length() + 1]);
        std::strcpy(cstr.get(), str.c_str());
        return cstr.release();
    }

    size_t ef_string::size() const
    {
        return m_size;
    }

    size_t ef_string::capacity() const
    {
        return m_bits.capacity();
    }



    ef_string::operator const char* ()
    {
        return c_str();
    }



    void ef_string::reserve(size_t new_capacity)
    {
        m_capacity = new_capacity;
        m_bits.reserve(m_capacity);
    }

    void ef_string::shrink_to_fit()
    {
        m_capacity = m_size;
        m_bits.shrink_to_fit();
    }

    void StringBit::operator=(char temp)
    {
        a = static_cast<int>(temp);
    }

    bool StringBit::operator==(const StringBit& other) const
    {
        return a == other.a;
    }

    bool StringBit::operator==(char temp) const
    {
        return static_cast<char>(a) == temp;
    }

    bool StringBit::operator!=(char temp) const
    {
        return static_cast<char>(a) != temp;
    }

    bool StringBit::operator!=(const StringBit& other) const
    {
        return a != other.a;
    }

    StringBit::operator char()
    {
        return static_cast<char>(a);
    }

    void ef_string::resize(size_t new_size)
    {
        if (new_size > 0)
        {
            m_bits.resize(new_size);
            m_size = new_size;
            m_capacity = new_size;
        }
    }

    void ef_string::push_back(char c)
    {
        ++m_size;
        ++m_capacity;
        m_bits.push_back(StringBit(c));
    }

    void ef_string::append(ef_string& to_append)
    {
        *this += to_append;
    }

    void ef_string::append(std::string& to_append)
    {
        *this += to_append.c_str();
    }

    void ef_string::append(const char* to_append)
    {
        *this += to_append;
    }

    void ef_string::pop_back()
    {
        if (m_size > 0)
        {
            --m_size;
            m_bits.pop_back();
            --m_capacity;
        }
    }

    void ef_string::pop_front()
    {
        if (m_size > 0)
        {
            --m_size;
            m_bits.erase(m_bits.begin());
            --m_capacity;
        }
    }

    ef_string ef_string::substr(size_t pos, size_t count) const
    {
        if (pos > m_size) {
            throw std::out_of_range("Position is out of range");
        }

        size_t new_size = std::min(count, m_size - pos);
        ef_string sub_str;
        sub_str.reserve(new_size);

        for (size_t i = pos; i < pos + new_size; ++i) {
            sub_str.push_back(static_cast<char>(m_bits[i].a));
        }

        return sub_str;
    }

    size_t ef_string::find(const ef_string& str, size_t pos) const
    {
        if (str.m_size == 0 || m_size < str.m_size || pos > m_size - str.m_size) {
            return npos;
        }

        for (size_t i = pos; i <= m_size - str.m_size; ++i) {
            bool found = true;
            for (size_t j = 0; j < str.m_size; ++j) {
                if (m_bits[i + j].a != str.m_bits[j].a) {
                    found = false;
                    break;
                }
            }
            if (found) {
                return i;
            }
        }

        return npos;
    }

    size_t ef_string::find(char ch, size_t pos) const
    {
        for (size_t i = pos; i < m_size; ++i) {
            if (m_bits[i].a == static_cast<unsigned>(ch)) {
                return i;
            }
        }

        return npos;
    }

    void ef_string::trimTrailingWhitespace()
    {
        size_t start{ find_first_not_of(' ') },
            end{ find_last_not_of(' ') };

        *this = substr(start, end - start + 1);
    }

    ef_string::operator std::string()
    {

        return std::string(c_str());

    }

    size_t ef_string::find_first_not_of(char c)  const
    {
        for (auto i = 0u; i < m_size; ++i)
        {
            if (m_bits[i] != c)
            {
                return i;
            }
        }

        return npos;
    }

    size_t ef_string::find_last_not_of(char c)  const
    {

        for (auto i = m_size - 1; i != 0; --i)
        {
            if (m_bits[i] != c)
            {
                return i;
            }
        }

        return npos;
    }

    size_t ef_string::find_first_of(char c) const
    {
        for (auto i = 0u; i < m_size; ++i)
        {
            if (m_bits[i] == c)
            {
                return i;
            }
        }


        return npos;
    }

    size_t ef_string::find_last_of(char c) const
    {
        size_t rc = npos;

        for (auto i = 0u; i < m_size; ++i)
        {
            if (m_bits[i] == c)
            {
                rc = i;
            }
        }

        return rc;
    }

    StringBit& ef_string::back()
    {
        if (m_size > 0)
        {
            return m_bits[m_size - 1];
        }
        throw std::out_of_range("Subscript out of range");
        _RPTF0(_CRT_ASSERT, "Subscript Out Of Range");
    }

    StringBit& ef_string::front()
    {
        if (m_size >= 0)
        {
            return m_bits[0];
        }
        throw std::out_of_range("Subscript out of range");
        _RPTF0(_CRT_ASSERT, "Subscript Out Of Range");
    }

    ef_string& ef_string::erase(size_t pos, size_t count)
    {
        // Check if the position is within the bounds of the string
        if (pos >= m_size) {
            _RPTF0(_CRT_ASSERT, "Subscript Out Of Range");
            throw std::out_of_range("Subscript out of range");
        }
        else if (pos + count > m_size)
        {
            _RPTF0(_CRT_ASSERT, "Subscript Out Of Range");
            throw std::out_of_range("Subscript out of range");
        }

        m_bits.erase(m_bits.begin() + pos, m_bits.begin() + pos + count);


        // Reduce the size of the string
        resize(m_bits.size());

        return *this;
    }

    ef_string::reverse_iterator ef_string::rbegin() {
        if (m_bits.empty()) {
            return m_bits.rend();
        }
        return std::prev(m_bits.rend());
    }

    ef_string::reverse_iterator ef_string::rend() {
        if (m_bits.empty()) {
            return m_bits.rend();
        }
        return m_bits.rbegin();
    }

    ef_string::const_reverse_iterator ef_string::rbegin() const {
        if (m_bits.empty()) {
            return m_bits.crend();
        }
        return std::prev(m_bits.crend());
    }

    ef_string::const_reverse_iterator ef_string::rend() const {
        if (m_bits.empty()) {
            return m_bits.crend();
        }
        return m_bits.crbegin();
    }

    ef_string::const_reverse_iterator ef_string::crbegin() const {
        if (m_bits.empty()) {
            return m_bits.crend();
        }
        return std::prev(m_bits.crend());
    }

    ef_string::const_reverse_iterator ef_string::crend() const {
        if (m_bits.empty()) {
            return m_bits.crend();
        }
        return m_bits.crbegin();
    }


    ef_string::iterator ef_string::begin() {
        if (m_bits.empty()) {
            return m_bits.end();
        }
        return m_bits.begin();
    }


    ef_string::iterator ef_string::end() {
        if (m_bits.empty()) {
            return m_bits.end();
        }
        return std::prev(m_bits.end());
    }

    ef_string::const_iterator ef_string::begin() const {
        if (m_bits.empty()) {
            return m_bits.cend();
        }
        return m_bits.begin();
    }

    ef_string::const_iterator ef_string::end() const {
        if (m_bits.empty()) {
            return m_bits.cend();
        }
        return std::prev(m_bits.cend());
    }

    ef_string::const_iterator ef_string::cbegin() const {
        if (m_bits.empty()) {
            return m_bits.cend();
        }
        return m_bits.begin();
    }

    ef_string::const_iterator ef_string::cend() const {
        if (m_bits.empty()) {
            return m_bits.cend();
        }
        return std::prev(m_bits.cend());
    }

    size_t ef_string::length() const
    {
        return m_size;
    }

    size_t ef_string::max_size() const
    {
        return m_bits.max_size();
    }

    void ef_string::swap(ef_string& other)
    {
        ef_string buffer(move(other));

        other = move(*this);

        *this = move(buffer);

    }

    string ef_string::inString() const
    {

        return string(this->c_str());

    }

    void ef_string::assign(const char* other)
    {
        *this = other;
    }

    void ef_string::assign(std::string other)
    {
        *this = other.c_str();
    }

    ef_string& ef_string::insert(size_t pos, const ef_string& str)
    {
        if (pos > m_size)
        {
            throw std::out_of_range("Subscript out of range");
            _RPTF0(_CRT_ASSERT, "Subscript Out Of Range");
        }
        else if (pos == m_size)
        {
            *this += str;
            return *this;
        }

        size_t temp_size = m_size - pos;

        vector<StringBit> temp;

        for (auto i = 0u; i < pos; ++i)
        {
            temp.push_back(m_bits[i]);
        }

        for (auto i = 0u; i < str.m_size; ++i)
        {
            temp.push_back(str.m_bits[i]);
        }

        for (auto i = m_size - temp_size; i < m_size; ++i)
        {
            temp.push_back(m_bits[i]);
        }

        m_size = temp.size();
        m_bits = move(temp);

        return *this;
    }


    ef_string& ef_string::insert(size_t pos, const ef_string& str, size_t subpos, size_t sublen)
    {
        if (subpos > str.m_size)
        {
            return *this;
        }
        sublen = std::min(sublen, str.m_size - subpos);
        ef_string sub_str = str.substr(subpos, sublen);
        return insert(pos, sub_str);
    }

    ef_string& ef_string::insert(size_t pos, const char* s)
    {
        ef_string str(s);
        return insert(pos, str);
    }

    ef_string& ef_string::insert(size_t pos, const char* s, size_t n)
    {
        ef_string str(s, n);
        return insert(pos, str);
    }

    ef_string& ef_string::insert(size_t pos, size_t n, char c)
    {
        ef_string str(n, c);
        return insert(pos, str);
    }

    char* ef_string::data()
    {

        return reinterpret_cast<char*>(m_bits.data());
    }

    size_t ef_string::reserve() const
    {
        return m_bits.capacity();
    }

    ef_string& ef_string::replace(size_t pos, size_t len, const ef_string& str)
    {
        if (pos >= m_size)
        {
            _RPTF0(_CRT_ASSERT, "Pos Is Out Of Range");
            throw out_of_range("Pos is out of range");
        }

        if (len >= m_size && pos == 0u)
        {
            *this = str;

            return *this;
        }

        vector<StringBit> temp{};

        size_t curr_size = m_size;

        size_t temp_len = len;

        for (auto i = 0u; i < pos; ++i)
        {
            --curr_size;
            temp.push_back(m_bits[i]);
        }

        for (auto i = 0u; i < len && i < str.m_size; ++i)
        {
            --temp_len;
            --curr_size;
            temp.push_back(str.m_bits[i]);
        }

        if (temp.size() < m_size)
        {
            size_t curr_pos = temp.size() - 1,
                start = curr_pos + temp_len + 1,
                end = curr_size + curr_pos + 1;
            for (auto i = start; i < curr_size + curr_pos + 1; ++i)
            {
                temp.push_back(m_bits[i]);
            }
        }
        m_size = temp.size();
        m_bits = move(temp);



        return *this;
    }

    ef_string& ef_string::replace(size_t pos, size_t len, const ef_string& str, size_t subpos, size_t sublen)
    {
        if (subpos > str.m_size)
        {
            return *this;
        }
        sublen = std::min(sublen, str.m_size - subpos);
        ef_string sub_str = str.substr(subpos, sublen);
        return replace(pos, len, sub_str);
    }

    ef_string& ef_string::replace(size_t pos, size_t len, const char* s)
    {
        ef_string str(s);
        return replace(pos, len, str);
    }

    ef_string& ef_string::replace(size_t pos, size_t len, const char* s, size_t n)
    {
        ef_string str(s, n);
        return replace(pos, len, str);
    }

    ef_string& ef_string::replace(size_t pos, size_t len, size_t n, char c)
    {
        ef_string str(n, c);
        return replace(pos, len, str);
    }


    size_t ef_string::rfind(const ef_string& str, size_t pos) const
    {
        if (str.empty()) return pos == npos ? m_size : std::min(pos, m_size);

        if (m_size < str.m_size) return npos;

        size_t end_pos = pos == npos ? m_size - str.m_size : std::min(pos, m_size - str.m_size);

        for (size_t i = end_pos + 1; i-- > 0;) {
            if (this->substr(i, str.m_size) == str) {
                return i;
            }
        }
        return npos;
    }

    size_t ef_string::rfind(const char* s, size_t pos) const {
        return rfind(ef_string(s), pos);
    }

    size_t ef_string::rfind(const char* s, size_t pos, size_t n) const {
        return rfind(ef_string(s, n), pos);
    }

    size_t ef_string::rfind(char c, size_t pos) const {
        if (m_size == 0) return npos;

        int end_pos = pos == npos ? static_cast<int>(m_size - 1) : static_cast<int>(std::min(pos, m_size - 1));
        end_pos -= 1;

        for (int i = end_pos; i >= 0; --i) {
            if ((*this)[i] == c) {
                return static_cast<size_t>(i);
            }
        }
        return npos;
    }


    size_t ef_string::copy(char* destination, size_t len, size_t pos) const
    {
        if (pos >= m_size) {
            return 0;
        }

        size_t copied = 0;
        for (; copied < len && pos + copied < m_size; ++copied) {
            destination[copied] = static_cast<char>(m_bits[pos + copied].a);
        }

        return copied;
    }




    bool ef_string::compare(ef_string& str) const
    {
        return *this == str;
    }

    bool ef_string::compare(std::string& str) const
    {
        return *this == str;
    }

    bool ef_string::compare(const char* str) const
    {
        return *this == str;
    }

    size_t ef_string::find_first_not_of(const char* s, size_t pos) const
    {
        if (pos >= m_size) {
            return npos;
        }

        for (size_t i = pos; i < m_size; i++) {
            bool found = false;
            for (size_t j = 0; s[j] != '\0'; j++) {
                if (m_bits[i].a == s[j]) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                return i;
            }
        }

        return npos;
    }

    size_t ef_string::find_first_not_of(const char* s, size_t pos, size_t n) const
    {
        if (pos >= m_size) {
            return npos;
        }

        size_t endPos = std::min(pos + n, m_size);
        for (size_t i = pos; i < endPos; i++) {
            bool found = false;
            for (size_t j = 0; s[j] != '\0'; j++) {
                if (m_bits[i].a == s[j]) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                return i;
            }
        }

        return npos;
    }

    size_t ef_string::find_first_not_of(const std::string& str, size_t pos) const
    {
        return find_first_not_of(str.c_str(), pos, str.length());
    }

    size_t ef_string::find_first_not_of(const std::string& str, size_t pos, size_t n) const
    {
        return find_first_not_of(str.c_str(), pos, std::min(n, str.length()));
    }

    size_t ef_string::find_first_not_of(const std::ef_string& str, size_t pos) const
    {
        return find_first_not_of(str.c_str(), pos, str.length());
    }

    size_t ef_string::find_first_not_of(const std::ef_string& str, size_t pos, size_t n) const
    {
        return find_first_not_of(str.c_str(), pos, std::min(n, str.length()));
    }

    size_t ef_string::find_last_not_of(const char* s, size_t pos) const
    {
        if (m_size == 0) {
            return npos;
        }
        if (pos >= m_size) {
            pos = m_size - 1;
        }

        for (size_t i = pos; i != npos; i--) {
            bool found = false;
            for (size_t j = 0; s[j] != '\0'; j++) {
                if (m_bits[i].a == s[j]) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                return i;
            }
        }

        return npos;
    }

    size_t ef_string::find_last_not_of(const char* s, size_t pos, size_t n) const
    {
        if (m_size == 0) {
            return npos;
        }
        size_t startPos = std::min(pos, m_size - 1);
        size_t endPos = std::max(startPos - n, static_cast<size_t>(0));

        for (size_t i = startPos; i != endPos - 1; i--) {
            bool found = false;
            for (size_t j = 0; s[j] != '\0'; j++) {
                if (m_bits[i].a == s[j]) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                return i;
            }
        }

        return npos;
    }

    size_t ef_string::find_last_not_of(const std::string& str, size_t pos) const
    {
        return find_last_not_of(str.c_str(), pos, str.length());
    }

    size_t ef_string::find_last_not_of(const std::string& str, size_t pos, size_t n) const
    {
        return find_last_not_of(str.c_str(), pos, std::min(n, str.length()));
    }

    size_t ef_string::find_last_not_of(const std::ef_string& str, size_t pos) const
    {
        return find_last_not_of(str.c_str(), pos, str.length());
    }

    size_t ef_string::find_last_not_of(const std::ef_string& str, size_t pos, size_t n) const
    {
        return find_last_not_of(str.c_str(), pos, std::min(n, str.length()));
    }

    size_t ef_string::find_first_of(const char* s, size_t pos) const
    {
        if (pos >= m_size) {
            return npos;
        }

        for (size_t i = pos; i < m_size; i++) {
            for (size_t j = 0; s[j] != '\0'; j++) {
                if (m_bits[i].a == s[j]) {
                    return i;
                }
            }
        }

        return npos;
    }

    size_t ef_string::find_first_of(const char* s, size_t pos, size_t n) const
    {
        if (pos >= m_size) {
            return npos;
        }
        size_t endPos = std::min(pos + n, m_size);

        for (size_t i = pos; i < endPos; i++) {
            for (size_t j = 0; s[j] != '\0'; j++) {
                if (m_bits[i].a == s[j]) {
                    return i;
                }
            }
        }

        return npos;
    }

    size_t ef_string::find_first_of(const std::string& str, size_t pos) const
    {
        return find_first_of(str.c_str(), pos, str.length());
    }

    size_t ef_string::find_first_of(const std::string& str, size_t pos, size_t n) const
    {
        return find_first_of(str.c_str(), pos, std::min(n, str.length()));
    }

    size_t ef_string::find_first_of(const std::ef_string& str, size_t pos) const
    {
        return find_first_of(str.c_str(), pos, str.length());
    }

    size_t ef_string::find_first_of(const std::ef_string& str, size_t pos, size_t n) const
    {
        return find_first_of(str.c_str(), pos, std::min(n, str.length()));
    }

    size_t ef_string::find_last_of(const char* s, size_t pos) const
    {
        if (m_size == 0) {
            return npos;
        }
        if (pos >= m_size) {
            pos = m_size - 1;
        }

        for (size_t i = pos; i != npos; i--) {
            for (size_t j = 0; s[j] != '\0'; j++) {
                if (m_bits[i].a == s[j]) {
                    return i;
                }
            }
        }

        return npos;
    }

    size_t ef_string::find_last_of(const char* s, size_t pos, size_t n) const
    {
        if (m_size == 0) {
            return npos;
        }
        size_t startPos = std::min(pos, m_size - 1);
        size_t endPos = std::max(startPos - n, static_cast<size_t>(0));

        for (size_t i = startPos; i != endPos - 1; i--) {
            for (size_t j = 0; s[j] != '\0'; j++) {
                if (m_bits[i].a == s[j]) {
                    return i;
                }
            }
        }

        return npos;
    }

    size_t ef_string::find_last_of(const std::string& str, size_t pos) const
    {
        return find_last_of(str.c_str(), pos, str.length());
    }

    size_t ef_string::find_last_of(const std::string& str, size_t pos, size_t n) const
    {
        return find_last_of(str.c_str(), pos, std::min(n, str.length()));
    }

    size_t ef_string::find_last_of(const std::ef_string& str, size_t pos) const
    {
        return find_last_of(str.c_str(), pos, str.length());
    }

    size_t ef_string::find_last_of(const std::ef_string& str, size_t pos, size_t n) const
    {
        return find_last_of(str.c_str(), pos, std::min(n, str.length()));
    }

}

