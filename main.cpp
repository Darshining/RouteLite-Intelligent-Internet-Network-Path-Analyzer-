
#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
using namespace std;

// Base class
class NetworkNode
{
protected:
    string ip;

public:
    NetworkNode(string address)
    {
        ip = address;
    }

    virtual void display()
    {
        cout << "IP Address: " << ip << endl;
    }

    virtual ~NetworkNode() {}
};

// Derived class
class Destination : public NetworkNode
{
public:
    Destination(string address) : NetworkNode(address) {}

    virtual void display()
    {
        cout << "Destination IP: " << ip << endl;
    }
};

// Simulated DNS resolver
class DNSResolver
{
public:
    string resolve(string domain)
    {
        if (domain == "google.com")
            return "142.250.72.14";
        else if (domain == "youtube.com")
            return "142.250.72.46";
        else if (domain == "github.com")
            return "140.82.112.4";
        else
            throw runtime_error("Domain not found!");
    }
};

// Simulated route analyzer
class RouteAnalyzer
{
public:
    int trace(string ipAddress)
    {
        cout << "\nTracing route to " << ipAddress << "...\n";

        cout << "Hop 1: 192.168.1.1\n";
        cout << "Hop 2: 10.0.0.1\n";
        cout << "Hop 3: " << ipAddress << endl;

        return 3;
    }
};

// Route quality assessment
class RouteQuality
{
public:
    string check(int hops)
    {
        if (hops <= 5)
            return "GOOD";
        else if (hops <= 10)
            return "AVERAGE";
        else
            return "COMPLEX";
    }
};

// Template function
template <class T>
void showMessage(T message)
{
    cout << "\n" << message << endl;
}

int main()
{
    string domain;

    showMessage("ROUTELITE - NETWORK PATH ANALYZER");

    cout << "Enter domain (google.com, youtube.com, github.com): ";
    cin >> domain;

    try
    {
        DNSResolver dns;
        string ipAddress = dns.resolve(domain);

        cout << "\nDomain: " << domain << endl;
        cout << "Resolved IP: " << ipAddress << endl;

        Destination destination(ipAddress);

        // Pointer and runtime polymorphism
        NetworkNode *ptr = &destination;
        ptr->display();

        RouteAnalyzer analyzer;
        int hops = analyzer.trace(ipAddress);

        RouteQuality quality;
        string status = quality.check(hops);

        cout << "\nTotal Network Hops: " << hops << endl;
        cout << "Route Quality: " << status << endl;

        // Save report
        ofstream file("RouteLite.txt");

        if (!file.is_open())
            throw runtime_error("Unable to create result file!");

        file << "ROUTELITE - NETWORK PATH ANALYZER\n";
        file << "Domain: " << domain << endl;
        file << "Resolved IP: " << ipAddress << endl;
        file << "Number of Hops: " << hops << endl;
        file << "Route Quality: " << status << endl;

        file.close();

        cout << "\nResult saved to RouteLite.txt\n";
        showMessage("ANALYSIS COMPLETE");
    }
    catch (const exception &e)
    {
        cout << "\nError: " << e.what() << endl;
    }

    return 0;
}
