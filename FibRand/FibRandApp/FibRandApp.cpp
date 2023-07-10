// FibRandApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
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
double CalculateFibonacci(int value, unsigned long& iteration, double& n_1, double& n_2, double gr)
{
    double fib = value ? n_1 + n_2 : n_1 - n_2;
    double result = abs(fib / n_1);
    n_2 = n_1;
    n_1 = fib;
    iteration++;
    return result;
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
        double n_1 = 1, n_2 = 1;
        for (int i = 0; i < bytes.size(); i++)
        {
            for(int b = 0; b<8; b++)
            {
                auto val = CalculateFibonacci((bytes[i] >> b) & 0b00000001, counter, n_1, n_2, gr);
                if(counter % 100 == 0)
                    cout << val << "\n";
            }
        }
    }
    else if(op == "write")
    {
        vector<unsigned char> bytes;
        for (int i = 0; i < 10000000; i++)
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
