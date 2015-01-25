#ifndef MINMAX_H
#define MINMAX_H

#include <algorithm>

namespace my {

template<typename T>
const T& max(const T& a, const T& b)
{
    return (a < b) ? b : a;
}

template<typename T>
const T& min(const T& a, const T& b)
{
    return (a < b) ? a : b;
}

template<typename ForwordIt>
ForwordIt max_element(ForwordIt start, ForwordIt end)
{
    if (start == end) return end;
    ForwordIt largest = start;
    ++start;
    for (; start != end; ++start) {
        if (*largest < *start)
            largest = start;
    }
    return largest;
}

template<typename ForwordIt>
ForwordIt min_element(ForwordIt start, ForwordIt end)
{
    if (start == end) return end;
    ForwordIt smallest = start;
    ++start;
    for (; start != end; ++start) {
        if (*smallest > *start)
            smallest = start;
    }
    return smallest;
}

template<typename T>
std::pair<const T&, const T&> minmax(const T& a, const T& b)
{
    return (a < b) ? std::pair<const T&, const T&>(a, b)
                   : std::pair<const T&, const T&>(b, a);
}

template<typename ForwordIt>
std::pair<ForwordIt, ForwordIt> minmax_element(ForwordIt start, ForwordIt end)
{
    std::pair<ForwordIt, ForwordIt> result(start, start);
    if (start == end) return result;
    while (++start != end) {
        if (*start < *result.first)
            result.first = start;
        if (*start >= *result.second)
            result.second = start;
    }
    return result;
}

// only work on ascii
template<typename InputIt1, typename InputIt2>
bool lexicographical_compare(InputIt1 start1, InputIt1 end1,
        InputIt2 start2, InputIt2 end2)
{
    for (; start1 != end1 && start2 != end2; ++start1, ++start2) {
        if (*start2 > *start1) return true;
        if (*start2 < *start1) return false;
    }
    return start1 == end1 && start2 != end2;
}

template<typename ForwordIt1, typename ForwordIt2>
bool is_permutation(ForwordIt1 start1, ForwordIt1 end1,
        ForwordIt2 start2, ForwordIt2 end2)
{
   if (std::distance(start1, end1) != std::distance(start2, end2))
       return false;
   std::tie(start1, start2) = std::mismatch(start1, end1, start2);
   if (start1 != end1) {
       for (ForwordIt1 i = start1; i != end1; ++i) {
           if (i != std::find(start1, i, *i))
               continue;
           size_t match = std::count(start2, end2, *i);
           if (match == 0 || match != std::count(i, end1, *i))
               return false;
       }
   }
   return true;
}

template<typename BidirIt>
bool next_permutation(BidirIt start, BidirIt end)
{
    if (start == end || start + 1 == end) return false;
    BidirIt i = end - 1;
    while (true) {
        BidirIt i1 = i, i2;
        if (*--i < *i1) {
            i2 = end - 1;
            while (!(*i < *i2))
                i2--;
            std::iter_swap(i, i2);
            std::reverse(i1, end);
            return true;
        }
        if (i == start) {
            std::reverse(start, end);
            return false;
        }
    }
}

template<typename BidirIt>
bool prev_permutation(BidirIt start, BidirIt end)
{
    if (start == end || start + 1 == end) return false;
    BidirIt i = end - 1;
    while (true) {
        BidirIt i1 = i, i2;
        if (*i1 < *--i) {
            i2 = end - 1;
            while (!(*i2 < *i))
                i2--;
            std::iter_swap(i, i2);
            std::reverse(i1, end);
            return true;
        }
        if (i == start) {
            std::reverse(start, end);
            return false;
        }
    }
}
}

#endif /* MINMAX_H */
