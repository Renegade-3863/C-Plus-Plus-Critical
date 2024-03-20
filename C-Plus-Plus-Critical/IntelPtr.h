#pragma once
// <memory> library is needed for creating smart pointers
#include <memory>
#include <iostream>
#include <string>
#include <exception>

void normalAlloc(std::string& str) noexcept;

void smartAllocS(const std::string& str) throw(std::exception, int);

void smartAllocU(const std::string& str) throw(std::exception, int);

void DistSU(const std::string& str1, const std::string& str2) throw(std::exception, int);

void ProblemSptr(const std::string& str) throw(std::string);
