#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

using namespace std;

string getKeyFromFile(const filesystem::path& p) {
    std::ifstream infile(p.c_str());
    if (infile.fail()) {
        throw ios_base::failure("Unable to open file " + p.string());
    }

    string contents;
    string key;
    std::string line;
    bool copy = false;
    while (std::getline(infile, line))
    {
        //cout << line << endl;
        contents += line + '\n';
        if(string::npos != line.find("-----BEGIN RSA PRIVATE KEY-----")) {
            copy = true;
            continue;
        }
        if(copy && string::npos != line.find("-----END RSA PRIVATE KEY-----")) {
            copy = false;
            continue;
        }
        if (copy) {
            key += line;
            //cout << "<key>" << key << "</key>" << endl;
        }
    }
    cout << "contents:" << endl << contents << endl;
    cout << "<key>" << key << "</key>" << endl;

    return key;
}

string tag(const string& name, const string& value) {
    return "<" + name + ">" + value + "</" + name + ">";
}

string getKeyFromFile(const string& filename) {
    cout << endl << __func__ << ": " << filename << endl;
    filesystem::path path(filename);
    string key =  getKeyFromFile(path);
    cout << path.filename() << ":" << endl << tag(path.filename().string(), key)
    << endl;
    //<< "<key>" << key << "</key>" << endl;
    return key;
}


int main() {
    std::cout << "Hello, World!" << std::endl;

    //const string aName("C:\\Users\\cassi\\.ssh\\id_rsa");
    const string aName("C:\\Users\\cassi\\.ssh\\id_rsa.orig");
    filesystem::path aPath(aName);
    string aKey = getKeyFromFile(aName);

    string bName("C:\\Users\\cassi\\.ssh\\github_rsa");
    filesystem::path bPath(bName);
    string bKey = getKeyFromFile(bName);

    if( aKey != bKey ) {
        cout << "" << "different" << endl;
    } else {
        cout << "same" << endl;
    }
    cout << "\033[39m\\033[49m - Reset colour" << endl;

    return 0;
}
