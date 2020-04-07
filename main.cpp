#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

std::vector<unsigned char> pictures;

void loadTexture(std::string path){
    std::ifstream file;
    file.open( path.c_str(), ios::binary | ios::in );

    std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(file), {});
    pictures.insert( pictures.end(), buffer.begin(), buffer.end() );

    file.close();
}

void saveTexture3D(std::string path){
    std::ofstream file;
    file.open( path.c_str(), ios::binary | ios::out );

    file.write((char*)&pictures[0], pictures.size() * sizeof(unsigned char));

    file.close();
}

void createDescriptor(std::string path, int frameCount, int x, int y){
    std::ofstream file;
    file.open(path.c_str());

    file << "frameCount:" << frameCount << endl;
    file << "X:" << x << endl;
    file << "Y:" << y << endl;
    file << "interpolation:1" << endl;

    file.close();
}

int main(int argc, char* argv[])
{
    if(argc < 5){
        cout << "Invalid arguments (name, frameCount, sizeX, sizeY)" << endl;
    }
    int spriteCount = stoi(argv[2]);

    cout << "Loading textures..." << endl;

    for(int i=0; i<spriteCount; i++){
        std::stringstream path("");
        if(i < 10){
            path << argv[1] << "_00" << i << ".data";
        }else{
            path << argv[1] << "_0" << i << ".data";
        }

        loadTexture(path.str());
    }

    cout << "Writing new 3D texture..." << endl;

    saveTexture3D("newTexture.s3D");
    createDescriptor("newTexture.cfg", spriteCount, stoi(argv[3]), stoi(argv[4]));

    cout << "New texture generated!" << endl;

    return 0;
}
