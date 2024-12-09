#ifndef FILEOPERATOR_H
#define FILEOPERATOR_H
#include <fstream>
#include <string>

class FileOperator 
{
    public:
        // konsturktor
        FileOperator(std::string path);
        
        // destruktor
        virtual ~FileOperator() = 0;

        // vraca true ako je fajl trenutno otvoren
        bool isActive();

        // otvara fajl ako fajl nije trenutno otvoren
        virtual void openFile();

        // zatvara fajl ako je fajl trenutno otvoren
        virtual void closeFile();

    protected:
        std::ifstream *file;
        std::string path;
    
    private:
        bool active;
};

inline bool FileOperator::isActive()
{
    return active;
}

inline void FileOperator::openFile()
{
    if (!active)
    {
        file = new std::ifstream(path);
        active = true;
    }
}

inline void FileOperator::closeFile()
{
    if (active)
    {
        file->close();
        active = false;
    }
}

inline FileOperator::FileOperator(std::string path): path(path), active(true)
{
    file = new std::ifstream(path);
}

#endif 