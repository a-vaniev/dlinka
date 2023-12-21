#include <cmath>
#include <string>

namespace dlinka
{
    const long long base = 10; // Internal numeric system base. Better to use high bases to better use long long digits.

    // TODO Copyable / movable

    class verylong
    {
    public:
        verylong()
        {
        }

        verylong(long long val)
        {
            value.clear();
            while (val)
            {
                long long digit = val % base;
                val = val / base;
                value.push_back(digit);
            }
        }

        verylong(std::string val)
        {
            // TODO
        }

        verylong(const verylong &other)
        {
            value = other.value;
        }

        long long asLongLong() // Returns value as long long (may hit limit)
        {
            long long res = 0;
            long long coeff = 1;
            for (auto digit : value)
            {
                res += digit * coeff;
                coeff *= base;
            }
            return res;
        }

        std::string asString() // Returns value as string
        {
            // TODO
            return "YOBA";
        }

        verylong &operator=(verylong other)
        {
            std::swap(value, other.value);
            return *this;
        }

        // Arithmetic operators
        verylong operator+(verylong const &other)
        {
            auto max_digit = base - 1;
            verylong result;
            long long over = 0;
            long long i = 0;
            while (over || (i < std::max(value.size(), other.value.size())))
            {
                long long cur = ((i < value.size()) ? value[i] : 0);
                long long oth = ((i < other.value.size()) ? other.value[i] : 0);
                long long digit = cur + oth + over;
                if (digit > max_digit)
                {
                    over = digit / base;
                    digit = digit % base;
                }
                else
                {
                    over = 0;
                }
                result.value.push_back(digit);
                i++;
            }
            result.cutTail();
            return result;
        }

        bool operator>(verylong const &other)
        {
            if (value.size() > other.value.size())
                return true;
            if (value.size() < other.value.size())
                return false;
            for (long long i = other.value.size() - 1; i >= 0; i--)
            {
                if (value[i] > other.value[i])
                    return true;
                if (value[i] < other.value[i])
                    return false;
            }
            return false;
        }

        bool operator<(verylong const &other)
        {
            if (value.size() < other.value.size())
                return true;
            if (value.size() > other.value.size())
                return false;
            for (long long i = other.value.size() - 1; i >= 0; i--)
            {
                if (value[i] < other.value[i])
                    return true;
                if (value[i] > other.value[i])
                    return false;
            }
            return false;
        }

        bool operator==(verylong const &other)
        {
            if (this == &other)
                return true;
            if (value.size() != other.value.size())
                return false;
            auto ita = this->value.begin();
            auto itb = other.value.begin();
            for (; (ita < this->value.end()) && (itb < other.value.end()); ita++, itb++)
            {
                if (*ita != *itb)
                    return false;
            }
            return true;
        }

        verylong operator-(verylong const &other)
        {
            auto max_digit = base - 1;
            verylong result = *this;
            long long over = 0;
            for (long long i = 0; i < other.value.size(); i++)
            {
                result = (result.subtractDigit(other.value[i], i));
            }
result.cutTail();
            return result;
        }

        verylong operator*(verylong const &other)
        {
            verylong accum;
            for (long long j = 0; j < other.value.size(); j++)
            {
                verylong part = (this->mul_digit(other.value[j])).shift(j);
                accum = accum + part;
            }
            return accum;
        }

        verylong operator/(verylong const &other)
        {
            // Dumb subraction
            verylong result;
            verylong one(1);
            long long cnt = 0;
            verylong temp(*this);
            while (temp > other)
            {
                try
                {
                    temp = temp - other;
                    result = result + one;
                }
                catch (...)
                {
                    break;
                }
            }
            result.cutTail();
            return result;
        }

    private:
        std::vector<long long> value;

        //Cut leading zeros
        void cutTail()
        {
        auto it = this->value.rbegin();
        for (;it<this->value.rend();it++)
        {
        if(*it!=0)break;
        }
        if(it!=value.rbegin())
        {
            value.erase(it.base(),value.rbegin().base());
        }
    }
        // Supplementary calculation functions
        verylong shift(long long pos)
        {
            verylong result;
            while (pos--)
                result.value.push_back(0);
            for (auto d : value)
                result.value.push_back(d);
            return result;
        }

        verylong subtractDigit(long long digit, long long pos)
        {
            if (pos >= value.size())
            {
                throw std::exception();
            };
            verylong result = *this;
            if (value[pos] >= digit)
            {
                result.value[pos] -= digit;
            }
            else
            {
                result = this->subtractDigit(1, pos + 1);
                result.value[pos] = base + result.value[pos] - digit;
            }
            return result;
        }

        verylong mul_digit(long long multiplier)
        {
            auto max_digit = base - 1;
            verylong result;
            long long over = 0;

            long long i = 0;
            while (over || (i < value.size()))
            {
                long long cur = ((i < value.size()) ? value[i] : 0);
                long long digit = cur * multiplier + over;
                if (digit > max_digit)
                {
                    over = digit / base;
                    digit = digit % base;
                }
                else
                {
                    over = 0;
                }
                result.value.push_back(digit);
                i++;
            }
            return result;
        }
    };
} // namespace
