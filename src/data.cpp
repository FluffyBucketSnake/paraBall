#include <data.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

void DataFile::Open(const std::string &filePath)
{
    //Check if file exists. If not, create it.
    struct stat buffer;
    if (stat(filePath.c_str(),&buffer) != 0)
    {
        //Create a file.
        Stream.open(filePath,std::ios::out);
        //Fill it with the default settings.
        Save();
    }
    //Open file.
    Stream.open(filePath,std::ios::in | std::ios::out | std::ios::binary);
}

void DataFile::Load()
{
    //Check if stream is open.
    if (!Stream.is_open())
        return;
    //Move the stream's read cursor to the beggining.
    Stream.seekg(0);
    //Read all the file until it reach end of the file or data.
    Stream.read(reinterpret_cast<char*>(&LoadedData.WindowFlags),sizeof(Uint32));
    Stream.read(reinterpret_cast<char*>(&LoadedData.Resolution.x),sizeof(int));
    Stream.read(reinterpret_cast<char*>(&LoadedData.Resolution.y),sizeof(int));
    Stream.read(reinterpret_cast<char*>(&LoadedData.MaxFps),sizeof(int));
    Stream.read(reinterpret_cast<char*>(&LoadedData.MasterVolume),sizeof(int));
}

void DataFile::Save()
{
    //Check if stream is open.
    if (!Stream.is_open())
        return;
    //Move the stream's write cursor to the beggining.
    Stream.seekp(0);
    //Save the data.
    Stream.write(reinterpret_cast<const char*>(&LoadedData.WindowFlags),sizeof(Uint32));
    Stream.write(reinterpret_cast<const char*>(&LoadedData.Resolution.x),sizeof(int));
    Stream.write(reinterpret_cast<const char*>(&LoadedData.Resolution.y),sizeof(int));
    Stream.write(reinterpret_cast<const char*>(&LoadedData.MaxFps),sizeof(int));
    Stream.write(reinterpret_cast<const char*>(&LoadedData.MasterVolume),sizeof(int));
    //Flush it down.
    Stream.flush();
}

void DataFile::Close()
{
    //Check if stream is open. If it is, close it.
    if (Stream.is_open())
        Stream.close();
}