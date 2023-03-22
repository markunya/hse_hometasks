#pragma once

#include <cstddef>
#include <string_view>
#include "proxy_char.h"
#include "cow_string_buffer.h"

class CowStringIterator;
class ConstCowStringIterator;
class CowString;

class ProxyChar {
public:
    explicit ProxyChar(size_t index, CowString *str);

    operator char() const;

    ProxyChar& operator=(const char symbol);

private:
    size_t index_;
    CowString* str_;
};


class CowString {
public:
    friend class ProxyChar;
    friend class CowStringIterator;
    friend class ConstCowStringIterator;
    friend CowString operator+(std::string_view other_1, const CowString& other_2);
    friend CowString operator+(const CowString& other_1, std::string_view other_2);
    friend CowString operator+(const CowString& other_1, const CowString& other_2);

    explicit CowString(CowStringBuffer* buffer);
    CowString(const CowString& other);
    explicit CowString(const std::string_view other);
    CowString(CowString&& other);

    void Delete();
    char* GetData() const;

    operator std::string_view() const;
    CowString& operator=(CowString&& other);
    CowString& operator=(const CowString& other);
    bool operator==(const std::string_view other) const;
    bool operator==(const CowString& other) const;
    CowString operator+=(const CowString& other);
    CowString operator+=(const std::string_view other);
    ProxyChar operator[](size_t index);
    const char At(size_t index) const;

    CowStringIterator begin();
    CowStringIterator end();
    ConstCowStringIterator begin() const;
    ConstCowStringIterator end() const;

    ~CowString();
private:
    CowStringBuffer* buffer_;
};


class CowStringIterator {
public:
    explicit CowStringIterator(size_t index, CowString *str) : index_(index), str_(str) {}

    CowStringIterator* operator++() {
        ++index_;
        return this;
    }

    bool operator!=(const CowStringIterator& other) const {
        return index_ != other.index_;
    }

    ProxyChar operator*() {
        return ProxyChar(index_, str_);
    }

private:
    size_t index_;
    CowString* str_;
};

class ConstCowStringIterator {
public:
    explicit ConstCowStringIterator(size_t index, const CowString *str) : index_(index), cstr_(str) {}

    ConstCowStringIterator* operator++() {
        ++index_;
        return this;
    }

    bool operator!=(const ConstCowStringIterator& other) const {
        return index_ != other.index_;
    }

    const char operator*() const {
        return cstr_->buffer_->buffer[index_];
    }

private:
    size_t index_;
    const CowString* cstr_;
};