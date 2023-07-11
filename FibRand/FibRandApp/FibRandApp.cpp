// FibRandApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
const double leo = 1.1319882487943;
double GetGoldenRatio()
{
    return (1.0 + std::sqrt(5.0)) / 2.0;
}
double GetGrowthRate(double gr, double value)
{
    auto a = std::pow(gr, value);
    auto b = std::pow(-1.0 / gr, value);
    auto c = std::sqrt(5.0);
    return (a - b) / c;
}
long long CalculateFibonacci(int value, unsigned long& iteration, long long& n_1, long long& n_2, double gr, long long& max)
{
    long long fib = abs(value ? n_1 + n_2 : n_1 - n_2);
    //if(!isfinite(fib))
    //{
    //    long double div = std::pow(10, 20);
    //    n_1 /= div;
    //    n_2 /= div;
    //    fib = value ? n_1 + n_2 : n_1 - n_2;
    //}
    n_2 = n_1;
    n_1 = fib;
    iteration++;
    return fib;
}
vector<char> GetBytes(string path)
{
    std::ifstream is{ path, std::ios::binary | std::ios::ate };
    if (!is)
        throw runtime_error("Error while opening file");
    auto size = is.tellg();
    vector<char> bytes(size);
    is.seekg(0);
    if (!is.read(bytes.data(), size))
        throw runtime_error("Error while reading file");
    is.close();
    return bytes;
}
void WriteBytes(vector<unsigned char> bytes, string path)
{
    ofstream fout;
    fout.open(path, ios::binary | ios::out);
    fout.write((char*)&bytes[0], sizeof(unsigned char) * bytes.size());
    fout.close();
}
int main(int c, char* v[])
{
    if (c != 3)
    {
        cout << "Usage: FibRandApp read/write <path>\n";
        return 1;
    }
    std::string op = string(v[1]);
    auto gr = GetGoldenRatio();
    if(op == "read")
    {
        auto bytes = GetBytes(v[2]);
        unsigned long counter = 1;
        long long n_1 = 1, n_2 = 1, max = 1;
        for (int i = 0; i < bytes.size(); i++)
        {
            for(int b = 0; b<8; b++)
            {
                long long val = CalculateFibonacci((bytes[i] >> b) & 0b00000001, counter, n_1, n_2, gr, max);
                max = std::max(max, val);
                double pow_val = std::pow((double)val, 1.0 / (double)counter);
                cout << pow_val << " (" << (std::abs(pow_val - leo)/leo)*100.0 << "%)\n";
                std::cin.get();
            }
        }
    }
    else if(op == "write")
    {
        vector<unsigned char> bytes;
        for (int i = 0; i < 100000000; i++)
        {
            bytes.push_back(rand());
        }
        WriteBytes(bytes, v[2]);
    }
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
