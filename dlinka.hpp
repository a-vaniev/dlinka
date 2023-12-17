#include <cmath>
#include <string>

namespace dlinka
{
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
            return result;
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
            verylong result;
            verylong one(1);
            long long cnt = 0;
            verylong temp = *this;
            while (true)
            {
                try
                {
                    temp = temp - other;
                    result = result + one;
                    // cnt++;
                }
                catch (...)
                {
                    break;
                }
            }
            // result.setLL(cnt);
            return result;
        }

    private:
        const long long base = 1000000000;
        std::vector<long long> value;

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
