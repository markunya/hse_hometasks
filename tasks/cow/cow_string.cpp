#include <stdexcept>
#include <cstring>
#include "cow_string.h"


ProxyChar::ProxyChar(size_t index, CowString* str) : index_(index), str_(str) {
}

ProxyChar::operator char() const {
    return str_->buffer_->buffer[index_];
}


ProxyChar& ProxyChar::operator=(const char symbol) {
    if (symbol == str_->buffer_->buffer[index_]) {
        return *this;
    }
    if (str_->buffer_->count == 1) {
        str_->buffer_->buffer[index_] = symbol;
        return *this;
    }
    CowStringBuffer* new_buffer = new CowStringBuffer();
    new_buffer->size = str_->buffer_->size;
    new_buffer->count = 1;
    new_buffer->buffer = new char[str_->buffer_->size];
    std::memcpy(new_buffer->buffer, str_->buffer_->buffer, str_->buffer_->size);
    new_buffer->buffer[index_] = symbol;
    str_->Delete();
    str_->buffer_ = new_buffer;
    return *this;
}

CowString::CowString(const CowString& other) : buffer_(other.buffer_) {
    ++buffer_->count;
}

CowString::CowString(CowStringBuffer* buffer) : buffer_(buffer) {
}

CowString::CowString(CowString&& other) {
    buffer_ = other.buffer_;
    ++buffer_->count;
}

CowString::CowString(std::string_view other) {
    buffer_ = new CowStringBuffer();
    buffer_->size = other.size();
    buffer_->buffer = new char[other.size()];
    std::memcpy(buffer_->buffer, other.data(), other.size());
    buffer_->count = 1;
}

void CowString::Delete() {
    --buffer_->count;
    if (buffer_->count == 0) {
        delete[] buffer_->buffer;
        delete buffer_;
    }
}

char* CowString::GetData() const {
    return buffer_->buffer;
}

CowString& CowString::operator=(CowString&& other) {
    if (this == &other) {
        return *this;
    }
    this->Delete();
    buffer_ = other.buffer_;
    ++buffer_->count;
    return *this;
}

CowString& CowString::operator=(const CowString& other) {
    if (this == &other) {
        return *this;
    }
    this->Delete();
    buffer_ = other.buffer_;
    ++buffer_->count;
    return *this;
}

bool CowString::operator==(const std::string_view other) const {
    if (other.size() != buffer_->size) {
        return false;
    }
    for (size_t i = 0; i < buffer_->size; ++i) {
        if (other[i] != buffer_->buffer[i]) {
            return false;
        }
    }
    return true;
}

bool CowString::operator==(const CowString& other) const {
    if (other.buffer_->size != buffer_->size) {
        return false;
    }
    for (size_t i = 0; i < buffer_->size; ++i) {
        if (other.buffer_->buffer[i] != buffer_->buffer[i]) {
            return false;
        }
    }
    return true;
}

CowString operator+(const CowString& other_1, const CowString& other_2) {
        if (other_1.buffer_->size == 0) {
            return CowString(other_2);
        }
        if (other_2.buffer_->size == 0) {
            return CowString(other_1);
        }
        CowStringBuffer* new_buffer = new CowStringBuffer();
        new_buffer->size = other_1.buffer_->size + other_2.buffer_->size;
        new_buffer->count = 1;
        new_buffer->buffer = new char[other_1.buffer_->size + other_2.buffer_->size];
        std::memcpy(new_buffer->buffer, other_1.buffer_->buffer, other_1.buffer_->size);
        std::memcpy(new_buffer->buffer + other_1.buffer_->size, other_2.buffer_->buffer, other_2.buffer_->size);
        return CowString(new_buffer);
}

CowString operator+(std::string_view other_1, const CowString& other_2) {
        if (other_2.buffer_->size == 0) {
            return CowString(other_1);
        }
        if (other_1.empty()) {
            return CowString(other_2);
        }
        CowStringBuffer* new_buffer = new CowStringBuffer();
        new_buffer->size = other_2.buffer_->size + other_1.size();
        new_buffer->count = 1;
        new_buffer->buffer = new char[other_2.buffer_->size + other_1.size()];
        std::memcpy(new_buffer->buffer, other_1.data(), other_1.size());
        std::memcpy(new_buffer->buffer + other_1.size(), other_2.buffer_->buffer, other_2.buffer_->size);
        return CowString(new_buffer);
}

CowString operator+(const CowString& other_1, std::string_view other_2) {
    if (other_1.buffer_->size == 0) {
            return CowString(other_2);
    }
    if (other_2.empty()) {
            return CowString(other_1);
    }
    CowStringBuffer* new_buffer = new CowStringBuffer();
    new_buffer->size = other_1.buffer_->size + other_2.size();
    new_buffer->count = 1;
    new_buffer->buffer = new char[other_1.buffer_->size + other_2.size()];
    std::memcpy(new_buffer->buffer, other_1.buffer_->buffer, other_1.buffer_->size);
    std::memcpy(new_buffer->buffer + other_1.buffer_->size, other_2.data(), other_2.size());
    return CowString(new_buffer);
}

CowString CowString::operator+=(const CowString& other) {
    if (other.buffer_->size == 0) {
        return *this;
    }
    CowStringBuffer* new_buffer = new CowStringBuffer();
    new_buffer->size = this->buffer_->size + other.buffer_->size;
    new_buffer->count = 1;
    new_buffer->buffer = new char[this->buffer_->size + other.buffer_->size];
    std::memcpy(new_buffer->buffer, this->buffer_->buffer, this->buffer_->size);
    std::memcpy(new_buffer->buffer + this->buffer_->size, other.buffer_->buffer, other.buffer_->size);
    this->Delete();
    this->buffer_ = new_buffer;
    return *this;
}

CowString CowString::operator+=(const std::string_view other) {
    if (other.empty()) {
        return *this;
    }
    CowStringBuffer* new_buffer = new CowStringBuffer();
    new_buffer->size = this->buffer_->size + other.size();
    new_buffer->count = 1;
    new_buffer->buffer = new char[this->buffer_->size + other.size()];
    std::memcpy(new_buffer->buffer, this->buffer_->buffer, this->buffer_->size);
    std::memcpy(new_buffer->buffer + this->buffer_->size, other.data(), other.size());
    this->Delete();
    this->buffer_ = new_buffer;
    return *this;
}

CowString::operator std::string_view() const {
    return std::string_view(buffer_->buffer);
}

ProxyChar CowString::operator[](size_t index) {
    return ProxyChar(index, this);
}

const char CowString::At(size_t index) const {
    if (index < buffer_->size) {
        return buffer_->buffer[index];
    }
    throw std::out_of_range("bustard");
}

CowStringIterator CowString::begin() {
    return CowStringIterator(0, this);
}

CowStringIterator CowString::end() {
    return CowStringIterator(buffer_->size, this);
}

ConstCowStringIterator CowString::begin() const {
    return ConstCowStringIterator(0, this);
}

ConstCowStringIterator CowString::end() const {
    return ConstCowStringIterator(0, this);
}


CowString::~CowString() {
    Delete();
}